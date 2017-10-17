/*
 * Inode functions
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsext_debug.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfcache.h"
#include "libfsext_libfdata.h"
#include "libfsext_libfdatetime.h"
#include "libfsext_unused.h"

#include "fsext_inode.h"

uint8_t empty_inode_data[ sizeof( fsext_inode_ext4_t ) ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00 };

/* Creates a inode
 * Make sure the value inode is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_initialize(
     libfsext_inode_t **inode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_initialize";

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
	if( *inode != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid inode value already set.",
		 function );

		return( -1 );
	}
	*inode = memory_allocate_structure(
	          libfsext_inode_t );

	if( *inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create inode.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *inode,
	     0,
	     sizeof( libfsext_inode_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear inode.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *inode != NULL )
	{
		memory_free(
		 *inode );

		*inode = NULL;
	}
	return( -1 );
}

/* Frees a inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_free(
     libfsext_inode_t **inode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_free";

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
	if( *inode != NULL )
	{
		memory_free(
		 *inode );

		*inode = NULL;
	}
	return( 1 );
}

/* Clones an inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_clone(
     libfsext_inode_t **destination_inode,
     libfsext_inode_t *source_inode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_clone";

	if( destination_inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode.",
		 function );

		return( -1 );
	}
	if( *destination_inode != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination inode value already set.",
		 function );

		return( -1 );
	}
	if( source_inode == NULL )
	{
		*destination_inode = source_inode;

		return( 1 );
	}
	*destination_inode = memory_allocate_structure(
	                      libfsext_inode_t );

	if( destination_inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination inode.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_inode,
	     source_inode,
	     sizeof( libfsext_inode_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy source to destination inode.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_inode != NULL )
	{
		memory_free(
		 *destination_inode );

		*destination_inode = NULL;
	}
	return( -1 );
}

/* Reads the inode data
 * Returns 1 if successful, 0 if the inode is empty or -1 on error
 */
int libfsext_inode_read_data(
     libfsext_inode_t *inode,
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function             = "libfsext_inode_read_data";
	size_t data_offset                = 0;
	size_t inode_data_size            = 0;
	uint64_t value_64bit              = 0;
	uint32_t value_32bit              = 0;
	uint8_t direct_block_number_index = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit              = 0;
#endif

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
	if( io_handle->format_version == 4 )
	{
		inode_data_size = sizeof( fsext_inode_ext4_t );
	}
	else if( io_handle->format_version == 3 )
	{
		inode_data_size = sizeof( fsext_inode_ext3_t );
	}
	else
	{
		inode_data_size = sizeof( fsext_inode_ext2_t );
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
	if( data_size < inode_data_size )
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
	if( memory_compare(
	     empty_inode_data,
	     data,
	     data_size ) == 0 )
	{
		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: inode data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->file_mode,
	 inode->file_mode );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->user_identifier,
	 inode->user_identifier );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->data_size,
	 inode->data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->access_time,
	 inode->access_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->inode_change_time,
	 inode->inode_change_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->modification_time,
	 inode->modification_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->deletion_time,
	 inode->deletion_time );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->group_identifier,
	 inode->group_identifier );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->links_count,
	 inode->links_count );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->blocks_count,
	 inode->blocks_count );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->flags,
	 inode->flags );

	data_offset = 0;

	for( direct_block_number_index = 0;
	     direct_block_number_index < 12;
	     direct_block_number_index++ )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( ( ( (fsext_inode_ext2_t *) data )->direct_block_numbers )[ data_offset ] ),
		 ( inode->direct_block_number )[ direct_block_number_index ] );

		data_offset += 4;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->indirect_block_number,
	 inode->indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->double_indirect_block_number,
	 inode->double_indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->triple_indirect_block_number,
	 inode->triple_indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->nfs_generation_number,
	 inode->nfs_generation_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->file_acl,
	 inode->file_acl );

	if( ( io_handle->format_version == 2 )
	 || ( io_handle->format_version == 3 ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext2_t *) data )->directory_acl,
		 inode->directory_acl );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->fragment_block_address,
	 inode->fragment_block_address );

	/* TODO: fragment_block_index */

	/* TODO: fragment_size */

	if( io_handle->format_version == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->creation_time,
		 inode->creation_time );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file mode\t\t\t\t\t: %" PRIo16 "\n",
		 function,
		 inode->file_mode );
		libfsext_debug_print_file_mode(
		 inode->file_mode );

		libcnotify_printf(
		 "%s: user identifier (lower)\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->user_identifier );

		if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: data size (lower)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->data_size );
		}
		else
		{
			libcnotify_printf(
			 "%s: data size\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->data_size );
		}
		if( libfsext_debug_print_posix_time_value(
		     function,
		     "access time\t\t\t\t\t",
		     ( (fsext_inode_ext2_t *) data )->access_time,
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
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		if( libfsext_debug_print_posix_time_value(
		     function,
		     "inode change time\t\t\t\t",
		     ( (fsext_inode_ext2_t *) data )->inode_change_time,
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
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		if( libfsext_debug_print_posix_time_value(
		     function,
		     "modification time\t\t\t\t",
		     ( (fsext_inode_ext2_t *) data )->modification_time,
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
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		if( libfsext_debug_print_posix_time_value(
		     function,
		     "deletion time\t\t\t\t\t",
		     ( (fsext_inode_ext2_t *) data )->deletion_time,
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
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: group identifier (lower)\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->group_identifier );

		libcnotify_printf(
		 "%s: links count\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->links_count );

		if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: blocks count (lower)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->blocks_count );
		}
		else
		{
			libcnotify_printf(
			 "%s: blocks count\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->blocks_count );
		}
		libcnotify_printf(
		 "%s: flags\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 inode->flags );

		if( io_handle->format_version == 4 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->version_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: version (lower)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		else
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext2_t *) data )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown (reserved)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: direct block numbers\t\t\t\t:",
		 function );

		for( direct_block_number_index = 0;
		     direct_block_number_index < 12;
		     direct_block_number_index++ )
		{
			if( direct_block_number_index == 0 )
			{
				libcnotify_printf(
				 " %" PRIu32 "",
				 inode->direct_block_number[ direct_block_number_index ] );
			}
			else
			{
				libcnotify_printf(
				 ", %" PRIu32 "",
				 inode->direct_block_number[ direct_block_number_index ] );
			}
		}
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: indirect block number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->indirect_block_number );

		libcnotify_printf(
		 "%s: double indirect block number\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->double_indirect_block_number );

		libcnotify_printf(
		 "%s: triple indirect block number\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->triple_indirect_block_number );

		libcnotify_printf(
		 "%s: nfs generation number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->nfs_generation_number );

		if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: file acl (lower)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->file_acl );
		}
		else
		{
			libcnotify_printf(
			 "%s: file acl\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->file_acl );
		}
		if( io_handle->format_version == 4 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->data_size_upper,
			 value_32bit );
			libcnotify_printf(
			 "%s: data size (upper)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		else
		{
			libcnotify_printf(
			 "%s: directory acl\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->directory_acl );
		}
		libcnotify_printf(
		 "%s: fragment block address\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->fragment_block_address );

		libcnotify_printf(
		 "%s: fragment block index\t\t\t\t: %" PRIu8 "\n",
		 function,
		 inode->fragment_block_index );

		libcnotify_printf(
		 "%s: fragment size\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 inode->fragment_size );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext2_t *) data )->padding1,
		 value_16bit );
		libcnotify_printf(
		 "%s: padding1\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext2_t *) data )->user_identifier_upper,
		 value_16bit );
		libcnotify_printf(
		 "%s: user identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext2_t *) data )->group_identifier_upper,
		 value_16bit );
		libcnotify_printf(
		 "%s: group identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		if( io_handle->format_version == 4 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext4_t *) data )->checksum_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: checksum (lower)\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext4_t *) data )->unknown2,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown (reserved)\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );
		}
		else
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext2_t *) data )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown (reserved)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		if( ( io_handle->format_version == 3 )
		 || ( io_handle->format_version == 4 ) )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext3_t *) data )->unknown3,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext3_t *) data )->padding2,
			 value_16bit );
			libcnotify_printf(
			 "%s: padding2\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );
		}
		if( io_handle->format_version == 4 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext4_t *) data )->checksum_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: checksum (upper)\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->inode_change_time_extra,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode change time extra\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->modification_time_extra,
			 value_32bit );
			libcnotify_printf(
			 "%s: modification time extra\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->access_time_extra,
			 value_32bit );
			libcnotify_printf(
			 "%s: access time extra\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			if( libfsext_debug_print_posix_time_value(
			     function,
			     "creation time\t\t\t\t",
			     ( (fsext_inode_ext4_t *) data )->creation_time,
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
				 "%s: unable to print POSIX time value.",
				 function );

				return( -1 );
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->creation_time_extra,
			 value_32bit );
			libcnotify_printf(
			 "%s: creation time extra\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext4_t *) data )->checksum_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: checksum (upper)\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext4_t *) data )->version_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: version (upper)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->user_identifier_upper,
	 value_32bit );

	inode->user_identifier |= value_32bit << 16;

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->group_identifier_upper,
	 value_32bit );

	inode->group_identifier |= value_32bit << 16;

	if( io_handle->format_version == 4 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext4_t *) data )->blocks_count_upper,
		 value_64bit );

		inode->blocks_count |= value_64bit << 32;

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext4_t *) data )->file_acl_upper,
		 value_64bit );

		inode->file_acl |= value_64bit << 32;

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->data_size_upper,
		 value_64bit );

		inode->data_size |= value_64bit << 32;

/* TODO handle extra precision */
	}
	return( 1 );
}

/* Retrieves the access date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_access_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_access_time";

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
	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid POSIX time.",
		 function );

		return( -1 );
	}
	*posix_time = inode->access_time;

	return( 1 );
}

/* Retrieves the inode change time date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_inode_change_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_inode_change_time";

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
	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid POSIX time.",
		 function );

		return( -1 );
	}
	*posix_time = inode->inode_change_time;

	return( 1 );
}

/* Retrieves the modification date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_modification_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_modification_time";

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
	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid POSIX time.",
		 function );

		return( -1 );
	}
	*posix_time = inode->modification_time;

	return( 1 );
}

/* Retrieves the deletion date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_deletion_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_deletion_time";

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
	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid POSIX time.",
		 function );

		return( -1 );
	}
	*posix_time = inode->deletion_time;

	return( 1 );
}

/* Reads an inode
 * Callback function for the inodes vector
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index LIBFSEXT_ATTRIBUTE_UNUSED,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_flags LIBFSEXT_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBFSEXT_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libfsext_inode_t *inode = NULL;
	uint8_t *data           = NULL;
	static char *function   = "libfsext_inode_read_element_data";
	ssize_t read_count      = 0;

	LIBFSEXT_UNREFERENCED_PARAMETER( element_data_file_index )
	LIBFSEXT_UNREFERENCED_PARAMETER( element_flags )
	LIBFSEXT_UNREFERENCED_PARAMETER( read_flags )

	if( (uint64_t) element_index > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: element index value out of bounds.",
		 function );

		return( -1 );
	}
	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: element data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading inode at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 element_data_offset,
		 element_data_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     element_data_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek inode offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 element_data_offset,
		 element_data_offset );

		goto on_error;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * (size_t) element_data_size );

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
	              (size_t) element_data_size,
	              error );

	if( read_count != (ssize_t) element_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read inode at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 element_data_offset,
		 element_data_offset );

		goto on_error;
	}
	if( libfsext_inode_initialize(
	     &inode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create inode.",
		 function );

		goto on_error;
	}
	if( libfsext_inode_read_data(
	     inode,
	     io_handle,
	     data,
	     (size_t) element_data_size,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read inode at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 element_data_offset,
		 element_data_offset );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) inode,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_inode_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set inode as element value.",
		 function );

		goto on_error;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

