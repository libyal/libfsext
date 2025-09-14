/*
 * Library checksum functions test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fsext_test_libcerror.h"
#include "fsext_test_libfsext.h"
#include "fsext_test_macros.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_checksum.h"

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

/* Tests the libfsext_checksum_initialize_crc32_table function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_checksum_initialize_crc32_table(
     void )
{
	/* Test invocation of function only
	 */
	libfsext_checksum_initialize_crc32_table(
	 0x82f63b78UL );

	return( 1 );
}

/* Tests the libfsext_checksum_calculate_weak_crc32 function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_checksum_calculate_weak_crc32(
     void )
{
	uint8_t data[ 16 ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	libcerror_error_t *error = NULL;
	uint32_t checksum        = 0;
	int result               = 0;

	libfsext_checksum_crc32_table_computed = 0;

	/* Test regular cases
	 */
	result = libfsext_checksum_calculate_weak_crc32(
	          &checksum,
	          data,
	          16,
	          0,
	          &error );

	FSEXT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FSEXT_TEST_ASSERT_EQUAL_UINT32(
	 "checksum",
	 checksum,
	 (uint32_t) 0x9bb99201UL );

	FSEXT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfsext_checksum_calculate_weak_crc32(
	          NULL,
	          data,
	          16,
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

	result = libfsext_checksum_calculate_weak_crc32(
	          &checksum,
	          NULL,
	          16,
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

	result = libfsext_checksum_calculate_weak_crc32(
	          &checksum,
	          data,
	          (size_t) SSIZE_MAX + 1,
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
	 "libfsext_checksum_initialize_crc32_table",
	 fsext_test_checksum_initialize_crc32_table );

	FSEXT_TEST_RUN(
	 "libfsext_checksum_calculate_weak_crc32",
	 fsext_test_checksum_calculate_weak_crc32 );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */
}

