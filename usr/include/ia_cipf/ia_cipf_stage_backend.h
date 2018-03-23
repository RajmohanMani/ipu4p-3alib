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

#ifndef _IA_CIPF_STAGE_BACKEND_H_
#define _IA_CIPF_STAGE_BACKEND_H_

#include <ia_cipf/ia_cipf_types.h>
#include <ia_cipf/ia_cipf_stage.h>

/** \defgroup ia_cipf_stage_backend Stage backend
 *
 * \ingroup ia_cipf_backend
 * \brief CIPF interface for stage realizations
 */

/**
 * \ingroup ia_cipf_stage_backend
 */
typedef css_err_t (*stage_op)(ia_cipf_stage_t*);
typedef css_err_t (*stage_set_property_op)(struct _cipf_stage*,
                                          ia_uid uid,
                                          const ia_cipf_property_t *);
typedef css_err_t (*stage_get_property_op)(struct _cipf_stage*,
                                          ia_uid uid,
                                          ia_cipf_property_t *);

/** Set stage operations
 *
 * With this function, the stage realization can set handlers for its
 * main operations execute(), wait() and destroy() plus for any custom
 * property operations.
 *
 * Note: for basic property handling, the stage can utilize common
 *       implementations in CIPF. This includes creation, adding, querying and
 *       assigning of stage- and buffer-associated properties. Property
 *       operations available via this function are meant for custom handling
 *       of property objects, e.g when property payload size need to change
 *       dynamically and interpretation needs custom implementation.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      load_op         function pointer for load() operation
 * \param[in]      execute_op      function pointer for execute() operation
 * \param[in]      wait_op         function pointer for wait() operation
 * \param[in]      destroy_op      function pointer for destroy() operation
 * \param[in]      get_property_op function pointer for get_property() operation
 * \param[in]      set_property_op function pointer for set_property() operation
 *
 * \return         css_err_none if successful
 */
css_err_t
ia_cipf_stage_set_operations(ia_cipf_stage_t *stage,
                             stage_op load_op,
                             stage_op execute_op,
                             stage_op wait_op,
                             stage_op destroy_op,
                             stage_get_property_op get_property_op,
                             stage_set_property_op set_property_op);

/** Add a private data section to stage
 *
 * Adds a private data section to the stage that can be used to store stage
 * specific information (e.g. a stage implementation defined struct) and be
 * later queried and used/modified when necessary. Memory allocation is handled
 * by the function call, and ownership of the memory is retained by the stage.
 *
 * \see ia_cipf_stage_get_private
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      size            size of the private section in bytes
 *
 * \return         pointer to the private memory, NULL if failed
 */
void*
ia_cipf_stage_add_private(ia_cipf_stage_t *stage, uint32_t size);

/** Get a pointer to the private section in a stage
 *
 * Gets a pointer to the private section in a stage. Private must be first added
 * successfully before it can be queried. Ownership of the memory is retained by
 * the stage, the caller must not free it.
 *
 * \see ia_cipf_stage_add_private
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 *
 * \return         pointer to the private memory, NULL if failed
 */
void*
ia_cipf_stage_get_private(ia_cipf_stage_t *stage);

/** Add a terminal to the stage
 *
 * Add a terminal of a given type to the stage. Stage implementation should not
 * use this function directly, but rather use terminal_base.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      type            type of the container
 *
 * \return         pointer to ia_cipf_terminal_t, NULL if failed
 */
ia_cipf_terminal_t*
ia_cipf_stage_add_terminal(ia_cipf_stage_t *stage,
                           ia_cipf_terminal_type_t type);

/** Remove a terminal from the stage
 *
 * Removes the given terminal from the stage.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      terminal        ia_cipf_terminal_t handle
 *
 * \return         css_err_none if successful
 */
css_err_t
ia_cipf_stage_remove_terminal(ia_cipf_stage_t *stage,
                              ia_cipf_terminal_t *terminal);

/** Base implementation for assigning a property to a stage
 *
 * Assign a property to a stage. This is the base implementation for property
 * assign, and can be used by stage implementations for general property assign,
 * i.e. setting properties that do not need special handling.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      uid             uid of the stage property to be assigned to
 * \param[in]      property        handle of the property being assigned
 *
 * \return         css_err_none if successful
 */
css_err_t
stage_base_assign_property(ia_cipf_stage_t *stage,
                           ia_uid uid,
                           const ia_cipf_property_t *property);

/** Base implementation for stage get property
 *
 * Get a copy of a property from a stage. The caller must provide a property
 * object that contains the uid of the requested property either by manually
 * setting it or by reusing an existing property object. This is the base
 * implementation for property get, and can be used by stage implementation for
 * general property getting.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in,out]  property        property object containing the property uid
 *
 * \return         css_err_none if successful
 */
css_err_t
stage_base_get_property(ia_cipf_stage_t *stage,
                        ia_cipf_property_t *property);

/** Base implementation for stage get property reference
 *
 * Get a reference to a property in a stage. The ownership of the property is
 * not transferred, and the caller must not free the property. This is the base
 * implementation for get property reference, and can be used by stage
 * implementation for convenient access to internal properties.
 *
 * \ingroup ia_cipf_stage_backend
 *
 * \param[in]      stage           ia_cipf_stage_t handle
 * \param[in]      uid             uid of the property to get
 *
 * \return         pointer to the requested property, NULL if failed
 */
ia_cipf_property_t *
stage_base_get_property_ref(ia_cipf_stage_t *stage,
                            ia_uid uid);

#endif /* _IA_CIPF_STAGE_BACKEND_H_ */
