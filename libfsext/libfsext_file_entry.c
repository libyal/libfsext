/*
 * File entry functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfsext_block_stream.h"
#include "libfsext_definitions.h"
#include "libfsext_directory.h"
#include "libfsext_directory_entry.h"
#include "libfsext_file_entry.h"
#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libcthreads.h"
#include "libfsext_libuna.h"
#include "libfsext_types.h"

/* Creates a file entry
 * Make sure the value file_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_initialize(
     libfsext_file_entry_t **file_entry,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsext_inode_table_t *inode_table,
     uint32_t inode_number,
     libfsext_inode_t *inode,
     libfsext_directory_entry_t *directory_entry,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_initialize";

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( *file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file entry value already set.",
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
	internal_file_entry = memory_allocate_structure(
	                       libfsext_internal_file_entry_t );

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file_entry,
	     0,
	     sizeof( libfsext_internal_file_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file entry.",
		 function );

		memory_free(
		 internal_file_entry );

		return( -1 );
	}
	if( ( ( inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_REGULAR_FILE )
	 || ( ( inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_SYMBOLIC_LINK ) )
	{
		if( libfsext_inode_get_data_size(
		     inode,
		     (uint64_t *) &( internal_file_entry->data_size ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data size from inode.",
			 function );

			goto on_error;
		}
		if( ( ( inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_REGULAR_FILE )
		 || ( internal_file_entry->data_size >= 60 ) )
		{
			if( libfsext_block_stream_initialize(
			     &( internal_file_entry->data_block_stream ),
			     io_handle,
			     inode,
			     internal_file_entry->data_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data block stream.",
				 function );

				goto on_error;
			}
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_file_entry->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_file_entry->io_handle       = io_handle;
	internal_file_entry->file_io_handle  = file_io_handle;
	internal_file_entry->inode_table     = inode_table;
	internal_file_entry->inode_number    = inode_number;
	internal_file_entry->inode           = inode;
	internal_file_entry->directory_entry = directory_entry;
	internal_file_entry->flags           = flags;

	*file_entry = (libfsext_file_entry_t *) internal_file_entry;

	return( 1 );

on_error:
	if( internal_file_entry != NULL )
	{
		if( internal_file_entry->data_block_stream != NULL )
		{
			libfdata_stream_free(
			 &( internal_file_entry->data_block_stream ),
			 NULL );
		}
		memory_free(
		 internal_file_entry );
	}
	return( -1 );
}

/* Frees a file entry
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_free(
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_free";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( *file_entry != NULL )
	{
		internal_file_entry = (libfsext_internal_file_entry_t *) *file_entry;
		*file_entry         = NULL;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_file_entry->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		/* The file_io_handle and io_handle references are freed elsewhere
		 */
		if( internal_file_entry->inode != NULL )
		{
			if( libfsext_inode_free(
			     &( internal_file_entry->inode ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free inode.",
				 function );

				result = -1;
			}
		}
		if( internal_file_entry->directory_entry != NULL )
		{
			if( libfsext_directory_entry_free(
			     &( internal_file_entry->directory_entry ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory entry.",
				 function );

				result = -1;
			}
		}
		if( internal_file_entry->directory != NULL )
		{
			if( libfsext_directory_free(
			     &( internal_file_entry->directory ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free directory.",
				 function );

				result = -1;
			}
		}
		if( internal_file_entry->data_block_stream != NULL )
		{
			if( libfdata_stream_free(
			     &( internal_file_entry->data_block_stream ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data block stream.",
				 function );

				result = -1;
			}
		}
		if( internal_file_entry->symbolic_link_data != NULL )
		{
			memory_free(
			 internal_file_entry->symbolic_link_data );
		}
		memory_free(
		 internal_file_entry );
	}
	return( result );
}

/* Determines the directory
 * Returns 1 if successful or -1 on error
 */
int libfsext_internal_file_entry_get_directory(
     libfsext_internal_file_entry_t *internal_file_entry,
     libcerror_error_t **error )
{
	static char *function = "libfsext_internal_file_entry_get_directory";

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file entry - directory value already set.",
		 function );

		return( -1 );
	}
	if( ( internal_file_entry->inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_DIRECTORY )
	{
		if( libfsext_directory_initialize(
		     &( internal_file_entry->directory ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create directory.",
			 function );

			goto on_error;
		}
		if( libfsext_directory_read_file_io_handle(
		     internal_file_entry->directory,
		     internal_file_entry->io_handle,
		     internal_file_entry->file_io_handle,
		     internal_file_entry->inode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory for inode: %" PRIu64 ".",
			 function,
			 internal_file_entry->inode_number );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( internal_file_entry->directory != NULL )
	{
		libfsext_directory_free(
		 &( internal_file_entry->directory ),
		 NULL );
	}
	return( -1 );
}

/* Determines the symbolic link data
 * Returns 1 if successful or -1 on error
 */
int libfsext_internal_file_entry_get_symbolic_link_data(
     libfsext_internal_file_entry_t *internal_file_entry,
     libcerror_error_t **error )
{
	static char *function = "libfsext_internal_file_entry_get_symbolic_link_data";
	ssize_t read_count    = 0;
	uint64_t data_size    = 0;
	uint16_t file_mode    = 0;

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file entry - symbolic link data value already set.",
		 function );

		return( -1 );
	}
	if( libfsext_inode_get_file_mode(
	     internal_file_entry->inode,
	     &file_mode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file mode from inode.",
		 function );

		goto on_error;
	}
	if( ( file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_SYMBOLIC_LINK )
	{
		if( libfsext_inode_get_data_size(
		     internal_file_entry->inode,
		     &data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data size from inode.",
			 function );

			goto on_error;
		}
		if( ( data_size == 0 )
		 || ( data_size > (uint64_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data size value out of bounds.",
			 function );

			goto on_error;
		}
		internal_file_entry->symbolic_link_data = (uint8_t *) memory_allocate(
		                                                       sizeof( uint8_t ) * (size_t) data_size );

		if( internal_file_entry->symbolic_link_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create symbolic link data.",
			 function );

			goto on_error;
		}
		internal_file_entry->symbolic_link_data_size = (size_t) data_size;

		if( data_size < 60 )
		{
			if( memory_copy(
			     internal_file_entry->symbolic_link_data,
			     internal_file_entry->inode->data_reference,
			     (size_t) data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to copy data reference data.",
				 function );

				goto on_error;
			}
		}
		else
		{
			read_count = libfdata_stream_read_buffer_at_offset(
			              internal_file_entry->data_block_stream,
			              (intptr_t *) internal_file_entry->file_io_handle,
			              internal_file_entry->symbolic_link_data,
			              (size_t) data_size,
			              0,
			              0,
			              error );

			if( read_count != (ssize_t) data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read from data block stream.",
				 function );

				goto on_error;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: symbolic link data:\n",
			 function );
			libcnotify_print_data(
			 internal_file_entry->symbolic_link_data,
			 internal_file_entry->symbolic_link_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
	}
	return( 1 );

on_error:
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		memory_free(
		 internal_file_entry->symbolic_link_data );

		internal_file_entry->symbolic_link_data = NULL;
	}
	internal_file_entry->symbolic_link_data_size = 0;

	return( -1 );
}

/* Determines if the file entry is empty
 * Returns 1 if empty, 0 if not or -1 on error
 */
int libfsext_file_entry_is_empty(
     libfsext_file_entry_t *file_entry,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_is_empty";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	result = libfsext_inode_is_empty(
	          internal_file_entry->inode,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if inode is empty.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the inode number
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_inode_number(
     libfsext_file_entry_t *file_entry,
     uint32_t *inode_number,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_inode_number";

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( inode_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid inode number.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*inode_number = internal_file_entry->inode_number;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the access date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_access_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_access_time";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_access_time(
	     internal_file_entry->inode,
	     posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve access time from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the creation date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_creation_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_creation_time";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	result = libfsext_inode_get_creation_time(
	          internal_file_entry->inode,
	          posix_time,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve creation time from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the inode change time date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_inode_change_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_inode_change_time";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_inode_change_time(
	     internal_file_entry->inode,
	     posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode change time time from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the modification date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_modification_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_modification_time";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_modification_time(
	     internal_file_entry->inode,
	     posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve modification time from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the deletion date and time
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_deletion_time(
     libfsext_file_entry_t *file_entry,
     int32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_deletion_time";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_deletion_time(
	     internal_file_entry->inode,
	     posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve deletion time from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the file mode
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_file_mode(
     libfsext_file_entry_t *file_entry,
     uint16_t *file_mode,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_file_mode";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_file_mode(
	     internal_file_entry->inode,
	     file_mode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file mode from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the owner identifier
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_owner_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *owner_identifier,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_owner_identifier";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_owner_identifier(
	     internal_file_entry->inode,
	     owner_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve owner identifier from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the group identifier
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_group_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *group_identifier,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_group_identifier";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_group_identifier(
	     internal_file_entry->inode,
	     group_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve group identifier from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf8_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf8_name_size";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->directory_entry != NULL )
	{
		result = libfsext_directory_entry_get_utf8_name_size(
		          internal_file_entry->directory_entry,
		          utf8_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of UTF-8 name from directory entry.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf8_name(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf8_name";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->directory_entry != NULL )
	{
		result = libfsext_directory_entry_get_utf8_name(
		          internal_file_entry->directory_entry,
		          utf8_string,
		          utf8_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 name from directory entry.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf16_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf16_name_size";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->directory_entry != NULL )
	{
		result = libfsext_directory_entry_get_utf16_name_size(
		          internal_file_entry->directory_entry,
		          utf16_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of UTF-16 name from directory entry.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf16_name(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf16_name";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->directory_entry != NULL )
	{
		result = libfsext_directory_entry_get_utf16_name(
		          internal_file_entry->directory_entry,
		          utf16_string,
		          utf16_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 name from directory entry.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-8 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf8_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf8_symbolic_link_target_size";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->symbolic_link_data == NULL )
	{
		if( libfsext_internal_file_entry_get_symbolic_link_data(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine symbolic link data.",
			 function );

			result = -1;
		}
	}
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		result = libuna_utf8_string_size_from_utf8_stream(
		          internal_file_entry->symbolic_link_data,
		          internal_file_entry->symbolic_link_data_size,
		          utf8_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-8 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf8_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf8_symbolic_link_target";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->symbolic_link_data == NULL )
	{
		if( libfsext_internal_file_entry_get_symbolic_link_data(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine symbolic link data.",
			 function );

			result = -1;
		}
	}
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		result = libuna_utf8_string_copy_from_utf8_stream(
		          utf8_string,
		          utf8_string_size,
		          internal_file_entry->symbolic_link_data,
		          internal_file_entry->symbolic_link_data_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-16 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf16_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf16_symbolic_link_target_size";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->symbolic_link_data == NULL )
	{
		if( libfsext_internal_file_entry_get_symbolic_link_data(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine symbolic link data.",
			 function );

			result = -1;
		}
	}
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		result = libuna_utf16_string_size_from_utf8_stream(
		          internal_file_entry->symbolic_link_data,
		          internal_file_entry->symbolic_link_data_size,
		          utf16_string_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-16 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_file_entry_get_utf16_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_utf16_symbolic_link_target";
	int result                                          = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->symbolic_link_data == NULL )
	{
		if( libfsext_internal_file_entry_get_symbolic_link_data(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine symbolic link data.",
			 function );

			result = -1;
		}
	}
	if( internal_file_entry->symbolic_link_data != NULL )
	{
		result = libuna_utf16_string_copy_from_utf8_stream(
		          utf16_string,
		          utf16_string_size,
		          internal_file_entry->symbolic_link_data,
		          internal_file_entry->symbolic_link_data_size,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the number of sub file entries
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_number_of_sub_file_entries(
     libfsext_file_entry_t *file_entry,
     int *number_of_sub_file_entries,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_number_of_sub_file_entries";
	int result                                          = 1;
	int safe_number_of_sub_file_entries                 = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( number_of_sub_file_entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sub file entries.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( internal_file_entry->directory == NULL )
	{
		if( libfsext_internal_file_entry_get_directory(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine directory.",
			 function );

			result = -1;
		}
	}
	if( internal_file_entry->directory != NULL )
	{
		if( libfsext_directory_get_number_of_entries(
		     internal_file_entry->directory,
		     &safe_number_of_sub_file_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of entries from directory.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( result == 1 )
	{
		*number_of_sub_file_entries = safe_number_of_sub_file_entries;
	}
	return( result );
}

/* Retrieves the sub file entry for the specific index
 * Returns 1 if successful or -1 on error
 */
int libfsext_internal_file_entry_get_sub_file_entry_by_index(
     libfsext_internal_file_entry_t *internal_file_entry,
     int sub_file_entry_index,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_directory_t *directory                  = NULL;
	libfsext_directory_entry_t *directory_entry      = NULL;
	libfsext_directory_entry_t *safe_directory_entry = NULL;
	libfsext_inode_t *inode                          = NULL;
	libfsext_inode_t *safe_inode                     = NULL;
	static char *function                            = "libfsext_file_entry_get_sub_file_entry_by_index";

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->directory == NULL )
	{
		if( libfsext_internal_file_entry_get_directory(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine directory.",
			 function );

			goto on_error;
		}
	}
	if( libfsext_directory_get_entry_by_index(
	     internal_file_entry->directory,
	     sub_file_entry_index,
	     &directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d from directory.",
		 function,
		 sub_file_entry_index );

		goto on_error;
	}
	if( directory_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing directory entry: %d.",
		 function,
		 sub_file_entry_index );

		goto on_error;
	}
	if( libfsext_inode_table_get_inode_by_number(
	     internal_file_entry->inode_table,
	     internal_file_entry->file_io_handle,
	     directory_entry->inode_number,
	     &inode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode number: %" PRIu32 ".",
		 function,
		 directory_entry->inode_number );

		goto on_error;
	}
	if( inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing inode: %" PRIu32 ".",
		 function,
		 directory_entry->inode_number );

		goto on_error;
	}
	if( libfsext_inode_clone(
	     &safe_inode,
	     inode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create inode.",
		 function );

		goto on_error;
	}
	if( libfsext_directory_entry_clone(
	     &safe_directory_entry,
	     directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory entry.",
		 function );

		goto on_error;
	}
	/* libfsext_file_entry_initialize takes over management of safe_inode and safe_directory_entry
	 */
	if( libfsext_file_entry_initialize(
	     sub_file_entry,
	     internal_file_entry->io_handle,
	     internal_file_entry->file_io_handle,
	     internal_file_entry->inode_table,
	     directory_entry->inode_number,
	     safe_inode,
	     safe_directory_entry,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub file entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( safe_directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &safe_directory_entry,
		 NULL );
	}
	if( safe_inode != NULL )
	{
		libfsext_inode_free(
		 &safe_inode,
		 NULL );
	}
	if( directory != NULL )
	{
		libfsext_directory_free(
		 &directory,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sub file entry for the specific index
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_sub_file_entry_by_index(
     libfsext_file_entry_t *file_entry,
     int sub_file_entry_index,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_index";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_internal_file_entry_get_sub_file_entry_by_index(
	     internal_file_entry,
	     sub_file_entry_index,
	     sub_file_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub file entry: %d.",
		 function,
		 sub_file_entry_index );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the sub file entry for an UTF-8 encoded name
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_internal_file_entry_get_sub_file_entry_by_utf8_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry     = NULL;
	libfsext_directory_entry_t *sub_directory_entry = NULL;
	libfsext_inode_t *inode                         = NULL;
	static char *function                           = "libfsext_internal_file_entry_get_sub_file_entry_by_utf8_name";
	int result                                      = 0;

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->directory == NULL )
	{
		if( libfsext_internal_file_entry_get_directory(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine directory.",
			 function );

			goto on_error;
		}
	}
	result = libfsext_directory_get_entry_by_utf8_name(
	          internal_file_entry->directory,
	          utf8_string,
	          utf8_string_length,
	          &directory_entry,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory entry.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_clone(
	     &sub_directory_entry,
	     directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub directory entry.",
		 function );

		goto on_error;
	}
/* TODO set inode */
	/* libfsext_file_entry_initialize takes over management of sub_directory_entry
	 */
	if( libfsext_file_entry_initialize(
	     sub_file_entry,
	     internal_file_entry->io_handle,
	     internal_file_entry->file_io_handle,
	     internal_file_entry->inode_table,
	     sub_directory_entry->inode_number,
	     inode,
	     sub_directory_entry,
	     internal_file_entry->flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub file entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sub_directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &sub_directory_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sub file entry for an UTF-8 encoded name
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_file_entry_get_sub_file_entry_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_utf8_name";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_internal_file_entry_get_sub_file_entry_by_utf8_name(
	     internal_file_entry,
	     utf8_string,
	     utf8_string_length,
	     sub_file_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub file entry.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the sub file entry for an UTF-16 encoded name
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_internal_file_entry_get_sub_file_entry_by_utf16_name(
     libfsext_internal_file_entry_t *internal_file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry     = NULL;
	libfsext_directory_entry_t *sub_directory_entry = NULL;
	libfsext_inode_t *inode                         = NULL;
	static char *function                           = "libfsext_internal_file_entry_get_sub_file_entry_by_utf16_name";
	int result                                      = 0;

	if( internal_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->directory == NULL )
	{
		if( libfsext_internal_file_entry_get_directory(
		     internal_file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine directory.",
			 function );

			goto on_error;
		}
	}
	result = libfsext_directory_get_entry_by_utf16_name(
	          internal_file_entry->directory,
	          utf16_string,
	          utf16_string_length,
	          &directory_entry,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory entry.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_clone(
	     &sub_directory_entry,
	     directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub directory entry.",
		 function );

		goto on_error;
	}
/* TODO set inode */
	/* libfsext_file_entry_initialize takes over management of sub_directory_entry
	 */
	if( libfsext_file_entry_initialize(
	     sub_file_entry,
	     internal_file_entry->io_handle,
	     internal_file_entry->file_io_handle,
	     internal_file_entry->inode_table,
	     sub_directory_entry->inode_number,
	     inode,
	     sub_directory_entry,
	     internal_file_entry->flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sub file entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sub_directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &sub_directory_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the sub file entry for an UTF-16 encoded name
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_file_entry_get_sub_file_entry_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_utf16_name";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( sub_file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sub file entry.",
		 function );

		return( -1 );
	}
	if( *sub_file_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sub file entry value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_internal_file_entry_get_sub_file_entry_by_utf16_name(
	     internal_file_entry,
	     utf16_string,
	     utf16_string_length,
	     sub_file_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sub file entry.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Reads data at the current offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfsext_file_entry_read_buffer(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_read_buffer";
	ssize_t read_count                                  = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( ( internal_file_entry->inode->file_mode & 0xf000 ) != LIBFSEXT_FILE_TYPE_REGULAR_FILE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file entry - invalid inode - unsupported file mode not a regular file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libfdata_stream_read_buffer(
	              internal_file_entry->data_block_stream,
	              (intptr_t *) internal_file_entry->file_io_handle,
	              buffer,
	              buffer_size,
	              0,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from data block stream.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libfsext_file_entry_read_buffer_at_offset(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_read_buffer_at_offset";
	ssize_t read_count                                  = 0;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( ( internal_file_entry->inode->file_mode & 0xf000 ) != LIBFSEXT_FILE_TYPE_REGULAR_FILE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file entry - invalid inode - unsupported file mode not a regular file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libfdata_stream_read_buffer_at_offset(
	              internal_file_entry->data_block_stream,
	              (intptr_t *) internal_file_entry->file_io_handle,
	              buffer,
	              buffer_size,
	              offset,
	              0,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from data block stream.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Seeks a certain offset in the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libfsext_file_entry_seek_offset(
         libfsext_file_entry_t *file_entry,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                                = "libfsext_file_entry_seek_offset";

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( ( internal_file_entry->inode->file_mode & 0xf000 ) != LIBFSEXT_FILE_TYPE_REGULAR_FILE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file entry - invalid inode - unsupported file mode not a regular file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libfdata_stream_seek_offset(
	          internal_file_entry->data_block_stream,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in data block stream.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the data
 * Returns the offset if successful or -1 on error
 */
int libfsext_file_entry_get_offset(
     libfsext_file_entry_t *file_entry,
     off64_t *offset,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_offset";
	int result                                          = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
		 function );

		return( -1 );
	}
	if( ( internal_file_entry->inode->file_mode & 0xf000 ) != LIBFSEXT_FILE_TYPE_REGULAR_FILE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file entry - invalid inode - unsupported file mode not a regular file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfdata_stream_get_offset(
	     internal_file_entry->data_block_stream,
	     offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset from data block stream.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the data
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_size(
     libfsext_file_entry_t *file_entry,
     size64_t *size,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_size";

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*size = internal_file_entry->data_size;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the number of extents of the data
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_number_of_extents(
     libfsext_file_entry_t *file_entry,
     int *number_of_extents,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_number_of_extents";
	int result                                           = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_number_of_extents(
	     internal_file_entry->inode,
	     number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents from inode.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves a specific extent of the data
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_extent_by_index(
     libfsext_file_entry_t *file_entry,
     int extent_index,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libcerror_error_t **error )
{
	libfsext_extent_t *extent                           = NULL;
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_extent_by_index";
	int result                                           = 1;

	if( file_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file entry.",
		 function );

		return( -1 );
	}
	internal_file_entry = (libfsext_internal_file_entry_t *) file_entry;

	if( internal_file_entry->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file_entry->inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file entry - missing inode.",
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
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libfsext_inode_get_extent_by_index(
	     internal_file_entry->inode,
	     extent_index,
	     &extent,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent: %d from inode.",
		 function,
		 extent_index );

		result = -1;
	}
#if defined( HAVE_LIBFSEXT_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file_entry->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( result == 1 )
	{
		*extent_offset = (off64_t) extent->physical_block_number * (off64_t) internal_file_entry->io_handle->block_size;
		*extent_size   = (size64_t) extent->number_of_blocks * (size64_t) internal_file_entry->io_handle->block_size;
		*extent_flags  = extent->range_flags;
	}
	return( result );
}

