/*
 * Extent functions
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

#if !defined( _LIBFSEXT_EXTENT_H )
#define _LIBFSEXT_EXTENT_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_extent libfsext_extent_t;

struct libfsext_extent
{
	/* Logical block number
	 */
	uint32_t logical_block_number;

	/* Physical block number
	 */
	uint64_t physical_block_number;

	/* Number of blocks
	 */
	uint64_t number_of_blocks;

	/* The range flags
	 */
	uint32_t range_flags;
};

int libfsext_extent_initialize(
     libfsext_extent_t **extent,
     libcerror_error_t **error );

int libfsext_extent_free(
     libfsext_extent_t **extent,
     libcerror_error_t **error );

int libfsext_extent_clone(
     libfsext_extent_t **destination_extent,
     libfsext_extent_t *source_extent,
     libcerror_error_t **error );

int libfsext_extent_read_data(
     libfsext_extent_t *extent,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_extent_get_values(
     libfsext_extent_t *extent,
     libfsext_io_handle_t *io_handle,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_EXTENT_H ) */

