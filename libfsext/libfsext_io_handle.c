/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libfsext_debug.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdatetime.h"
#include "libfsext_libfguid.h"

#include "fsext_group_descriptor.h"
#include "fsext_superblock.h"

const char fsext_volume_signature[ 2 ] = "\x53\xef";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_initialize(
     libfsext_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libfsext_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libfsext_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libfsext_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_free(
     libfsext_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libfsext_io_handle_free";
	int result            = 1;

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_clear(
     libfsext_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libfsext_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libfsext_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the superblock
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_read_superblock(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t superblock_data[ 1024 ];

	fsext_dynamic_inode_information_t *dynamic_inode_information = NULL;
	fsext_journal_information_t *journal_information             = NULL;
	fsext_performance_hints_t *performance_hints                 = NULL;
	fsext_volume_header_t *volume_header                         = NULL;
	static char *function                                        = "libfsext_io_handle_read_superblock";
	size_t superblock_data_offset                                = 0;
	ssize_t read_count                                           = 0;
	uint32_t blocks_per_block_group                              = 0;
	uint32_t number_of_block_groups                              = 0;
	uint32_t number_of_blocks                                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t posix_time_string[ 32 ];
	libcstring_system_character_t guid_string[ 48 ];

	libfdatetime_posix_time_t *posix_time                        = NULL;
	libfguid_identifier_t *guid                                  = NULL;
	uint32_t value_32bit                                         = 0;
	uint16_t value_16bit                                         = 0;
	int result                                                   = 0;
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading superblock at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
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
		 "%s: unable to seek superblock offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &superblock_data,
	              1024,
	              error );

	if( read_count != (ssize_t) 1024 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read superblock data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: volume header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) superblock_data,
		 sizeof( fsext_volume_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	volume_header = (fsext_volume_header_t *) superblock_data;

	if( memory_compare(
	     volume_header->signature,
	     fsext_volume_signature,
	     2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid volume system signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 volume_header->number_of_blocks,
	 number_of_blocks );

	byte_stream_copy_to_uint32_little_endian(
	 volume_header->block_size,
	 io_handle->block_size );

	byte_stream_copy_to_uint32_little_endian(
	 volume_header->blocks_per_block_group,
	 blocks_per_block_group );

	byte_stream_copy_to_uint32_little_endian(
	 volume_header->format_revision,
	 io_handle->format_revision );

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
		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 volume_header->number_of_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of inodes\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_blocks );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->number_of_reserved_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of reserved blocks\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->number_of_unallocated_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated blocks\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->number_of_unallocated_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated inodes\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->root_block_group_block_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: root block group block number\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: block size\t\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << io_handle->block_size,
		 io_handle->block_size );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->fragment_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragment size\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		libcnotify_printf(
		 "%s: blocks per block group\t\t: %" PRIu32 "\n",
		 function,
		 blocks_per_block_group );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->fragments_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragments per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->inodes_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: inodes per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     volume_header->last_mount_time,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "%s: last mount time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     volume_header->last_written_time,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "%s: last written time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: mount count\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->maximum_mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum mount count\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: signature\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 volume_header->signature[ 0 ],
		 volume_header->signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->file_system_state_flags,
		 value_16bit );
		libcnotify_printf(
		 "%s: file system state flags\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );
		libfsext_debug_print_file_system_state_flags(
		 value_16bit );
		libcnotify_printf(
		 "\n" );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->error_handling_status,
		 value_16bit );
		libcnotify_printf(
		 "%s: error handling status\t\t: %" PRIu16 " (%s)\n",
		 function,
		 value_16bit,
		 libfsext_debug_print_error_handling_status(
		  value_16bit ) );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->minor_format_revision,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor format revision\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     volume_header->last_consistency_check_time,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "%s: last consistency check time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

/* TODO print interval as duration? */
		byte_stream_copy_to_uint32_little_endian(
		 volume_header->consistency_check_interval,
		 value_32bit );
		libcnotify_printf(
		 "%s: consistency check interval\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header->creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creator operating system\t\t: %" PRIu32 " (%s)\n",
		 function,
		 value_32bit,
		 libfsext_debug_print_creator_operating_system(
		  value_32bit ) );

		libcnotify_printf(
		 "%s: format revision\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->format_revision );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->reserved_block_uid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block UID\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header->reserved_block_gid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block GID\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	superblock_data_offset += sizeof( fsext_volume_header_t );

	io_handle->block_size = 1024 << io_handle->block_size;

	if( io_handle->format_revision > 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format revision: %" PRIu32 ".",
		 function,
		 io_handle->format_revision );

		goto on_error;
	}
	if( io_handle->format_revision == 1 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: dynamic inode information data:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &( superblock_data[ superblock_data_offset ] ),
			 sizeof( fsext_dynamic_inode_information_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		dynamic_inode_information = (fsext_dynamic_inode_information_t *) &( superblock_data[ superblock_data_offset ] );

		byte_stream_copy_to_uint32_little_endian(
		 dynamic_inode_information->compatible_features_flags,
		 io_handle->compatible_features_flags );

		byte_stream_copy_to_uint32_little_endian(
		 dynamic_inode_information->incompatible_features_flags,
		 io_handle->incompatible_features_flags );

		byte_stream_copy_to_uint32_little_endian(
		 dynamic_inode_information->read_only_compatible_features_flags,
		 io_handle->read_only_compatible_features_flags );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 dynamic_inode_information->first_non_reserved_inode,
			 value_32bit );
			libcnotify_printf(
			 "%s: first non-reserved inode\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 dynamic_inode_information->inode_size,
			 value_16bit );
			libcnotify_printf(
			 "%s: inode size\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 dynamic_inode_information->block_group,
			 value_16bit );
			libcnotify_printf(
			 "%s: block group\t\t\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			libcnotify_printf(
			 "%s: compatible features flags\t\t: 0x%08" PRIx32 "\n",
			 function,
			 io_handle->compatible_features_flags );
			libfsext_debug_print_compatible_features_flags(
			 io_handle->compatible_features_flags );
			libcnotify_printf(
			 "\n" );

			libcnotify_printf(
			 "%s: incompatible features flags\t\t: 0x%08" PRIx32 "\n",
			 function,
			 io_handle->incompatible_features_flags );
			libfsext_debug_print_incompatible_features_flags(
			 io_handle->incompatible_features_flags );
			libcnotify_printf(
			 "\n" );

			libcnotify_printf(
			 "%s: read-only compatible features flags\t: 0x%08" PRIx32 "\n",
			 function,
			 io_handle->read_only_compatible_features_flags );
			libfsext_debug_print_read_only_compatible_features_flags(
			 io_handle->read_only_compatible_features_flags );
			libcnotify_printf(
			 "\n" );

			if( libfguid_identifier_copy_from_byte_stream(
			     guid,
			     dynamic_inode_information->file_system_identifier,
			     16,
			     LIBFGUID_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy byte stream to GUID.",
				 function );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfguid_identifier_copy_to_utf16_string(
				  guid,
				  (uint16_t *) guid_string,
				  48,
				  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
				  error );
#else
			result = libfguid_identifier_copy_to_utf8_string(
				  guid,
				  (uint8_t *) guid_string,
				  48,
				  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy GUID to string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: file system identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
			 function,
			 guid_string );

/* TODO print as string */
			libcnotify_printf(
			 "%s: volume label:\n",
			 function );
			libcnotify_print_data(
			 dynamic_inode_information->volume_label,
			 16,
			 0 );

/* TODO print as string */
			libcnotify_printf(
			 "%s: last mounted path:\n",
			 function );
			libcnotify_print_data(
			 dynamic_inode_information->last_mounted_path,
			 64,
			 0 );

			byte_stream_copy_to_uint32_little_endian(
			 dynamic_inode_information->algorithm_usage_bitmap,
			 value_32bit );
			libcnotify_printf(
			 "%s: algorithm usage bitmap\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	superblock_data_offset += sizeof( fsext_dynamic_inode_information_t );

	if( ( ( io_handle->compatible_features_flags & 0x00000200 ) != 0 )
	 || ( ( io_handle->incompatible_features_flags & 0x0001f7c0 ) != 0 )
	 || ( ( io_handle->read_only_compatible_features_flags & 0x00000378 ) != 0 ) )
	{
		io_handle->format_version = 4;
	}
	else if( ( ( io_handle->compatible_features_flags & 0x00000004 ) != 0 )
	      || ( ( io_handle->incompatible_features_flags & 0x0000000c ) != 0 ) )
	{
		io_handle->format_version = 3;
	}
	else
	{
		io_handle->format_version = 2;
	}
	if( ( io_handle->compatible_features_flags & 0x00000001UL ) != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: performance hints data:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &( superblock_data[ superblock_data_offset ] ),
			 sizeof( fsext_performance_hints_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		performance_hints = (fsext_performance_hints_t *) &( superblock_data[ superblock_data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: number of blocks per file\t\t: %" PRIu8 "\n",
			 function,
			 performance_hints->number_of_blocks_per_file );

			libcnotify_printf(
			 "%s: number of blocks per directory\t\t: %" PRIu8 "\n",
			 function,
			 performance_hints->number_of_blocks_per_directory );

			libcnotify_printf(
			 "%s: padding:\n",
			 function );
			libcnotify_print_data(
			 performance_hints->padding,
			 2,
			 0 );
		}
#endif
	}
	superblock_data_offset += sizeof( fsext_performance_hints_t );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: journal information data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &( superblock_data[ superblock_data_offset ] ),
		 sizeof( fsext_journal_information_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	journal_information = (fsext_journal_information_t *) &( superblock_data[ superblock_data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     journal_information->journal_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: journal identifier\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		byte_stream_copy_to_uint32_little_endian(
		 journal_information->journal_inode,
		 value_32bit );
		libcnotify_printf(
		 "%s: journal inode\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 journal_information->journal_device,
		 value_32bit );
		libcnotify_printf(
		 "%s: journal device\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 journal_information->orphan_inode_list_head,
		 value_32bit );
		libcnotify_printf(
		 "%s: orphan inode list head\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: HTREE hash seed:\n",
		 function );
		libcnotify_print_data(
		 journal_information->htree_hash_seed,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: default hash version\t\t: %" PRIu8 "\n",
		 function,
		 journal_information->default_hash_version );

		libcnotify_printf(
		 "%s: padding:\n",
		 function );
		libcnotify_print_data(
		 journal_information->padding,
		 3,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 journal_information->default_mount_options,
		 value_32bit );
		libcnotify_printf(
		 "%s: default mount options\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 journal_information->first_metadata_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: first metadata block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     journal_information->file_system_creation_time,
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
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "%s: file system creation time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		libcnotify_printf(
		 "%s: backup journal inodes:\n",
		 function );
		libcnotify_print_data(
		 journal_information->backup_journal_inodes,
		 68,
		 0 );
	}
#endif
	superblock_data_offset += sizeof( fsext_journal_information_t );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reserved data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &( superblock_data[ superblock_data_offset ] ),
		 1024 - superblock_data_offset,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
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
#endif
	if( number_of_blocks == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of blocks value out of bounds.",
		 function );

		goto on_error;
	}
	if( blocks_per_block_group == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block per block group value out of bounds.",
		 function );

		goto on_error;
	}
	number_of_block_groups = number_of_blocks / blocks_per_block_group;

	if( ( number_of_blocks % blocks_per_block_group ) != 0 )
	{
		number_of_block_groups += 1;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->format_version );

		libcnotify_printf(
		 "%s: number of block groups\t\t: %" PRIu32 "\n",
		 function,
		 number_of_block_groups );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
#endif
	return( -1 );
}

/* Reads the group descriptor
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_read_group_descriptor(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *block_data               = NULL;
	static char *function             = "libfsext_io_handle_read_group_descriptor";
	size_t block_data_offset          = 0;
	size_t group_descriptor_data_size = 0;
	ssize_t read_count                = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit              = 0;
	uint16_t value_16bit              = 0;
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
	block_data = memory_allocate(
	              sizeof( uint8_t ) * io_handle->block_size );

	if( block_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     block_data,
	     0,
	     sizeof( uint8_t ) * io_handle->block_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear block data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading group descriptor at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
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
		 "%s: unable to seek group descriptor offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              block_data,
	              io_handle->block_size,
	              error );

	if( read_count != (ssize_t) io_handle->block_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read group descriptor data.",
		 function );

		goto on_error;
	}
	if( ( io_handle->incompatible_features_flags & 0x00000080UL ) == 0 )
	{
		group_descriptor_data_size = sizeof( fsext_group_descriptor_ext2_t );
	}
	else
	{
		group_descriptor_data_size = sizeof( fsext_group_descriptor_ext4_t );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: group descriptor data:\n",
		 function );
		libcnotify_print_data(
		 block_data,
		 group_descriptor_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( io_handle->format_version == 4 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->block_bitmap_block_number_lower,
			 value_32bit );
			libcnotify_printf(
			 "%s: block bitmap block number (lower)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_bitmap_block_number_lower,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode bitmap block number (lower)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_table_block_number_lower,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode table block number (lower)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unallocated_blocks_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated blocks (lower)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unallocated_inodes_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated inodes (lower)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_directories_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of directories (lower)\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->exclude_bitmap_block_number_lower,
			 value_32bit );
			libcnotify_printf(
			 "%s: exclude bitmap block number (lower)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->block_bitmap_checksum_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: block bitmap checksum (lower)\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_bitmap_checksum_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: inode bitmap checksum (lower)\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unused_inodes_lower,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unused inodes (lower)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->checksum,
			 value_16bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->block_bitmap_block_number_upper,
			 value_32bit );
			libcnotify_printf(
			 "%s: block bitmap block number (upper)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_bitmap_block_number_upper,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode bitmap block number (upper)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_table_block_number_upper,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode table block number (upper)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unallocated_blocks_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated blocks (upper)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unallocated_inodes_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated inodes (upper)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_directories_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of directories (upper)\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->number_of_unused_inodes_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unused inodes (upper)\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->exclude_bitmap_block_number_upper,
			 value_32bit );
			libcnotify_printf(
			 "%s: exclude bitmap block number (upper)\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->block_bitmap_checksum_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: block bitmap checksum (upper)\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->inode_bitmap_checksum_upper,
			 value_16bit );
			libcnotify_printf(
			 "%s: inode bitmap checksum (upper)\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_group_descriptor_ext4_t *) block_data )->unknown1,
			 4,
			 0 );
		}
#endif
	}
	else
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->block_bitmap_block_number,
			 value_32bit );
			libcnotify_printf(
			 "%s: block bitmap block number\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->inode_bitmap_block_number,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode bitmap block number\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->inode_table_block_number,
			 value_32bit );
			libcnotify_printf(
			 "%s: inode table block number\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->number_of_unallocated_blocks,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated blocks\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->number_of_unallocated_inodes,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of unallocated inodes\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->number_of_directories,
			 value_16bit );
			libcnotify_printf(
			 "%s: number of directories\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			libcnotify_printf(
			 "%s: padding:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->padding,
			 2,
			 0 );

			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (fsext_group_descriptor_ext2_t *) block_data )->unknown1,
			 12,
			 0 );
		}
#endif
	}
	block_data_offset += group_descriptor_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: trailing data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &( block_data[ block_data_offset ] ),
		 (size_t) io_handle->block_size - block_data_offset,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	memory_free(
	 block_data );

	block_data = NULL;

	return( 1 );

on_error:
	if( block_data != NULL )
	{
		memory_free(
		 block_data );
	}
	return( -1 );
}

