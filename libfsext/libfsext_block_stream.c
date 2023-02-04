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

#include <common.h>
#include <types.h>

#include "libfsext_block_data_handle.h"
#include "libfsext_buffer_data_handle.h"
#include "libfsext_definitions.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfdata.h"

/* Creates data block stream from a buffer of data
 * Make sure the value block_stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_stream_initialize_from_data(
     libfdata_stream_t **block_stream,
     const uint8_t *data,
     size64_t data_size,
     libcerror_error_t **error )
{
	libfdata_stream_t *safe_data_stream        = NULL;
	libfsext_buffer_data_handle_t *data_handle = NULL;
	static char *function                      = "libfsext_block_stream_initialize_from_data";
	int segment_index                          = 0;
	size_t inline_data_size                    = 60;

	if( block_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block stream.",
		 function );

		return( -1 );
	}
	if( data_size < inline_data_size )
	{
		inline_data_size = (size_t) data_size;
	}
	if( libfsext_buffer_data_handle_initialize(
	     &data_handle,
	     data,
	     inline_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create buffer data handle.",
		 function );

		goto on_error;
	}
	if( libfdata_stream_initialize(
	     &safe_data_stream,
	     (intptr_t *) data_handle,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_buffer_data_handle_free,
	     NULL,
	     NULL,
	     (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &libfsext_buffer_data_handle_read_segment_data,
	     NULL,
	     (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &libfsext_buffer_data_handle_seek_segment_offset,
	     LIBFDATA_DATA_HANDLE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data stream.",
		 function );

		goto on_error;
	}
	data_handle = NULL;

	if( libfdata_stream_append_segment(
	     safe_data_stream,
	     &segment_index,
	     0,
	     0,
	     (size64_t) inline_data_size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data stream segment.",
		 function );

		goto on_error;
	}
	if( data_size >= 60 )
	{
		if( libfdata_stream_append_segment(
		     safe_data_stream,
		     &segment_index,
		     0,
		     0,
		     data_size - inline_data_size,
		     LIBFSEXT_EXTENT_FLAG_IS_SPARSE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append sparse data stream segment.",
			 function );

			goto on_error;
		}
	}
	*block_stream = safe_data_stream;

	return( 1 );

on_error:
	if( safe_data_stream != NULL )
	{
		libfdata_stream_free(
		 &safe_data_stream,
		 NULL );
	}
	if( data_handle != NULL )
	{
		libfsext_buffer_data_handle_free(
		 &data_handle,
		 NULL );
	}
	return( -1 );
}

/* Creates data block stream from extents
 * Make sure the value data_stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_stream_initialize_from_extents(
     libfdata_stream_t **block_stream,
     libfsext_io_handle_t *io_handle,
     libfsext_inode_t *inode,
     libcerror_error_t **error )
{
	libfdata_stream_t *safe_data_stream = NULL;
	libfsext_extent_t *extent           = NULL;
	static char *function               = "libfsext_block_stream_initialize_from_extents";
	size64_t data_segment_size          = 0;
	off64_t data_segment_offset         = 0;
	int extent_index                    = 0;
	int number_of_extents               = 0;
	int segment_index                   = 0;

	if( block_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data stream.",
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
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_initialize(
	     &safe_data_stream,
	     NULL,
	     NULL,
	     NULL,
	     NULL,
	     (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &libfsext_block_data_handle_read_segment_data,
	     NULL,
	     (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &libfsext_block_data_handle_seek_segment_offset,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data stream.",
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
		 "%s: unable to retrieve number of extents.",
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
		data_segment_offset = extent->physical_block_number * io_handle->block_size;
		data_segment_size   = (size64_t) extent->number_of_blocks * io_handle->block_size;

		if( libfdata_stream_append_segment(
		     safe_data_stream,
		     &segment_index,
		     0,
		     data_segment_offset,
		     data_segment_size,
		     extent->range_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append extent: %d data stream segment.",
			 function,
			 extent_index );

			goto on_error;
		}
	}
	if( libfdata_stream_set_mapped_size(
	     safe_data_stream,
	     inode->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set mapped size of data stream.",
		 function );

		goto on_error;
	}
	*block_stream = safe_data_stream;

	return( 1 );

on_error:
	if( safe_data_stream != NULL )
	{
		libfdata_stream_free(
		 &safe_data_stream,
		 NULL );
	}
	return( -1 );
}

/* Creates a block stream
 * Make sure the value block_stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_block_stream_initialize(
     libfdata_stream_t **block_stream,
     libfsext_io_handle_t *io_handle,
     libfsext_inode_t *inode,
     size64_t data_size,
     libcerror_error_t **error )
{
	libfdata_stream_t *safe_block_stream = NULL;
	static char *function                = "libfsext_block_stream_initialize";
	int result                           = 0;

	if( block_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block stream.",
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
	if( ( data_size == 0 )
	 || ( ( io_handle->format_version == 4 )
	  &&  ( ( inode->flags & LIBFSEXT_INODE_FLAG_INLINE_DATA ) != 0 ) ) )
	{
		result = libfsext_block_stream_initialize_from_data(
		          &safe_block_stream,
		          inode->data_reference,
		          (size_t) data_size,
		          error );
	}
	else
	{
		result = libfsext_block_stream_initialize_from_extents(
		          &safe_block_stream,
		          io_handle,
		          inode,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block stream.",
		 function );

		goto on_error;
	}
	*block_stream = safe_block_stream;

	return( 1 );

on_error:
	if( safe_block_stream != NULL )
	{
		libfdata_stream_free(
		 &safe_block_stream,
		 NULL );
	}
	return( -1 );
}

