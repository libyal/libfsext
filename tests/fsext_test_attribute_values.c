/*
 * Library attribute_values type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_libuna.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_attribute_values.h"

uint8_t fsext_test_attribute_values_data1[ 24 ] = {
        0x08, 0x01, 0xbc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x2b, 0xfe, 0x48, 0x83,
        0x6d, 0x79, 0x78, 0x61, 0x74, 0x74, 0x72, 0x31 };

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_attribute_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libfsext_attribute_values_t *attribute_values = NULL;
	int result                                    = 0;

#if defined( HAVE_FSEXT_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 1;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Test regular cases
	 */
	result = libfsext_attribute_values_initialize(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "attribute_values",
	 attribute_values );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_attribute_values_free(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "attribute_values",
	 attribute_values );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_attribute_values_initialize(
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

	attribute_values = (libfsext_attribute_values_t *) 0x12345678UL;

	result = libfsext_attribute_values_initialize(
	          &attribute_values,
	          &error );

	attribute_values = NULL;

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FSEXT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_attribute_values_initialize with malloc failing
		 */
		fsext_test_malloc_attempts_before_fail = test_number;

		result = libfsext_attribute_values_initialize(
		          &attribute_values,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;

			if( attribute_values != NULL )
			{
				libfsext_attribute_values_free(
				 &attribute_values,
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
			 "attribute_values",
			 attribute_values );

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
		/* Test libfsext_attribute_values_initialize with memset failing
		 */
		fsext_test_memset_attempts_before_fail = test_number;

		result = libfsext_attribute_values_initialize(
		          &attribute_values,
		          &error );

		if( fsext_test_memset_attempts_before_fail != -1 )
		{
			fsext_test_memset_attempts_before_fail = -1;

			if( attribute_values != NULL )
			{
				libfsext_attribute_values_free(
				 &attribute_values,
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
			 "attribute_values",
			 attribute_values );

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
	if( attribute_values != NULL )
	{
		libfsext_attribute_values_free(
		 &attribute_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_attribute_values_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_attribute_values_free(
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

/* Tests the libfsext_attribute_values_read_data function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_read_data(
     void )
{
	libcerror_error_t *error                    = NULL;
	libfsext_attribute_values_t *attribute_values = NULL;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libfsext_attribute_values_initialize(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "attribute_values",
	 attribute_values );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_attribute_values_read_data(
	          attribute_values,
	          fsext_test_attribute_values_data1,
	          24,
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
	result = libfsext_attribute_values_read_data(
	          NULL,
	          fsext_test_attribute_values_data1,
	          24,
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

	result = libfsext_attribute_values_read_data(
	          attribute_values,
	          NULL,
	          24,
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

	result = libfsext_attribute_values_read_data(
	          attribute_values,
	          fsext_test_attribute_values_data1,
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

	result = libfsext_attribute_values_read_data(
	          attribute_values,
	          fsext_test_attribute_values_data1,
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

	/* Clean up
	 */
	result = libfsext_attribute_values_free(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "attribute_values",
	 attribute_values );

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
	if( attribute_values != NULL )
	{
		libfsext_attribute_values_free(
		 &attribute_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_attribute_values_compare_name_with_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int fsapfs_test_attribute_values_compare_name_with_utf8_string(
     libfsext_attribute_values_t *attribute_values )
{
	uint8_t utf8_string[ 14 ] = { 'u', 's', 'e', 'r', '.', 'm', 'y', 'x', 'a', 't', 't', 'r', '1', 0 };
	libcerror_error_t *error  = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_compare_name_with_utf8_string(
	          attribute_values,
	          utf8_string,
	          13,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_attribute_values_compare_name_with_utf8_string(
	          NULL,
	          utf8_string,
	          13,
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

	result = libfsext_attribute_values_compare_name_with_utf8_string(
		  attribute_values,
		  NULL,
	          13,
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

/* Tests the libfsext_attribute_values_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_get_utf8_name_size(
     libfsext_attribute_values_t *attribute_values )
{
	libcerror_error_t *error = NULL;
	size_t utf8_name_size    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_get_utf8_name_size(
	          attribute_values,
	          &utf8_name_size,
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
	result = libfsext_attribute_values_get_utf8_name_size(
	          NULL,
	          &utf8_name_size,
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

	result = libfsext_attribute_values_get_utf8_name_size(
		  attribute_values,
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

/* Tests the libfsext_attribute_values_get_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_get_utf8_name(
     libfsext_attribute_values_t *attribute_values )
{
	uint8_t utf8_name[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_get_utf8_name(
	          attribute_values,
	          utf8_name,
	          256,
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
	result = libfsext_attribute_values_get_utf8_name(
	          NULL,
	          utf8_name,
	          256,
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

	result = libfsext_attribute_values_get_utf8_name(
	          attribute_values,
	          NULL,
	          256,
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

	result = libfsext_attribute_values_get_utf8_name(
	          attribute_values,
	          utf8_name,
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

	result = libfsext_attribute_values_get_utf8_name(
	          attribute_values,
	          utf8_name,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_attribute_values_compare_name_with_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int fsapfs_test_attribute_values_compare_name_with_utf16_string(
     libfsext_attribute_values_t *attribute_values )
{
	uint16_t utf16_string[ 14 ] = { 'u', 's', 'e', 'r', '.', 'm', 'y', 'x', 'a', 't', 't', 'r', '1', 0 };
	libcerror_error_t *error    = NULL;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_compare_name_with_utf16_string(
	          attribute_values,
	          utf16_string,
	          13,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBUNA_COMPARE_EQUAL );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_attribute_values_compare_name_with_utf16_string(
	          NULL,
	          utf16_string,
	          13,
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

	result = libfsext_attribute_values_compare_name_with_utf16_string(
		  attribute_values,
		  NULL,
	          13,
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

/* Tests the libfsext_attribute_values_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_get_utf16_name_size(
     libfsext_attribute_values_t *attribute_values )
{
	libcerror_error_t *error = NULL;
	size_t utf16_name_size   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_get_utf16_name_size(
	          attribute_values,
	          &utf16_name_size,
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
	result = libfsext_attribute_values_get_utf16_name_size(
	          NULL,
	          &utf16_name_size,
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

	result = libfsext_attribute_values_get_utf16_name_size(
		  attribute_values,
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

/* Tests the libfsext_attribute_values_get_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_attribute_values_get_utf16_name(
     libfsext_attribute_values_t *attribute_values )
{
	uint16_t utf16_name[ 256 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_attribute_values_get_utf16_name(
	          attribute_values,
	          utf16_name,
	          256,
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
	result = libfsext_attribute_values_get_utf16_name(
	          NULL,
	          utf16_name,
	          256,
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

	result = libfsext_attribute_values_get_utf16_name(
	          attribute_values,
	          NULL,
	          256,
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

	result = libfsext_attribute_values_get_utf16_name(
	          attribute_values,
	          utf16_name,
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

	result = libfsext_attribute_values_get_utf16_name(
	          attribute_values,
	          utf16_name,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FSEXT_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FSEXT_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FSEXT_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FSEXT_TEST_ATTRIBUTE_UNUSED )
#endif
{
#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )
	libcerror_error_t *error                      = NULL;
	libfsext_attribute_values_t *attribute_values = NULL;
	int result                                    = 0;
#endif

	FSEXT_TEST_UNREFERENCED_PARAMETER( argc )
	FSEXT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	FSEXT_TEST_RUN(
	 "libfsext_attribute_values_initialize",
	 fsext_test_attribute_values_initialize );

	FSEXT_TEST_RUN(
	 "libfsext_attribute_values_free",
	 fsext_test_attribute_values_free );

	FSEXT_TEST_RUN(
	 "libfsext_attribute_values_read_data",
	 fsext_test_attribute_values_read_data );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize attribute_values for tests
	 */
	result = libfsext_attribute_values_initialize(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "attribute_values",
	 attribute_values );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_attribute_values_read_data(
	          attribute_values,
	          fsext_test_attribute_values_data1,
	          24,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_compare_name_with_utf8_string",
	 fsapfs_test_attribute_values_compare_name_with_utf8_string,
	 attribute_values );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_get_utf8_name_size",
	 fsext_test_attribute_values_get_utf8_name_size,
	 attribute_values );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_get_utf8_name",
	 fsext_test_attribute_values_get_utf8_name,
	 attribute_values );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_compare_name_with_utf16_string",
	 fsapfs_test_attribute_values_compare_name_with_utf16_string,
	 attribute_values );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_get_utf16_name_size",
	 fsext_test_attribute_values_get_utf16_name_size,
	 attribute_values );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_attribute_values_get_utf16_name",
	 fsext_test_attribute_values_get_utf16_name,
	 attribute_values );

	/* Clean up
	 */
	result = libfsext_attribute_values_free(
	          &attribute_values,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "attribute_values",
	 attribute_values );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

on_error:
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( attribute_values != NULL )
	{
		libfsext_attribute_values_free(
		 &attribute_values,
		 NULL );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */
}

