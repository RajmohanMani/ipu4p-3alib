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

#ifndef _IA_CIPF_CONNECTION_H_
#define _IA_CIPF_CONNECTION_H_

#include "ia_cipf_types.h"

/** \defgroup ia_cipf_connection Connection (ia_cipf_connection_t)
 * \ingroup ia_cipf
 * \brief the ia_cipf_connection_t object interface
 */

/**
 * \ingroup ia_cipf_connection
 */
ia_cipf_connection_t *
ia_cipf_connection_create(void);

/**
 * \ingroup ia_cipf_connection
 */
void
ia_cipf_connection_destroy(ia_cipf_connection_t *connection);

/**
 * \ingroup ia_cipf_connection
 */
ia_cipf_connection_t *
ia_cipf_connection_create_init(ia_cipf_terminal_t *source,
                               ia_cipf_terminal_t *sink,
                               int32_t          branch_id,
                               ia_cipf_connection_type_t type);
#endif /* _IA_CIPF_CONNECTION_H_ */
