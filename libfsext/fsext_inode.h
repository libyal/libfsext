/*
 * Inode of a Extended File System
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

	/* User identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier[ 2 ];

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

	/* Blocks count
	 * Consists of 4 bytes
	 */
	uint8_t blocks_count[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Direct block numbers
	 * Consists of 48 bytes
	 */
	uint8_t direct_block_numbers[ 48 ];

	/* Indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t indirect_block_number[ 4 ];

	/* Double indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t double_indirect_block_number[ 4 ];

	/* Triple indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t triple_indirect_block_number[ 4 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File acl
	 * Consists of 4 bytes
	 */
	uint8_t file_acl[ 4 ];

	/* Directory acl
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

	/* User identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier_upper[ 2 ];

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

	/* User identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier[ 2 ];

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

	/* Blocks count
	 * Consists of 4 bytes
	 */
	uint8_t blocks_count[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Direct block numbers
	 * Consists of 48 bytes
	 */
	uint8_t direct_block_numbers[ 48 ];

	/* Indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t indirect_block_number[ 4 ];

	/* Double indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t double_indirect_block_number[ 4 ];

	/* Triple indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t triple_indirect_block_number[ 4 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File acl
	 * Consists of 4 bytes
	 */
	uint8_t file_acl[ 4 ];

	/* Directory acl
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

	/* User identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier_upper[ 2 ];

	/* Group identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier_upper[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown3[ 2 ];

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

	/* User identifier (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier[ 2 ];

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

	/* Blocks count (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t blocks_count_lower[ 4 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown (version (lower 32_bit))
	 * Consists of 4 bytes
	 */
	uint8_t version_lower[ 4 ];

	/* Direct block numbers
	 * Consists of 48 bytes
	 */
	uint8_t direct_block_numbers[ 48 ];

	/* Indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t indirect_block_number[ 4 ];

	/* Double indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t double_indirect_block_number[ 4 ];

	/* Triple indirect block number
	 * Consists of 4 bytes
	 */
	uint8_t triple_indirect_block_number[ 4 ];

	/* NFS generation number
	 * Consists of 4 bytes
	 */
	uint8_t nfs_generation_number[ 4 ];

	/* File acl (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t file_acl_lower[ 4 ];

	/* Data size (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t data_size_upper[ 4 ];

	/* Fragment block address
	 * Consists of 4 bytes
	 */
	uint8_t fragment_block_address[ 4 ];

	/* Blocks count (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t blocks_count_upper[ 2 ];

	/* File acl (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t file_acl_upper[ 2 ];

	/* User identifier (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier_upper[ 2 ];

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

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown3[ 2 ];

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
