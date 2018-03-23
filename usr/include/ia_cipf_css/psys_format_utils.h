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
#ifndef _PSYS_FORMAT_UTILS_H_
#define _PSYS_FORMAT_UTILS_H_


#include <ia_css_program_group_data_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "ia_tools/css_types.h"


/* Get css frame format type for fourcc */
css_err_t fourcc_to_css_frame_format(const uint32_t fourcc,
    ia_css_frame_format_type_t *css_frame_format_out,
    bool *raw_bayer_out,
    bool *packed_out);

#ifdef __cplusplus
}
#endif

#endif
