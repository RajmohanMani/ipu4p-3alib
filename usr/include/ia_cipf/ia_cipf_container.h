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

#ifndef _IA_CIPF_CONTAINER_H_
#define _IA_CIPF_CONTAINER_H_

#include "ia_cipf_types_internal.h"

/** \defgroup ia_cipf_container Container (ia_cipf_container_t)
 * \ingroup ia_cipf
 * \brief the ia_cipf_container_t object inteface
 */

/**
 * \ingroup ia_cipf_container
 */
ia_cipf_container_t*
ia_cipf_container_create(void *owner);

/**
 * \ingroup ia_cipf_container
 */
void
ia_cipf_container_destroy(ia_cipf_container_t *container);

/**
 * \ingroup ia_cipf_container
 */
void*
ia_cipf_container_add_private(ia_cipf_container_t *container, uint32_t size);

/**
 * \ingroup ia_cipf_container
 */
void*
ia_cipf_container_get_private(ia_cipf_container_t *container);

/** Add property into container
 *
 * \ingroup ia_cipf_container
 *
 * Adds ia_cipf_property_t object reference into container object. Once the
 * function returns, the ownership of property object is passed to container
 * and given property will be destroyed with the container.
 *
 * Added property is exposed and accessible via container interface property
 * functions using enumeration or the given uid.
 *
 * \param[in]   container   handle to container object
 * \param[in]   uid         identifier of property
 * \param[in]   property    property to add
 *
 * \return      css_err_none if successful
 */
css_err_t
ia_cipf_container_add_property(ia_cipf_container_t *container,
                               ia_uid uid,
                               ia_cipf_property_t *property,
                               property_association_type_t patype);

/** Remove property from container
 *
 * \ingroup ia_cipf_container
 *
 * Removes and destroys ia_cipf_property_t object from container object.
 *
 * \param[in]   container   handle to container object
 * \param[in]   property    property to be removed
 *
 * \return      css_err_none if successful
 */
css_err_t
ia_cipf_container_remove_property(ia_cipf_container_t *container,
                                  ia_cipf_property_t *property);

/** Get reference to the container property by index
 *
 * \ingroup ia_cipf_container
 *
 * \param[in]   container   handle to container object
 * \param[in]   index       index of the property
 *
 * \return      requested property reference
 */
ia_cipf_property_t*
ia_cipf_container_get_property_ref_by_index(ia_cipf_container_t *container, uint32_t index);

/** Get reference to the container property by uid
 *
 * \ingroup ia_cipf_container
 *
 * \param[in]   container   handle to container object
 * \param[in]   uid         UID of the property
 *
 * \return      requested property reference
 */
ia_cipf_property_t*
ia_cipf_container_get_property_ref(ia_cipf_container_t *container, ia_uid uid);

/** Get copy of container property
 *
 * Gets a copy of a property found with the association information present
 * in the given property object. Property without the association info is
 * considered an error. Supports only getting container properties. The
 * received property can be used in the set functions.
 *
 * \ingroup ia_cipf_container
 *
 * \param[in]       container   handle to the container
 * \param[in,out]   prop        property object where copy will be stored
 *
 * \return          css_err_none if successful
 */
css_err_t
ia_cipf_container_get_property(ia_cipf_container_t *container,
                               ia_cipf_property_t *prop);

/** Get copy of container property by uid
 *
 * Gets a copy of a container property found by the given uid. The contents and
 * the association information of the property found are copied into a property
 * object given by the user. The received property can be used in the set
 * functions.
 *
 * \ingroup ia_cipf_container
 *
 * \param[in]       container   handle to the container
 * \param[in]       uid         UID of property to get
 * \param[in,out]   prop        property object where copy will be stored
 *
 * \return          css_err_none if successful
 */
css_err_t
ia_cipf_container_get_property_by_uid(ia_cipf_container_t *container,
                                      ia_uid uid,
                                      ia_cipf_property_t *prop);

/** Set container property
 *
 * Sets the property found by the association information present in the
 * property given by the user. Given property is assigned to the property
 * already existing. Ownership of the property is not transferred, the user must
 * destroy it after the function returns.
 *
 * \param[in]   container   handle to the container
 * \param[in]   prop        property to assign
 *
 * \return      css_err_none if successful
 *
 * \ingroup ia_cipf_container
 */
css_err_t
ia_cipf_container_set_property(ia_cipf_container_t *container,
                               const ia_cipf_property_t *prop);

/** Set property of container by uid
 *
 * Sets the pipe property with the given uid. Any association information
 * present in the property given by the user is ignored. Given property is
 * assigned to the property already existing. Ownership of the property is not
 * transferred, the user must destroy it after the function returns.
 *
 * \ingroup ia_cipf_container
 *
 * \param[in]  container   handle to the container
 * \param[in]  uid         UID of property to set
 * \param[in]  prop        property to assign
 *
 * \return     css_err_none if successful
 */
css_err_t
ia_cipf_container_set_property_by_uid(ia_cipf_container_t *container,
                                      ia_uid uid,
                                      const ia_cipf_property_t *prop);

/**
 * \ingroup ia_cipf_container
 */
uint32_t
ia_cipf_container_get_num_properties(ia_cipf_container_t *container);

#endif /* _IA_CIPF_CONTAINER_H_ */
