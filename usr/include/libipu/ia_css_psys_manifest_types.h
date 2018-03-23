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

#ifndef __IA_CSS_PSYS_MANIFEST_TYPES_H
#define __IA_CSS_PSYS_MANIFEST_TYPES_H

/*! \file */

/** @file ia_css_psys_manifest_types.h
 *
 * The types belonging to the terminal/program/
 * program group manifest static module
 */

#include <type_support.h>
#include "vied_nci_psys_resource_model.h"


/* This value is used in the manifest to indicate that the resource
 * offset field must be ignored and the resource is relocatable
 */
#define IA_CSS_PROGRAM_MANIFEST_RESOURCE_OFFSET_IS_RELOCATABLE ((vied_nci_resource_size_t)(-1))

/*
 * Connection type defining the interface source/sink
 *
 * Note that the connection type does not define the
 * real-time configuration of the system, i.e. it
 * does not describe whether a source and sink
 * program group or sub-system operate synchronously
 * that is a program script property {online, offline}
 * (see FAS 5.16.3)
 */
#define IA_CSS_CONNECTION_BITMAP_BITS 8
typedef uint8_t ia_css_connection_bitmap_t;

#define IA_CSS_CONNECTION_TYPE_BITS 32
typedef enum ia_css_connection_type {
	/**< The terminal is in DDR */
	IA_CSS_CONNECTION_MEMORY = 0,
	/**< The terminal is a (watermark) queued stream over DDR */
	IA_CSS_CONNECTION_MEMORY_STREAM,
	/* The terminal is a device port */
	IA_CSS_CONNECTION_STREAM,
	IA_CSS_N_CONNECTION_TYPES
} ia_css_connection_type_t;

#define IA_CSS_PROGRAM_TYPE_BITS 32
typedef enum ia_css_program_type {
	IA_CSS_PROGRAM_TYPE_SINGULAR = 0,
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUB,
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUPER,
	IA_CSS_PROGRAM_TYPE_PARALLEL_SUB,
	IA_CSS_PROGRAM_TYPE_PARALLEL_SUPER,
	IA_CSS_PROGRAM_TYPE_VIRTUAL_SUB,
	IA_CSS_PROGRAM_TYPE_VIRTUAL_SUPER,
/*
 * Future extension; A bitmap coding starts making more sense
 *
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUB_PARALLEL_SUB,
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUB_PARALLEL_SUPER,
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUPER_PARALLEL_SUB,
	IA_CSS_PROGRAM_TYPE_EXCLUSIVE_SUPER_PARALLEL_SUPER,
 */
	IA_CSS_N_PROGRAM_TYPES
} ia_css_program_type_t;

#define IA_CSS_PROGRAM_GROUP_ID_BITS 32
typedef uint32_t ia_css_program_group_ID_t;
#define IA_CSS_PROGRAM_ID_BITS 32
typedef uint32_t ia_css_program_ID_t;

#define IA_CSS_PROGRAM_INVALID_ID ((uint32_t)(-1))
#define IA_CSS_PROGRAM_GROUP_INVALID_ID ((uint32_t)(-1))

typedef struct ia_css_program_group_manifest_s
ia_css_program_group_manifest_t;
typedef struct ia_css_program_manifest_s
ia_css_program_manifest_t;
typedef struct ia_css_data_terminal_manifest_s
ia_css_data_terminal_manifest_t;

/* ============ Program Control Init Terminal Manifest - START ============ */
typedef struct ia_css_program_control_init_manifest_program_desc_s
	ia_css_program_control_init_manifest_program_desc_t;

typedef struct ia_css_program_control_init_terminal_manifest_s
	ia_css_program_control_init_terminal_manifest_t;
/* ============ Program Control Init Terminal Manifest - END ============ */

#endif /* __IA_CSS_PSYS_MANIFEST_TYPES_H */
