/*
 * Volume functions
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsext_bitmap.h"
#include "libfsext_debug.h"
#include "libfsext_definitions.h"
#include "libfsext_group_descriptor.h"
#include "libfsext_file_entry.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libuna.h"
#include "libfsext_superblock.h"
#include "libfsext_volume.h"

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_initialize(
     libfsext_volume_t **volume,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_initialize";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume value already set.",
		 function );

		return( -1 );
	}
	internal_volume = memory_allocate_structure(
	                   libfsext_internal_volume_t );

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume,
	     0,
	     sizeof( libfsext_internal_volume_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume.",
		 function );

		goto on_error;
	}
	if( libfsext_io_handle_initialize(
	     &( internal_volume->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_volume->group_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create group descriptors array.",
		 function );

		goto on_error;
	}
	*volume = (libfsext_volume_t *) internal_volume;

	return( 1 );

on_error:
	if( internal_volume != NULL )
	{
		if( internal_volume->io_handle != NULL )
		{
			libfsext_io_handle_free(
			 &( internal_volume->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_volume );
	}
	return( -1 );
}

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_free(
     libfsext_volume_t **volume,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_free";
	int result                                  = 1;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( *volume != NULL )
	{
		internal_volume = (libfsext_internal_volume_t *) *volume;

		if( internal_volume->file_io_handle != NULL )
		{
			if( libfsext_volume_close(
			     *volume,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close volume.",
				 function );

				result = -1;
			}
		}
		*volume = NULL;

		if( libcdata_array_free(
		     &( internal_volume->group_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_group_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free group descriptors array.",
			 function );

			result = -1;
		}
		if( libfsext_io_handle_free(
		     &( internal_volume->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_volume );
	}
	return( result );
}

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_signal_abort(
     libfsext_volume_t *volume,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_signal_abort";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_volume->io_handle->abort = 1;

	return( 1 );
}

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_open(
     libfsext_volume_t *volume,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_open";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSEXT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libfsext_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_volume->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
        return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_open_wide(
     libfsext_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_open_wide";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSEXT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libfsext_volume_open_file_io_handle(
	     volume,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_volume->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
        return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_open_file_io_handle";
	int bfio_access_flags                       = 0;
	int file_io_handle_is_open                  = 0;
	int file_io_handle_opened_in_library        = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBFSEXT_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSEXT_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBFSEXT_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libfsext_volume_open_read(
	     internal_volume,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
	internal_volume->file_io_handle                   = file_io_handle;
	internal_volume->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
int libfsext_volume_close(
     libfsext_volume_t *volume,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_close";
	int result                                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_volume->file_io_handle_created_in_library != 0 )
		{
			if( libfsext_debug_print_read_offsets(
			     internal_volume->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_volume->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_volume->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_opened_in_library = 0;
	}
	if( internal_volume->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_volume->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_volume->file_io_handle_created_in_library = 0;
	}
	internal_volume->file_io_handle = NULL;

	if( libfsext_io_handle_clear(
	     internal_volume->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( internal_volume->superblock != NULL )
	{
		if( libfsext_superblock_free(
		     &( internal_volume->superblock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free superblock.",
			 function );

			result = -1;
		}
	}
	if( libcdata_array_empty(
	     internal_volume->group_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_group_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty group descriptors array.",
		 function );

		result = -1;
	}
	if( internal_volume->inode_table != NULL )
	{
		if( libfsext_inode_table_free(
		     &( internal_volume->inode_table ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free inode table.",
			 function );

			result = -1;
		}
	}
	return( result );
}

/* Opens a volume for reading
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_open_read(
     libfsext_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libfsext_volume_open_read";
	off64_t file_offset   = 1024;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( libfsext_volume_read_block_groups(
	     internal_volume,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block groups.",
		 function );

		goto on_error;
	}
	if( libfsext_inode_table_initialize(
	     &( internal_volume->inode_table ),
	     internal_volume->io_handle->inode_size,
	     internal_volume->io_handle,
	     internal_volume->superblock,
	     internal_volume->group_descriptors_array,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create inode table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_volume->inode_table != NULL )
	{
		libfsext_inode_table_free(
		 &( internal_volume->inode_table ),
		 NULL );
	}
	libcdata_array_empty(
	 internal_volume->group_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfsext_group_descriptor_free,
	 NULL );

	if( internal_volume->superblock != NULL )
	{
		libfsext_superblock_free(
		 &( internal_volume->superblock ),
		 NULL );
	}
	return( -1 );
}

/* Reads the block groups
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_read_block_groups(
     libfsext_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libfsext_bitmap_t *bitmap                     = NULL;
	libfsext_group_descriptor_t *group_descriptor = NULL;
	libfsext_superblock_t *superblock             = NULL;
	static char *function                         = "libfsext_volume_read_block_groups";
	off64_t block_bitmap_offset                   = 0;
	off64_t block_group_offset                    = 0;
	off64_t group_descriptor_offset               = 0;
	off64_t inode_bitmap_offset                   = 0;
	off64_t superblock_offset                     = 0;
	uint32_t block_group_index                    = 0;
	uint32_t exponent3                            = 3;
	uint32_t exponent5                            = 5;
	uint32_t exponent7                            = 7;
	uint32_t group_descriptor_index               = 0;
	uint32_t number_of_block_groups               = 0;
	uint8_t block_group_has_superblock            = 0;
	int entry_index                               = 0;

	if( internal_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal volume.",
		 function );

		return( -1 );
	}
	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal volume - missing IO handle.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( internal_volume->io_handle->block_size > (uint32_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid internal volume - invalid IO handle - block size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
	do
	{
		if( exponent7 < block_group_index )
		{
			exponent7 *= 7;
		}
		if( exponent5 < block_group_index )
		{
			exponent5 *= 5;
		}
		if( exponent3 < block_group_index )
		{
			exponent3 *= 3;
		}
		block_group_has_superblock = 0;

		if( ( block_group_index == 0 )
		 || ( block_group_index == 1 ) )
		{
			block_group_has_superblock = 1;
		}
		else if( ( internal_volume->superblock != NULL )
		      && ( ( internal_volume->superblock->read_only_compatible_features_flags & 0x00000001UL ) != 0 ) )
		{
			if( ( block_group_index == exponent3 )
			 || ( block_group_index == exponent5 )
			 || ( block_group_index == exponent7 ) )
			{
				block_group_has_superblock = 1;
			}
		}
		group_descriptor_offset = block_group_offset;

		if( block_group_has_superblock != 0 )
		{
			if( ( block_group_offset == 0 )
			 || ( internal_volume->io_handle->block_size == 1024 ) )
			{
				superblock_offset = block_group_offset + 1024;
			}
			else
			{
				superblock_offset = block_group_offset;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "Reading superblock: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 block_group_index,
				 superblock_offset,
				 superblock_offset );
			}
#endif
			if( libfsext_superblock_initialize(
			     &superblock,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create superblock.",
				 function );

				goto on_error;
			}
			if( libfsext_superblock_read_file_io_handle(
			     superblock,
			     file_io_handle,
			     superblock_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read superblock: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 block_group_index,
				 superblock_offset,
				 superblock_offset );

				goto on_error;
			}
			if( block_group_index == 0 )
			{
				internal_volume->io_handle->block_size                          = superblock->block_size;
				internal_volume->io_handle->inode_size                          = superblock->inode_size;
				internal_volume->io_handle->format_revision                     = superblock->format_revision;
				internal_volume->io_handle->compatible_features_flags           = superblock->compatible_features_flags;
				internal_volume->io_handle->incompatible_features_flags         = superblock->incompatible_features_flags;
				internal_volume->io_handle->read_only_compatible_features_flags = superblock->read_only_compatible_features_flags;
				internal_volume->io_handle->format_version                      = superblock->format_version;

				number_of_block_groups = superblock->number_of_block_groups;

				internal_volume->superblock = superblock;
				superblock                  = NULL;
			}
			else
			{
/* TODO compare superblocks */
				if( libfsext_superblock_free(
				     &superblock,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free superblock.",
					 function );

					goto on_error;
				}
			}
			/* The group descriptors are stored in the first block after the superblock
			 */
			if( internal_volume->io_handle->block_size == 1024 )
			{
				group_descriptor_offset = block_group_offset + 1024 + internal_volume->io_handle->block_size;
			}
			else
			{
				group_descriptor_offset = block_group_offset + internal_volume->io_handle->block_size;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "Reading group descriptors: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 block_group_index,
				 group_descriptor_offset,
				 group_descriptor_offset );
			}
#endif
			if( libbfio_handle_seek_offset(
			     file_io_handle,
			     group_descriptor_offset,
			     SEEK_SET,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_SEEK_FAILED,
				 "%s: unable to seek group descriptors: %" PRIu32 " offset: %" PRIi64 " (0x%08" PRIx64 ").",
				 function,
				 block_group_index,
				 group_descriptor_offset,
				 group_descriptor_offset );

				goto on_error;
			}
			for( group_descriptor_index = 0;
			     group_descriptor_index < number_of_block_groups;
			     group_descriptor_index++ )
			{
				if( libfsext_group_descriptor_initialize(
				     &group_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create group descriptor.",
					 function );

					goto on_error;
				}
				if( libfsext_group_descriptor_read_file_io_handle(
				     group_descriptor,
				     internal_volume->io_handle,
				     file_io_handle,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read group descriptor: %" PRIu32 ".",
					 function,
					 group_descriptor_index );

					goto on_error;
				}
				if( block_group_index == 0 )
				{
					if( libcdata_array_append_entry(
					     internal_volume->group_descriptors_array,
					     &entry_index,
					     (intptr_t *) group_descriptor,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
						 "%s: unable to append group descriptor: %" PRIu32 " to array.",
						 function,
						 group_descriptor_index );

						goto on_error;
					}
					group_descriptor = NULL;
				}
				else
				{
/* TODO compare group descriptors */
					if( libfsext_group_descriptor_free(
					     &group_descriptor,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free group descriptor: %" PRIu32 ".",
						 function,
						 group_descriptor_index );

						goto on_error;
					}
				}
			}
		}
#ifdef TODO
/* TODO get group descriptor of block group */

		block_bitmap_offset  = group_descriptor->block_bitmap_block_number * internal_volume->io_handle->block_size;
		inode_bitmap_offset  = group_descriptor->inode_bitmap_block_number * internal_volume->io_handle->block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading block bitmap: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
			 block_group_index,
			 block_bitmap_offset,
			 block_bitmap_offset );
		}
#endif
		if( libfsext_bitmap_initialize(
		     &bitmap,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create bitmap.",
			 function );

			goto on_error;
		}
		if( libfsext_bitmap_read_file_io_handle(
		     bitmap,
		     internal_volume->io_handle,
		     file_io_handle,
		     block_bitmap_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read block bitmap: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 block_group_index,
			 block_bitmap_offset,
			 block_bitmap_offset );

			goto on_error;
		}
		if( libfsext_bitmap_free(
		     &bitmap,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free bitmap.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading inode bitmap: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
			 block_group_index,
			 inode_bitmap_offset,
			 inode_bitmap_offset );
		}
#endif
		if( libfsext_bitmap_initialize(
		     &bitmap,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create bitmap.",
			 function );

			goto on_error;
		}
		if( libfsext_bitmap_read_file_io_handle(
		     bitmap,
		     internal_volume->io_handle,
		     file_io_handle,
		     inode_bitmap_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read inode bitmap at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 inode_bitmap_offset,
			 inode_bitmap_offset );

			goto on_error;
		}
		if( libfsext_bitmap_free(
		     &bitmap,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free bitmap.",
			 function );

			goto on_error;
		}
#endif /* TODO */
		block_group_offset += internal_volume->superblock->block_group_size;

		block_group_index++;
	}
	while( block_group_index < number_of_block_groups );

	return( 1 );

on_error:
	if( bitmap != NULL )
	{
		libfsext_bitmap_free(
		 &bitmap,
		 NULL );
	}
	if( group_descriptor != NULL )
	{
		libfsext_group_descriptor_free(
		 &group_descriptor,
		 NULL );
	}
	if( superblock != NULL )
	{
		libfsext_superblock_free(
		 &superblock,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 encoded label
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_utf8_label_size(
     libfsext_volume_t *volume,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_utf8_label_size";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		if( utf8_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-8 string size.",
			 function );

			return( -1 );
		}
		*utf8_string_size = 0;
	}
	else
	{
		if( libuna_utf8_string_size_from_utf8_stream(
		     internal_volume->superblock->volume_label,
		     16,
		     utf8_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 volume label string size.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded label
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_utf8_label(
     libfsext_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_utf8_label";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		if( utf8_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-8 string.",
			 function );

			return( -1 );
		}
		if( utf8_string_size == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid UTF-8 string size value too small.",
			 function );

			return( -1 );
		}
		if( utf8_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid UTF-8 string size value exceeds maximum.",
			 function );

			return( -1 );
		}
		utf8_string[ 0 ] = 0;
	}
	else
	{
		if( libuna_utf8_string_copy_from_utf8_stream(
		     utf8_string,
		     utf8_string_size,
		     internal_volume->superblock->volume_label,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 volume label string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded label
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_utf16_label_size(
     libfsext_volume_t *volume,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_utf16_label_size";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		if( utf16_string_size == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-16 string size.",
			 function );

			return( -1 );
		}
		*utf16_string_size = 0;
	}
	else
	{
		if( libuna_utf16_string_size_from_utf8_stream(
		     internal_volume->superblock->volume_label,
		     16,
		     utf16_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 volume label string size.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded label
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_utf16_label(
     libfsext_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_utf16_label";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		if( utf16_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid UTF-16 string.",
			 function );

			return( -1 );
		}
		if( utf16_string_size == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid UTF-16 string size value too small.",
			 function );

			return( -1 );
		}
		if( utf16_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid UTF-16 string size value exceeds maximum.",
			 function );

			return( -1 );
		}
		utf16_string[ 0 ] = 0;
	}
	else
	{
		if( libuna_utf16_string_copy_from_utf8_stream(
		     utf16_string,
		     utf16_string_size,
		     internal_volume->superblock->volume_label,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 volume label string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves the last mount time
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_volume_get_last_mount_time(
     libfsext_volume_t *volume,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_last_mount_time";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid posix time.",
		 function );

		return( -1 );
	}
	if( internal_volume->superblock == NULL )
	{
		return( 0 );
	}
	*posix_time = internal_volume->superblock->last_mount_time;

	return( 1 );
}

/* Retrieves the last written time
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfsext_volume_get_last_written_time(
     libfsext_volume_t *volume,
     uint32_t *posix_time,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_last_mount_time";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( posix_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid posix time.",
		 function );

		return( -1 );
	}
	if( internal_volume->superblock == NULL )
	{
		return( 0 );
	}
	*posix_time = internal_volume->superblock->last_written_time;

	return( 1 );
}

/* Retrieves the number of file entries (inodes)
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_number_of_file_entries(
     libfsext_volume_t *volume,
     uint32_t *number_of_file_entries,
     libcerror_error_t **error )
{
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_number_of_file_entries";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing superblock.",
		 function );

		return( -1 );
	}
	if( number_of_file_entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of file entries.",
		 function );

		return( -1 );
	}
	*number_of_file_entries = internal_volume->superblock->number_of_inodes;

	return( 1 );
}

/* Retrieves the file entry of a specific inode
 * Returns 1 if successful or -1 on error
 */
int libfsext_volume_get_file_entry_by_index(
     libfsext_volume_t *volume,
     uint32_t inode_number,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error )
{
	libfsext_inode_t *inode                     = NULL;
	libfsext_inode_t *safe_inode                = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_file_entry_by_index";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

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
	if( libfsext_inode_table_get_inode_by_number(
	     internal_volume->inode_table,
	     internal_volume->file_io_handle,
	     inode_number,
	     &inode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode number: %" PRIu32 ".",
		 function,
		 inode_number );

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
		 inode_number );

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
	/* libfsext_file_entry_initialize takes over management of safe_inode
	 */
	if( libfsext_file_entry_initialize(
	     file_entry,
	     internal_volume->io_handle,
	     internal_volume->file_io_handle,
	     internal_volume->inode_table,
	     inode_number,
	     safe_inode,
	     NULL,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( safe_inode != NULL )
	{
		libfsext_inode_free(
		 &safe_inode,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the root directory file entry
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libfsext_volume_get_root_directory(
     libfsext_volume_t *volume,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error )
{
	libfsext_inode_t *inode                     = NULL;
	libfsext_inode_t *safe_inode                = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_root_directory";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

	if( internal_volume->superblock == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing superblock.",
		 function );

		return( -1 );
	}
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
	if( internal_volume->superblock->number_of_inodes < LIBFSEXT_INODE_NUMBER_ROOT_DIRECTORY )
	{
		return( 0 );
	}
	if( libfsext_inode_table_get_inode_by_number(
	     internal_volume->inode_table,
	     internal_volume->file_io_handle,
	     LIBFSEXT_INODE_NUMBER_ROOT_DIRECTORY,
	     &inode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode number: 2.",
		 function );

		goto on_error;
	}
	if( inode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing inode: 2.",
		 function );

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
	/* libfsext_file_entry_initialize takes over management of safe_inode
	 */
	if( libfsext_file_entry_initialize(
	     file_entry,
	     internal_volume->io_handle,
	     internal_volume->file_io_handle,
	     internal_volume->inode_table,
	     LIBFSEXT_INODE_NUMBER_ROOT_DIRECTORY,
	     safe_inode,
	     NULL,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( safe_inode != NULL )
	{
		libfsext_inode_free(
		 &safe_inode,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file entry for an UTF-8 encoded path
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_volume_get_file_entry_by_utf8_path(
     libfsext_volume_t *volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_file_entry_by_utf8_path";
	int result                                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

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
/* TODO */
	return( result );

on_error:
	if( directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file entry for an UTF-16 encoded path
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
int libfsext_volume_get_file_entry_by_utf16_path(
     libfsext_volume_t *volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **file_entry,
     libcerror_error_t **error )
{
	libfsext_directory_entry_t *directory_entry = NULL;
	libfsext_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libfsext_volume_get_file_entry_by_utf16_path";
	int result                                  = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libfsext_internal_volume_t *) volume;

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
/* TODO */
	return( result );

on_error:
	if( directory_entry != NULL )
	{
		libfsext_directory_entry_free(
		 &directory_entry,
		 NULL );
	}
	return( -1 );
}

