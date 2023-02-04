/*
 * Debug functions
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFSEXT_DEBUG_H )
#define _LIBFSEXT_DEBUG_H

#include <common.h>
#include <types.h>

#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

void libfsext_debug_print_file_system_state_flags(
      uint16_t file_system_state_flags );

void libfsext_debug_print_compatible_features_flags(
      uint32_t compatible_features_flags );

void libfsext_debug_print_incompatible_features_flags(
      uint32_t incompatible_features_flags );

void libfsext_debug_print_read_only_compatible_features_flags(
      uint32_t read_only_compatible_features_flags );

void libfsext_debug_print_inode_flags(
      uint32_t inode_flags );

void libfsext_debug_print_file_mode(
      uint16_t file_mode );

const char *libfsext_debug_print_error_handling_status(
             uint16_t error_handling_status );

const char *libfsext_debug_print_creator_operating_system(
             uint32_t creator_operating_system );

const char *libfsext_debug_print_file_type(
             uint16_t file_type );

int libfsext_debug_print_posix_time_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint8_t value_type,
     uint32_t string_format_flags,
     libcerror_error_t **error );

int libfsext_debug_print_guid_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error );

int libfsext_debug_print_utf8_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error );

int libfsext_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_DEBUG_H ) */

