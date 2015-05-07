/*
 * The ext volume header definition
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _FSEXT_VOLUME_HEADER_H )
#define _FSEXT_VOLUME_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_volume_header fsext_volume_header_t;

struct fsext_volume_header
{
	/* The number of inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_inodes[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* The number of reserved blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_reserved_blocks[ 4 ];

	/* The number of unallocated blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_blocks[ 4 ];

	/* The number of unallocated inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_inodes[ 4 ];

	/* The root block group block number
	 * Consists of 4 bytes
	 */
	uint8_t root_block_group_block_number[ 4 ];

	/* The block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* The fragment size
	 * Consists of 4 bytes
	 */
	uint8_t fragment_size[ 4 ];

	/* The number of blocks per block group
	 * Consists of 4 bytes
	 */
	uint8_t blocks_per_block_group[ 4 ];

	/* The number of fragments per block group
	 * Consists of 4 bytes
	 */
	uint8_t fragments_per_block_group[ 4 ];

	/* The number of inodes per block group
	 * Consists of 4 bytes
	 */
	uint8_t inodes_per_block_group[ 4 ];

	/* The last mount time
	 * Consists of 4 bytes
	 * Contains: a POSIX timestamp
	 */
	uint8_t last_mount_time[ 4 ];

	/* The last written time
	 * Consists of 4 bytes
	 * Contains: a POSIX timestamp
	 */
	uint8_t last_written_time[ 4 ];

	/* The (current) mount count
	 * Consists of 2 bytes
	 */
	uint8_t mount_count[ 2 ];

	/* The maximum mount count
	 * Consists of 2 bytes
	 */
	uint8_t maximum_mount_count[ 2 ];

	/* The signature
	 * Consists of 2 bytes
	 * Contains: 0x53 0xef
	 */
	uint8_t signature[ 2 ];

	/* The file system state flags
	 * Consists of 2 bytes
	 */
	uint8_t file_system_state_flags[ 2 ];

	/* The error-handeling status
	 * Consists of 2 bytes
	 */
	uint8_t error_handling_status[ 2 ];

	/* The minor version
	 * Consists of 2 bytes
	 */
	uint8_t minor_version[ 2 ];

	/* The last consistency check time
	 * Consists of 4 bytes
	 * Contains: a POSIX timestamp
	 */
	uint8_t last_consistency_check_time[ 4 ];

	/* The consistency check interval
	 * Consists of 4 bytes
	 * Contains: a POSIX timestamp
	 */
	uint8_t consistency_check_interval[ 4 ];

	/* The creator operating system
	 * Consists of 4 bytes
	 */
	uint8_t creator_operating_system[ 4 ];

	/* The format revision
	 * Consists of 4 bytes
	 */
	uint8_t format_revision[ 4 ];

	/* The reserved block user identifier (UID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_uid[ 2 ];

	/* The reserved block group identifier (GID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_gid[ 2 ];
};

typedef struct fsext_volume_dynamic_inode_information fsext_volume_dynamic_inode_information_t;

struct fsext_volume_dynamic_inode_information
{
	/* The first non-reserved inode
	 * Consists of 4 bytes
	 */
	uint8_t first_non_reserved_inode[ 4 ];

	/* The inode size
	 * Consists of 2 bytes
	 */
	uint8_t inode_size[ 2 ];

	/* The block group
	 * Consists of 2 bytes
	 */
	uint8_t block_group[ 2 ];

	/* The compatible feature flags
	 * Consists of 4 bytes
	 */
	uint8_t compatible_features_flags[ 4 ];

	/* The incompatible feature flags
	 * Consists of 4 bytes
	 */
	uint8_t incompatible_features_flags[ 4 ];

	/* The read-only compatible feature flags
	 * Consists of 4 bytes
	 */
	uint8_t read_only_compatible_features_flags[ 4 ];

	/* The file system identifier
	 * Consists of 16 bytes
	 * Contains a GUID/UUID
	 */
	uint8_t file_system_identifier[ 16 ];

	/* The volume label
	 * Consists of 16 bytes
	 * Contains an UTF-8 string
	 */
	uint8_t volume_label[ 16 ];

	/* The last mounted path
	 * Consists of 64 bytes
	 * Contains an UTF-8 string
	 */
	uint8_t last_mounted_path[ 64 ];

	/* The algorithm usage bitmap
	 * Consists of 4 bytes
	 */
	uint8_t algorithm_usage_bitmap[ 4 ];
};

typedef struct fsext_volume_performance_hints fsext_volume_performance_hints_t;

struct fsext_volume_performance_hints
{
	/* The number of pre-allocated blocks per file
	 * Consists of 1 byte
	 */
	uint8_t number_of_block_per_file;

	/* The number of pre-allocated blocks per directory
	 * Consists of 1 byte
	 */
	uint8_t number_of_block_per_directory;

	/* Padding
	 * Consists of 2 bytes
	 */
	uint8_t padding[ 2 ];
};

typedef struct fsext_volume_journal_information fsext_volume_journal_information_t;

struct fsext_volume_journal_information
{
	/* The journal identifier
	 * Consists of 16 bytes
	 * Contains a GUID/UUID
	 */
	uint8_t journal_identifier[ 16 ];

	/* The journal inode
	 * Consists of 4 bytes
	 */
	uint8_t journal_inode[ 4 ];

	/* The journal device
	 * Consists of 4 bytes
	 */
	uint8_t journal_device[ 4 ];

	/* The orphan inode list head
	 * Consists of 4 bytes
	 */
	uint8_t orphan_inode_list_head[ 4 ];

	/* The HTREE hash seed
	 * Consists of 16 bytes
	 */
	uint8_t htree_hash_seed[ 16 ];

	/* The default hash version
	 * Consists of 1 byte
	 */
	uint8_t default_hash_version;

	/* Padding
	 * Consists of 3 bytes
	 */
	uint8_t padding[ 3 ];

	/* The default mount options
	 * Consists of 4 bytes
	 */
	uint8_t default_mount_options[ 4 ];

	/* The first metadata block group
	 * Consists of 4 bytes
	 */
	uint8_t first_metadata_block_group[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif

