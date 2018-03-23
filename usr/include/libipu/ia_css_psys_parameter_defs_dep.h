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

#ifndef __IA_CSS_PSYS_PARAMETER_DEFS_DEP_H
#define __IA_CSS_PSYS_PARAMETER_DEFS_DEP_H

#include "ia_css_isa_parameter_defs_dep.h"
#include "ia_css_psa_parameter_defs_dep.h"

/* Please be aware that below enums are not released userspace
 * The only reason to still have them is that test application
 * and the bxt_pss code has dependency to these enums
 */

enum ia_css_psys_kernel_id {
	IA_CSS_PSYS_KERNEL_ID_WBA_WBA,
	IA_CSS_PSYS_KERNEL_ID_RYNR_SPLITTER,
	IA_CSS_PSYS_KERNEL_ID_RYNR_COLLECTOR,
	IA_CSS_PSYS_KERNEL_ID_RYNR_BNLM,
	IA_CSS_PSYS_KERNEL_ID_RYNR_VCUD,
	IA_CSS_PSYS_KERNEL_ID_DEMOSAIC_DEMOSAIC,
	IA_CSS_PSYS_KERNEL_ID_ACM_CCM,
	IA_CSS_PSYS_KERNEL_ID_ACM_ACM,
	IA_CSS_PSYS_KERNEL_ID_VCA_VCR2,
	IA_CSS_PSYS_KERNEL_ID_GTC_CSC_CDS,
	IA_CSS_PSYS_KERNEL_ID_GTC_GTM,
	IA_CSS_PSYS_KERNEL_ID_YUV1_SPLITTER,
	IA_CSS_PSYS_KERNEL_ID_YUV1_IEFD,
	IA_CSS_PSYS_KERNEL_ID_YUV1_YDS,
	IA_CSS_PSYS_KERNEL_ID_YUV1_TCC,
	IA_CSS_PSYS_KERNEL_ID_DVS_YBIN,
	IA_CSS_PSYS_KERNEL_ID_DVS_DVS,
	IA_CSS_PSYS_KERNEL_ID_LACE_LACE,
	IA_CSS_PSYS_KERNEL_ID_OFS_OF,
	IA_CSS_PSYS_KERNEL_ID_OFS_SC0,
	IA_CSS_PSYS_KERNEL_ID_OFS_SC1,
	IA_CSS_PSYS_KERNEL_ID_OFS_ISP,
	N_IA_CSS_PSYS_KERNEL_ID
};


enum ia_css_psys_acc_id {
	IA_CSS_PSYS_ACC_ID_WBA,
	IA_CSS_PSYS_ACC_ID_RYNR,
	IA_CSS_PSYS_ACC_ID_DEMOSAIC,
	IA_CSS_PSYS_ACC_ID_ACM,
	IA_CSS_PSYS_ACC_ID_GTC,
	IA_CSS_PSYS_ACC_ID_YUV1,
	IA_CSS_PSYS_ACC_ID_DVS,
	IA_CSS_PSYS_ACC_ID_LACE,
	IA_CSS_PSYS_ACC_ID_OFS,
	N_IA_CSS_PSYS_ACC_ID
};

#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_RYNR_SPLITTER                    (IA_CSS_PSYS_ACC_ID_RYNR)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_RYNR_COLLECTOR                   (IA_CSS_PSYS_ACC_ID_RYNR)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_RYNR_BNLM                        (IA_CSS_PSYS_ACC_ID_RYNR)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_RYNR_VCUD                        (IA_CSS_PSYS_ACC_ID_RYNR)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_ACM_CCM                          (IA_CSS_PSYS_ACC_ID_ACM)
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_ACM_ACM                          (IA_CSS_PSYS_ACC_ID_ACM)
/* The VCA cluster and ACM cluster are equivalent */
#define IA_CSS_PSYS_KERNEL_BELONGS_TO_ACC_VCA_VCR2                         (IA_CSS_PSYS_ACC_ID_ACM)

/*END of section that is referred by "Please be aware that below enums are not released userspace" comment. */


#endif /* __IA_CSS_PSYS_PARAMETER_DEFS_DEP_H */
