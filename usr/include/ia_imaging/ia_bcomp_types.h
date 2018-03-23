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

/*!
 * \file ia_bcomp_types.h
*/

#ifndef IA_BCOMP_TYPES_H_
#define IA_BCOMP_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_AMOUNT_OF_KNEE_POINTS   16

typedef struct ia_bcomp_t ia_bcomp;

/*!
* \brief compression curves.
*/
typedef struct ia_pwl_compression_curve
{
    uint32_t x[MAX_AMOUNT_OF_KNEE_POINTS];
    uint32_t y[MAX_AMOUNT_OF_KNEE_POINTS];
    uint32_t num_of_knee_points;
} ia_pwl_compression_curve;

/*!
 * \brief calculated compression curves.
 */
typedef struct ia_bcomp_results
{
    ia_pwl_compression_curve pwl_compression_curve; /*!< piecewise linear compression curve */
} ia_bcomp_results;


#ifdef __cplusplus
}
#endif
#endif /* IA_BCOMP_TYPES_H_ */
