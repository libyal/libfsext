/*
 * Group descriptor functions
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

#include "libfsext_definitions.h"
#include "libfsext_group_descriptor.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_group_descriptor.h"

/* Creates a group descriptor
 * Make sure the value group_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_group_descriptor_initialize(
     libfsext_group_descriptor_t **group_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsext_group_descriptor_initialize";

	if( group_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid group descriptor.",
		 function );

		return( -1 );
	}
	if( *group_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid group descriptor value already set.",
		 function );

		return( -1 );
	}
	*group_descriptor = memory_allocate_structure(
	                     libfsext_group_descriptor_t );

	if( *group_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create group descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *group_descriptor,
	     0,
	     sizeof( libfsext_group_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear group descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *group_descriptor != NULL )
	{
		memory_free(
		 *group_descriptor );

		*group_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a group descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsext_group_descriptor_free(
     libfsext_group_descriptor_t **group_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libfsext_group_descriptor_free";

	if( group_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid group descriptor.",
		 function );

		return( -1 );
	}
	if( *group_descriptor != NULL )
	{
		memory_free(
		 *group_descriptor );

		*group_descriptor = NULL;
	}
	return( 1 );
}

/* Reads the group descriptor data
 * Returns 1 if successful or -1 on error
 */
int libfsext_group_descriptor_read_data(
     libfsext_group_descriptor_t *group_descriptor,
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function             = "libfsext_group_descriptor_read_data";
	size_t group_descriptor_data_size = 0;
	uint64_t value_64bit              = 0;
	uint32_t value_32bit              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit              = 0;
#endif

	if( group_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid group descriptor.",
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
	if( io_handle->format_version < 4 )
	{
		group_descriptor_data_size = sizeof( fsext_group_descriptor_ext2_t );
	}
	else if( ( ( io_handle->incompatible_features_flags & LIBFSEXT_INCOMPATIBLE_FEATURES_FLAG_64BIT_SUPPORT ) != 0 )
	      && ( io_handle->group_descriptor_size > 32 ) )
	{
		group_descriptor_data_size = 64;
	}
	else
	{
		group_descriptor_data_size = 32;
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
	if( data_size < group_descriptor_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: group descriptor data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 group_descriptor_data_size,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->block_bitmap_block_number,
	 group_descriptor->block_bitmap_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->inode_bitmap_block_number,
	 group_descriptor->inode_bitmap_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->inode_table_block_number,
	 group_descriptor->inode_table_block_number );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->number_of_unallocated_blocks,
	 group_descriptor->number_of_unallocated_blocks );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->number_of_unallocated_inodes,
	 group_descriptor->number_of_unallocated_inodes );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_group_descriptor_ext2_t *) data )->number_of_directories,
	 group_descriptor->number_of_directories );

	if( io_handle->format_version < 4 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block bitmap block number\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->block_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode bitmap block number\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode table block number\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_table_block_number );

			libcnotify_printf(
			 "%s: number of unallocated blocks\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_blocks );

			libcnotify_printf(
			 "%s: number of unallocated inodes\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_inodes );

			libcnotify_printf(
			 "%s: number of directories\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_directories );

			libcnotify_printf(
			 "%s: padding1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_group_descriptor_ext2_t *) data )->padding1,
			 2,
			 0 );

			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_group_descriptor_ext2_t *) data )->unknown1,
			 12,
			 0 );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	else
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_group_descriptor_ext4_t *) data )->exclude_bitmap_block_number_lower,
		 group_descriptor->exclude_bitmap_block_number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_group_descriptor_ext4_t *) data )->block_bitmap_checksum_lower,
		 group_descriptor->block_bitmap_checksum );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_group_descriptor_ext4_t *) data )->inode_bitmap_checksum_lower,
		 group_descriptor->inode_bitmap_checksum );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unused_inodes_lower,
		 group_descriptor->number_of_unused_inodes );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block bitmap block number (lower)\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->block_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode bitmap block number (lower)\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode table block number (lower)\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_table_block_number );

			libcnotify_printf(
			 "%s: number of unallocated blocks (lower)\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_blocks );

			libcnotify_printf(
			 "%s: number of unallocated inodes (lower)\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_inodes );

			libcnotify_printf(
			 "%s: number of directories (lower)\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_directories );

			libcnotify_printf(
			 "%s: exclude bitmap block number (lower)\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->exclude_bitmap_block_number );

			libcnotify_printf(
			 "%s: block bitmap checksum (lower)\t\t: 0x%04" PRIx32 "\n",
			 function,
			 group_descriptor->block_bitmap_checksum );

			libcnotify_printf(
			 "%s: inode bitmap checksum (lower)\t\t: 0x%04" PRIx32 "\n",
			 function,
			 group_descriptor->inode_bitmap_checksum );

			libcnotify_printf(
			 "%s: number of unused inodes (lower)\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unused_inodes );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->checksum,
			 value_16bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		if( ( ( io_handle->incompatible_features_flags & LIBFSEXT_INCOMPATIBLE_FEATURES_FLAG_64BIT_SUPPORT ) != 0 )
		 && ( io_handle->group_descriptor_size > 32 ) )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->block_bitmap_block_number_upper,
				 value_32bit );
				libcnotify_printf(
				 "%s: block bitmap block number (upper)\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->inode_bitmap_block_number_upper,
				 value_32bit );
				libcnotify_printf(
				 "%s: inode bitmap block number (upper)\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->inode_table_block_number_upper,
				 value_32bit );
				libcnotify_printf(
				 "%s: inode table block number (upper)\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unallocated_blocks_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: number of unallocated blocks (upper)\t: %" PRIu16 "\n",
				 function,
				 value_16bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unallocated_inodes_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: number of unallocated inodes (upper)\t: %" PRIu16 "\n",
				 function,
				 value_16bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->number_of_directories_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: number of directories (upper)\t\t: %" PRIu16 "\n",
				 function,
				 value_16bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unused_inodes_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: number of unused inodes (upper)\t\t: %" PRIu16 "\n",
				 function,
				 value_16bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->exclude_bitmap_block_number_upper,
				 value_32bit );
				libcnotify_printf(
				 "%s: exclude bitmap block number (upper)\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->block_bitmap_checksum_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: block bitmap checksum (upper)\t\t: 0x%04" PRIx16 "\n",
				 function,
				 value_16bit );

				byte_stream_copy_to_uint16_little_endian(
				 ( (fsext_group_descriptor_ext4_t *) data )->inode_bitmap_checksum_upper,
				 value_16bit );
				libcnotify_printf(
				 "%s: inode bitmap checksum (upper)\t\t: 0x%04" PRIx16 "\n",
				 function,
				 value_16bit );

				libcnotify_printf(
				 "%s: unknown1:\n",
				 function );
				libcnotify_print_data(
				 ( (fsext_group_descriptor_ext4_t *) data )->unknown1,
				 4,
				 0 );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->block_bitmap_block_number_upper,
			 value_64bit );

			group_descriptor->block_bitmap_block_number |= value_64bit << 32;

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->inode_bitmap_block_number_upper,
			 value_64bit );

			group_descriptor->inode_bitmap_block_number |= value_64bit << 32;

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->inode_table_block_number_upper,
			 value_64bit );

			group_descriptor->inode_table_block_number |= value_64bit << 32;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unallocated_blocks_upper,
			 value_32bit );

			group_descriptor->number_of_unallocated_blocks |= value_32bit << 16;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unallocated_inodes_upper,
			 value_32bit );

			group_descriptor->number_of_unallocated_inodes |= value_32bit << 16;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->number_of_directories_upper,
			 value_32bit );

			group_descriptor->number_of_directories |= value_32bit << 16;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->number_of_unused_inodes_upper,
			 value_32bit );

			group_descriptor->number_of_unused_inodes |= value_32bit << 16;

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->exclude_bitmap_block_number_upper,
			 value_64bit );

			group_descriptor->exclude_bitmap_block_number |= value_64bit << 32;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->block_bitmap_checksum_upper,
			 value_32bit );

			group_descriptor->block_bitmap_checksum |= value_32bit << 16;

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) data )->inode_bitmap_checksum_upper,
			 value_32bit );

			group_descriptor->inode_bitmap_checksum |= value_32bit << 16;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: block bitmap block number\t\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->block_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode bitmap block number\t\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_bitmap_block_number );

			libcnotify_printf(
			 "%s: inode table block number\t\t\t: %" PRIu64 "\n",
			 function,
			 group_descriptor->inode_table_block_number );

			libcnotify_printf(
			 "%s: number of unallocated blocks\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_blocks );

			libcnotify_printf(
			 "%s: number of unallocated inodes\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unallocated_inodes );

			libcnotify_printf(
			 "%s: number of directories\t\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_directories );

			libcnotify_printf(
			 "%s: number of unused inodes\t\t\t: %" PRIu32 "\n",
			 function,
			 group_descriptor->number_of_unused_inodes );

			libcnotify_printf(
			 "%s: block bitmap checksum\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 group_descriptor->block_bitmap_checksum );

			libcnotify_printf(
			 "%s: inode bitmap checksum\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 group_descriptor->inode_bitmap_checksum );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	return( 1 );
}

/* Reads the group descriptor from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_group_descriptor_read_file_io_handle(
     libfsext_group_descriptor_t *group_descriptor,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t *data                     = NULL;
	static char *function             = "libfsext_group_descriptor_read_file_io_handle";
	size_t group_descriptor_data_size = 0;
	ssize_t read_count                = 0;

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
	if( io_handle->format_version < 4 )
	{
		group_descriptor_data_size = sizeof( fsext_group_descriptor_ext2_t );
	}
	else if( ( ( io_handle->incompatible_features_flags & LIBFSEXT_INCOMPATIBLE_FEATURES_FLAG_64BIT_SUPPORT ) != 0 )
	      && ( io_handle->group_descriptor_size > 32 ) )
	{
		group_descriptor_data_size = 64;
	}
	else
	{
		group_descriptor_data_size = 32;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * group_descriptor_data_size );

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
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data,
	              group_descriptor_data_size,
	              error );

	if( read_count != (ssize_t) group_descriptor_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read group descriptor.",
		 function );

		goto on_error;
	}
	if( libfsext_group_descriptor_read_data(
	     group_descriptor,
	     io_handle,
	     data,
	     group_descriptor_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read group descriptor.",
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

