/*
 * Inode functions
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

#if !defined( _LIBFSEXT_INODE_H )
#define _LIBFSEXT_INODE_H

#include <common.h>
#include <types.h>

#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_inode libfsext_inode_t;

struct libfsext_inode
{
	/* File mode
	 */
	uint16_t file_mode;

	/* User identifier
	 */
	uint16_t user_identifier;

	/* Data size
	 */
	uint32_t data_size;

	/* Last access time
	 */
	uint32_t last_access_time;

	/* Last inode change time
	 */
	uint32_t last_inode_change_time;

	/* Last modification time
	 */
	uint32_t last_modification_time;

	/* Deletion time
	 */
	uint32_t deletion_time;

	/* Group identifier
	 */
	uint16_t group_identifier;

	/* Link count
	 */
	uint16_t link_count;

	/* Sector count
	 */
	uint32_t sector_count;

	/* Flags
	 */
	uint32_t flags;

	/* Unknown (reserved)
	 */
	uint32_t unknown1;

	/* Direct block numbers
	 */
	/* TODO: implement */

	/* Indirect block number
	 */
	uint32_t indirect_block_number;

	/* Double indirect block number
	 */
	uint32_t double_indirect_block_number;

	/* Triple indirect block number
	 */
	uint32_t triple_indirect_block_number;

	/* Nfs generation number
	 */
	uint32_t nfs_generation_number;

	/* File acl
	 */
	uint32_t file_acl;

	/* Directory acl
	 */
	uint32_t directory_acl;

	/* Fragment block address
	 */
	uint32_t fragment_block_address;

	/* Fragment block index
	 */
	uint8_t fragment_block_index;

	/* Fragment size
	 */
	uint8_t fragment_size;

	/* Padding1
	 */
	uint16_t padding1;

	/* User identifier 32bit
	 */
	uint16_t user_identifier_32bit;

	/* Group identifier 32bit
	 */
	uint16_t group_identifier_32bit;

	/* Unknown (reserved)
	 */
	uint32_t unknown2;
};

int libfsext_inode_initialize(
     libfsext_inode_t **inode,
     libcerror_error_t **error );

int libfsext_inode_free(
     libfsext_inode_t **inode,
     libcerror_error_t **error );

int libfsext_inode_read_data(
     libfsext_inode_t *inode,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_inode_read_file_io_handle(
     libfsext_inode_t *inode,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_INODE_H ) */

