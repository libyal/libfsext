/*
 * Data blocks functions
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

#if !defined( _LIBFSEXT_DATA_BLOCKS_H )
#define _LIBFSEXT_DATA_BLOCKS_H

#include <common.h>
#include <types.h>

#include "libfsext_extent.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libfsext_data_blocks_get_last_extent(
     libcdata_array_t *extents_array,
     libfsext_extent_t **last_extent,
     libcerror_error_t **error );

int libfsext_data_blocks_read_inode_data_reference(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_data_blocks_read_data(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     uint64_t block_number,
     const uint8_t *data,
     size_t data_size,
     int depth,
     libcerror_error_t **error );

int libfsext_data_blocks_read_file_io_handle(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     uint32_t block_number,
     int depth,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_DATA_BLOCKS_H ) */

