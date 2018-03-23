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

#ifndef _IA_CIPF_STAGE_H_
#define _IA_CIPF_STAGE_H_

#include "ia_cipf_types.h"

/**
 * \defgroup ia_cipf_stage Stage (ia_cipf_stage_t)
 * \ingroup ia_cipf ia_cipf_backend
 * \brief The ia_cipf_stage_t object interface
 */

/**
 * \ingroup ia_cipf_stage
 */
ia_cipf_stage_t *
ia_cipf_stage_create(void);

/**
 * \ingroup ia_cipf_stage
 */
void
ia_cipf_stage_destroy(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_upstream_connections_count(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_downstream_connections_count(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_input_terminal_count(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
ia_uid
ia_cipf_stage_get_uid(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_output_terminal_count(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_terminal_count(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_stage
 */
ia_cipf_terminal_t*
ia_cipf_stage_get_input_terminal(ia_cipf_stage_t *stage, uint32_t index);

/**
 * \ingroup ia_cipf_stage
 */
ia_cipf_terminal_t*
ia_cipf_stage_get_output_terminal(ia_cipf_stage_t *stage, uint32_t index);

/**
 * \ingroup ia_cipf_stage
 */
ia_cipf_terminal_t*
ia_cipf_stage_get_terminal_by_uid(ia_cipf_stage_t *stage, ia_uid uid);

/**
 * \ingroup ia_cipf_stage
 *
 * TODO: should not be part of public iface
 */
ia_cipf_terminal_t*
ia_cipf_stage_enumerate_terminals(ia_cipf_stage_t *stage, uint32_t index);

/** Add property to the stage
 *
 * Adds the given property to the stage object. Once the function returns, the
 * ownership of property object is passed to stage and given property will be
 * destroyed with the stage.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]  stage   handle to the stage
 * \param[in]  uid     UID of property to add
 * \param[in]  prop    property to be added
 *
 * \return     css_err_none if successful
 */
css_err_t
ia_cipf_stage_add_property(ia_cipf_stage_t *stage,
                           ia_uid uid,
                           ia_cipf_property_t *prop);

/** Set property of stage
 *
 * Sets the property found by the association information present in the
 * property given by the user. Also terminal properties inside this stage can be
 * set. Given property is assigned to the property already existing. Ownership
 * of the property is not transferred, the user must destroy it after the
 * function returns.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]   stage   handle to the stage
 * \param[in]   prop    property to assign into associated property in stage
 *
 * \return      css_err_none if successful
 */
css_err_t
ia_cipf_stage_set_property(ia_cipf_stage_t *stage,
                           const ia_cipf_property_t *prop);

/** Set property of stage by uid
 *
 * Sets the stage property with the given uid. Any association information
 * present in the property given by the user is ignored. Given property is
 * assigned to the property already existing. Ownership of the property is not
 * transferred, the user must destroy it after the function returns.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]  stage  handle to the stage
 * \param[in]  uid    UID of property to set
 * \param[in]  prop   property to assign into associated property in pipe
 *
 * \return     css_err_none if successful
 */
css_err_t
ia_cipf_stage_set_property_by_uid(ia_cipf_stage_t *stage,
                                  ia_uid uid,
                                  const ia_cipf_property_t *prop);

/** Get copy of property from stage
 *
 * Gets a copy of a property found with the association information present
 * in the given property object. Property without the association info is
 * considered an error. Supports getting stage and terminal level
 * properties. The received property can be used in the set functions.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]       stage   handle to the stage
 * \param[in,out]   prop    property object where copy will be stored
 *
 * \return          css_err_none if successful
 */
css_err_t
ia_cipf_stage_get_property(ia_cipf_stage_t *stage,
                           ia_cipf_property_t *prop);

/** Get copy of property from stage by uid
 *
 * Gets a copy of a pipe property found by the given uid. The contents and the
 * association information of the property found are copied into a property
 * object given by the user. The received property can be used in the set
 * functions.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]       stage   handle to the stage
 * \param[in]       uid     UID of property to get
 * \param[in,out]   prop    property object where copy will be stored
 *
 * \return          css_err_none if successful
 */
css_err_t
ia_cipf_stage_get_property_by_uid(ia_cipf_stage_t *stage,
                                  ia_uid uid,
                                  ia_cipf_property_t *prop);

/** Get reference to stage property by UID
 *
 * Hands over the reference to property from stage by uid. Only the constant
 * reference to the property is returned.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in] stage   handle to the stage
 * \param[in] uid     UID of property to fetch
 *
 * \return    reference to requested property
 */
const ia_cipf_property_t*
ia_cipf_stage_get_property_ref(ia_cipf_stage_t *stage, ia_uid uid);

/** Enumerate all container properties from stage
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]   stage   handle to the stage
 * \param[in]   index   number of the property in enumeration
 *                      (cumulated in container index order)
 *
 * \return      reference to requested property
 */
const ia_cipf_property_t*
ia_cipf_stage_enumerate_property(ia_cipf_stage_t *stage, uint32_t index);

/**
 * \ingroup ia_cipf_stage
 */
css_err_t
ia_cipf_stage_next_buffer_requirement(ia_cipf_stage_t *stage,
                                      ia_cipf_buffer_t *ipf_buffer);

/**
 * \ingroup ia_cipf_stage
 */
css_err_t
ia_cipf_stage_register_buffer(ia_cipf_stage_t *stage, ia_cipf_buffer_t *buffer);

/**
 * \ingroup ia_cipf_stage
 */
css_err_t
ia_cipf_stage_unregister_buffer(ia_cipf_stage_t *stage, ia_cipf_buffer_t *buffer);

/**
 * \ingroup ia_cipf_stage
 */
css_err_t
ia_cipf_stage_set_iteration_index(ia_cipf_stage_t *stage, uint32_t index);

/**
 * \ingroup ia_cipf_stage
 */
uint32_t
ia_cipf_stage_get_iteration_index(ia_cipf_stage_t *stage);

/** Get association from stage
 *
 * Gets the association information of the given stage to the empty
 * ia_cipf_association_t provided by the user.
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]       stage        ia_cipf_stage handle
 * \param[out]      association  pointer to ia_cipf_association_t
 */
css_err_t
ia_cipf_stage_get_association(const ia_cipf_stage_t *stage,
                              ia_cipf_association_t *association);

/** Add completion operation to stage
 *
 * Completion operations added to stage are executed once the stage execution
 * is completed (@wait).
 *
 * \ingroup ia_cipf_stage
 *
 * \param[in]       stage        ia_cipf_stage handle
 * \param[in]       op           completion operation function handle
 * \param[in]       priv         private handle to pass to the function
 */
css_err_t
ia_cipf_stage_add_completion_operation(ia_cipf_stage_t *stage,
                                       ia_cipf_stage_completion_op_t op,
                                       void *priv);



#endif /* _IA_CIPF_STAGE_H_ */
