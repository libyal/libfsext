/*
 * Inode functions
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

#if !defined( _LIBFSEXT_INODE_H )
#define _LIBFSEXT_INODE_H

#include <common.h>
#include <types.h>

#include "libfsext_extent.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcdata.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_inode libfsext_inode_t;

struct libfsext_inode
{
	/* File mode
	 */
	uint16_t file_mode;

	/* Data size
	 */
	uint64_t data_size;

	/* Number of (hard) links
	 */
	uint16_t number_of_links;

	/* Number of (data) blocks
	 */
	uint32_t number_of_blocks;

	/* Fragment block address
	 */
	uint32_t fragment_block_address;

	/* Fragment block index
	 */
	uint8_t fragment_block_index;

	/* Fragment size
	 */
	uint8_t fragment_size;

	/* Access time
	 */
	int64_t access_time;

	/* Creation time
	 */
	int64_t creation_time;

	/* Inode change time
	 */
	int64_t inode_change_time;

	/* Modification time
	 */
	int64_t modification_time;

	/* Deletion time
	 */
	uint32_t deletion_time;

	/* Flags
	 */
	uint32_t flags;

	/* Owner identifier
	 */
	uint32_t owner_identifier;

	/* Group identifier
	 */
	uint32_t group_identifier;

	/* File ACL (or extended attributes) block number
	 */
	uint32_t file_acl_block_number;

	/* Directory ACL
	 */
	uint32_t directory_acl;

	/* NFS generation number
	 */
	uint32_t nfs_generation_number;

	/* Data reference
	 */
	uint8_t data_reference[ 60 ];

	/* Data extents array
	 */
	libcdata_array_t *data_extents_array;

	/* The extended attributes
	 */
	libcdata_array_t *extended_attributes_array;

	/* Value to indicate the inode has a creation time
	 */
	uint8_t has_creation_time;

	/* Value to indicate the inode is empty
	 */
	uint8_t is_empty;
};

int libfsext_inode_check_for_empty_block(
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_inode_initialize(
     libfsext_inode_t **inode,
     libcerror_error_t **error );

int libfsext_inode_free(
     libfsext_inode_t **inode,
     libcerror_error_t **error );

int libfsext_inode_clone(
     libfsext_inode_t **destination_inode,
     libfsext_inode_t *source_inode,
     libcerror_error_t **error );

int libfsext_inode_read_data(
     libfsext_inode_t *inode,
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_inode_read_data_reference(
     libfsext_inode_t *inode,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libfsext_inode_is_empty(
     libfsext_inode_t *inode,
     libcerror_error_t **error );

int libfsext_inode_get_access_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_creation_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_inode_change_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_modification_time(
     libfsext_inode_t *inode,
     int64_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_deletion_time(
     libfsext_inode_t *inode,
     int32_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_file_mode(
     libfsext_inode_t *inode,
     uint16_t *file_mode,
     libcerror_error_t **error );

int libfsext_inode_get_number_of_links(
     libfsext_inode_t *inode,
     uint16_t *number_of_links,
     libcerror_error_t **error );

int libfsext_inode_get_data_size(
     libfsext_inode_t *inode,
     uint64_t *data_size,
     libcerror_error_t **error );

int libfsext_inode_get_owner_identifier(
     libfsext_inode_t *inode,
     uint32_t *owner_identifier,
     libcerror_error_t **error );

int libfsext_inode_get_group_identifier(
     libfsext_inode_t *inode,
     uint32_t *group_identifier,
     libcerror_error_t **error );

int libfsext_inode_get_file_acl_block_number(
     libfsext_inode_t *inode,
     uint32_t *file_acl_block_number,
     libcerror_error_t **error );

int libfsext_inode_get_device_identifier(
     libfsext_inode_t *inode,
     uint32_t *device_identifier,
     libcerror_error_t **error );

int libfsext_inode_get_device_number(
     libfsext_inode_t *inode,
     uint8_t *major_device_number,
     uint8_t *minor_device_number,
     libcerror_error_t **error );

int libfsext_inode_get_number_of_extents(
     libfsext_inode_t *inode,
     int *number_of_extents,
     libcerror_error_t **error );

int libfsext_inode_get_extent_by_index(
     libfsext_inode_t *inode,
     int extent_index,
     libfsext_extent_t **extent,
     libcerror_error_t **error );

int libfsext_inode_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_INODE_H ) */

