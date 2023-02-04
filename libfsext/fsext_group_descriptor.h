/*
 * Group descriptor of an Extended File System
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

#if !defined( _FSEXT_GROUP_DESCRIPTOR_H )
#define _FSEXT_GROUP_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_group_descriptor_ext2 fsext_group_descriptor_ext2_t;

struct fsext_group_descriptor_ext2
{
	/* Block bitmap block number
	 * Consists of 4 bytes
	 */
	uint8_t block_bitmap_block_number[ 4 ];

	/* Inode bitmap block number
	 * Consists of 4 bytes
	 */
	uint8_t inode_bitmap_block_number[ 4 ];

	/* Inode table block number
	 * Consists of 4 bytes
	 */
	uint8_t inode_table_block_number[ 4 ];

	/* Number of unallocated blocks
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_blocks[ 2 ];

	/* Number of unallocated inodes
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_inodes[ 2 ];

	/* Number of directories
	 * Consists of 2 bytes
	 */
	uint8_t number_of_directories[ 2 ];

	/* Padding
	 * Consists of 2 bytes
	 */
	uint8_t padding1[ 2 ];

	/* Unknown (reserved)
	 * Consists of 12 bytes
	 */
	uint8_t unknown1[ 12 ];
};

typedef struct fsext_group_descriptor_ext4 fsext_group_descriptor_ext4_t;

struct fsext_group_descriptor_ext4
{
	/* Block bitmap block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t block_bitmap_block_number_lower[ 4 ];

	/* Inode bitmap block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t inode_bitmap_block_number_lower[ 4 ];

	/* Inode table block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t inode_table_block_number_lower[ 4 ];

	/* Number of unallocated blocks (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_blocks_lower[ 2 ];

	/* Number of unallocated inodes (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_inodes_lower[ 2 ];

	/* Number of directories (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_directories_lower[ 2 ];

	/* Block group flags
	 * Consists of 2 bytes
	 */
	uint8_t block_group_flags[ 2 ];

	/* Exclude bitmap block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t exclude_bitmap_block_number_lower[ 4 ];

	/* Block bitmap checksum (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t block_bitmap_checksum_lower[ 2 ];

	/* Inode bitmap checksum (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t inode_bitmap_checksum_lower[ 2 ];

	/* Number of unused inodes (lower 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unused_inodes_lower[ 2 ];

	/* Checksum
	 * Consists of 2 bytes
	 */
	uint8_t checksum[ 2 ];

	/* Block bitmap block number (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t block_bitmap_block_number_upper[ 4 ];

	/* Inode bitmap block number (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t inode_bitmap_block_number_upper[ 4 ];

	/* Inode table block number (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t inode_table_block_number_upper[ 4 ];

	/* Number of unallocated blocks (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_blocks_upper[ 2 ];

	/* Number of unallocated inodes (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_inodes_upper[ 2 ];

	/* Number of directories (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_directories_upper[ 2 ];

	/* Number of unused inodes (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unused_inodes_upper[ 2 ];

	/* Exclude bitmap block number (upper 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t exclude_bitmap_block_number_upper[ 4 ];

	/* Block bitmap checksum (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t block_bitmap_checksum_upper[ 2 ];

	/* Inode bitmap checksum (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t inode_bitmap_checksum_upper[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_GROUP_DESCRIPTOR_H ) */

