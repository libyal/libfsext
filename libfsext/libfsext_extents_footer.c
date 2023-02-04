/*
 * Extents footer functions
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

#include "libfsext_extents_footer.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_extents.h"

/* Creates an extents footer
 * Make sure the value extents_footer is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_footer_initialize(
     libfsext_extents_footer_t **extents_footer,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_footer_initialize";

	if( extents_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents footer.",
		 function );

		return( -1 );
	}
	if( *extents_footer != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extents footer value already set.",
		 function );

		return( -1 );
	}
	*extents_footer = memory_allocate_structure(
	                   libfsext_extents_footer_t );

	if( *extents_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extents footer.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extents_footer,
	     0,
	     sizeof( libfsext_extents_footer_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extents footer.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *extents_footer != NULL )
	{
		memory_free(
		 *extents_footer );

		*extents_footer = NULL;
	}
	return( -1 );
}

/* Frees an extents footer
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_footer_free(
     libfsext_extents_footer_t **extents_footer,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_footer_free";

	if( extents_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents footer.",
		 function );

		return( -1 );
	}
	if( *extents_footer != NULL )
	{
		memory_free(
		 *extents_footer );

		*extents_footer = NULL;
	}
	return( 1 );
}

/* Reads the extents footer data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extents_footer_read_data(
     libfsext_extents_footer_t *extents_footer,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extents_footer_read_data";

	if( extents_footer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extents footer.",
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
	if( ( data_size < sizeof( fsext_extents_footer_ext4_t ) )
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
		 "%s: extents footer data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extents_footer_ext4_t *) data )->checksum,
	 extents_footer->checksum );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 extents_footer->checksum );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

