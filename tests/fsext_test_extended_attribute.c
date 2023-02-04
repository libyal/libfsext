/*
 * Library extended_attribute type test program
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

#if defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#endif

#include <time.h>

#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_extended_attribute.h"

#define FSEXT_TEST_EXTENDED_ATTRIBUTE_READ_BUFFER_SIZE	4096

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

/* Tests the libfsext_extended_attribute_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_extended_attribute_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_extended_attribute_free(
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

	/* TODO: add tests for libfsext_extended_attribute_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	FSEXT_TEST_RUN(
	 "libfsext_extended_attribute_free",
	 fsext_test_extended_attribute_free );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	/* TODO: add tests for libfsext_internal_extended_attribute_free */

	/* TODO: add tests for libfsext_extended_attribute_read_key_data */

	/* TODO: add tests for libfsext_extended_attribute_read_value_data */

	/* TODO: add tests for libfsext_extended_attribute_get_data_stream */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	/* TODO: add tests for libfsext_extended_attribute_get_utf8_name_size */

	/* TODO: add tests for libfsext_extended_attribute_get_utf8_name */

	/* TODO: add tests for libfsext_extended_attribute_get_utf16_name_size */

	/* TODO: add tests for libfsext_extended_attribute_get_utf16_name */

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	/* TODO: add tests for libfsext_internal_extended_attribute_get_data_stream */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	/* TODO: add tests for libfsext_extended_attribute_read_buffer */

	/* TODO: add tests for libfsext_extended_attribute_read_buffer_at_offset */

	/* TODO: add tests for libfsext_extended_attribute_seek_offset */

	/* TODO: add tests for libfsext_extended_attribute_get_offset */

	/* TODO: add tests for libfsext_extended_attribute_get_size */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

