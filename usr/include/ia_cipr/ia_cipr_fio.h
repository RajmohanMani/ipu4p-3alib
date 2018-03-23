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

#ifndef _IA_CIPR_FIO_H_
#define _IA_CIPR_FIO_H_

/**
 * \file ia_cipr_fio.h
 *
 * Tentative CIPR File IO Header
 *
 * \defgroup ia_cipr_fio File-IO
 * \ingroup ia_cipr
 *
 * CIPR File IO is inteded for wrapping basic stdio file operations.
 * This is mainly needed for Windows kernel mode compilation. The rest of CIPR
 * build scenarions are using stdio directly via declarations below.
 */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void ia_cipr_file_t;

/**
 * \ingroup ia_cipr_fio
 */
ia_cipr_file_t* ia_cipr_fopen(const char *, const char *);

/**
 * \ingroup ia_cipr_fio
 */
int ia_cipr_fclose(ia_cipr_file_t *);

/**
 * \ingroup ia_cipr_fio
 */
size_t ia_cipr_fread(void *, size_t, size_t, ia_cipr_file_t *);

/**
 * \ingroup ia_cipr_fio
 */
size_t ia_cipr_fwrite(const void *, size_t, size_t, ia_cipr_file_t *);

/**
 * \ingroup ia_cipr_fio
 */
int ia_cipr_fseek(ia_cipr_file_t *, long int, int);

/**
 * \ingroup ia_cipr_fio
 */
long int ia_cipr_ftell(ia_cipr_file_t *);

/**
 * \ingroup ia_cipr_fio
 */
int ia_cipr_ferror(ia_cipr_file_t *);

/**
 * \ingroup ia_cipr_fio
 */
void ia_cipr_clearerr(ia_cipr_file_t *);

#ifdef __cplusplus
}
#endif


#endif /* _IA_CIPF_FIO_H_ */
