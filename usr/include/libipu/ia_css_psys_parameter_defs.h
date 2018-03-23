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

#ifndef __IA_CSS_PSYS_PARAMETER_DEFS_H
#define __IA_CSS_PSYS_PARAMETER_DEFS_H


#include "type_support.h"

#include "ia_css_psys_parameter_defs_dep.h"

#include "ia_css_isa_parameter_defs.h"
#include "ia_css_psa_parameter_defs.h"
#include "ia_css_ofs_parameter_defs.h"

#define IA_CSS_PSYS_KERNEL_UNSUPPORTED (0)
#define IA_CSS_PSYS_KERNEL_TO_BE_COMPLETED (0)
#define IA_CSS_PSYS_SPATIAL_PARAMETER_TERMINAL_INVALID (0)

enum ia_css_psys_exclusive_group_id {
	IA_CSS_PSYS_EXCLUSIVE_GROUP_INVALID,
	N_IA_CSS_PSYS_EXCLUSIVE_GROUP
};

enum ia_css_psys_kernel_state {
	IA_CSS_PSYS_KERNEL_STATE_DISABLED,
	IA_CSS_PSYS_KERNEL_STATE_ENABLED,
	IA_CSS_PSYS_KERNEL_STATE_EXCLUDED,
	N_IA_CSS_PSYS_KERNEL_STATE
};

enum ia_css_psys_kernel_param_section {
	IA_CSS_PSYS_KERNEL_PARAM_SECTION_0,
	IA_CSS_PSYS_KERNEL_PARAM_SECTION_1,
	IA_CSS_PSYS_KERNEL_PARAM_SECTION_2,
	IA_CSS_PSYS_KERNEL_PARAM_SECTION_3,
	N_IA_CSS_PSYS_KERNEL_PARAM_SECTION
};

enum ia_css_psys_kernel_fragment_param_section {
	IA_CSS_PSYS_KERNEL_FRAGMENT_PARAM_SECTION_0,
	IA_CSS_PSYS_KERNEL_FRAGMENT_PARAM_SECTION_1,
	N_IA_CSS_PSYS_KERNEL_FRAGMENT_PARAM_SECTION
};

enum ia_css_psys_kernel_frame_grid_param_section {
	IA_CSS_PSYS_KERNEL_FRAME_GRID_PARAM_SECTION_0,
	IA_CSS_PSYS_KERNEL_FRAME_GRID_PARAM_SECTION_1,
	N_IA_CSS_PSYS_KERNEL_FRAME_GRID_PARAM_SECTION
};

/* fragment descriptor, in future official fragment
 * descriptor from PSYS API can be used */
struct ia_css_fragment_desc {
	uint16_t	fragment_width;
	uint16_t	fragment_height;
	uint16_t	fragment_start_x;
	uint16_t	fragment_start_y;
};

/* Common defines across A0 and B0 */

#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_WBA_WBA                          (IA_CSS_PSYS_ACC_ID_WBA)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_DEMOSAIC_DEMOSAIC                (IA_CSS_PSYS_ACC_ID_DEMOSAIC)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_GTC_CSC_CDS                      (IA_CSS_PSYS_ACC_ID_GTC)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_GTC_GTM                          (IA_CSS_PSYS_ACC_ID_GTC)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_YUV1_SPLITTER                    (IA_CSS_PSYS_ACC_ID_YUV1)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_YUV1_IEFD                        (IA_CSS_PSYS_ACC_ID_YUV1)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_YUV1_YDS                         (IA_CSS_PSYS_ACC_ID_YUV1)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_YUV1_TCC                         (IA_CSS_PSYS_ACC_ID_YUV1)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_DVS_YBIN                         (IA_CSS_PSYS_ACC_ID_DVS)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_DVS_DVS                          (IA_CSS_PSYS_ACC_ID_DVS)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_LACE_LACE                        (IA_CSS_PSYS_ACC_ID_LACE)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_OFS_OF                           (IA_CSS_PSYS_ACC_ID_OFS)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_OFS_SC0                          (IA_CSS_PSYS_ACC_ID_OFS)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_OFS_SC1                          (IA_CSS_PSYS_ACC_ID_OFS)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_OFS_ISP                          (IA_CSS_PSYS_ACC_ID_OFS)


#endif /* __IA_CSS_PSYS_PARAMETER_DEFS_H */

