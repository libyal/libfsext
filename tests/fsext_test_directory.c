/*
 * Library directory type test program
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_directory.h"

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_directory_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_directory_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfsext_directory_t *directory = NULL;
	int result                      = 0;

#if defined( HAVE_FSEXT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfsext_directory_initialize(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "directory",
	 directory );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_directory_free(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "directory",
	 directory );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_directory_initialize(
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

	directory = (libfsext_directory_t *) 0x12345678UL;

	result = libfsext_directory_initialize(
	          &directory,
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

	directory = NULL;

#if defined( HAVE_FSEXT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_directory_initialize with malloc failing
		 */
		fsext_test_malloc_attempts_before_fail = test_number;

		result = libfsext_directory_initialize(
		          &directory,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;

			if( directory != NULL )
			{
				libfsext_directory_free(
				 &directory,
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
			 "directory",
			 directory );

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
		/* Test libfsext_directory_initialize with memset failing
		 */
		fsext_test_memset_attempts_before_fail = test_number;

		result = libfsext_directory_initialize(
		          &directory,
		          &error );

		if( fsext_test_memset_attempts_before_fail != -1 )
		{
			fsext_test_memset_attempts_before_fail = -1;

			if( directory != NULL )
			{
				libfsext_directory_free(
				 &directory,
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
			 "directory",
			 directory );

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
	if( directory != NULL )
	{
		libfsext_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_directory_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_directory_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_directory_free(
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

/* Tests the libfsext_directory_get_number_of_entries function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_directory_get_number_of_entries(
     void )
{
	libcerror_error_t *error        = NULL;
	libfsext_directory_t *directory = NULL;
	int number_of_entries           = 0;
	int number_of_entries_is_set    = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfsext_directory_initialize(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "directory",
	 directory );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_directory_get_number_of_entries(
	          directory,
	          &number_of_entries,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_entries_is_set = result;

	/* Test error cases
	 */
	result = libfsext_directory_get_number_of_entries(
	          NULL,
	          &number_of_entries,
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

	if( number_of_entries_is_set != 0 )
	{
		result = libfsext_directory_get_number_of_entries(
		          directory,
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
	/* Clean up
	 */
	result = libfsext_directory_free(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "directory",
	 directory );

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
	if( directory != NULL )
	{
		libfsext_directory_free(
		 &directory,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_directory_get_entry_by_index function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_directory_get_entry_by_index(
     void )
{
	libcerror_error_t *error                   = NULL;
	libfsext_directory_t *directory            = NULL;
	libfsext_directory_entry_t *entry_by_index = 0;
	int result                                 = 0;

	/* Initialize test
	 */
	result = libfsext_directory_initialize(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "directory",
	 directory );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_directory_get_entry_by_index(
	          directory,
	          0,
	          &entry_by_index,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "entry_by_index",
	 entry_by_index );

	result = libfsext_directory_entry_free(
	          &entry_by_index,
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
	result = libfsext_directory_get_entry_by_index(
	          NULL,
	          0,
	          &entry_by_index,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "entry_by_index",
	 entry_by_index );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfsext_directory_get_entry_by_index(
	          directory,
	          -1,
	          &entry_by_index,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "entry_by_index",
	 entry_by_index );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfsext_directory_get_entry_by_index(
	          directory,
	          0,
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "entry_by_index",
	 entry_by_index );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libfsext_directory_free(
	          &directory,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "directory",
	 directory );

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
	if( directory != NULL )
	{
		libfsext_directory_free(
		 &directory,
		 NULL );
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
	FSEXT_TEST_UNREFERENCED_PARAMETER( argc )
	FSEXT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	FSEXT_TEST_RUN(
	 "libfsext_directory_initialize",
	 fsext_test_directory_initialize );

	FSEXT_TEST_RUN(
	 "libfsext_directory_free",
	 fsext_test_directory_free );

	/* TODO: add tests for libfsext_directory_read_file_io_handle */

	FSEXT_TEST_RUN(
	 "libfsext_directory_get_number_of_entries",
	 fsext_test_directory_get_number_of_entries );

#ifdef TODO

	FSEXT_TEST_RUN(
	 "libfsext_directory_get_entry_by_index",
	 fsext_test_directory_get_entry_by_index );

#endif /* TODO */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

