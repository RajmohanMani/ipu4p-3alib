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

#ifndef __IA_CSS_PSYS_PROCESS_HSYS_KERNEL_H
#define __IA_CSS_PSYS_PROCESS_HSYS_KERNEL_H

/*! \file */

/** @file ia_css_psys_process.hsys.kernel.h
 *
 * Define the methods on the process object: Hsys kernel interface
 */

#include <ia_css_psys_process_types.h>

#include <vied_nci_psys_system_global.h>

/*
 * Internal resources
 */

/*! Clear all resource (offset) specifications

 @param	process[in]				process object

 @return < 0 on error
 */
extern int ia_css_process_clear_all(ia_css_process_t *process);

/*! Set the cell ID resource specification

 @param	process[in]				process object
 @param	cell_id[in]				cell ID

 @return < 0 on error
 */
extern int ia_css_process_set_cell(
	ia_css_process_t					*process,
	const vied_nci_cell_ID_t				cell_id);

/*! Clear cell ID resource specification

 @param	process[in]				process object

 @return < 0 on error
 */
extern int ia_css_process_clear_cell(ia_css_process_t *process);

/*! Set the memory resource (offset) specification for a memory
 that belongs to the cell that is assigned to the process

 @param	process[in]				process object
 @param	mem_type_id[in]				mem type ID
 @param	offset[in]				offset

 Precondition: The cell ID must be set

 @return < 0 on error
 */
extern int ia_css_process_set_int_mem(
	ia_css_process_t		*process,
	const	vied_nci_mem_type_ID_t	mem_type_id,
	const vied_nci_resource_size_t	offset);

/*! Clear the memory resource (offset) specification for a memory
 type that belongs to the cell that is assigned to the process

 @param	process[in]				process object
 @param	mem_id[in]				mem ID

 Precondition: The cell ID must be set

 @return < 0 on error
 */
extern int ia_css_process_clear_int_mem(
	ia_css_process_t		*process,
	const vied_nci_mem_type_ID_t	mem_type_id);

/*! Set the memory resource (offset) specification for a memory
 that does not belong to the cell that is assigned to the process

 @param	process[in]				process object
 @param	mem_type_id[in]				mem type ID
 @param	offset[in]				offset

 Precondition: The cell ID must be set

 @return < 0 on error
 */
extern int ia_css_process_set_ext_mem(
	ia_css_process_t		*process,
	const vied_nci_mem_ID_t		mem_id,
	const vied_nci_resource_size_t	offset);

/*! Clear the memory resource (offset) specification for a memory
 type that does not belong to the cell that is assigned to the process

 @param	process[in]				process object
 @param	mem_id[in]				mem ID

 Precondition: The cell ID must be set

 @return < 0 on error
 */
extern int ia_css_process_clear_ext_mem(
	ia_css_process_t		*process,
	const vied_nci_mem_type_ID_t	mem_type_id);

/*! Set a device channel resource (offset) specification

 @param	process[in]				process object
 @param	dev_chn_id[in]			device channel ID
 @param	offset[in]				offset

 @return < 0 on error
 */
extern int ia_css_process_set_dev_chn(
	ia_css_process_t		*process,
	const vied_nci_dev_chn_ID_t	dev_chn_id,
	const vied_nci_resource_size_t	offset);

/*! Clear a device channel resource (offset) specification

 @param	process[in]				process object
 @param	dev_chn_id[in]			device channel ID

 @return < 0 on error
 */
extern int ia_css_process_clear_dev_chn(
	ia_css_process_t		*process,
	const vied_nci_dev_chn_ID_t	dev_chn_id);

#endif /* __IA_CSS_PSYS_PROCESS_HSYS_KERNEL_H */
