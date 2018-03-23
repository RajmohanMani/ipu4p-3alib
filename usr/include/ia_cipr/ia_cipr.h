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

#ifndef _IA_CIPR_H_
#define _IA_CIPR_H_

/**
 * TODO: split & get rid of ia_tools
 */
#include <ia_tools/css_types.h>

/** \file ia_cipr.h
 *
 * \ingroup ia_cipr
 *
 * Common API for Camera Imaging Platform Runtime features
 *
 * Includes qyery functions with semantics derived from OpenCL Platform Layer.
 */

typedef uint8_t ia_cipr_platform_id_t;
typedef uint8_t ia_cipr_device_id_t;
typedef uint8_t ia_cipr_device_type_t;

typedef enum {
    cipr_platform_info_key_na
} ia_cipr_platform_info_key_t;

typedef enum {
    cipr_device_info_key_na
} ia_cipr_device_info_key_t;

typedef struct _cipr_context* ia_cipr_context_t;

/**
 * Create and initialize CIPR context
 *
 * \ingroup ia_cipr
 *
 * \return cipr context struct
 */
ia_cipr_context_t ia_cipr_create(void);

/**
 * Destroy and deinitialize CIPR context
 *
 * \ingroup ia_cipr
 *
 * \param[in] cipr context struct
 */
void ia_cipr_destroy(ia_cipr_context_t ctx);

/**
 * Qyery available platform IDs
 *
 * \ingroup ia_cipr
 *
 * \param[in]   num_entries   number of platform id elements that can be stored
 *                            in \p platforms.
 * \param[out]  platforms     returns a list of platform IDs available.
 * \param[out]  num_platforms returns the number of IDs stored in \p
 *                            platforms.
 */
css_err_t ia_cipr_get_platform_ids(uint32_t num_entries,
                                  ia_cipr_platform_id_t *platforms,
                                  uint32_t *num_platforms);

/**
 * Query platform info
 *
 * \ingroup ia_cipr
 *
 * \param[in]   platform      platform ID to query
 * \param[in]   key           key for information to query
 * \param[in]   value_size    storage size in bytes for \p value
 * \param[out]  value         pointer where to store the info
 * \param[out]  ret_value_size returns size in bytes written to \p value
 */
css_err_t ia_cipr_get_platform_info(ia_cipr_platform_id_t platform,
                                   ia_cipr_platform_info_key_t key,
                                   uint32_t value_size,
                                   void *value,
                                   uint32_t *ret_value_size);

/**
 * Qyery available device IDs from platform
 *
 * \ingroup ia_cipr
 *
 * \param[in]   platform      platform ID to query
 * \param[in]   device_type   bitfield for device types to query
 * \param[in]   num_entries   number of platform id elements that can be stored
 *                            in \p platforms.
 * \param[out]  devices       a list of device IDs available in platform
 * \param[out]  num_devices   returns the number of IDs stored in \p
 *                            platforms.
 */
css_err_t ia_cipr_get_device_ids(ia_cipr_platform_id_t platform,
                                ia_cipr_device_type_t device_type,
                                uint32_t num_entries,
                                ia_cipr_device_id_t *devices,
                                uint32_t *num_devices);

/**
 * Query device info
 *
 * \ingroup ia_cipr
 *
 * \param[in]   device        device ID to query
 * \param[in]   key           key for information to query
 * \param[in]   value_size    storage size in bytes for \p value
 * \param[out]  value         pointer where to store the info
 * \param[out]  ret_value_size returns size in bytes written to \p value
 */
css_err_t ia_cipr_get_device_info(ia_cipr_device_id_t device,
                                 ia_cipr_device_info_key_t key,
                                 uint32_t value_size,
                                 void *value,
                                 uint32_t *ret_value_size);

#endif /* _IA_CIPR_H_ */
