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

#ifndef __IA_CSS_PKG_DIR_IUNIT_H
#define __IA_CSS_PKG_DIR_IUNIT_H

/* In bootflow, pkg_dir only supports upto 16 entries in pkg_dir
 * pkg_dir_header + Psys_server pg + Isys_server pg + 13 Client pg
 */

enum  {
	IA_CSS_PKG_DIR_SIZE    = 16,
	IA_CSS_PKG_DIR_ENTRIES = IA_CSS_PKG_DIR_SIZE - 1
};

#define IUNIT_MAX_CLIENT_PKG_ENTRIES	13

/* Example assignment of unique identifiers for the FW components
 * This should match the identifiers in the manifest
 */
enum ia_css_pkg_dir_entry_type {
	IA_CSS_PKG_DIR_HEADER = 0,
	IA_CSS_PKG_DIR_PSYS_SERVER_PG,
	IA_CSS_PKG_DIR_ISYS_SERVER_PG,
	IA_CSS_PKG_DIR_CLIENT_PG
};

/* Fixed entries in the package directory */
enum ia_css_pkg_dir_index {
	IA_CSS_PKG_DIR_PSYS_INDEX = 0,
	IA_CSS_PKG_DIR_ISYS_INDEX = 1,
	IA_CSS_PKG_DIR_CLIENT_0   = 2
};

#endif /* __IA_CSS_PKG_DIR_IUNIT_H */

