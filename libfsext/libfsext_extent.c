/*
 * Extent functions
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

#include "libfsext_definitions.h"
#include "libfsext_extent.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_extents.h"

/* Creates an extent
 * Make sure the value extent is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_initialize(
     libfsext_extent_t **extent,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_initialize";

	if( extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent.",
		 function );

		return( -1 );
	}
	if( *extent != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent value already set.",
		 function );

		return( -1 );
	}
	*extent = memory_allocate_structure(
	           libfsext_extent_t );

	if( *extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extent.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extent,
	     0,
	     sizeof( libfsext_extent_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extent.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *extent != NULL )
	{
		memory_free(
		 *extent );

		*extent = NULL;
	}
	return( -1 );
}

/* Frees an extent
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_free(
     libfsext_extent_t **extent,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_free";

	if( extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent.",
		 function );

		return( -1 );
	}
	if( *extent != NULL )
	{
		memory_free(
		 *extent );

		*extent = NULL;
	}
	return( 1 );
}

/* Clones an extent
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_clone(
     libfsext_extent_t **destination_extent,
     libfsext_extent_t *source_extent,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_clone";

	if( destination_extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent.",
		 function );

		return( -1 );
	}
	if( *destination_extent != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination extent value already set.",
		 function );

		return( -1 );
	}
	if( source_extent == NULL )
	{
		*destination_extent = source_extent;

		return( 1 );
	}
	*destination_extent = memory_allocate_structure(
	                       libfsext_extent_t );

	if( *destination_extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination extent.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_extent,
	     source_extent,
	     sizeof( libfsext_extent_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy source to destination extent.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_extent != NULL )
	{
		memory_free(
		 *destination_extent );

		*destination_extent = NULL;
	}
	return( -1 );
}

/* Reads the extent data
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_read_data(
     libfsext_extent_t *extent,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function                = "libfsext_extent_read_data";
	uint32_t physical_block_number_lower = 0;
	uint16_t physical_block_number_upper = 0;

	if( extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent.",
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
	if( ( data_size < sizeof( fsext_extent_ext4_t ) )
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
		 "%s: extent data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extent_ext4_t *) data )->logical_block_number,
	 extent->logical_block_number );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_extent_ext4_t *) data )->number_of_blocks,
	 extent->number_of_blocks );

	byte_stream_copy_to_uint16_little_endian(
	 ( (fsext_extent_ext4_t *) data )->physical_block_number_upper,
	 physical_block_number_upper );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fsext_extent_ext4_t *) data )->physical_block_number_lower,
	 physical_block_number_lower );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: logical block number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 extent->logical_block_number );

		if( extent->number_of_blocks > 32768 )
		{
			libcnotify_printf(
			 "%s: number of blocks\t\t\t\t: %" PRIu64 " (uninitialized)\n",
			 function,
			 extent->number_of_blocks - 32768 );
		}
		else
		{
			libcnotify_printf(
			 "%s: number of blocks\t\t\t\t: %" PRIu64 "\n",
			 function,
			 extent->number_of_blocks );
		}
		libcnotify_printf(
		 "%s: physical block number (upper)\t\t: %" PRIu16 "\n",
		 function,
		 physical_block_number_upper );

		libcnotify_printf(
		 "%s: physical block number (lower)\t\t: %" PRIu32 "\n",
		 function,
		 physical_block_number_lower );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	extent->physical_block_number = ( (uint64_t) physical_block_number_upper << 32 ) | physical_block_number_lower;

	if( extent->number_of_blocks > 32768 )
	{
		extent->number_of_blocks -= 32768;
		extent->range_flags       = LIBFSEXT_EXTENT_FLAG_IS_SPARSE;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: physical block number\t\t\t: %" PRIu32 "\n",
		 function,
		 extent->physical_block_number );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Retrieves the extents values
 * Returns 1 if successful or -1 on error
 */
int libfsext_extent_get_values(
     libfsext_extent_t *extent,
     libfsext_io_handle_t *io_handle,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libcerror_error_t **error )
{
	static char *function = "libfsext_extent_get_values";

	if( extent == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent.",
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
	if( io_handle->block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - block size value out of bounds.",
		 function );

		return( -1 );
	}
	if( extent_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent offset.",
		 function );

		return( -1 );
	}
	if( extent_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent size.",
		 function );

		return( -1 );
	}
	if( extent_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent flags.",
		 function );

		return( -1 );
	}
	if( extent->physical_block_number > ( (uint64_t) INT64_MAX / io_handle->block_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid extent - invalid physical block number value out of bounds.",
		 function );

		return( -1 );
	}
	if( extent->number_of_blocks > ( (uint64_t) UINT64_MAX / io_handle->block_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid extent - invalid number of blocks value out of bounds.",
		 function );

		return( -1 );
	}
	*extent_offset = (off64_t) extent->physical_block_number * (off64_t) io_handle->block_size;
	*extent_size   = (size64_t) extent->number_of_blocks * (size64_t) io_handle->block_size;
	*extent_flags  = extent->range_flags;

	return( 1 );
}

