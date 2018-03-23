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

#ifndef __IA_CSS_PKG_DIR_INT_H
#define __IA_CSS_PKG_DIR_INT_H

/*
 *	Package Dir structure as specified in CSE FAS
 *
 *	PKG DIR Header
 *	Qword	63:56	55	54:48	47:32	31:24	23:0
 *	0	"_IUPKDR_"
 *	1	Rsvd	Rsvd	Type	Version	Rsvd	Size
 *
 *	Version:	Version of the Structure
 *	Size:	Size of the entire table (including header) in 16 byte chunks
 *	Type:	Must be 0 for header
 *
 *	Figure 13: PKG DIR Header
 *
 *
 *	PKG DIR Entry
 *	Qword	63:56	55	54:48	47:32	31:24	23:0
 *	N	Address/Offset
 *	N+1	Rsvd	Rsvd	Type	Version	Rsvd	Size
 *
 *	Version:	Version # of the Component
 *	Size:	Size of the component in bytes
 *	Type:	Component Identifier
 */

#define PKG_DIR_SIZE_BITS 24
#define PKG_DIR_TYPE_BITS 7

#define PKG_DIR_MAGIC_VAL_1	(('_' << 24) | ('I' << 16) | ('U' << 8) | 'P')
#define PKG_DIR_MAGIC_VAL_0	(('K' << 24) | ('D' << 16) | ('R' << 8) | '_')

#endif /* __IA_CSS_PKG_DIR_INT_H */

