/*
 * Library volume type test program
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

#include "../libfsext/libfsext_volume.h"

#if !defined( LIBFSEXT_HAVE_BFIO )

LIBFSEXT_EXTERN \
int libfsext_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsext_error_t **error );

#endif /* !defined( LIBFSEXT_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make fsext_test_volume generate verbose output
#define FSEXT_TEST_VOLUME_VERBOSE
 */

/* Creates and opens a source volume
 * Returns 1 if successful or -1 on error
 */
int fsext_test_volume_open_source(
     libfsext_volume_t **volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "fsext_test_volume_open_source";
	int result            = 0;

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
	if( libfsext_volume_initialize(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	result = libfsext_volume_open_file_io_handle(
	          *volume,
	          file_io_handle,
	          LIBFSEXT_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *volume != NULL )
	{
		libfsext_volume_free(
		 volume,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source volume
 * Returns 1 if successful or -1 on error
 */
int fsext_test_volume_close_source(
     libfsext_volume_t **volume,
     libcerror_error_t **error )
{
	static char *function = "fsext_test_volume_close_source";
	int result            = 0;

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
	if( libfsext_volume_free(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libfsext_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfsext_volume_t *volume       = NULL;
	int result                      = 0;

#if defined( HAVE_FSEXT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfsext_volume_initialize(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_volume_free(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_volume_initialize(
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

	volume = (libfsext_volume_t *) 0x12345678UL;

	result = libfsext_volume_initialize(
	          &volume,
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

	volume = NULL;

#if defined( HAVE_FSEXT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_volume_initialize with malloc failing
		 */
		fsext_test_malloc_attempts_before_fail = test_number;

		result = libfsext_volume_initialize(
		          &volume,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libfsext_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			FSEXT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FSEXT_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_volume_initialize with memset failing
		 */
		fsext_test_memset_attempts_before_fail = test_number;

		result = libfsext_volume_initialize(
		          &volume,
		          &error );

		if( fsext_test_memset_attempts_before_fail != -1 )
		{
			fsext_test_memset_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libfsext_volume_free(
				 &volume,
				 NULL );
			}
		}
		else
		{
			FSEXT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FSEXT_TEST_ASSERT_IS_NULL(
			 "volume",
			 volume );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_volume_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_volume_free(
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

/* Tests the libfsext_volume_open function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libfsext_volume_t *volume = NULL;
	int result                = 0;

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

	result = libfsext_volume_initialize(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libfsext_volume_open(
	          volume,
	          narrow_source,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_open(
	          NULL,
	          narrow_source,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open(
	          volume,
	          NULL,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open(
	          volume,
	          narrow_source,
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

	/* Test open when already opened
	 */
	result = libfsext_volume_open(
	          volume,
	          narrow_source,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_free(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libfsext_volume_open_wide function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libfsext_volume_t *volume = NULL;
	int result                = 0;

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

	result = libfsext_volume_initialize(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libfsext_volume_open_wide(
	          volume,
	          wide_source,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_open_wide(
	          NULL,
	          wide_source,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open_wide(
	          volume,
	          NULL,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open_wide(
	          volume,
	          wide_source,
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

	/* Test open when already opened
	 */
	result = libfsext_volume_open_wide(
	          volume,
	          wide_source,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_free(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libfsext_volume_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libfsext_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

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

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FSEXT_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfsext_volume_initialize(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libfsext_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open_file_io_handle(
	          volume,
	          NULL,
	          LIBFSEXT_OPEN_READ,
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

	result = libfsext_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
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

	/* Test open when already opened
	 */
	result = libfsext_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBFSEXT_OPEN_READ,
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
	result = libfsext_volume_free(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_volume_close function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_volume_close(
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

/* Tests the libfsext_volume_open and libfsext_volume_close functions
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libfsext_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libfsext_volume_initialize(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "volume",
	 volume );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_volume_open_wide(
	          volume,
	          source,
	          LIBFSEXT_OPEN_READ,
	          &error );
#else
	result = libfsext_volume_open(
	          volume,
	          source,
	          LIBFSEXT_OPEN_READ,
	          &error );
#endif

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_volume_close(
	          volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfsext_volume_open_wide(
	          volume,
	          source,
	          LIBFSEXT_OPEN_READ,
	          &error );
#else
	result = libfsext_volume_open(
	          volume,
	          source,
	          LIBFSEXT_OPEN_READ,
	          &error );
#endif

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_volume_close(
	          volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfsext_volume_free(
	          &volume,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_volume_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_signal_abort(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_signal_abort(
	          volume,
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
	result = libfsext_volume_signal_abort(
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

/* Tests the libfsext_volume_get_utf8_label_size function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_utf8_label_size(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error   = NULL;
	size_t utf8_label_size     = 0;
	int result                 = 0;
	int utf8_label_size_is_set = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_utf8_label_size(
	          volume,
	          &utf8_label_size,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_label_size_is_set = result;

	/* Test error cases
	 */
	result = libfsext_volume_get_utf8_label_size(
	          NULL,
	          &utf8_label_size,
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

	if( utf8_label_size_is_set != 0 )
	{
		result = libfsext_volume_get_utf8_label_size(
		          volume,
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

/* Tests the libfsext_volume_get_utf8_label function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_utf8_label(
     libfsext_volume_t *volume )
{
	uint8_t utf8_label[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;
	int utf8_label_is_set    = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_utf8_label(
	          volume,
	          utf8_label,
	          512,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_label_is_set = result;

	/* Test error cases
	 */
	result = libfsext_volume_get_utf8_label(
	          NULL,
	          utf8_label,
	          512,
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

	if( utf8_label_is_set != 0 )
	{
		result = libfsext_volume_get_utf8_label(
		          volume,
		          NULL,
		          512,
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

		result = libfsext_volume_get_utf8_label(
		          volume,
		          utf8_label,
		          0,
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

		result = libfsext_volume_get_utf8_label(
		          volume,
		          utf8_label,
		          (size_t) SSIZE_MAX + 1,
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

/* Tests the libfsext_volume_get_utf16_label_size function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_utf16_label_size(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error    = NULL;
	size_t utf16_label_size     = 0;
	int result                  = 0;
	int utf16_label_size_is_set = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_utf16_label_size(
	          volume,
	          &utf16_label_size,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_label_size_is_set = result;

	/* Test error cases
	 */
	result = libfsext_volume_get_utf16_label_size(
	          NULL,
	          &utf16_label_size,
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

	if( utf16_label_size_is_set != 0 )
	{
		result = libfsext_volume_get_utf16_label_size(
		          volume,
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

/* Tests the libfsext_volume_get_utf16_label function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_utf16_label(
     libfsext_volume_t *volume )
{
	uint16_t utf16_label[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;
	int utf16_label_is_set   = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_utf16_label(
	          volume,
	          utf16_label,
	          512,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_label_is_set = result;

	/* Test error cases
	 */
	result = libfsext_volume_get_utf16_label(
	          NULL,
	          utf16_label,
	          512,
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

	if( utf16_label_is_set != 0 )
	{
		result = libfsext_volume_get_utf16_label(
		          volume,
		          NULL,
		          512,
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

		result = libfsext_volume_get_utf16_label(
		          volume,
		          utf16_label,
		          0,
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

		result = libfsext_volume_get_utf16_label(
		          volume,
		          utf16_label,
		          (size_t) SSIZE_MAX + 1,
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

/* Tests the libfsext_volume_get_last_mount_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_last_mount_time(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int32_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_last_mount_time(
	          volume,
	          &posix_time,
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
	result = libfsext_volume_get_last_mount_time(
	          NULL,
	          &posix_time,
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

	result = libfsext_volume_get_last_mount_time(
	          volume,
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

/* Tests the libfsext_volume_get_last_written_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_last_written_time(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int32_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_last_written_time(
	          volume,
	          &posix_time,
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
	result = libfsext_volume_get_last_written_time(
	          NULL,
	          &posix_time,
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

	result = libfsext_volume_get_last_written_time(
	          volume,
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

/* Tests the libfsext_volume_get_root_directory function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_volume_get_root_directory(
     libfsext_volume_t *volume )
{
	libcerror_error_t *error              = NULL;
	libfsext_file_entry_t *root_directory = 0;
	int result                            = 0;
	int root_directory_is_set             = 0;

	/* Test regular cases
	 */
	result = libfsext_volume_get_root_directory(
	          volume,
	          &root_directory,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	root_directory_is_set = result;

	if( root_directory_is_set != 0 )
	{
		FSEXT_TEST_ASSERT_IS_NOT_NULL(
		 "root_directory",
		 root_directory );

		result = libfsext_file_entry_free(
		          &root_directory,
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
	result = libfsext_volume_get_root_directory(
	          NULL,
	          &root_directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "root_directory",
	 root_directory );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( root_directory_is_set != 0 )
	{
		result = libfsext_volume_get_root_directory(
		          volume,
		          NULL,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "root_directory",
		 root_directory );

		FSEXT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
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
	libbfio_handle_t *file_io_handle  = NULL;
	libcerror_error_t *error          = NULL;
	libfsext_volume_t *volume         = NULL;
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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( FSEXT_TEST_VOLUME_VERBOSE )
	libfsext_notify_set_verbose(
	 1 );
	libfsext_notify_set_stream(
	 stderr,
	 NULL );
#endif

	FSEXT_TEST_RUN(
	 "libfsext_volume_initialize",
	 fsext_test_volume_initialize );

	FSEXT_TEST_RUN(
	 "libfsext_volume_free",
	 fsext_test_volume_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_range_initialize(
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_range_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_range_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        FSEXT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libbfio_file_range_set(
		          file_io_handle,
		          volume_offset,
		          0,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        FSEXT_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libfsext_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( ( result != 0 )
	 && ( volume_offset == 0 ) )
	{
		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_open",
		 fsext_test_volume_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_open_wide",
		 fsext_test_volume_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_open_file_io_handle",
		 fsext_test_volume_open_file_io_handle,
		 source );

		FSEXT_TEST_RUN(
		 "libfsext_volume_close",
		 fsext_test_volume_close );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_open_close",
		 fsext_test_volume_open_close,
		 source );
	}
	if( result != 0 )
	{
		/* Initialize volume for tests
		 */
		result = fsext_test_volume_open_source(
		          &volume,
		          file_io_handle,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FSEXT_TEST_ASSERT_IS_NOT_NULL(
		 "volume",
		 volume );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_signal_abort",
		 fsext_test_volume_signal_abort,
		 volume );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

		/* TODO: add tests for libfsext_volume_open_read */

		/* TODO: add tests for libfsext_volume_read_block_groups */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_utf8_label_size",
		 fsext_test_volume_get_utf8_label_size,
		 volume );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_utf8_label",
		 fsext_test_volume_get_utf8_label,
		 volume );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_utf16_label_size",
		 fsext_test_volume_get_utf16_label_size,
		 volume );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_utf16_label",
		 fsext_test_volume_get_utf16_label,
		 volume );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_last_mount_time",
		 fsext_test_volume_get_last_mount_time,
		 volume );

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_last_written_time",
		 fsext_test_volume_get_last_written_time,
		 volume );

		/* TODO: add tests for libfsntfs_volume_get_number_of_file_entries */

		/* TODO: add tests for libfsntfs_volume_get_file_entry_by_index */

		FSEXT_TEST_RUN_WITH_ARGS(
		 "libfsext_volume_get_root_directory",
		 fsext_test_volume_get_root_directory,
		 volume );

		/* Clean up
		 */
		result = fsext_test_volume_close_source(
		          &volume,
		          &error );

		FSEXT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "volume",
		 volume );

		FSEXT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
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
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libfsext_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

