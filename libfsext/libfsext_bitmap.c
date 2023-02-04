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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfsext_bitmap.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

/* Creates a bitmap
 * Make sure the value bitmap is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_bitmap_initialize(
     libfsext_bitmap_t **bitmap,
     libcerror_error_t **error )
{
	static char *function = "libfsext_bitmap_initialize";

	if( bitmap == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bitmap.",
		 function );

		return( -1 );
	}
	if( *bitmap != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid bitmap value already set.",
		 function );

		return( -1 );
	}
	*bitmap = memory_allocate_structure(
	           libfsext_bitmap_t );

	if( *bitmap == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create bitmap.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *bitmap,
	     0,
	     sizeof( libfsext_bitmap_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear bitmap.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *bitmap != NULL )
	{
		memory_free(
		 *bitmap );

		*bitmap = NULL;
	}
	return( -1 );
}

/* Frees a bitmap
 * Returns 1 if successful or -1 on error
 */
int libfsext_bitmap_free(
     libfsext_bitmap_t **bitmap,
     libcerror_error_t **error )
{
	static char *function = "libfsext_bitmap_free";

	if( bitmap == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bitmap.",
		 function );

		return( -1 );
	}
	if( *bitmap != NULL )
	{
		memory_free(
		 *bitmap );

		*bitmap = NULL;
	}
	return( 1 );
}

/* Reads the bitmap data
 * Returns 1 if successful or -1 on error
 */
int libfsext_bitmap_read_data(
     libfsext_bitmap_t *bitmap,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function             = "libfsext_bitmap_read_data";
	size_t data_offset                = 0;
	uint8_t bit_index                 = 0;
	uint8_t byte_value                = 0;
	uint8_t in_allocated_range        = 0;
	int allocated_element_index       = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	int first_allocated_element_index = 0;
#endif

	if( bitmap == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bitmap.",
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
	if( ( data_size == 0 )
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: bitmap data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	while( data_offset < data_size )
	{
		byte_value = data[ data_offset ];

		data_offset++;

		for( bit_index = 0;
		     bit_index < 8;
		     bit_index++ )
		{
			if( in_allocated_range == 0 )
			{
				if( ( byte_value & 0x01 ) != 0 )
				{
					in_allocated_range            = 1;
#if defined( HAVE_DEBUG_OUTPUT )
					first_allocated_element_index = allocated_element_index;
#endif
				}
			}
			else if( ( byte_value & 0x01 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					if( first_allocated_element_index == ( allocated_element_index - 1 ) )
					{
						libcnotify_printf(
						 "%s: allocated element\t\t\t\t: %d\n",
						 function,
						 first_allocated_element_index );
					}
					else
					{
						libcnotify_printf(
						 "%s: allocated element\t\t\t\t: %d - %d\n",
						 function,
						 first_allocated_element_index,
						 allocated_element_index - 1 );
					}
				}
#endif
				in_allocated_range = 0;
			}
			byte_value >>= 1;

			allocated_element_index++;
		}
	}
	if( in_allocated_range != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( first_allocated_element_index == ( allocated_element_index - 1 ) )
			{
				libcnotify_printf(
				 "%s: allocated element\t\t\t\t: %d\n",
				 function,
				 first_allocated_element_index );
			}
			else
			{
				libcnotify_printf(
				 "%s: allocated element\t\t\t\t: %d - %d\n",
				 function,
				 first_allocated_element_index,
				 allocated_element_index - 1 );
			}
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the bitmap from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_bitmap_read_file_io_handle(
     libfsext_bitmap_t *bitmap,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfsext_bitmap_read_file_io_handle";
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
	if( ( io_handle->block_size == 0 )
	 || ( io_handle->block_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - block size value out of bounds.",
		 function );

		return( -1 );
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * io_handle->block_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading bitmap at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              (size_t) io_handle->block_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) io_handle->block_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read bitmap at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libfsext_bitmap_read_data(
	     bitmap,
	     data,
	     (size_t) io_handle->block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read bitmap at offset: %" PRIi64 " (0x%08" PRIx64 ").",
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

