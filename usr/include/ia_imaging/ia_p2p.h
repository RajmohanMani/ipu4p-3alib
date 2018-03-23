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

#ifndef IA_P2P_H_
#define IA_P2P_H_

#include "ia_css_terminal_types.h"
#include "ia_css_terminal.h"
#include "ia_css_kernel_bitmap.h"
#include "ia_p2p_types.h"

#ifdef IA_P2P_ENABLE_DEBUG_SUPPORT
#include "ia_p2p_private.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  Initializes IA_P2P module for the given platform.
 *
 *  \param [in] platform The platform for which to initialize P2P.
 *
 *  \return The IA_P2P instance handle, or NULL if errors.
 */
ia_p2p_handle ia_p2p_init(ia_p2p_platform_t platform);

/*!
 *  De-initializes IA_P2P module.
 *
 *  \param [in] ia_p2p IA_P2P instance handle.
 */
void ia_p2p_deinit(ia_p2p_handle ia_p2p);

/*!
 *  Returns the required size for the cache buffer.
 *
 *  \param [in] ia_p2p IA_P2P instance handle.
 */
uint32_t ia_p2p_get_cache_buffer_size(ia_p2p_handle ia_p2p);

/*!
 *  Parses the public data ready to be used for encoding.
 *
 *  \param [in] ia_p2p          IA_P2P instance handle.
 *  \param [in] public_data     The public data to parse (from PAL output).
 *  \param [in] cache_buffer    A pointer to the cache buffer. The buffer is allocated and managed by the user (query the required size with ia_p2p_get_cache_buffer_size()).
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 *          ia_err_data, if public_data doesn't contain enough data.
 */
ia_err ia_p2p_parse(
    ia_p2p_handle ia_p2p,
    const ia_binary_data* public_data,
    void* cache_buffer);

/*!
 *  Serializes the statistics to a single binary blob.
 *
 *  \param [in]  ia_p2p     IA_P2P instance handle.
 *  \param [out] statistics The resulting statistics data.
 *  \param [out] included   Flags which indicate what statistics are included in the data.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 *
 *  \remarks The returned data buffer is owned by P2P and is valid as long as any P2P decode functions are not called.
 */
ia_err ia_p2p_serialize_statistics(
    ia_p2p_handle ia_p2p,
    ia_binary_data* statistics,
    ia_p2p_statistics_included_t* included);

/*!
 *  Generates a kernel bitmap for the requested program group.
 *
 *  \param [in] ia_p2p  IA_P2P instance handle.
 *  \param [in] pg_id   The program group id.
 *
 *  \return The kernel bitmap where set bit means that the kernel is an imaging kernel and should be encoded by P2P.
 */
ia_css_kernel_bitmap_t ia_p2p_get_kernel_bitmap(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id);

/*!
*  Generates a kernel bitmap for enabled kernels of the requested program group.
*
*  \param [in] ia_p2p  IA_P2P instance handle.
*  \param [in] pg_id   The program group id.
*
*  \return The kernel bitmap where set bit means that the kernel is enabled and should be encoded by P2P.
*/
ia_css_kernel_bitmap_t ia_p2p_get_kernel_enable_bitmap(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id);

/*!
*  Generates a kernel bitmap for disabled kernels of the requested program group.
*
*  \param [in] ia_p2p  IA_P2P instance handle.
*  \param [in] pg_id   The program group id.
*
*  \return The kernel bitmap where set bit means that the kernel need to be disabled for the PG.
*/
ia_css_kernel_bitmap_t ia_p2p_get_kernel_disable_bitmap(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id);

/*!
 * Check if the kernel bitmaps is empty.
 *
 * \param [in] bitmap Kernel bitmap.
 *
 * \return bitmap == 0.
 */
bool ia_p2p_is_kernel_bitmap_empty(ia_css_kernel_bitmap_t bitmap);

/*!
 *  Calculates proper fragments for ISL.
 *
 *  \param [in]   ia_p2p                                     IA_P2P instance handle.
 *  \param [in]   fragment_count                             The number of fragments.
 *  \param [out]  input_pixel_fragment_descs                 The resulting array of fragment descriptors, one for each fragment.
 *  \param [out]  input_pixel_fragment_descs_display_pin     The resulting array of output fragment descriptors for Bayer (non-scaled) output.
 *  \param [out]  input_pixel_fragment_descs_main_pin        The resulting array of output fragment descriptors for YUV (scaled) output.
 */
ia_err ia_p2p_calculate_isl_fragments(
    ia_p2p_handle ia_p2p,
    unsigned int fragment_count,
    ia_p2p_fragment_desc* input_pixel_fragment_descs,
    ia_p2p_fragment_desc* output_pixel_fragment_descs_bayer,
    ia_p2p_fragment_desc* output_pixel_fragment_descs_yuv);

/*!
 *  Calculates proper fragments for post-GDC.
 *
 *  \param [in]   ia_p2p                                     IA_P2P instance handle.
 *  \param [in]   fragment_count                             The number of fragments.
 *  \param [out]  input_pixel_fragment_descs                 The resulting array of fragment descriptors, one for each fragment.
 *  \param [out]  input_pixel_fragment_descs_display_pin     The resulting array of output fragment descriptors for display pin, one for each fragment.
 *  \param [out]  input_pixel_fragment_descs_main_pin        The resulting array of output fragment descriptors for main pin, one for each fragment.
 *  \param [out]  input_pixel_fragment_descs_postprocess_pin The resulting array of output fragment descriptors for post-process pin, one for each fragment.
 */
ia_err ia_p2p_calculate_postgdc_fragments(
    ia_p2p_handle ia_p2p,
    unsigned int fragment_count,
    ia_p2p_fragment_desc* input_pixel_fragment_descs,
    ia_p2p_fragment_desc* output_pixel_fragment_descs_display_pin,
    ia_p2p_fragment_desc* output_pixel_fragment_descs_main_pin,
    ia_p2p_fragment_desc* output_pixel_fragment_descs_postprocess_pin);

/*!
 *  Calculates proper fragments for pre-GDC.
 *
 *  \param [in]   ia_p2p                                     IA_P2P instance handle.
 *  \param [in]   fragment_count                             The number of fragments.
 *  \param [in]   frame_width                                Frame width
 *  \param [in]   frame_height                               Frame height
 *  \param [in]   input_bpe                                  Input bits per element because of DMA packing
 *  \param [in]   output_bpe                                 Output bits per element because of DMA packing
 *  \param [out]  input_pixel_fragment_descs                 The resulting array of fragment descriptors, one for each fragment.
 *  \param [out]  output_pixel_fragment_descs                The resulting array of fragment descriptors, one for each fragment.
 */
ia_err ia_p2p_calculate_pregdc_fragments(
    ia_p2p_handle ia_p2p,
    unsigned int fragment_count,
    unsigned int frame_width,
    unsigned int frame_height,
    unsigned int input_bpe,
    unsigned int output_bpe,
    ia_p2p_fragment_desc* input_pixel_fragment_descs,
    ia_p2p_fragment_desc* output_pixel_fragment_descs);

/*!
 *  Calculates proper fragments for a program group.
 *
 *  \param [in]   ia_p2p            IA_P2P instance handle.
 *  \param [in]   pg_id             The program group id.
 *  \param [in]   fragment_count    The number of fragments.
 *  \param [out]  configuration     The resulting fragment configuration.
 */
ia_err ia_p2p_calculate_fragments(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    ia_p2p_fragment_configuration_t* configuration);

/*!
 *  Returns the required slice counts for each fragment for the given kernel.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  kernel_id              The program group specific identifier of the kernel whose payload sizes to calculate.
 *  \param [in]  fragment_count         The number of fragments.
 *  \param [in]  pixel_fragment_descs   An array of fragment descriptors, one for each fragment.
 *  \param [out] slice_counts           The resulting array of slice counts, one for each fragment.
 */
ia_err ia_p2p_get_slice_counts(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    unsigned int* slice_counts);

/*!
 *  Calculates the required number of section descriptors for each terminal type for the given kernel.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  kernel_id              The program group specific identifier of the kernel whose descriptor to calculate.
 *  \param [out] kernel_requirements    The calculated requirements for each terminal for the given kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_get_kernel_terminal_requirements(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    ia_p2p_terminal_requirements_t* kernel_requirements);

/*!
 *  Calculates the total size of payload for each terminal type for the given kernel.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  kernel_id              The program group specific identifier of the kernel whose payload sizes to calculate.
 *  \param [in]  fragment_count         The number of fragments.
 *  \param [in]  pixel_fragment_descs   An array of fragment descriptors, one for each fragment.
 *  \param [out] kernel_payload_desc    The calculated total payload size for each terminal for the given kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_get_kernel_payload_desc(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_p2p_payload_desc* kernel_payload_desc);

/*!
 *  Gets the section count and size of payload for param-in/param-out/program terminal for the given kernel.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  kernel_id              The program group specific identifier of the kernel whose section count and sizes to get.
 *  \param [out] kernel_payload_desc    The section count and size for param-in/param-out/program terminal for the given kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 *          ia_err_data, if the section count is out of boundary.
 */
ia_err ia_p2p_get_kernel_payload_section_desc(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    ia_p2p_payload_section_desc* kernel_payload_desc);

/*!
 *  Encodes data for a single kernel in a parameter terminal.
 *
 *  \param [in]     ia_p2p              IA_P2P instance handle.
 *  \param [in]     pg_id               The program group id.
 *  \param [in]     kernel_id           The program group specific identifier of the kernel to encode.
 *  \param [in,out] terminal            The parameter terminal.
 *  \param [in]     section_index       The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in,out] payload_buffer      A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_base_offset The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_param_in_terminal_encode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    ia_css_param_terminal_t* terminal,
    unsigned int section_index,
    unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Initializes the program terminal sequencer with fragment information.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     fragment_count          The number of fragments.
 *  \param [in]     pixel_fragment_descs    An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                The program terminal.
 */
ia_err ia_p2p_program_terminal_init(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_program_terminal_t* terminal);

/*!
 *  Initializes the program terminal sequencer with fragment information.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     configuration           Fragment configuration calculated with ia_p2p_calculate_fragments().
 *  \param [in,out] terminal                The program terminal.
 */
ia_err ia_p2p_program_terminal_init_v2(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    const ia_p2p_fragment_configuration_t* configuration,
    ia_css_program_terminal_t* terminal);

/*!
 *  Encodes data for a single kernel in a program terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to encode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     pixel_fragment_descs            An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                        The program terminal.
 *  \param [in]     section_index                   The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in]     total_section_count             The total number of sections for one fragment including all kernels.
 *  \param [in,out] payload_buffer                  A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size             The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_base_offset             The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_program_terminal_encode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_program_terminal_t* terminal,
    unsigned int section_index,
    unsigned int total_section_count,
    unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Encodes data for a single kernel in a spatial param input terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to encode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     pixel_fragment_descs            An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                        The spatial param input terminal.
 *  \param [in]     section_index                   The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in,out] payload_buffer                  A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size             The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_base_offset             The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_in_terminal_encode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_spatial_param_terminal_t* terminal,
    unsigned int section_index,
    unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Encodes data for a single kernel in a spatial param output terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to encode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     pixel_fragment_descs            An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                        The spatial param output terminal.
 *  \param [in]     section_index                   The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in]     payload_buffer_size             The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_base_offset             The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_out_terminal_prepare(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_spatial_param_terminal_t* terminal,
    unsigned int section_index,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Decodes spatial parameter data for a single kernel from a spatial param output terminal.
 *
 *  \param [in]     ia_p2p              IA_P2P instance handle.
 *  \param [in]     pg_id               The program group id.
 *  \param [in]     kernel_id           The program group specific identifier of the kernel to decode.
 *  \param [in]     terminal            The spatial param output terminal.
 *  \param [in]     section_index       The index of the first section where the data for this kernel is available in the terminal.
 *  \param [in]     payload_buffer      A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size The total size of the given payload buffer, in bytes.
 *  \param [in,out] cache_buffer        A pointer to the cache buffer for storing the cached outputs.
 *                                      The buffer is allocated and managed by the user (query the required size with ia_p2p_get_cache_buffer_size()).
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_out_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    ia_css_spatial_param_terminal_t* terminal,
    unsigned int section_index,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    void* cache_buffer);

/*!
*  Decodes spatial parameter data for a single kernel from a spatial param output terminal with fragment information.
*
*  \param [in]     ia_p2p               IA_P2P instance handle.
*  \param [in]     pg_id                The program group id.
*  \param [in]     kernel_id            The program group specific identifier of the kernel to decode.
*  \param [in]     fragments_count      To apply offsets to subsequent fragments.
*  \param [in]     pixel_fragment_descs Pixel fragment descriptors that were used when encoding current frame.
*  \param [in]     terminal             The spatial param output terminal.
*  \param [in]     section_index        The index of the first section where the data for this kernel is available in the terminal.
*  \param [in]     payload_buffer       A pointer to the beginning of the payload buffer.
*  \param [in]     payload_buffer_size  The total size of the given payload buffer, in bytes.
*  \param [in,out] cache_buffer         A pointer to the cache buffer for storing the cached outputs.
*                                       The buffer is allocated and managed by the user (query the required size with ia_p2p_get_cache_buffer_size()).
*
*
*  \return ia_err_none, if no errors.
*          ia_err_argument, if the arguments are invalid.
*/
ia_err ia_p2p_spatial_param_out_terminal_decode_v2(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragments_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_spatial_param_terminal_t* terminal,
    unsigned int section_index,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    void* cache_buffer);

/*!
 *  Prepares payload for a single kernel in a parameter output terminal.
 *
 *  \param [in]     ia_p2p              IA_P2P instance handle.
 *  \param [in]     pg_id               The program group id.
 *  \param [in]     kernel_id           The program group specific identifier of the kernel whose descriptors to prepare.
 *  \param [in]     fragment_count      The number of fragments.
 *  \param [in,out] terminal            The param output terminal.
 *  \param [in]     section_index       The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in]     total_section_count The total number of sections for one fragment including all kernels.
 *  \param [in]     payload_buffer_size The total size of the payload buffer, in bytes.
 *  \param [in]     payload_base_offset The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_param_out_terminal_prepare(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    ia_css_param_terminal_t* terminal,
    unsigned int section_index,
    unsigned int total_section_count,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Decodes param out data for a single kernel in a parameter output terminal.
 *
 *  \param [in]     ia_p2p              IA_P2P instance handle.
 *  \param [in]     pg_id               The program group id.
 *  \param [in]     kernel_id           The program group specific identifier of the kernel to decode.
 *  \param [in]     fragment_count      The number of fragments.
 *  \param [in]     terminal            The param output terminal.
 *  \param [in]     section_index       The index of the first section where the data for this kernel is written to the terminal.
 *  \param [in]     total_section_count The total number of sections for one fragment including all kernels.
 *  \param [in]     payload_buffer_size The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_buffer      A pointer to the beginning of the payload buffer.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_param_out_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_css_param_terminal_t* terminal,
    unsigned int section_index,
    unsigned int total_section_count,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size);

/*!
 *  Encodes data for a single kernel in a sliced parameter terminal.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     kernel_id               The program group specific identifier of the kernel to encode.
 *  \param [in]     fragment_count          The number of fragments.
 *  \param [in]     pixel_fragment_descs    An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                The parameter terminal.
 *  \param [in,out] payload_buffer          A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size     The total size of the given payload buffer, in bytes.
 *  \param [in]     payload_base_offset     The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_sliced_param_in_terminal_encode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_sliced_param_terminal_t* terminal,
    unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Prepares payload for a single kernel in a sliced parameter output terminal.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     kernel_id               The program group specific identifier of the kernel whose descriptors to prepare.
 *  \param [in]     fragment_count          The number of fragments.
 *  \param [in]     pixel_fragment_descs    An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                The param output terminal.
 *  \param [in]     payload_buffer_size     The total size of the payload buffer, in bytes.
 *  \param [in]     payload_base_offset     The base offset in the payload buffer for this kernel.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_sliced_param_out_terminal_prepare(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    ia_css_sliced_param_terminal_t* terminal,
    unsigned int payload_buffer_size,
    unsigned int payload_base_offset);

/*!
 *  Decodes param out data for a single kernel in a sliced parameter output terminal.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     kernel_id               The program group specific identifier of the kernel to decode.
 *  \param [in]     fragment_count          The number of fragments.
 *  \param [in]     pixel_fragment_descs    An array of fragment descriptors, one for each fragment.
 *  \param [in]     terminal                The param output terminal.
 *  \param [in]     payload_buffer          A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size     The total size of the given payload buffer, in bytes.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_sliced_param_out_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    const ia_css_sliced_param_terminal_t* terminal,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size);

/*!
 *  Returns the size of kernel user parameters for all the kernels in the given Program Group.
 *  This is used in VP-less environment where some of the parameter calculation is done in P2P
 *  instead of firmware.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  fragment_count         The number of fragments.
 *  \param [out] user_parameter_size    Size of the kernel user parameters in the given PG.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_get_kernel_user_parameter_size(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    unsigned int* user_parameter_size);

/*!
 *  Returns the size of kernel user parameters descriptor and payload size separately for the
 *  parambin generation purpose.
 *
 *  \param [in]  ia_p2p                 IA_P2P instance handle.
 *  \param [in]  pg_id                  The program group id.
 *  \param [in]  fragment_count         The number of fragments.
 *  \param [out] kup_desc_size          Size of the kernel user parameter descriptor for a given PG
 *  \param [out] kup_payload_size       Size of the kernel user parameter payload for a given PG.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_get_kup_desc_and_payload_size(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    unsigned int* kup_desc_size,
    unsigned int* kup_payload_size);

/*!
 *  Initializes the Program Group with kernel specific user parameters.
 *  This is used in VP-less environment where some of the parameter calculation is done in P2P
 *  instead of firmware.
 *
 *  \param [in]     ia_p2p                   IA_P2P instance handle.
 *  \param [in]     pg_id                    The program group id.
 *  \param [in]     fragment_count           The number of fragments.
 *  \param [in]     pixel_fragment_descs     An array of fragment descriptors, one for each fragment.
 *  \param [in,out] user_parameters          A pointer to the beginning of user parameters.
 */
ia_err ia_p2p_get_kernel_user_parameters(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    unsigned char* user_parameters);

/*!
*  Initializes the Program Group with kernel specific user parameters.
*  This is used in VP-less environment where some of the parameter calculation is done in P2P
*  instead of firmware.
*
*  \param [in]     ia_p2p                   IA_P2P instance handle.
*  \param [in]     pg_id                    The program group id.
*  \param [in]     fragment_count           The number of fragments.
*  \param [in]     frag_configuration       Fragment configuration calculated with ia_p2p_calculate_fragments().
*  \param [in,out] user_parameters          A pointer to the beginning of user parameters.
*/
ia_err ia_p2p_get_kernel_user_parameters_v2(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_configuration_t* frag_configuration,
    unsigned char* user_parameters);

/*!
 * \brief Get version.
 * Get version from version header.
 *
 * \return                                  Version string.
 */
const char* ia_p2p_get_version(void);

/*!
*  Decodes kernel user parameters for all kernels in the program group.
*  The result is printout of each parameter.
*
*  \param [in]     ia_p2p                   IA_P2P instance handle.
*  \param [in]     pg_id                    The program group id.
*  \param [in]     kup_descriptor           The kernel user parameter payload layout information.
*  \param [in]     payload_buffer           Kernel user parameter binary.
*/
ia_err ia_p2p_decode_kup(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    const unsigned char* kup_descriptor,
    const unsigned char* payload_buffer);


#ifdef IA_P2P_ENABLE_DEBUG_SUPPORT
/*!
 *  Decodes data for a single kernel in a parameter terminal.
 *
 *  \param [in]     ia_p2p              IA_P2P instance handle.
 *  \param [in]     pg_id               The program group id.
 *  \param [in]     kernel_id           The program group specific identifier of the kernel to encode.
 *  \param [in,out] terminal            The parameter terminal.
 *  \param [in]     section_index       The index of the first section where the data for this kernel is available in the terminal.
 *  \param [in,out] payload_buffer      A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size The total size of the given payload buffer, in bytes.
 *  \param [out]    public_data_out     A structure for the public data output.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_param_in_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    const ia_css_param_terminal_t* terminal,
    unsigned int section_index,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    ia_p2p_public_data_t* public_data_out);

/*!
 *  Encodes data for a single kernel in a program terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to decode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     sequencer_fragment_descs        An array of fragment grid descriptors, one for each fragment. These must be retrieved from the
 *                                                  spatial param terminal via ia_p2p_spatial_param_in_terminal_decode_grid_descriptors().
 *  \param [in,out] terminal                        The program terminal.
 *  \param [in]     section_index                   The index of the first section where the data for this kernel is available in the terminal.
 *  \param [in]     total_section_count             The total number of sections for one fragment including all kernels.
 *  \param [in]     payload_buffer                  A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size             The total size of the given payload buffer, in bytes.
 *  \param [out]    public_data_out                 A structure for the decoded output.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_program_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_css_fragment_grid_desc_t* sequencer_fragment_descs,
    ia_css_program_terminal_t* terminal,
    unsigned int section_index,
    unsigned int total_section_count,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    ia_p2p_public_data_t* public_data_out);

/*!
 *  Decodes fragment grid descriptors for a single kernel from a spatial param input terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to decode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     terminal                        The spatial param input terminal.
 *  \param [in]     public_data_out                 A structure for the decoded output.
 *  \param [out]    sequencer_fragment_descs        The resulting array of fragment grid descriptors.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_in_terminal_decode_grid_descriptors(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    ia_css_spatial_param_terminal_t* terminal,
    ia_p2p_public_data_t* public_data_out,
    ia_css_fragment_grid_desc_t* sequencer_fragment_descs);

/*!
 *  Decodes spatial parameter data for a single kernel from a spatial param input terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to decode.
 *  \param [in]     terminal                        The spatial param input terminal.
 *  \param [in]     section_index                   The index of the first section where the data for this kernel is available in the terminal.
 *  \param [in]     payload_buffer                  A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size             The total size of the given payload buffer, in bytes.
 *  \param [in,out] public_data_out                 A structure for the decoded output.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_in_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    ia_css_spatial_param_terminal_t* terminal,
    unsigned int section_index,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    ia_p2p_public_data_t* public_data_out);

/*!
 *  Decodes fragment grid descriptors for a single kernel from a spatial param output terminal.
 *
 *  \param [in]     ia_p2p                          IA_P2P instance handle.
 *  \param [in]     pg_id                           The program group id.
 *  \param [in]     kernel_id                       The program group specific identifier of the kernel to decode.
 *  \param [in]     fragment_count                  The number of fragments.
 *  \param [in]     terminal                        The spatial param output terminal.
 *  \param [in]     public_data_out                 A structure for the decoded output.
 *  \param [out]    sequencer_fragment_descs        The resulting array of fragment grid descriptors.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_spatial_param_out_terminal_decode_grid_descriptors(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    ia_css_spatial_param_terminal_t* terminal,
    ia_p2p_public_data_t* public_data_out,
    ia_css_fragment_grid_desc_t* sequencer_fragment_descs);

/*!
 *  Decodes data for a single kernel in a sliced parameter terminal.
 *
 *  \param [in]     ia_p2p                  IA_P2P instance handle.
 *  \param [in]     pg_id                   The program group id.
 *  \param [in]     kernel_id               The program group specific identifier of the kernel to encode.
 *  \param [in]     fragment_count          The number of fragments.
 *  \param [in]     pixel_fragment_descs    An array of fragment descriptors, one for each fragment.
 *  \param [in,out] terminal                The parameter terminal.
 *  \param [in,out] payload_buffer          A pointer to the beginning of the payload buffer.
 *  \param [in]     payload_buffer_size     The total size of the given payload buffer, in bytes.
 *  \param [out]    public_data_out         A structure for the public data output.
 *
 *  \return ia_err_none, if no errors.
 *          ia_err_argument, if the arguments are invalid.
 */
ia_err ia_p2p_sliced_param_in_terminal_decode(
    ia_p2p_handle ia_p2p,
    uint32_t pg_id,
    uint32_t kernel_id,
    unsigned int fragment_count,
    const ia_p2p_fragment_desc* pixel_fragment_descs,
    const ia_css_sliced_param_terminal_t* terminal,
    const unsigned char* payload_buffer,
    unsigned int payload_buffer_size,
    ia_p2p_public_data_t* public_data_out);

#endif

#ifdef __cplusplus
}
#endif

#endif /* IA_P2P_H_ */
