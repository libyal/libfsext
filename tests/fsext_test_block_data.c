/*
 * Library inode type test program
 *
 * Copyright (C) 2010-2025, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfsext/libfsext_block_data.h"

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

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_block_data_check_empty function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_block_data_check_empty(
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
	result = libfsext_block_data_check_empty(
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

	result = libfsext_block_data_check_empty(
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

	result = libfsext_block_data_check_empty(
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
	result = libfsext_block_data_check_empty(
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

	result = libfsext_block_data_check_empty(
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
	 "libfsext_block_data_check_empty",
	 fsext_test_block_data_check_empty );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */
}

