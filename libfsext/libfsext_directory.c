/*
 * Directory functions
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsext_directory.h"
#include "libfsext_directory_entry.h"
#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

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
	libfsext_directory_entry_t *directory_entry = NULL;
	uint8_t *data                               = NULL;
	static char *function                       = "libfsext_directory_read_file_io_handle";
	size_t data_offset                          = 0;
	ssize_t read_count                          = 0;
	off64_t file_offset                         = 0;
	uint32_t block_number                       = 0;
	uint32_t directory_entry_index              = 0;
	uint8_t direct_block_index                  = 0;
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
	if( ( inode->file_mode & 0x4000 ) == 0 ) 
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid inode - unsupported file mode.",
		 function );

		return( -1 );
	}
/* TODO replace by block vector or stream */
	for( direct_block_index = 0;
	     direct_block_index < 12;
	     direct_block_index++ )
	{
		block_number = inode->direct_block_number[ direct_block_index ];

		if( block_number == 0 )
		{
			break;
		}
		file_offset = block_number * io_handle->block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading directory entries at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 file_offset,
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
			 "%s: unable to seek directory entries offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		data = (uint8_t *) memory_allocate(
		                    sizeof( uint8_t ) * (size_t) io_handle->block_size );

		if( data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              data,
		              (size_t) io_handle->block_size,
		              error );

		if( read_count != (ssize_t) io_handle->block_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory entries at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		data_offset = 0;

		while( data_offset < (size_t) io_handle->block_size )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "Reading directory entry: %" PRIu32 "\n",
				 directory_entry_index );
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
			     (size_t) io_handle->block_size - data_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read directory entry: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 directory_entry_index,
				 file_offset + (off64_t) data_offset,
				 file_offset + (off64_t) data_offset );

				goto on_error;
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
			}
			directory_entry = NULL;

			directory_entry_index++;
		}
		memory_free(
		 data );

		data = NULL;
	}
	return( 1 );

on_error:
	if( directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	if( data != NULL )
	{
		memory_free(
		 data );
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

