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

#ifndef _SCOPEDATRACE_H_
#define _SCOPEDATRACE_H_

#include <unistd.h>

namespace icamera {

/**
 * Following 2 macros PERF_CAMERA_ATRACE() or PERF_CAMERA_ATRACE_PARAM1() can be called in the function we are
 * scoping. Environment variable "camPerf" is need to be set as "16", to enalbe such atrace profiling.
 */
class ScopedAtrace {
      public:
          ScopedAtrace(const char* func, const char* tag, const char* note = NULL, long value = -1, \
                         const char* note2 = NULL, int value2 = -1, const char* note3 = NULL, int value3 = -1);
          ~ScopedAtrace();
          static void setTraceLevel(int);
};
#define PERF_CAMERA_ATRACE() ScopedAtrace atrace(__func__, LOG_TAG);
#define PERF_CAMERA_ATRACE_PARAM1(note, value) ScopedAtrace atrace(__func__, LOG_TAG, note, value);
#define PERF_CAMERA_ATRACE_PARAM2(note, value, note2, value2) \
        ScopedAtrace atrace(__func__, LOG_TAG, note, value, note2, value2);
#define PERF_CAMERA_ATRACE_PARAM3(note, value, note2, value2, note3, value3) \
        ScopedAtrace atrace(__func__, LOG_TAG, note, value, note2, value2, note3, value3);

} // namespace icamera

#endif //_SCOPEDATRACE_H_
