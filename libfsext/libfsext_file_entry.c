/*
 * File entry functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include "libfsext_definitions.h"
#include "libfsext_directory.h"
#include "libfsext_directory_entry.h"
#include "libfsext_file_entry.h"
#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
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
	if( ( inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_DIRECTORY )
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
		     io_handle,
		     file_io_handle,
		     inode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory for inode: %" PRIu32 ".",
			 function,
			 inode_number );

			goto on_error;
		}
	}
	else if( ( inode->file_mode & 0xf000 ) == LIBFSEXT_FILE_TYPE_REGULAR_FILE )
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
	}
	internal_file_entry->io_handle       = io_handle;
	internal_file_entry->file_io_handle  = file_io_handle;
	internal_file_entry->inode_table     = inode_table;
	internal_file_entry->inode           = inode;
	internal_file_entry->directory_entry = directory_entry;
	internal_file_entry->flags           = flags;

	*file_entry = (libfsext_file_entry_t *) internal_file_entry;

	return( 1 );

on_error:
	if( internal_file_entry != NULL )
	{
		if( internal_file_entry->directory != NULL )
		{
			libfsext_directory_free(
			 &( internal_file_entry->directory ),
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
		memory_free(
		 internal_file_entry );
	}
	return( result );
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

		return( -1 );
	}
	return( result );
}

/* Retrieves the access date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_access_time(
     libfsext_file_entry_t *file_entry,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_access_time";

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

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the inode change time date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_inode_change_time(
     libfsext_file_entry_t *file_entry,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_inode_change_time";

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

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the modification date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_modification_time(
     libfsext_file_entry_t *file_entry,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_modification_time";

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

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the deletion date and time
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_deletion_time(
     libfsext_file_entry_t *file_entry,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_deletion_time";

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

		return( -1 );
	}
	return( 1 );
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

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the user identifier
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_file_entry_get_user_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *user_identifier,
     libcerror_error_t **error )
{
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_user_identifier";

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
	if( libfsext_inode_get_user_identifier(
	     internal_file_entry->inode,
	     user_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve user identifier from inode.",
		 function );

		return( -1 );
	}
	return( 1 );
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

		return( -1 );
	}
	return( 1 );
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
	if( internal_file_entry->directory_entry == NULL )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_get_utf8_name_size(
	     internal_file_entry->directory_entry,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 name from directory entry.",
		 function );

		return( -1 );
	}
	return( 1 );
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
	if( internal_file_entry->directory_entry == NULL )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_get_utf8_name(
	     internal_file_entry->directory_entry,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 name from directory entry.",
		 function );

		return( -1 );
	}
	return( 1 );
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
	if( internal_file_entry->directory_entry == NULL )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_get_utf16_name_size(
	     internal_file_entry->directory_entry,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 name from directory entry.",
		 function );

		return( -1 );
	}
	return( 1 );
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
	if( internal_file_entry->directory_entry == NULL )
	{
		return( 0 );
	}
	if( libfsext_directory_entry_get_utf16_name(
	     internal_file_entry->directory_entry,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 name from directory entry.",
		 function );

		return( -1 );
	}
	return( 1 );
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

	if( internal_file_entry->directory == NULL )
	{
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
		*number_of_sub_file_entries = 0;
	}
	else
	{
		if( libfsext_directory_get_number_of_entries(
		     internal_file_entry->directory,
		     number_of_sub_file_entries,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of entries from directory.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
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
	libfsext_directory_t *directory                     = NULL;
	libfsext_directory_entry_t *directory_entry         = NULL;
	libfsext_directory_entry_t *safe_directory_entry    = NULL;
	libfsext_inode_t *inode                             = NULL;
	libfsext_inode_t *safe_inode                        = NULL;
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_index";
	uint32_t inode_number                               = 0;

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
	if( libfsext_directory_get_entry_by_inode_number(
	     internal_file_entry->directory,
	     directory_entry->inode_number,
	     &directory_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory entry for inode: %" PRIu32 ".",
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
	     inode_number,
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
	libfsext_directory_entry_t *directory_entry         = NULL;
	libfsext_directory_entry_t *sub_directory_entry     = NULL;
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	libfsext_inode_t *inode                             = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_utf8_name";
	uint32_t inode_number                               = 0;
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
	     inode_number,
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
	libfsext_directory_entry_t *directory_entry         = NULL;
	libfsext_directory_entry_t *sub_directory_entry     = NULL;
	libfsext_internal_file_entry_t *internal_file_entry = NULL;
	libfsext_inode_t *inode                             = NULL;
	static char *function                               = "libfsext_file_entry_get_sub_file_entry_by_utf16_name";
	uint32_t inode_number                               = 0;
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
	     inode_number,
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

/* TODO */
	read_count = -1;

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from data cluster block stream.",
		 function );

		return( -1 );
	}
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
	static char *function = "libfsext_file_entry_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libfsext_file_entry_seek_offset(
	     file_entry,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libfsext_file_entry_read_buffer(
	              file_entry,
	              buffer,
	              buffer_size,
	              error );

	if( read_count <= -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
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

/* TODO */
	offset = -1;

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in data cluster block stream.",
		 function );

		return( -1 );
	}
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
	static char *function                                = "libfsext_file_entry_get_offset";

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

/* TODO */
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	offset = -1;

	return( 1 );
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
	*size = internal_file_entry->data_size;

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

		return( -1 );
	}
	return( 1 );
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

		return( -1 );
	}
	*extent_offset = (off64_t) extent->physical_block_number * (off64_t) internal_file_entry->io_handle->block_size;
	*extent_size   = (size64_t) extent->number_of_blocks * (size64_t) internal_file_entry->io_handle->block_size;
	*extent_flags  = 0;

	return( 1 );
}

