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
	fsext_volume_header_t volume_header_data;

	static char *function = "libfsext_io_handle_read_volume_header";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
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

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &volume_header_data,
	              sizeof( fsext_volume_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( fsext_volume_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volume header data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: volume header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &volume_header_data,
		 sizeof( fsext_volume_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     volume_header_data.signature,
	     fsext_volume_signature,
	     2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid volume system signature.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.number_of_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of inodes\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.number_of_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.number_of_reserved_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of reserved blocks\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.number_of_unallocated_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated blocks\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.number_of_unallocated_inodes,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of unallocated inodes\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.root_block_group_block_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: root block group block number\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.block_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: block size\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.fragment_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragment size\t\t\t: %" PRIu32 " (%" PRIu32 ")\n",
		 function,
		 1024 << value_32bit,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.blocks_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: blocks per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.fragments_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: fragments per block group\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.inodes_per_block_group,
		 value_32bit );
		libcnotify_printf(
		 "%s: inodes per block group\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

/* TODO print date and time value */

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.last_mount_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: last mount time\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

/* TODO print date and time value */

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.last_written_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: last written time\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: mount count\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.maximum_mount_count,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum mount count\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: signature\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
		 function,
		 volume_header_data.signature[ 0 ],
		 volume_header_data.signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.file_system_state_flags,
		 value_16bit );
		libcnotify_printf(
		 "%s: file system state flagt\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );
		libfsext_debug_print_file_system_state_flags(
		 value_16bit );
		libcnotify_printf(
		 "\n" );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.error_handling_status,
		 value_16bit );
		libcnotify_printf(
		 "%s: error handling status\t\t: %" PRIu16 " (%s)\n",
		 function,
		 value_16bit,
		 libfsext_debug_print_erro_handling_status(
		  value_16bit ) );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.minor_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor version\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

/* TODO print date and time value */

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.last_consistency_check_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: last consistency check time\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

/* TODO print duration/interval value */

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.consistency_check_interval,
		 value_32bit );
		libcnotify_printf(
		 "%s: consistency check interval\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creator operating system\t\t: %" PRIu32 " (%s)\n",
		 function,
		 value_32bit,
		 libfsext_debug_print_creator_operating_system(
		  value_32bit ) );

		byte_stream_copy_to_uint32_little_endian(
		 volume_header_data.major_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: major version\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.reserved_block_uid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block UID\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 volume_header_data.reserved_block_gid,
		 value_16bit );
		libcnotify_printf(
		 "%s: reserved block GID\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

