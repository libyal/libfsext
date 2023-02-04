/*
 * OSS-Fuzz target for libfsext volume type
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libfsext.h"

#if !defined( LIBFSEXT_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsext_error_t **error );

#endif /* !defined( LIBFSEXT_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t volume_identifier[ 16 ];
	uint8_t string_value[ 64 ];

	libbfio_handle_t *file_io_handle             = NULL;
	libfsext_volume_t *volume                    = NULL;
	size_t string_size                           = 0;
	uint32_t compatible_features_flags           = 0;
	uint32_t incompatible_features_flags         = 0;
	uint32_t number_of_file_entries              = 0;
	uint32_t read_only_compatible_features_flags = 0;
	int32_t posix_time                           = 0;
	uint8_t format_version                       = 0;
	int result                                   = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libfsext_volume_initialize(
	     &volume,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	result = libfsext_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBFSEXT_OPEN_READ,
	          NULL );

	if( result != -1 )
	{
		libfsext_volume_get_format_version(
		 volume,
		 &format_version,
		 NULL );

		libfsext_volume_get_features_flags(
		 volume,
		 &compatible_features_flags,
		 &incompatible_features_flags,
		 &read_only_compatible_features_flags,
		 NULL );

		libfsext_volume_get_identifier(
		 volume,
		 volume_identifier,
		 16,
		 NULL );

		libfsext_volume_get_utf8_label_size(
		 volume,
		 &string_size,
		 NULL );

		libfsext_volume_get_utf8_label(
		 volume,
		 string_value,
		 64,
		 NULL );

		libfsext_volume_get_utf8_last_mount_path_size(
		 volume,
		 &string_size,
		 NULL );

		libfsext_volume_get_utf8_last_mount_path(
		 volume,
		 string_value,
		 64,
		 NULL );

		libfsext_volume_get_last_mount_time(
		 volume,
		 &posix_time,
		 NULL );

		libfsext_volume_get_last_written_time(
		 volume,
		 &posix_time,
		 NULL );

		libfsext_volume_get_number_of_file_entries(
		 volume,
		 &number_of_file_entries,
		 NULL );

		libfsext_volume_close(
		 volume,
		 NULL );
	}
	libfsext_volume_free(
	 &volume,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

