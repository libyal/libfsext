/*
 * File entry functions
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

#if !defined( _LIBFSEXT_FILE_ENTRY_H )
#define _LIBFSEXT_FILE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libfsext_attribute_values.h"
#include "libfsext_directory.h"
#include "libfsext_directory_entry.h"
#include "libfsext_extern.h"
#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcthreads.h"
#include "libfsext_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_internal_file_entry libfsext_internal_file_entry_t;

struct libfsext_internal_file_entry
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

	/* The inode number
	 */
	uint32_t inode_number;

	/* The inode
	 */
	libfsext_inode_t *inode;

	/* The directory entry
	 */
	libfsext_directory_entry_t *directory_entry;

	/* The extended attributes
	 */
	libcdata_array_t *extended_attributes_array;

	/* The directory
	 */
	libfsext_directory_t *directory;

	/* The data size
	 */
	size64_t data_size;

	/* The data block stream
	 */
	libfdata_stream_t *data_block_stream;

	/* The symbolic link data
	 */
	uint8_t *symbolic_link_data;

	/* The symbolic link data size
	 */
	size_t symbolic_link_data_size;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libfsext_file_entry_initialize(
     libfsext_file_entry_t **file_entry,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsext_inode_table_t *inode_table,
     uint32_t inode_number,
     libfsext_inode_t *inode,
     libfsext_directory_entry_t *directory_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_free(
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_directory(
     libfsext_internal_file_entry_t *internal_file_entry,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_symbolic_link_data(
     libfsext_internal_file_entry_t *internal_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_is_empty(
     libfsext_file_entry_t *file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_inode_number(
     libfsext_file_entry_t *file_entry,
     uint32_t *inode_number,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_access_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_creation_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_inode_change_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_modification_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_deletion_time(
     libfsext_file_entry_t *file_entry,
     int32_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_file_mode(
     libfsext_file_entry_t *file_entry,
     uint16_t *file_mode,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_links(
     libfsext_file_entry_t *file_entry,
     uint16_t *number_of_links,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_owner_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *owner_identifier,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_group_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *group_identifier,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_device_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *device_identifier,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_device_number(
     libfsext_file_entry_t *file_entry,
     uint8_t *major_device_number,
     uint8_t *minor_device_number,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_name(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_name(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_extended_attributes(
     libfsext_internal_file_entry_t *internal_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_extended_attributes(
     libfsext_file_entry_t *file_entry,
     int *number_of_extended_attributes,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_index(
     libfsext_file_entry_t *file_entry,
     int extended_attribute_index,
     libfsext_extended_attribute_t **extended_attribute,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_attribute_values_by_utf8_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_attribute_values_t **attribute_values,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_attribute_values_by_utf16_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_attribute_values_t **attribute_values,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_has_extended_attribute_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_has_extended_attribute_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_extended_attribute_t **extended_attribute,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_extended_attribute_t **extended_attribute,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_sub_file_entries(
     libfsext_file_entry_t *file_entry,
     int *number_of_sub_entries,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_sub_file_entry_by_index(
     libfsext_internal_file_entry_t *internal_file_entry,
     int sub_file_entry_index,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_index(
     libfsext_file_entry_t *file_entry,
     int sub_file_entry_index,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_sub_file_entry_by_utf8_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

int libfsext_internal_file_entry_get_sub_file_entry_by_utf16_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint16_t *utf8_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
ssize_t libfsext_file_entry_read_buffer(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
ssize_t libfsext_file_entry_read_buffer_at_offset(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
off64_t libfsext_file_entry_seek_offset(
         libfsext_file_entry_t *file_entry,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_offset(
     libfsext_file_entry_t *file_entry,
     off64_t *offset,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_size(
     libfsext_file_entry_t *file_entry,
     size64_t *size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_extents(
     libfsext_file_entry_t *file_entry,
     int *number_of_extents,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extent_by_index(
     libfsext_file_entry_t *file_entry,
     int extent_index,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_FILE_ENTRY_H ) */

