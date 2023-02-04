/*
 * Library support functions test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsext_test_functions.h"
#include "fsext_test_getopt.h"
#include "fsext_test_libbfio.h"
#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#if !defined( LIBFSEXT_HAVE_BFIO )

LIBFSEXT_EXTERN \
int libfsext_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBFSEXT_HAVE_BFIO ) */

/* Tests the libfsext_get_version function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libfsext_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBFSEXT_VERSION_STRING,
	          9 );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libfsext_get_access_flags_read function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_get_access_flags_read(
     void )
{
	int access_flags = 0;

	access_flags = libfsext_get_access_flags_read();

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "access_flags",
	 access_flags,
	 LIBFSEXT_ACCESS_FLAG_READ );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libfsext_get_codepage function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_get_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libfsext_get_codepage(
	          &codepage,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_get_codepage(
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_set_codepage function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_set_codepage(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libfsext_set_codepage(
	          0,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_set_codepage(
	          -1,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_check_volume_signature function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_check_volume_signature(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = fsext_test_get_narrow_source(
		          source,
		          narrow_source,
		          256,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libfsext_check_volume_signature(
		          narrow_source,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfsext_check_volume_signature(
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfsext_check_volume_signature(
	          "",
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( source != NULL )
	{
#if defined( HAVE_FSEXT_TEST_MEMORY )

		/* Test libfsext_check_volume_signature with malloc failing in libbfio_file_initialize
		 */
		fsext_test_malloc_attempts_before_fail = 0;

		result = libfsext_check_volume_signature(
		          narrow_source,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;
		}
		else
		{
			FSEXT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libfsext_check_volume_signature_wide function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_check_volume_signature_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = fsext_test_get_wide_source(
		          source,
		          wide_source,
		          256,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libfsext_check_volume_signature_wide(
		          wide_source,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfsext_check_volume_signature_wide(
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfsext_check_volume_signature_wide(
	          L"",
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( source != NULL )
	{
#if defined( HAVE_FSEXT_TEST_MEMORY )

		/* Test libfsext_check_volume_signature_wide with malloc failing in libbfio_file_initialize
		 */
		fsext_test_malloc_attempts_before_fail = 0;

		result = libfsext_check_volume_signature_wide(
		          wide_source,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;
		}
		else
		{
			FSEXT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libfsext_check_volume_signature_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_check_volume_signature_file_io_handle(
     const system_character_t *source )
{
	uint8_t empty_block[ 8192 ];

	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	void *memset_result              = NULL;
	size_t source_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	memset_result = memory_set(
	                 empty_block,
	                 0,
	                 sizeof( uint8_t ) * 8192 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "memset_result",
	 memset_result );

	if( source != NULL )
	{
		/* Initialize test
		 */
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NOT_NULL(
		 "file_io_handle",
		 file_io_handle );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		source_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          source_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          source_length,
		          &error );
#endif
		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_open(
		          file_io_handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test check volume signature
		 */
		result = libfsext_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfsext_check_volume_signature_file_io_handle(
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	if( source != NULL )
	{
		result = libbfio_handle_close(
		          file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "file_io_handle",
		 file_io_handle );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test check volume signature with data too small
	 */
	result = fsext_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 1,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = fsext_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test check volume signature with empty block
	 */
	result = fsext_test_open_file_io_handle(
	          &file_io_handle,
	          empty_block,
	          sizeof( uint8_t ) * 8192,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = fsext_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error          = NULL;
	system_character_t *option_offset = NULL;
	system_character_t *source        = NULL;
	system_integer_t option           = 0;
	size_t string_length              = 0;
	off64_t volume_offset             = 0;
	int result                        = 0;

	while( ( option = fsext_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "o:" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );

			case (system_integer_t) 'o':
				option_offset = optarg;

				break;
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
	if( option_offset != NULL )
	{
		string_length = system_string_length(
		                 option_offset );

		result = fsext_test_system_string_copy_from_64_bit_in_decimal(
		          option_offset,
		          string_length + 1,
		          (uint64_t *) &volume_offset,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        FSEXT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
	FSEXT_TEST_RUN(
	 "libfsext_get_version",
	 fsext_test_get_version );

	FSEXT_TEST_RUN(
	 "libfsext_get_access_flags_read",
	 fsext_test_get_access_flags_read );

	FSEXT_TEST_RUN(
	 "libfsext_get_codepage",
	 fsext_test_get_codepage );

	FSEXT_TEST_RUN(
	 "libfsext_set_codepage",
	 fsext_test_set_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( ( source != NULL )
	 && ( volume_offset == 0 ) )
	{
		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_check_volume_signature",
		 fsext_test_check_volume_signature,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_check_volume_signature_wide",
		 fsext_test_check_volume_signature_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_check_volume_signature_file_io_handle",
		 fsext_test_check_volume_signature_file_io_handle,
		 source );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

