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

#ifndef _IA_CIPF_TYPES_H_
#define _IA_CIPF_TYPES_H_

#include <ia_tools/ia_list.h>
#include <ia_tools/css_types.h>

/** \file ia_cipf_types.h
 *
 * Definitions for datatypes used with public CIPF interfaces
 *
 * \ingroup ia_cipf
 *
 * Includes opaque CIPF objects and types for data management
 */

/**
 * \ingroup ia_cipf
 */
typedef struct _cipf_terminal ia_cipf_terminal_t;

/**
 * \ingroup ia_cipf
 */
typedef struct _cipf_container ia_cipf_container_t;

/**
 * \ingroup ia_cipf
 */
typedef struct _cipf_connection ia_cipf_connection_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_registry ia_cipf_registry_t;

/**
 * \ingroup ia_cipf
 */
typedef struct _cipf_property ia_cipf_property_t;

/**
 * \ingroup ia_cipf
 */
typedef struct _cipf_stage ia_cipf_stage_t;

/**
 * \ingroup ia_cipf
 */
typedef css_err_t (*ia_cipf_stage_completion_op_t)(ia_cipf_stage_t*, void *priv);

/** ia_cipf_iterator_t - context of single pipeline iteration
 *
 * \ingroup ia_cipf
 *
 * Iterator object holds accessors (<stage, container>-pairs called parcels)
 * for pipeline components associated with single execution step. Amount of
 * stages and terminals within single execution step may vary based on
 * DAG definition.
 */
typedef struct ia_cipf_iterator ia_cipf_iterator_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_pipe ia_cipf_pipe_t;

/**
 * \ingroup ia_cipf
 */
typedef uint32_t ia_uid;

/**
 * \ingroup ia_cipf
 */
#define ia_fourcc(a, b, c, d) ((uint32_t)(d) | ((uint32_t)(c) << 8) \
                              | ((uint32_t)(b) << 16) | ((uint32_t)(a) << 24))

typedef struct log_context log_context_t;

/*
 * \todo Add documentation where do the format definitions come from
 * and/or how are they defined.
 */

/* Native UID definitions for fourcc pixel formats */
#define ia_cipf_frame_fourcc_i420 ia_fourcc('V','4','2','0')
#define ia_cipf_frame_fourcc_iyuv ia_fourcc('I','Y','U','V') /* YUV420 planar */
#define ia_cipf_frame_fourcc_ciyuv ia_fourcc('C','I','Y','U') /* YUV420 planar, compressed */
#define ia_cipf_frame_fourcc_nv12 ia_fourcc('N','V','1','2')
#define ia_cipf_frame_fourcc_cnv12_tnr ia_fourcc('C','T','1','2') /* Compressed planar NV12, for TNR input/output */
#define ia_cipf_frame_fourcc_nv21 ia_fourcc('N','V','2','1')
#define ia_cipf_frame_fourcc_yuy2 ia_fourcc('Y','U','Y','2')
#define ia_cipf_frame_fourcc_ba10 ia_fourcc('B','A','1','0')
#define ia_cipf_frame_fourcc_rg10 ia_fourcc('R','G','1','0')
#define ia_cipf_frame_fourcc_bg10 ia_fourcc('B','G','1','0')
#define ia_cipf_frame_fourcc_gb10 ia_fourcc('G','B','1','0')
#define ia_cipf_frame_fourcc_gr08 ia_fourcc('G','R','0','8')
#define ia_cipf_frame_fourcc_gr10 ia_fourcc('G','R','1','0')
#define ia_cipf_frame_fourcc_grbg ia_fourcc('G','R','B','G')
#define ia_cipf_frame_fourcc_rggb ia_fourcc('R','G','G','B')
#define ia_cipf_frame_fourcc_bggr ia_fourcc('B','G','G','R')
#define ia_cipf_frame_fourcc_gbrg ia_fourcc('G','B','R','G')
#define ia_cipf_frame_fourcc_y800 ia_fourcc('Y','8','0','0')
#define ia_cipf_frame_fourcc_tile ia_fourcc('T','I','L','E') /* NV12 tiled */
#define ia_cipf_frame_fourcc_cile ia_fourcc('C','I','L','E') /* NV12 tiled, compressed */
#define ia_cipf_frame_fourcc_bin8 ia_fourcc('B','I','N','8')
#define ia_cipf_frame_fourcc_uyvy ia_fourcc('U','Y','V','Y')
#define ia_cipf_frame_fourcc_srgb48 ia_fourcc('S','R','4','8')
#define ia_cipf_frame_fourcc_yuv420_16_pl ia_fourcc('S','4','2','0')
#define ia_cipf_frame_fourcc_yuv444_8_pl ia_fourcc('N','A','N','A')
#define ia_cipf_frame_fourcc_yuv420_8_sp_c_tnr ia_fourcc('C','T','1','2')
#define ia_cipf_frame_fourcc_yuv420_16_sp ia_fourcc('P','0','1','6')

/* pdaf bayer formats */
#define ia_cipf_frame_fourcc_pafn ia_fourcc('P','A','F','n')
#define ia_cipf_frame_fourcc_pafi ia_fourcc('P','A','F','i')
#define ia_cipf_frame_fourcc_paf_08 ia_fourcc('P','F','8','n')
#define ia_cipf_frame_fourcc_paf_10 ia_fourcc('P','F','1','n')
#define ia_cipf_frame_fourcc_paf_12 ia_fourcc('P','F','2','n')
#define ia_cipf_frame_fourcc_paf_14 ia_fourcc('P','F','4','n')
#define ia_cipf_frame_fourcc_paf_16 ia_fourcc('P','F','6','n')

#define ia_cipf_frame_fourcc_paf_08i ia_fourcc('P','F','8','i')
#define ia_cipf_frame_fourcc_paf_10i ia_fourcc('P','F','1','i')
#define ia_cipf_frame_fourcc_paf_12i ia_fourcc('P','F','2','i')
#define ia_cipf_frame_fourcc_paf_14i ia_fourcc('P','F','4','i')
#define ia_cipf_frame_fourcc_paf_16i ia_fourcc('P','F','6','i')

#define ia_cipf_frame_fourcc_ba12 ia_fourcc('B','A','1','2')

/* CSS format fourcc codes for export */
#define css_fourcc_raw                  ia_fourcc('C','S','B','A')

/* Vectorized Bayer formats */
#define css_fourcc_bggr_10_v32          ia_fourcc('b','V','0','E')
#define css_fourcc_gbrg_10_v32          ia_fourcc('b','V','0','F')
#define css_fourcc_grbg_10_v32          ia_fourcc('b','V','0','G')
#define css_fourcc_rggb_10_v32          ia_fourcc('b','V','0','H')
#define css_fourcc_bggr_12_v32          ia_fourcc('b','V','0','I')
#define css_fourcc_gbrg_12_v32          ia_fourcc('b','V','0','J')
#define css_fourcc_grbg_12_v32          ia_fourcc('b','V','0','K')
#define css_fourcc_rggb_12_v32          ia_fourcc('b','V','0','L')

/* Not actually raw interleaved format but 12 bit vectorized GRBG bayer. Wrong
 * naming but is still used in HAL.
 ** \todo Remove this definition once there are no more dependencies */
#define css_fourcc_raw_interleaved      css_fourcc_grbg_12_v32

/* Packed vectorized Bayer formats */
#define css_fourcc_bggr_10_v32_p64      ia_fourcc('b','V','0','M')
#define css_fourcc_gbrg_10_v32_p64      ia_fourcc('b','V','0','N')
#define css_fourcc_grbg_10_v32_p64      ia_fourcc('b','V','0','O')
#define css_fourcc_rggb_10_v32_p64      ia_fourcc('b','V','0','P')
#define css_fourcc_bggr_12_v32_p64      ia_fourcc('b','V','0','Q')
#define css_fourcc_gbrg_12_v32_p64      ia_fourcc('b','V','0','R')
#define css_fourcc_grbg_12_v32_p64      ia_fourcc('b','V','0','S')
#define css_fourcc_rggb_12_v32_p64      ia_fourcc('b','V','0','T')

/* Packed Normal Bayer Formats */
#define css_fourcc_bggr_14_p64          ia_fourcc('p','B','E','E')
#define css_fourcc_gbrg_14_p64          ia_fourcc('p','G','E','E')
#define css_fourcc_grbg_14_p64          ia_fourcc('p','g','E','E')
#define css_fourcc_rggb_14_p64          ia_fourcc('p','R','E','E')
#define css_fourcc_bggr_12_p64          ia_fourcc('p','B','C','C')
#define css_fourcc_gbrg_12_p64          ia_fourcc('p','G','C','C')
#define css_fourcc_grbg_12_p64          ia_fourcc('p','g','C','C')
#define css_fourcc_rggb_12_p64          ia_fourcc('p','R','C','C')
#define css_fourcc_bggr_10_p64          ia_fourcc('p','B','A','A')
#define css_fourcc_gbrg_10_p64          ia_fourcc('p','G','A','A')
#define css_fourcc_grbg_10_p64          ia_fourcc('p','g','A','A')
#define css_fourcc_rggb_10_p64          ia_fourcc('p','R','A','A')

/* Line interleaved formats */
#define css_fourcc_bggr_10_li           ia_fourcc('C','S','L','0')
#define css_fourcc_gbrg_10_li           ia_fourcc('C','S','L','1')
#define css_fourcc_grbg_10_li           ia_fourcc('C','S','L','2')
#define css_fourcc_rggb_10_li           ia_fourcc('C','S','L','3')
#define css_fourcc_bggr_12_li           ia_fourcc('C','S','L','4')
#define css_fourcc_gbrg_12_li           ia_fourcc('C','S','L','5')
#define css_fourcc_grbg_12_li           ia_fourcc('C','S','L','6')
#define css_fourcc_rggb_12_li           ia_fourcc('C','S','L','7')

/* Compressed bayer formats */
#define css_fourcc_bggr_8_c             ia_fourcc('B','G','8','C')
#define css_fourcc_gbrg_8_c             ia_fourcc('G','B','8','C')
#define css_fourcc_grbg_8_c             ia_fourcc('G','R','8','C')
#define css_fourcc_rggb_8_c             ia_fourcc('R','G','8','C')
#define css_fourcc_bggr_10_c            ia_fourcc('B','G','1','C')
#define css_fourcc_gbrg_10_c            ia_fourcc('G','B','1','C')
#define css_fourcc_grbg_10_c            ia_fourcc('G','R','1','C')
#define css_fourcc_rggb_10_c            ia_fourcc('R','G','1','C')

/* YUV formats */
#define css_fourcc_internal_yuv_line    ia_fourcc('C','S','Y','C')
#define css_fourcc_yyuv420_v32          ia_fourcc('y','0','3','2')
#define css_fourcc_yyuv420_12_v32_p64   ia_fourcc('y','0','3','6')
#define css_fourcc_yuv420_internal      ia_fourcc('C','S','Y','I') /* denotes all YUVs with bpe 8, for TNR, for example */
#define css_fourcc_yplanar              ia_fourcc('C','S','Y','P')
#define css_fourcc_yuv420_12_p64        ia_fourcc('C','S','4','2')
#define css_fourcc_yuv420_10_p64        ia_fourcc('C','S','4','0')

#define css_fourcc_p010                 ia_fourcc('P','0','1','0')
#define css_fourcc_p010_lsb             ia_fourcc('P','0','1','L')
/* Intel internal format: P010 Tile-Y (MSB) */
#define css_fourcc_p010_msb_tile_y          ia_fourcc('T','0','1','0')
/* Intel internal format: P010 Tile-Y (MSB), compressed*/
#define css_fourcc_p010_msb_cile_y          ia_fourcc('C','0','1','0')

/* Native object type reference UIDs */
#define ia_cipf_pipeline_location_ref_uid   ia_fourcc('P','O','L','R')
#define ia_cipf_platform_buffer_ref_uid     ia_fourcc('P','O','B','R')
#define ia_cipf_platform_buffer_offset_uid  ia_fourcc('P','O','B','O')
#define ia_cipf_platform_memory_ref_uid     ia_fourcc('P','O','M','R')
#define ia_cipf_platform_memory_device_ref_uid ia_fourcc('P','O','M','D')

/* Native type payload UIDs */
#define ia_cipf_payload_uid_int32           ia_fourcc('D','A','$','0')
#define ia_cipf_payload_uid_uint32          ia_fourcc('D','A','$','1')
#define ia_cipf_payload_uid_resolution      ia_fourcc('D','A','$','2')
#define ia_cipf_payload_uid_boolean         ia_fourcc('D','A','$','3')
#define ia_cipf_payload_uid_uint64          ia_fourcc('D','A','$','4')
#define ia_cipf_payload_uid_void_ref        ia_fourcc('D','R','$','0')
#define ia_cipf_payload_uid_int32_ref       ia_fourcc('D','R','$','1')
#define ia_cipf_payload_uid_uint32_ref      ia_fourcc('D','R','$','2')
#define ia_cipf_payload_uid_resolution_ref  ia_fourcc('D','R','$','3')
#define ia_cipf_payload_uid_string_ref      ia_fourcc('D','R','$','4')
#define ia_cipf_payload_uid_uint64_ref      ia_fourcc('D','R','$','5')
#define ia_cipf_payload_uid_offset_ref      ia_fourcc('D','O','$','0')

/* Native payload for special unidentified property */
#define ia_cipf_payload_uid_unidentified    ia_fourcc('U','I','P','R')

/* Native property UIDs */
#define ia_cipf_frame_format_uid ia_fourcc('P','X','F','M')
#define ia_cipf_frame_uid ia_fourcc('F','R','A','M')
#define ia_cipf_fragment_descriptor_uid ia_fourcc('F','R','D','S')
#define ia_cipf_property_data_uid ia_fourcc('D','A','T','A')
#define ia_cipf_tunneled_terminal_data_uid  ia_fourcc('A','U','T','O')

#define IA_CIPF_PAYLOAD_STORAGE_SIZE 8

/** Identifiable data payload type
 *
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_payload {
    ia_uid     uid;  /* data type identifier */
    uint32_t   size; /* size in bytes allocated to data.cpu_ptr */
    union {
        void        *cpu_ptr;
        uint32_t    offset;
        uint32_t    handle;
        uint8_t     raw[IA_CIPF_PAYLOAD_STORAGE_SIZE];
        uint32_t    uvalue;
        uint64_t    u64value;
        int32_t     svalue;
    } data;
} ia_cipf_payload_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_frame_format {
    uint32_t        width;    /**< Width of the frame in pixels */
    uint32_t        height;   /**< Height of the frame in lines */
    uint32_t        fourcc;   /**< Frame format */
    uint32_t        bpl;      /**< Bytes per line*/
    uint32_t        bpp;      /**< Bits per pixel */
} ia_cipf_frame_format_t;

#define IA_CIPF_MAX_PLANES 6

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_timestamp {
    uint64_t seconds; /**< Number of whole seconds */
    uint64_t useconds; /**< Rest of the time in microseconds */
} ia_cipf_timestamp_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_frame {
    ia_uid              uid;
    uint32_t            id;
    uint32_t            sequence;
    ia_cipf_timestamp_t timestamp;
    uint32_t            flags;
    uint32_t            allocated;
    uint32_t            planes;
    ia_cipf_payload_t   payload[IA_CIPF_MAX_PLANES];
} ia_cipf_frame_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_buffer {
    ia_cipf_payload_t    payload;
} ia_cipf_buffer_t;

/**
 * \ingroup ia_cipf
 */
typedef enum ia_cipf_terminal_type {
    ia_cipf_terminal_type_frame_input,
    ia_cipf_terminal_type_frame_output,
    ia_cipf_terminal_type_param_input,
    ia_cipf_terminal_type_param_output
} ia_cipf_terminal_type_t;

/**
 * \ingroup ia_cipf
 */
typedef enum ia_cipf_connection_type {
    connection_type_push, /* data is pushed by source stage execute */
    connection_type_pull  /* data is pulled by sink stage execute */
} ia_cipf_connection_type_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_point {
    uint16_t x;
    uint16_t y;
} ia_cipf_point_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_rect {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} ia_cipf_rect_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_resolution {
    uint16_t width;
    uint16_t height;
} ia_cipf_resolution_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_association {
    ia_uid stage;
    ia_uid terminal;
    ia_uid property;
} ia_cipf_association_t;

/**
 * \ingroup ia_cipf
 */
typedef struct ia_cipf_fragment_desc {
    ia_cipf_resolution_t size;
    ia_cipf_point_t start;
} ia_cipf_fragment_desc_t;

#endif /* _IA_CIPF_TYPES_H_ */
