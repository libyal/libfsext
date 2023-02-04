/*
 * Extent index functions
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

#include "libfsext_extent_index.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_extents.h"

/* Creates an extent index
 * Make sure the value extent_index is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_index_initialize(
     libfsext_extent_index_t **extent_index,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_index_initialize";

	if( extent_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent index.",
		 function );

		return( -1 );
	}
	if( *extent_index != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent index value already set.",
		 function );

		return( -1 );
	}
	*extent_index = memory_allocate_structure(
	                 libfsext_extent_index_t );

	if( *extent_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extent index.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extent_index,
	     0,
	     sizeof( libfsext_extent_index_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extent index.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *extent_index != NULL )
	{
		memory_free(
		 *extent_index );

		*extent_index = NULL;
	}
	return( -1 );
}

/* Frees an extent index
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_index_free(
     libfsext_extent_index_t **extent_index,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_index_free";

	if( extent_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent index.",
		 function );

		return( -1 );
	}
	if( *extent_index != NULL )
	{
		memory_free(
		 *extent_index );

		*extent_index = NULL;
	}
	return( 1 );
}

/* Reads the extent index data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_index_read_data(
     libfsext_extent_index_t *extent_index,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function                = "libfsext_extent_index_read_data";
	uint32_t physical_block_number_lower = 0;
	uint16_t physical_block_number_upper = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit                 = 0;
#endif

	if( extent_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent index.",
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
	if( ( data_size < sizeof( fsext_extent_index_ext4_t ) )
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
		 "%s: extent index data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extent_index_ext4_t *) data )->logical_block_number,
	 extent_index->logical_block_number );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extent_index_ext4_t *) data )->physical_block_number_lower,
	 physical_block_number_lower );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_extent_index_ext4_t *) data )->physical_block_number_upper,
	 physical_block_number_upper );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: logical block number\t\t\t: %" PRIu32 "\n",
		 function,
		 extent_index->logical_block_number );

		libcnotify_printf(
		 "%s: physical block number (lower)\t\t: %" PRIu32 "\n",
		 function,
		 physical_block_number_lower );

		libcnotify_printf(
		 "%s: physical block number (upper)\t\t: %" PRIu16 "\n",
		 function,
		 physical_block_number_upper );

		byte_stream_copy_to_uint16_little_endian(
		 ( (fsext_extent_index_ext4_t *) data )->unknown1,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	extent_index->physical_block_number = ( (uint64_t) physical_block_number_upper << 32 ) | physical_block_number_lower;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: physical block number\t\t\t: %" PRIu32 "\n",
		 function,
		 extent_index->physical_block_number );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

