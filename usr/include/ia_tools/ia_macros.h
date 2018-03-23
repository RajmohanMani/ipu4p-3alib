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

#ifndef _IA_MACROS_H_
#define _IA_MACROS_H_

#include <string.h>

/**
 * Clear x
 * \ingroup ia_tools
 */
#define CLEAR(x)    memset (&(x), 0, sizeof (x))

/**
* Align to 4 byte boundary
* \ingroup ia_tools
*/
#define ALIGN4(x) (((x) + 3U) & (~3U))

/**
 * Align to 8 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN8(x)   (((x) + 7U) & ~7U)
/**
 * Align to 16 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN16(x)  (((x) + 15U) & ~15U)
/**
 * Align to 32 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN32(x)  (((x) + 31U) & ~31U)
/**
 * Align to 64 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN64(x)  (((x) + 63U) & ~63U)
/**
 * Align to 128 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN128(x) (((x) + 127U) & ~127U)
/**
 * Align to 256 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN256(x) (((x) + 255U) & ~255U)
/**
 * Align to 512 byte boundary
 * \ingroup ia_tools
 */
#define ALIGN512(x) (((x) + 511U) & ~511U)

/**
 * Align to page boundary
 * \ingroup ia_tools
 */
#ifndef PAGE_ALIGN
#define PAGE_ALIGN(x) ((x + 0xfff) & 0xfffff000)
#endif

/* Integer round-up division of a with b */
#define CEIL_DIV(a, b)  ((b) ? (((a) + (b) - 1) / (b)) : 0)
/* Align a to the upper multiple of b */
#define CEIL_MUL(a, b)  CEIL_DIV(a, b) * (b)

/* Number of elements in an array */
#define NOF_ARRAY_ELEMENTS(array) (sizeof(array) / sizeof(array[0]))

/* Return smaller of two values */
#define IA_MIN(a, b) ((a) < (b) ? (a) : (b))
/* Return larger of two values */
#define IA_MAX(a, b) ((a) > (b) ? (a) : (b))

#endif

