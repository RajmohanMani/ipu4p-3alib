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

#include "ia_css_rbm_manifest.h"
#include "ia_css_rbm_trace.h"

#include "type_support.h"
#include "math_support.h"
#include "error_support.h"
#include "assert_support.h"
#include "print_support.h"

STORAGE_CLASS_INLINE
void __ia_css_rbm_manifest_check_struct(void)
{
	COMPILATION_ERROR_IF(
		sizeof(ia_css_rbm_manifest_t) != (SIZE_OF_RBM_MANIFEST_S / IA_CSS_UINT8_T_BITS));
	COMPILATION_ERROR_IF(
		(sizeof(ia_css_rbm_manifest_t) % 8 /* 64 bit */) != 0);
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
unsigned int
ia_css_rbm_manifest_get_size(void)
{
	unsigned int size = sizeof(struct ia_css_rbm_manifest_s);

	return ceil_mul(size, sizeof(uint64_t));
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
void
ia_css_rbm_manifest_init(struct ia_css_rbm_manifest_s *rbm)
{
	rbm->mux_desc_count = 0;
	rbm->terminal_routing_desc_count = 0;
	rbm->validation_rule_count = 0;
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
ia_css_rbm_mux_desc_t *
ia_css_rbm_manifest_get_muxes(const ia_css_rbm_manifest_t *manifest)
{
#if VIED_NCI_RBM_MAX_MUX_COUNT == 0
	(void)manifest;
	return NULL;
#else
	return (ia_css_rbm_mux_desc_t *)manifest->mux_desc;
#endif
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
unsigned int
ia_css_rbm_manifest_get_mux_count(const ia_css_rbm_manifest_t *manifest)
{
	return manifest->mux_desc_count;
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
ia_css_rbm_validation_rule_t *
ia_css_rbm_manifest_get_validation_rules(const ia_css_rbm_manifest_t *manifest)
{
#if VIED_NCI_RBM_MAX_VALIDATION_RULE_COUNT == 0
	(void)manifest;
	return NULL;
#else
	return (ia_css_rbm_validation_rule_t *)manifest->validation_rules;
#endif
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
unsigned int
ia_css_rbm_manifest_get_validation_rule_count(const ia_css_rbm_manifest_t *manifest)
{
	return manifest->validation_rule_count;
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
ia_css_rbm_terminal_routing_desc_t *
ia_css_rbm_manifest_get_terminal_routing_desc(const ia_css_rbm_manifest_t *manifest)
{
#if VIED_NCI_RBM_MAX_TERMINAL_DESC_COUNT == 0
	(void)manifest;
	return NULL;
#else
	return (ia_css_rbm_terminal_routing_desc_t *)manifest->terminal_routing_desc;
#endif
}

IA_CSS_RBM_MANIFEST_STORAGE_CLASS_C
unsigned int
ia_css_rbm_manifest_get_terminal_routing_desc_count(const ia_css_rbm_manifest_t *manifest)
{
	return manifest->terminal_routing_desc_count;
}
