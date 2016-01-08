/*
 * Volume functions
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSEXT_INTERNAL_VOLUME_H )
#define _LIBFSEXT_INTERNAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libfsext_extern.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_internal_volume libfsext_internal_volume_t;

struct libfsext_internal_volume
{
	/* The IO handle
	 */
	libfsext_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;
};

LIBFSEXT_EXTERN \
int libfsext_volume_initialize(
     libfsext_volume_t **volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_free(
     libfsext_volume_t **volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_signal_abort(
     libfsext_volume_t *volume,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_open(
     libfsext_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBFSEXT_EXTERN \
int libfsext_volume_open_wide(
     libfsext_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );
#endif

LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_close(
     libfsext_volume_t *volume,
     libcerror_error_t **error );

int libfsext_volume_open_read(
     libfsext_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label_size(
     libfsext_volume_t *volume,
     size_t *utf8_label_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label(
     libfsext_volume_t *volume,
     uint8_t *utf8_label,
     size_t utf8_label_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label_size(
     libfsext_volume_t *volume,
     size_t *utf16_label_size,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label(
     libfsext_volume_t *volume,
     uint16_t *utf16_label,
     size_t utf16_label_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

