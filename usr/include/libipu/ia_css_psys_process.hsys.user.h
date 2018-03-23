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

#ifndef __IA_CSS_PSYS_PROCESS_HSYS_USER_H
#define __IA_CSS_PSYS_PROCESS_HSYS_USER_H

/*! \file */

/** @file ia_css_psys_process.hsys.user.h
 *
 * Define the methods on the process object: Hsys user interface
 */

#include <ia_css_program_group_param.h>		/* ia_css_program_param_t */

#include <ia_css_psys_process_types.h>
#include <ia_css_psys_manifest_types.h>

#include <type_support.h>					/* uint8_t */

/*
 * Creation
 */

/*! Compute the size of storage required for allocating the process object

 @param	manifest[in]			program manifest
 @param	param[in]				program parameters

 @return 0 on error
 */
extern size_t ia_css_sizeof_process(
	const ia_css_program_manifest_t			*manifest,
	const ia_css_program_param_t			*param);

/*! Create the process object

 @param	raw_mem[in]				pre allocated memory
 @param	manifest[in]			program manifest
 @param	param[in]				program parameters

 @return NULL on error
 */
extern ia_css_process_t *ia_css_process_create(
	void				*raw_mem,
	const ia_css_program_manifest_t	*manifest,
	const ia_css_program_param_t	*param,
	const uint32_t			program_idx);

/*! Destroy (the storage of) the process object

 @param	process[in]				process object

 @return NULL
 */
extern ia_css_process_t *ia_css_process_destroy(
	ia_css_process_t	*process);

/*
 * Access functions
 */

/*! Print the process object to file/stream

 @param	process[in]				process object
 @param	fid[out]				file/stream handle

 @return < 0 on error
 */
extern int ia_css_process_print(
	const ia_css_process_t	*process,
	void			*fid);

#endif /* __IA_CSS_PSYS_PROCESS_HSYS_USER_H */
