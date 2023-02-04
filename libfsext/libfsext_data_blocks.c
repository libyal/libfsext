/*
 * Data blocks functions
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
#include <types.h>

#include "libfsext_block.h"
#include "libfsext_data_blocks.h"
#include "libfsext_definitions.h"
#include "libfsext_extent.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

/* Retrieves the last extent
 * Returns 1 if successful or -1 on error
 */
int libfsext_data_blocks_get_last_extent(
     libcdata_array_t *extents_array,
     libfsext_extent_t **last_extent,
     libcerror_error_t **error )
{
	static char *function = "libfsext_data_blocks_get_last_extent";
	int number_of_extents = 0;

	if( last_extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid last extent.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     extents_array,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		return( -1 );
	}
	if( number_of_extents == 0 )
	{
		*last_extent = NULL;
	}
	else if( libcdata_array_get_entry_by_index(
	          extents_array,
	          number_of_extents - 1,
	          (intptr_t **) last_extent,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent: %d.",
		 function,
		 number_of_extents - 1 );

		return( -1 );
	}
	return( 1 );
}

/* Reads the inode data reference
 * Returns 1 if successful or -1 on error
 */
int libfsext_data_blocks_read_inode_data_reference(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsext_extent_t *last_extent      = NULL;
	static char *function               = "libfsext_data_blocks_read_inode_data_reference";
	uint32_t block_number               = 0;
	uint32_t extent_number_of_blocks    = 0;
	uint32_t logical_block_number       = 0;
	uint32_t number_of_blocks_per_block = 0;

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
	if( data_size != 60 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	number_of_blocks_per_block = ( io_handle->block_size / 4 );

	/* Passing the 1 + largest possible block number here 0xffffffff
	 */
	if( libfsext_data_blocks_read_data(
	     extents_array,
	     io_handle,
	     file_io_handle,
	     number_of_blocks,
	     (uint64_t) 0x100000000UL,
	     data,
	     48,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read direct block numbers from data reference.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ 48 ] ),
	 block_number );

	if( block_number == 0 )
	{
		if( libfsext_data_blocks_get_last_extent(
		     extents_array,
		     &last_extent,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve last extent.",
			 function );

			return( -1 );
		}
		if( last_extent == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing last extent.",
			 function );

			return( -1 );
		}
		logical_block_number = last_extent->logical_block_number + last_extent->number_of_blocks;

		if( logical_block_number < number_of_blocks )
		{
			extent_number_of_blocks = number_of_blocks_per_block;

			if( extent_number_of_blocks > ( number_of_blocks - logical_block_number ) )
			{
				extent_number_of_blocks = number_of_blocks - logical_block_number;
			}
			last_extent->number_of_blocks += extent_number_of_blocks;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: logical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->logical_block_number );

				libcnotify_printf(
				 "%s: physical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->physical_block_number );

				libcnotify_printf(
				 "%s: number of blocks\t: %" PRIu64 "\n",
				 function,
				 last_extent->number_of_blocks );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		}
	}
	else
	{
		if( libfsext_data_blocks_read_file_io_handle(
		     extents_array,
		     io_handle,
		     file_io_handle,
		     number_of_blocks,
		     block_number,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read indirect block: %" PRIu32 ".",
			 function,
			 block_number );

			return( -1 );
		}
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ 52 ] ),
	 block_number );

	if( block_number == 0 )
	{
		if( libfsext_data_blocks_get_last_extent(
		     extents_array,
		     &last_extent,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve last extent.",
			 function );

			return( -1 );
		}
		if( last_extent == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing last extent.",
			 function );

			return( -1 );
		}
		logical_block_number = last_extent->logical_block_number + last_extent->number_of_blocks;

		if( logical_block_number < number_of_blocks )
		{
			extent_number_of_blocks = number_of_blocks_per_block * number_of_blocks_per_block;

			if( extent_number_of_blocks > ( number_of_blocks - logical_block_number ) )
			{
				extent_number_of_blocks = number_of_blocks - logical_block_number;
			}
			last_extent->number_of_blocks += extent_number_of_blocks;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: logical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->logical_block_number );

				libcnotify_printf(
				 "%s: physical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->physical_block_number );

				libcnotify_printf(
				 "%s: number of blocks\t: %" PRIu64 "\n",
				 function,
				 last_extent->number_of_blocks );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		}
	}
	else
	{
		if( libfsext_data_blocks_read_file_io_handle(
		     extents_array,
		     io_handle,
		     file_io_handle,
		     number_of_blocks,
		     block_number,
		     2,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read double indirect block: %" PRIu32 ".",
			 function,
			 block_number );

			return( -1 );
		}
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ 56 ] ),
	 block_number );

	if( block_number == 0 )
	{
		if( libfsext_data_blocks_get_last_extent(
		     extents_array,
		     &last_extent,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve last extent.",
			 function );

			return( -1 );
		}
		if( last_extent == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing last extent.",
			 function );

			return( -1 );
		}
		logical_block_number = last_extent->logical_block_number + last_extent->number_of_blocks;

		if( logical_block_number < number_of_blocks )
		{
			extent_number_of_blocks = number_of_blocks_per_block * number_of_blocks_per_block * number_of_blocks_per_block;

			if( extent_number_of_blocks > ( number_of_blocks - logical_block_number ) )
			{
				extent_number_of_blocks = number_of_blocks - logical_block_number;
			}
			last_extent->number_of_blocks += extent_number_of_blocks;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: logical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->logical_block_number );

				libcnotify_printf(
				 "%s: physical block number\t: %" PRIu64 "\n",
				 function,
				 last_extent->physical_block_number );

				libcnotify_printf(
				 "%s: number of blocks\t: %" PRIu64 "\n",
				 function,
				 last_extent->number_of_blocks );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		}
	}
	else
	{
		if( libfsext_data_blocks_read_file_io_handle(
		     extents_array,
		     io_handle,
		     file_io_handle,
		     number_of_blocks,
		     block_number,
		     3,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read triple indirect block: %" PRIu32 ".",
			 function,
			 block_number );

			return( -1 );
		}
	}
	return( 1 );
}

/* Reads direct and indirect block data
 * Returns 1 if successful or -1 on error
 */
int libfsext_data_blocks_read_data(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     uint64_t block_number,
     const uint8_t *data,
     size_t data_size,
     int depth,
     libcerror_error_t **error )
{
	libfsext_extent_t *extent           = NULL;
	libfsext_extent_t *last_extent      = NULL;
	static char *function               = "libfsext_data_blocks_read_data";
	size_t data_offset                  = 0;
	uint32_t extent_number_of_blocks    = 0;
	uint32_t number_of_blocks_per_block = 0;
	uint32_t sub_block_number           = 0;
	uint32_t sub_logical_block_number   = 0;
	uint8_t create_new_extent           = 0;
	uint8_t extend_last_extent          = 0;
	int depth_iterator                  = 0;
	int entry_index                     = 0;

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
	if( ( data_size == 0 )
	 || ( data_size > (size_t) SSIZE_MAX )
	 || ( ( data_size % 4 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( depth < 0 )
	 || ( depth > 3 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid depth value out of bounds.",
		 function );

		return( -1 );
	}
	number_of_blocks_per_block = ( io_handle->block_size / 4 );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block data at depth: %d:\n",
		 function,
		 depth );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libfsext_data_blocks_get_last_extent(
	     extents_array,
	     &last_extent,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve last extent.",
		 function );

		goto on_error;
	}
	if( last_extent != NULL )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: logical block number\t\t\t: %" PRIu64 "\n",
			 function,
			 last_extent->logical_block_number );

			libcnotify_printf(
			 "%s: physical block number\t\t\t: %" PRIu64 "\n",
			 function,
			 last_extent->physical_block_number );

			libcnotify_printf(
			 "%s: number of blocks\t\t\t: %" PRIu64 "\n",
			 function,
			 last_extent->number_of_blocks );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		sub_logical_block_number = last_extent->logical_block_number + last_extent->number_of_blocks;
	}
	while( data_offset < data_size )
	{
		if( sub_logical_block_number >= number_of_blocks )
		{
			break;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset ] ),
		 sub_block_number );

		data_offset += 4;

		if( (uint64_t) sub_block_number == block_number )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid sub block number value out of bounds.",
			 function );

			goto on_error;
		}
		create_new_extent       = 1;
		extend_last_extent      = 0;
		extent_number_of_blocks = 1;

		if( sub_block_number == 0 )
		{
			for( depth_iterator = 0;
			     depth_iterator < depth;
			     depth_iterator++ )
			{
				extent_number_of_blocks *= number_of_blocks_per_block;
			}
			if( extent_number_of_blocks > ( number_of_blocks - sub_logical_block_number ) )
			{
				extent_number_of_blocks = number_of_blocks - sub_logical_block_number;
			}
			if( ( last_extent != NULL )
			 && ( ( last_extent->range_flags & LIBFSEXT_EXTENT_FLAG_IS_SPARSE ) != 0 ) )
			{
				extend_last_extent = 1;
			}
		}
		else if( depth > 0 )
		{
			if( libfsext_data_blocks_read_file_io_handle(
			     extents_array,
			     io_handle,
			     file_io_handle,
			     number_of_blocks,
			     sub_block_number,
			     depth,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read indirect block: %" PRIu32 " at depth: %d.",
				 function,
				 sub_block_number,
				 depth );

				goto on_error;
			}
			if( libfsext_data_blocks_get_last_extent(
			     extents_array,
			     &last_extent,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve last extent.",
				 function );

				goto on_error;
			}
			sub_logical_block_number = last_extent->logical_block_number + last_extent->number_of_blocks;

			create_new_extent = 0;
		}
		else if( ( last_extent != NULL )
		      && ( last_extent->physical_block_number == ( sub_block_number - last_extent->number_of_blocks ) ) )
		{
			extend_last_extent = 1;
		}
		if( extend_last_extent != 0 )
		{
			if( last_extent->number_of_blocks > ( ( (uint64_t) UINT64_MAX / io_handle->block_size ) - extent_number_of_blocks ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid last extent - number of blocks value out of bounds.",
				 function );

				goto on_error;
			}
			last_extent->number_of_blocks += extent_number_of_blocks;
		}
		else if( create_new_extent != 0 )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( ( libcnotify_verbose != 0 )
			 && ( last_extent != NULL )
			 && ( data_offset > 4 ) )
			{
				libcnotify_printf(
				 "\n" );

				libcnotify_printf(
				 "%s: logical block number\t\t\t: %" PRIu64 "\n",
				 function,
				 last_extent->logical_block_number );

				libcnotify_printf(
				 "%s: physical block number\t\t\t: %" PRIu64 "\n",
				 function,
				 last_extent->physical_block_number );

				libcnotify_printf(
				 "%s: number of blocks\t\t\t: %" PRIu64 "\n",
				 function,
				 last_extent->number_of_blocks );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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
			extent->logical_block_number  = sub_logical_block_number;
			extent->physical_block_number = sub_block_number;
			extent->number_of_blocks      = extent_number_of_blocks;

			if( sub_block_number == 0 )
			{
				extent->range_flags = LIBFSEXT_EXTENT_FLAG_IS_SPARSE;
			}
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
			last_extent = extent;
			extent      = NULL;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block number at depth: %d\t\t: %" PRIu32 "\n",
			 function,
			 depth,
			 sub_block_number );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		sub_logical_block_number++;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( ( libcnotify_verbose != 0 )
	 && ( last_extent != NULL ) )
	{
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: logical block number\t\t\t: %" PRIu64 "\n",
		 function,
		 last_extent->logical_block_number );

		libcnotify_printf(
		 "%s: physical block number\t\t\t: %" PRIu64 "\n",
		 function,
		 last_extent->physical_block_number );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu64 "\n",
		 function,
		 last_extent->number_of_blocks );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
	if( extent != NULL )
	{
		libfsext_extent_free(
		 &extent,
		 NULL );
	}
	return( -1 );
}

/* Reads an indirect block
 * Returns 1 if successful or -1 on error
 */
int libfsext_data_blocks_read_file_io_handle(
     libcdata_array_t *extents_array,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint64_t number_of_blocks,
     uint32_t block_number,
     int depth,
     libcerror_error_t **error )
{
	libfsext_block_t *block = NULL;
	static char *function   = "libfsext_data_blocks_read_file_io_handle";
	off64_t block_offset    = 0;

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
	block_offset = (off64_t) block_number * io_handle->block_size;
	
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading indirect block: %" PRIu32 " at depth: %d of size: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 block_number,
		 depth,
		 io_handle->block_size,
		 block_offset,
		 block_offset );
	}
#endif
	if( libfsext_block_initialize(
	     &block,
	     (size_t) io_handle->block_size,
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
		 "%s: unable to read indirect block: %" PRIu32 ".",
		 function,
		 block_number );

		goto on_error;
	}
	if( libfsext_data_blocks_read_data(
	     extents_array,
	     io_handle,
	     file_io_handle,
	     number_of_blocks,
	     (uint64_t) block_number,
	     block->data,
	     (size_t) io_handle->block_size,
	     depth - 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read indirect block: %" PRIu32 " at depth: %d.",
		 function,
		 block_number,
		 depth );

		goto on_error;
	}
	if( libfsext_block_free(
	     &block,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free block.",
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

