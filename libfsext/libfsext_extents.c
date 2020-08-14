/*
 * Extents functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfsext_extent.h"
#include "libfsext_extent_index.h"
#include "libfsext_extents.h"
#include "libfsext_extents_footer.h"
#include "libfsext_extents_header.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

/* Reads the extents data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_read_data(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsext_extent_t *extent                 = NULL;
	libfsext_extent_index_t *extent_index     = NULL;
	libfsext_extents_footer_t *extents_footer = NULL;
	libfsext_extents_header_t *extents_header = NULL;
	static char *function                     = "libfsext_extents_read_data";
	size_t extents_block_size                 = 0;
	size_t data_offset                        = 0;
	off64_t extents_block_offset              = 0;
	uint8_t block_number_index                = 0;
	int entry_index                           = 0;

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
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < 12 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libfsext_extents_header_initialize(
	     &extents_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extents header.",
		 function );

		goto on_error;
	}
	if( libfsext_extents_header_read_data(
	     extents_header,
	     data,
	     12,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extents header.",
		 function );

		goto on_error;
	}
	data_offset = 12;

	if( extents_header->depth > 5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid depth value out of bounds.",
		 function );

		goto on_error;
	}
	if( extents_header->number_of_extents > ( ( data_size - data_offset ) / 12 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of extents value out of bounds.",
		 function );

		goto on_error;
	}
	for( block_number_index = 0;
	     block_number_index < extents_header->number_of_extents;
	     block_number_index++ )
	{
		if( extents_header->depth == 0 )
		{
			if( libfsext_extent_initialize(
			     &extent,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create extent.",
				 function );

				goto on_error;
			}
			if( libfsext_extent_read_data(
			     extent,
			     &( data[ data_offset ] ),
			     12,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read extent.",
				 function );

				goto on_error;
			}
			data_offset += 12;

			if( extent->number_of_blocks == 0 )
			{
				if( libfsext_extent_free(
				     &extent,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free extent.",
					 function );

					goto on_error;
				}
			}
			else
			{
				if( libcdata_array_append_entry(
				     extents_array,
				     &entry_index,
				     (intptr_t *) extent,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append data extent to array.",
					 function );

					goto on_error;
				}
				extent = NULL;
			}
		}
		else
		{
			if( libfsext_extent_index_initialize(
			     &extent_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create extent index.",
				 function );

				goto on_error;
			}
			if( libfsext_extent_index_read_data(
			     extent_index,
			     &( data[ data_offset ] ),
			     12,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read extent index.",
				 function );

				goto on_error;
			}
			data_offset += 12;

			if( extent_index->physical_block_number > ( (uint64_t) INT64_MAX / io_handle->block_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid extent index - physical block number value out of bounds.",
				 function );

				goto on_error;
			}
			extents_block_offset = (off64_t) extent_index->physical_block_number * io_handle->block_size;

			if( (size_t) extent_index->number_of_blocks > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / io_handle->block_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid extent index - number of blocks value out of bounds.",
				 function );

				goto on_error;
			}
			extents_block_size = (size_t) extent_index->number_of_blocks * io_handle->block_size;

			if( libfsext_extents_read_file_io_handle(
			     extents_array,
			     io_handle,
			     file_io_handle,
			     extents_block_offset,
			     extents_block_size,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read extents at depth: %" PRIu16 ".",
				 function,
				 extents_header->depth - 1 );

				goto on_error;
			}
			if( libfsext_extent_index_free(
			     &extent_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free extent index.",
				 function );

				goto on_error;
			}
		}
	}
	if( libfsext_extents_header_free(
	     &extents_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free extents header.",
		 function );

		goto on_error;
	}
	if( data_offset > ( data_size - 4 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libfsext_extents_footer_initialize(
	     &extents_footer,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extents footer.",
		 function );

		goto on_error;
	}
	if( libfsext_extents_footer_read_data(
	     extents_footer,
	     &( data[ data_offset ] ),
	     4,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extents footer.",
		 function );

		goto on_error;
	}
	if( libfsext_extents_footer_free(
	     &extents_footer,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free extents footer.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( extents_footer != NULL )
	{
		libfsext_extents_footer_free(
		 &extents_footer,
		 NULL );
	}
	if( extent_index != NULL )
	{
		libfsext_extent_index_free(
		 &extent_index,
		 NULL );
	}
	if( extent != NULL )
	{
		libfsext_extent_free(
		 &extent,
		 NULL );
	}
	if( extents_header != NULL )
	{
		libfsext_extents_header_free(
		 &extents_header,
		 NULL );
	}
	return( -1 );
}

/* Reads the extents data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_read_file_io_handle(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     size_t data_size,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfsext_extents_read_file_io_handle";
	ssize_t read_count    = 0;

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
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading extents data of size: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_size,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek extents data offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extents data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data,
	              data_size,
	              error );

	if( read_count != (ssize_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extents data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libfsext_extents_read_data(
	     extents_array,
	     io_handle,
	     file_io_handle,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extents data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

