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

#ifndef __PRINT_SUPPORT_H
#define __PRINT_SUPPORT_H

#if defined(_MSC_VER)
#ifdef _KERNEL_MODE

/* TODO: Windows driver team to provide tracing mechanism for kernel mode
 * e.g. DbgPrint and DbgPrintEx
 */
extern void FwTracePrintPWARN(const char *fmt, ...);
extern void FwTracePrintPRINT(const char *fmt, ...);
extern void FwTracePrintPERROR(const char *fmt, ...);
extern void FwTracePrintPDEBUG(const char *fmt, ...);

#define PWARN(format, ...)	FwTracePrintPWARN(format, __VA_ARGS__)
#define PRINT(format, ...)	FwTracePrintPRINT(format, __VA_ARGS__)
#define PERROR(format, ...)	FwTracePrintPERROR(format, __VA_ARGS__)
#define PDEBUG(format, ...)	FwTracePrintPDEBUG(format, __VA_ARGS__)

#else
/* Windows usermode compilation */
#include <stdio.h>

/* To change the defines below, communicate with Windows team first
 * to ensure they will not get flooded with prints
 */
/* This is temporary workaround to avoid flooding userspace
 * Windows driver with prints
 */

#define PWARN(format, ...)
#define PRINT(format, ...)
#define PERROR(format, ...)	printf("error: " format, __VA_ARGS__)
#define PDEBUG(format, ...)

#endif /* _KERNEL_MODE */

#elif defined(__HIVECC)
#include <hive/support.h>
/* To be revised

#define PWARN(format)
#define PRINT(format)				OP___printstring(format)
#define PERROR(variable)			OP___dump(9999, arguments)
#define PDEBUG(variable)			OP___dump(__LINE__, arguments)

*/

#define PRINTSTRING(str) OP___printstring(str)

#elif defined(__KERNEL__)
#include <linux/kernel.h>
#include <linux/printk.h>


#define PWARN(format, arguments...)	pr_debug(format, ##arguments)
#define PRINT(format, arguments...)	pr_debug(format, ##arguments)
#define PERROR(format, arguments...)	pr_debug(format, ##arguments)
#define PDEBUG(format, arguments...)	pr_debug(format, ##arguments)

#else
#include <stdio.h>

#define PRINT_HELPER(prefix, format, ...) printf(prefix format "%s", __VA_ARGS__)

/* The trailing "" allows the edge case of printing single string */
#define PWARN(...)  PRINT_HELPER("warning: ", __VA_ARGS__, "")
#define PRINT(...)  PRINT_HELPER("", __VA_ARGS__, "")
#define PERROR(...) PRINT_HELPER("error: ", __VA_ARGS__, "")
#define PDEBUG(...) PRINT_HELPER("debug: ", __VA_ARGS__, "")

#define PRINTSTRING(str) PRINT(str)

#endif

#endif /* __PRINT_SUPPORT_H */
