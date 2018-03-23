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
#ifndef _PSYS_UTILS_H_
#define _PSYS_UTILS_H_

#include <ia_cipf/ia_cipf_types.h>

/** Write data into parameter section associated with buffer
 *
 * PSYS PG parameter sections are exposed as CIPF stage properties
 * with offset value from buffer payload start address. This function
 * fetches the property with given UID and copies data from given
 * data address to section offset address. Function is intended for
 * writing defaults. Dynamic operations should access the payload
 * directly.
 *
 * \ingroup ia_cipf_css
 *
 * \param[in,out]   buffer      handle to ia_cipf_buffer_t
 * \param[in]       section_uid uid to the payload section property
 * \param[in]       data        pointer to source data to copy
 * \param[in]       size        size of source data to validate with property
 */
css_err_t
psys_utils_write_buffer_section(ia_cipf_buffer_t *buffer,
                                ia_uid section_uid,
                                void const *data,
                                uint32_t size);

/** Read data from parameter section associated with buffer
 *
 * PSYS PG parameter sections are exposed as CIPF stage properties
 * with offset value from buffer payload start address. This function
 * fetches the property with given UID and copies data from section
 * offset address to given data address.
 *
 * \ingroup ia_cipf_css
 *
 * \param[in]   buffer      handle to ia_cipf_buffer_t
 * \param[in]   section_uid uid to the payload section property
 * \param[out]  data        pointer to source data to copy
 * \param[in]   size        size of source data to validate with property
 */
css_err_t
psys_utils_read_buffer_section(ia_cipf_buffer_t *buffer,
                               ia_uid section_uid,
                               void *data,
                               uint32_t size);

#endif /* _PSYS_UTILS_H_ */
