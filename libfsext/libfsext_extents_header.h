/*
 * Extents header functions
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSEXT_EXTENTS_HEADER_H )
#define _LIBFSEXT_EXTENTS_HEADER_H

#include <common.h>
#include <types.h>

#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_extents_header libfsext_extents_header_t;

struct libfsext_extents_header
{
	/* Logical block number
	 */
	uint32_t logical_block_number;

	/* Offset
	 */
	off64_t offset;

	/* Size
	 */
	size64_t size;
};

int libfsext_extents_header_initialize(
     libfsext_extents_header_t **extents_header,
     libcerror_error_t **error );

int libfsext_extents_header_free(
     libfsext_extents_header_t **extents_header,
     libcerror_error_t **error );

int libfsext_extents_header_read_data(
     libfsext_extents_header_t *extents_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_EXTENTS_HEADER_H ) */

