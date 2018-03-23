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

#ifndef GRAPH_QUERY_MANAGER_H
#define GRAPH_QUERY_MANAGER_H

#include "gcss.h"
#include "gcss_item.h"
#include "gcss_utils.h"

namespace GCSS {

class GraphQueryManager
{
public:
    ~GraphQueryManager(){};

    typedef std::vector<GraphConfigNode*> GraphQueryResult; // DEPRECATED
    typedef std::map<ItemUID, std::string> GraphQuery;
    typedef std::vector<IGraphConfig*> QueryResult;

    /**
     * Create graph
     *
     * \ingroup gcss
     *
     * Takes pointer to one of the settings found with queryGraphs and
     * returns full graph combined with graph descriptor.
     *
     * \param[in] settings
     * \param[out] result
     */
    css_err_t createGraph(IGraphConfig* settingsGraph, IGraphConfig** result);

    /**
     * Destroy graph
     *
     * \ingroup gcss
     *
     * Needs to be called for each graph created with createGraph
     *
     * \param[in] graph
     *
     */
    static void destroyGraph(IGraphConfig* graph);

    /**
     * DEPRECATED
     *
     * Query graphs
     *
     * \ingroup gcss
     *
     * Query graph settings file for settings that matches search terms in
     * GraphQuery;
     *
     * \param[in] GraphQuery
     * \param[out] GraphQueryResult
     * \param[optional | in] strict if true, all search terms has to match
     */
    css_err_t queryGraphs(const GraphQuery&,
                          GraphQueryResult&,
                          bool strict = true);
    css_err_t queryGraphs(const GraphQuery&,
                          const GraphQueryResult&,
                          GraphQueryResult&,
                          bool strict = true);

    /**
    * Query graphs
    *
    * \ingroup gcss
    *
    * Query graph settings file for settings that matches search terms in
    * GraphQuery;
    *
    * \param[in] GraphQuery
    * \param[out] GraphQueryResult
    * \param[optional | in] strict if true, all search terms has to match
    */
    css_err_t queryGraphs(const GraphQuery&,
                          QueryResult&,
                          bool strict = true);
    css_err_t queryGraphs(const GraphQuery&,
                          const QueryResult&,
                          QueryResult&,
                          bool strict = true);

    /**
     * Set graph settings
     *
     * \ingroup gcss
     *
     * Set parsed graph settings to graph query manager for later use.
     *
     * \param[in] settings
     */
    void setGraphSettings(const IGraphConfig* settings);

    /**
     * Set graph descriptor
     *
     * \ingroup gcss
     *
     * Set parsed graph descriptor to graph query manager for later use.
     *
     * \param[in] descriptor
     */
    void setGraphDescriptor(const IGraphConfig* descriptor);

    /* DEPRECATED */
    void setGraphSettings(const GraphConfigNode* settings) {mGraphSettings = settings;}
    /* DEPRECATED */
    void setGraphDescriptor(const GraphConfigNode* descriptor) {mGraphDescriptor = descriptor;}
    /* DEPRECATED */
    css_err_t getGraph(GraphConfigNode*, GraphConfigNode*);
private:
    // true = every search item has to match, false = at least one match
    bool strictQuery = true;
    // Store parsed data into these containers, instead of using a single node
    const GraphConfigNode *mGraphSettings   = nullptr;
    const GraphConfigNode *mGraphDescriptor = nullptr;

    css_err_t goThroughSettings(const GraphQuery&,
                               const GraphQueryResult&,
                               GraphQueryResult&);
    css_err_t goThroughSearchItems(const GraphQuery&, GraphConfigNode*, uint16_t&);

    static css_err_t addSensorModeData(GraphConfigNode *sensorNode,
                                      GraphConfigNode *sensorModesNode,
                                      const std::string &sensorModeID);
    css_err_t getConnectionData(const std::string& source_connection,
                               const std::string& sink_connection,
                               GraphConfigNode *settings,
                               GraphConfigNode *ret_node);
    css_err_t getStaticConnectionData(const std::string& source_connection,
                                      const std::string& sink_connection,
                                      GraphConfigNode *ret_node);
    IGraphConfig *copyNodeToResult(GraphConfigNode* descriptorNodes,
                                   ia_uid nodeId,
                                   GraphConfigNode* resultNode);
    css_err_t propagateIntAttribute(IGraphConfig *srcNode,
                                    IGraphConfig *dstNode,
                                    ia_uid attributeId);
    css_err_t propagateStrAttribute(IGraphConfig *srcNode,
                                    IGraphConfig *dstNode,
                                    ia_uid attributeId);
    css_err_t processGraphOverrides(GraphConfigNode &graphNode,
                                    GraphConfigNode &results);
    css_err_t validateSettingsAgainstDescriptor();
};
} // namespace
#endif
