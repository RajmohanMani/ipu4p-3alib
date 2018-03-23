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

#ifndef __IA_CSS_PSYS_PRIVATE_PG_DATA_H
#define __IA_CSS_PSYS_PRIVATE_PG_DATA_H

#include "ipu_device_acb_devices.h"
#include "ipu_device_gp_devices.h"
#include "type_support.h"
#include "vied_nci_acb_route_type.h"

#define PRIV_CONF_INVALID	0xFF

struct ia_css_psys_pg_buffer_information_s {
	unsigned int buffer_base_addr;
	unsigned int bpe;
	unsigned int buffer_width;
	unsigned int buffer_height;
	unsigned int num_of_buffers;
	unsigned int dfm_port_addr;
};

typedef struct ia_css_psys_pg_buffer_information_s ia_css_psys_pg_buffer_information_t;

struct ia_css_psys_private_pg_data {
	nci_acb_route_t acb_route[IPU_DEVICE_ACB_NUM_ACB];
	uint8_t psa_mux_conf[IPU_DEVICE_GP_PSA_MUX_NUM_MUX];
	uint8_t isa_mux_conf[IPU_DEVICE_GP_ISA_STATIC_MUX_NUM_MUX];
	ia_css_psys_pg_buffer_information_t input_buffer_info;
};

#endif /* __IA_CSS_PSYS_PRIVATE_PG_DATA_H */

