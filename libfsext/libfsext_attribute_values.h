/*
 * Extended attribute values functions
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

#if !defined( _LIBFSEXT_ATTRIBUTE_VALUES_H )
#define _LIBFSEXT_ATTRIBUTE_VALUES_H

#include <common.h>
#include <types.h>

#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_attribute_values libfsext_attribute_values_t;

struct libfsext_attribute_values
{
	/* Name
	 */
	uint8_t *name;

	/* Name size
	 */
	size_t name_size;

	/* Value data inode number
	 */
	uint32_t value_data_inode_number;

	/* Value data offset
	 */
	uint16_t value_data_offset;

	/* Value data size
	 */
	uint32_t value_data_size;

	/* Value data
	 */
	uint8_t *value_data;
};

int libfsext_attribute_values_initialize(
     libfsext_attribute_values_t **attribute_values,
     libcerror_error_t **error );

int libfsext_attribute_values_free(
     libfsext_attribute_values_t **attribute_values,
     libcerror_error_t **error );

int libfsext_attribute_values_read_data(
     libfsext_attribute_values_t *attribute_values,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_attribute_values_compare_name_with_utf8_string(
     libfsext_attribute_values_t *attribute_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libfsext_attribute_values_get_utf8_name_size(
     libfsext_attribute_values_t *attribute_values,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfsext_attribute_values_get_utf8_name(
     libfsext_attribute_values_t *attribute_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfsext_attribute_values_compare_name_with_utf16_string(
     libfsext_attribute_values_t *attribute_values,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libcerror_error_t **error );

int libfsext_attribute_values_get_utf16_name_size(
     libfsext_attribute_values_t *attribute_values,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfsext_attribute_values_get_utf16_name(
     libfsext_attribute_values_t *attribute_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_ATTRIBUTE_VALUES_H ) */

