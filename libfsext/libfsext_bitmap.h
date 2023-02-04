/*
 * Bitmap functions
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

#if !defined( _LIBFSEXT_BITMAP_H )
#define _LIBFSEXT_BITMAP_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_bitmap libfsext_bitmap_t;

struct libfsext_bitmap
{
	/* Dummy value
	 */
	int dummy;
};

int libfsext_bitmap_initialize(
     libfsext_bitmap_t **bitmap,
     libcerror_error_t **error );

int libfsext_bitmap_free(
     libfsext_bitmap_t **bitmap,
     libcerror_error_t **error );

int libfsext_bitmap_read_data(
     libfsext_bitmap_t *bitmap,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_bitmap_read_file_io_handle(
     libfsext_bitmap_t *bitmap,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_BITMAP_H ) */

