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

#ifndef __IA_CSS_ISYS_PROCESS_GROUP_TYPES_H
#define __IA_CSS_ISYS_PROCESS_GROUP_TYPES_H

#include "type_support.h"


struct ia_css_process_group_light_s {			/**< Structure as is is 64-bit aligned */
	uint32_t	size;				/**< Total size of this structure and all its underlying ones */
	uint16_t	terminals_offset_offset;	/**< offset of "ia_css_terminal_offset_t array[terminal_count]" containing terminal offsets on this process group */
	uint16_t	terminal_count;			/**< Number of terminals for this process group (param, program, spatial param) */
};


#endif /* __IA_CSS_ISYS_PROCESS_GROUP_TYPES_H */
