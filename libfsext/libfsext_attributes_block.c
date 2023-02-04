/*
 * Extended attributes block functions
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

#include "libfsext_attribute_values.h"
#include "libfsext_attributes_block.h"
#include "libfsext_debug.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_attributes.h"

/* Reads the extended attributes block header data
 * Returns 1 if successful or -1 on error
 */
int libfsext_attributes_block_read_header_data(
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function     = "libfsext_attributes_block_read_header_data";
	uint32_t number_of_blocks = 0;
	uint32_t signature        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit      = 0;
#endif

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
	if( ( data_size < sizeof( fsext_attributes_header_ext2_t ) )
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
		 "%s: extended attributes block header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsext_attributes_header_ext2_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_attributes_header_ext2_t *) data )->signature,
	 signature );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_attributes_header_ext2_t *) data )->number_of_blocks,
	 number_of_blocks );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 signature );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_attributes_header_ext2_t *) data )->reference_count,
		 value_32bit );
		libcnotify_printf(
		 "%s: reference count\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of blocks\t\t: %" PRIu32 "\n",
		 function,
		 number_of_blocks );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_attributes_header_ext2_t *) data )->attributes_hash,
		 value_32bit );
		libcnotify_printf(
		 "%s: attributes hash\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( io_handle->format_version == 2 )
		 || ( io_handle->format_version == 3 ) )
		{
			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_attributes_header_ext2_t *) data )->unknown1,
			 16,
			 0 );
		}
		else if( io_handle->format_version == 4 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_attributes_header_ext4_t *) data )->checksum,
			 value_32bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_attributes_header_ext4_t *) data )->unknown1,
			 12,
			 0 );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( signature != 0xea020000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	if( number_of_blocks != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of blocks value out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the extended attributes block entries data
 * Returns 1 if successful or -1 on error
 */
int libfsext_attributes_block_read_entries_data(
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcdata_array_t *extended_attributes,
     libcerror_error_t **error )
{
	libfsext_attribute_values_t *attribute_values = NULL;
	static char *function                         = "libfsext_attributes_block_read_entries_data";
	size_t alignment_padding_size                 = 0;
	int attribute_index                           = 0;
	int entry_index                               = 0;

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
	if( ( data_size < sizeof( fsext_attributes_entry_t ) )
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
	if( data_offset >= ( data_size - sizeof( fsext_attributes_entry_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	while( data_offset < data_size )
	{
		if( data_offset >= ( data_size - sizeof( fsext_attributes_entry_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
		/* The list terminator consist of 4 0-byte values
		 */
		if( memory_compare(
		     &( data[ data_offset ] ),
		     "\x00\x00\x00\x00",
		     4 ) == 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: extended attributes entry: %d data:\n",
				 function,
				 attribute_index );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 sizeof( fsext_attributes_entry_t ),
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			break;
		}
		if( libfsext_attribute_values_initialize(
		     &attribute_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create attribute: %d values.",
			 function,
			 attribute_index );

			goto on_error;
		}
		if( libfsext_attribute_values_read_data(
		     attribute_values,
		     &( data[ data_offset ] ),
		     data_size - data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read attribute: %d values.",
			 function,
			 attribute_index );

			goto on_error;
		}
		data_offset += sizeof( fsext_attributes_entry_t ) + data[ data_offset ];

		alignment_padding_size = data_offset % 4;

		if( alignment_padding_size != 0 )
		{
			alignment_padding_size = 4 - alignment_padding_size;
		}
		if( alignment_padding_size > 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			data_offset += alignment_padding_size;
		}
		if( ( attribute_values->value_data_inode_number == 0 )
		 && ( attribute_values->value_data_size > 0 ) )
		{
			if( ( attribute_values->value_data_offset < sizeof( fsext_attributes_header_ext2_t ) )
			 || ( attribute_values->value_data_offset >= data_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid value data offset value out of bounds.",
				 function );

				goto on_error;
			}
			if( attribute_values->value_data_size > ( data_size - attribute_values->value_data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid value data size value out of bounds.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: attribute: %d value data:\n",
				 function,
				 attribute_index );
				libcnotify_print_data(
				 &( data[ attribute_values->value_data_offset ] ),
				 attribute_values->value_data_size,
				 0 );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			attribute_values->value_data = (uint8_t *) memory_allocate(
			                                            sizeof( uint8_t ) * attribute_values->value_data_size );

			if( attribute_values->value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create value data.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     attribute_values->value_data,
			     &( data[ attribute_values->value_data_offset ] ),
			     (size_t) attribute_values->value_data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy value data to attribute values.",
				 function );

				goto on_error;
			}
		}
		if( libcdata_array_append_entry(
		     extended_attributes,
		     &entry_index,
		     (intptr_t *) attribute_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append attribute: %d values to array.",
			 function,
			 attribute_index );

			goto on_error;
		}
		attribute_values = NULL;

		attribute_index++;
	}
	return( 1 );

on_error:
	if( attribute_values != NULL )
	{
		libfsext_attribute_values_free(
		 &attribute_values,
		 NULL );
	}
	libcdata_array_empty(
	 extended_attributes,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_attribute_values_free,
	 NULL );

	return( -1 );
}

/* Reads the extended attributes block from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_attributes_block_read_file_io_handle(
     libcdata_array_t *extended_attributes,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfsext_attributes_block_read_file_io_handle";
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
		 "%s: reading extended attributes block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
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
		 "%s: unable to read extended attributes block data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libfsext_attributes_block_read_header_data(
	     io_handle,
	     data,
	     (size_t) io_handle->block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extended attributes block header.",
		 function );

		goto on_error;
	}
	if( libfsext_attributes_block_read_entries_data(
	     data,
	     (size_t) io_handle->block_size,
	     sizeof( fsext_attributes_header_ext2_t ),
	     extended_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read extended attributes block entries.",
		 function );

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

