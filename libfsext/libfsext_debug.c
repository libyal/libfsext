/*
 * Debug functions
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfsext_debug.h"
#include "libfsext_definitions.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcnotify.h"
#include "libfsext_libfdatetime.h"
#include "libfsext_libfguid.h"
#include "libfsext_libuna.h"

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
		 "\tHas metadata block groups (EXT2_FEATURE_INCOMPAT_META_BG)\n" );
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
		 "\tHas flexible block groups (EXT4_FEATURE_INCOMPAT_FLEX_BG)\n" );
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
	if( ( incompatible_features_flags & 0x00020000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(EXT4_FEATURE_INCOMPAT_CASEFOLD)\n" );
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
	if( ( read_only_compatible_features_flags & 0x00000080UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(RO_COMPAT_HAS_SNAPSHOT)\n" );
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
	if( ( read_only_compatible_features_flags & 0x00000400UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(RO_COMPAT_METADATA_CSUM)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00000800UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(RO_COMPAT_REPLICA)\n" );
	}

	if( ( read_only_compatible_features_flags & 0x00001000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(RO_COMPAT_READONLY)\n" );
	}
	if( ( read_only_compatible_features_flags & 0x00002000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t(RO_COMPAT_PROJECT)\n" );
	}
}

/* Prints the inode flags
 */
void libfsext_debug_print_inode_flags(
      uint32_t inode_flags )
{
	if( ( inode_flags & 0x00000001UL ) != 0 )
	{
		libcnotify_printf(
		 "\tSecure deletion (EXT2_SECRM_FL)\n" );
	}
	if( ( inode_flags & 0x00000002UL ) != 0 )
	{
		libcnotify_printf(
		 "\tUndelete (EXT2_UNRM_FL)\n" );
	}
	if( ( inode_flags & 0x00000004UL ) != 0 )
	{
		libcnotify_printf(
		 "\tCompress file (EXT2_COMPR_FL)\n" );
	}
	if( ( inode_flags & 0x00000008UL ) != 0 )
	{
		libcnotify_printf(
		 "\tSynchronous updates (EXT2_SYNC_FL)\n" );
	}
	if( ( inode_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\tImmutable file (EXT2_IMMUTABLE_FL)\n" );
	}
	if( ( inode_flags & 0x00000020UL ) != 0 )
	{
		libcnotify_printf(
		 "\tWrites to file may only append (EXT2_APPEND_FL)\n" );
	}
	if( ( inode_flags & 0x00000040UL ) != 0 )
	{
		libcnotify_printf(
		 "\tDo not dump file (EXT2_NODUMP_FL)\n" );
	}
	if( ( inode_flags & 0x00000080UL ) != 0 )
	{
		libcnotify_printf(
		 "\tDo not update atime (EXT2_NOATIME_FL)\n" );
	}
	if( ( inode_flags & 0x00000100UL ) != 0 )
	{
		libcnotify_printf(
		 "\tReserved for compression usage (EXT2_DIRTY_FL)\n" );
	}
	if( ( inode_flags & 0x00000200UL ) != 0 )
	{
		libcnotify_printf(
		 "\tOne or more compressed clusters (EXT2_COMPRBLK_FL)\n" );
	}
	if( ( inode_flags & 0x00000400UL ) != 0 )
	{
		libcnotify_printf(
		 "\tDo no compress (EXT2_NOCOMPR_FL)\n" );
	}
/* TODO add ext2 and ext3 support */
	if( ( inode_flags & 0x00000800UL ) != 0 )
	{
		libcnotify_printf(
		 "\tEncrypted file (EXT4_ENCRYPT_FL)\n" );
	}
/* TODO add ext2 b-tree support */
	if( ( inode_flags & 0x00001000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tHash-indexed directory (EXT2_INDEX_FL)\n" );
	}
	if( ( inode_flags & 0x00002000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tAFS directory (EXT2_IMAGIC_FL)\n" );
	}
	if( ( inode_flags & 0x00004000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tFile data should be journaled (EXT2_JOURNAL_DATA_FL)\n" );
	}
	if( ( inode_flags & 0x00008000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tFile tail should not be merged (EXT2_NOTAIL_FL)\n" );
	}
	if( ( inode_flags & 0x00010000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tDirsync behaviour (EXT2_DIRSYNC_FL)\n" );
	}
	if( ( inode_flags & 0x00020000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tTop of directory hierarchy (EXT2_TOPDIR_FL)\n" );
	}
	if( ( inode_flags & 0x00040000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tSet to each huge file (EXT4_HUGE_FILE_FL)\n" );
	}
	if( ( inode_flags & 0x00080000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tInode uses extents (EXT4_EXTENTS_FL)\n" );
	}
	if( ( inode_flags & 0x00200000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tInode used for large extended attribute (EXT4_EA_INODE_FL)\n" );
	}
	if( ( inode_flags & 0x00400000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tBlocks allocated beyond end-of-file (EXT4_EOFBLOCKS_FL)\n" );
	}
	if( ( inode_flags & 0x10000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tInode has inline data (EXT4_INLINE_DATA_FL)\n" );
	}
	if( ( inode_flags & 0x20000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tCreate with parents projid (EXT4_PROJINHERIT_FL)\n" );
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

/* Prints an UTF-8 string value
 * Returns 1 if successful or -1 on error
 */
int libfsext_debug_print_utf8_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "libfsext_debug_print_utf8_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s: \n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf8_stream(
		  byte_stream,
		  byte_stream_size,
		  &string_size,
		  error );
#else
	result = libuna_utf8_string_size_from_utf8_stream(
		  byte_stream,
		  byte_stream_size,
		  &string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	string = system_string_allocate(
	          string_size );

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_copy_from_utf8_stream(
		  (libuna_utf16_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  error );
#else
	result = libuna_utf8_string_copy_from_utf8_stream(
		  (libuna_utf8_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %" PRIs_SYSTEM "\n",
	 function_name,
	 value_name,
	 string );

	memory_free(
	 string );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
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

