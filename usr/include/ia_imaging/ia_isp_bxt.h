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
 * \file ia_isp_bxt.h
 * \brief ia_isp_bxt specific implementation.
 *
 * \mainpage
 * \section main Automatic ISP (AIC) Configuration component for IPU4 (and onwards)
 *
 * AIC is stateless component, which purpose is to
 * - Convert generic results into ISP specific format.
 * - Adapt ISP tunings based on run-time changing parameters.
 * - Convert ISP specific statistics into format that is used by 3A and control other algorithms.
 *
 * AIC consists of following components:
 * - \ref gaic
 * - \ref pal
 *
 * AIC API is defined in ia_isp_bxt.h file.
 *
 * See \ref integration for more detailed information about various integration details.
 *
 * \page aicparts AIC modules
 * \section gaic Generic AIC (GAIC)
 *
 * GAIC implements generic adaptation of tunings (generated with IQ tools) as factor of run-time changing parameters. GAIC uses various interpolation
 * schemes to calculate ISP parameters between distinct tunings.
 *
 * \section pal Parameter Abstraction Layer (PAL)
 *
 * PAL generates ISP parameters to each ISP block based on distinct tuning given to it. Refer to PAL documentation for detailed description for
 * configuration and dependencies of each ISP block.
 *
 * \page integration Integration notes
 * \section AIC output buffer state
 *
 * AIC is stateless but instead state is stored inside output buffer. Naturally, if same output buffer is not given back to AIC in the next iteration
 * AIC will recalculate all ISP parameters, thus maintaining backwards compatibility for systems that don't utilize buffer state.AIC determines if the given buffer
 * is the same by compating if the first 8 bytes of the given buffer are always the same. If AIC client uses the same output buffer all the time, client should
 * invalidate (by clearing the first 8 bytes of the) given AIC output buffer when any resolution (resolution_info or resolution_history) parameters change at any
 * stage of the camera operation. Such changes include for example change in digital zoom, scaling and cropping.
 *
 * \section ispdg Digital gain in ISP
 *
 * Applying DG in ISP is preferable over sensor digital gain in certain cases:
 * - ISP may have higher bit depth in the image and retain information that would be lost, if digital gain operation would be done in the sensor.
 * - ISP can apply gains after statistics calculation. This allows 3A algorithms to operate on statistics, which would be saturated by digital gain.
 *   - Sometimes this is the only way to gain image data further, if higher that maximum WB gains that ISP block supports are required.
 *
 * There are three ways to implement digital gain operation in a running system (using input parameters for ia_isp_bxt_run function).
 * AIC client should make decision how to apply digital gain before and after statistics (or partially both):
 * 1. Apply digital gain in WB gains.
 *  - Digital gain operation is applied in ISP after statistic collection (preferred)
 *  - Applying digital gain after statistics collection reduces saturation of image before statistics calculation giving 3A+ algorithms best possible statistics input.
 *  - This can be done only if all digital gain can be applied by WB ISP block.
 *  - Route AEC digital gain to ia_aiq_pa_run() in ia_aiq_pa_input_params->color_gains. Further route ia_aiq_pa_results to AIC.
 * 2. Apply digital gain in manual_digital_gain.
 *  - This is simple from integration point of view.
 *  - Digital gain operation is applied before statistics collection (may saturate some image data in early phase of image processing).
 *  - Route AEC digital gain directly to manual_digital_gain parameter.
 * 3. Apply digital gain partially in WB gains and partially in manual_digital_gain.
 *  - Should be considered only if digital gain exceeds maximum gain supported by WB ISP block (see option 1).
 *  - Most difficult to integrate. Consider using this option, if image quality is not sufficient by using option 2.
 *  - Each ia_aiq_pa_results->color_gains gain is compared against maximum supported gain in the WB ISP block.
 *  - If all gains are below maximum supported gain, apply all gains in color_gains.
 *   - Example:
 *    - Maximum supported gain in WB ISP block is 15.9.
 *    - AEC requests digital gain on 4.0 -> apply digital gain to all color channels as color_gains in ia_aiq_pa_run() input parameters.
 *    - WB gains for all color channels after ia_aiq_pa_run() (including white point gains from AWB results) are all below 15.9
 *     -> pass ia_aiq_pa_results to AIC as they are.
 *  - If some of the gains are above maximum supported gain, extract smallest amount of common gains from all color channels and set that in manual_digital_gain.
 *   - Note for integration: When giving statistics to AIQ, modified ia_aiq_pa_results (where common gain was removed) should be given along with the statistics.
 *     Also manual_digital_gain should be given in ia_aiq_ae_results, which indicates how much digital gain was applied in the statistics.
 *   - Example:
 *    - Maximum supported gain in WB ISP block is 15.9.
 *    - AEC requests digital gain on 18.0 -> apply digital gain to all color channels as color_gains in ia_aiq_pa_run() input parameters.
 *    - Some color channels' WB gains after ia_aiq_pa_run() (including white point gains from AWB results) are all above 15.9
 *     -> modify WB gains so that common for all color channels gain is removed from ia_aiq_pa_results->color_gains and given as manual_digital_gain to AIC.
 *
 * \section performance Power & Perfomance optimizations
 *
 * \subsection state AIC output buffer state
 *
 * AIC being stateless component, won't retain anything in history of previous iterations. However, if AIC output buffer is given to AIC (to fill) by the client,
 * AIC stores state of ISP parameters in that buffer. Then in the next iteration, if same AIC output buffer (with same exact list of run_kernels) is given back to AIC,
 * it can decide to execute or skip calculation of new ISP parameters.
 *
 * \subsection tunablerunrate Tunable run rate of ISP algorithms
 *
 * Calculation of some ISP configuration parameters can be heavy and in some cases it is not needed to run some algorithms at every ia_isp_bxt_run iteration.
 * AIC supports variable run rate of ISP algorithms via tuning record, which contains list of ISP block UUIDs and their corresponding execution rate in microseconds.
 * AIC needs to get correct timestamp in microseconds as input. This timestamp is stored into the AIC output buffer. If same buffer is given back to AIC in the
 * next iteration, AIC detects it, compares newly given timestamp against the timestamp of the previous run and decides if calculation of certain ISP parameters
 * need to be done.
 *
*/

#ifndef IA_ISP_BXT_H_
#define IA_ISP_BXT_H_

#include "ia_aiq_types.h"
#include "ia_types.h"
#include "ia_isp_bxt_types.h"
#include "ia_isp_bxt_statistics_types.h"
#include "ia_isp_types.h"
#include "ia_dvs_types.h"
#include "ia_ltm_types.h"
#include "ia_mkn_types.h"
#include "ia_view_types.h"
#include "ia_ob.h"
#include "ia_isp_bxt_deprecated.h"
#include "ia_bcomp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Initialize IA_ISP and its submodules.
 * This function must be called before any other function in the library. It allocates memories and parses ISP specific parts from CPFF.
 * Initialization returns a handle to the ISP instance, which is given as input parameter for all the
 * ISP functions.
 *
 * \param[in]     aiqb_data          Mandatory although function will not return error, if it not given.\n
 *                                   Reads generic AIC records Block from CPFF.
 * \param[in]     ia_cmc             Mandatory. Parsed camera module characterization structure. IA_ISP will use structures behind given pointer.
 *                                   Structure must be valid throughout whole lifetime of IA_ISP component.
 * \param[in]     max_stats_width    Mandatory. Maximum width of RGBS and AF statistics grids from ISP. Used to calculate size of
 *                                   memory buffers for the IA_AIQ algorithms. The same maximum width will be used for all RGBS
 *                                   and AF statistics grid allocations.
 * \param[in]     max_stats_height   Mandatory. Maximum height of RGBS and AF statistics grids from ISP. Used to calculate size of
 *                                   memory buffers for the IA_AIQ algorithms. The same maximum height will be used for all RGBS
 *                                   and AF statistics grid allocations.l
 *                                   Initialization parameters for statistics conversion.
 * \param[in]     max_num_stats_in   Mandatory. The maximum number of input statistics for one frame. Each statistics is related to different exposure.
 *                                   Used especially for sensors that support two or more simultaneous exposures (HDR).
 */

LIBEXPORT ia_isp_bxt*
ia_isp_bxt_init(
    const ia_binary_data *aiqb_data,
    const ia_cmc_t *ia_cmc,
    unsigned int max_stats_width,
    unsigned int max_stats_height,
    unsigned int max_num_stats_in,
    ia_mkn *ia_mkn);

LIBEXPORT void
ia_isp_bxt_deinit(ia_isp_bxt *ia_isp_bxt);

/*!
 *  \brief IA_ISP_BXT parameter input structure.
 */
typedef struct
{
    ia_aiq_frame_params *sensor_frame_params;        /*!< Mandatory. Sensor frame parameters. Describe frame scaling/cropping done in sensor. */
    ia_aiq_awb_results *awb_results;                 /*!< Mandatory. WB results which are to be used to calculate next ISP parameters (WB gains, color matrix,etc). */
    ia_aiq_gbce_results *gbce_results;               /*!< Mandatory. GBCE Gamma tables which are to be used to calculate next ISP parameters.*/
    ia_aiq_ae_results *ae_results;                   /*!< Mandatory. Exposure results which are to be used to calculate next ISP parameters.
                                                                     Currently only exposure times, analog and digital gains are used. For convenience reasons AIC takes
                                                                     ae results and not only needed parameters. */
    ia_aiq_pa_results *pa_results;                   /*!< Mandatory. Parameter adaptor results from AIQ. */
    ia_aiq_sa_results *sa_results;                   /*!< Mandatory. Shading adaptor results from AIQ. */
    ia_aiq_hist_weight_grid *weight_grid;            /*!< Mandatory. Weight map to be used in the next frame histogram calculation. */
    ia_isp_bxt_program_group *program_group;         /*!< Mandatory. List of kernels associated with this program group */
    unsigned int stream_id;                          /*!< Optional. If program_group is not given, stream_id is used to fetch all the tunings for all the kernels
                                                                    associated with the stream_id. */
    ia_isp_feature_setting nr_setting;               /*!< Mandatory. Feature setting for noise reduction algorithms. */
    ia_isp_feature_setting ee_setting;               /*!< Mandatory. Feature setting for edge enhancement algorithms. */
    char manual_brightness;                          /*!< Optional. Manual brightness value range [-128,127]. Value 0 means no change. */
    char manual_contrast;                            /*!< Optional. Manual contrast value range [-128,127]. Value 0 means no change. */
    char manual_hue;                                 /*!< Optional. Manual hue value range [-128,127]. Value 0 means no change.
                                                                    Value -96 means red become blue, green become red, blue become green */
    char manual_saturation;                          /*!< Optional. Manual saturation value range [-128,127]. Value 0 means no change. */
    ia_isp_effect effects;                           /*!< Optional. Manual setting for special effects. Combination of ia_isp_effect enums.*/
    ia_dvs_morph_table *dvs_morph_table;             /*!< Mandatory. DVS results which are passed to GDC ISP FW. If null is given, PAL produces default
                                                                     morphing table in PAL results. PAL will add scaling to the grid if defined in resolution info.*/
    ia_isp_custom_controls* custom_controls;         /*!< Optional. Custom control parameter for interpolating between different tunings.
                                                                    If custom controls are not used, pointer can be set as null.*/
    ia_binary_data* pal_override;                    /*!< Optional. Set of parameters for overriding tunings from CPF. Parameters need to follow
                                                                    Algo API binary format. Binary may contain multiple parameter sets.
                                                                    Can be set as null if PAL override functionality is not used. */
    ia_ltm_results *ltm_results;                     /*!< Mandatory. Local tone mapping results from LTM. */
    ia_ltm_drc_params *ltm_drc_params;               /*!< Mandatory. DRC parameters from LTM. */
    float manual_digital_gain;                       /*!< Optional. Additional digital gain that is applied to all color channels of the image before ISP statistics collection.
                                                                    Values less than 1.0 means no additional gain. */
    ia_ob_output ob_black_level;                     /*!< Optional. Black level values calculated on-the-fly when the sensor supports. */
    unsigned long long timestamp;                    /*!< Mandatory. Current timestamp (is microseconds) when ia_isp_bxt_run function is called. AIC uses timestamp to decide what
                                                                     calculations are done based on tunable run rate for each ISP configuration algorithm. */
    ia_dvs_image_transformation *gdc_transformation; /*!< Mandatory. Image transformation parameters for GDC5 ISP FW. This feature replaces the need for morph_table usage.*/
    ia_isp_bxt_view_params_t const *view_params;     /*!< Optional. View parameters for running in GDC5 mode.*/
    ia_media_format media_format;                    /*!< Mandatory. Selected Digital television output format.(e.g. BT709) */
    ia_bcomp_results const *bcomp_results;           /*!< Optional.  bit-compression curves. */
} ia_isp_bxt_input_params;

/*!
 * \brief ISP configuration for the next frame
 * Computes ISP parameters from input parameters and CPF values for the next image.
 *
 * \param[in] ia_isp_bxt                    Mandatory. ISP instance handle.
 * \param[in] input_params                  Mandatory. Input parameters for ISP calculations.
 * \param[in] output_data                   Mandatory. Output data structure. If output_data->data pointer is given, AIC writes the results to given buffer.
 *                                                     Output is PAL output following ISP API format.
 * \return                                  Error code.
 *
 */
LIBEXPORT ia_err
ia_isp_bxt_run(
    ia_isp_bxt *ia_isp_bxt,
    const ia_isp_bxt_input_params *input_params,
    ia_binary_data *output_data);

/*!
 * \brief Get version.
 * Get version from version header.
 *
 * \return                         Version string.
 */
LIBEXPORT const char*
ia_isp_bxt_get_version(void);

/*!
 * \brief Calculates ISP parameters output buffer size for given program group.
 * This function can be used by AIC client to query the size of AIC output buffer for particular program group. Client should allocate the memory and
 * pass the size and data it to ia_isp_bxt_run() function in the output_data structure.
 *
 * \param[in] program_group        Optional. List of kernels associated with this program group. If NULL, AIC calculates output size of all ISP blocks.
 * \return                         Size of memory to allocate in order to fit the
 */
LIBEXPORT int
ia_isp_bxt_get_output_size(ia_isp_bxt_program_group *program_group);

/*!
 * \brief Gets a pointer of HDR YV statistics inside the given binary statistics buffer.
 * Note! Output hdr_yv_grid always points inside the given statistics buffer.
 * \param[in]  statistics        Mandatory. Statistics in ISP specific format.
 * \param[out] hdr_yv_grid       Mandatory. Pointer's pointer where address of statistics are located. Pointing inside given statistics buffer.
 * \return                       Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_get_hdr_yv_in_binary(
    const ia_binary_data *statistics,
    ia_isp_bxt_hdr_yv_grid_t **hdr_yv_grid);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in] ia_isp_bxt         Mandatory. ia_isp_bxt instance handle.
 * \param[in]  statistics        Mandatory. Statistics in ISP specific format.
 * \param[out] out_query_results Mandatory. A pointer to the query results which indicate which statistics are available.
 * \return                       Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_query(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    ia_isp_bxt_statistics_query_results_t* out_query_results);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in] ia_isp_bxt        Mandatory. ia_isp_bxt instance handle.
 * \param[in]  statistics       Mandatory. Statistics in ISP specific format.
 * \param[in]  ir_weight        Mandatory for RGB-IR sensors, NULL otherwise. IR contamination grid.
 * \param[in]  ae_results       Mandatory for 2DP-SVE sensors for frames captured with >=2 exposures, ignored otherwise. Exposure parameters
                                used in de-stiching of input HDR statistics to num_exposures LDR RGBS grids.
 * \param[out] out_rgbs_grid    Mandatory. Pointer's pointer where address of converted statistics are stored.
 *                              Converted RGBS grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                              if the external buffer is provided in out_rgbs_grid it will be used otherwise internal buffer is used.
 * \param[out] out_ir_grid      Mandatory for RGB-IR sensors, NULL otherwise. Pointer's pointer where address of converted statistics are stored.
 *                              Converted IR grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                              if the external buffer is provided in out_ir_grid it will be used otherwise internal buffer is used.
 * \return                      Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_awb_from_binary_v2(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    const ia_aiq_ir_weight_t *ir_weight,
    const ia_aiq_ae_results *ae_results,
    ia_aiq_rgbs_grid **out_rgbs_grid,
    ia_aiq_grid **out_ir_grid);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in] ia_isp_bxt     Mandatory.\n
 *                           ia_isp_bxt instance handle.
 * \param[in]  stats_width   Mandatory actual width of the statistics grid.
 * \param[in]  stats_height  Mandatory actual height of the statistics grid.
 * \param[in]  c0_avg        Mandatory Average level of c0 color
 * \param[in]  c1_avg        Mandatory Average level of c0 color
 * \param[in]  c2_avg        Mandatory Average level of c0 color
 * \param[in]  c3_avg        Mandatory Average level of c0 color
 * \param[in]  c4_avg        Mandatory Average level of c0 color
 * \param[in]  c5_avg        Mandatory Average level of c0 color
 * \param[in]  c6_avg        Mandatory Average level of c0 color
 * \param[in]  c7_avg        Mandatory Average level of c0 color
 * \param[in]  sat_ratio_0   Mandatory Represents Saturation ratio.
 *                                     0: 0% above saturation
 *                                     255: 100% above saturation
 * \param[in]  sat_ratio_1   Mandatory Represents Saturation ratio.
 *                                     0: 0% above saturation
 *                                     255: 100% above saturation
 * \param[in]  sat_ratio_2   Mandatory Represents Saturation ratio.
 *                                     0: 0% above saturation
 *                                     255: 100% above saturation
 * \param[in]  sat_ratio_3   Mandatory Represents Saturation ratio.
 *                                     0: 0% above saturation
 *                                     255: 100% above saturation
 * \param[in]  ir_weight     Mandatory for RGB-IR sensors, NULL otherwise. IR contamination grid for given frame.
 * \param[in]  ae_results    Mandatory for 2DP-SVE sensors for frames captured with >=2 exposures, ignored otherwise. Exposure parameters
 *                                     used in de-stiching of input HDR statistics to num_exposures LDR RGBS grids.
 *
 * \param[out] out_rgbs_grid Mandatory. Pointer's pointer where address of converted statistics are stored.
 *                           Converted RGBS grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                           if the external buffer is provided in out_rgbs_grid it will be used otherwise internal buffer is used.
 * \param[out] out_ir_grid   Mandatory for RGB-IR sensors, NULL otherwise. Pointer's pointer where address of converted statistics are stored.
 *                           Converted IR grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                           if the external buffer is provided in out_ir_grid it will be used otherwise internal buffer is used.
 *
 * \return                   Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_awb_v2(
                    ia_isp_bxt *ia_isp_bxt,
                    unsigned int stats_width,
                    unsigned int stats_height,
                    void *c0_avg,
                    void *c1_avg,
                    void *c2_avg,
                    void *c3_avg,
                    void *c4_avg,
                    void *c5_avg,
                    void *c6_avg,
                    void *c7_avg,
                    void *sat_ratio_0,
                    void *sat_ratio_1,
                    void *sat_ratio_2,
                    void *sat_ratio_3,
                    const ia_aiq_ir_weight_t *ir_weight,
                    const ia_aiq_ae_results *ae_results,
                    ia_aiq_rgbs_grid **out_rgbs_grid,
                    ia_aiq_grid **out_ir_grid);

/*!
* \brief Converts BXT ISP specific statistics (MSB aligned) to IA_AIQ format.
* ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
* from various ISP formats into AIQ statistics format.
*
* \param[in] ia_isp_bxt                          Mandatory. ia_isp_bxt instance handle.
* \param[in]  statistics                         Mandatory. Statistics in ISP specific format.
* \param[in]  hdr_compression                    Optional. NULL, if HDR statistics are already in linear space (no compression).
* \param[in]  stats_rgbs_hdr_block_pixel_width   Mandatory. TODO: Remove when FW will output saturation percentage instead of saturation count. Width of the block in pixel used in computing the saturation percentage.
* \param[in]  stats_rgbs_hdr_block_pixel_height  Mandatory. TODO: Remove when FW will output saturation percentage instead of saturation count. Height of the block in pixel used in computing the saturation percentage.
* \param[in]  r_gain                             Mandatory. Gain applied to the R color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[in]  g_gain                             Mandatory. Gain applied to the G color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[in]  b_gain                             Mandatory. Gain applied to the B color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[out] out_rgbs_grid                      Mandatory. Pointer's pointer where address of converted statistics are stored.
* \param[out] out_hdr_rgbs_grid                  Optional. Pointer's pointer where address of combined HDR statistics are stored.
*                                                Converted RGBS grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
*                                                if the external buffer is provided in out_rgbs_grid it will be used otherwise internal buffer is used.
* \return                                        Error code.
*/
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_awb_hdr_from_binary_v2(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    const ia_aiq_ae_results *ae_results,
    const ia_isp_bxt_hdr_compression_t *hdr_compression,
    unsigned int stats_rgbs_hdr_block_pixel_width,
    unsigned int stats_rgbs_hdr_block_pixel_height,
    float r_gain,
    float g_gain,
    float b_gain,
    ia_aiq_rgbs_grid **out_rgbs_grid,
    ia_aiq_hdr_rgbs_grid **out_hdr_rgbs_grid);

/*!
* \brief Converts HDR DP RGBS statistics (MSB aligned) to AIQ format.
* ISP/VLIW generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted  into AIQ statistics format.
* \param[in]  ia_isp_bxt                         Mandatory. ia_isp_bxt instance handle.
* \param[in]  stats_width                        Mandatory. Actual width of the statistics grid.
* \param[in]  stats_height                       Mandatory. Actual height of the statistics grid.
* \param[in]  stats_r                            Mandatory.
* \param[in]  stats_b                            Mandatory.
* \param[in]  stats_g                            Mandatory.
* \param[in]  stats_s                            Mandatory.
* \param[in]  hdr_compression                    Optional. NULL, if HDR statistics are already in linear space (no compression).
* \param[in]  stats_rgbs_hdr_block_pixel_width   Mandatory. TODO: Remove when FW will output saturation percentage instead of saturation count. Width of the block in pixel used in computing the saturation percentage.
* \param[in]  stats_rgbs_hdr_block_pixel_height  Mandatory. TODO: Remove when FW will output saturation percentage instead of saturation count. Height of the block in pixel used in computing the saturation percentage.
* \param[in]  r_gain                             Mandatory. Gain applied to the R color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[in]  g_gain                             Mandatory. Gain applied to the G color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[in]  b_gain                             Mandatory. Gain applied to the B color channel before HDR statistic collection. Gain will be reverted from HDR statistics.
* \param[out] out_rgbs_grid                      Mandatory. Pointer's pointer where address of de-stitched statistics array is stored.
* \param[out] out_hdr_rgbs_grid                  Optional. Pointer's pointer where address of combined HDR statistics is stored.
*                                                Converted RGBS grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
*                                                if the external buffer is provided in out_rgbs_grid it will be used otherwise internal buffer is used.
* \return                                        Error code.
*/
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_awb_hdr_v2(
    ia_isp_bxt *ia_isp_bxt_ptr,
    unsigned int stats_width,
    unsigned int stats_height,
    void *stats_r,
    void *stats_g,
    void *stats_b,
    void *stats_s,
    const ia_aiq_ae_results *ae_results,
    const ia_isp_bxt_hdr_compression_t *hdr_compression,
    unsigned int stats_rgbs_hdr_block_pixel_width,
    unsigned int stats_rgbs_hdr_block_pixel_height,
    float  r_gain,
    float  g_gain,
    float  b_gain,
    ia_aiq_rgbs_grid **out_rgbs_grid,
    ia_aiq_hdr_rgbs_grid **out_hdr_rgbs_grid);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in]  ia_isp_bxt     Mandatory ia_isp_bxt instance handle.
 * \param[in]  statistics     Mandatory. Statistics in ISP specific format.
 *
 * \param[out] out_af_grid    Mandatory. This pointer is returned from the initialize function
 *                            Pointer's pointer where address of converted statistics are stored.
 *                            Converted af grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                            if the external buffer is provided in out_af_grid it will be used otherwise internal buffer is used.
 * \return                    Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_af_from_binary(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    ia_aiq_af_grid **out_af_grid);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in]  ia_isp_bxt    Mandatory. ia_isp_bxt instance handle.
 * \param[in]  stats_width   Mandatory. Actual width of the statistics grid.
 * \param[in]  stats_height  Mandatory. Actual height of the statistics grid.
 * \param[in]  y00_avg       Mandatory. Blocks value of Y00 filter response
 * \param[in]  y01_avg       Mandatory. Blocks value of Y01 filter response
 * \param[in]  y10_avg       Mandatory. Blocks value of Y10 filter response
 * \param[in]  y11_avg       Mandatory. Blocks value of Y11 filter response
 *
 * \param[out] out_af_grid   Mandatory.\n
 *                           Pointer's pointer where address of converted statistics are stored.
 *                           Converted af grid statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                           if the external buffer is provided in out_af_grid it will be used otherwise internal buffer is used.
 * \return                   Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_af(
    ia_isp_bxt *ia_isp_bxt,
    unsigned int stats_width,
    unsigned int stats_height,
    void *y00_avg,
    void *y01_avg,
    void *y10_avg,
    void *y11_avg,
    ia_aiq_af_grid **out_af_grid);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in]  ia_isp_bxt        Mandatory. ia_isp_bxt instance handle.
 * \param[in]  statistics        Mandatory. Statistics in ISP specific format.
 * \param[out] out_aiq_histogram Mandatory. Pointer's pointer where address of converted statistics are stored.
 *                               Converted aiq histogram statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                               if the external buffer is provided in out_aiq_histogram it will be used otherwise internal buffer is used.
 * \return                       Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_ae_from_binary(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    ia_aiq_histogram **out_aiq_histogram);

/*!
 * \brief Converts BXT ISP specific statistics to IA_AIQ format.
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 * \param[in]  ia_isp_bxt        Mandatory. ia_isp_bxt instance handle.
 * \param[in]  c0_histogram      Mandatory. Block value of c0_histogram
 * \param[in]  c1_histogram      Mandatory. Block value of c1_histogram
 * \param[in]  c2_histogram      Mandatory. Block value of c2_histogram
 * \param[in]  c3_histogram      Mandatory. Block value of c3_histogram
 * \param[in]  num_bins          Mandatory. Number of histogram bins in ISP generated histograms.
 * \param[out] out_aiq_histogram Mandatory. Pointer's pointer where address of converted statistics are stored.
 *                               Converted aiq histogram statistics. Output can be directly used as input in function ia_aiq_statistics_set.
 *                               if the external buffer is provided in out_aiq_histogram it will be used otherwise internal buffer is used.
 * \return                       Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_ae(
    ia_isp_bxt *ia_isp_bxt,
    void *c0_histogram,
    void *c1_histogram,
    void *c2_histogram,
    void *c3_histogram,
    unsigned int num_bins,
    ia_aiq_histogram **out_aiq_histogram);

/*!
 * \brief This function converts corner based statistics to generic DVS statistics.
 *
 * ISP generated statistics may not be in the format in which AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into AIQ statistics format.
 *
 * \param[in]  ia_isp_bxt                  Mandatory. ia_isp_bxt instance handle.
 * \param[in]  statistics                  Mandatory. Statistics in ISP specific format.
 * \param[in]  dvs_statistics_input_width  Mandatory. DVS statistics input width. Used only in DVS statistics conversion.
 * \param[in]  dvs_statistics_input_height Mandatory. DVS statistics input height. Used only in DVS statistics conversion.
 * \param[out] dvs_statistics              Mandatory. Pointer's pointer where address of converted statistics are stored.
 *                                         Converted DVS statistics. Output can be directly used as input in function ia_dvs_set_statistics.
 *                                         If the external buffer is provided in dvs_statistics it will be used otherwise internal buffer is used.
 * \return                                 Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_dvs_from_binary(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *statistics,
    unsigned int dvs_statistics_input_width,
    unsigned int dvs_statistics_input_height,
    ia_dvs_statistics **dvs_statistics);

/*!
 * \brief This function converts corner based statistics to generic DVS statistics.
 *
 * ISP generated statistics may not be in the format in which DVS algorithms expect. Statistics need to be converted
 * from various ISP formats into DVS statistics format.
 *
 * \param[in]  ia_isp_bxt                  Mandatory. ia_isp_bxt instance handle.
 * \param[in]  bxt_dvs_statistics          Mandatory. Binary data which contains pointer to BXT specific DVS statistics structure.
 * \param[in]  dvs_statistics_input_width  Mandatory. DVS statistics input width. Used only in DVS statistics conversion.
 * \param[in]  dvs_statistics_input_height Mandatory. DVS statistics input height. Used only in DVS statistics conversion.
 * \param[out] dvs_statistics              Mandatory. Converted DVS statistics. Output can be directly used as input in function ia_dvs_set_statistics.
 *                                         If the external buffer is provided in dvs_statistics it will be used otherwise internal buffer is used.
 * \return                                 Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_statistics_convert_dvs(
    ia_isp_bxt *ia_isp_bxt,
    const ia_binary_data *bxt_dvs_statistics,
    unsigned int dvs_statistics_input_width,
    unsigned int dvs_statistics_input_height,
    ia_dvs_statistics **dvs_statistics);

/*!
 * \brief Read parameters, interpolated by GAIC, of requested ISP block.
 * This function queries currently effective Algorithm API parameters, which are interpolated by GAIC, of a target ISP block.
 *
 * \param [in]  ia_isp_bxt         Mandatory.  ia_isp_bxt instance handle.
 * \param [in]  target_id          Mandatory.  uuid of queried ISP block.
 * \param [out] target_data_ptr    Mandatory.  a pointer of a pointer to data buffer that will have read parameters.
 * \param [out] output_size_ptr    Mandatory.  a size of all parameters. 0 if a target record does not exist.
 *
 * \return                         Error code.
 */
LIBEXPORT ia_err
ia_isp_bxt_get_interpolated_parameters(
    const ia_isp_bxt *ia_isp_bxt_ptr,
    const unsigned int target_id,
    char **target_data_ptr,
    size_t *output_size_ptr);

/*!
 * \brief Converts BXT ISP PAF statistics to IA_AIQ format.
 *
 * ISP generated statistics may not be in the format in which IA_AIQ algorithms expect. Statistics need to be converted
 * from various ISP formats into IA_AIQ statistics format.
 *
 * \param[in]  ia_isp_bxt                  Mandatory. ia_isp_bxt instance handle.
 * \param[in]  paf_data                    Mandatory. PAF data handle.
 * \param[in]  bxt_paf_statistics          Mandatory. Binary data which contains pointer to BXT specific PAF statistics structure.
 * \param[in]  paf_statistics_input_width  Mandatory. PAF statistics input width.
 * \param[in]  paf_statistics_input_height Mandatory. PAF statistics input height.
 * \param[out] depth_statistics            Mandatory. Converted PAF statistics. Output can be directly used as input in function ia_statistics_set.
 * \return                                 Error code.
 */
ia_err ia_isp_bxt_statistics_convert_paf_from_binary(
        ia_isp_bxt *ia_isp_bxt,
        const ia_binary_data *bxt_paf_statistics,
        unsigned int paf_statistics_input_width,
        unsigned int paf_statistics_input_height,
        ia_aiq_depth_grid **depth_statistics);

#ifdef __cplusplus
}
#endif
#endif /* IA_ISP_BXT_H_ */
