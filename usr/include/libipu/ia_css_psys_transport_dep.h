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

#ifndef __IA_CSS_PSYS_TRANSPORT_DEP_H
#define __IA_CSS_PSYS_TRANSPORT_DEP_H

/*
 * The ID's of the Psys specific queues.
 */
typedef enum ia_css_psys_cmd_queues {
	/**< The in-order queue for scheduled process groups */
	IA_CSS_PSYS_CMD_QUEUE_COMMAND_ID = 0,
	/**< The in-order queue for commands changing psys or
	 * process group state
	 */
	IA_CSS_PSYS_CMD_QUEUE_DEVICE_ID,
	/**< An in-order queue for dedicated PPG commands */
	IA_CSS_PSYS_CMD_QUEUE_PPG0_COMMAND_ID,
	/**< An in-order queue for dedicated PPG commands */
	IA_CSS_PSYS_CMD_QUEUE_PPG1_COMMAND_ID,
	IA_CSS_N_PSYS_CMD_QUEUE_ID
} ia_css_psys_cmd_queue_ID_t;

#endif /* __IA_CSS_PSYS_TRANSPORT_DEP_H */
