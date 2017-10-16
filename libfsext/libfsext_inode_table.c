/*
 * Inode table functions
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

#include "libfsext_inode.h"
#include "libfsext_inode_table.h"
#include "libfsext_io_handle.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"

#include "fsext_inode.h"

/* Creates an inode table
 * Make sure the value inode_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_initialize(
     libfsext_inode_table_t **inode_table,
     libcerror_error_t **error )
{
	static char *function = "libfsext_inode_table_initialize";

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
	return( 1 );

on_error:
	if( *inode_table != NULL )
	{
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
		memory_free(
		 *inode_table );

		*inode_table = NULL;
	}
	return( 1 );
}

/* Reads the inode_table data
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_read_data(
     libfsext_inode_table_t *inode_table,
     const uint8_t *data,
     size_t data_size,
     off64_t file_offset,
     libcerror_error_t **error )
{
	libfsext_inode_t *inode = NULL;
	static char *function   = "libfsext_inode_table_read_data";
	size_t data_offset      = 0;

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
	while( ( data_size > sizeof( fsext_inode_t ) )
	    && ( data_offset < ( data_size - sizeof( fsext_inode_t ) ) ) )
	{
		if( libfsext_inode_initialize(
		     &inode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to inode.",
			 function );

			goto on_error;
		}
		if( libfsext_inode_read_data(
		     inode,
		     &( data[ data_offset ] ),
		     data_size - data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read inode at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset + (off64_t) data_offset,
			 file_offset + (off64_t) data_offset );

			goto on_error;
		}
		data_offset += sizeof( fsext_inode_t );

		if( libfsext_inode_free(
		     &inode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free inode.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	return( -1 );
}

/* Reads the inode_table from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libfsext_inode_table_read_file_io_handle(
     libfsext_inode_table_t *inode_table,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libfsext_inode_table_read_file_io_handle";
	ssize_t read_count    = 0;

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
#if SIZEOF_SIZE_T <= 4
	if( io_handle->block_size > (uint32_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - block size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading inode table at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
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
		 "%s: unable to seek inode table offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * io_handle->block_size );

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
		 "%s: unable to read inode table at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libfsext_inode_table_read_data(
	     inode_table,
	     data,
	     (size_t) io_handle->block_size,
	     file_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read inode table at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

