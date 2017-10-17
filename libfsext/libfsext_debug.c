/*
 * Debug functions
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
#include <memory.h>
#include <types.h>

#include "libfsext_debug.h"
#include "libfsext_definitions.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdatetime.h"
#include "libfsext_libfguid.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the file system state flags
 */
void libfsext_debug_print_file_system_state_flags(
      uint16_t file_system_state_flags )
{
	if( ( file_system_state_flags & 0x0001 ) != 0 )
	{
		libcnotify_printf(
		 "\tIs clean\n" );
	}
	if( ( file_system_state_flags & 0x0002 ) != 0 )
	{
		libcnotify_printf(
		 "\tHas errors\n" );
	}
	if( ( file_system_state_flags & 0x0004 ) != 0 )
	{
		libcnotify_printf(
		 "\tRecovering orphan inodes\n" );
	}
}

/* Prints the compatible features flags
 */
void libfsext_debug_print_compatible_features_flags(
      uint32_t compatible_features_flags )
{
	if( ( compatible_features_flags & 0x00000001UL ) != 0 )
	{
		libcnotify_printf(
		 "\tPre-allocate directory blocks (EXT2_COMPAT_PREALLOC)\n" );
	}
	if( ( compatible_features_flags & 0x00000002UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas AFS server inodes (EXT2_FEATURE_COMPAT_IMAGIC_INODES)\n" );
	}
	if( ( compatible_features_flags & 0x00000004UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas journal (EXT3_FEATURE_COMPAT_HAS_JOURNAL)\n" );
	}
	if( ( compatible_features_flags & 0x00000008UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHave extended inode attributes (EXT2_FEATURE_COMPAT_EXT_ATTR)\n" );
	}
	if( ( compatible_features_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\tResizable volume (EXT2_FEATURE_COMPAT_RESIZE_INO)\n" );
	}
	if( ( compatible_features_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\tUse directory hash index (EXT2_FEATURE_COMPAT_DIR_INDEX)\n" );
	}

	if( ( compatible_features_flags & 0x00000200UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_COMPAT_SPARSE_SUPER2)\n" );
	}
}

/* Prints the incompatible features flags
 */
void libfsext_debug_print_incompatible_features_flags(
      uint32_t incompatible_features_flags )
{
	if( ( incompatible_features_flags & 0x00000001UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas compression (EXT2_FEATURE_INCOMPAT_COMPRESSION)\n" );
	}
	if( ( incompatible_features_flags & 0x00000002UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas directory type (EXT2_FEATURE_INCOMPAT_FILETYPE)\n" );
	}
	if( ( incompatible_features_flags & 0x00000004UL ) != 0 )
	{
		libcnotify_printf(
		 "\tNeeds recovery (EXT3_FEATURE_INCOMPAT_RECOVER)\n" );
	}
	if( ( incompatible_features_flags & 0x00000008UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas journal device (EXT3_FEATURE_INCOMPAT_JOURNAL_DEV)\n" );
	}
	if( ( incompatible_features_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas metadata block group (EXT2_FEATURE_INCOMPAT_META_BG)\n" );
	}

	if( ( incompatible_features_flags & 0x00000040UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas extents (EXT4_FEATURE_INCOMPAT_EXTENTS)\n" );
	}
	if( ( incompatible_features_flags & 0x00000080UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas 64-bit support (EXT4_FEATURE_INCOMPAT_64BIT)\n" );
	}
	if( ( incompatible_features_flags & 0x00000100UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_MMP)\n" );
	}
	if( ( incompatible_features_flags & 0x00000200UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_FLEX_BG)\n" );
	}
	if( ( incompatible_features_flags & 0x00000400UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_EA_INODE)\n" );
	}

	if( ( incompatible_features_flags & 0x00001000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_DIRDATA)\n" );
	}
	if( ( incompatible_features_flags & 0x00002000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_BG_USE_META_CSUM)\n" );
	}
	if( ( incompatible_features_flags & 0x00004000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_LARGEDIR)\n" );
	}
	if( ( incompatible_features_flags & 0x00008000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_INLINE_DATA)\n" );
	}
	if( ( incompatible_features_flags & 0x00010000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_ENCRYPT)\n" );
	}
}

/* Prints the read-only compatible features flags
 */
void libfsext_debug_print_read_only_compatible_features_flags(
      uint32_t read_only_compatible_features_flags )
{
	if( ( read_only_compatible_features_flags & 0x00000001UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHas sparse superblocks and group descriptor tables (EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000002UL ) != 0 )
	{
		libcnotify_printf(
		 "\tContains large files (EXT2_FEATURE_RO_COMPAT_LARGE_FILE)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000004UL ) != 0 )
	{
		libcnotify_printf(
		 "\tUse directory B-tree (EXT2_FEATURE_RO_COMPAT_BTREE_DIR)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000008UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_HUGE_FILE)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_GDT_CSUM)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000020UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_DIR_NLINK)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000040UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00000100UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_QUOTA)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000200UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_RO_COMPAT_BIGALLOC)\n" );
	}
}

/* Prints the file mode
 */
void libfsext_debug_print_file_mode(
      uint16_t file_mode )
{
	if( ( file_mode & 0x0007 ) != 0 )
	{
		libcnotify_printf(
		 "\tAccess other: " );

		if( ( file_mode & 0x0004 ) != 0 )
		{
			libcnotify_printf(
			 "R" );
		}
		if( ( file_mode & 0x0002 ) != 0 )
		{
			libcnotify_printf(
			 "W" );
		}
		if( ( file_mode & 0x0001 ) != 0 )
		{
			libcnotify_printf(
			 "X" );
		}
		libcnotify_printf(
		 "\n" );
	}
	if( ( file_mode & 0x0038 ) != 0 )
	{
		libcnotify_printf(
		 "\tAccess group: " );

		if( ( file_mode & 0x0020 ) != 0 )
		{
			libcnotify_printf(
			 "R" );
		}
		if( ( file_mode & 0x0010 ) != 0 )
		{
			libcnotify_printf(
			 "W" );
		}
		if( ( file_mode & 0x0008 ) != 0 )
		{
			libcnotify_printf(
			 "X" );
		}
		libcnotify_printf(
		 "\n" );
	}
	if( ( file_mode & 0x01c0 ) != 0 )
	{
		libcnotify_printf(
		 "\tAccess user: " );

		if( ( file_mode & 0x0100 ) != 0 )
		{
			libcnotify_printf(
			 "R" );
		}
		if( ( file_mode & 0x0080 ) != 0 )
		{
			libcnotify_printf(
			 "W" );
		}
		if( ( file_mode & 0x0040 ) != 0 )
		{
			libcnotify_printf(
			 "X" );
		}
		libcnotify_printf(
		 "\n" );
	}
	if( ( file_mode & 0x0200 ) != 0 )
	{
		libcnotify_printf(
		 "\tSticky bit (S_ISTXT)" );
	}
	if( ( file_mode & 0x0400 ) != 0 )
	{
		libcnotify_printf(
		 "\tSet group identifer (GID) on execution (S_ISGID)\n" );
	}
	if( ( file_mode & 0x0800 ) != 0 )
	{
		libcnotify_printf(
		 "\tSet user identifer (UID) on execution (S_ISUID)\n" );
	}
	switch( file_mode & 0xf000 )
	{
		case 0x1000:
			libcnotify_printf(
			 "\tNamed pipe (FIFO) (S_IFIFO)\n" );
			break;

		case 0x2000:
			libcnotify_printf(
			 "\tCharacter device (S_IFCHR)\n" );
			break;

		case 0x4000:
			libcnotify_printf(
			 "\tDirectory (S_IFDIR)\n" );
			break;

		case 0x6000:
			libcnotify_printf(
			 "\tBlock device (S_IFBLK)\n" );
			break;

		case 0x8000:
			libcnotify_printf(
			 "\tRegular file (S_IFREG)\n" );
			break;

		case 0xa000:
			libcnotify_printf(
			 "\tSymbolic link (S_IFLNK)\n" );
			break;

		case 0xc000:
			libcnotify_printf(
			 "\tSocket (S_IFSOCK)\n" );
			break;

		default:
			break;
	}
	libcnotify_printf(
	 "\n" );
}

/* Prints the error handling status
 */
const char *libfsext_debug_print_error_handling_status(
             uint16_t error_handling_status )
{
	switch( error_handling_status )
	{
		case 1:
			return( "Continue" );

		case 2:
			return( "Remount as read-only" );

		case 3:
			return( "Panic" );
	}
	return( "Unknown" );
}

/* Prints the creator operating system
 */
const char *libfsext_debug_print_creator_operating_system(
             uint32_t creator_operating_system )
{
	switch( creator_operating_system )
	{
		case 0:
			return( "Linux" );

		case 1:
			return( "GNU herd" );

		case 2:
			return( "Masix" );

		case 3:
			return( "FreeBSD" );

		case 4:
			return( "Lites" );
	}
	return( "Unknown" );
}

/* Prints the file type
 */
const char *libfsext_debug_print_file_type(
             uint16_t file_type )
{
	switch( file_type )
	{
		case 0:
			return( "Unknown (EXT2_FT_UNKNOWN)" );

		case 1:
			return( "Regular file (EXT2_FT_REG_FILE)" );

		case 2:
			return( "Directory (EXT2_FT_DIR)" );

		case 3:
			return( "Character device (EXT2_FT_CHRDEV)" );

		case 4:
			return( "Block device (EXT2_FT_BLKDEV)" );

		case 5:
			return( "FIFO queue (EXT2_FT_FIFO)" );

		case 6:
			return( "Socket (EXT2_FT_SOCK)" );

		case 7:
			return( "Symbolic link (EXT2_FT_SYMLINK)" );
	}
	return( "Unknown" );
}

/* Prints a POSIX value
 * Returns 1 if successful or -1 on error
 */
int libfsext_debug_print_posix_time_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint8_t value_type,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	char date_time_string[ 32 ];

	libfdatetime_posix_time_t *posix_time = NULL;
	static char *function                 = "libfsext_debug_print_posix_time_value";

	if( libfdatetime_posix_time_initialize(
	     &posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create posix time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_posix_time_copy_from_byte_stream(
	     posix_time,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to posix time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_posix_time_copy_to_utf8_string(
	     posix_time,
	     (uint8_t *) date_time_string,
	     32,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy posix_time to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s UTC\n",
	 function_name,
	 value_name,
	 date_time_string );

	if( libfdatetime_posix_time_free(
	     &posix_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free posix time.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( posix_time != NULL )
	{
		libfdatetime_posix_time_free(
		 &posix_time,
		 NULL );
	}
	return( -1 );
}

/* Prints a GUID/UUID value
 * Returns 1 if successful or -1 on error
 */
int libfsext_debug_print_guid_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid = NULL;
	static char *function       = "libfsext_debug_print_guid_value";

	if( libfguid_identifier_initialize(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create GUID.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to GUID.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_to_utf8_string(
	     guid,
	     (uint8_t *) guid_string,
	     48,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy GUID to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
	 value_name,
	 guid_string );

	if( libfguid_identifier_free(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free GUID.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libfsext_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libfsext_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

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
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + (off64_t) size,
		 offset + (off64_t) size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

