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
#ifndef _DEC400_UTIL_WRAPPER_H_
#define _DEC400_UTIL_WRAPPER_H_

#include <stdint.h>

// This needs to stay in sync with IA_CSS_CMPRS_MAX_TS_OFFSETS from nci_dec400_util_inline.h
#define MAX_TS_OFFSETS 3

namespace dec400util {

unsigned calcBufferSize(
    const uint32_t fourcc,
    unsigned bitDepth,
    bool isTnr,
    unsigned stride,
    unsigned height,
    unsigned extraMem,
    unsigned tsOffsets[MAX_TS_OFFSETS],
    unsigned tsSizes[MAX_TS_OFFSETS]);

unsigned numberOfPlanes(const uint32_t fourcc);

} // namespace dec400util

#endif // _DEC400_UTIL_WRAPPER_H_

