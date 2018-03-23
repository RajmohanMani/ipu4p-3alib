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

#ifndef __IA_CSS_CLIENT_PKG_TYPES_H
#define __IA_CSS_CLIENT_PKG_TYPES_H

#include "type_support.h"

typedef void ia_css_client_pkg_t;

struct ia_css_client_pkg_header_s {
	uint32_t prog_list_offset;
	uint32_t prog_list_size;
	uint32_t prog_desc_offset;
	uint32_t prog_desc_size;
	uint32_t pg_manifest_offset;
	uint32_t pg_manifest_size;
	uint32_t prog_bin_offset;
	uint32_t prog_bin_size;
};

struct ia_css_client_pkg_prog_s {
	uint32_t prog_id;
	uint32_t prog_offset;
	uint32_t prog_size;
};

struct ia_css_client_pkg_prog_list_s {
	uint32_t prog_desc_count;
	uint32_t prog_bin_count;
};

#endif /* __IA_CSS_CLIENT_PKG_TYPES_H */
