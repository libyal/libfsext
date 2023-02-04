/*
 * Inode table functions
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
#include "libfsext_group_descriptor.h"
#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfcache.h"
#include "libfsext_libfdata.h"
#include "libfsext_superblock.h"

#include "fsext_inode.h"

/* Creates an inode table
 * Make sure the value inode_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_initialize(
     libfsext_inode_table_t **inode_table,
     uint16_t inode_size,
     libfsext_io_handle_t *io_handle,
     libfsext_superblock_t *superblock,
     libcdata_array_t *group_descriptors_array,
     libcerror_error_t **error )
{
	libfsext_group_descriptor_t *group_descriptor = NULL;
	static char *function                         = "libfsext_inode_table_initialize";
	size64_t file_size                            = 0;
	size_t inode_data_size                        = 0;
	off64_t file_offset                           = 0;
	int group_descriptor_index                    = 0;
	int number_of_group_descriptors               = 0;
	int segment_index                             = 0;

	if( inode_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode table.",
		 function );

		return( -1 );
	}
	if( *inode_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid inode table value already set.",
		 function );

		return( -1 );
	}
	if( ( inode_size != 128 )
	 && ( inode_size != 256 )
	 && ( inode_size != 512 )
	 && ( inode_size != 1024 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported inode size.",
		 function );

		return( -1 );
	}
	if( superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid superblock.",
		 function );

		return( -1 );
	}
	if( superblock->block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid superblock - block size value out of bounds.",
		 function );

		return( -1 );
	}
	*inode_table = memory_allocate_structure(
	                libfsext_inode_table_t );

	if( *inode_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create inode table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *inode_table,
	     0,
	     sizeof( libfsext_inode_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear inode table.",
		 function );

		goto on_error;
	}
	if( inode_size != 0 )
	{
		inode_data_size = (size_t) inode_size;
	}
	else if( io_handle->format_version == 4 )
	{
		inode_data_size = sizeof( fsext_inode_ext4_t );
	}
	else if( io_handle->format_version == 3 )
	{
		inode_data_size = sizeof( fsext_inode_ext3_t );
	}
	else
	{
		inode_data_size = sizeof( fsext_inode_ext2_t );
	}
	if( libfdata_vector_initialize(
	     &( ( *inode_table )->inodes_vector ),
	     inode_data_size,
	     (intptr_t *) io_handle,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfdata_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libfsext_inode_read_element_data,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create inodes vector.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     group_descriptors_array,
	     &number_of_group_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of group descriptors.",
		 function );

		goto on_error;
	}
	for( group_descriptor_index = 0;
	     group_descriptor_index < number_of_group_descriptors;
	     group_descriptor_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     group_descriptors_array,
		     group_descriptor_index,
		     (intptr_t **) &group_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve group descriptor: %d.",
			 function,
			 group_descriptor_index );

			goto on_error;
		}
		if( group_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing group descriptor: %d.",
			 function,
			 group_descriptor_index );

			goto on_error;
		}
		if( (uint64_t) group_descriptor->inode_table_block_number > ( (uint64_t) INT64_MAX / superblock->block_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid group descriptor - inode table block number value out of bounds.",
			 function );

			goto on_error;
		}
		file_offset = (off64_t) group_descriptor->inode_table_block_number * superblock->block_size;
		file_size   = (size64_t) superblock->number_of_inodes_per_block_group * inode_data_size;

		if( libfdata_vector_append_segment(
		     ( *inode_table )->inodes_vector,
		     &segment_index,
		     0,
		     file_offset,
		     file_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append segment to inodes vector.",
			 function );

			goto on_error;
		}
	}
	if( libfcache_cache_initialize(
	     &( ( *inode_table )->inodes_cache ),
	     LIBFSEXT_MAXIMUM_CACHE_ENTRIES_INODES,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create inodes cache.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *inode_table != NULL )
	{
		if( ( *inode_table )->inodes_vector != NULL )
		{
			libfdata_vector_free(
			 &( ( *inode_table )->inodes_vector ),
			 NULL );
		}
		memory_free(
		 *inode_table );

		*inode_table = NULL;
	}
	return( -1 );
}

/* Frees an inode_table
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_free(
     libfsext_inode_table_t **inode_table,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_table_free";
	int result            = 1;

	if( inode_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode table.",
		 function );

		return( -1 );
	}
	if( *inode_table != NULL )
	{
		if( libfdata_vector_free(
		     &( ( *inode_table )->inodes_vector ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free inodes vector.",
			 function );

			result = -1;
		}
		if( libfcache_cache_free(
		     &( ( *inode_table )->inodes_cache ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free inodes cache.",
			 function );

			result = -1;
		}
		memory_free(
		 *inode_table );

		*inode_table = NULL;
	}
	return( result );
}

/* Retrieves a specific inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_get_inode_by_number(
     libfsext_inode_table_t *inode_table,
     libbfio_handle_t *file_io_handle,
     uint32_t inode_number,
     libfsext_inode_t **inode,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_table_get_inode_by_number";

	if( inode_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode table.",
		 function );

		return( -1 );
	}
	if( inode_number == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid inode number value zero or less.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Retrieving inode: %" PRIu32 ".\n",
		 inode_number );
	}
#endif
	if( libfdata_vector_get_element_value_by_index(
	     inode_table->inodes_vector,
	     (intptr_t *) file_io_handle,
	     (libfdata_cache_t *) inode_table->inodes_cache,
	     inode_number - 1,
	     (intptr_t **) inode,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode: %" PRIu32 ".",
		 function,
		 inode_number );

		return( -1 );
	}
	return( 1 );
}

