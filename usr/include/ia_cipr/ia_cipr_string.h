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

#ifndef _IA_CIPR_STRING_H_
#define _IA_CIPR_STRING_H_

/**
 * \file ia_cipr_string.h
 *
 * Tentative CIPR String header
 *
 * \defgroup ia_cipr_string String
 * \ingroup ia_cipr
 *
 */

#include <stddef.h>

/**
 * \ingroup ia_cipr_string
 */
size_t ia_cipr_strnlen(const char *str, size_t size);

/**
 * \ingroup ia_cipr_string
 */
int ia_cipr_snprintf_s(char *str, size_t str_size, size_t n, const char *fmt, ...);


#endif /* _IA_CIPF_FIO_H_ */
