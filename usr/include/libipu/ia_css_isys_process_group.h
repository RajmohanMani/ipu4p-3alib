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

#ifndef __IA_CSS_ISYS_PROCESS_GROUP_H
#define __IA_CSS_ISYS_PROCESS_GROUP_H

#include "ia_css_isys_process_group_types.h" /* for ia_css_process_group_light_s */
#include "type_support.h"

typedef struct ia_css_process_group_light_s	ia_css_process_group_light_t;
typedef uint16_t 				ia_css_terminal_offset_t;		/**< To be used as element in the array of terminal offsets */


/**< Partial means without counting the terminal sizes contained */
extern unsigned int ia_css_process_group_light_get_partial_descriptor_size(
	const unsigned int terminal_count
);

/**< This returns the pointer where the terminal_index'th terminal offset is stored */
extern ia_css_terminal_offset_t *ia_css_process_group_light_get_terminal_offset_offset(
	const ia_css_process_group_light_t *process_group_light,
	const uint16_t terminal_index
);

/**< This will initialize the process_group_light basic struct (optimal packing) */
extern int ia_css_process_group_light_create(
	ia_css_process_group_light_t *process_group_light,
	const uint32_t total_process_group_light_size,	/**< Contains also the terminal sizes */
	const uint16_t terminal_count
);


#endif /* __IA_CSS_ISYS_PROCESS_GROUP_H */
