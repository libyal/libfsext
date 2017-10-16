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

#include "libfsext_inode.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdatetime.h"

#include "fsext_inode.h"

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

/* Reads the inode data
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_read_data(
     libfsext_inode_t *inode,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function                 = "libfsext_inode_read_data";
	size_t data_offset                    = 0;
	uint32_t value_32bit                  = 0;
	uint8_t direct_block_number_index     = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t posix_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	uint16_t value_16bit                  = 0;
	int result                            = 0;
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
	if( data_size < sizeof( fsext_inode_t ) )
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
		 "%s: inode data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fsext_inode_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->file_mode,
	 inode->file_mode );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->user_identifier,
	 inode->user_identifier );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->data_size,
	 inode->data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->last_access_time,
	 inode->last_access_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->last_inode_change_time,
	 inode->last_inode_change_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->last_modification_time,
	 inode->last_modification_time );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->deletion_time,
	 inode->deletion_time );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->group_identifier,
	 inode->group_identifier );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->link_count,
	 inode->link_count );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->sector_count,
	 inode->sector_count );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->flags,
	 inode->flags );

	data_offset = 0;

	for( direct_block_number_index = 0;
	     direct_block_number_index < 48;
	     direct_block_number_index++ )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( ( ( (fsext_inode_t *) data )->direct_block_numbers )[ data_offset ] ),
		 ( inode->direct_block_number )[ direct_block_number_index ] );

		data_offset += 4;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->indirect_block_number,
	 inode->indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->double_indirect_block_number,
	 inode->double_indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->triple_indirect_block_number,
	 inode->triple_indirect_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->nfs_generation_number,
	 inode->nfs_generation_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->file_acl,
	 inode->file_acl );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->directory_acl,
	 inode->directory_acl );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_inode_t *) data )->fragment_block_address,
	 inode->fragment_block_address );

	/* TODO: fragment_block_index */

	/* TODO: fragment_size */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfdatetime_posix_time_initialize(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create POSIX time.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: file mode\t\t\t\t\t: %" PRIo16 "\n",
		 function,
		 inode->file_mode );

		libcnotify_printf(
		 "%s: user identifier\t\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->user_identifier );

		libcnotify_printf(
		 "%s: data size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->data_size );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_inode_t *) data )->last_access_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: last access time\t\t\t\t: %" PRIs_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_inode_t *) data )->last_inode_change_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: last inode change time\t\t\t: %" PRIs_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_inode_t *) data )->last_modification_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: last modification time\t\t\t: %" PRIs_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_inode_t *) data )->deletion_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) posix_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: deletion time\t\t\t\t\t: %" PRIs_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		libcnotify_printf(
		 "%s: group identifier\t\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->group_identifier );

		libcnotify_printf(
		 "%s: link count\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 inode->link_count );

		libcnotify_printf(
		 "%s: sector count\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->sector_count );

		libcnotify_printf(
		 "%s: flags\t\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->flags );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: Unknown (reserved)\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		for( direct_block_number_index = 0;
		     direct_block_number_index < 48;
		     direct_block_number_index++ )
		{
			libcnotify_printf(
			 "%s: direct block number: %" PRIu8 "\t\t\t: %" PRIu32 "\n",
			 function,
			 direct_block_number_index,
			 inode->indirect_block_number );
		}
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

		libcnotify_printf(
		 "%s: file acl\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->file_acl );

		libcnotify_printf(
		 "%s: directory acl\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 inode->directory_acl );

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
		 ( (fsext_inode_t *) data )->padding1,
		 value_16bit );
		libcnotify_printf(
		 "%s: padding1\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_t *) data )->user_identifier_upper,
		 value_16bit );
		libcnotify_printf(
		 "%s: user identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_inode_t *) data )->group_identifier_upper,
		 value_16bit );
		libcnotify_printf(
		 "%s: group identifier (upper)\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_inode_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: Unknown (reserved)\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );

		if( libfdatetime_posix_time_free(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free POSIX time.",
			 function );

			goto on_error;
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->user_identifier_upper,
	 value_32bit );

	inode->user_identifier |= value_32bit << 16;

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_inode_t *) data )->group_identifier_upper,
	 value_32bit );

	inode->group_identifier |= value_32bit << 16;

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( -1 );
}

