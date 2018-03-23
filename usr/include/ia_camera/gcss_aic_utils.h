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
#ifndef GCSS_AIC_UTILS_H_
#define GCSS_AIC_UTILS_H_

extern "C" {
#include "ia_isp_bxt_types.h"
}
#include "gcss.h"
#include "gcss_item.h"
#include "graph_utils.h"
namespace GCSS {

typedef std::map<GCSS::IGraphConfig*, ia_isp_bxt_resolution_info_t> portResHistoryMap;
typedef std::vector<GCSS::IGraphConfig*> NodesVector;
typedef std::vector<int32_t> ExecCtxsVector;
/*
 * Maps the execution context id to index of the vector mKernels  where the
 * pre-allocated arrays of ia_isp_bxt_run_kernels_t are stored. <exec_ctx_id, idx>
 */
typedef std::map<int32_t, uint32_t> ExecCtxIdsMap;

/**
* \class BxtAicUtils
* GCSS AIC dependent utility functions
* */
class BxtAicUtils {
public:
    /**
     * \param legacy true if stream id is used instead of execution context
     */
    BxtAicUtils(bool legacy = true);
    ~BxtAicUtils();
    /**
     * Init aic utils
     *
     * Reserves memory, and creates kernel lists for each stream
     *
     * \ingroup gcss
     *
     * \param[in] GCHandle a handle to createGraph result
     * \return css_err_none when successful
     */
    css_err_t initAicUtils(const IGraphConfig *GCHandle);

    /**
     * get the list of stream Ids available in the graph settings initialized
     * in this object.
     *
     * \param[out] streamIds vector with the stream id's
     *
     * \return css_err_none
     */

    css_err_t getStreamIds(std::vector<int32_t> &streamIds) const;
    /**
     * get the list of executions contexts available in the graph settings
     * initialized in this object.
     *
     * \param[out] execCtxts vector with the executions contexts id's
     *
     * \return css_err_none
     */
    css_err_t getExecCtxIds(std::vector<int32_t> &execCtxts) const;
    /**
     * Get program group by execution context Id
     *
     * \ingroup gcss
     *
     * Returns pointer to program group struct, which is allocated as a
     * member of this class.
     *
     * \param[in] execCtxId a stream id of the program group being requested
     * \param[out] pg pointer to a program group struct being populated
     */
    void getProgramGroup(int32_t streamId, ia_isp_bxt_program_group &pg);


    /**
     * Get cmc mode id associated with the sensor
     * \ingroup gcss
     *
     * Returns cmc mode id. If not found, returns -1.
     */
    int32_t getSensorCmcId();

    /**
     * Get the IGraphConfig root node that was used to initialize this utility
     * class. This allows users to perform other queries to the IGraphConfig
     * interface.
     * \ingroup gcss
     *
     */
    const IGraphConfig* getGraphConfig() { return mGCHandle; }

    /**
     * Dumps the list of kernels for given stream
     *
     * \ingroup gcss
     *
     * \param[in] streamId
     */
    void dumpKernels(int32_t streamId);
    /**
     * Dumps the information from a list of kernels descriptors
     *
     * \ingroup gcss
     *
     * \param[in] streamId
     */
    static void dumpKernels(ia_isp_bxt_run_kernels_t *kernelList,
                            uint32_t kernel_count);
private:
    /* pair of execution context id and port */
    typedef std::pair<int32_t, IGraphConfig*> StreamPort;

    /* Helper classes to store sensor and kernel information */
    class Dimensions {
    public:
        Dimensions() : w(0), h(0) {};
        int32_t w; /**< width */
        int32_t h; /**< height */
    };
    class Crop {
    public:
        Crop() : l(0), r(0), t(0), b(0) {};
        int32_t l; /**< left */
        int32_t r; /**< right */
        int32_t t; /**< top */
        int32_t b; /**< bottom */
    };
    class Scaler {
    public:
        Scaler() : num(1), denom(1) {}; /**< avoid possible division by 0 */
        int32_t num;  /**< numerator */
        int32_t denom; /**< denominator */
        Crop crop;
        Dimensions size;
    };
    struct PixelArray {
        Crop crop;
        Dimensions size;
    };
    struct PixelFormatter {
        Crop crop;
        Dimensions sizeIn;
        Dimensions sizeOut;
    };
    struct ResolutionMemPool {
           std::vector<ia_isp_bxt_resolution_info_t *> resHistorys;
           std::vector<ia_isp_bxt_resolution_info_t *> resInfos;
    };
    // Storage for kernel info extensions to AIC requirements
    css_err_t getPgsIntAttribute(std::vector<int32_t> &pgsAttribute,
                                 ia_uid attributeKey) const;
    int32_t getUpstreamExecCtxId(int32_t exeCtxId,
                                 GCSS::IGraphConfig **upstreamPort);
    css_err_t createKernelListStructures();
    static css_err_t sourceGetResolutionHistory(ia_isp_bxt_resolution_info_t &history,
                                                IGraphConfig &sourceNode);
    static css_err_t  calculateSensorResolutionHistory(IGraphConfig &sensorNode,
                                                       ia_isp_bxt_resolution_info_t &history);
    static css_err_t  calculateTPGResolutionHistory(IGraphConfig &sensorNode,
                                                    ia_isp_bxt_resolution_info_t &history);
    static css_err_t calculateBufSrcResolutionHistory(IGraphConfig &tpgNode,
                                                     ia_isp_bxt_resolution_info_t &history);
    css_err_t populateKernelArray(int32_t streamId,
                                 ia_isp_bxt_run_kernels_t *kernelList,
                                 uint32_t index,
                                 ia_isp_bxt_resolution_info_t inputHistory,
                                 portResHistoryMap &portResHistory);
    css_err_t getStreamChains(std::map<int32_t, std::vector<StreamPort>> &streamChains);
    css_err_t generateKernelListsForExecCtxs();
    static css_err_t kernelGetValues(const GCSS::IGraphConfig *kernelNode,
                                     int32_t *palUuid = NULL,
                                     int32_t *kernelId = NULL,
                                     uint32_t *metadata = NULL,
                                     int32_t *enable = NULL,
                                     int32_t *rcb = NULL,
                                     int32_t *branchPoint = NULL,
                                     int32_t *sinkPort = NULL,
                                     int32_t *restorePoint = NULL);
    static css_err_t kernelGetResolutions(const GCSS::IGraphConfig *kernelNode,
                                          int32_t &inputWidth,
                                          int32_t &inputHeight,
                                          int32_t &outputWidth,
                                          int32_t &outputHeight,
                                          ia_rectangle &inputCrop,
                                          ia_rectangle &outputCrop);
    static css_err_t kernelGetBppInfo(const IGraphConfig &kernelNode,
                                      ia_isp_bxt_run_kernels_t &runKernel);

    css_err_t graphGetSinks(std::vector<IGraphConfig*> &sinks);
    bool nodesHaveKernelLinks();
    static bool kernelHasResolutions(GCSS::IGraphConfig *kernelNode);
    void deleteKernelInfo();
    /* private dump utils */
    static void dumpResInfo(ia_isp_bxt_resolution_info_t &resInfo,
                            const char *name);
    static void dumpPortResHistoryMap (portResHistoryMap &m);

    friend class GraphUtil;
    ExecCtxIdsMap mExecCtxIds;
    std::vector<ia_isp_bxt_run_kernels_t*> mKernels;
    std::vector<ResolutionMemPool> mResMems;
    /*
     * Map to know the number of actual kernels in an entry of mKernels
     * key is stream/exec id value is the number of kernels.
     */
    std::map<int32_t, uint32_t> mKernelCountsMap;

    const IGraphConfig *mGCHandle;
    bool mUseStreamId;
    GraphUtil mGraphUtil;
};
} // namespace
#endif
