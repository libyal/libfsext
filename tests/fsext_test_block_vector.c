/*
 * Library block_vector functions test program
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
#include "fsext_test_libfdata.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_block_vector.h"
#include "../libfsext/libfsext_inode.h"
#include "../libfsext/libfsext_io_handle.h"

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_block_vector_initialize function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_block_vector_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfdata_vector_t *block_vector = NULL;
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
	result = libfsext_block_vector_initialize(
	          &block_vector,
	          io_handle,
	          inode,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NOT_NULL(
	 "block_vector",
	 block_vector );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_vector_free(
	          &block_vector,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "block_vector",
	 block_vector );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_block_vector_initialize(
	          NULL,
	          io_handle,
	          inode,
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

	result = libfsext_block_vector_initialize(
	          &block_vector,
	          NULL,
	          inode,
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

	result = libfsext_block_vector_initialize(
	          &block_vector,
	          io_handle,
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

#if defined( HAVE_FSEXT_TEST_MEMORY )

	/* Test libfsext_block_vector_initialize with malloc failing in libfdata_vector_initialize
	 */
	fsext_test_malloc_attempts_before_fail = 0;

	result = libfsext_block_vector_initialize(
		  &block_vector,
		  io_handle,
		  inode,
		  &error );

	if( fsext_test_malloc_attempts_before_fail != -1 )
	{
		fsext_test_malloc_attempts_before_fail = -1;

		if( block_vector != NULL )
		{
			libfdata_vector_free(
			 &block_vector,
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
		 "block_vector",
		 block_vector );

		FSEXT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FSEXT_TEST_MEMORY ) */

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
	if( block_vector != NULL )
	{
		libfdata_vector_free(
		 &block_vector,
		 NULL );
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
	return( 1 );
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
	 "libfsext_block_vector_initialize",
	 fsext_test_block_vector_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

