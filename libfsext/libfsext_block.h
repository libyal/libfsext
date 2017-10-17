/*
 * Block functions
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

#if !defined( _LIBFSEXT_BLOCK_H )
#define _LIBFSEXT_BLOCK_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfcache.h"
#include "libfsext_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_block libfsext_block_t;

struct libfsext_block
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libfsext_block_initialize(
     libfsext_block_t **block,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_block_free(
     libfsext_block_t **block,
     libcerror_error_t **error );

int libfsext_block_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t block_offset,
     size64_t block_size,
     uint32_t range_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_BLOCK_H ) */

