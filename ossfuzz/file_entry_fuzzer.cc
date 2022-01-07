/*
 * OSS-Fuzz target for libfsext file_entry type
 *
 * Copyright (C) 2010-2022, Joachim Metz <joachim.metz@gmail.com>
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
	libbfio_handle_t *file_io_handle      = NULL;
	libfsext_file_entry_t *root_directory = NULL;
	libfsext_file_entry_t *sub_file_entry = NULL;
	libfsext_volume_t *volume             = NULL;
	int number_of_sub_file_entries        = 0;

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
	if( libfsext_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     LIBFSEXT_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libfsext_volume;
	}
	if( libfsext_volume_get_root_directory(
	     volume,
	     &root_directory,
	     NULL ) == 1 )
	{
		if( libfsext_file_entry_get_number_of_sub_file_entries(
		     root_directory,
		     &number_of_sub_file_entries,
		     NULL ) != 1 )
		{
			goto on_error_libfsext_root_directory;
		}
		if( number_of_sub_file_entries > 0 )
		{
			if( libfsext_file_entry_get_sub_file_entry_by_index(
			     root_directory,
			     0,
			     &sub_file_entry,
			     NULL ) != 1 )
			{
				goto on_error_libfsext_root_directory;
			}
			libfsext_file_entry_free(
			 &sub_file_entry,
			 NULL );
		}
on_error_libfsext_root_directory:
		libfsext_file_entry_free(
		 &root_directory,
		 NULL );
	}
	libfsext_volume_close(
	 volume,
	 NULL );

on_error_libfsext_volume:
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

