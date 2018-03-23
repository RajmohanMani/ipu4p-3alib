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

#ifndef __IA_CSS_TERMINAL_BASE_TYPES_H
#define __IA_CSS_TERMINAL_BASE_TYPES_H


#include "type_support.h"
#include "ia_css_terminal_defs.h"

#define N_UINT16_IN_TERMINAL_STRUCT		3
#define N_PADDING_UINT8_IN_TERMINAL_STRUCT	5

#define SIZE_OF_TERMINAL_STRUCT_BITS \
	(IA_CSS_TERMINAL_TYPE_BITS \
	+ IA_CSS_TERMINAL_ID_BITS  \
	+ N_UINT16_IN_TERMINAL_STRUCT * IA_CSS_UINT16_T_BITS \
	+ N_PADDING_UINT8_IN_TERMINAL_STRUCT * IA_CSS_UINT8_T_BITS)

/* ==================== Base Terminal - START ==================== */
struct ia_css_terminal_s {						/**< Base terminal */
	ia_css_terminal_type_t			terminal_type;		/**< Type ia_css_terminal_type_t */
	int16_t					parent_offset;		/**< Offset to the process group */
	uint16_t				size;			/**< Size of this whole terminal layout-structure */
	uint16_t				tm_index;		/**< Index of the terminal manifest object */
	ia_css_terminal_ID_t			ID;			/**< Absolute referal ID for this terminal, valid ID's != 0 */
	uint8_t					padding[N_PADDING_UINT8_IN_TERMINAL_STRUCT];
};
/* ==================== Base Terminal - END ==================== */

#endif /* __IA_CSS_TERMINAL_BASE_TYPES_H */

