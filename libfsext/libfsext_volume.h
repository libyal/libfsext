/*
 * Volume functions
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

#if !defined( _LIBFSEXT_INTERNAL_VOLUME_H )
#define _LIBFSEXT_INTERNAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libfsext_extern.h"
#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcthreads.h"
#include "libfsext_superblock.h"
#include "libfsext_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_internal_volume libfsext_internal_volume_t;

struct libfsext_internal_volume
{
	/* The superblock
	 */
	libfsext_superblock_t *superblock;

	/* Group descriptors array
	 */
	libcdata_array_t *group_descriptors_array;

	/* The inode table
	 */
	libfsext_inode_table_t *inode_table;

	/* The IO handle
	 */
	libfsext_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBFSEXT_EXTERN \
int libfsext_volume_initialize(
     libfsext_volume_t **volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_free(
     libfsext_volume_t **volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_signal_abort(
     libfsext_volume_t *volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_open(
     libfsext_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBFSEXT_EXTERN \
int libfsext_volume_open_wide(
     libfsext_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_close(
     libfsext_volume_t *volume,
     libcerror_error_t **error );

int libfsext_internal_volume_open_read(
     libfsext_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libfsext_internal_volume_read_block_groups(
     libfsext_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_format_version(
     libfsext_volume_t *volume,
     uint8_t *format_version,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_features_flags(
     libfsext_volume_t *volume,
     uint32_t *compatible_features_flags,
     uint32_t *incompatible_features_flags,
     uint32_t *read_only_compatible_features_flags,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_identifier(
     libfsext_volume_t *volume,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label_size(
     libfsext_volume_t *volume,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label(
     libfsext_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label_size(
     libfsext_volume_t *volume,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label(
     libfsext_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_last_mount_path_size(
     libfsext_volume_t *volume,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_last_mount_path(
     libfsext_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_last_mount_path_size(
     libfsext_volume_t *volume,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_last_mount_path(
     libfsext_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_last_mount_time(
     libfsext_volume_t *volume,
     int32_t *posix_time,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_last_written_time(
     libfsext_volume_t *volume,
     int32_t *posix_time,
     libcerror_error_t **error );

int libfsext_internal_volume_get_root_directory(
     libfsext_internal_volume_t *internal_volume,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_root_directory(
     libfsext_volume_t *volume,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

int libfsext_internal_volume_get_file_entry_by_utf8_path(
     libfsext_internal_volume_t *internal_volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_number_of_file_entries(
     libfsext_volume_t *volume,
     uint32_t *number_of_file_entries,
     libcerror_error_t **error );

int libfsext_internal_volume_get_file_entry_by_inode(
     libfsext_internal_volume_t *internal_volume,
     uint32_t inode_number,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_inode(
     libfsext_volume_t *volume,
     uint32_t inode_number,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_utf8_path(
     libfsext_volume_t *volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

int libfsext_internal_volume_get_file_entry_by_utf16_path(
     libfsext_internal_volume_t *internal_volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_utf16_path(
     libfsext_volume_t *volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_INTERNAL_VOLUME_H ) */

