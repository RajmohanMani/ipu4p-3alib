/*
 * Copyright (C) 2015 - 2018 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef IA_CAMERA_GCSS_GRAPH_UTILS_GRAPH_UTILS_H_
#define IA_CAMERA_GCSS_GRAPH_UTILS_GRAPH_UTILS_H_

#include <memory>
#include <functional>
#include <set>

extern "C" {
#include "ia_isp_bxt_types.h"
}
#include "gcss.h"

namespace GCSS {


/**
 * \class GraphUtil
 *
 * This class implements similar functionality as BxtAicUtils. It is meant as
 * a replacement for IPU graphs that contain more explicit graph information.
 * It is then an internal implementation detail of BxtAicUtils that has more
 * capabilities.
 *
 * This class analyses the graph settings and creates a representation
 * of the graph and inner imaging graphs.
 *
 * This representation does not duplicate data, just stores it in a more
 * convenient way to perform graph operations.
 *
 * We need to separate conceptually the XML data stored in IGraphConfig containers
 * (that is also stored as a tree of nodes) from the actual graph that represents
 * the information stored, the graph that represents an imaging system.
 * For that we formalise the following concepts:
 * - Container graph: This is the graph made out of IGraphConfig nodes. It is a
 *   representation of the XML hierarchical structure. The information stored
 *   in this graph is a 1:1 mapping with the XML data. IGraphConfig methods
 *   helps us to traverse this graph and find information from the nodes (xml
 *   tags) and xml attributes.
 *
 * - Camera Graph: this is the graph that represents a camera subsystem. The nodes
 *   in this graph are sensor, buffer source/sinks and processing nodes like
 *   Program Groups (FW).
 *
 * - Imaging Graph: This is the graph that represents the image processing
 * nodes inside the camera graph processing nodes (ex: PG). The nodes of
 * this graph are imaging kernels (PAL/ATE), routing elements (mux/demux/split)
 * and also PG ports because one imaging graph may expand multiple PG's
 *
 * - Meta-graph: This is the graph made out of camera subgraphs. The Camera graph
 * may group its nodes in two different ways:
 *   - stream-id: this traditionally aligns with the video/still/IR pipes.
 *   - execution context id: This grouping is done to split the nodes in separate
 *   threads (execution contexts). Only used by CISU.
 *
 * Conceptually the last three graphs are nested, the metagraph is at the top,
 * then the camera graph and finally the imaging graph.
 *
 * The imaging graphs are split per subgraph id because the structures given to
 * PAL are also grouped by subgraph id, whatever this may be (stream-id or exec-ctx)
 *
 * The container graph is the data storage that is passed during the initialisation
 * of this class, but the other three graphs are now represented by the
 * following member variables of this class:
 * - Camera Graph: mGraphNodes
 * - MetaGraph : mSubGraphInfoMap
 * - Imaging Graph: inside a a subgraph info map entry as imagingGraph.
 *
 * All the nodes of these three graphs derived from the same base struct that
 * contains the needed fields to traverse those graphs in topological order.
 * This is, a bi-directional adjacently list.
 * With this representation it is very easy to perform any type of operation in
 * topological order. We use the same algorithm (Graph Depth First) implemented
 * in method traverseGraph with different visitor functions.
 * Same scheme can be used at any of those 3 levels.
 *
 * At the moment the visitors are used for:
 * - Dumping information in traces for each node (for the 3 graphs)
 * - Calculating the resolution history of the imaging kernels
 * - detecting subgraph boundaries at the camera graph
 *
 * Any new operation on the graph only requires a new visitor function at the
 * correct level of detail (meta-graph, graph or imaging-graph)
 *
 */
class GraphUtil
{
public:
    GraphUtil();
    ~GraphUtil();
    /**
     * Initialise the GraphUtils class.
     * During this call the class will analyse the graph settings and create
     * structures to store the information of the imaging kernels found.
     * It creates
     * \param[in] subgraphType either GCSS_KEY_STREAM_ID or GCSS_ID_EXEC_CTX
     *                         It determines what type of subgraph will be used
     *                         to group the kernels.
     * \param[out] gcHandle Pointer to a IGraphConfig Object that represents
     *                      some graph-settings.
     * \return css_err_none if everything is fine
     * \return css_err_no_memory if there is some problem allocating the new
     *                           structures.
     * \return css_err_internal if there is some problem with the graph settings
     *                          being analysed
     */
    css_err_t init(ia_uid subgraphType, const IGraphConfig *gcHandle);

    /* Query methods */
    /**
     * isInitialized
     * returns true if the class was initialised with some settings
     */
    inline bool isInitialized() { return (mGraphSettings != nullptr); }
    /**
     * Get program group by execution context Id or stream id
     *
     *
     * Fills the provided structure with the relevant data for that subgraph
     * id provided. This id needs to be align with the construction time parameter.
     * i.e. you cannot construct this object with GCSS_KEY_STREAM_ID and then
     * pass a execution ctx id to this method.
     *
     * The granularity of the subgraphs is different and it should match the
     * granularity of the AIC execution.
     *
     * \param[in] subgraphId A stream id (or exec Ctx) of the program group
     *                      being requested.
     *                      The concrete value needs to be in sync with the input
     *                      parameter during initialisation call.
     * \param[out] pg reference to a program group struct being populated
     *
     * \return css_err_none if everything is fine.
     * \return css_err_data if the subgraph does not contain any subgraphs with
     *                      the requested id.
     */
    css_err_t getAicData(int32_t subgraphId, ia_isp_bxt_program_group &pg);
    /**
     * Debugging tool to dump to error traces the AIC structures of the given
     * subgraph id.
     * \param[in] subgraphId
     */
    void dumpKernels(int32_t subgraphId);

private: // types
    /**
     * \struct KernelInfoMemPool
     * structure to associate the array of run kernel structs for each subgraph-id
     * and the resolution info structures allocated for each kernel.
     * Each kernel needs two, the size of these vector should
     * match the number of kernels in a given subgraph-id.
     * This struct is used only for memory management purposes (allocate/free).
     * We need this for two reasons:
     * - because the structure ia_isp_bxt_run_kernels_t has pointers to two
     *   structures of type ia_isp_bxt_resolution_info_t that may be null.
     * - because the interface of AIC requires a C-style array of run kernels
     *   structures
     */
    struct KernelInfoMemPool {
           ia_isp_bxt_run_kernels_t *runKernels;
           std::vector<ia_isp_bxt_resolution_info_t *> resHistorys;
           std::vector<ia_isp_bxt_resolution_info_t *> resInfos;
    };
    /**
     * \enum
     * Type of the inner graph nodes
     */
    enum ImagingNodeType {
            IMAGING_NODE_KERNEL,
            IMAGING_NODE_MUX,
            IMAGING_NODE_DEMUX,
            IMAGING_NODE_SPLIT,
            IMAGING_NODE_PG_PORT_IN,
            IMAGING_NODE_PG_PORT_OUT,
            IMAGING_NODE_NONE
    };
    /**
     * \struct BaseGraphNode
     * Base structure that is used for the three types of nodes that
     * the camera graph has at different levels
     * Top level meta-graph made out of subgraphs
     * Medium level graph made out of sources, PG's, sink etc..
     * Inner graph that represent the imaging elements inside the Program Group
     * nodes the inner graph is made out of kernels, mux/demux and ports of the
     * PG's
     * This structure has the basics to traverse the graph in any direction
     * using standard graph traversal algorithms.
     */

    struct BaseGraphNode {
        std::string name;
        IGraphConfig* data;
        bool visited;
        std::vector<BaseGraphNode*> parents;
        std::vector<BaseGraphNode*> children;
        BaseGraphNode(): data(nullptr), visited(false) {}
        void addParent(BaseGraphNode *p) { parents.push_back(p); }
        void addChild(BaseGraphNode *c) { children.push_back(c); }
    };

    struct GraphNode : public BaseGraphNode {
        ia_uid type;    /**<GCSS_KEY_HW, GCSS_KEY_PROGRAM_GROUP, GCSS_KEY_SINK */
        int32_t streamId;
        int32_t exeCtxId;
        GraphNode(): BaseGraphNode(),
                     type(GCSS_KEY_PROGRAM_GROUP),
                     streamId(-1),
                     exeCtxId(-1){}
    };
    typedef std::shared_ptr<GraphNode> GraphNodePtr;

    /**
     * \struct ImagingNode
     * Node in the pipe of imaging elements (kernels)
     * This struct is used to create a graph of nodes and perform operations
     * in topological order, like the resolution history calculation.
     * The information of the links is derived from kernel links(klink)
     */
    struct ImagingNode : public BaseGraphNode {
        ImagingNodeType type;
        int32_t rcb;
        ia_isp_bxt_resolution_info_t resolutionInfo;
        ia_isp_bxt_resolution_info_t resolutionHistory;
        ia_isp_bxt_run_kernels_t kernelInfo;
        ImagingNode();
    };
    typedef std::shared_ptr<ImagingNode> ImagingNodePtr;

    /**
     * \struct SubGraphInfo
     * Container for the information of a single subgraph.
     * The type of subgraph can be stream-id or exec-ctx.
     * It can be also considered a node of a meta-graph made out of subgraphs.
     */
    struct SubGraphInfo : public BaseGraphNode {
        ia_uid subgraphType;  /**< gcss key for exec-ctx or stream-id */
        int32_t id;           /**< id fo the subgraph */
        /**< if the subgraph type is stream id this value is the same as id,
         * if subgraph type is execution context then this value is the stream
         * id of all the nodes inside the subgraph, there cannot be more than 1
         **/
        int32_t streamId;
        uint32_t ispTuningMode;
        std::vector<GraphNode*> nodes;
        std::vector<IGraphConfig*> pgs;
        std::vector<IGraphConfig*> inputPorts;
        std::vector<IGraphConfig*> outputPorts;
        size_t kernelCount;
        ia_isp_bxt_run_kernels_t *kernelMemory;
        std::map<std::string, ImagingNodePtr> imagingGraph;
        SubGraphInfo() : BaseGraphNode(),
                         subgraphType(GCSS_KEY_STREAM_ID),
                         id(0), streamId(-1),
                         ispTuningMode(0),kernelCount(0),
                         kernelMemory(nullptr) {}
    };
    typedef std::shared_ptr<SubGraphInfo> SubGraphInfoPtr;

private: //methods
    css_err_t analyzeGraphSettings();
    css_err_t allocateAicData();
    void deleteAicStructs();
    css_err_t populateAicData();
    css_err_t analyzeSubGraphs(std::map<int32_t, SubGraphInfoPtr> &infoMap);
    css_err_t addGraphNode(IGraphConfig &node);
    css_err_t addGraphConnection(IGraphConfig &node);
    css_err_t addImagingNode(SubGraphInfo &sgInfo, IGraphConfig &kernel);
    css_err_t addImagingLink(SubGraphInfo &ctxInfo, IGraphConfig &klink,
                             IGraphConfig &pg);
    css_err_t addRoutingNode(SubGraphInfo &sgInfo, IGraphConfig &routing,
                             ImagingNodeType type);
    css_err_t collectPgInnerGraph(SubGraphInfo &sgi, IGraphConfig &pg);
    css_err_t collectInterPgConnections(SubGraphInfo &sgi);
    css_err_t collectSubgraphConnections();
    css_err_t traverseGraph(BaseGraphNode *item,
                            std::function<css_err_t(BaseGraphNode*)> &f);
    css_err_t getDownstreamSubgraphs(IGraphConfig *src,
                                    std::vector<int32_t> &subgraphIds);
    css_err_t calculateSourceResHistory(SubGraphInfo &sgi,
                                       ia_isp_bxt_resolution_info_t &resHistory);
    css_err_t fillAicRunKernels(SubGraphInfo &sgi);
    css_err_t getUpstreamResHistory(ImagingNode &portNode);
    css_err_t getCrossSgInPorts(GraphNode &node,
                                std::vector<IGraphConfig *> &ports);
    void getAvailableSubgraphs(std::set<int32_t> &ids);
    void resetGraph();
    void resetInnerGraph(SubGraphInfo &sgi);
    void resetMetaGraph();
    css_err_t subgraphConnectionVisitor(BaseGraphNode *n);
    css_err_t resHistoryCalcVisitor(BaseGraphNode *n);
    css_err_t resHistoryVisitor(BaseGraphNode *n);
    // Debug utils
    void dumpSubGraphInfos();
    void dumpInnerGraph(int32_t id);
    void dumpOuterGraph();
    void dumpAicStructs();
    static css_err_t dumpInnerNodeVisitor(BaseGraphNode *item, ImagingNodeType type);
    static css_err_t printOuterNode(BaseGraphNode *item);
private: // members
    const IGraphConfig *mGraphSettings;
    ia_uid mSubgraphType;   /**< GCSS_KEY_STREAM_ID, GCSS_KEY_EXEC_CTX_ID */

    /**
     * map with the Info for each subgraph, the key is the subgraph id.
     * The concrete subrgraph type is passed in the constructor
     * we can use stream-id or execution-context-id
     * The inner graphs are stored in the SubgraphInfo structure
     */
    std::map<int32_t, SubGraphInfoPtr> mSubgraphInfoMap;

    /**
     * outer graph as represented by the lighter GraphNode structures.
     * The key is the name of the node.
     */
    std::map<std::string, GraphNodePtr> mGraphNodes;
    std::vector<IGraphConfig*> mConnections;
    /**
     * map used to store the memory for the AIC structs associated with a given
     * subgraph id. The key of the map is the subgraph-id
     * This map is used only for memory management (alloc/free).
     * The arrays stored here are used via the SubgraphInfo::kernelMemory field
     */
    std::map<int32_t, KernelInfoMemPool> mKernelMemoryMap;
};

} //namespace GCSS


#endif /* IA_CAMERA_GCSS_GRAPH_UTILS_GRAPH_UTILS_H_ */
