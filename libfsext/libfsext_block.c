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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfsext_block.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfcache.h"
#include "libfsext_libfdata.h"
#include "libfsext_types.h"
#include "libfsext_unused.h"

/* Creates a block
 * Make sure the value block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_initialize(
     libfsext_block_t **block,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsext_block_initialize";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid block value already set.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*block = memory_allocate_structure(
	          libfsext_block_t );

	if( *block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *block,
	     0,
	     sizeof( libfsext_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block.",
		 function );

		memory_free(
		 *block );

		*block = NULL;

		return( -1 );
	}
	if( data_size > 0 )
	{
		( *block )->data = (uint8_t *) memory_allocate(
		                                sizeof( uint8_t ) * data_size );

		if( ( *block )->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		( *block )->data_size = data_size;
	}
	return( 1 );

on_error:
	if( *block != NULL )
	{
		memory_free(
		 *block );

		*block = NULL;
	}
	return( -1 );
}

/* Frees a block
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_free(
     libfsext_block_t **block,
     libcerror_error_t **error )
{
	static char *function = "libfsext_block_free";

	if( block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block.",
		 function );

		return( -1 );
	}
	if( *block != NULL )
	{
		if( ( *block )->data != NULL )
		{
			memory_free(
			 ( *block )->data );
		}
		memory_free(
		 *block );

		*block = NULL;
	}
	return( 1 );
}

/* Reads a block
 * Callback function for the block vector
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index LIBFSEXT_ATTRIBUTE_UNUSED,
     int element_data_file_index LIBFSEXT_ATTRIBUTE_UNUSED,
     off64_t block_offset,
     size64_t block_size,
     uint32_t range_flags,
     uint8_t read_flags LIBFSEXT_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libfsext_block_t *block = NULL;
	static char *function   = "libfsext_block_read_element_data";
	ssize_t read_count      = 0;

	LIBFSEXT_UNREFERENCED_PARAMETER( element_index )
	LIBFSEXT_UNREFERENCED_PARAMETER( element_data_file_index )
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
	if( ( range_flags & LIBFDATA_RANGE_FLAG_IS_SPARSE ) != 0 )
	{
		if( memory_set(
		     block->data,
		     0,
		     block->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear block data.",
			 function );

			goto on_error;
		}
	}
	else
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading block at offset: 0x%08" PRIx64 " with size: %" PRIu64 ".\n",
			 function,
			 block_offset,
			 block_size );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     block_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek offset: 0x%08" PRIx64 ".",
			 function,
			 block_offset );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              block->data,
		              block->data_size,
		              error );

		if( read_count != (ssize_t) block->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block.",
			 function );

			goto on_error;
		}
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

