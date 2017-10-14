/*
 * Directory entry functions
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFSEXT_DIRECTORY_ENTRY_H )
#define _LIBFSEXT_DIRECTORY_ENTRY_H

#include <common.h>
#include <types.h>

#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_directory_entry libfsext_directory_entry_t;

struct libfsext_directory_entry
{
	/* Inode number
	 */
	uint32_t inode_number;

	/* Size
	 */
	uint16_t size;

	/* Name string size
	 */
	uint8_t name_string_size;

	/* File type
	 */
	uint8_t file_type;

	/* Name string
	 */
	uint8_t *name_string;
};

int libfsext_directory_entry_initialize(
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_entry_free(
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_entry_read_data(
     libfsext_directory_entry_t *directory_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_directory_entry_read_file_io_handle(
     libfsext_directory_entry_t *directory_entry,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_DIRECTORY_ENTRY_H ) */

