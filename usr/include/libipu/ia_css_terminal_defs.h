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

#ifndef __IA_CSS_TERMINAL_DEFS_H
#define __IA_CSS_TERMINAL_DEFS_H


#include "type_support.h"

#define IA_CSS_TERMINAL_ID_BITS		8
typedef uint8_t				ia_css_terminal_ID_t;
#define IA_CSS_TERMINAL_INVALID_ID	((ia_css_terminal_ID_t)(-1))

/*
 * Terminal Base Type
 */
typedef enum ia_css_terminal_type {
	/**< Data input */
	IA_CSS_TERMINAL_TYPE_DATA_IN = 0,
	/**< Data output */
	IA_CSS_TERMINAL_TYPE_DATA_OUT,
	/**< Type 6 parameter input */
	IA_CSS_TERMINAL_TYPE_PARAM_STREAM,
	/**< Type 1-5 parameter input */
	IA_CSS_TERMINAL_TYPE_PARAM_CACHED_IN,
	/**< Type 1-5 parameter output */
	IA_CSS_TERMINAL_TYPE_PARAM_CACHED_OUT,
	/**< Represent the new type of terminal for the
	 * "spatial dependent parameters", when params go in
	 */
	IA_CSS_TERMINAL_TYPE_PARAM_SPATIAL_IN,
	/**< Represent the new type of terminal for the
	 * "spatial dependent parameters", when params go out
	 */
	IA_CSS_TERMINAL_TYPE_PARAM_SPATIAL_OUT,
	/**< Represent the new type of terminal for the
	 * explicit slicing, when params go in
	 */
	IA_CSS_TERMINAL_TYPE_PARAM_SLICED_IN,
	/**< Represent the new type of terminal for the
	 * explicit slicing, when params go out
	 */
	IA_CSS_TERMINAL_TYPE_PARAM_SLICED_OUT,
	/**< State (private data) input */
	IA_CSS_TERMINAL_TYPE_STATE_IN,
	/**< State (private data) output */
	IA_CSS_TERMINAL_TYPE_STATE_OUT,
	IA_CSS_TERMINAL_TYPE_PROGRAM,
	IA_CSS_TERMINAL_TYPE_PROGRAM_CONTROL_INIT,
	IA_CSS_N_TERMINAL_TYPES
} ia_css_terminal_type_t;

#define IA_CSS_TERMINAL_TYPE_BITS				32

/* Temporary redirection needed to facilicate merging with the drivers
   in a backwards compatible manner */
#define IA_CSS_TERMINAL_TYPE_PARAM_CACHED IA_CSS_TERMINAL_TYPE_PARAM_CACHED_IN

/*
 * Dimensions of the data objects. Note that a C-style
 * data order is assumed. Data stored by row.
 */
/* A strange problem with hivecc compiler which is described
 * here https://icggerrit.ir.intel.com/#/c/51630/1 forces this
 * enum to be explicitly initialized for the moment
 */
typedef enum ia_css_dimension {
	/**< The number of columns, i.e. the size of the row */
	IA_CSS_COL_DIMENSION = 0,
	/**< The number of rows, i.e. the size of the column */
	IA_CSS_ROW_DIMENSION = 1,
	IA_CSS_N_DATA_DIMENSION = 2
} ia_css_dimension_t;

#define IA_CSS_N_COMMAND_COUNT (4)

#ifndef PIPE_GENERATION
/* Don't include these complex enum structures in Genpipe, it can't handle and it does not need them */
/*
 * enum ia_css_isys_link_id. Lists the link IDs used by the FW for On The Fly feature
 */
typedef enum ia_css_isys_link_id {
	IA_CSS_ISYS_LINK_OFFLINE = 0,
	IA_CSS_ISYS_LINK_MAIN_OUTPUT = 1,
	IA_CSS_ISYS_LINK_PDAF_OUTPUT = 2
} ia_css_isys_link_id_t;
#define N_IA_CSS_ISYS_LINK_ID	(IA_CSS_ISYS_LINK_PDAF_OUTPUT + 1)

/*
 * enum ia_css_data_barrier_link_id. Lists the link IDs used by the FW for data barrier feature
 */
typedef enum ia_css_data_barrier_link_id {
	IA_CSS_DATA_BARRIER_LINK_MEMORY = N_IA_CSS_ISYS_LINK_ID,
	N_IA_CSS_DATA_BARRIER_LINK_ID
} ia_css_data_barrier_link_id_t;

#endif /* #ifndef PIPE_GENERATION */
#endif /* __IA_CSS_TERMINAL_DEFS_H */
