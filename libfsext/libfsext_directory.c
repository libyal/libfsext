/*
 * Directory functions
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

#include "libfsext_block.h"
#include "libfsext_block_vector.h"
#include "libfsext_definitions.h"
#include "libfsext_directory.h"
#include "libfsext_directory_entry.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdata.h"
#include "libfsext_libfcache.h"
#include "libfsext_libuna.h"

/* Creates a directory
 * Make sure the value directory is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_initialize(
     libfsext_directory_t **directory,
     libcerror_error_t **error )
{
	static char *function = "libfsext_directory_initialize";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory value already set.",
		 function );

		return( -1 );
	}
	*directory = memory_allocate_structure(
	              libfsext_directory_t );

	if( *directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *directory,
	     0,
	     sizeof( libfsext_directory_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory.",
		 function );

		memory_free(
		 *directory );

		*directory = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *directory )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *directory != NULL )
	{
		memory_free(
		 *directory );

		*directory = NULL;
	}
	return( -1 );
}

/* Frees a directory
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_free(
     libfsext_directory_t **directory,
     libcerror_error_t **error )
{
	static char *function = "libfsext_directory_free";
	int result            = 1;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( *directory != NULL )
	{
		if( libcdata_array_free(
		     &( ( *directory )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_directory_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 *directory );

		*directory = NULL;
	}
	return( result );
}

/* Reads the directory entries from block data
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_read_block_data(
     libfsext_directory_t *directory,
     const uint8_t *data,
     size_t data_size,
     uint32_t *directory_entry_index,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry = NULL;
	static char *function                       = "libfsext_directory_read_block_data";
	size_t data_offset                          = 0;
	uint32_t safe_directory_entry_index         = 0;
	int entry_index                             = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
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
	if( directory_entry_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory entry index.",
		 function );

		return( -1 );
	}
	safe_directory_entry_index = *directory_entry_index;

	while( data_offset < data_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading directory entry: %" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx ")\n",
			 safe_directory_entry_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfsext_directory_entry_initialize(
		     &directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create directory entry: %" PRIu32 ".",
			 function,
			 safe_directory_entry_index );

			goto on_error;
		}
		if( libfsext_directory_entry_read_data(
		     directory_entry,
		     &( data[ data_offset ] ),
		     data_size - data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory entry: %" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx ").",
			 function,
			 safe_directory_entry_index,
			 data_offset,
			 data_offset );

			goto on_error;
		}
		if( directory_entry->size == 0 )
		{
			if( libfsext_directory_entry_free(
			     &directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory entry: %" PRIu32 ".",
				 function,
				 safe_directory_entry_index );

				goto on_error;
			}
			break;
		}
		data_offset += directory_entry->size;

/* TODO lost+found has directory entries with size but no values */
		if( ( ( directory_entry->name_size == 2 )
		  && ( directory_entry->name[ 0 ] == '.' ) )
		 || ( ( directory_entry->name_size == 3 )
		  && ( directory_entry->name[ 0 ] == '.' )
		  && ( directory_entry->name[ 1 ] == '.' ) )
		 || ( directory_entry->inode_number == 0 ) )
		{
			if( libfsext_directory_entry_free(
			     &directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory entry: %" PRIu32 ".",
				 function,
				 safe_directory_entry_index );

				goto on_error;
			}
		}
		else
		{
			if( libcdata_array_append_entry(
			     directory->entries_array,
			     &entry_index,
			     (intptr_t *) directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append directory entry: %" PRIu32 " to array.",
				 function,
				 safe_directory_entry_index );

				goto on_error;
			}
			directory_entry = NULL;
		}
		safe_directory_entry_index++;
	}
	*directory_entry_index = safe_directory_entry_index;

	return( 1 );

on_error:
	if( directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( -1 );
}

/* Reads the directory entries from inline data
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_read_inline_data(
     libfsext_directory_t *directory,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry = NULL;
	static char *function                       = "libfsext_directory_read_inline_data";
	size_t data_offset                          = 0;
	uint32_t directory_entry_index              = 0;
	uint32_t parent_inode_number                = 0;
	int entry_index                             = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
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
	if( ( data_size < 4 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 data,
	 parent_inode_number );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: parent inode number\t\t: %" PRIu32 "\n",
		 function,
		 parent_inode_number );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += 4;

	while( data_offset < data_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading directory entry: %" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx ")\n",
			 directory_entry_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfsext_directory_entry_initialize(
		     &directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create directory entry: %" PRIu32 ".",
			 function,
			 directory_entry_index );

			goto on_error;
		}
		if( libfsext_directory_entry_read_data(
		     directory_entry,
		     &( data[ data_offset ] ),
		     data_size - data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory entry: %" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx ").",
			 function,
			 directory_entry_index,
			 data_offset,
			 data_offset );

			goto on_error;
		}
		if( directory_entry->size == 0 )
		{
			if( libfsext_directory_entry_free(
			     &directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory entry: %" PRIu32 ".",
				 function,
				 directory_entry_index );

				goto on_error;
			}
			break;
		}
		data_offset += directory_entry->size;

/* TODO lost+found has directory entries with size but no values */
		if( ( ( directory_entry->name_size == 2 )
		  && ( directory_entry->name[ 0 ] == '.' ) )
		 || ( ( directory_entry->name_size == 3 )
		  && ( directory_entry->name[ 0 ] == '.' )
		  && ( directory_entry->name[ 1 ] == '.' ) )
		 || ( directory_entry->inode_number == 0 ) )
		{
			if( libfsext_directory_entry_free(
			     &directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory entry: %" PRIu32 ".",
				 function,
				 directory_entry_index );

				goto on_error;
			}
		}
		else
		{
			if( libcdata_array_append_entry(
			     directory->entries_array,
			     &entry_index,
			     (intptr_t *) directory_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append directory entry: %" PRIu32 " to array.",
				 function,
				 directory_entry_index );

				goto on_error;
			}
			directory_entry = NULL;
		}
		directory_entry_index++;
	}
	return( 1 );

on_error:
	if( directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( -1 );
}

/* Reads the directory entries
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_read_file_io_handle(
     libfsext_directory_t *directory,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsext_inode_t *inode,
     libcerror_error_t **error )
{
	libfcache_cache_t *block_cache  = NULL;
	libfdata_vector_t *block_vector = NULL;
	libfsext_block_t *block         = NULL;
	static char *function           = "libfsext_directory_read_file_io_handle";
	size_t inline_data_size         = 0;
	uint32_t directory_entry_index  = 0;
	int block_index                 = 0;
	int number_of_blocks            = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
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
	if( ( inode->file_mode & 0xf000 ) != LIBFSEXT_FILE_TYPE_DIRECTORY )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid inode - unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( io_handle->format_version == 4 )
	 && ( ( inode->flags & LIBFSEXT_INODE_FLAG_INLINE_DATA ) != 0 ) )
	{
		/* Note that inode->data_size can be larger than 60
		 * but inode->data_reference only holds 60 bytes
		 */
		if( inode->data_size < 60 )
		{
			inline_data_size = inode->data_size;
		}
		else
		{
			inline_data_size = 60;
		}
		if( libfsext_directory_read_inline_data(
		     directory,
		     inode->data_reference,
		     inline_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory inline data.",
			 function );

			goto on_error;
		}
	}
	else
	{
		if( libfsext_block_vector_initialize(
		     &block_vector,
		     io_handle,
		     inode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block vector.",
			 function );

			goto on_error;
		}
		if( libfcache_cache_initialize(
		     &block_cache,
		     LIBFSEXT_MAXIMUM_CACHE_ENTRIES_BLOCKS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create block cache.",
			 function );

			goto on_error;
		}
		if( libfdata_vector_get_number_of_elements(
		     block_vector,
		     &number_of_blocks,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of blocks.",
			 function );

			goto on_error;
		}
		for( block_index = 0;
		     block_index < number_of_blocks;
		     block_index++ )
		{
			if( libfdata_vector_get_element_value_by_index(
			     block_vector,
			     (intptr_t *) file_io_handle,
			     (libfdata_cache_t *) block_cache,
			     block_index,
			     (intptr_t **) &block,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve block: %d.",
				 function,
				 block_index );

				goto on_error;
			}
			if( block == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid block.",
				 function );

				goto on_error;
			}
			if( libfsext_directory_read_block_data(
			     directory,
			     block->data,
			     (size_t) block->data_size,
			     &directory_entry_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read directory block: %d.",
				 function,
				 block_index );

				goto on_error;
			}
		}
		if( libfcache_cache_free(
		     &block_cache,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block cache.",
			 function );

			goto on_error;
		}
		if( libfdata_vector_free(
		     &block_vector,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free block vector.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( block_cache != NULL )
	{
		libfcache_cache_free(
		 &block_cache,
		 NULL );
	}
	if( block_vector != NULL )
	{
		libfdata_vector_free(
		 &block_vector,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of entries
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_get_number_of_entries(
     libfsext_directory_t *directory,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libfsext_directory_get_number_of_entries";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific entry
 * Returns 1 if successful or -1 on error
 */
int libfsext_directory_get_entry_by_index(
     libfsext_directory_t *directory,
     int entry_index,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	static char *function = "libfsext_directory_get_entry_by_index";

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     directory->entries_array,
	     entry_index,
	     (intptr_t **) directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the directory entry for an UTF-8 encoded name
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libfsext_directory_get_entry_by_utf8_name(
     libfsext_directory_t *directory,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *safe_directory_entry = NULL;
	static char *function                            = "libfsext_directory_get_entry_by_utf8_name";
	int entry_index                                  = 0;
	int number_of_entries                            = 0;
	int result                                       = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     directory->entries_array,
		     entry_index,
		     (intptr_t **) &safe_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		result = libfsext_directory_entry_compare_with_utf8_string(
		          safe_directory_entry,
		          utf8_string,
		          utf8_string_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare UTF-8 string with directory entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		else if( result == LIBUNA_COMPARE_EQUAL )
		{
			*directory_entry = safe_directory_entry;

			return( 1 );
		}
	}
	*directory_entry = NULL;

	return( 0 );
}

/* Retrieves the directory entry for an UTF-16 encoded name
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libfsext_directory_get_entry_by_utf16_name(
     libfsext_directory_t *directory,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_directory_entry_t **directory_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *safe_directory_entry = NULL;
	static char *function                            = "libfsext_directory_get_entry_by_utf16_name";
	int entry_index                                  = 0;
	int number_of_entries                            = 0;
	int result                                       = 0;

	if( directory == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     directory->entries_array,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     directory->entries_array,
		     entry_index,
		     (intptr_t **) &safe_directory_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		result = libfsext_directory_entry_compare_with_utf16_string(
		          safe_directory_entry,
		          utf16_string,
		          utf16_string_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare UTF-16 string with directory entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		else if( result == LIBUNA_COMPARE_EQUAL )
		{
			*directory_entry = safe_directory_entry;

			return( 1 );
		}
	}
	*directory_entry = NULL;

	return( 0 );
}

