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

#ifndef __IA_CSS_TERMINAL_MANIFEST_BASE_TYPES_H
#define __IA_CSS_TERMINAL_MANIFEST_BASE_TYPES_H

#include "ia_css_terminal_defs.h"

#define N_PADDING_UINT8_IN_TERMINAL_MAN_STRUCT	5
#define SIZE_OF_TERMINAL_MANIFEST_STRUCT_IN_BITS \
	(IA_CSS_UINT16_T_BITS \
	+ IA_CSS_TERMINAL_ID_BITS \
	+ IA_CSS_TERMINAL_TYPE_BITS \
	+ IA_CSS_UINT32_T_BITS \
	+ (N_PADDING_UINT8_IN_TERMINAL_MAN_STRUCT*IA_CSS_UINT8_T_BITS))

/* ==================== Base Terminal Manifest - START ==================== */
struct ia_css_terminal_manifest_s {
	ia_css_terminal_type_t				terminal_type;		/**< Type ia_css_terminal_type_t */
	int16_t						parent_offset;		/**< Offset to the program group manifest */
	uint16_t					size;			/**< Size of this whole terminal-manifest layout-structure */
	ia_css_terminal_ID_t				ID;
	uint8_t						padding[N_PADDING_UINT8_IN_TERMINAL_MAN_STRUCT];
};

typedef struct ia_css_terminal_manifest_s
	ia_css_terminal_manifest_t;

/* ==================== Base Terminal Manifest - END ==================== */

#endif /* __IA_CSS_TERMINAL_MANIFEST_BASE_TYPES_H */

