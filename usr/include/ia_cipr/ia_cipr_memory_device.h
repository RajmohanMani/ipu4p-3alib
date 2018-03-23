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

#ifndef _IA_CIPR_MEMORY_DEVICE_H_
#define _IA_CIPR_MEMORY_DEVICE_H_

#include <ia_cipr/ia_cipr_memory.h>

/**
 * \file ia_cipr_memory_device.h
 *
 * \brief Tentative definition for memory device interface abstraction
 *
 * \defgroup ia_cipr_memory_device Memory Device
 * \ingroup ia_cipr_memory
 */
typedef struct _cipr_memory_device_ops  ia_cipr_memory_device_t;

/**
 * Migrate buffer object with specific memory device
 *
 * This function lets user to associate in which device address space the
 * memory of buffer resides. Actual memory operations done depend on
 * allocation and usage information given to \p buffer.
 *
 * \ingroup ia_cipr_memory_device
 *
 * \param[in]   memory_device   interface handle of specific memory device
 * \param[in]   buffer          buffer object to associate
 */
css_err_t
ia_cipr_memory_device_migrate_buffer(ia_cipr_memory_device_t *memory_device,
                                     ia_cipr_buffer_t *buffer);

#endif /* _IA_CIPR_MEMORY_DEVICE_H_ */

