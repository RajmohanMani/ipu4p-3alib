/*
 * Copyright 2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*!
 * \file ia_aiq_deprecated.h
 * \brief Definitions and declarations of Intel 3A library.
 */

#ifndef _IA_AIQ_DEPRECATED_H_
#define _IA_AIQ_DEPRECATED_H_

#include "ia_aiq_types.h"
#include "ia_face.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
  Forward declaration of struct declared in ia_aiq.h
*/
struct ia_aiq_pa_input_params;

/*!
 *  \brief Input parameter structure for setting the statistics.
 */
typedef struct
{
    unsigned long long frame_id;                                /*!< The frame identifier which identifies to which frame the given statistics correspond. Must be positive. */
    unsigned long long frame_timestamp;                         /*!< Mandatory although function will not return error, if not given.
                                                                     Start of frame timestamp in microseconds. This value is used in conjunction with timestamps
                                                                     provided in the AIQ algorithms function calls to calculate the convergence
                                                                     speed of AIQ algorithms.
                                                                     AEC, AWB and AF will not converge, if not given. */
    const ia_aiq_ae_results *frame_ae_parameters;               /*!< Mandatory although function will not return error, if not given.
                                                                     Exposure results from AEC which were used to capture this frame.
                                                                     AEC depends on this parameters. AEC will return cold start values if not given.*/
    const ia_aiq_af_results *frame_af_parameters;               /*!< Mandatory although function will not return error, if not given.
                                                                     Focus results from AF which were used to capture this frame.
                                                                     AEC with AF assist light and flash usage in macro functionalities depend on these parameters. */
    const ia_aiq_rgbs_grid **rgbs_grids;                        /*!< Mandatory. Almost all AIQ algorithms require RGBS grid statistics. */
    unsigned int num_rgbs_grids;                                /*!< The number of RGBS grids. */
    const ia_aiq_hdr_rgbs_grid* hdr_rgbs_grid;                  /*!< Optional. HDR statistics grid. */
    const ia_aiq_af_grid **af_grids;                            /*!< Mandatory although function will not return error, if not given.
                                                                     AF will return a NULL pointer, if not given.
                                                                     DSD will not return all scene modes, if not given. */
    unsigned int num_af_grids;                                  /*!< The number of AF grids. */
    const ia_aiq_histogram **external_histograms;               /*!< Optional. If ISP calculates histogram, if can be given. If external histogram is not given,
                                                                     AIQ internally calculates the histogram from the RGBS grid statistics and given AWB parameters. */
    unsigned int num_external_histograms;                       /*!< The number of external histograms. */
    const ia_aiq_pa_results *frame_pa_parameters;               /*!< Optional (Mandatory if external_histogram is not given).
                                                                     AWB results used in the frame from where the statistics are collected.
                                                                     GBCE will give default gamma table if external histogram or AWB results are not available. */
    const ia_face_state *faces;                                 /*!< Mandatory although function will not return error, if not given.
                                                                     Face coordinates from external face detector.
                                                                     DSD will not return all scene modes, if not given.
                                                                     AWB will not take face information into account, if not given. */
    ia_aiq_camera_orientation camera_orientation;               /*!< The orientation of the camera. Currently unused. */

    const ia_aiq_awb_results *awb_results;                      /*!< Optional. Estimated AWB results from the previous run of AWB */
    const ia_aiq_sa_results *frame_sa_parameters;               /*!< Optional. LSC results used in the frame for statistics collected. */
    const ia_aiq_depth_grid **depth_grids;                      /*!< Optional. Depth grid statistics */
    unsigned int num_depth_grids;                               /*!< Optional. Number of depth grid statistics */
} ia_aiq_statistics_input_params;

/*!
* \brief Ambient Light EventsLIGHT_AMBIENTLIGHT
* NOTE: This should always match to libsensorhub API
*/
typedef struct
{
    unsigned long long ts;  /*!< Time stamp in usec (microseconds) */
    float data;             /*!< Ambient Light data ? */
    float sensitivity;      /*!< Sensitivity of Ambient Light sensor */
    unsigned long long fs;  /*!< Frame stamp in usec (microseconds) */
} ia_aiq_ambient_light_events;

/*!
* \brief Data from external sensors
*/
typedef struct
{
    ia_aiq_sensor_data *accelerometer_events;                       /*!< The data holds information on the acceleration of the device in mg/sec (miligravity per second).
                                                                    Acceleration = Gravity + Linear Acceleration*/
    unsigned int num_accelerometer_events;                          /*!< Number of accelerometer events */
    ia_aiq_sensor_data *gravity_events;                             /*!< The data holds information on the gravitation of the device in mg/sec (miligravity per second) */
    unsigned int num_gravity_events;                                /*!< Number of gravity events */
    ia_aiq_sensor_data *gyroscope_events;                           /*!< The data holds information on the angular velocity of the device in rad/sec */
    unsigned int num_gyroscope_events;                              /*!< Number of gyroscope events */
    ia_aiq_ambient_light_events *ambient_light_events;              /*!< The data holds information on the ambient light */
    unsigned int num_ambient_light_events;                          /*!< Number of ambient light events */
    ia_aiq_dmd_sensor_events *dmd_events;                           /*!< Device Movement Detector (DMD) virtual sensor */
    unsigned int num_dmd_events;                                    /*!< Number of DMD sensor events */
} ia_aiq_sensor_events;

LIBEXPORT ia_err
ia_aiq_statistics_set(ia_aiq *ia_aiq,
    const ia_aiq_statistics_input_params *statistics_input_params);

/*!
* \brief Parameter adaptor calculations for the next frame.
* Compute generic parameters (Color Correction Matrix and Black Level Correction),
* which should be used to correct the next frame. Calculations are based on previously calculated AIQ algorithm results.
* These generic results are converted to ISP specific parameters by ia_isp component.
*
* \param[in] ia_aiq                Mandatory.\n
*                                  AIQ instance handle.
* \param[in] pa_input_params       Mandatory.\n
*                                  Input parameters for PA calculations.
* \param[out] pa_results           Mandatory.\n
*                                  Pointer's pointer where address of parameter adaptor results are stored.

* \return                          Error code.
*/
LIBEXPORT ia_err
ia_aiq_pa_run(ia_aiq *ia_aiq,
     const struct ia_aiq_pa_input_params *pa_input_params,
     ia_aiq_pa_results **pa_results);

/*!
 * \brief Set event statistics.
 * Some of the AIQ algorithms benefit from sensor information which tells about the conditions in which the device is in use
 *
 * \param[in] ia_aiq                        Mandatory.\n
 *                                          AIQ instance handle.
 * \param[in] sensor_events_input           Mandatory.\n
 *                                          Sensor events input holds data from libsensorhub.
 * \return                                  Error code.
 */
LIBEXPORT ia_err
ia_aiq_sensor_events_set(ia_aiq *ia_aiq, const ia_aiq_sensor_events *sensor_events_input);

#ifdef __cplusplus
}
#endif

#endif /* _IA_AIQ_DEPRECATED_H_ */
