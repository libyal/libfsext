/*
 * Inode functions
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsext_block.h"
#include "libfsext_debug.h"
#include "libfsext_definitions.h"
#include "libfsext_extent.h"
#include "libfsext_extents_header.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
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

		memory_free(
		 *inode );

		*inode = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *inode )->data_extents_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data extents array.",
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
	int result            = 1;

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
		if( libcdata_array_free(
		     &( ( *inode )->data_extents_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_extent_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data extents array.",
			 function );

			result = -1;
		}
		memory_free(
		 *inode );

		*inode = NULL;
	}
	return( result );
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

	if( *destination_inode == NULL )
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
	( *destination_inode )->data_extents_array = NULL;

	if( libcdata_array_clone(
	     &( ( *destination_inode )->data_extents_array ),
	     source_inode->data_extents_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_extent_free,
	     (int (*)(intptr_t **, intptr_t *, libcerror_error_t **)) &libfsext_extent_clone,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination data extents array.",
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
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_read_data(
     libfsext_inode_t *inode,
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function           = "libfsext_inode_read_data";
	uint32_t access_time            = 0;
	uint32_t creation_time          = 0;
	uint32_t data_size_upper        = 0;
	uint32_t inode_change_time      = 0;
	uint32_t modification_time      = 0;
	uint32_t value_32bit            = 0;
	uint16_t blocks_count_upper     = 0;
	uint16_t file_acl_upper         = 0;
	uint16_t group_identifier_upper = 0;
	uint16_t owner_identifier_upper = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t data_offset              = 0;
	uint16_t value_16bit            = 0;
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
	if( ( data_size != 128 )
	 && ( data_size != 256 )
	 && ( data_size != 512 )
	 && ( data_size != 1024 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported data size.",
		 function );

		return( -1 );
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
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     empty_inode_data,
	     data,
	     data_size ) == 0 )
	{
		inode->is_empty = 1;

		return( 1 );
	}
	else
	{
		inode->is_empty = 0;
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->file_mode,
	 inode->file_mode );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->owner_identifier,
	 inode->owner_identifier );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->data_size,
	 inode->data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->access_time,
	 access_time );

	inode->access_time  = (int32_t) access_time;
	inode->access_time *= 1000000000;

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->inode_change_time,
	 inode_change_time );

	inode->inode_change_time  = (int32_t) inode_change_time;
	inode->inode_change_time *= 1000000000;

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->modification_time,
	 modification_time );

	inode->modification_time  = (int32_t) modification_time;
	inode->modification_time *= 1000000000;

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

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file mode\t\t\t\t\t: %" PRIo16 " (0x%04" PRIx16 ")\n",
		 function,
		 inode->file_mode,
		 inode->file_mode );
		libfsext_debug_print_file_mode(
		 inode->file_mode );

		libcnotify_printf(
		 "%s: owner identifier (lower)\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->owner_identifier );

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
		libfsext_debug_print_inode_flags(
		 inode->flags );
		libcnotify_printf(
		 "\n" );

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
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( memory_copy(
	     inode->data_reference,
	     ( (fsext_inode_ext2_t *) data )->data_reference,
	     60 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data reference.",
		 function );

		return( -1 );
	}
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
	else if( io_handle->format_version == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->data_size_upper,
		 data_size_upper );

		inode->data_size |= (uint64_t) data_size_upper << 32;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_ext2_t *) data )->fragment_block_address,
	 inode->fragment_block_address );

	if( ( io_handle->format_version == 2 )
	 || ( io_handle->format_version == 3 ) )
	{
		/* TODO: fragment_block_index */

		/* TODO: fragment_size */
	}
	else if( io_handle->format_version == 4 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext4_t *) data )->blocks_count_upper,
		 blocks_count_upper );

		inode->blocks_count |= (uint64_t) blocks_count_upper << 32;

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_ext4_t *) data )->file_acl_upper,
		 file_acl_upper );
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->owner_identifier_upper,
	 owner_identifier_upper );

	inode->owner_identifier |= owner_identifier_upper << 16;

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_ext2_t *) data )->group_identifier_upper,
	 group_identifier_upper );

	inode->group_identifier |= value_32bit << 16;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( io_handle->format_version == 4 )
		 && ( ( inode->flags & 0x10080000UL ) != 0 ) )
		{
			libcnotify_printf(
			 "%s: data reference:\n",
			 function );
			libcnotify_print_data(
			 inode->data_reference,
			 60,
			 0 );
		}
		else if( ( ( inode->file_mode & 0xf000 ) == 0xa000 )
		      && ( inode->data_size < 60 ) )
		{
			libcnotify_printf(
			 "%s: symbolic link data:\n",
			 function );
			libcnotify_print_data(
			 inode->data_reference,
			 60,
			 0 );
		}
		else
		{
			libcnotify_printf(
			 "%s: direct block numbers\t\t\t\t:",
			 function );

			for( data_offset = 0;
			     data_offset < 48;
			     data_offset += 4 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 &( ( inode->data_reference )[ data_offset ] ),
				 value_32bit );

				if( data_offset == 0 )
				{
					libcnotify_printf(
					 " %" PRIu32 "",
					 value_32bit );
				}
				else
				{
					libcnotify_printf(
					 ", %" PRIu32 "",
					 value_32bit );
				}
			}
			libcnotify_printf(
			 "\n" );

			byte_stream_copy_to_uint32_little_endian(
			 &( ( inode->data_reference )[ data_offset ] ),
			 value_32bit );

			data_offset += 4;

			libcnotify_printf(
			 "%s: indirect block number\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( ( inode->data_reference )[ data_offset ] ),
			 value_32bit );

			data_offset += 4;

			libcnotify_printf(
			 "%s: double indirect block number\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( ( inode->data_reference )[ data_offset ] ),
			 value_32bit );

			data_offset += 4;

			libcnotify_printf(
			 "%s: triple indirect block number\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: nfs generation number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->nfs_generation_number );

		if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: file ACL (lower)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->file_acl );
		}
		else
		{
			libcnotify_printf(
			 "%s: file ACL\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 inode->file_acl );
		}
		if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: data size (upper)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 data_size_upper );
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

		if( ( io_handle->format_version == 2 )
		 || ( io_handle->format_version == 3 ) )
		{
			libcnotify_printf(
			 "%s: fragment block index\t\t\t\t: %" PRIu8 "\n",
			 function,
			 ( (fsext_inode_ext2_t *) data )->fragment_block_index );

			libcnotify_printf(
			 "%s: fragment size\t\t\t\t\t: %" PRIu8 "\n",
			 function,
			 ( (fsext_inode_ext2_t *) data )->fragment_size );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_inode_ext2_t *) data )->padding1,
			 value_16bit );
			libcnotify_printf(
			 "%s: padding1\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );
		}
		else if( io_handle->format_version == 4 )
		{
			libcnotify_printf(
			 "%s: block count (upper)\t\t\t\t: %" PRIu16 "\n",
			 function,
			 blocks_count_upper );

			libcnotify_printf(
			 "%s: file ACL (upper)\t\t\t\t: %" PRIu16 "\n",
			 function,
			 file_acl_upper );
		}
		libcnotify_printf(
		 "%s: owner identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 owner_identifier_upper );

		libcnotify_printf(
		 "%s: group identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 group_identifier_upper );

		if( ( io_handle->format_version == 2 )
		 || ( io_handle->format_version == 3 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_inode_ext2_t *) data )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown (reserved)\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
		else if( io_handle->format_version == 4 )
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
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( data_size > sizeof( fsext_inode_ext2_t ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	if( data_size > sizeof( fsext_inode_ext3_t ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->inode_change_time_extra,
		 value_32bit );

		if( ( value_32bit & 0x00000003UL ) != 0 )
		{
			inode->inode_change_time  = 0x100000000UL;
			inode->inode_change_time *= ( value_32bit & 0x00000003UL );
			inode->inode_change_time += (int32_t) inode_change_time;
			inode->inode_change_time *= 1000000000;
		}
		inode->inode_change_time += value_32bit >> 2;

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->modification_time_extra,
		 value_32bit );

		if( ( value_32bit & 0x00000003UL ) != 0 )
		{
			inode->modification_time  = 0x100000000UL;
			inode->modification_time *= ( value_32bit & 0x00000003UL );
			inode->modification_time += (int32_t) modification_time;
			inode->modification_time *= 1000000000;
		}
		inode->modification_time += value_32bit >> 2;

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->access_time_extra,
		 value_32bit );

		if( ( value_32bit & 0x00000003UL ) != 0 )
		{
			inode->access_time  = 0x100000000UL;
			inode->access_time *= ( value_32bit & 0x00000003UL );
			inode->access_time += (int32_t) access_time;
			inode->access_time *= 1000000000;
		}
		inode->access_time += value_32bit >> 2;

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->creation_time,
		 creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_ext4_t *) data )->creation_time_extra,
		 value_32bit );

		if( ( value_32bit & 0x00000003UL ) == 0 )
		{
			inode->creation_time = (int32_t) creation_time;
		}
		else
		{
			inode->creation_time  = 0x100000000UL;
			inode->creation_time *= ( value_32bit & 0x00000003UL );
			inode->creation_time += (int32_t) creation_time;
		}
		inode->creation_time *= 1000000000;
		inode->creation_time += value_32bit >> 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
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
			 "%s: inode change time extra\t\t\t: 0x%04" PRIx32 "\n",
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
			 "%s: access time extra\t\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			if( libfsext_debug_print_posix_time_value(
			     function,
			     "creation time\t\t\t\t\t",
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
			 "%s: creation time extra\t\t\t\t: 0x%04" PRIx32 "\n",
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_size > sizeof( fsext_inode_ext4_t ) )
		{
			libcnotify_printf(
			 "%s: extended attributes data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ sizeof( fsext_inode_ext4_t ) ] ),
			 data_size - sizeof( fsext_inode_ext4_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
		else
		{
			libcnotify_printf(
			 "\n" );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( io_handle->format_version == 4 )
	{
		inode->file_acl |= (uint64_t) file_acl_upper << 32;
	}
	return( 1 );
}

/* Reads the inode data reference
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_read_data_reference(
     libfsext_inode_t *inode,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libfsext_block_t *block                   = NULL;
	libfsext_extent_t *extent                 = NULL;
	libfsext_extents_header_t *extents_header = NULL;
	static char *function                     = "libfsext_inode_read_data_reference";
	size_t data_offset                        = 0;
	uint32_t block_number                     = 0;
	uint8_t block_number_index                = 0;
	int entry_index                           = 0;

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
	if( ( io_handle->format_version == 4 )
	 && ( ( inode->flags & LIBFSEXT_INODE_FLAG_COMPRESSED_DATA ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: compressed data currently not supported.",
		 function );

		goto on_error;
	}
	if( ( io_handle->format_version == 4 )
	 && ( ( inode->flags & LIBFSEXT_INODE_FLAG_INLINE_DATA ) != 0 ) )
	{
		/* The data is stored inline in inode->data_reference */
	}
	else if( ( io_handle->format_version == 4 )
	      && ( ( inode->flags & LIBFSEXT_INODE_FLAG_HAS_EXTENTS ) != 0 ) )
	{
		data_offset = 0;

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
		     &( ( inode->data_reference )[ data_offset ] ),
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
		data_offset += 12;

		if( extents_header->number_of_extents > 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported number of extents.",
			 function );

			goto on_error;
		}
		if( extents_header->depth != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported depth.",
			 function );

			goto on_error;
		}
		for( block_number_index = 0;
		     block_number_index < extents_header->number_of_extents;
		     block_number_index++ )
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
			     &( ( inode->data_reference )[ data_offset ] ),
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
				     inode->data_extents_array,
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
/* TODO debug print remaining extents */
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
	}
	else if( ( ( inode->file_mode & 0xf000 ) == 0xa000 )
	      && ( inode->data_size < 60 ) )
	{
		/* The symbolic link target path is stored in inode->data_reference */
	}
	else
	{
		if( libfsext_inode_read_direct_block_number_data(
		     inode,
		     inode->data_reference,
		     48,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read direct block numbers.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( ( inode->data_reference )[ 48 ] ),
		 block_number );

		if( block_number != 0 )
		{
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
			     (off64_t) block_number * io_handle->block_size,
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
			if( libfsext_inode_read_direct_block_number_data(
			     inode,
			     block->data,
			     (size_t) io_handle->block_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read direct block numbers of indirect block: %" PRIu32 ".",
				 function,
				 block_number );

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
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( ( inode->data_reference )[ 52 ] ),
		 block_number );

		if( block_number != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported double indirect block number.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( ( inode->data_reference )[ 56 ] ),
		 block_number );

		if( block_number != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported tripple indirect block number.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( block != NULL )
	{
		libfsext_block_free(
		 &block,
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

/* Reads direct block number data
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_read_direct_block_number_data(
     libfsext_inode_t *inode,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsext_extent_t *extent          = NULL;
	libfsext_extent_t *previous_extent = NULL;
	static char *function              = "libfsext_inode_read_direct_block_number_data";
	size_t data_offset                 = 0;
	uint32_t block_number              = 0;
	uint32_t logical_block_number      = 0;
	int entry_index                    = 0;
	int number_of_extents              = 0;

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
		 "%s: direct block number data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libcdata_array_get_number_of_entries(
	     inode->data_extents_array,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		goto on_error;
	}
	if( number_of_extents > 0 )
	{
		if( libcdata_array_get_entry_by_index(
		     inode->data_extents_array,
		     number_of_extents - 1,
		     (intptr_t **) &previous_extent,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent: %d.",
			 function,
			 number_of_extents - 1 );

			goto on_error;
		}
		if( previous_extent == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing extent: %d.",
			 function,
			 number_of_extents - 1 );

			goto on_error;
		}
		logical_block_number = previous_extent->logical_block_number + previous_extent->number_of_blocks;
	}
	while( data_offset < data_size )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset ] ),
		 block_number );

		data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( ( libcnotify_verbose != 0 )
		 && ( previous_extent != NULL ) )
		{
			libcnotify_printf(
			 "%s: block number\t\t: %" PRIu32 "\n",
			 function,
			 block_number );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( block_number == 0 )
		{
			break;
		}
		if( ( previous_extent != NULL )
		 && ( previous_extent->physical_block_number == ( block_number - previous_extent->number_of_blocks ) ) )
		{
			logical_block_number              += 1;
			previous_extent->number_of_blocks += 1;

			continue;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( ( libcnotify_verbose != 0 )
		 && ( previous_extent != NULL ) )
		{
			libcnotify_printf(
			 "%s: physical block number\t: %" PRIu64 "\n",
			 function,
			 previous_extent->physical_block_number );

			libcnotify_printf(
			 "%s: number of blocks\t\t: %" PRIu64 "\n",
			 function,
			 previous_extent->number_of_blocks );

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
		extent->logical_block_number  = logical_block_number;
		extent->physical_block_number = block_number;
		extent->number_of_blocks      = 1;

		if( libcdata_array_append_entry(
		     inode->data_extents_array,
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
		previous_extent = extent;
		extent          = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( ( libcnotify_verbose != 0 )
	 && ( previous_extent != NULL ) )
	{
		libcnotify_printf(
		 "%s: physical block number\t: %" PRIu64 "\n",
		 function,
		 previous_extent->physical_block_number );

		libcnotify_printf(
		 "%s: number of blocks\t\t: %" PRIu64 "\n",
		 function,
		 previous_extent->number_of_blocks );

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

/* Determines if the inode is empty
 * Returns 1 if empty, 0 if not or -1 on error
 */
int libfsext_inode_is_empty(
     libfsext_inode_t *inode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_is_empty";

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
	return( (int) inode->is_empty );
}

/* Retrieves the access date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_access_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
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

/* Retrieves the creation date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_creation_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_creation_time";

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
	*posix_time = inode->creation_time;

	return( 1 );
}

/* Retrieves the inode change time date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_inode_change_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
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
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_modification_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
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
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_deletion_time(
     libfsext_inode_t *inode,
     int32_t *posix_time,
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
	*posix_time = (int32_t) inode->deletion_time;

	return( 1 );
}

/* Retrieves the file mode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_file_mode(
     libfsext_inode_t *inode,
     uint16_t *file_mode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_file_mode";

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
	if( file_mode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file mode.",
		 function );

		return( -1 );
	}
	*file_mode = inode->file_mode;

	return( 1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_data_size(
     libfsext_inode_t *inode,
     uint64_t *data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_data_size";

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
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data_size = inode->data_size;

	return( 1 );
}

/* Retrieves the owner identifier
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_owner_identifier(
     libfsext_inode_t *inode,
     uint32_t *owner_identifier,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_owner_identifier";

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
	if( owner_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid owner identifier.",
		 function );

		return( -1 );
	}
	*owner_identifier = inode->owner_identifier;

	return( 1 );
}

/* Retrieves the group identifier
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_group_identifier(
     libfsext_inode_t *inode,
     uint32_t *group_identifier,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_group_identifier";

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
	if( group_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid group identifier.",
		 function );

		return( -1 );
	}
	*group_identifier = inode->group_identifier;

	return( 1 );
}

/* Retrieves the number of extents
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_number_of_extents(
     libfsext_inode_t *inode,
     int *number_of_extents,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_number_of_extents";

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
	if( libcdata_array_get_number_of_entries(
	     inode->data_extents_array,
	     number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific extent
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_get_extent_by_index(
     libfsext_inode_t *inode,
     int extent_index,
     libfsext_extent_t **extent,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_get_extent_by_index";

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
	if( libcdata_array_get_entry_by_index(
	     inode->data_extents_array,
	     extent_index,
	     (intptr_t **) extent,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent: %d.",
		 function,
		 extent_index );

		return( -1 );
	}
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
     libfdata_cache_t *cache,
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
	if( ( element_data_size == 0 )
	 || ( element_data_size > (size64_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
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
	     error ) != 1 )
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
	if( libfsext_inode_read_data_reference(
	     inode,
	     io_handle,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read inode data reference.",
		 function );

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

