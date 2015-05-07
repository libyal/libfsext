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

#include "fsext_volume_header.h"

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

/* Reads the volume header
 * Returns 1 if successful or -1 on error
 */
int libfsext_io_handle_read_volume_header(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t volume_header_data[ 1024 ];

	static char *function                 = "libfsext_io_handle_read_volume_header";
	size_t volume_header_data_offset      = 0;
	ssize_t read_count                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t posix_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	uint32_t value_32bit                  = 0;
	uint16_t value_16bit                  = 0;
	int result                            = 0;
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
		 "%s: reading volume header at offset: 1024 (0x00000400)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     1024,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek volume header offset: 1024.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &volume_header_data,
	              1024,
	              error );

	if( read_count != (ssize_t) 1024 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volume header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: volume header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) volume_header_data,
		 sizeof( fsext_volume_header_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (fsext_volume_header_t *) volume_header_data )->signature,
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
	 ( (fsext_volume_header_t *) volume_header_data )->format_revision,
	 io_handle->format_revision );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->number_of_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of inodes\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->number_of_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->number_of_reserved_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of reserved blocks\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->number_of_unallocated_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated blocks\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->number_of_unallocated_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated inodes\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->root_block_group_block_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: root block group block number\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->block_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: block size\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->fragment_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragment size\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->blocks_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: blocks per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->fragments_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragments per block group\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->inodes_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: inodes per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

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
		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_volume_header_t *) volume_header_data )->last_mount_time,
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
		     ( (fsext_volume_header_t *) volume_header_data )->last_written_time,
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
		 "%s: last written time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: mount count\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->maximum_mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum mount count\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: signature\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 ( (fsext_volume_header_t *) volume_header_data )->signature[ 0 ],
		 ( (fsext_volume_header_t *) volume_header_data )->signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->file_system_state_flags,
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
		 ( (fsext_volume_header_t *) volume_header_data )->error_handling_status,
		 value_16bit );
		libcnotify_printf(
		 "%s: error handling status\t\t: %" PRIu16 " (%s)\n",
		 function,
		 value_16bit,
		 libfsext_debug_print_error_handling_status(
		  value_16bit ) );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->minor_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor version\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		if( libfdatetime_posix_time_copy_from_byte_stream(
		     posix_time,
		     ( (fsext_volume_header_t *) volume_header_data )->last_consistency_check_time,
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
		 "%s: last consistency check time\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 posix_time_string );

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
/* TODO print interval as duration? */
		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->consistency_check_interval,
		 value_32bit );
		libcnotify_printf(
		 "%s: consistency check interval\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->creator_operating_system,
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
		 ( (fsext_volume_header_t *) volume_header_data )->reserved_block_uid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block UID\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_volume_header_t *) volume_header_data )->reserved_block_gid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block GID\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	volume_header_data_offset += sizeof( fsext_volume_header_t );

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
			 "%s: volume dynamic inode information:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &( volume_header_data[ volume_header_data_offset ] ),
			 sizeof( fsext_volume_dynamic_inode_information_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
	}
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
#endif
	return( -1 );
}

