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
 * ia_trace_linux.h
 *
 */

#ifndef _IA_TRACE_H
#define _IA_TRACE_H

#ifndef LOG_TAG
#define LOG_TAG "IA_TRACE"
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <unistd.h>
#include "ia_cipr_log.h"

#define CAMERA_PRId32 "d"
#define CAMERA_PRId64 "I64d"
#define IA_TRACE_MESSAGE_LENGTH 1024
#define IA_TRACE_TAG_ALWAYS           (1 << 0)
#define IA_TRACE_TAG_NOT_READY        (1ULL << 63)
#define IA_TRACE_TAG IA_TRACE_TAG_ALWAYS

#define IA_TRACE_INIT() ia_trace_init()
#define IA_TRACE_ENABLED() ia_trace_is_tag_enabled(IA_TRACE_TAG)
#define IA_TRACE_BEGIN(name) ia_trace_begin(IA_TRACE_TAG, name)
#define IA_TRACE_END() ia_trace_end(IA_TRACE_TAG)

#define IA_TRACE_DECLSPEC static inline

void ia_trace_setup(void);
extern volatile int32_t ia_trace_is_ready;
extern uint64_t ia_trace_enabled_tags;
extern int ia_trace_marker_fd;

IA_TRACE_DECLSPEC __attribute__((always_inline)) int32_t
ia_trace_atomic_acquire_load(volatile const int32_t *ptr)
{
    int32_t value = *ptr;
    __asm__ __volatile__ ("" : : : "memory");
    return value;
}
IA_TRACE_DECLSPEC void ia_trace_init(void)
{
    if (!ia_trace_atomic_acquire_load(&ia_trace_is_ready)) {
        ia_trace_setup();
    }
}
IA_TRACE_DECLSPEC uint64_t ia_trace_is_tag_enabled(uint64_t tag)
{
    ia_trace_init();
    return ia_trace_enabled_tags & tag;
}
IA_TRACE_DECLSPEC void ia_trace_begin(uint64_t tag, const char *name)
{
    if (ia_trace_is_tag_enabled(tag)) {
        char buf[IA_TRACE_MESSAGE_LENGTH];
        ssize_t len;
        len = snprintf(buf, IA_TRACE_MESSAGE_LENGTH, "B|%d|%s", getpid(), name);
        if (len < 0) {
            CSS_DEBUG_ERR("snprintf error!");
            return;
        }
        if (write(ia_trace_marker_fd, buf, (size_t)len) != len)
            CSS_DEBUG_ERR("write error!");
    }
}
IA_TRACE_DECLSPEC void ia_trace_end(uint64_t tag)
{
    if (ia_trace_is_tag_enabled(tag)) {
        char c = 'E';
        if (write(ia_trace_marker_fd, &c, 1) !=1)
            CSS_DEBUG_ERR("write error!");
    }
}
#endif //_IA_TRACE_H
