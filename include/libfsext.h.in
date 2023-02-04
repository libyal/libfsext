/*
 * Library to access the Extended File System (ext) format
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

#if !defined( _LIBFSEXT_H )
#define _LIBFSEXT_H

#include <libfsext/codepage.h>
#include <libfsext/definitions.h>
#include <libfsext/error.h>
#include <libfsext/extern.h>
#include <libfsext/features.h>
#include <libfsext/types.h>

#include <stdio.h>

#if defined( LIBFSEXT_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBFSEXT_EXTERN \
const char *libfsext_get_version(
             void );

/* Returns the access flags for reading
 */
LIBFSEXT_EXTERN \
int libfsext_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_get_codepage(
     int *codepage,
     libfsext_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_set_codepage(
     int codepage,
     libfsext_error_t **error );

/* Determines if a file contains an ext volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_check_volume_signature(
     const char *filename,
     libfsext_error_t **error );

#if defined( LIBFSEXT_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains an ext volume signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_check_volume_signature_wide(
     const wchar_t *filename,
     libfsext_error_t **error );

#endif /* defined( LIBFSEXT_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFSEXT_HAVE_BFIO )

/* Determines if a file contains an ext volume signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libfsext_error_t **error );

#endif /* defined( LIBFSEXT_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBFSEXT_EXTERN \
void libfsext_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_notify_set_stream(
     FILE *stream,
     libfsext_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_notify_stream_open(
     const char *filename,
     libfsext_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_notify_stream_close(
     libfsext_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBFSEXT_EXTERN \
void libfsext_error_free(
      libfsext_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_error_fprint(
     libfsext_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_error_sprint(
     libfsext_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_error_backtrace_fprint(
     libfsext_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_error_backtrace_sprint(
     libfsext_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_initialize(
     libfsext_volume_t **volume,
     libfsext_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_free(
     libfsext_volume_t **volume,
     libfsext_error_t **error );

/* Signals the volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_signal_abort(
     libfsext_volume_t *volume,
     libfsext_error_t **error );

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_open(
     libfsext_volume_t *volume,
     const char *filename,
     int access_flags,
     libfsext_error_t **error );

#if defined( LIBFSEXT_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_open_wide(
     libfsext_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libfsext_error_t **error );

#endif /* defined( LIBFSEXT_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBFSEXT_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsext_error_t **error );

#endif /* defined( LIBFSEXT_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_close(
     libfsext_volume_t *volume,
     libfsext_error_t **error );

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_format_version(
     libfsext_volume_t *volume,
     uint8_t *format_version,
     libfsext_error_t **error );

/* Retrieves the feature flags
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_features_flags(
     libfsext_volume_t *volume,
     uint32_t *compatible_features_flags,
     uint32_t *incompatible_features_flags,
     uint32_t *read_only_compatible_features_flags,
     libfsext_error_t **error );

/* Retrieves the identifier
 * The identifier is an UUID stored in big-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_identifier(
     libfsext_volume_t *volume,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-8 encoded label
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label_size(
     libfsext_volume_t *volume,
     size_t *utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-8 encoded label
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_label(
     libfsext_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-16 encoded label
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label_size(
     libfsext_volume_t *volume,
     size_t *utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-16 encoded label
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_label(
     libfsext_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-8 encoded last mount path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_last_mount_path_size(
     libfsext_volume_t *volume,
     size_t *utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-8 encoded last mount path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf8_last_mount_path(
     libfsext_volume_t *volume,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-16 encoded last mount path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_last_mount_path_size(
     libfsext_volume_t *volume,
     size_t *utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-16 encoded last mount path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_utf16_last_mount_path(
     libfsext_volume_t *volume,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the last mount time
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_last_mount_time(
     libfsext_volume_t *volume,
     int32_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the last written time
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_last_written_time(
     libfsext_volume_t *volume,
     int32_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the root directory file entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_root_directory(
     libfsext_volume_t *volume,
     libfsext_file_entry_t **file_entry,
     libfsext_error_t **error );

/* Retrieves the number of file entries (inodes)
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_number_of_file_entries(
     libfsext_volume_t *volume,
     uint32_t *number_of_file_entries,
     libfsext_error_t **error );

/* Retrieves the file entry of a specific inode number
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_inode(
     libfsext_volume_t *volume,
     uint32_t inode_number,
     libfsext_file_entry_t **file_entry,
     libfsext_error_t **error );

/* Retrieves the file entry for an UTF-8 encoded path
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_utf8_path(
     libfsext_volume_t *volume,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **file_entry,
     libfsext_error_t **error );

/* Retrieves the file entry for an UTF-16 encoded path
 * Returns 1 if successful, 0 if no such file entry or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_volume_get_file_entry_by_utf16_path(
     libfsext_volume_t *volume,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **file_entry,
     libfsext_error_t **error );

/* -------------------------------------------------------------------------
 * File entry functions
 * ------------------------------------------------------------------------- */

/* Frees a file entry
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_free(
     libfsext_file_entry_t **file_entry,
     libfsext_error_t **error );

/* Determines if the file entry is emtpy
 * Returns 1 if empty, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_is_empty(
     libfsext_file_entry_t *file_entry,
     libfsext_error_t **error );

/* Retrieves the inode number
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_inode_number(
     libfsext_file_entry_t *file_entry,
     uint32_t *inode_number,
     libfsext_error_t **error );

/* Retrieves the access date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_access_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the creation date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode and only supported by ext4
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_creation_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the inode change date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_inode_change_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the modification date and time
 * The timestamp is a signed 64-bit POSIX date and time value in number of nano seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_modification_time(
     libfsext_file_entry_t *file_entry,
     int64_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the deletion date and time
 * The timestamp is a signed 32-bit POSIX date and time value in number of seconds
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_deletion_time(
     libfsext_file_entry_t *file_entry,
     int32_t *posix_time,
     libfsext_error_t **error );

/* Retrieves the file mode
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_file_mode(
     libfsext_file_entry_t *file_entry,
     uint16_t *file_mode,
     libfsext_error_t **error );

/* Retrieves the number of (hard) links
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_links(
     libfsext_file_entry_t *file_entry,
     uint16_t *number_of_links,
     libfsext_error_t **error );

/* Retrieves the owner identifier
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_owner_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *owner_identifier,
     libfsext_error_t **error );

/* Retrieves the group identifier
 * This value is retrieved from the inode
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_group_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *group_identifier,
     libfsext_error_t **error );

/* Retrieves the device identifier
 * This value is retrieved from the inode
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_device_identifier(
     libfsext_file_entry_t *file_entry,
     uint32_t *device_identifier,
     libfsext_error_t **error );

/* Retrieves the device number
 * This value is retrieved from the inode
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_device_number(
     libfsext_file_entry_t *file_entry,
     uint8_t *major_device_number,
     uint8_t *minor_device_number,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_name(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_name_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * This value is retrieved from the directory entry
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_name(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-8 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-8 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf8_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-16 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_symbolic_link_target_size(
     libfsext_file_entry_t *file_entry,
     size_t *utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-16 encoded symbolic link target
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_utf16_symbolic_link_target(
     libfsext_file_entry_t *file_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the number of extended attributes
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_extended_attributes(
     libfsext_file_entry_t *file_entry,
     int *number_of_extended_attributes,
     libfsext_error_t **error );

/* Retrieves the extended attribute for the specific index
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_index(
     libfsext_file_entry_t *file_entry,
     int extended_attribute_index,
     libfsext_extended_attribute_t **extended_attribute,
     libfsext_error_t **error );

/* Determines if there is an extended attribute for an UTF-8 encoded name
 * Returns 1 if available, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_has_extended_attribute_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_error_t **error );

/* Determines if there is an extended attribute for an UTF-16 encoded name
 * Returns 1 if available, 0 if not or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_has_extended_attribute_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_error_t **error );

/* Retrieves the extended attribute for an UTF-8 encoded name
 * Returns 1 if successful, 0 if the file entry does not contain such value or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_extended_attribute_t **extended_attribute,
     libfsext_error_t **error );

/* Retrieves the extended attribute for an UTF-16 encoded name
 * Returns 1 if successful, 0 if the file entry does not contain such value or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extended_attribute_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_extended_attribute_t **extended_attribute,
     libfsext_error_t **error );

/* Retrieves the number of sub file entries
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_sub_file_entries(
     libfsext_file_entry_t *file_entry,
     int *number_of_sub_entries,
     libfsext_error_t **error );

/* Retrieves the sub file entry for the specific index
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_index(
     libfsext_file_entry_t *file_entry,
     int sub_file_entry_index,
     libfsext_file_entry_t **sub_file_entry,
     libfsext_error_t **error );

/* Retrieves the sub file entry for an UTF-8 encoded name
 * Returns 1 if successful, 0 if the file entry does not contain such value or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_utf8_name(
     libfsext_file_entry_t *file_entry,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libfsext_error_t **error );

/* Retrieves the sub file entry for an UTF-16 encoded name
 * Returns 1 if successful, 0 if the file entry does not contain such value or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_sub_file_entry_by_utf16_name(
     libfsext_file_entry_t *file_entry,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfsext_file_entry_t **sub_file_entry,
     libfsext_error_t **error );

/* Reads data at the current offset
 * Returns the number of bytes read or -1 on error
 */
LIBFSEXT_EXTERN \
ssize_t libfsext_file_entry_read_buffer(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         libfsext_error_t **error );

/* Reads data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBFSEXT_EXTERN \
ssize_t libfsext_file_entry_read_buffer_at_offset(
         libfsext_file_entry_t *file_entry,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libfsext_error_t **error );

/* Seeks a certain offset
 * Returns the offset if seek is successful or -1 on error
 */
LIBFSEXT_EXTERN \
off64_t libfsext_file_entry_seek_offset(
         libfsext_file_entry_t *file_entry,
         off64_t offset,
         int whence,
         libfsext_error_t **error );

/* Retrieves the current offset
 * Returns the offset if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_offset(
     libfsext_file_entry_t *file_entry,
     off64_t *offset,
     libfsext_error_t **error );

/* Retrieves the size of the data
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_size(
     libfsext_file_entry_t *file_entry,
     size64_t *size,
     libfsext_error_t **error );

/* Retrieves the number of extents
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_number_of_extents(
     libfsext_file_entry_t *file_entry,
     int *number_of_extents,
     libfsext_error_t **error );

/* Retrieves a specific extent
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_file_entry_get_extent_by_index(
     libfsext_file_entry_t *file_entry,
     int extent_index,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libfsext_error_t **error );

/* -------------------------------------------------------------------------
 * Extended attribute functions
 * ------------------------------------------------------------------------- */

/* Frees an extended attribute
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_free(
     libfsext_extended_attribute_t **extended_attribute,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf8_name_size(
     libfsext_extended_attribute_t *extended_attribute,
     size_t *utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf8_name(
     libfsext_extended_attribute_t *extended_attribute,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfsext_error_t **error );

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf16_name_size(
     libfsext_extended_attribute_t *extended_attribute,
     size_t *utf16_string_size,
     libfsext_error_t **error );

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_utf16_name(
     libfsext_extended_attribute_t *extended_attribute,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfsext_error_t **error );

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBFSEXT_EXTERN \
ssize_t libfsext_extended_attribute_read_buffer(
         libfsext_extended_attribute_t *extended_attribute,
         void *buffer,
         size_t buffer_size,
         libfsext_error_t **error );

/* Reads data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBFSEXT_EXTERN \
ssize_t libfsext_extended_attribute_read_buffer_at_offset(
         libfsext_extended_attribute_t *extended_attribute,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libfsext_error_t **error );

/* Seeks a certain offset
 * Returns the offset if seek is successful or -1 on error
 */
LIBFSEXT_EXTERN \
off64_t libfsext_extended_attribute_seek_offset(
         libfsext_extended_attribute_t *extended_attribute,
         off64_t offset,
         int whence,
         libfsext_error_t **error );

/* Retrieves the current offset
 * Returns the offset if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_offset(
     libfsext_extended_attribute_t *extended_attribute,
     off64_t *offset,
     libfsext_error_t **error );

/* Retrieves the size of the data stream object
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_size(
     libfsext_extended_attribute_t *extended_attribute,
     size64_t *size,
     libfsext_error_t **error );

/* Retrieves the number of extents
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_number_of_extents(
     libfsext_extended_attribute_t *extended_attribute,
     int *number_of_extents,
     libfsext_error_t **error );

/* Retrieves a specific extent
 * Returns 1 if successful or -1 on error
 */
LIBFSEXT_EXTERN \
int libfsext_extended_attribute_get_extent_by_index(
     libfsext_extended_attribute_t *extended_attribute,
     int extent_index,
     off64_t *extent_offset,
     size64_t *extent_size,
     uint32_t *extent_flags,
     libfsext_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_H ) */

