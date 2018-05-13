/*
 * Block vector functions
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

#include <common.h>
#include <types.h>

#include "libfsext_block.h"
#include "libfsext_block_vector.h"
#include "libfsext_extent.h"
#include "libfsext_inode.h"
#include "libfsext_definitions.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfcache.h"
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
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfcache_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libfsext_block_read_element_data,
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

