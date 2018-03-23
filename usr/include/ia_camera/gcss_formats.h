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

#ifndef __GCSS_FORMATS_H__
#define __GCSS_FORMATS_H__

#include <ia_tools/css_types.h>
#include <ia_cipf/ia_cipf_types.h>
#include <map>
#include <vector>
#include <string>

namespace GCSSFormats {

struct ia_format_plane_t {
    std::string name;
    int32_t bpp;
};
typedef std::vector<ia_format_plane_t> planes_vector_t;

/**
 * Container for common format data. Last member is reserved for user to
 * add own identifier for the format.
 */
struct ia_format_t {
    std::string      name;        /**< format name                            */
    uint32_t         fourcc;      /**< int representation of the format       */
    std::string      type;        /**< format type (BAYER, YUV)               */
    int32_t          bpp;         /**< bits per pixel                         */
    int32_t          precision;   /**< meaningful bits per element            */
    int32_t          bpe;         /**< bits per element                       */
    int32_t          vector_size; /**< 0 if data is not vectorized            */
    bool             packed;      /**< packed yes =1, no =0                   */
    planes_vector_t  planes;      /**< vector to contain planes if available  */
    int32_t          fw_id;       /**< maps the format with fw formats enum   */
    uint32_t         os_id;       /**< Reserved for user defined id. This is to
                                       associate os defined formats with the
                                       common, xos formats */
};

typedef std::vector<ia_format_t> formats_vector_t;


/**
 * Parses given formats xml and populates g_formats.
 *
 * \param[in] formatsXML, path to the xml file
 * \return css_err_none at success
 */
css_err_t initGCSSFormats();

/**
 * Get format by id

 * \param[in] id
 * \param[out] format
 * \return css_err_none at success
 */
css_err_t getFormatById(uint32_t id, ia_format_t &format);

/**
 * Get format by name

 * \param[in] name
 * \param[out] format
 * \return css_err_none at success
 */
css_err_t getFormatByName(const std::string &name, ia_format_t &format);

/**
* Get format by fourcc

* \param[in] fourcc
* \param[out] format
* \return css_err_none at success
*/
css_err_t getFormatByFourcc(uint32_t fourcc, ia_format_t &format);

/**
* Get plane count by fourcc

* \param[in] fourcc
* \return plane count
*/
int32_t getPlaneCountByFourcc(uint32_t fourcc);

/**
 * set user defined id for format
 *
 * Searches vector of formats by name and sets id. The id is used to associate
 * os defined formats with the formats provided by xos.
 *
 * \param[in] name,     Name of the format to which to set the id
 * \param[in] id,       the user defined id
 */
css_err_t setFormatId(const std::string &name, uint32_t id);

/**
 * Calculate bytes per line(bpl) for a given format
 *
 * \param[in] format
 * \param[in] width, in pixels
 * \return bpl bytes per line
 */
uint32_t getBpl(const ia_format_t &format, uint32_t width);

/**
* Calculate buffer size for format
*
* \param[in] gcssFormat Format of the frame for which the size is to be calculated
* \param[in] width In pixels
* \param[in] height In pixels
* \param[in] bpl Calculated based on format and width, if not given by caller
* \param[out] tsOffsets (Optional) A caller-provided array of size MAX_TS_OFFSETS, for outputting TS offsets (For compressed frames.)
* \param[out] tsSizes (Optional) A caller-provided array of size MAX_TS_OFFSETS, for outputting TS sizes (For compressed frames.)
* \return buffer size
*/
uint32_t calculateBufferSize(
    const ia_format_t &gcssFormat,
    uint32_t width,
    uint32_t height,
    uint32_t bpl = 0,
    unsigned int tsOffsets[] = NULL,
    unsigned int tsSizes[] = NULL);
} // namespace
#endif
