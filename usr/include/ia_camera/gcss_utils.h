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
#ifndef GCSS_UTILS_H_
#define GCSS_UTILS_H_

#include "gcss.h"
#include <set>
#include <utility>
#include <string>
#include <limits>

namespace GCSS {

/**
 * \class GraphCameraUtil
 * Class that holds utility functions to derive information from
 * GraphConfig container for Camera runtime.
 *
 * Utilities are separated from GraphConfig interface in order to
 * specialize the XML-schema that Camera runtime is dependent of
 * from the generic concept of graph information.
 *
 * These specializations include execCtxs, ports, execCtx edges
 * as well as sensor and imaging kernel details that are nested
 * in generic graph elements hierarchy.
 */
class GraphCameraUtil
{
public: // types
   /**
    * \struct PortDescriptor
    * Information of a port from an XML graph node
    */
    struct PortDescriptor {
        std::string    name;
        std::string    pgName;
        int32_t        direction;
        int32_t        enabled;
        uint32_t       terminalId; /**< Unique terminal id (is a fourcc code)
                                         this is relevant only when the node
                                         is a PG and then the port is a terminal */
        uint32_t        width;    /**< Width of the frame in pixels */
        uint32_t        height;   /**< Height of the frame in lines */
        std::string     format;   /**< Frame format name, use gcss_format
                                       utilities to query more information */
    };

public:
    virtual ~GraphCameraUtil() {}

    static const int32_t PORT_DIRECTION_INPUT = 0;
    static const int32_t PORT_DIRECTION_OUTPUT = 1;
    //pair of source and sink between either 2 pg, or 2 execution context.
    typedef std::pair<std::string, std::string> StreamConnection;

    /*
     * Generic Dimensions prototype:
     *
     * Port-elements, kernels as well as sensor entities input and output
     * elements reuse the common dimensions prototype including
     *  GCSS_KEY_WIDTH, GCSS_KEY_HEIGHT, GCSS_KEY_BYTES_PER_LINE,
     *  GCSS_KEY_LEFT, GCSS_KEY_TOP, GCSS_KEY_RIGHT, GCSS_KEY_BOTTOM
     */

    /**
     * Get width, height, bpl and cropping values from the given element
     *
     * \ingroup gcss
     *
     * \param[in] node the node to read the values from
     * \param[out] w width
     * \param[out] h height
     * \param[out] bpl bytes per line
     * \param[out] l left crop
     * \param[out] t top crop
     * \param[out] r right crop
     * \param[out] b bottom crop
     */
    static css_err_t getDimensions(const IGraphConfig *node,
                                  int32_t *w = NULL,
                                  int32_t *h = NULL,
                                  int32_t *bpl = NULL,
                                  int32_t *l = NULL,
                                  int32_t *t = NULL,
                                  int32_t *r = NULL,
                                  int32_t *b = NULL);

    /*
     * NODE-specialization
     */
    static IGraphConfig* nodeGetPortById(const IGraphConfig *node, uint32_t id);

    /*
     * PORT-specialization
     */

    /**
     * Check if port is at the edge
     *
     * \ingroup gcss
     *
     * A port is at the edge of the video execCtx (pipeline) if its peer is in a PG
     * that has a different execCtxID (a.k.a. pipeline id) or if its peer is a
     * virtual sink.
     *
     * Here we check for both conditions and return true if this port is at either
     * edge of a pipeline
     * \param[in] port Reference to port Graph node
     * \return true if it is edge port
     */
    static bool isEdgePort(const IGraphConfig* port);

    /**
     * Check if port is virtual
     *
     * \ingroup gcss
     *
     * Check if the port is a virtual port. this is the end point
     * of the graph. Virtual ports are the nodes of type sink.
     *
     * \param[in] port Reference to port Graph node
     * \return true if it is a virtual port
     * \return false if it is not a virtual port
     */
    static bool portIsVirtual(const IGraphConfig* port);
    /**
     * return child node full name, this is pg-name:child-name
     *
     * This makes the child name unique in the graph, because multiple
     * nodes may have children named same way (ex: input)
     *
     * \ingroup gcss
     *
     * \param[in] port Reference to port Graph node
     * \return string with the full name
     */
    static std::string getFullName(const IGraphConfig &child);

    /**
     * Return the port descriptor
     *
     * \ingroup gcss
     *
     * \param[in] port
     * \param[out] descriptor
     * \return 0 if it is an input port
     * \return 1 if it is an output port
     */
    static css_err_t portGetDescriptor(const IGraphConfig* port,
                                       PortDescriptor &desc);
    /**
     * Return the port direction
     *
     * \ingroup gcss
     *
     * \param[in] port
     * \return 0 if it is an input port
     * \return 1 if it is an output port
     */
    static int portGetDirection(const IGraphConfig* port);

    /**
     * For a given port node it constructs the fourCC code used in the connection
     * object. This is constructed from the program group id.
     *
     * \ingroup gcss
     *
     * \param[in] portNode
     * \param[out] stageId Fourcc code that describes the PG where this node is
     *                     contained
     * \param[out] terminalID Fourcc code that describes the port, in FW jargon,
     *                        this is a PG terminal.
     * \return css_err_none in case of no error
     * \return css_err_argument in case some error is found
     */
    static css_err_t portGetFourCCInfo(const IGraphConfig *portNode,
                                      ia_uid& stageId,
                                      uint32_t& terminalId);

    /**
     * Retrieve the graph config node of the port that is connected to a given port.
     *
     * \ingroup gcss
     *
     * \param[in] port Node with the info of the port that we want to find its peer.
     * \param[out] peer Pointer to a node where the peer node reference will be
     *                  stored
     * \return css_err_none
     * \return css_err_argument if any of the graph settings is incorrect.
     */
    static css_err_t portGetPeer(const IGraphConfig* port, IGraphConfig** peer);

    /**
     * Finds the stream id of the program group that the port is in.
     *
     * \ingroup gcss
     *
     * \param[in] port The port whose stream id is being returned
     * \return valid stream id, or -1 in case of error.
     */
    static int portGetStreamId(const IGraphConfig *port);
    /**
     * Finds the execCtx id of the program group that the port is in.
     *
     * \ingroup gcss
     *
     * \param[in] port The port whose execCtx is being returned
     * \return valid execCtx id, or -1 in case of error.
     */
    static int portGetExecCtxId(const IGraphConfig *port);
    static int getExecCtxIds(const IGraphConfig &setting,
                             std::set<int32_t> &execCtxIds);
    static int portGetKey(const IGraphConfig *port, ia_uid uid);

    /**
    * Retrieves the format information of a port. Uses the peer port (i.e. the
    * port connected to this one) to get the information if not found from the
    * given port.
    *
    * Returns an error if some of the information is missing unless it is a
    * private port.
    *
    * \ingroup gcss
    *
    * \param[in] port        Port to query the format.
    * \param[out] enabled    Passthrough, enabled or disabled status
    * \param[out] terminalId Unique terminal id
    * \param[out] width      Width of the frame in pixels
    * \param[out] height     Height of the frame in lines
    * \param[out] fourcc     Frame format
    * \param[out] bpl        Bytes per line
    * \param[out] bpp        Bits per pixel
    */
    static css_err_t portGetFormat(const GCSS::IGraphConfig *port,
                                   uint32_t &enabled,
                                   uint32_t &terminalId,
                                   uint32_t &width,
                                   uint32_t &height,
                                   uint32_t &fourcc,
                                   uint32_t &bpl,
                                   uint32_t &bpp);

    /**
     * SENSOR-specialization
     */

    /**
     * Get binning factor values from the given node
     *
     * \ingroup gcss
     *
     * \param[in] node the node to read the values from
     * \param[out] hBin horizontal binning factor
     * \param[out] vBin vertical binning factor
     */
    static css_err_t sensorGetBinningFactor(const IGraphConfig *node,
                                           int &hBin, int &vBin);

    /**
     * Get scaling factor values from the given node
     *
     * \ingroup gcss
     *
     * \param[in] node the node to read the values from
     * \param[out] scalingNum scaling ratio
     * \param[out] scalingDenom scaling ratio
     */
    static css_err_t sensorGetScalingFactor(const IGraphConfig *node,
                                           int &scalingNum,
                                           int &scalingDenom);

    /**
     * Analyse all connections between execution context.
     * Generates 3 lists:
     * - list of pair of names of inter-connections between execution contexts
     * - list of input ports names associated with input streams
     * - list of output ports names associated with output streams
     *
     * \ingroup gcss
     *
     * \param[in] graphHandle pointer to any node in the graph
     * \param[out] connections set connections with edges pair
     * \param[out] pixel_sources pixel data sources
     * \param[out] pixel_sinks pixel data sinks
     */
    static css_err_t getExecCtxConnectionPorts(const IGraphConfig *graphHandle,
                                               std::vector<StreamConnection> &connections,
                                               std::vector<std::string> &pixel_sources,
                                               std::vector<std::string> &pixel_sinks);
    /**
     * Finds input ports for the given execCtx or stream id
     *
     * \ingroup gcss
     *
     * \param[in] uid key identifying whether the next value is a stream id or
     *                a exec ctx id.
     * \param[in] execCtxId id of the execCtx OR stream id
     * \param[in] graphHandle pointer to any node in the graph
     * \param[out] ports reference to a vector of IGraphConfig where to store the
     *                   found ports
     */
    static css_err_t getInputPorts(ia_uid uid,
                                   int32_t execCtxId,
                                   const IGraphConfig &graphHandle,
                                   std::vector<IGraphConfig *> &ports);
    /**
     * Finds output ports for the given execCtx or stream id
     *
     * \ingroup gcss
     *
     * \param[in] uid key identifying whether the next value is a stream id or
     *                a exec ctx id.
     * \param[in] execCtxId id of the execCtx OR stream id
     * \param[in] graphHandle pointer to any node in the graph
     * \param[out] ports reference to a vector of IGraphConfig where to store the
     *                   found ports
     */
    static css_err_t getOutputPorts(ia_uid uid,
                                    int32_t execCtxId,
                                    const IGraphConfig &graphHandle,
                                    std::vector<IGraphConfig *> &ports);
    /**
     * Finds input port for the given execCtx or stream id
     *
     * \ingroup gcss
     *
     * \param[in] uid key identifying whether the next value is a stream id or
     *                a exec ctx id.
     * \param[in] execCtxId id of the execCtx OR stream id
     * \param[in] graphHandle pointer to any node in the graph
     * \param[out] port input port
     */
    static css_err_t getInputPort(ia_uid uid,
                                  int32_t execCtxId,
                                  const IGraphConfig *graphHandle,
                                  IGraphConfig **port);

    /**
     * getSubgraphPorts
     *
     * For a given subgraph, specified via stream id or exec-ctx id, retrieve the
     * ports that cross subgraph boundaries.
     *
     * \ingroup gcss
     * \param[in] uid Key to specify whether we are looking for stream id or exec ctx
     *                ids input port. Possible values are GCSS_KEY_STREAM_ID or
     *                GCSS_KEY_EXEC_CTX_ID
     * \param[in] execCtxId Value of the stream/exec-ctx id
     * \param[in] direction Either PORT_DIRECTION_INPUT or PORT_DIRECTION_OUTPUT
     * \param[in] graphHandle Reference to the root node of the tree
     * \param[out] ports vector of pointers where to store the found port nodes.
     *
     * \return  css_err_argument in case of any of the input parameters being invalid
     *                           or in case it did not find any port.
     */
    static css_err_t getSubgraphPorts(ia_uid uid,
                                      int32_t execCtxId,
                                      int32_t direction,
                                      const IGraphConfig &graphHandle,
                                      std::vector<IGraphConfig *> &ports);
    /**
     * DEPRECATED see above
     */
    static css_err_t streamGetInputPort(int32_t execCtxId,
                                       const IGraphConfig *graphHandle,
                                       IGraphConfig **port);

    /**
     *
     * Retrieve a list of program groups that belong to a given execCtx id or
     * stream id.
     * Iterates through the graph configuration storing the program groups
     * that match this execCtx id into the provided vector.
     *
     * \param[in] uid Used to determine if we search the PG per stream-id or exec
     *                ctx-id
     * \param[in] value Depending on the key parameter this is the value of the
     *                  stream-id or execCtx-id to match.
     * \param[in] GCHandle Handle to get graph result.
     * \param[out] programGroups Vector with the nodes that match the criteria.
     */
    static css_err_t getProgramGroups(ia_uid uid,
                                     int32_t value,
                                     const GCSS::IGraphConfig *GCHandle,
                                     std::vector<IGraphConfig*> &pgs);

    /**
     * Helper function to get values from the kernel settings
     * \todo Moved to bxt aic utils, will be removed from here after hal has
     *       adapted to changes.
     * \ingroup gcss
     *
     * \param[in] kernelNode
     * \param[out] palUuid
     * \param[out] kernelId
     * \param[out] metadata
     * \param[out] enable
     * \param[out] rcb
     * \param[out] branchPoint
     */
    static css_err_t kernelGetValues(const IGraphConfig *kernelNode,
                                    int32_t *palUuid = NULL,
                                    int32_t *kernelId = NULL,
                                    uint32_t *metadata = NULL,
                                    int32_t *enable = NULL,
                                    int32_t *rcb = NULL,
                                    int32_t *branchPoint = NULL,
                                    int32_t *sinkPort = NULL);

    /**
     * Return pointer to active source
     *
     * Graph descriptor may define multiple sources. This function returns
     * pointer to source node that is set active.
     *
     * \ingroup gcss
     *
     * \param[in]  settings,   pointer to gc graph
     * \param[out] sourceNode, vector of pointers to active sources
     */
    static css_err_t getSourceNode(const IGraphConfig *gcHandle,
            std::vector<IGraphConfig*> &sourceNodes);

    /**
     * Debug utils
     */

    /**
     * Pretty print any recognized element: node, port, kernel
     *
     * \ingroup gcss
     *
     * \param[in] node of which name to print
     */
    static std::string print(const IGraphConfig *node);

    /**
     * Dumps the whole tree of nodes and attributes.
     *
     * \ingroup gcss
     *
     * \param node Node to dump
     * \param depth Depth level of the dump. Default(whole tree) is 0
     */
    static void dumpNodeTree(const IGraphConfig* node, int depth = 0);

    /**
     * Convert string containing a number to a binary blob.
     *
     * \ingroup gcss
     *
     * \param[in] str String containing a number in decimal or hex (prefix "0x").
     * \param[out] bytes Size of the new binary data in bytes.
     *
     * \return void* Pointer to the newly allocated binary data.
     *               The format is little-endian, least significant bytes first.
     *               Caller must free with IA_CIPR_FREE()
     */
    static void *numString2binary(const std::string &str, unsigned int *bytes = NULL);

};

/**
 * \brief Rounds the given number up to the next power of 2
 *
 * Rounds given number up to the next power two. Up to number
 * of bits in 'unsigned int' type.
 *
 * \returns Value of 'a' rounded up to the next power of two.
 *          Zero in case of an overflow.
*/
inline unsigned ceil_pow2(unsigned a)
{
    // Maximum number of possible bit shifts, to avoid error situations
    const int maxNumShifts = std::numeric_limits<unsigned>::digits - 1;

    unsigned result = 1;
    int shifts = 0;
    while (result <= a && shifts <= maxNumShifts) {
        result <<= 1;
        ++shifts;
    }

    if (shifts > maxNumShifts) {
        // Overflow, return zero.
        result = 0;
    }

    return result;
}

} // namespace GCSS

#endif /* GCSS_UTILS_H_ */
