/*
 * Superblock functions
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsext_debug.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdatetime.h"
#include "libfsext_libfguid.h"
#include "libfsext_superblock.h"

#include "fsext_superblock.h"

const char *fsext_superblock_signature = "\x53\xef";

/* Creates a superblock
 * Make sure the value superblock is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_superblock_initialize(
     libfsext_superblock_t **superblock,
     libcerror_error_t **error )
{
	static char *function = "libfsext_superblock_initialize";

	if( superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid superblock.",
		 function );

		return( -1 );
	}
	if( *superblock != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid superblock value already set.",
		 function );

		return( -1 );
	}
	*superblock = memory_allocate_structure(
	               libfsext_superblock_t );

	if( *superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create superblock.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *superblock,
	     0,
	     sizeof( libfsext_superblock_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear superblock.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *superblock != NULL )
	{
		memory_free(
		 *superblock );

		*superblock = NULL;
	}
	return( -1 );
}

/* Frees a superblock
 * Returns 1 if successful or -1 on error
 */
int libfsext_superblock_free(
     libfsext_superblock_t **superblock,
     libcerror_error_t **error )
{
	static char *function = "libfsext_superblock_free";

	if( superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid superblock.",
		 function );

		return( -1 );
	}
	if( *superblock != NULL )
	{
		memory_free(
		 *superblock );

		*superblock = NULL;
	}
	return( 1 );
}

/* Reads the superblock data
 * Returns 1 if successful or -1 on error
 */
int libfsext_superblock_read_data(
     libfsext_superblock_t *superblock,
     const uint8_t *data,
     size_t data_size,
     int *format_version,
     uint32_t *number_of_block_groups,
     libcerror_error_t **error )
{
	static char *function                     = "libfsext_superblock_read_data";
	uint32_t number_of_blocks_per_block_group = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                      = 0;
	uint16_t value_16bit                      = 0;
#endif

	if( superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid superblock.",
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
	if( data_size < sizeof( fsext_superblock_ext2_t ) )
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
	if( format_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid format version.",
		 function );

		return( -1 );
	}
	if( number_of_block_groups == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of block groups.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: superblock data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsext_superblock_ext2_t ),
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( memory_compare(
	     ( (fsext_superblock_ext2_t *) data )->signature,
	     fsext_superblock_signature,
	     2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_inodes,
	 superblock->number_of_inodes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_blocks,
	 superblock->number_of_blocks );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_reserved_blocks,
	 superblock->number_of_reserved_blocks );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_unallocated_blocks,
	 superblock->number_of_unallocated_blocks );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_unallocated_inodes,
	 superblock->number_of_unallocated_inodes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->block_size,
	 superblock->block_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_blocks_per_block_group,
	 number_of_blocks_per_block_group );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->format_revision,
	 superblock->format_revision );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->number_of_inodes_per_block_group,
	 superblock->number_of_inodes_per_block_group );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->last_mount_time,
	 superblock->last_mount_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_superblock_ext2_t *) data )->last_written_time,
	 superblock->last_written_time );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: number of inodes\t\t\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_inodes );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_blocks );

		libcnotify_printf(
		 "%s: number of reserved blocks\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_reserved_blocks );

		libcnotify_printf(
		 "%s: number of unallocated blocks\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_unallocated_blocks );

		libcnotify_printf(
		 "%s: number of unallocated inodes\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_unallocated_inodes );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->first_data_block_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: first data block number\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: block size\t\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << superblock->block_size,
		 superblock->block_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->fragment_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragment size\t\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of blocks per block group\t\t: %" PRIu32 "\n",
		 function,
		 number_of_blocks_per_block_group );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->number_of_fragments_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of fragments per block group\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of inodes per block group\t\t: %" PRIu32 "\n",
		 function,
		 superblock->number_of_inodes_per_block_group );

		if( libfsext_debug_print_posix_time_value(
		     function,
		     "last mount time\t\t\t\t",
		     ( (fsext_superblock_ext2_t *) data )->last_mount_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print posix time value.",
			 function );

			return( -1 );
		}
		if( libfsext_debug_print_posix_time_value(
		     function,
		     "last written time\t\t\t",
		     ( (fsext_superblock_ext2_t *) data )->last_written_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print posix time value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: mount count\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->maximum_mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum mount count\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: signature\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 ( (fsext_superblock_ext2_t *) data )->signature[ 0 ],
		 ( (fsext_superblock_ext2_t *) data )->signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->file_system_state_flags,
		 value_16bit );
		libcnotify_printf(
		 "%s: file system state flags\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );
		libfsext_debug_print_file_system_state_flags(
		 value_16bit );
		libcnotify_printf(
		 "\n" );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->error_handling_status,
		 value_16bit );
		libcnotify_printf(
		 "%s: error handling status\t\t\t: %" PRIu16 " (%s)\n",
		 function,
		 value_16bit,
		 libfsext_debug_print_error_handling_status(
		  value_16bit ) );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->minor_format_revision,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor format revision\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		if( libfsext_debug_print_posix_time_value(
		     function,
		     "last consistency check time\t\t",
		     ( (fsext_superblock_ext2_t *) data )->last_consistency_check_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print posix time value.",
			 function );

			return( -1 );
		}

/* TODO print interval as duration? */
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->consistency_check_interval,
		 value_32bit );
		libcnotify_printf(
		 "%s: consistency check interval\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creator operating system\t\t\t: %" PRIu32 " (%s)\n",
		 function,
		 value_32bit,
		 libfsext_debug_print_creator_operating_system(
		  value_32bit ) );

		libcnotify_printf(
		 "%s: format revision\t\t\t\t: %" PRIu32 "\n",
		 function,
		 superblock->format_revision );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->reserved_block_user_identifier,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block user identifier\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->reserved_block_group_identifier,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block group identifier\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	superblock->block_size = 1024 << superblock->block_size;

	if( superblock->format_revision > 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format revision: %" PRIu32 ".",
		 function,
		 superblock->format_revision );

		return( -1 );
	}
	if( superblock->format_revision == 1 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->compatible_features_flags,
		 superblock->compatible_features_flags );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->incompatible_features_flags,
		 superblock->incompatible_features_flags );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->read_only_compatible_features_flags,
		 superblock->read_only_compatible_features_flags );

		if( memory_copy(
		     superblock->file_system_identifier,
		     ( (fsext_superblock_ext2_t *) data )->file_system_identifier,
		     16 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy file system identifier.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     superblock->volume_label,
		     ( (fsext_superblock_ext2_t *) data )->volume_label,
		     16 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy volume label.",
			 function );

			return( -1 );
		}
		if( memory_copy(
		     superblock->last_mounted_path,
		     ( (fsext_superblock_ext2_t *) data )->last_mounted_path,
		     64 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy last mounted path.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_superblock_ext2_t *) data )->first_non_reserved_inode,
			 value_32bit );
			libcnotify_printf(
			 "%s: first non-reserved inode\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_superblock_ext2_t *) data )->inode_size,
			 value_16bit );
			libcnotify_printf(
			 "%s: inode size\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_superblock_ext2_t *) data )->block_group,
			 value_16bit );
			libcnotify_printf(
			 "%s: block group\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			libcnotify_printf(
			 "%s: compatible features flags\t\t: 0x%08" PRIx32 "\n",
			 function,
			 superblock->compatible_features_flags );
			libfsext_debug_print_compatible_features_flags(
			 superblock->compatible_features_flags );
			libcnotify_printf(
			 "\n" );

			libcnotify_printf(
			 "%s: incompatible features flags\t\t: 0x%08" PRIx32 "\n",
			 function,
			 superblock->incompatible_features_flags );
			libfsext_debug_print_incompatible_features_flags(
			 superblock->incompatible_features_flags );
			libcnotify_printf(
			 "\n" );

			libcnotify_printf(
			 "%s: read-only compatible features flags\t: 0x%08" PRIx32 "\n",
			 function,
			 superblock->read_only_compatible_features_flags );
			libfsext_debug_print_read_only_compatible_features_flags(
			 superblock->read_only_compatible_features_flags );
			libcnotify_printf(
			 "\n" );

			if( libfsext_debug_print_guid_value(
			     function,
			     "file system identifier\t\t\t",
			     ( (fsext_superblock_ext2_t *) data )->file_system_identifier,
			     16,
			     LIBFGUID_ENDIAN_LITTLE,
			     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print GUID value.",
				 function );

				return( -1 );
			}

/* TODO print as string */
			libcnotify_printf(
			 "%s: volume label:\n",
			 function );
			libcnotify_print_data(
			 superblock->volume_label,
			 16,
			 0 );

/* TODO print as string */
			libcnotify_printf(
			 "%s: last mounted path:\n",
			 function );
			libcnotify_print_data(
			 superblock->last_mounted_path,
			 64,
			 0 );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_superblock_ext2_t *) data )->algorithm_usage_bitmap,
			 value_32bit );
			libcnotify_printf(
			 "%s: algorithm usage bitmap\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	if( ( ( superblock->compatible_features_flags & 0x00000200 ) != 0 )
	 || ( ( superblock->incompatible_features_flags & 0x0001f7c0 ) != 0 )
	 || ( ( superblock->read_only_compatible_features_flags & 0x00000378 ) != 0 ) )
	{
		*format_version = 4;
	}
	else if( ( ( superblock->compatible_features_flags & 0x00000004 ) != 0 )
	      || ( ( superblock->incompatible_features_flags & 0x0000000c ) != 0 ) )
	{
		*format_version = 3;
	}
	else
	{
		*format_version = 2;
	}
	if( ( superblock->compatible_features_flags & 0x00000001UL ) != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: number of pre-allocated blocks per file\t: %" PRIu8 "\n",
			 function,
			 ( (fsext_superblock_ext2_t *) data )->number_of_pre_allocated_blocks_per_file );

			libcnotify_printf(
			 "%s: number of pre-allocated blocks per directory\t: %" PRIu8 "\n",
			 function,
			 ( (fsext_superblock_ext2_t *) data )->number_of_pre_allocated_blocks_per_directory );

			libcnotify_printf(
			 "%s: padding1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_superblock_ext2_t *) data )->padding1,
			 2,
			 0 );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfsext_debug_print_guid_value(
		     function,
		     "journal identifier\t\t\t",
		     ( (fsext_superblock_ext2_t *) data )->journal_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->journal_inode_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: journal inode number\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->journal_device,
		 value_32bit );
		libcnotify_printf(
		 "%s: journal device\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->orphan_inode_list_head,
		 value_32bit );
		libcnotify_printf(
		 "%s: orphan inode list head\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: HTREE hash seed:\n",
		 function );
		libcnotify_print_data(
		 ( (fsext_superblock_ext2_t *) data )->htree_hash_seed,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: default hash version\t\t\t: %" PRIu8 "\n",
		 function,
		 ( (fsext_superblock_ext2_t *) data )->default_hash_version );

		libcnotify_printf(
		 "%s: padding2:\n",
		 function );
		libcnotify_print_data(
		 ( (fsext_superblock_ext2_t *) data )->padding2,
		 3,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->default_mount_options,
		 value_32bit );
		libcnotify_printf(
		 "%s: default mount options\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_superblock_ext2_t *) data )->first_metadata_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: first metadata block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( *format_version == 4 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libfsext_debug_print_posix_time_value(
			     function,
			     "file system creation time\t\t",
			     ( (fsext_superblock_ext4_t *) data )->file_system_creation_time,
			     4,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print posix time value.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "%s: backup journal inodes:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_superblock_ext4_t *) data )->backup_journal_inodes,
			 68,
			 0 );

/* TODO print remaining values */
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}

#if defined( HAVE_DEBUG_OUTPUT )
	if( *format_version < 4 )
	{
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: padding3:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_superblock_ext2_t *) data )->padding3,
			 3,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( superblock->number_of_blocks == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of blocks value out of bounds.",
		 function );

		return( -1 );
	}
	if( number_of_blocks_per_block_group == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of blocks per block group value out of bounds.",
		 function );

		return( -1 );
	}
	*number_of_block_groups = superblock->number_of_blocks / number_of_blocks_per_block_group;

	if( ( superblock->number_of_blocks % number_of_blocks_per_block_group ) != 0 )
	{
		*number_of_block_groups += 1;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu32 "\n",
		 function,
		 *format_version );

		libcnotify_printf(
		 "%s: number of block groups\t\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_block_groups );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the superblock from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_superblock_read_file_io_handle(
     libfsext_superblock_t *superblock,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     int *format_version,
     uint32_t *number_of_block_groups,
     libcerror_error_t **error )
{
	uint8_t data[ 1024 ];

	static char *function = "libfsext_superblock_read_file_io_handle";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading superblock at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
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
		 "%s: unable to seek superblock offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data,
	              1024,
	              error );

	if( read_count != (ssize_t) 1024 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read superblock at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libfsext_superblock_read_data(
	     superblock,
	     data,
	     1024,
	     format_version,
	     number_of_block_groups,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read superblock at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	return( 1 );
}

