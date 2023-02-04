/*
 * Library inode type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_extent.h"
#include "../libfsext/libfsext_inode.h"
#include "../libfsext/libfsext_io_handle.h"

/* ext3 inode */
uint8_t fsext_test_inode_data1[ 128 ] = {
	0x00, 0x04, 0x00, 0x00, 0x3d, 0x13, 0xc1, 0x3f, 0x44, 0x13, 0xc1, 0x3f, 0x44, 0x13, 0xc1, 0x3f,
	0x00, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* ext4 inode without EXT4_EXTENTS_FL */
uint8_t fsext_test_inode_data2[ 128 ] = {
	0xed, 0x41, 0xe8, 0x03, 0x00, 0x04, 0x00, 0x00, 0xdf, 0xc3, 0xd7, 0x49, 0xdf, 0xc3, 0xd7, 0x49,
	0xdf, 0xc3, 0xd7, 0x49, 0x00, 0x00, 0x00, 0x00, 0xe8, 0x03, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* ext4 inode with EXT4_EXTENTS_FL */
uint8_t fsext_test_inode_data3[ 128 ] = {
	0xed, 0x41, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xb4, 0x69, 0x47, 0x55, 0xb4, 0x69, 0x47, 0x55,
	0xb4, 0x69, 0x47, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xf3, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* empty inode */
uint8_t fsext_test_inode_data4[ 128 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_inode_check_for_empty_block function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_check_for_empty_block(
     void )
{
	uint8_t inode_data[ 128 ];

	libcerror_error_t *error = NULL;
	void *memset_result      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	memset_result = memory_set(
	                 inode_data,
	                 0,
	                 sizeof( uint8_t ) * 128 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "memset_result",
	 memset_result );

	/* Test regular cases
	 */
	result = libfsext_inode_check_for_empty_block(
	          inode_data,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	inode_data[ 127 ] = 0xff;

	result = libfsext_inode_check_for_empty_block(
	          &( inode_data[ 1 ] ),
	          128 - 1,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_inode_check_for_empty_block(
	          fsext_test_inode_data1,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_inode_check_for_empty_block(
	          NULL,
	          128,
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

	result = libfsext_inode_check_for_empty_block(
	          inode_data,
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
	int number_of_malloc_fail_tests = 2;
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

#if defined( HAVE_FSEXT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int test_number                 = 0;

#if defined( OPTIMIZATION_DISABLED )
	int number_of_memcpy_fail_tests = 1;
#endif
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */

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

	destination_inode = (libfsext_inode_t *) 0x12345678UL;

	result = libfsext_inode_clone(
	          &destination_inode,
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

	destination_inode = NULL;

#if defined( HAVE_FSEXT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_inode_clone with malloc failing
		 */
		fsext_test_malloc_attempts_before_fail = test_number;

		result = libfsext_inode_clone(
		          &destination_inode,
		          source_inode,
		          &error );

		if( fsext_test_malloc_attempts_before_fail != -1 )
		{
			fsext_test_malloc_attempts_before_fail = -1;

			if( destination_inode != NULL )
			{
				libfsext_inode_free(
				 &destination_inode,
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
			 "destination_inode",
			 destination_inode );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#if defined( OPTIMIZATION_DISABLED )

	for( test_number = 0;
	     test_number < number_of_memcpy_fail_tests;
	     test_number++ )
	{
		/* Test libfsext_inode_clone with memcpy failing
		 */
		fsext_test_memcpy_attempts_before_fail = 0;

		result = libfsext_inode_clone(
		          &destination_inode,
		          source_inode,
		          &error );

		if( fsext_test_memcpy_attempts_before_fail != -1 )
		{
			fsext_test_memcpy_attempts_before_fail = -1;

			if( destination_inode != NULL )
			{
				libfsext_inode_free(
				 &destination_inode,
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
			 "destination_inode",
			 destination_inode );

			FSEXT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */

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

/* Tests the libfsext_inode_read_data function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_read_data(
     void )
{
	libcerror_error_t *error        = NULL;
	libfsext_inode_t *inode         = NULL;
	libfsext_io_handle_t *io_handle = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libfsext_io_handle_initialize(
	          &io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->format_version = 4;
	io_handle->block_size     = 1024;
	io_handle->inode_size     = 128;

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
	io_handle->format_version = 3;
	io_handle->inode_size     = 0;

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data1,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->format_version = 4;
	io_handle->inode_size     = 128;

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data2,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->format_version = 4;
	io_handle->inode_size     = 128;

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data3,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "inode->is_empty",
	 inode->is_empty,
	 0 );

	io_handle->format_version = 2;
	io_handle->inode_size     = 0;

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data4,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "inode->is_empty",
	 inode->is_empty,
	 1 );

	/* Test error cases
	 */
	io_handle->format_version = 3;
	io_handle->inode_size     = 0;

	result = libfsext_inode_read_data(
	          NULL,
	          io_handle,
	          fsext_test_inode_data1,
	          128,
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

	result = libfsext_inode_read_data(
	          inode,
	          NULL,
	          fsext_test_inode_data1,
	          128,
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

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          NULL,
	          128,
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

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data1,
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

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data1,
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

	result = libfsext_io_handle_free(
	          &io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libfsext_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_access_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_access_time(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int64_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_access_time(
	          inode,
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
	result = libfsext_inode_get_access_time(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_creation_time(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int64_t posix_time       = 0;
	int creation_time_is_set = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_creation_time(
	          inode,
	          &posix_time,
	          &error );

	FSEXT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	creation_time_is_set = result;

	/* Test error cases
	 */
	result = libfsext_inode_get_creation_time(
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

	if( creation_time_is_set != 0 )
	{
		result = libfsext_inode_get_creation_time(
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
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_inode_change_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_inode_change_time(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int64_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_inode_change_time(
	          inode,
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
	result = libfsext_inode_get_inode_change_time(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_modification_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_modification_time(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int64_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_modification_time(
	          inode,
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
	result = libfsext_inode_get_modification_time(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_deletion_time function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_deletion_time(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int32_t posix_time       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_deletion_time(
	          inode,
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
	result = libfsext_inode_get_deletion_time(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_file_mode function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_file_mode(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	uint16_t file_mode       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_file_mode(
	          inode,
	          &file_mode,
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
	result = libfsext_inode_get_file_mode(
	          NULL,
	          &file_mode,
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

	result = libfsext_inode_get_file_mode(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_number_of_links function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_number_of_links(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	uint16_t number_of_links = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_number_of_links(
	          inode,
	          &number_of_links,
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
	result = libfsext_inode_get_number_of_links(
	          NULL,
	          &number_of_links,
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

	result = libfsext_inode_get_number_of_links(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_owner_identifier function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_owner_identifier(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error  = NULL;
	uint32_t owner_identifier = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_owner_identifier(
	          inode,
	          &owner_identifier,
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
	result = libfsext_inode_get_owner_identifier(
	          NULL,
	          &owner_identifier,
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

	result = libfsext_inode_get_owner_identifier(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_group_identifier function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_group_identifier(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error  = NULL;
	uint32_t group_identifier = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_group_identifier(
	          inode,
	          &group_identifier,
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
	result = libfsext_inode_get_group_identifier(
	          NULL,
	          &group_identifier,
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

	result = libfsext_inode_get_group_identifier(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_file_acl_block_number function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_file_acl_block_number(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error       = NULL;
	uint32_t file_acl_block_number = 0;
	int result                     = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_file_acl_block_number(
	          inode,
	          &file_acl_block_number,
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
	result = libfsext_inode_get_file_acl_block_number(
	          NULL,
	          &file_acl_block_number,
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

	result = libfsext_inode_get_file_acl_block_number(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_device_number function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_device_number(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error    = NULL;
	uint8_t major_device_number = 0;
	uint8_t minor_device_number = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_device_number(
	          inode,
	          &major_device_number,
	          &minor_device_number,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_inode_get_device_number(
	          NULL,
	          &major_device_number,
	          &minor_device_number,
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

	result = libfsext_inode_get_device_number(
	          inode,
	          NULL,
	          &minor_device_number,
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

	result = libfsext_inode_get_device_number(
	          inode,
	          &major_device_number,
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

/* Tests the libfsext_inode_get_number_of_extents function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_number_of_extents(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error = NULL;
	int number_of_extents    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_number_of_extents(
	          inode,
	          &number_of_extents,
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
	result = libfsext_inode_get_number_of_extents(
	          NULL,
	          &number_of_extents,
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

	result = libfsext_inode_get_number_of_extents(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfsext_inode_get_extent_by_index function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_inode_get_extent_by_index(
     libfsext_inode_t *inode )
{
	libcerror_error_t *error  = NULL;
	libfsext_extent_t *extent = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfsext_inode_get_extent_by_index(
	          inode,
	          0,
	          &extent,
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
	result = libfsext_inode_get_extent_by_index(
	          NULL,
	          0,
	          &extent,
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

	result = libfsext_inode_get_extent_by_index(
	          inode,
	          0,
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
	libcerror_error_t *error        = NULL;
	libfsext_inode_t *inode         = NULL;
	libfsext_io_handle_t *io_handle = NULL;
	int result                      = 0;
#endif

	FSEXT_TEST_UNREFERENCED_PARAMETER( argc )
	FSEXT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	FSEXT_TEST_RUN(
	 "libfsext_inode_check_for_empty_block",
	 fsext_test_inode_check_for_empty_block );

	FSEXT_TEST_RUN(
	 "libfsext_inode_initialize",
	 fsext_test_inode_initialize );

	FSEXT_TEST_RUN(
	 "libfsext_inode_free",
	 fsext_test_inode_free );

	FSEXT_TEST_RUN(
	 "libfsext_inode_clone",
	 fsext_test_inode_clone );

	FSEXT_TEST_RUN(
	 "libfsext_inode_read_data",
	 fsext_test_inode_read_data );

	/* TODO: add tests for libfsext_inode_read_element_data */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize inode for tests
	 */
	result = libfsext_io_handle_initialize(
	          &io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->format_version = 4;
	io_handle->block_size     = 1024;
	io_handle->inode_size     = 128;

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

	result = libfsext_inode_read_data(
	          inode,
	          io_handle,
	          fsext_test_inode_data3,
	          128,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfsext_inode_read_data_reference(
	          inode,
	          io_handle,
	          NULL,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO add test for libfsext_inode_is_empty */

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_access_time",
	 fsext_test_inode_get_access_time,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_creation_time",
	 fsext_test_inode_get_creation_time,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_inode_change_time",
	 fsext_test_inode_get_inode_change_time,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_modification_time",
	 fsext_test_inode_get_modification_time,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_deletion_time",
	 fsext_test_inode_get_deletion_time,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_file_mode",
	 fsext_test_inode_get_file_mode,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_number_of_links",
	 fsext_test_inode_get_number_of_links,
	 inode );

/* TODO add test for libfsext_inode_get_data_size */

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_owner_identifier",
	 fsext_test_inode_get_owner_identifier,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_group_identifier",
	 fsext_test_inode_get_group_identifier,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_file_acl_block_number",
	 fsext_test_inode_get_file_acl_block_number,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_device_number",
	 fsext_test_inode_get_device_number,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_number_of_extents",
	 fsext_test_inode_get_number_of_extents,
	 inode );

	FSEXT_TEST_RUN_WITH_ARGS(
	 "libfsext_inode_get_extent_by_index",
	 fsext_test_inode_get_extent_by_index,
	 inode );

/* TODO add test for libfsext_inode_read_element_data */

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

	result = libfsext_io_handle_free(
	          &io_handle,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

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
	if( io_handle != NULL )
	{
		libfsext_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */
}

