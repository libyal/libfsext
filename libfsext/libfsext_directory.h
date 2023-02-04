/*
 * Directory functions
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

#if !defined( _LIBFSEXT_DIRECTORY_H )
#define _LIBFSEXT_DIRECTORY_H

#include <common.h>
#include <types.h>

#include "libfsext_directory_entry.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_directory libfsext_directory_t;

struct libfsext_directory
{
	/* Entries array
	 */
	libcdata_array_t *entries_array;
};

int libfsext_directory_initialize(
     libfsext_directory_t **directory,
     libcerror_error_t **error );

int libfsext_directory_free(
     libfsext_directory_t **directory,
     libcerror_error_t **error );

int libfsext_directory_read_block_data(
     libfsext_directory_t *directory,
     const uint8_t *data,
     size_t data_size,
     uint32_t *directory_entry_index,
     libcerror_error_t **error );

int libfsext_directory_read_inline_data(
     libfsext_directory_t *directory,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_directory_read_file_io_handle(
     libfsext_directory_t *directory,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsext_inode_t *inode,
     libcerror_error_t **error );

int libfsext_directory_get_number_of_entries(
     libfsext_directory_t *directory,
     int *number_of_entries,
     libcerror_error_t **error );

int libfsext_directory_get_entry_by_index(
     libfsext_directory_t *directory,
     int entry_index,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_get_entry_by_utf8_name(
     libfsext_directory_t *directory,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_get_entry_by_utf16_name(
     libfsext_directory_t *directory,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_DIRECTORY_H ) */

