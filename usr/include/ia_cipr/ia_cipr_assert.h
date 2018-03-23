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
 * ia_cipr_assert.h
 */

#ifndef IA_CIPR_ASSERT_H_
#define IA_CIPR_ASSERT_H_

#ifdef _KERNEL_MODE

#include <wdm.h>
#include <windef.h>
/**
* \ingroup ia_cipr
* assert wrapper-macro. Breaks if expression fails.
*/
#define IA_CIPR_ASSERT(expr) \
    ASSERT(expr)

#else  /* _KERNEL_MODE */

#include <assert.h>

/**
 * \ingroup ia_cipr
 * assert wrapper-macro. Breaks if expression fails.
 */
#ifdef __KLOCWORK__
#define IA_CIPR_ASSERT(expr) do { if (!(expr)) abort(); } while (0)
#else
#define IA_CIPR_ASSERT(expr) assert(expr)
#endif /* __KLOCWORK__ */

#endif /* _KERNEL_MODE */

/**
* \ingroup ia_cipr
* compilation time check. Fails compilation if expression is true
*/
#define IA_CIPR_COMPILATION_FAIL_IF(condition) \
      ((void)sizeof(char[1 - 2*!!(condition)]))

#endif /* IA_CIPR_ASSERT_H_ */
