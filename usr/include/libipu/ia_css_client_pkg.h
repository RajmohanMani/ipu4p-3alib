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

#ifndef __IA_CSS_CLIENT_PKG_H
#define __IA_CSS_CLIENT_PKG_H

#include "type_support.h"
#include "ia_css_client_pkg_storage_class.h"
/* for ia_css_client_pkg_header_s (ptr only), ia_css_client_pkg_t */
#include "ia_css_client_pkg_types.h"

IA_CSS_CLIENT_PKG_STORAGE_CLASS_H
int ia_css_client_pkg_get_pg_manifest_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size);

IA_CSS_CLIENT_PKG_STORAGE_CLASS_H
int ia_css_client_pkg_get_prog_list_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size);

IA_CSS_CLIENT_PKG_STORAGE_CLASS_H
int ia_css_client_pkg_get_prog_desc_offset_size(
	const struct ia_css_client_pkg_header_s *client_pkg_header,
	uint32_t *offset,
	uint32_t *size);

IA_CSS_CLIENT_PKG_STORAGE_CLASS_H
int ia_css_client_pkg_get_prog_bin_entry_offset_size(
	const ia_css_client_pkg_t *client_pkg,
	uint32_t program_id,
	uint32_t *offset,
	uint32_t *size);

IA_CSS_CLIENT_PKG_STORAGE_CLASS_H
int ia_css_client_pkg_get_indexed_prog_desc_entry_offset_size(
	const ia_css_client_pkg_t *client_pkg,
	uint32_t program_id,
	uint32_t program_index,
	uint32_t *offset,
	uint32_t *size);

#ifdef __INLINE_CLIENT_PKG__
#include "ia_css_client_pkg_impl.h"
#endif

#endif /* __IA_CSS_CLIENT_PKG_H */
