/*
 * Library inode type test program
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

#include "../libfsext/libfsext_inode.h"

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_inode_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfsext_inode_t *inode         = NULL;
	int result                      = 0;

#if defined( HAVE_FSEXT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfsext_inode_initialize(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_inode_free(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_inode_initialize(
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

	inode = (libfsext_inode_t *) 0x12345678UL;

	result = libfsext_inode_initialize(
	          &inode,
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

	inode = NULL;

#if defined( HAVE_FSEXT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_inode_initialize with malloc failing
		 */
		fsext_test_malloc_attempts_before_fail = test_number;

		result = libfsext_inode_initialize(
		          &inode,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;

			if( inode != NULL )
			{
				libfsext_inode_free(
				 &inode,
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
			 "inode",
			 inode );

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
		/* Test libfsext_inode_initialize with memset failing
		 */
		fsext_test_memset_attempts_before_fail = test_number;

		result = libfsext_inode_initialize(
		          &inode,
		          &error );

		if( fsext_test_memset_attempts_before_fail != -1 )
		{
			fsext_test_memset_attempts_before_fail = -1;

			if( inode != NULL )
			{
				libfsext_inode_free(
				 &inode,
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
			 "inode",
			 inode );

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
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_inode_free(
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

/* Tests the libfsext_inode_clone function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_clone(
     void )
{
	libcerror_error_t *error            = NULL;
	libfsext_inode_t *destination_inode = NULL;
	libfsext_inode_t *source_inode      = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfsext_inode_initialize(
	          &source_inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "source_inode",
	 source_inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_inode_clone(
	          &destination_inode,
	          source_inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "destination_inode",
	 destination_inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_inode_free(
	          &destination_inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "destination_inode",
	 destination_inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_inode_clone(
	          &destination_inode,
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "destination_inode",
	 destination_inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_inode_clone(
	          NULL,
	          source_inode,
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
	result = libfsext_inode_free(
	          &source_inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "source_inode",
	 source_inode );

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
	if( destination_inode != NULL )
	{
		libfsext_inode_free(
		 &destination_inode,
		 NULL );
	}
	if( source_inode != NULL )
	{
		libfsext_inode_free(
		 &source_inode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_access_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_access_time(
     void )
{
	libcerror_error_t *error = NULL;
	libfsext_inode_t *inode  = NULL;
	uint32_t access_time     = 0;
	int access_time_is_set   = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfsext_inode_initialize(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_inode_get_access_time(
	          inode,
	          &access_time,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	access_time_is_set = result;

	/* Test error cases
	 */
	result = libfsext_inode_get_access_time(
	          NULL,
	          &access_time,
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

	if( access_time_is_set != 0 )
	{
		result = libfsext_inode_get_access_time(
		          inode,
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
	result = libfsext_inode_free(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "inode",
	 inode );

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
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_inode_change_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_inode_change_time(
     void )
{
	libcerror_error_t *error     = NULL;
	libfsext_inode_t *inode      = NULL;
	uint32_t inode_change_time   = 0;
	int inode_change_time_is_set = 0;
	int result                   = 0;

	/* Initialize test
	 */
	result = libfsext_inode_initialize(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_inode_get_inode_change_time(
	          inode,
	          &inode_change_time,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	inode_change_time_is_set = result;

	/* Test error cases
	 */
	result = libfsext_inode_get_inode_change_time(
	          NULL,
	          &inode_change_time,
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

	if( inode_change_time_is_set != 0 )
	{
		result = libfsext_inode_get_inode_change_time(
		          inode,
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
	result = libfsext_inode_free(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "inode",
	 inode );

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
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_modification_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_modification_time(
     void )
{
	libcerror_error_t *error     = NULL;
	libfsext_inode_t *inode      = NULL;
	uint32_t modification_time   = 0;
	int modification_time_is_set = 0;
	int result                   = 0;

	/* Initialize test
	 */
	result = libfsext_inode_initialize(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_inode_get_modification_time(
	          inode,
	          &modification_time,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	modification_time_is_set = result;

	/* Test error cases
	 */
	result = libfsext_inode_get_modification_time(
	          NULL,
	          &modification_time,
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

	if( modification_time_is_set != 0 )
	{
		result = libfsext_inode_get_modification_time(
		          inode,
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
	result = libfsext_inode_free(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "inode",
	 inode );

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
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_deletion_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_deletion_time(
     void )
{
	libcerror_error_t *error = NULL;
	libfsext_inode_t *inode  = NULL;
	uint32_t deletion_time   = 0;
	int deletion_time_is_set = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfsext_inode_initialize(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "inode",
	 inode );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfsext_inode_get_deletion_time(
	          inode,
	          &deletion_time,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	deletion_time_is_set = result;

	/* Test error cases
	 */
	result = libfsext_inode_get_deletion_time(
	          NULL,
	          &deletion_time,
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

	if( deletion_time_is_set != 0 )
	{
		result = libfsext_inode_get_deletion_time(
		          inode,
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
	result = libfsext_inode_free(
	          &inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "inode",
	 inode );

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
	if( inode != NULL )
	{
		libfsext_inode_free(
		 &inode,
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
	 "libfsext_inode_initialize",
	 fsext_test_inode_initialize );

	FSEXT_TEST_RUN(
	 "libfsext_inode_free",
	 fsext_test_inode_free );

	FSEXT_TEST_RUN(
	 "libfsext_inode_clone",
	 fsext_test_inode_clone );

	/* TODO: add tests for libfsext_inode_read_data */

	FSEXT_TEST_RUN(
	 "libfsext_inode_get_access_time",
	 fsext_test_inode_get_access_time );

	FSEXT_TEST_RUN(
	 "libfsext_inode_get_inode_change_time",
	 fsext_test_inode_get_inode_change_time );

	FSEXT_TEST_RUN(
	 "libfsext_inode_get_modification_time",
	 fsext_test_inode_get_modification_time );

	FSEXT_TEST_RUN(
	 "libfsext_inode_get_deletion_time",
	 fsext_test_inode_get_deletion_time );

	/* TODO: add tests for libfsext_inode_read_element_data */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

