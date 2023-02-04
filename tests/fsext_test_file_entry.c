/*
 * Library file_entry type test program
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
#include "fsext_test_macros.h"
#include "fsext_test_memory.h"
#include "fsext_test_unused.h"

#include "../libfsext/libfsext_file_entry.h"

/* Tests the libfsext_file_entry_free function
 * Returns 1 if successful or 0 if not
 */
int fsext_test_file_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfsext_file_entry_free(
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

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

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

	/* TODO: add tests for libfsext_file_entry_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	FSEXT_TEST_RUN(
	 "libfsext_file_entry_free",
	 fsext_test_file_entry_free );

#if defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT )

	/* TODO: add tests for libfsext_file_entry_is_empty */

	/* TODO: add tests for libfsext_file_entry_get_access_time */

	/* TODO: add tests for libfsext_file_entry_get_inode_change_time */

	/* TODO: add tests for libfsext_file_entry_get_modification_time */

	/* TODO: add tests for libfsext_file_entry_get_deletion_time */

	/* TODO: add tests for libfsext_file_entry_get_file_mode */

	/* TODO: add tests for libfsext_file_entry_get_user_identifier */

	/* TODO: add tests for libfsext_file_entry_get_group_identifier */

	/* TODO: add tests for libfsext_file_entry_get_utf8_name_size */

	/* TODO: add tests for libfsext_file_entry_get_utf8_name */

	/* TODO: add tests for libfsext_file_entry_get_utf16_name_size */

	/* TODO: add tests for libfsext_file_entry_get_utf16_name */

	/* TODO: add tests for libfsext_file_entry_get_number_of_sub_file_entries */

	/* TODO: add tests for libfsext_file_entry_get_sub_file_entry_by_index */

	/* TODO: add tests for libfsext_file_entry_get_sub_file_entry_by_utf8_name */

	/* TODO: add tests for libfsext_file_entry_get_sub_file_entry_by_utf16_name */

	/* TODO: add tests for libfsext_file_entry_read_buffer */

	/* TODO: add tests for libfsext_file_entry_read_buffer_at_offset */

	/* TODO: add tests for libfsext_file_entry_seek_offset */

	/* TODO: add tests for libfsext_file_entry_get_offset */

	/* TODO: add tests for libfsext_file_entry_get_size */

	/* TODO: add tests for libfsext_file_entry_get_number_of_extents */

	/* TODO: add tests for libfsext_file_entry_get_extent_by_index */

#endif /* defined( __GNUC__ ) && !defined( LIBFSEXT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

