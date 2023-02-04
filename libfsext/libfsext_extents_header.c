/*
 * Extents header functions
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

#include "libfsext_extents_header.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_extents.h"

const char *fsext_extents_header_signature = "\x0a\xf3";

/* Creates an extents header
 * Make sure the value extents_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_header_initialize(
     libfsext_extents_header_t **extents_header,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_header_initialize";

	if( extents_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents header.",
		 function );

		return( -1 );
	}
	if( *extents_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extents header value already set.",
		 function );

		return( -1 );
	}
	*extents_header = memory_allocate_structure(
	                   libfsext_extents_header_t );

	if( *extents_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extents header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extents_header,
	     0,
	     sizeof( libfsext_extents_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extents header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *extents_header != NULL )
	{
		memory_free(
		 *extents_header );

		*extents_header = NULL;
	}
	return( -1 );
}

/* Frees an extents header
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_header_free(
     libfsext_extents_header_t **extents_header,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_header_free";

	if( extents_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents header.",
		 function );

		return( -1 );
	}
	if( *extents_header != NULL )
	{
		memory_free(
		 *extents_header );

		*extents_header = NULL;
	}
	return( 1 );
}

/* Reads the extents header data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_header_read_data(
     libfsext_extents_header_t *extents_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit  = 0;
#endif

	if( extents_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents header.",
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
	if( ( data_size < sizeof( fsext_extents_header_ext4_t ) )
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
		 "%s: extents header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( memory_compare(
	     ( (fsext_extents_header_ext4_t *) data )->signature,
	     fsext_extents_header_signature,
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
	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_extents_header_ext4_t *) data )->number_of_extents,
	 extents_header->number_of_extents );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_extents_header_ext4_t *) data )->depth,
	 extents_header->depth );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extents_header_ext4_t *) data )->generation,
	 extents_header->generation );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_extents_header_ext4_t *) data )->signature,
		 value_16bit );
		libcnotify_printf(
		 "%s: signature\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of extents\t\t\t: %" PRIu16 "\n",
		 function,
		 extents_header->number_of_extents );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_extents_header_ext4_t *) data )->maximum_number_of_extents,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum number of extents\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: depth\t\t\t\t: %" PRIu16 "\n",
		 function,
		 extents_header->depth );

		libcnotify_printf(
		 "%s: generation\t\t\t\t: %" PRIu32 "\n",
		 function,
		 extents_header->generation );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( extents_header->depth > 5 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid depth value out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

