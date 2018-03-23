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

#ifndef __IA_CSS_ISP_DVS_TYPES_H
#define __IA_CSS_ISP_DVS_TYPES_H

#include <type_support.h>

#define IA_CSS_PSYS_PARAMETER_TERMINAL_ISP_DVS_CONFIG_SECTION_COUNT  (1)
#define IA_CSS_PSYS_PARAMETER_TERMINAL_ISP_DVS_CONFIG_SIZE_SECTION_0 (sizeof(struct ia_css_isp_dvs_config))
#define IA_CSS_PSYS_PROGRAM_TERMINAL_ISP_DVS_CONFIG_SECTION_COUNT    (0)

#define IA_CSS_PSYS_SPATIAL_PARAMETER_TERMINAL_ISP_DVS_COORDS_SECTION_COUNT       1 /* only one section/plane is used */
#define IA_CSS_PSYS_SPATIAL_PARAMETER_TERMINAL_ISP_DVS_COORDS_REGION_ID           0 /* only have region 0 */
#define IA_CSS_PSYS_SPATIAL_PARAMETER_TERMINAL_ISP_DVS_COORDS_ELEM_SIZE           0x40 /*(sizeof(gdc_warp_param_mem_t)),  an element is of type gdc_warp_param_mem_t */


/** DVS frame
 *
 *  ISP block: dvs frame
 */

/** dvs params
 * The LUT has 256 entries, containing 6 coefficients each.
 * Each lut entry has to be stored in below format for 6x6 filter
 * LUT Entry	MSB Coeff	LSB Coeff
 * 0		C5		C4
 *			C3		C2
 *			C1		C0
 *			x		x
*/

struct ia_css_isp_dvs_config {
	uint32_t interpolation_type;
	uint32_t filter_size;
	uint32_t lut_sel;
	uint32_t nums_luts;
	uint16_t lut[6][256];
};


#endif /* __IA_CSS_ISP_DVS_TYPES_H */

