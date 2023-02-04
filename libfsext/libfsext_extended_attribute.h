/*
 * Extended attribute functions
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

#if !defined( _LIBFSEXT_EXTENDED_ATTRIBUTE_H )
#define _LIBFSEXT_EXTENDED_ATTRIBUTE_H

#include <common.h>
#include <types.h>

#include "libfsext_attribute_values.h"
#include "libfsext_extern.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcthreads.h"
#include "libfsext_libfdata.h"
#include "libfsext_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_internal_extended_attribute libfsext_internal_extended_attribute_t;

struct libfsext_internal_extended_attribute
{
	/* The IO handle
	 */
	libfsext_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The inode table
	 */
	libfsext_inode_table_t *inode_table;

	/* The attribute values
	 */
	libfsext_attribute_values_t *attribute_values;

	/* The data stream
	 */
	libfdata_stream_t *data_stream;

	/* Data extents array
	 */
	libcdata_array_t *data_extents_array;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libfsext_extended_attribute_initialize(
     libfsext_extended_attribute_t **extended_attribute,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsext_inode_table_t *inode_table,
     libfsext_attribute_values_t *attribute_values,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_free(
     libfsext_extended_attribute_t **extended_attribute,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf8_name_size(
     libfsext_extended_attribute_t *extended_attribute,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf8_name(
     libfsext_extended_attribute_t *extended_attribute,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf16_name_size(
     libfsext_extended_attribute_t *extended_attribute,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf16_name(
     libfsext_extended_attribute_t *extended_attribute,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libfsext_internal_extended_attribute_get_data_stream(
     libfsext_internal_extended_attribute_t *internal_extended_attribute,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
ssize_t libfsext_extended_attribute_read_buffer(
         libfsext_extended_attribute_t *extended_attribute,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
ssize_t libfsext_extended_attribute_read_buffer_at_offset(
         libfsext_extended_attribute_t *extended_attribute,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
off64_t libfsext_extended_attribute_seek_offset(
         libfsext_extended_attribute_t *extended_attribute,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_offset(
     libfsext_extended_attribute_t *extended_attribute,
     off64_t *offset,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_size(
     libfsext_extended_attribute_t *extended_attribute,
     size64_t *size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_number_of_extents(
     libfsext_extended_attribute_t *extended_attribute,
     int *number_of_extents,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_extent_by_index(
     libfsext_extended_attribute_t *extended_attribute,
     int extent_index,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_EXTENDED_ATTRIBUTE_H ) */

