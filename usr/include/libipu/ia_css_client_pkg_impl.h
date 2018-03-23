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

#ifndef __IA_CSS_CLIENT_PKG_IMPL_H
#define __IA_CSS_CLIENT_PKG_IMPL_H

#include "ia_css_client_pkg.h"
#include "ia_css_client_pkg_types.h"
#include "error_support.h"

IA_CSS_CLIENT_PKG_STORAGE_CLASS_C
int ia_css_client_pkg_get_pg_manifest_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size)
{
	int ret_val = -1;

	verifjmpexit(NULL != client_pkg_header);
	verifjmpexit(NULL != offset);
	verifjmpexit(NULL != size);

	*(offset) = client_pkg_header->pg_manifest_offset;
	*(size) = client_pkg_header->pg_manifest_size;
	ret_val = 0;
EXIT:
	return ret_val;
}

IA_CSS_CLIENT_PKG_STORAGE_CLASS_C
int ia_css_client_pkg_get_prog_list_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size)
{
	int ret_val = -1;

	verifjmpexit(NULL != client_pkg_header);
	verifjmpexit(NULL != offset);
	verifjmpexit(NULL != size);

	*(offset) = client_pkg_header->prog_list_offset;
	*(size) = client_pkg_header->prog_list_size;
	ret_val = 0;
EXIT:
	return ret_val;
}

IA_CSS_CLIENT_PKG_STORAGE_CLASS_C
int ia_css_client_pkg_get_prog_desc_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size)
{
	int ret_val = -1;

	verifjmpexit(NULL != client_pkg_header);
	verifjmpexit(NULL != offset);
	verifjmpexit(NULL != size);

	*(offset) = client_pkg_header->prog_desc_offset;
	*(size) = client_pkg_header->prog_desc_size;
	ret_val = 0;
EXIT:
	return ret_val;
}

IA_CSS_CLIENT_PKG_STORAGE_CLASS_C
int ia_css_client_pkg_get_prog_bin_entry_offset_size(
	const ia_css_client_pkg_t *client_pkg,
	uint32_t program_id,
	uint32_t *offset,
	uint32_t *size)
{
	uint8_t i;
	int ret_val = -1;
	struct ia_css_client_pkg_header_s *client_pkg_header = NULL;
	const struct ia_css_client_pkg_prog_list_s *pkg_prog_list = NULL;
	const struct ia_css_client_pkg_prog_s *pkg_prog_bin_entry = NULL;

	verifjmpexit(NULL != client_pkg);
	verifjmpexit(NULL != offset);
	verifjmpexit(NULL != size);

	client_pkg_header =
		(struct ia_css_client_pkg_header_s *)((uint8_t *)client_pkg);
	pkg_prog_list =
		(struct ia_css_client_pkg_prog_list_s *)((uint8_t *)client_pkg +
		client_pkg_header->prog_list_offset);
	pkg_prog_bin_entry =
		(struct ia_css_client_pkg_prog_s *)((uint8_t *)pkg_prog_list +
		sizeof(struct ia_css_client_pkg_prog_list_s));
	pkg_prog_bin_entry += pkg_prog_list->prog_desc_count;

	for (i = 0; i < pkg_prog_list->prog_bin_count; i++) {
		if (program_id == pkg_prog_bin_entry->prog_id) {
			*(offset) = pkg_prog_bin_entry->prog_offset;
			*(size) = pkg_prog_bin_entry->prog_size;
			ret_val = 0;
			break;
		} else if (0 == pkg_prog_bin_entry->prog_size) {
			/* We can have a variable number of program descriptors.
			 * The first non-valid one will have size set to 0
			*/
			break;
		}
		pkg_prog_bin_entry++;
	}
EXIT:
	return ret_val;
}

IA_CSS_CLIENT_PKG_STORAGE_CLASS_C
int ia_css_client_pkg_get_indexed_prog_desc_entry_offset_size(
	const ia_css_client_pkg_t *client_pkg,
	uint32_t program_id,
	uint32_t program_index,
	uint32_t *offset,
	uint32_t *size)
{
	int ret_val = -1;
	struct ia_css_client_pkg_header_s *client_pkg_header = NULL;
	const struct ia_css_client_pkg_prog_list_s *pkg_prog_list = NULL;
	const struct ia_css_client_pkg_prog_s *pkg_prog_desc_entry = NULL;

	verifjmpexit(NULL != client_pkg);
	verifjmpexit(NULL != offset);
	verifjmpexit(NULL != size);

	client_pkg_header =
		(struct ia_css_client_pkg_header_s *)((uint8_t *)client_pkg);
	pkg_prog_list =
		(struct ia_css_client_pkg_prog_list_s *)((uint8_t *)client_pkg +
		client_pkg_header->prog_list_offset);
	pkg_prog_desc_entry =
		(struct ia_css_client_pkg_prog_s *)((uint8_t *)pkg_prog_list +
		sizeof(struct ia_css_client_pkg_prog_list_s));

	verifjmpexit(program_index < pkg_prog_list->prog_desc_count);
	verifjmpexit(program_id == pkg_prog_desc_entry[program_index].prog_id);
	verifjmpexit(pkg_prog_desc_entry[program_index].prog_size > 0);
	*(offset) = pkg_prog_desc_entry[program_index].prog_offset;
	*(size) = pkg_prog_desc_entry[program_index].prog_size;
	ret_val = 0;

EXIT:
	return ret_val;
}

#endif /* __IA_CSS_CLIENT_PKG_IMPL_H */
