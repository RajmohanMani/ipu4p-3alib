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

#ifndef __IA_CSS_TERMINAL_MANIFEST_H
#define __IA_CSS_TERMINAL_MANIFEST_H

#include "type_support.h"
#include "ia_css_param_storage_class.h"
#include "ia_css_terminal_manifest_types.h"

IA_CSS_PARAMETERS_STORAGE_CLASS_H
unsigned int ia_css_param_terminal_manifest_get_size(
	const unsigned int nof_sections
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
int ia_css_param_terminal_manifest_init(
	ia_css_param_terminal_manifest_t *param_terminal,
	const uint16_t section_count
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
ia_css_param_manifest_section_desc_t *
ia_css_param_terminal_manifest_get_prm_sct_desc(
	const ia_css_param_terminal_manifest_t *param_terminal_manifest,
	const unsigned int section_index
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
unsigned int ia_css_spatial_param_terminal_manifest_get_size(
	const unsigned int nof_frame_param_sections
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
int ia_css_spatial_param_terminal_manifest_init(
	ia_css_spatial_param_terminal_manifest_t *spatial_param_terminal,
	const uint16_t section_count
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
ia_css_frame_grid_param_manifest_section_desc_t *
ia_css_spatial_param_terminal_manifest_get_frm_grid_prm_sct_desc(
	const ia_css_spatial_param_terminal_manifest_t *
		spatial_param_terminal_manifest,
	const unsigned int section_index
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
unsigned int ia_css_sliced_param_terminal_manifest_get_size(
	const unsigned int nof_slice_param_sections
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
int ia_css_sliced_param_terminal_manifest_init(
	ia_css_sliced_param_terminal_manifest_t *sliced_param_terminal,
	const uint16_t section_count
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
ia_css_sliced_param_manifest_section_desc_t *
ia_css_sliced_param_terminal_manifest_get_sliced_prm_sct_desc(
	const ia_css_sliced_param_terminal_manifest_t *
		sliced_param_terminal_manifest,
	const unsigned int section_index
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
unsigned int ia_css_program_terminal_manifest_get_size(
	const unsigned int nof_fragment_param_sections,
	const unsigned int nof_kernel_fragment_sequencer_infos
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
int ia_css_program_terminal_manifest_init(
	ia_css_program_terminal_manifest_t *program_terminal,
	const uint16_t fragment_param_section_count,
	const uint16_t kernel_fragment_seq_info_section_count
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
ia_css_fragment_param_manifest_section_desc_t *
ia_css_program_terminal_manifest_get_frgmnt_prm_sct_desc(
	const ia_css_program_terminal_manifest_t *program_terminal_manifest,
	const unsigned int section_index
);

IA_CSS_PARAMETERS_STORAGE_CLASS_H
ia_css_kernel_fragment_sequencer_info_manifest_desc_t *
ia_css_program_terminal_manifest_get_kernel_frgmnt_seq_info_desc(
	const ia_css_program_terminal_manifest_t *program_terminal_manifest,
	const unsigned int info_index
);

#ifdef __INLINE_PARAMETERS__
#include "ia_css_terminal_manifest_impl.h"
#endif /* __INLINE_PARAMETERS__ */

#endif /* __IA_CSS_TERMINAL_MANIFEST_H */
