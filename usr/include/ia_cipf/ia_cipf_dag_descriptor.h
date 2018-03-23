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

#ifndef _DAG_DESCRIPTOR_H_
#define _DAG_DESCRIPTOR_H_

/** \defgroup ia_cipf_dag_descriptor DAG Descriptor (ia_cipf_dag_descriptor_t)
 * \ingroup ia_cipf
 */

#define GRAPH_URN_MAX_LENGTH 64

#include <ia_cipf/ia_cipf_types.h>
#include <ia_tools/ia_list.h>
#include <ia_tools/css_types.h>

/**
 * \ingroup ia_cipf_dag_descriptor
 */
typedef enum cipf_dag_item_type
{
    cipf_dag_item_type_na,
    cipf_dag_item_type_stage,
    cipf_dag_item_type_connection
} cipf_dag_item_type_t;

/**
 * \ingroup ia_cipf_dag_descriptor
 */
typedef enum cipf_dag_attribute_type
{
    cipf_dag_attribute_type_na,
    cipf_dag_attribute_type_property,
    /* connnection attributes */
    cipf_dag_attribute_type_connection      = (1 << 8),
    cipf_dag_attribute_type_source          = (1 << 9),
    cipf_dag_attribute_type_source_terminal = (1 << 10),
    cipf_dag_attribute_type_sink            = (1 << 11),
    cipf_dag_attribute_type_sink_terminal   = (1 << 12),
    cipf_dag_attribute_type_iteration       = (1 << 13)
} cipf_dag_attribute_type_t;

/**
 * \ingroup ia_cipf_dag_descriptor
 */
typedef struct cipf_dag_descriptor
{
    char        uri[GRAPH_URN_MAX_LENGTH];
    ia_uid      uid;
    ia_list_t   *item;
} ia_cipf_dag_descriptor_t;

/**
 * \ingroup ia_cipf_dag_descriptor
 */
typedef struct cipf_dag_attribute
{
    cipf_dag_attribute_type_t   type;
    ia_cipf_payload_t           payload;
} ia_cipf_dag_attribute_t;

/**
 * \ingroup ia_cipf_dag_descriptor
 */
typedef struct cipf_dag_item
{
    cipf_dag_item_type_t    type;
    ia_uid                  uid;
    ia_list_t               *attribute;
} ia_cipf_dag_item_t;

/** Descriptor **/

/** Create dag descriptor object
 *
 * \ingroup ia_cipf_dag_descriptor
 */
ia_cipf_dag_descriptor_t* ia_cipf_dag_descriptor_create(void);

/** Add item into dag descriptor
 *
 * \ingroup ia_cipf_dag_descriptor
 *
 * Passes the ownership of item object to the descriptor.
 */
css_err_t ia_cipf_dag_descriptor_add_item(ia_cipf_dag_descriptor_t *dag_desc,
                                         ia_cipf_dag_item_t *item);

/** Destroy dag descriptor object
 *
 *  \ingroup ia_cipf_dag_descriptor
 *
 * Destroys all the child items.
 */
void ia_cipf_dag_descriptor_destroy(ia_cipf_dag_descriptor_t *dag_desc);

/** Item **/

/** Create dag descriptor item
 *
 *  \ingroup ia_cipf_dag_descriptor
 */
ia_cipf_dag_item_t* ia_cipf_dag_item_create(void);

/** Add attribute into dag descriptor item
 *
 * \ingroup ia_cipf_dag_descriptor
 *
 * Passes the ownership of attribute object to the item.
 */
css_err_t ia_cipf_dag_item_add_attribute(ia_cipf_dag_item_t *item,
                                        ia_cipf_dag_attribute_t *attribute);

/** Destroy dag descriptor item
 *
 * \ingroup ia_cipf_dag_descriptor
 *
 * Destroys all the child attributes
 */
void ia_cipf_dag_item_destroy(ia_cipf_dag_item_t *item);

/** Attribute **/

/** Create dag descriptor item attribute
 *
 * \ingroup ia_cipf_dag_descriptor
 */
ia_cipf_dag_attribute_t* ia_cipf_dag_attribute_create(void);

/** Destroy dag descriptor item attribute
 *
 * \ingroup ia_cipf_dag_descriptor
 */
void ia_cipf_dag_attribute_destroy(ia_cipf_dag_attribute_t *attribute);


#endif
