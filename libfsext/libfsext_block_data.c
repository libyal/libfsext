/*
 * Block functions
 *
 * Copyright (C) 2010-2025, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libfsext_libcerror.h"
#include "libfsext_types.h"

/* Checks if a buffer block data is filled with 0-byte values (empty-block)
 * Returns 1 if empty, 0 if not or -1 on error
 */
int libfsext_block_data_check_empty(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsext_aligned_t *aligned_data_index = NULL;
	libfsext_aligned_t *aligned_data_start = NULL;
	uint8_t *data_index                    = NULL;
	uint8_t *data_start                    = NULL;
	static char *function                  = "libfsext_block_data_check_empty";

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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	data_start = (uint8_t *) data;
	data_index = (uint8_t *) data + 1;
	data_size -= 1;

	/* Only optimize for data larger than the alignment
	 */
	if( data_size > ( 2 * sizeof( libfsext_aligned_t ) ) )
	{
		/* Align the data start
		 */
		while( ( (intptr_t) data_start % sizeof( libfsext_aligned_t ) ) != 0 )
		{
			if( *data_start != *data_index )
			{
				return( 0 );
			}
			data_start += 1;
			data_index += 1;
			data_size  -= 1;
		}
		/* Align the data index
		 */
		while( ( (intptr_t) data_index % sizeof( libfsext_aligned_t ) ) != 0 )
		{
			if( *data_start != *data_index )
			{
				return( 0 );
			}
			data_index += 1;
			data_size  -= 1;
		}
		aligned_data_start = (libfsext_aligned_t *) data_start;
		aligned_data_index = (libfsext_aligned_t *) data_index;

		while( data_size > sizeof( libfsext_aligned_t ) )
		{
			if( *aligned_data_start != *aligned_data_index )
			{
				return( 0 );
			}
			aligned_data_index += 1;
			data_size          -= sizeof( libfsext_aligned_t );
		}
		data_index = (uint8_t *) aligned_data_index;
	}
	while( data_size != 0 )
	{
		if( *data_start != *data_index )
		{
			return( 0 );
		}
		data_index += 1;
		data_size  -= 1;
	}
	return( 1 );
}

