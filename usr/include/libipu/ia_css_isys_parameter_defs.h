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

#ifndef __IA_CSS_ISYS_PARAMETER_DEFS_H
#define __IA_CSS_ISYS_PARAMETER_DEFS_H

#include "ia_css_isys_parameter_defs_dep.h"
#include "ia_css_isa_parameter_defs.h"

/* If in the future differences are found they need to be moved to the dep file */

enum ia_css_isys_exclusive_group_id {
	IA_CSS_ISYS_EXCLUSIVE_GROUP_INVALID,
	IA_CSS_ISYS_EXCLUSIVE_GROUP_BLC,
	IA_CSS_ISYS_EXCLUSIVE_GROUP_LSC,
	/* Add here more exclusive kernel group ID's if they exist */
	N_IA_CSS_ISYS_EXCLUSIVE_GROUP
};


enum ia_css_isys_kernel_state {
	IA_CSS_ISYS_KERNEL_STATE_DISABLED,
	IA_CSS_ISYS_KERNEL_STATE_ENABLED,
	IA_CSS_ISYS_KERNEL_STATE_EXCLUDED,
	N_IA_CSS_ISYS_KERNEL_STATE
};


#endif /* __IA_CSS_ISYS_PARAMETER_DEFS_H */

