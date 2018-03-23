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
#ifndef __IA_CSS_XNR4_STILL_DEFS_H
#define __IA_CSS_XNR4_STILL_DEFS_H

#include "ia_css_xnr4_defs.h"

/*******************************************************************************
 * XNR4 Still parameter terminal sections
 ******************************************************************************/
#define IA_CSS_PSYS_PARAMETER_TERMINAL_XNR4_STILL_SECTION_COUNT      (4)


/* Below 2 sections are required only for 1st ISP */
#define IA_CSS_PSYS_PARAMETER_TERMINAL_XNR4_STILL_MAX_SIZE_SECTION_0 (sizeof(struct ia_css_xnr4m_dmem_param))
#define IA_CSS_PSYS_PARAMETER_TERMINAL_XNR4_STILL_MAX_SIZE_SECTION_1 (sizeof(struct ia_css_xnr4m_vmem_param))

/* Below 2 sections are required for other 2 ISPs */
#define IA_CSS_PSYS_PARAMETER_TERMINAL_XNR4_STILL_MAX_SIZE_SECTION_2 (sizeof(struct ia_css_xnr4h_dmem_param))
#define IA_CSS_PSYS_PARAMETER_TERMINAL_XNR4_STILL_MAX_SIZE_SECTION_3 (sizeof(struct ia_css_xnr4h_vmem_param))

/*******************************************************************************
 * XNR4 Still program terminal sections
 ******************************************************************************/
#define IA_CSS_PSYS_PROGRAM_TERMINAL_XNR4_STILL_SECTION_COUNT      (1)

/* Below section is required for all 3 ISPs */
#define IA_CSS_PSYS_PROGRAM_TERMINAL_XNR4_STILL_MAX_SIZE_SECTION_0 (sizeof(struct ia_css_xnr4_fragment_param))

#endif /* __IA_CSS_XNR4_STILL_DEFS_H */
