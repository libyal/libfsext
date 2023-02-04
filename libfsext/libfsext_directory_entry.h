/*
 * Directory entry functions
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

#if !defined( _LIBFSEXT_DIRECTORY_ENTRY_H )
#define _LIBFSEXT_DIRECTORY_ENTRY_H

#include <common.h>
#include <types.h>

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

	/* File type
	 */
	uint8_t file_type;

	/* Name
	 */
	uint8_t *name;

	/* Name size
	 */
	uint8_t name_size;
};

int libfsext_directory_entry_initialize(
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_entry_free(
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error );

int libfsext_directory_entry_clone(
     libfsext_directory_entry_t **destination_directory_entry,
     libfsext_directory_entry_t *source_directory_entry,
     libcerror_error_t **error );

int libfsext_directory_entry_read_data(
     libfsext_directory_entry_t *directory_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_directory_entry_get_inode_number(
     libfsext_directory_entry_t *directory_entry,
     uint32_t *inode_number,
     libcerror_error_t **error );

int libfsext_directory_entry_get_utf8_name_size(
     libfsext_directory_entry_t *directory_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfsext_directory_entry_get_utf8_name(
     libfsext_directory_entry_t *directory_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfsext_directory_entry_compare_with_utf8_string(
     libfsext_directory_entry_t *directory_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libfsext_directory_entry_get_utf16_name_size(
     libfsext_directory_entry_t *directory_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfsext_directory_entry_get_utf16_name(
     libfsext_directory_entry_t *directory_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libfsext_directory_entry_compare_with_utf16_string(
     libfsext_directory_entry_t *directory_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_DIRECTORY_ENTRY_H ) */

