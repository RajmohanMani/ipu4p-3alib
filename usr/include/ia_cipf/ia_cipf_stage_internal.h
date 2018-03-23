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

#ifndef _IA_CIPF_STAGE_INTERNAL_H_
#define _IA_CIPF_STAGE_INTERNAL_H_

#include "ia_cipf_types.h"
#include <ia_cipf/ia_cipf_stage_backend.h>

/**
 * \ingroup ia_cipf_internals
 */
css_err_t
ia_cipf_stage_load(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_internals
 */
css_err_t
ia_cipf_stage_execute(ia_cipf_stage_t *stage);

/**
 * \ingroup ia_cipf_internals
 */
css_err_t
ia_cipf_stage_wait(ia_cipf_stage_t *stage);

#endif /* _IA_CIPF_STAGE_INTERNAL_H_ */
