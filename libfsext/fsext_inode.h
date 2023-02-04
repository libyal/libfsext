/*
 * Inode of an Extended File System
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

#if !defined( _FSEXT_INODE_H )
#define _FSEXT_INODE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_inode_ext2 fsext_inode_ext2_t;

struct fsext_inode_ext2
{
	/* File mode
	 * Consists of 2 bytes
	 */
	uint8_t file_mode[ 2 ];

	/* Owner identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier[ 2 ];

	/* Data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Access time
	 * Consists of 4 bytes
	 */
	uint8_t access_time[ 4 ];

	/* Inode change time
	 * Consists of 4 bytes
	 */
	uint8_t inode_change_time[ 4 ];

	/* Modification time
	 * Consists of 4 bytes
	 */
	uint8_t modification_time[ 4 ];

	/* Deletion time
	 * Consists of 4 bytes
	 */
	uint8_t deletion_time[ 4 ];

	/* Group identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier[ 2 ];

	/* Number of (hard) links
	 * Consists of 2 bytes
	 */
	uint8_t number_of_links[ 2 ];

	/* Number of (data) blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Data reference
	 * Consists of 60 bytes
	 * Contains 12 direct block numbers, 1 indirect block number, 1 double indirect block number and 1 triple indirect block number
	 */
	uint8_t data_reference[ 60 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File ACL (or extended attributes) block number
	 * Consists of 4 bytes
	 */
	uint8_t file_acl_block_number[ 4 ];

	/* Directory ACL
	 * Consists of 4 bytes
	 */
	uint8_t directory_acl[ 4 ];

	/* Fragment block address
	 * Consists of 4 bytes
	 */
	uint8_t fragment_block_address[ 4 ];

	/* Fragment block index
	 * Consists of 1 byte
	 */
	uint8_t fragment_block_index;

	/* Fragment size
	 * Consists of 1 byte
	 */
	uint8_t fragment_size;

	/* Padding1
	 * Consists of 2 bytes
	 */
	uint8_t padding1[ 2 ];

	/* Owner identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier_upper[ 2 ];

	/* Group identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier_upper[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

typedef struct fsext_inode_ext3 fsext_inode_ext3_t;

struct fsext_inode_ext3
{
	/* File mode
	 * Consists of 2 bytes
	 */
	uint8_t file_mode[ 2 ];

	/* Owner identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier[ 2 ];

	/* Data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Access time
	 * Consists of 4 bytes
	 */
	uint8_t access_time[ 4 ];

	/* Inode change time
	 * Consists of 4 bytes
	 */
	uint8_t inode_change_time[ 4 ];

	/* Modification time
	 * Consists of 4 bytes
	 */
	uint8_t modification_time[ 4 ];

	/* Deletion time
	 * Consists of 4 bytes
	 */
	uint8_t deletion_time[ 4 ];

	/* Group identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier[ 2 ];

	/* Links count
	 * Consists of 2 bytes
	 */
	uint8_t links_count[ 2 ];

	/* Number of (data) blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Data reference
	 * Consists of 60 bytes
	 * Contains 12 direct block numbers, 1 indirect block number, 1 double indirect block number and 1 triple indirect block number
	 */
	uint8_t data_reference[ 60 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File ACL (or extended attributes) block number
	 * Consists of 4 bytes
	 */
	uint8_t file_acl_block_number[ 4 ];

	/* Directory ACL
	 * Consists of 4 bytes
	 */
	uint8_t directory_acl[ 4 ];

	/* Fragment block address
	 * Consists of 4 bytes
	 */
	uint8_t fragment_block_address[ 4 ];

	/* Fragment block index
	 * Consists of 1 byte
	 */
	uint8_t fragment_block_index;

	/* Fragment size
	 * Consists of 1 byte
	 */
	uint8_t fragment_size;

	/* Padding1
	 * Consists of 2 bytes
	 */
	uint8_t padding1[ 2 ];

	/* Owner identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier_upper[ 2 ];

	/* Group identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier_upper[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Extended inode size
	 * Consists of 2 bytes
	 */
	uint8_t extended_inode_size[ 2 ];

	/* Padding2
	 * Consists of 2 bytes
	 */
	uint8_t padding2[ 2 ];
};

typedef struct fsext_inode_ext4 fsext_inode_ext4_t;

struct fsext_inode_ext4
{
	/* File mode
	 * Consists of 2 bytes
	 */
	uint8_t file_mode[ 2 ];

	/* Owner identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier[ 2 ];

	/* Data size (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t data_size_lower[ 4 ];

	/* Access time
	 * Consists of 4 bytes
	 */
	uint8_t access_time[ 4 ];

	/* Inode change time
	 * Consists of 4 bytes
	 */
	uint8_t inode_change_time[ 4 ];

	/* Modification time
	 * Consists of 4 bytes
	 */
	uint8_t modification_time[ 4 ];

	/* Deletion time
	 * Consists of 4 bytes
	 */
	uint8_t deletion_time[ 4 ];

	/* Group identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier[ 2 ];

	/* Links count
	 * Consists of 2 bytes
	 */
	uint8_t links_count[ 2 ];

	/* Number of (data) blocks (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks_lower[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (version (lower 32_bit))
	 * Consists of 4 bytes
	 */
	uint8_t version_lower[ 4 ];

	/* Data reference
	 * Consists of 60 bytes
	 * Contains either
	 * 12 direct block numbers, 1 indirect block number, 1 double indirect block number and 1 triple indirect block number
	 * or data extents
	 * or data
	 */
	uint8_t data_reference[ 60 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File ACL (or extended attributes) block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t file_acl_block_number_lower[ 4 ];

	/* Data size (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t data_size_upper[ 4 ];

	/* Fragment block address
	 * Consists of 4 bytes
	 */
	uint8_t fragment_block_address[ 4 ];

	/* Number of (data) blocks (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_blocks_upper[ 2 ];

	/* File ACL (or extended attributes) block number (upper 16-bit)
	 * Consists of 4 bytes
	 */
	uint8_t file_acl_block_number_upper[ 2 ];

	/* Owner identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t owner_identifier_upper[ 2 ];

	/* Group identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier_upper[ 2 ];

	/* Checksum (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t checksum_lower[ 2 ];

	/* Unknown (reserved)
	 * Consists of 2 bytes
	 */
	uint8_t unknown2[ 2 ];

	/* Extended inode size
	 * Consists of 2 bytes
	 */
	uint8_t extended_inode_size[ 2 ];

	/* Checksum (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t checksum_upper[ 2 ];

	/* Inode change time extra precision
	 * Consists of 4 bytes
	 */
	uint8_t inode_change_time_extra[ 4 ];

	/* Modification time extra precision
	 * Consists of 4 bytes
	 */
	uint8_t modification_time_extra[ 4 ];

	/* Access time extra precision
	 * Consists of 4 bytes
	 */
	uint8_t access_time_extra[ 4 ];

	/* Creation time
	 * Consists of 4 bytes
	 */
	uint8_t creation_time[ 4 ];

	/* Creation time extra precision
	 * Consists of 4 bytes
	 */
	uint8_t creation_time_extra[ 4 ];

	/* Unknown (version (upper 32_bit))
	 * Consists of 4 bytes
	 */
	uint8_t version_upper[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_INODE_H ) */

