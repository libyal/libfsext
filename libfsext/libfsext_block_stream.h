/*
 * Block stream functions
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

#if !defined( _LIBFSEXT_BLOCK_STREAM_H )
#define _LIBFSEXT_BLOCK_STREAM_H

#include <common.h>
#include <types.h>

#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libfsext_block_stream_initialize_from_data(
     libfdata_stream_t **block_stream,
     const uint8_t *data,
     size64_t data_size,
     libcerror_error_t **error );

int libfsext_block_stream_initialize_from_extents(
     libfdata_stream_t **block_stream,
     libfsext_io_handle_t *io_handle,
     libfsext_inode_t *inode,
     libcerror_error_t **error );

int libfsext_block_stream_initialize(
     libfdata_stream_t **block_stream,
     libfsext_io_handle_t *io_handle,
     libfsext_inode_t *inode,
     size64_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_BLOCK_STREAM_H ) */

