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
 * @file error_handler.h
 * @brief This file contains error enums and handler for the fwapi testbench.
 */

#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H

/* Bit position signifies the expected_error_code
 * for example: HOST_DATA_MISMATCH has expected_error_code as 2 */
#define HOST_MAX_STATUS 31
enum host_ret_type {
	HOST_SUCCESS            = 0,
	HOST_FAILURE            = (1 << 0),
	HOST_DATA_MISMATCH      = (1 << 1),
	HOST_PARAMOUT_MISMATCH  = (1 << 2),
	HOST_PGS_NOT_CONCURRENT = (1 << 3),
	HOST_PARSER_ERROR       = (1 << 4),
	HOST_PSYS_EVENT_HANDLER = (1 << 5),
	HOST_ISYS_EVENT_HANDLER = (1 << 6),
	HOST_MALLOC_FAILURE     = (1 << 7),
	HOST_ISYS_ERROR_FW_INTERNAL_CONSISTENCY             = (1 << 8),
	HOST_ISYS_ERROR_HW_CONSISTENCY                      = (1 << 9),
	HOST_ISYS_ERROR_DRIVER_INVALID_COMMAND_SEQUENCE     = (1 << 10),
	HOST_ISYS_ERROR_DRIVER_INVALID_DEVICE_CONFIGURATION = (1 << 11),
	HOST_ISYS_ERROR_DRIVER_INVALID_STREAM_CONFIGURATION = (1 << 12),
	HOST_ISYS_ERROR_DRIVER_INVALID_FRAME_CONFIGURATION  = (1 << 13),
	HOST_ISYS_ERROR_INSUFFICIENT_RESOURCES              = (1 << 14),
	HOST_ISYS_ERROR_HW_REPORTED_STR2MMIO                = (1 << 15),
	HOST_ISYS_ERROR_HW_REPORTED_SIG2CIO                 = (1 << 16),
	HOST_ISYS_ERROR_SENSOR_FW_SYNC                      = (1 << 17),
	HOST_ISYS_ERROR_STREAM_IN_SUSPENSION                = (1 << 18),
	HOST_ISYS_ERROR_RESPONSE_QUEUE_FULL                 = (1 << 19),
	HOST_ERROR_OPEN_STREAM                              = (1 << 20), /* Temporal error type */
	HOST_STIMULI_ERROR                                  = (1 << 21),
	/* New error codes to be added here */
	HOST_N_STATES           = (1 << HOST_MAX_STATUS)
};

/**
 * @brief Compare accumulated error with expected error.
 *
 * This function maps user given expected_error_code to host_ret_type enum
 * and checks if it matches accumulated error
 *
 * @param[in]   error                 Accumulated error
 * @param[in]   expected_error_code   Bit in host_ret_type enum; range in [0 .. HOST_MAX_STATUS]
 *
 * @retval HOST_SUCCESS     if (expected_error_code != 0) and expected error matches
 * @retval HOST_FAILURE     if (expected_error_code != 0) and expected error does not match
 * @retval error            if (expected_error_code == 0)
 */
enum host_ret_type
check_expected_error(int error, int expected_error_code);

#endif /* __ERROR_HANDLER_H */
