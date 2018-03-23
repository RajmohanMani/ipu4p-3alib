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
#ifndef IA_CAMERA_GCSS_GCSS_AIC_SIMULATION_UTILS_H_
#define IA_CAMERA_GCSS_GCSS_AIC_SIMULATION_UTILS_H_

extern "C" {
#include "ia_isp_bxt_types.h"
}
#include "gcss.h"

namespace GCSS {

/**
 * Static utilities used only by simulation clients.
 * It allows to perform operations not permitted in normal SW stack but required
 * in simulation environment.
 *
 * Normal client should not need to modify graph setting, only query information
 * from them. The methods in this class allow the modification of the
 * graph settings. It is recommended that you clone the original settings,
 * before modifying
 *
 * Do not use this unless you know the details of constructing graph settings.
 */
class BxtAicSimUtils {
public:

    typedef struct {
        std::string name;
        int pal_uuid;
    } KernelInfo;

    /**
     * Clones an instance of graph settings. This is all the nodes in a tree.
     * This method allocates a new tree and clones the content from the
     * input to the output. the caller is responsible of deleting
     * the cloned settings.
     */
    static css_err_t cloneSettings(const IGraphConfig *in, IGraphConfig **out);

    /**
     * Modifies the provided graph settings, searches for a kernel with a
     * given pal uuid and updates the resolution information.
     * It may return error if the kernel is not found in the settings.
     *
     * \param[in] settings   Pointer to the graph which to update
     * \param[in] palUuid    Pal uuid of the kernel to update
     * \param[in] resInfo    Struct that has the new data
     * \return    css_err_none at success
     */
    static css_err_t updateKernelInfo(IGraphConfig *graphSettings,
                                      int32_t palUuid,
                                      ia_isp_bxt_resolution_info_t &resInfo);

    /**
     * This method does not modify the settings it is purely a query, it will
     * be moved to gcss_utils or gcss_aic_utils
     * For a given graph settings it returns the pal_uuid of a kernel
     * specified by name.
     * It may return error if it does not find the kernel in the settings.
     **/
    static css_err_t getKernelPalUuid(const IGraphConfig *graphSettings,
                                      const std::string &kernelName,
                                      int32_t &palUuid);
    /**
     * This method takes as input the root of a GDF and returns a map
     * with the names and pal_uuids of the kernels inside a given stream-id and
     * graph, also passed as parameters. Kernels in the map are ordered similarly
     * as they appear in the run kernels list.
     *
     * \param[in] graphDescriptor Pointer to a node at the root of the parsed GDF
     * \param[in] graphId Target graph id to be analyzed
     * \param[in] streamId Target stream id to be analyzed
     * \param[out] kernelInfo vector with kernel names and uuid in a struct
     */
    static css_err_t getKernelList(const IGraphConfig *graphDescriptor,
                                   int32_t graphId, int32_t streamId,
                                   std::vector<KernelInfo> &kernelInfo);
    /**
     * From the root node of a GDF, and with the graph id this method
     * retrieves the list of program group nodes included in that graph.
     */
    static css_err_t getPgsInGraph(const IGraphConfig *graphDescriptor,
                                   int32_t graphId,
                                   std::set<IGraphConfig *> &pgs);
    /**
     * From graph settings this method retrieves list of routing elements in a
     * given stream id.
     * For each routing element(mux/demux) the name and the active route
     * is provided.
     * \param[in] settings   Pointer to the graph setting to analyze
     * \param[in] streamId   Stream id to target.
     * \param[out] muxConfig map with the results. key is the mux name, value
     *                       is the active route
     */
    static css_err_t getMuxConfiguration(const IGraphConfig *graphSettings,
                                         int32_t streamId,
                                         std::map<std::string, uint32_t>& muxConfig);

private:
    static css_err_t setValue(GraphConfigNode *output, ia_uid, int value);
    static css_err_t getKernelInfoList(const GCSS::IGraphConfig &pg,
        std::vector<KernelInfo> &kernelInfos);
};
}

#endif /* IA_CAMERA_GCSS_GCSS_AIC_SIMULATION_UTILS_H_ */
