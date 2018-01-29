/*
 * Inode functions
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

#if !defined( _LIBFSEXT_INODE_H )
#define _LIBFSEXT_INODE_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libfcache.h"
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

	/* Direct block numbers
	 */
	uint32_t direct_block_number[ 12 ];

	/* Indirect block number
	 */
	uint32_t indirect_block_number;

	/* Double indirect block number
	 */
	uint32_t double_indirect_block_number;

	/* Triple indirect block number
	 */
	uint32_t triple_indirect_block_number;

	/* Links count
	 */
	uint16_t links_count;

	/* Blocks count
	 */
	uint32_t blocks_count;

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
	uint64_t access_time;

	/* Creation time
	 */
	uint64_t creation_time;

	/* Inode change time
	 */
	uint64_t inode_change_time;

	/* Modification time
	 */
	uint64_t modification_time;

	/* Deletion time
	 */
	uint64_t deletion_time;

	/* Flags
	 */
	uint32_t flags;

	/* User identifier
	 */
	uint32_t user_identifier;

	/* Group identifier
	 */
	uint32_t group_identifier;

	/* File ACL
	 */
	uint32_t file_acl;

	/* Directory ACL
	 */
	uint32_t directory_acl;

	/* NFS generation number
	 */
	uint32_t nfs_generation_number;
};

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

int libfsext_inode_get_access_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_inode_change_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_modification_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_get_deletion_time(
     libfsext_inode_t *inode,
     uint32_t *posix_time,
     libcerror_error_t **error );

int libfsext_inode_read_element_data(
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
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

