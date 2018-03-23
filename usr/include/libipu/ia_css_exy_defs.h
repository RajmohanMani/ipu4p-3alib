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
#ifndef __IA_CSS_EXY_DEFS_H
#define __IA_CSS_EXY_DEFS_H

#include <type_support.h>

/*******************************************************************************
 * EXY parameter terminal sections
 ******************************************************************************/
#define IA_CSS_PSYS_PARAMETER_TERMINAL_EXY_SECTION_COUNT      (1)

#define IA_CSS_PSYS_PARAMETER_TERMINAL_EXY_MAX_SIZE_SECTION_0 (sizeof(struct ia_css_isp_exy_params))

struct ia_css_isp_exy_params {
	uint16_t lpf_coef[2];
	uint16_t ns_shift;
	uint16_t padding;
};

#endif /* __IA_CSS_EXY_DEFS_H */
