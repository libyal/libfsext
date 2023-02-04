/*
 * Block vector functions
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

#include <common.h>
#include <types.h>

#include "libfsext_block.h"
#include "libfsext_block_vector.h"
#include "libfsext_extent.h"
#include "libfsext_inode.h"
#include "libfsext_definitions.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"
#include "libfsext_libbfio.h"
#include "libfsext_libfdata.h"
#include "libfsext_unused.h"

/* Creates a block vector
 * Make sure the value block_vector is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_vector_initialize(
     libfdata_vector_t **block_vector,
     libfsext_io_handle_t *io_handle,
     libfsext_inode_t *inode,
     libcerror_error_t **error )
{
	libfsext_extent_t *extent = NULL;
	static char *function     = "libfsext_block_vector_initialize";
	size64_t data_size        = 0;
	off64_t file_offset       = 0;
	int extent_index          = 0;
	int number_of_extents     = 0;
	int segment_index         = 0;

	if( block_vector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block vector.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing block size.",
		 function );

		return( -1 );
	}
	if( inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode.",
		 function );

		return( -1 );
	}
	if( libfdata_vector_initialize(
	     block_vector,
	     (size64_t) io_handle->block_size,
	     (intptr_t *) io_handle,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfdata_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libfsext_block_vector_read_element_data,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block vector.",
		 function );

		goto on_error;
	}
	if( libfsext_inode_get_number_of_extents(
	     inode,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents from inode.",
		 function );

		goto on_error;
	}
	for( extent_index = 0;
	     extent_index < number_of_extents;
	     extent_index++ )
	{
		if( libfsext_inode_get_extent_by_index(
		     inode,
		     extent_index,
		     &extent,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent: %d.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( extent == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing extent: %d.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( extent->physical_block_number == 0 )
		{
			break;
		}
		if( extent->physical_block_number > ( (uint64_t) INT64_MAX / io_handle->block_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent: %d - invalid physical block number value out of bounds.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( extent->number_of_blocks > ( (uint64_t) UINT64_MAX / io_handle->block_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent: %d - invalid number of blocks value out of bounds.",
			 function,
			 extent_index );

			goto on_error;
		}
		file_offset = (off64_t) extent->physical_block_number * (off64_t) io_handle->block_size;
		data_size   = (size64_t) extent->number_of_blocks * io_handle->block_size;

		if( libfdata_vector_append_segment(
		     *block_vector,
		     &segment_index,
		     0,
		     file_offset,
		     data_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append block: %" PRIu64 " as vector segment.",
			 function,
			 extent->physical_block_number );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( *block_vector != NULL )
	{
		libfdata_vector_free(
		 block_vector,
		 NULL );
	}
	return( -1 );
}

/* Reads a block
 * Callback function for the block vector
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_vector_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index LIBFSEXT_ATTRIBUTE_UNUSED,
     int element_data_file_index LIBFSEXT_ATTRIBUTE_UNUSED,
     off64_t block_offset,
     size64_t block_size,
     uint32_t range_flags LIBFSEXT_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBFSEXT_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libfsext_block_t *block = NULL;
	static char *function   = "libfsext_block_vector_read_element_data";

	LIBFSEXT_UNREFERENCED_PARAMETER( element_index )
	LIBFSEXT_UNREFERENCED_PARAMETER( element_data_file_index )
	LIBFSEXT_UNREFERENCED_PARAMETER( range_flags )
	LIBFSEXT_UNREFERENCED_PARAMETER( read_flags )

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( block_size == 0 )
	 || ( block_size > (size64_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libfsext_block_initialize(
	     &block,
	     (size_t) block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing block.",
		 function );

		goto on_error;
	}
	if( libfsext_block_read_file_io_handle(
	     block,
	     file_io_handle,
	     block_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block.",
		 function );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) block,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_block_free,
	     LIBFDATA_VECTOR_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set block as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( block != NULL )
	{
		libfsext_block_free(
		 &block,
		 NULL );
	}
	return( -1 );
}

