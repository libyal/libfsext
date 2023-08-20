/*
 * Info handle
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "digest_hash.h"
#include "fsexttools_libbfio.h"
#include "fsexttools_libcerror.h"
#include "fsexttools_libclocale.h"
#include "fsexttools_libcnotify.h"
#include "fsexttools_libfdatetime.h"
#include "fsexttools_libfguid.h"
#include "fsexttools_libfsext.h"
#include "fsexttools_libhmac.h"
#include "fsexttools_libuna.h"
#include "info_handle.h"

#if !defined( LIBFSEXT_HAVE_BFIO )

extern \
int libfsext_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

extern \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsext_error_t **error );

#endif /* !defined( LIBFSEXT_HAVE_BFIO ) */

#define DIGEST_HASH_STRING_SIZE_MD5	33
#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int info_handle_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "info_handle_system_string_copy_from_64_bit_in_decimal";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     uint8_t calculate_md5,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libbfio_file_range_initialize(
	     &( ( *info_handle )->input_file_io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file IO handle.",
		 function );

		goto on_error;
	}
	( *info_handle )->calculate_md5 = calculate_md5;
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_file_io_handle != NULL )
		{
			libbfio_handle_free(
			 &( ( *info_handle )->input_file_io_handle ),
			 NULL );
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_volume != NULL )
		{
			if( libfsext_volume_free(
			     &( ( *info_handle )->input_volume ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input volume.",
				 function );

				result = -1;
			}
		}
		if( libbfio_handle_free(
		     &( ( *info_handle )->input_file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input file IO handle.",
			 function );

			result = -1;
		}
		if( ( *info_handle )->bodyfile_stream != NULL )
		{
			if( file_stream_close(
			     ( *info_handle )->bodyfile_stream ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close bodyfile stream.",
				 function );

				result = -1;
			}
			( *info_handle )->bodyfile_stream = NULL;
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_volume != NULL )
	{
		if( libfsext_volume_signal_abort(
		     info_handle->input_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input volume to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the bodyfile
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_bodyfile(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_bodyfile";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->bodyfile_stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle - bodyfile stream value already set.",
		 function );

		return( -1 );
	}
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	info_handle->bodyfile_stream = file_stream_open_wide(
	                                filename,
	                                L"wb" );
#else
	info_handle->bodyfile_stream = file_stream_open(
	                                filename,
	                                "wb" );
#endif
	if( info_handle->bodyfile_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open bodyfile stream.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the volume offset
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_volume_offset(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_volume_offset";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( info_handle_system_string_copy_from_64_bit_in_decimal(
	     string,
	     string_length + 1,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy string to 64-bit decimal.",
		 function );

		return( -1 );
	}
	info_handle->volume_offset = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function  = "info_handle_open_input";
	size_t filename_length = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	filename_length = system_string_length(
	                   filename );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_range_set_name_wide(
	     info_handle->input_file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#else
	if( libbfio_file_range_set_name(
	     info_handle->input_file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file name.",
		 function );

		goto on_error;
	}
	if( libbfio_file_range_set(
	     info_handle->input_file_io_handle,
	     info_handle->volume_offset,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set range.",
		 function );

		goto on_error;
	}
	if( libfsext_volume_initialize(
	     &( info_handle->input_volume ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input volume.",
		 function );

		goto on_error;
	}
	if( libfsext_volume_open_file_io_handle(
	     info_handle->input_volume,
	     info_handle->input_file_io_handle,
	     LIBFSEXT_OPEN_READ,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( info_handle->input_volume != NULL )
	{
		libfsext_volume_free(
		 &( info_handle->input_volume ),
		 NULL );
	}
	return( -1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_volume != NULL )
	{
		if( libfsext_volume_close(
		     info_handle->input_volume,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close input volume.",
			 function );

			return( -1 );
		}
	}
	return( 0 );
}

/* Calculates the MD5 of the contents of a file entry
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_entry_calculate_md5(
     info_handle_t *info_handle,
     libfsext_file_entry_t *file_entry,
     char *md5_string,
     size_t md5_string_size,
     libcerror_error_t **error )
{
	uint8_t md5_hash[ LIBHMAC_MD5_HASH_SIZE ];
	uint8_t read_buffer[ 4096 ];

	libhmac_md5_context_t *md5_context = NULL;
	static char *function              = "info_handle_file_entry_calculate_md5";
	size64_t data_size                 = 0;
	size_t read_size                   = 0;
	ssize_t read_count                 = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libfsext_file_entry_get_size(
	     file_entry,
	     &data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_seek_offset(
	     file_entry,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: 0 in file entry.",
		 function );

		goto on_error;
	}
	if( libhmac_md5_initialize(
	     &md5_context,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize MD5 context.",
		 function );

		goto on_error;
	}
	while( data_size > 0 )
	{
		read_size = 4096;

		if( (size64_t) read_size > data_size )
		{
			read_size = (size_t) data_size;
		}
		read_count = libfsext_file_entry_read_buffer(
		              file_entry,
		              read_buffer,
		              read_size,
		              error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from file entry.",
			 function );

			goto on_error;
		}
		data_size -= read_size;

		if( libhmac_md5_update(
		     md5_context,
		     read_buffer,
		     read_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update MD5 hash.",
			 function );

			goto on_error;
		}
	}
	if( libhmac_md5_finalize(
	     md5_context,
	     md5_hash,
	     LIBHMAC_MD5_HASH_SIZE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize MD5 hash.",
		 function );

		goto on_error;
	}
	if( libhmac_md5_free(
	     &md5_context,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free MD5 context.",
		 function );

		goto on_error;
	}
	if( digest_hash_copy_to_string(
	     md5_hash,
	     LIBHMAC_MD5_HASH_SIZE,
	     md5_string,
	     md5_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set MD5 hash string.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( md5_context != NULL )
	{
		libhmac_md5_free(
		 &md5_context,
		 NULL );
	}
	return( -1 );
}

/* Prints a file entry or data stream name
 * Returns 1 if successful or -1 on error
 */
int info_handle_name_value_fprint(
     info_handle_t *info_handle,
     const system_character_t *value_string,
     size_t value_string_length,
     libcerror_error_t **error )
{
	system_character_t *escaped_value_string     = NULL;
	static char *function                        = "info_handle_name_value_fprint";
	libuna_unicode_character_t unicode_character = 0;
	size_t escaped_value_string_index            = 0;
	size_t escaped_value_string_size             = 0;
	size_t value_string_index                    = 0;
	int print_count                              = 0;
	int result                                   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value string.",
		 function );

		return( -1 );
	}
	/* To ensure normalization in the escaped string is handled correctly
	 * it stored in a temporary variable. Note that there is a worst-case of
	 * a 1 to 4 ratio for each escaped character.
	 */
	if( value_string_length > (size_t) ( ( SSIZE_MAX - 1 ) / ( sizeof( system_character_t ) * 4 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid value string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	escaped_value_string_size = ( value_string_length * 4 ) + 1;

	escaped_value_string = (system_character_t *) memory_allocate(
	                                               sizeof( system_character_t ) * escaped_value_string_size );

	if( escaped_value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create escaped value string.",
		 function );

		goto on_error;
	}
	while( value_string_index < value_string_length )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libuna_unicode_character_copy_from_utf16(
		          &unicode_character,
		          (libuna_utf16_character_t *) value_string,
		          value_string_length,
		          &value_string_index,
		          error );
#else
		result = libuna_unicode_character_copy_from_utf8(
		          &unicode_character,
		          (libuna_utf8_character_t *) value_string,
		          value_string_length,
		          &value_string_index,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from value string.",
			 function );

			goto on_error;
		}
		/* Replace:
		 *   Control characters ([U+0-U+1f, U+7f-U+9f]) by \x##
		 */
		if( ( unicode_character <= 0x1f )
		 || ( ( unicode_character >= 0x7f )
		  &&  ( unicode_character <= 0x9f ) ) )
		{
			print_count = system_string_sprintf(
			               &( escaped_value_string[ escaped_value_string_index ] ),
			               escaped_value_string_size - escaped_value_string_index,
			               "\\x%02" PRIx32 "",
			               unicode_character );

			if( print_count < 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
				 "%s: unable to copy escaped Unicode character to escaped value string.",
				 function );

				goto on_error;
			}
			escaped_value_string_index += print_count;
		}
		else
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_unicode_character_copy_to_utf16(
			          unicode_character,
			          (libuna_utf16_character_t *) escaped_value_string,
			          escaped_value_string_size,
			          &escaped_value_string_index,
			          error );
#else
			result = libuna_unicode_character_copy_to_utf8(
			          unicode_character,
			          (libuna_utf8_character_t *) escaped_value_string,
			          escaped_value_string_size,
			          &escaped_value_string_index,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
				 "%s: unable to copy Unicode character to escaped value string.",
				 function );

				goto on_error;
			}
		}
	}
	escaped_value_string[ escaped_value_string_index ] = 0;

	if( info_handle->bodyfile_stream != NULL )
	{
		fprintf(
		 info_handle->bodyfile_stream,
		 "%" PRIs_SYSTEM "",
		 escaped_value_string );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "%" PRIs_SYSTEM "",
		 escaped_value_string );
	}
	memory_free(
	 escaped_value_string );

	return( 1 );

on_error:
	if( escaped_value_string != NULL )
	{
		memory_free(
		 escaped_value_string );
	}
	return( -1 );
}

/* Prints a seconds POSIX time value
 * Returns 1 if successful or -1 on error
 */
int info_handle_posix_time_in_seconds_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     int32_t value_32bit,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	static char *function                 = "info_handle_posix_time_in_seconds_value_fprint";
	int result                            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( value_32bit == 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "%s: Not set (0)\n",
		 value_name );
	}
	else
	{
		if( libfdatetime_posix_time_initialize(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create POSIX time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_posix_time_copy_from_32bit(
		     posix_time,
		     (uint32_t) value_32bit,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from 32-bit.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) date_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) date_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "%s: %" PRIs_SYSTEM " UTC\n",
		 value_name,
		 date_time_string );

		if( libfdatetime_posix_time_free(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free POSIX time.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( -1 );
}

/* Prints a nano seconds POSIX time value
 * Returns 1 if successful or -1 on error
 */
int info_handle_posix_time_in_nano_seconds_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     int64_t value_64bit,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	static char *function                 = "info_handle_posix_time_in_nano_seconds_value_fprint";
	int result                            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( value_64bit == 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "%s: Not set (0)\n",
		 value_name );
	}
	else
	{
		if( libfdatetime_posix_time_initialize(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create POSIX time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_posix_time_copy_from_64bit(
		     posix_time,
		     (uint64_t) value_64bit,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_NANO_SECONDS_64BIT_SIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time from 64-bit.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_posix_time_copy_to_utf16_string(
			  posix_time,
			  (uint16_t *) date_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_posix_time_copy_to_utf8_string(
			  posix_time,
			  (uint8_t *) date_time_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy POSIX time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "%s: %" PRIs_SYSTEM " UTC\n",
		 value_name,
		 date_time_string );

		if( libfdatetime_posix_time_free(
		     &posix_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free POSIX time.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( -1 );
}

/* Prints the compatible features flags to the notify stream
 */
void info_handle_compatible_features_flags_fprint(
      uint32_t compatible_features_flags,
      FILE *notify_stream )
{
	if( ( compatible_features_flags & 0x00000001UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tPre-allocate directory blocks (EXT2_COMPAT_PREALLOC)\n" );
	}
	if( ( compatible_features_flags & 0x00000002UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas AFS server inodes (EXT2_FEATURE_COMPAT_IMAGIC_INODES)\n" );
	}
	if( ( compatible_features_flags & 0x00000004UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas journal (EXT3_FEATURE_COMPAT_HAS_JOURNAL)\n" );
	}
	if( ( compatible_features_flags & 0x00000008UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHave extended inode attributes (EXT2_FEATURE_COMPAT_EXT_ATTR)\n" );
	}
	if( ( compatible_features_flags & 0x00000010UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tResizable volume (EXT2_FEATURE_COMPAT_RESIZE_INO)\n" );
	}
	if( ( compatible_features_flags & 0x00000010UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tUse directory hash index (EXT2_FEATURE_COMPAT_DIR_INDEX)\n" );
	}

	if( ( compatible_features_flags & 0x00000200UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_COMPAT_SPARSE_SUPER2)\n" );
	}
	fprintf(
	 notify_stream,
	 "\n" );
}

/* Prints the incompatible features flags to the notify stream
 */
void info_handle_incompatible_features_flags_fprint(
      uint32_t incompatible_features_flags,
      FILE *notify_stream )
{
	if( ( incompatible_features_flags & 0x00000001UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas compression (EXT2_FEATURE_INCOMPAT_COMPRESSION)\n" );
	}
	if( ( incompatible_features_flags & 0x00000002UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas directory type (EXT2_FEATURE_INCOMPAT_FILETYPE)\n" );
	}
	if( ( incompatible_features_flags & 0x00000004UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tNeeds recovery (EXT3_FEATURE_INCOMPAT_RECOVER)\n" );
	}
	if( ( incompatible_features_flags & 0x00000008UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas journal device (EXT3_FEATURE_INCOMPAT_JOURNAL_DEV)\n" );
	}
	if( ( incompatible_features_flags & 0x00000010UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas metadata block groups (EXT2_FEATURE_INCOMPAT_META_BG)\n" );
	}

	if( ( incompatible_features_flags & 0x00000040UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas extents (EXT4_FEATURE_INCOMPAT_EXTENTS)\n" );
	}
	if( ( incompatible_features_flags & 0x00000080UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas 64-bit support (EXT4_FEATURE_INCOMPAT_64BIT)\n" );
	}
	if( ( incompatible_features_flags & 0x00000100UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_MMP)\n" );
	}
	if( ( incompatible_features_flags & 0x00000200UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas flexible block groups (EXT4_FEATURE_INCOMPAT_FLEX_BG)\n" );
	}
	if( ( incompatible_features_flags & 0x00000400UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_EA_INODE)\n" );
	}

	if( ( incompatible_features_flags & 0x00001000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_DIRDATA)\n" );
	}
	if( ( incompatible_features_flags & 0x00002000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_BG_USE_META_CSUM)\n" );
	}
	if( ( incompatible_features_flags & 0x00004000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_LARGEDIR)\n" );
	}
	if( ( incompatible_features_flags & 0x00008000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_INLINE_DATA)\n" );
	}
	if( ( incompatible_features_flags & 0x00010000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_ENCRYPT)\n" );
	}
	if( ( incompatible_features_flags & 0x00020000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_INCOMPAT_CASEFOLD)\n" );
	}
	fprintf(
	 notify_stream,
	 "\n" );
}

/* Prints the read-only compatible features flags to the notify stream
 */
void info_handle_read_only_compatible_features_flags_fprint(
      uint32_t read_only_compatible_features_flags,
      FILE *notify_stream )
{
	if( ( read_only_compatible_features_flags & 0x00000001UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tHas sparse superblocks and group descriptor tables (EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000002UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContains large files (EXT2_FEATURE_RO_COMPAT_LARGE_FILE)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000004UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tUse directory B-tree (EXT2_FEATURE_RO_COMPAT_BTREE_DIR)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000008UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_HUGE_FILE)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00000010UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_GDT_CSUM)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000020UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_DIR_NLINK)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000040UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000080UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(RO_COMPAT_HAS_SNAPSHOT)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00000100UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_QUOTA)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000200UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_BIGALLOC)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000400UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_METADATA_CSUM)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000800UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_REPLICA)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00001000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_READONLY)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00002000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_PROJECT)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00004000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_SHARED_BLOCKS)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00008000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t(EXT4_FEATURE_RO_COMPAT_VERITY)\n" );
	}
	fprintf(
	 notify_stream,
	 "\n" );
}

/* Prints a file entry value with name
 * Returns 1 if successful, 0 if not or -1 on error
 */
int info_handle_file_entry_value_with_name_fprint(
     info_handle_t *info_handle,
     libfsext_file_entry_t *file_entry,
     const system_character_t *path,
     size_t path_length,
     const system_character_t *file_entry_name,
     size_t file_entry_name_length,
     libcerror_error_t **error )
{
	char md5_string[ DIGEST_HASH_STRING_SIZE_MD5 ] = {
		'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
		'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
		0 };

	char file_mode_string[ 11 ]                       = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 0 };

	libfsext_extended_attribute_t *extended_attribute = NULL;
	system_character_t *extended_attribute_name       = NULL;
	system_character_t *symbolic_link_target          = NULL;
	static char *function                             = "info_handle_file_entry_value_with_name_fprint";
	size64_t size                                     = 0;
	size_t extended_attribute_name_size               = 0;
	size_t symbolic_link_target_size                  = 0;
	int64_t access_time                               = 0;
	int64_t creation_time                             = 0;
	int64_t inode_change_time                         = 0;
	int64_t modification_time                         = 0;
	uint32_t file_entry_identifier                    = 0;
	uint32_t group_identifier                         = 0;
	uint32_t owner_identifier                         = 0;
	int32_t deletion_time                             = 0;
	uint16_t file_mode                                = 0;
	uint16_t number_of_links                          = 0;
	uint8_t has_creation_time                         = 0;
	uint8_t major_device_number                       = 0;
	uint8_t minor_device_number                       = 0;
	int extended_attribute_index                      = 0;
	int number_of_extended_attributes                 = 0;
	int result                                        = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libfsext_file_entry_get_inode_number(
	     file_entry,
	     &file_entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode number.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_get_modification_time(
	     file_entry,
	     &modification_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve modification time.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_get_inode_change_time(
	     file_entry,
	     &inode_change_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode change time.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_get_access_time(
	     file_entry,
	     &access_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve access time.",
		 function );

		goto on_error;
	}
	result = libfsext_file_entry_get_creation_time(
	          file_entry,
	          &creation_time,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve creation time.",
		 function );

		goto on_error;
	}
	has_creation_time = (uint8_t) result;

	if( libfsext_file_entry_get_owner_identifier(
	     file_entry,
	     &owner_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve owner identifier.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_get_group_identifier(
	     file_entry,
	     &group_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve group identifier.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_get_file_mode(
	     file_entry,
	     &file_mode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file mode.",
		 function );

		goto on_error;
	}
/* TODO move into function */
	if( ( file_mode & 0x0001 ) != 0 )
	{
		file_mode_string[ 9 ] = 'x';
	}
	if( ( file_mode & 0x0002 ) != 0 )
	{
		file_mode_string[ 8 ] = 'w';
	}
	if( ( file_mode & 0x0004 ) != 0 )
	{
		file_mode_string[ 7 ] = 'r';
	}
	if( ( file_mode & 0x0008 ) != 0 )
	{
		file_mode_string[ 6 ] = 'x';
	}
	if( ( file_mode & 0x0010 ) != 0 )
	{
		file_mode_string[ 5 ] = 'w';
	}
	if( ( file_mode & 0x0020 ) != 0 )
	{
		file_mode_string[ 4 ] = 'r';
	}
	if( ( file_mode & 0x0040 ) != 0 )
	{
		file_mode_string[ 3 ] = 'x';
	}
	if( ( file_mode & 0x0080 ) != 0 )
	{
		file_mode_string[ 2 ] = 'w';
	}
	if( ( file_mode & 0x0100 ) != 0 )
	{
		file_mode_string[ 1 ] = 'r';
	}
	switch( file_mode & 0xf000 )
	{
		case 0x1000:
			file_mode_string[ 0 ] = 'p';
			break;

		case 0x2000:
			file_mode_string[ 0 ] = 'c';
			break;

		case 0x4000:
			file_mode_string[ 0 ] = 'd';
			break;

		case 0x6000:
			file_mode_string[ 0 ] = 'b';
			break;

		case 0xa000:
			file_mode_string[ 0 ] = 'l';
			break;

		case 0xc000:
			file_mode_string[ 0 ] = 's';
			break;

		default:
			break;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_file_entry_get_utf16_symbolic_link_target_size(
	          file_entry,
	          &symbolic_link_target_size,
	          error );
#else
	result = libfsext_file_entry_get_utf8_symbolic_link_target_size(
	          file_entry,
	          &symbolic_link_target_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve symbolic link target string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		symbolic_link_target = system_string_allocate(
		                        symbolic_link_target_size );

		if( symbolic_link_target == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create symbolic link target string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsext_file_entry_get_utf16_symbolic_link_target(
		          file_entry,
		          (uint16_t *) symbolic_link_target,
		          symbolic_link_target_size,
		          error );
#else
		result = libfsext_file_entry_get_utf8_symbolic_link_target(
		          file_entry,
		          (uint8_t *) symbolic_link_target,
		          symbolic_link_target_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve symbolic link target string.",
			 function );

			goto on_error;
		}
	}
	if( libfsext_file_entry_get_size(
	     file_entry,
	     &size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		goto on_error;
	}
	if( info_handle->bodyfile_stream != NULL )
	{
		if( info_handle->calculate_md5 == 0 )
		{
			md5_string[ 1 ] = 0;
		}
		else if( ( file_mode & 0xf000 ) == 0x8000 )
		{
			if( info_handle_file_entry_calculate_md5(
			     info_handle,
			     file_entry,
			     md5_string,
			     DIGEST_HASH_STRING_SIZE_MD5,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retreive MD5 string.",
				 function );

				goto on_error;
			}
		}
		/* Colums in a Sleuthkit 3.x and later bodyfile
		 * MD5|name|inode|mode_as_string|UID|GID|size|atime|mtime|ctime|crtime
		 */
		fprintf(
		 info_handle->bodyfile_stream,
		 "%s|",
		 md5_string );

		if( path != NULL )
		{
			if( info_handle_name_value_fprint(
			     info_handle,
			     path,
			     path_length,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print path string.",
				 function );

				goto on_error;
			}
		}
		if( ( file_entry_name != NULL )
		 && ( file_entry_identifier != 2 ) )
		{
			if( info_handle_name_value_fprint(
			     info_handle,
			     file_entry_name,
			     file_entry_name_length,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print file entry name string.",
				 function );

				goto on_error;
			}
		}
		if( symbolic_link_target != NULL )
		{
			fprintf(
			 info_handle->bodyfile_stream,
			 " -> %" PRIs_SYSTEM "",
			 symbolic_link_target );
		}
		if( has_creation_time != 0 )
		{
			fprintf(
			 info_handle->bodyfile_stream,
			 "|%" PRIu32 "|%s|%" PRIu32 "|%" PRIu32 "|%" PRIu64 "|%" PRIi64 ".%09" PRIi64 "|%" PRIi64 ".%09" PRIi64 "|%" PRIi64 ".%09" PRIi64 "|%" PRIi64 ".%09" PRIi64 "\n",
			 file_entry_identifier,
			 file_mode_string,
			 owner_identifier,
			 group_identifier,
			 size,
			 access_time / 1000000000,
			 access_time - ( ( access_time / 1000000000 ) * 1000000000 ),
			 modification_time / 1000000000,
			 modification_time - ( ( modification_time / 1000000000 ) * 1000000000 ),
			 inode_change_time / 1000000000,
			 inode_change_time - ( ( inode_change_time / 1000000000 ) * 1000000000 ),
			 creation_time / 1000000000,
			 creation_time - ( ( creation_time / 1000000000 ) * 1000000000 ) );
		}
		else
		{
			fprintf(
			 info_handle->bodyfile_stream,
			 "|%" PRIu32 "|%s|%" PRIu32 "|%" PRIu32 "|%" PRIu64 "|%" PRIi64 "|%" PRIi64 "|%" PRIi64 "|0\n",
			 file_entry_identifier,
			 file_mode_string,
			 owner_identifier,
			 group_identifier,
			 size,
			 access_time / 1000000000,
			 modification_time / 1000000000,
			 inode_change_time / 1000000000 );
		}
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tInode number\t\t: %" PRIu32 "\n",
		 file_entry_identifier );

		if( file_entry_name != NULL )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tName\t\t\t: " );

			if( path != NULL )
			{
				if( info_handle_name_value_fprint(
				     info_handle,
				     path,
				     path_length,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print path string.",
					 function );

					goto on_error;
				}
			}
			if( ( file_entry_name != NULL )
			 && ( file_entry_identifier != 2 ) )
			{
				if( info_handle_name_value_fprint(
				     info_handle,
				     file_entry_name,
				     file_entry_name_length,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print file entry name string.",
					 function );

					goto on_error;
				}
			}
			fprintf(
			 info_handle->notify_stream,
			 "\n" );
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tSize\t\t\t: %" PRIu64 "\n",
		 size );

		if( has_creation_time != 0 )
		{
			result = info_handle_posix_time_in_nano_seconds_value_fprint(
			          info_handle,
			          "\tModification time\t",
			          modification_time,
			          error );
		}
		else
		{
			result = info_handle_posix_time_in_seconds_value_fprint(
			          info_handle,
			          "\tModification time\t",
			          (int32_t) ( modification_time / 1000000000 ),
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			goto on_error;
		}
		if( has_creation_time != 0 )
		{
			result = info_handle_posix_time_in_nano_seconds_value_fprint(
			          info_handle,
			          "\tInode change time\t",
			          inode_change_time,
			          error );
		}
		else
		{
			result = info_handle_posix_time_in_seconds_value_fprint(
			          info_handle,
			          "\tInode change time\t",
			          (int32_t) ( inode_change_time / 1000000000 ),
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			goto on_error;
		}
		if( has_creation_time != 0 )
		{
			result = info_handle_posix_time_in_nano_seconds_value_fprint(
			          info_handle,
			          "\tAccess time\t\t",
			          access_time,
			          error );
		}
		else
		{
			result = info_handle_posix_time_in_seconds_value_fprint(
			          info_handle,
			          "\tAccess time\t\t",
			          (int32_t) ( access_time / 1000000000 ),
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			goto on_error;
		}
		if( has_creation_time != 0 )
		{
			if( info_handle_posix_time_in_nano_seconds_value_fprint(
			     info_handle,
			     "\tCreation time\t\t",
			     creation_time,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print POSIX time value.",
				 function );

				goto on_error;
			}
		}
		if( libfsext_file_entry_get_deletion_time(
		     file_entry,
		     &deletion_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve deletion time.",
			 function );

			goto on_error;
		}
		if( info_handle_posix_time_in_seconds_value_fprint(
		     info_handle,
		     "\tDeletion time\t\t",
		     deletion_time,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			goto on_error;
		}
		if( libfsext_file_entry_get_number_of_links(
		     file_entry,
		     &number_of_links,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of links.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tNumber of links\t\t: %" PRIu16 "\n",
		 number_of_links );

		fprintf(
		 info_handle->notify_stream,
		 "\tOwner identifier\t: %" PRIu32 "\n",
		 owner_identifier );

		fprintf(
		 info_handle->notify_stream,
		 "\tGroup identifier\t: %" PRIu32 "\n",
		 group_identifier );

		fprintf(
		 info_handle->notify_stream,
		 "\tFile mode\t\t: %s (%07" PRIo16 ")\n",
		 file_mode_string,
		 file_mode );

		result = libfsext_file_entry_get_device_number(
		          file_entry,
		          &major_device_number,
		          &minor_device_number,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve device number.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tDevice number\t\t: %" PRIu8 ",%" PRIu8 "\n",
			 major_device_number,
			 minor_device_number );
		}
		if( symbolic_link_target != NULL )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tSymbolic link target\t: %" PRIs_SYSTEM "\n",
			 symbolic_link_target );
		}
		if( libfsext_file_entry_get_number_of_extended_attributes(
		     file_entry,
		     &number_of_extended_attributes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of extended attributes.",
			 function );

			goto on_error;
		}
		if( number_of_extended_attributes > 0 )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tExtended attributes:\n" );

			for( extended_attribute_index = 0;
			     extended_attribute_index < number_of_extended_attributes;
			     extended_attribute_index++ )
			{
				if( libfsext_file_entry_get_extended_attribute_by_index(
				     file_entry,
				     extended_attribute_index,
				     &extended_attribute,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve extended attribute: %d.",
					 function,
					 extended_attribute_index );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfsext_extended_attribute_get_utf16_name_size(
				          extended_attribute,
				          &extended_attribute_name_size,
				          error );
#else
				result = libfsext_extended_attribute_get_utf8_name_size(
				          extended_attribute,
				          &extended_attribute_name_size,
				          error );
#endif
				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve extended attribute name string size.",
					 function );

					goto on_error;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\t\tAttribute: %d\t: ",
				 extended_attribute_index + 1 );

				if( ( result == 1 )
				 && ( extended_attribute_name_size > 0 ) )
				{
					extended_attribute_name = system_string_allocate(
					                           extended_attribute_name_size );

					if( extended_attribute_name == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create extended attribute name string.",
						 function );

						goto on_error;
					}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfsext_extended_attribute_get_utf16_name(
					          extended_attribute,
					          (uint16_t *) extended_attribute_name,
					          extended_attribute_name_size,
					          error );
#else
					result = libfsext_extended_attribute_get_utf8_name(
					          extended_attribute,
					          (uint8_t *) extended_attribute_name,
					          extended_attribute_name_size,
					          error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve extended attribute name string.",
						 function );

						goto on_error;
					}
					fprintf(
					 info_handle->notify_stream,
					 "%" PRIs_SYSTEM "",
					 extended_attribute_name );

					memory_free(
					 extended_attribute_name );

					extended_attribute_name = NULL;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\n" );

				if( libfsext_extended_attribute_free(
				     &extended_attribute,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free extended attribute: %d.",
					 function,
					 extended_attribute_index );

					goto on_error;
				}
			}
		}
	}
	if( symbolic_link_target != NULL )
	{
		memory_free(
		 symbolic_link_target );

		symbolic_link_target = NULL;
	}
	return( 1 );

on_error:
	if( extended_attribute_name != NULL )
	{
		memory_free(
		 extended_attribute_name );
	}
	if( extended_attribute != NULL )
	{
		libfsext_extended_attribute_free(
		 &extended_attribute,
		 NULL );
	}
	if( symbolic_link_target != NULL )
	{
		memory_free(
		 symbolic_link_target );
	}
	return( -1 );
}

/* Prints file entry information as part of the file system hierarchy
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_system_hierarchy_fprint_file_entry(
     info_handle_t *info_handle,
     libfsext_file_entry_t *file_entry,
     const system_character_t *path,
     size_t path_length,
     libcerror_error_t **error )
{
	libfsext_file_entry_t *sub_file_entry = NULL;
	system_character_t *file_entry_name   = NULL;
	system_character_t *sub_path          = NULL;
	static char *function                 = "info_handle_file_system_hierarchy_fprint_file_entry";
	size_t file_entry_name_length         = 0;
	size_t file_entry_name_size           = 0;
	size_t sub_path_size                  = 0;
	uint32_t file_entry_identifier        = 0;
	int number_of_sub_file_entries        = 0;
	int result                            = 0;
	int sub_file_entry_index              = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfsext_file_entry_get_inode_number(
	     file_entry,
	     &file_entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve inode number.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_file_entry_get_utf16_name_size(
	          file_entry,
	          &file_entry_name_size,
	          error );
#else
	result = libfsext_file_entry_get_utf8_name_size(
	          file_entry,
	          &file_entry_name_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file entry name string size.",
		 function );

		goto on_error;
	}
	if( ( result == 1 )
	 && ( file_entry_name_size > 0 ) )
	{
		file_entry_name = system_string_allocate(
		                   file_entry_name_size );

		if( file_entry_name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create file entry name string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsext_file_entry_get_utf16_name(
		          file_entry,
		          (uint16_t *) file_entry_name,
		          file_entry_name_size,
		          error );
#else
		result = libfsext_file_entry_get_utf8_name(
		          file_entry,
		          (uint8_t *) file_entry_name,
		          file_entry_name_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file entry name string.",
			 function );

			goto on_error;
		}
		file_entry_name_length = file_entry_name_size - 1;
	}
	if( info_handle->bodyfile_stream != NULL )
	{
		if( info_handle_file_entry_value_with_name_fprint(
		     info_handle,
		     file_entry,
		     path,
		     path_length,
		     file_entry_name,
		     file_entry_name_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print file entry.",
			 function );

			goto on_error;
		}
	}
	else
	{
		if( info_handle_name_value_fprint(
		     info_handle,
		     path,
		     path_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print path string.",
			 function );

			goto on_error;
		}
		if( ( file_entry_name != NULL )
		 && ( file_entry_identifier != 2 ) )
		{
			if( info_handle_name_value_fprint(
			     info_handle,
			     file_entry_name,
			     file_entry_name_length,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print file entry name string.",
				 function );

				goto on_error;
			}
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	if( libfsext_file_entry_get_number_of_sub_file_entries(
	     file_entry,
	     &number_of_sub_file_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub file entries.",
		 function );

		goto on_error;
	}
	if( number_of_sub_file_entries > 0 )
	{
		sub_path_size = path_length + 1;

		if( file_entry_name != NULL )
		{
			sub_path_size += file_entry_name_size;
		}
		sub_path = system_string_allocate(
		            sub_path_size );

		if( sub_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create sub path.",
			 function );

			goto on_error;
		}
		if( system_string_copy(
		     sub_path,
		     path,
		     path_length ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy path to sub path.",
			 function );

			goto on_error;
		}
		if( file_entry_name != NULL )
		{
			if( system_string_copy(
			     &( sub_path[ path_length ] ),
			     file_entry_name,
			     file_entry_name_size - 1 ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy file entry name to sub path.",
				 function );

				goto on_error;
			}
			sub_path[ sub_path_size - 2 ] = (system_character_t) LIBFSEXT_SEPARATOR;
		}
		sub_path[ sub_path_size - 1 ] = (system_character_t) 0;

		for( sub_file_entry_index = 0;
		     sub_file_entry_index < number_of_sub_file_entries;
		     sub_file_entry_index++ )
		{
			if( libfsext_file_entry_get_sub_file_entry_by_index(
			     file_entry,
			     sub_file_entry_index,
			     &sub_file_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve sub file entry: %d.",
				 function,
				 sub_file_entry_index );

				goto on_error;
			}
			if( info_handle_file_system_hierarchy_fprint_file_entry(
			     info_handle,
			     sub_file_entry,
			     sub_path,
			     sub_path_size - 1,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print file entry: %d information.",
				 function,
				 sub_file_entry_index );

				goto on_error;
			}
			if( libfsext_file_entry_free(
			     &sub_file_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free sub file entry: %d.",
				 function,
				 sub_file_entry_index );

				goto on_error;
			}
		}
		if( sub_path != NULL )
		{
			memory_free(
			 sub_path );

			sub_path = NULL;
		}
	}
	if( file_entry_name != NULL )
	{
		memory_free(
		 file_entry_name );

		file_entry_name = NULL;
	}
	return( 1 );

on_error:
	if( sub_file_entry != NULL )
	{
		libfsext_file_entry_free(
		 &sub_file_entry,
		 NULL );
	}
	if( sub_path != NULL )
	{
		memory_free(
		 sub_path );
	}
	if( file_entry_name != NULL )
	{
		memory_free(
		 file_entry_name );
	}
	return( -1 );
}

/* Prints the file entries information
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_entries_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function           = "info_handle_file_entries_fprint";
	uint64_t file_entry_identifier  = 0;
	uint32_t number_of_file_entries = 0;

	if( libfsext_volume_get_number_of_file_entries(
	     info_handle->input_volume,
	     &number_of_file_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of file entries.",
		 function );

		return( -1 );
	}
	/* Inode 0 is not supported
	 */
	for( file_entry_identifier = 1;
	     file_entry_identifier < (uint64_t) number_of_file_entries;
	     file_entry_identifier++ )
	{
		if( info_handle_file_entry_fprint_by_identifier(
		     info_handle,
		     (uint32_t) file_entry_identifier,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print file entry: %" PRIu64 " information.",
			 function,
			 file_entry_identifier );

			return( -1 );
		}
	}
	return( 1 );
}

/* Prints the file entry information for a specific identifier
 * Returns 1 if successful, 0 if not or -1 on error
 */
int info_handle_file_entry_fprint_by_identifier(
     info_handle_t *info_handle,
     uint32_t file_entry_identifier,
     libcerror_error_t **error )
{
	libfsext_file_entry_t *file_entry = NULL;
	static char *function             = "info_handle_file_entry_fprint_by_identifier";
	int is_empty                      = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libfsext_volume_get_file_entry_by_inode(
	     info_handle->input_volume,
	     file_entry_identifier,
	     &file_entry,
	     error ) != 1 )
	{
		if( ( error != NULL )
		 && ( *error != NULL ) )
		{
			libcnotify_print_error_backtrace(
			 *error );
		}
		libcerror_error_free(
		 error );

		fprintf(
		 info_handle->notify_stream,
		 "Error reading file entry: %" PRIu32 "\n\n",
		 file_entry_identifier );

		return( 0 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "File entry: %" PRIu32 " information:\n",
	 file_entry_identifier );

	is_empty = libfsext_file_entry_is_empty(
	            file_entry,
	            error );

	if( is_empty == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if file entry is empty.",
		 function );

		goto on_error;
	}
	else if( is_empty != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tIs empty\n" );
	}
	else
	{
/* TODO implement is allocated */
		if( info_handle_file_entry_value_with_name_fprint(
		     info_handle,
		     file_entry,
		     NULL,
		     0,
		     NULL,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print file entry.",
			 function );

			goto on_error;
		}
	}
	if( libfsext_file_entry_free(
	     &file_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file entry.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( file_entry != NULL )
	{
		libfsext_file_entry_free(
		 &file_entry,
		 NULL );
	}
	return( -1 );
}

/* Prints the file entry information for a specific path
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_entry_fprint_by_path(
     info_handle_t *info_handle,
     const system_character_t *path,
     libcerror_error_t **error )
{
	libfsext_file_entry_t *file_entry = NULL;
	static char *function              = "info_handle_file_entry_fprint_by_path";
	size_t path_length                 = 0;
	int result                         = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	path_length = system_string_length(
	               path );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_volume_get_file_entry_by_utf16_path(
	          info_handle->input_volume,
	          (uint16_t *) path,
	          path_length,
	          &file_entry,
	          error );
#else
	result = libfsext_volume_get_file_entry_by_utf8_path(
	          info_handle->input_volume,
	          (uint8_t *) path,
	          path_length,
	          &file_entry,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file entry.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: file entry not found.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "Extended File System information:\n\n" );

	fprintf(
	 info_handle->notify_stream,
	 "File entry:\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tPath\t\t\t: " );

	if( info_handle_name_value_fprint(
	     info_handle,
	     path,
	     path_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print path string.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( info_handle_file_entry_value_with_name_fprint(
	     info_handle,
	     file_entry,
	     path,
	     path_length,
	     NULL,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print file entry.",
		 function );

		goto on_error;
	}
	if( libfsext_file_entry_free(
	     &file_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file entry.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( file_entry != NULL )
	{
		libfsext_file_entry_free(
		 &file_entry,
		 NULL );
	}
	return( -1 );
}

/* Prints the file system hierarchy information
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_system_hierarchy_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libfsext_file_entry_t *file_entry = NULL;
	static char *function             = "info_handle_file_system_hierarchy_fprint";
	int result                        = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->bodyfile_stream == NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Extended File System information:\n\n" );

		fprintf(
		 info_handle->notify_stream,
		 "File system hierarchy:\n" );
	}
	result = libfsext_volume_get_root_directory(
	          info_handle->input_volume,
	          &file_entry,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve root directory file entry.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( info_handle_file_system_hierarchy_fprint_file_entry(
		     info_handle,
		     file_entry,
		     _SYSTEM_STRING( "/" ),
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print root directory file entry information.",
			 function );

			goto on_error;
		}
		if( libfsext_file_entry_free(
		     &file_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file entry.",
			 function );

			goto on_error;
		}
	}
	if( info_handle->bodyfile_stream == NULL )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( file_entry != NULL )
	{
		libfsext_file_entry_free(
		 &file_entry,
		 NULL );
	}
	return( -1 );
}

/* Prints the volume information
 * Returns 1 if successful or -1 on error
 */
int info_handle_volume_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	system_character_t *value_string             = NULL;
	static char *function                        = "info_handle_volume_fprint";
	size_t value_string_size                     = 0;
	uint32_t compatible_features_flags           = 0;
	uint32_t incompatible_features_flags         = 0;
	uint32_t read_only_compatible_features_flags = 0;
	uint32_t value_32bit                         = 0;
	uint8_t format_version                       = 0;
	int result                                   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Extended File System information:\n\n" );

	fprintf(
	 info_handle->notify_stream,
	 "Volume information:\n" );

	if( libfsext_volume_get_format_version(
	     info_handle->input_volume,
	     &format_version,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve format version.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tFile system\t\t\t: ext%" PRIu8 "\n",
	 format_version );

	fprintf(
	 info_handle->notify_stream,
	 "\tLabel\t\t\t\t: " );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_volume_get_utf16_label_size(
	          info_handle->input_volume,
	          &value_string_size,
	          error );
#else
	result = libfsext_volume_get_utf8_label_size(
	          info_handle->input_volume,
	          &value_string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve label size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create label string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsext_volume_get_utf16_label(
		          info_handle->input_volume,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libfsext_volume_get_utf8_label(
		          info_handle->input_volume,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve label.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "%" PRIs_SYSTEM "",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( libfsext_volume_get_features_flags(
	     info_handle->input_volume,
	     &compatible_features_flags,
	     &incompatible_features_flags,
	     &read_only_compatible_features_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve feature flags.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tCompatible features\t\t: 0x%08" PRIx32 "\n",
	 compatible_features_flags );

	info_handle_compatible_features_flags_fprint(
	 compatible_features_flags,
	 info_handle->notify_stream );

	fprintf(
	 info_handle->notify_stream,
	 "\tIncompatible features\t\t: 0x%08" PRIx32 "\n",
	 incompatible_features_flags );

	info_handle_incompatible_features_flags_fprint(
	 incompatible_features_flags,
	 info_handle->notify_stream );

	fprintf(
	 info_handle->notify_stream,
	 "\tRead-only compatible features\t: 0x%08" PRIx32 "\n",
	 read_only_compatible_features_flags );

	info_handle_read_only_compatible_features_flags_fprint(
	 read_only_compatible_features_flags,
	 info_handle->notify_stream );

	if( libfsext_volume_get_number_of_file_entries(
	     info_handle->input_volume,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of file entries (inodes).",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of inodes\t\t: %" PRIu32 "\n",
	 value_32bit );

	fprintf(
	 info_handle->notify_stream,
	 "\tLast mount path\t\t\t: " );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_volume_get_utf16_last_mount_path_size(
	          info_handle->input_volume,
	          &value_string_size,
	          error );
#else
	result = libfsext_volume_get_utf8_last_mount_path_size(
	          info_handle->input_volume,
	          &value_string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve last mount path size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create last mount path string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfsext_volume_get_utf16_last_mount_path(
		          info_handle->input_volume,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libfsext_volume_get_utf8_last_mount_path(
		          info_handle->input_volume,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve last mount path.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "%" PRIs_SYSTEM "",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( libfsext_volume_get_last_mount_time(
	     info_handle->input_volume,
	     (int32_t *) &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve last mount time.",
		 function );

		goto on_error;
	}
	if( info_handle_posix_time_in_seconds_value_fprint(
	     info_handle,
	     "\tLast mount time\t\t\t",
	     value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print POSIX time value.",
		 function );

		goto on_error;
	}
	if( libfsext_volume_get_last_written_time(
	     info_handle->input_volume,
	     (int32_t *) &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve last written time.",
		 function );

		goto on_error;
	}
	if( info_handle_posix_time_in_seconds_value_fprint(
	     info_handle,
	     "\tLast written time\t\t",
	     value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print POSIX time value.",
		 function );

		goto on_error;
	}
/* TODO print more info */

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

