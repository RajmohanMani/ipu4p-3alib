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

#ifndef __IA_CSS_PSYS_SERVER_MANIFEST_H
#define __IA_CSS_PSYS_SERVER_MANIFEST_H

#include "vied_nci_psys_resource_model.h"

/**
 * Manifest of resources in use by PSYS itself
 */

#define PSYS_SERVER_DMA_CHANNEL_SIZE	2
#define PSYS_SERVER_DMA_CHANNEL_OFFSET	28

extern const vied_nci_resource_spec_t psys_server_manifest;

#endif /* __IA_CSS_PSYS_SERVER_MANIFEST_H */
