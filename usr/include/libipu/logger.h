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

/**
 * @file logger.h
 *
 * @brief Global objects needed for printing messages while doing logging
 */

#ifndef __LOGGER_H
#define __LOGGER_H

#include <string.h>
#include "print_support.h"
#include "misc_support.h"
#include "storage_class.h"
#include "assert_support.h"

/**
 * This variable represent the log message subtype
 */
enum loglevel {
	LOGLEVEL_INFO,
	LOGLEVEL_DEBUG,
	LOGLEVEL_WARNING,
	LOGLEVEL_ERROR
};

/**
 * This macro gives the short name of the input file, instead of providing the full path.
 * Note that the macro only might give a desired result on certain platforms.
 * In case no '/' is found, the input string is returned.
 */
#define __FILE_NO_PATH__ (__file_no_path__private(__FILE__))

STORAGE_CLASS_INLINE const char *__file_no_path__private(const char *file)
{
	const char *last_slash;

	assert(file != NULL); /* responsibility of caller to check for NULL */

	last_slash = strrchr(file, '/');
	/*
	 * If last_slash != NULL, then (last_slash + 1) is always a valid string.
	 * Note that *(last_slash + 1) is allowed to be and can be the string terminating character.
	 */
	return ((last_slash != NULL) ? (last_slash + 1) : file);
}

/**
 * Macro
 */

#ifdef HOST_DEBUG_ENABLE
#define PRINT_LOG_PRINT_DEBUG_LEVEL 1
#else
#define PRINT_LOG_PRINT_DEBUG_LEVEL 0
#endif

/** A code-path without using logger.c is implemented in order to avoid
 * the issue with unsafe functions that are used in logger.c.
 * Certain functions, like strlen, vsnprintf, ... are considered unsafe and
 * are not allowed in the Windows user mode release package (which uses logger.h).
 * However, the safe versions like strlen_s are not available for the FW build (GCC).
 * See ticket #H1504581314.
 */
#ifdef HOST_LOGGER_USE_LOGGER_C_BACKEND

/**
 * This macro acts as a wrapper of function "print_log". It adds the filename,
 * function name and line number as permanent input arguments of "print_log"
 * function call
 */
#define PRINT_LOG(level, msg, ...)                                          \
do {                                                                        \
if (level != LOGLEVEL_DEBUG || PRINT_LOG_PRINT_DEBUG_LEVEL)                 \
	print_log(level, msg", file: %s, func: %s, line: %d",               \
		  ##__VA_ARGS__, __FILE_NO_PATH__, __FUNCTION__, __LINE__); \
} while (0)

/**
 * Macro
 */
/**
 * This macro acts as a wrapper of function "print_log". It adds the filename,
 * function name and line number as permanent input arguments of "print_log"
 * function call
 */
#define PRINT_LOG_AND_TIME(level, msg, ...)                                  \
do {                                                                         \
	print_log_and_time(level, msg", file: %s, func: %s, line: %d",       \
		  ##__VA_ARGS__, __FILE_NO_PATH__, __FUNCTION__, __LINE__);  \
} while (0)                                                                  \

/**
 * @brief Print the message with given Level of the logging and argument list.
 *
 * This function directs the logging message to stdout
 * It calls generate_msg internally to construct message
 * in template format.
 * level argument refers to Info | Debug | Error | Warning
 * msg argument refers to variable message to be displayed.
 *
 * @param[in]   level           Level of the logging (Info/Debug/Warming/Error). Used for the prefix
 * @param[in]   msg             Base message.
 *
 * @return Generated message.
 */
void print_log(enum loglevel level, char *msg, ...);

/**
 * @brief Print the message with given Level of the logging and argument list (including timestamp).
 *
 * This function directs the logging message to stdout
 * It calls generate_msg internally to construct message
 * in template format.
 * level argument refers to Info | Debug | Error | Warning
 * msg argument refers to variable message to be displayed.
 *
 * @param[in]   level           Level of the logging (Info/Debug/Warming/Error). Used for the prefix
 * @param[in]   msg             Base message.
 *
 * @return Generated message.
 */
void print_log_and_time(enum loglevel level, char *msg, ...);


#else /* HOST_LOGGER_USE_LOGGER_C_BACKEND */


#define PRINT_LOG(level, msg, ...)                                          \
do {                                                                        \
if (level != LOGLEVEL_DEBUG || PRINT_LOG_PRINT_DEBUG_LEVEL)                 \
	PRINT(STR(level) " " msg ", file: %s, func: %s, line: %d\n",        \
		  ##__VA_ARGS__, __FILE_NO_PATH__, __FUNCTION__, __LINE__); \
} while (0)

#define PRINT_LOG_AND_TIME(level, msg, ...)  PRINT_LOG(level, msg, ##__VA_ARGS__)


#endif /* HOST_LOGGER_USE_LOGGER_C_BACKEND */

#endif /* __LOGGER_H */
