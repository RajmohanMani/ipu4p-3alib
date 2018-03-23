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

/*
 * ia_cipr_alloc.h
 */

#ifndef IA_CIPR_ALLOC_H_
#define IA_CIPR_ALLOC_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file ia_cipr_alloc.h
 *
 * \brief posix compatible host memory allocation API
 */

#ifdef RNDBUILD
#define IACIPR_FUNC __FUNCTION__
#define IACIPR_FILE __FILE__
#define IACIPR_LINE __LINE__
#else
#define IACIPR_FUNC ""
#define IACIPR_FILE ""
#define IACIPR_LINE 0
#endif

/**
 * \ingroup ia_cipr_memory
 * wrapper-macro for getting page size.
 *
 * Note: This is only code style addition to be used with
 * _ALLOC_ALIGNED-macro:
 * * IA_CIPR_ALLOC_ALIGNED(size, IA_CIPR_PAGESIZE())
 */
#define IA_CIPR_PAGESIZE() \
    ia_cipr_pagesize()

/**
 * \ingroup ia_cipr_memory
 * malloc wrapper-macro. Logs the caller among other things.
 */
#define IA_CIPR_MALLOC(size) \
    ia_cipr_malloc(size, IACIPR_FUNC, IACIPR_FILE, IACIPR_LINE)

/**
 * \ingroup ia_cipr_memory
 * calloc wrapper-macro. Logs the caller among other things.
 */
#define IA_CIPR_CALLOC(nmemb, size) \
    ia_cipr_calloc(nmemb, size, IACIPR_FUNC, IACIPR_FILE, IACIPR_LINE)

/**
 * \ingroup ia_cipr_memory
 * alloc_aligned wrapper-macro. Logs the caller among other things.
 */
#define IA_CIPR_ALLOC_ALIGNED(size, alignment) \
    ia_cipr_alloc_aligned(size, alignment, IACIPR_FUNC, IACIPR_FILE, IACIPR_LINE)

/**
 * \ingroup ia_cipr_memory
 * free wrapper-macro. Logs the caller among other things.
 */
#define IA_CIPR_FREE(ptr) \
    ia_cipr_free(ptr, IACIPR_FUNC)

/**
 * \ingroup ia_cipr_memory
 * memcpy wrapper-macro.
 */
#define IA_CIPR_MEMCOPY(dest, dest_size, src, n) \
    ia_cipr_memcopy(dest, dest_size, src, n)

/**
 * \ingroup ia_cipr_memory
 */
size_t ia_cipr_pagesize(void);

/**
 * \param size as in malloc
 * \param logmsg entered by macro IA_CIPR_MALLOC. The caller function.
 * \ingroup ia_cipr_memory
 */
void* ia_cipr_malloc(size_t size,
                     const char *logmsg,
                     const char *file_name,
                     int line);

/**
 * \param nmemb as in calloc
 * \param size as in calloc
 * \param logmsg entered by macro IA_CIPR_CALLOC. The caller function.
 * \ingroup ia_cipr_memory
 */
void* ia_cipr_calloc(size_t nmemb,
                     size_t size,
                     const char *logmsg,
                     const char *file_name,
                     int line);

/** Allocate aligned memory (as defined in posix_memalign())
 *
 * Returns pointer to free()'able memory or zero.
 *
 * \param size as in malloc
 * \param alignment as in posix_memalign
 * \param logmsg entered by macro IA_CIPR_CALLOC. The caller function.
 * \ingroup ia_cipr_memory
 */
void* ia_cipr_alloc_aligned(size_t size,
                            size_t alignment,
                            const char *logmsg,
                            const char *file_name,
                            int line);

/**
 * \param *ptr as in free
 * \param logmsg entered by macro IA_CIPR_FREE. The caller function.
 * \ingroup ia_cipr_memory
 */
void ia_cipr_free(void *ptr, const char *logmsg);

/**
 * \param dest as in memcpy
 * \param dest_size as in memcpy_s, max number of bytes to modify in destination
 * \param src as in memcpy
 * \param n as in memcpy
 * \ingroup ia_cipr_memory
 */
void ia_cipr_memcopy(void *dest,
                     size_t dest_size,
                     const void *src,
                     size_t n);

#ifdef __cplusplus
}
#endif


#endif /* IA_CIPR_ALLOC_H_ */
