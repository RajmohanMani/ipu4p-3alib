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
 * \file AlgoTuning.h
 * \brief Definitions of IQ tuning related parameters.
 */

#ifndef _CAMERA_ALGO_TUNING_H_
#define _CAMERA_ALGO_TUNING_H_

/*!
 * \brief Enumeration that indicates what results LTM algorithm outputs.
 */
typedef enum
{
    ltm_algo_optibright_gain_map = 0,
    ltm_algo_coala_gain_map,
    ltm_algo_clahe_gain_map,
    ltm_algo_optibright_tone_map = (1 << 3), /*!< Optibright algorithm outputs local tone map. */
    ltm_algo_coala_tone_map,
    ltm_algo_clahe_tone_map,
} ia_ltm_algo_t;


#define SIZEOF_OPTIBRIGHT_TUNING_V100   28
#define SIZEOF_OPTIBRIGHT_TUNING_V101   4  /* maskmid */
#define SIZEOF_OPTIBRIGHT_TUNING_V102   4  /* hlc_mode */
#define SIZEOF_OPTIBRIGHT_TUNING_V103   84 /* from max_isp_gain to wdr_gain_max */
#define SIZEOF_OPTIBRIGHT_TUNING_V104   4  /* frame_delay_adaption */
/*!
 * \brief OptiBright tuning data
 */

typedef struct
{
    /*!< GTM strength: low value - darker, high value - brighter */
    int32_t GTM_Str;
    /*!< regularization (0.0.15): low value - less halos, high value - more mid tone contrast */
    int32_t GF_epspar;
    /*!< localization (0.0.15): higher value result in better mid tone contrast */
    int32_t alpham1;
    /*!< strength (0.0.15): 16384 - no effect,
                            more than 16384 - higher value makes dark area brighter and bright area darker,
                            less than 16384 - lower value makes dark area darker and bright area brighter. */
    int32_t alpham;
    /*!< min threshold (0.0.15): higher value result in cutting LTM in dark part */
    int32_t maskmin;
    /*!< max threshold (0.0.15): lower value result in cutting LTM in bright part */
    int32_t maskmax;
    /*!< number of iteration */
    int32_t num_iteration;
    /*!< mask mid point (0.0.15): defines the contrast center of the image.
                                  regions darker than mid point after global tone mapping will be brightened,
                                  and brighter regions will be darkened. typical value is 16384 or less. */
    int32_t maskmid;
    /*!< HLC mode: 0 - disable, 1 - enable */
    int32_t hlc_mode;
    /*!< max isp gain applied in LTM, default is 32x. */
    int32_t max_isp_gain;
    /*!< convergence speed [sec] (0.2.13), 0.15 [sec], 0.15 [sec] x 2^13 = 1229 */
    int32_t convergence_speed;
    /*!< local motion trade-off (0.0.15): higher value result in more contrast and more halos on local motion, and vice versa. */
    int32_t lm_treatment;
    /*!< GTM mode: 0 - logarithmic, 1 - logarithmic after gamma */
    int32_t GTM_mode;
    /*!< pre-gamma before logarithmic global tone mapping. 40 is about gamma 0.7, 60 ~ 0.61, 80 ~ 0.54, 100 ~ 0.48 */
    int32_t pre_gamma;
    /*!< lav to p scale, [1 10] */
    int32_t lav2p_scale;
    /*!< max value of p (0.0.15): limit range of p in logarithmic global tone mapping. */
    int32_t p_max;
    /*!< p mode: 0 - auto, 1 - manual, when p mode is manual, p_value is used instead of calculating p from GTM_Str. */
    int32_t p_mode;
    /*!< p value used when p mode is on. */
    int32_t p_value;
    /*!< filter size for local mean: 0 - 3x3, 1 - 5x5, 2 - 7x7 */
    int32_t filter_size;
    /*!< max percentile for determine percentage of saturation (0.0.15), 0.005% saturation - (1.0 - 0.005) x 2^15 = 32604 (default) */
    int32_t max_percentile;
    /*!< set log space average pixel value you want before gamma for low dynamic range scene (0.0.15), in wall or flat scene, brightness become specified here. */
    int32_t ldr_brightness;
    /*!< value is divided by log space average, and the ratio is used for calculating dynamic range factor (0.015) */
    int32_t dr_mid;
    /*!< max value for normalizing dynamic range factor (0.4.11) */
    int32_t dr_norm_max;
    /*!< min value for normalizing dynamic range factor (0.4.11) */
    int32_t dr_norm_min;
    /*!< convergence speed [sec] in slow state (0.2.13), 1.0 [sec] x 2^13 = 8192 */
    int32_t convergence_speed_slow;
    /*!< sigma for convergence state transition (0.0.15), 0.15 x 2^15 = 4915 */
    int32_t convergence_sigma;
    /*!< LTM gain extraction mode, 0 - gainext_max, 1 - gainext_logavg, in the future there is possibility to add new mode */
    int32_t gainext_mode;
    /*!< WDR level LTM_noit increase ratio (0.2.13), 1.5x by default */
    int32_t wdr_scale_max;
    /*!< WDR level LTM_noit decrease ratio (0.2.13), 1/8x by default */
    int32_t wdr_scale_min;
    /*!< WDR level ldr_scale increase ratio (0.2.13), 2x by default */
    int32_t wdr_gain_max;
    /*!< frame delay compensation mode, 0 - disable, 1 - enable a frame delay compensation */
    int32_t frame_delay_compensation;
} optibright_tuning_t;

/*!
* \brief MPGC tuning data
*/
typedef struct
{
    /*!< local motion stability (0.0.15): higher value result in more filtering between frames but it has more delay, and vice versa. */
    int32_t lm_stability;
    /*!< local motion sensitivity (0.0.15): higher value detect more local motion but it may increase false detection rate, and vice versa. */
    int32_t lm_sensitivity;
    /*!< filter size for gain blur: 0 - 1x1 (turn off), 1 - 3x3, 2 - 5x5, 3 - 7x7, 4 - 9x9, 5 - 11x11, 6 - 13x13 */
    int32_t blur_size;
    /*!< tf strength (0.0.15): high value - more filter, low value - less filter, 0 - turn off */
    int32_t tf_str;
} mpgc_tuning_t;

/*!
* \brief DRC SW tuning data
*/
typedef struct
{
    /*!< sigma for similarity computation in DRC FW block (0.0.15): high value - high sigma, low value - low sigma */
    int32_t blus_sim_sigma;
} drcsw_tuning_t;

/*!
 * \brief Coala tuning data
 */
typedef struct
{
    /*!< shadows_val shadows adjustment slider. Lower - darken. Higher - brightnen. */
    int32_t shadows_val;
    /*!< highlights_val highlights adjustment slider. Lower - darken. Higher - brightnen. */
    int32_t highlights_val;
    /*!< brightness_slope overall brightness adjustment: "late gain" form. This value is the gain */
    int32_t brightness_slope;
    /*!< brightness_sign 0 for darkening. 1 for brightening */
    int32_t brightness_sign;
    /*!< brightness_knee knee point for late gain curve */
    int32_t brightness_knee;
    /*!< brightness_th this value determined from where luma is saturated */
    int32_t brightness_th;
    /*!< contrast_Qa contrast enhancement parameter for highlights\shadows */
    int32_t contrast_Qa;
    /*!< contrast_Qb contrast enhancement parameter for mid tones */
    int32_t contrast_Qb;
    /*!< reg_maxval regularization parameter max values (the larger, the result looks more like prior optimization result) */
    int32_t reg_maxval;
    /*!< reg_minval regularization parameter min values (the larger, the result looks more like prior optimization result) */
    int32_t reg_minval;
    /*!< reg_thval regularization parameter edge threshold value (the larger, the result looks more like prior optimization result) */
    int32_t reg_thval;
    /*!< ub_high_th upper bound of optimization edge high threshold */
    int32_t ub_high_th;
    /*!< ub_low_th upper bound of optimization edge low threshold */
    int32_t ub_low_th;
    /*!< alpha_thetaGain2 theta parameter gain multiplication (for local tone mapping) */
    int32_t alpha_thetaGain2;
    /*!< alpha_thetaGain1 theta parameter gain multiplication (for local tone mapping) */
    int32_t alpha_thetaGain1;
    /*!< alpha_thetaBias theta parameter bias factor (for local tone mapping) */
    int32_t alpha_thetaBias;
} coala_tuning_t;

/*!
* \brief Clahe tuning data
*/
typedef struct
{
    /*!< Clipping limit for the histogram [0,1]. Higher value increases overall contrast */
    float clip_limit;

    /*!< Maximum slope for the final curves [0,Inf]
     * - Higher limit may allow better brightness in dark regions, but may also create artifacts */
    float max_slope;

    /*!< Min/Max values for the shadow pivot point [0,1]
     * - Controls the contrast in shadows */
    float shadow_min;
    float shadow_max;

    /*!< Min/Max values for the midtone pivot point [0,1]
     * - Controls the contrast in midtones */
    float midtone_min;
    float midtone_max;

    /*!< Min/Max values for the highlight pivot point [0,1]
     * - Controls the contrast highlights */
    float highlight_min;
    float highlight_max;

    /*!< Values at which pivots are calculated [0,1]
     * - Control the brightness in respective tones (higher/lower = brighter/darker) */
    float pivot_shadow;
    float pivot_midtone;
    float pivot_highlight;

    /*!< Defines which input statistics Clahe should use
     * 0: RAW statistics, 1: rgbs statistics */
    uint32_t input_statistics;
} clahe_tuning_t;
/*!
 * \brief tuning data for LTM
 */
typedef struct
{
    ia_ltm_algo_t algo_mode;                 /*!< LTM algo: 0 - OptiBright, 1 - COALA, 2 - CLAHE */
    uint32_t grid_density;                   /*!< LTM grid density. An abstract tuning parameter where minimum value (1) means maximum PnP and maximum value (5) means maximum IQ. Not supported yet.*/
    optibright_tuning_t optibright_tuning;   /*!< OptiBright tuning data */
    coala_tuning_t coala_tuning;             /*!< Coala tuning data, not supported yet.*/
    clahe_tuning_t clahe_tuning;             /*!< Clahe tuning data not supported yet.*/
    mpgc_tuning_t mpgc_tuning;               /*!< MPGC tuning data */
    drcsw_tuning_t drcsw_tuning;             /*!< DRC SW tuning data */
} ltm_tuning_data;

#endif /* _CAMERA_ALGO_TUNING_H_ */

