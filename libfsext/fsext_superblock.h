/*
 * Superblock of an Extended File System
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

#if !defined( _FSEXT_SUPERBLOCK_H )
#define _FSEXT_SUPERBLOCK_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_superblock_ext2 fsext_superblock_ext2_t;

struct fsext_superblock_ext2
{
	/* Number of inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_inodes[ 4 ];

	/* Number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Number of reserved blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_reserved_blocks[ 4 ];

	/* Number of unallocated blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_blocks[ 4 ];

	/* Number of unallocated inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_inodes[ 4 ];

	/* First data block number
	 * Consists of 4 bytes
	 */
	uint8_t first_data_block_number[ 4 ];

	/* Block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* Fragment size
	 * Consists of 4 bytes
	 */
	uint8_t fragment_size[ 4 ];

	/* Number of blocks per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks_per_block_group[ 4 ];

	/* Number of fragments per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_fragments_per_block_group[ 4 ];

	/* Number of inodes per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_inodes_per_block_group[ 4 ];

	/* Last mount time
	 * Consists of 4 bytes
	 */
	uint8_t last_mount_time[ 4 ];

	/* Last written time
	 * Consists of 4 bytes
	 */
	uint8_t last_written_time[ 4 ];

	/* Mount count
	 * Consists of 2 bytes
	 */
	uint8_t mount_count[ 2 ];

	/* Maximum mount count
	 * Consists of 2 bytes
	 */
	uint8_t maximum_mount_count[ 2 ];

	/* Signature
	 * Consists of 2 bytes
	 */
	uint8_t signature[ 2 ];

	/* File system state flags
	 * Consists of 2 bytes
	 */
	uint8_t file_system_state_flags[ 2 ];

	/* Error handling status
	 * Consists of 2 bytes
	 */
	uint8_t error_handling_status[ 2 ];

	/* Minor format revision
	 * Consists of 2 bytes
	 */
	uint8_t minor_format_revision[ 2 ];

	/* Last consistency check time
	 * Consists of 4 bytes
	 */
	uint8_t last_consistency_check_time[ 4 ];

	/* Consistency check interval
	 * Consists of 4 bytes
	 */
	uint8_t consistency_check_interval[ 4 ];

	/* Creator operating system
	 * Consists of 4 bytes
	 */
	uint8_t creator_operating_system[ 4 ];

	/* Format revision
	 * Consists of 4 bytes
	 */
	uint8_t format_revision[ 4 ];

	/* Reserved block user identifier (UID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_user_identifier[ 2 ];

	/* Reserved block group identifier (GID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_group_identifier[ 2 ];

	/* First non reserved inode
	 * Consists of 4 bytes
	 */
	uint8_t first_non_reserved_inode[ 4 ];

	/* Inode size
	 * Consists of 2 bytes
	 */
	uint8_t inode_size[ 2 ];

	/* Block group
	 * Consists of 2 bytes
	 */
	uint8_t block_group[ 2 ];

	/* Compatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t compatible_features_flags[ 4 ];

	/* Incompatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t incompatible_features_flags[ 4 ];

	/* Read only compatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t read_only_compatible_features_flags[ 4 ];

	/* File system identifier
	 * Consists of 16 bytes
	 */
	uint8_t file_system_identifier[ 16 ];

	/* Volume label
	 * Consists of 16 bytes
	 */
	uint8_t volume_label[ 16 ];

	/* Last mount path
	 * Consists of 64 bytes
	 */
	uint8_t last_mount_path[ 64 ];

	/* Algorithm usage bitmap
	 * Consists of 4 bytes
	 */
	uint8_t algorithm_usage_bitmap[ 4 ];

	/* Number of pre allocated blocks per file
	 * Consists of 1 byte
	 */
	uint8_t number_of_pre_allocated_blocks_per_file;

	/* Number of pre allocated blocks per directory
	 * Consists of 1 byte
	 */
	uint8_t number_of_pre_allocated_blocks_per_directory;

	/* Padding1
	 * Consists of 2 bytes
	 */
	uint8_t padding1[ 2 ];

	/* Journal identifier
	 * Consists of 16 bytes
	 */
	uint8_t journal_identifier[ 16 ];

	/* Journal inode number
	 * Consists of 4 bytes
	 */
	uint8_t journal_inode_number[ 4 ];

	/* Journal device
	 * Consists of 4 bytes
	 */
	uint8_t journal_device[ 4 ];

	/* Orphan inode list head
	 * Consists of 4 bytes
	 */
	uint8_t orphan_inode_list_head[ 4 ];

	/* HTREE hash seed
	 * Consists of 16 bytes
	 */
	uint8_t htree_hash_seed[ 16 ];

	/* Default hash version
	 * Consists of 1 byte
	 */
	uint8_t default_hash_version;

	/* Padding2
	 * Consists of 3 bytes
	 */
	uint8_t padding2[ 3 ];

	/* Default mount options
	 * Consists of 4 bytes
	 */
	uint8_t default_mount_options[ 4 ];

	/* First metadata block group
	 * Consists of 4 bytes
	 */
	uint8_t first_metadata_block_group[ 4 ];

	/* Padding3
	 * Consists of 190 bytes
	 */
	uint8_t padding3[ 190 ];
};

typedef struct fsext_superblock_ext4 fsext_superblock_ext4_t;

struct fsext_superblock_ext4
{
	/* Number of inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_inodes[ 4 ];

	/* Number of blocks lower
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks_lower[ 4 ];

	/* Number of reserved blocks lower
	 * Consists of 4 bytes
	 */
	uint8_t number_of_reserved_blocks_lower[ 4 ];

	/* Number of unallocated blocks lower
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_blocks_lower[ 4 ];

	/* Number of unallocated inodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_inodes[ 4 ];

	/* First data block number
	 * Consists of 4 bytes
	 */
	uint8_t first_data_block_number[ 4 ];

	/* Block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* Fragment size
	 * Consists of 4 bytes
	 */
	uint8_t fragment_size[ 4 ];

	/* Number of blocks per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks_per_block_group[ 4 ];

	/* Number of fragments per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_fragments_per_block_group[ 4 ];

	/* Number of inodes per block group
	 * Consists of 4 bytes
	 */
	uint8_t number_of_inodes_per_block_group[ 4 ];

	/* Last mount time
	 * Consists of 4 bytes
	 */
	uint8_t last_mount_time[ 4 ];

	/* Last written time
	 * Consists of 4 bytes
	 */
	uint8_t last_written_time[ 4 ];

	/* Mount count
	 * Consists of 2 bytes
	 */
	uint8_t mount_count[ 2 ];

	/* Maximum mount count
	 * Consists of 2 bytes
	 */
	uint8_t maximum_mount_count[ 2 ];

	/* Signature
	 * Consists of 2 bytes
	 */
	uint8_t signature[ 2 ];

	/* File system state flags
	 * Consists of 2 bytes
	 */
	uint8_t file_system_state_flags[ 2 ];

	/* Error handling status
	 * Consists of 2 bytes
	 */
	uint8_t error_handling_status[ 2 ];

	/* Minor format revision
	 * Consists of 2 bytes
	 */
	uint8_t minor_format_revision[ 2 ];

	/* Last consistency check time
	 * Consists of 4 bytes
	 */
	uint8_t last_consistency_check_time[ 4 ];

	/* Consistency check interval
	 * Consists of 4 bytes
	 */
	uint8_t consistency_check_interval[ 4 ];

	/* Creator operating system
	 * Consists of 4 bytes
	 */
	uint8_t creator_operating_system[ 4 ];

	/* Format revision
	 * Consists of 4 bytes
	 */
	uint8_t format_revision[ 4 ];

	/* Reserved block user identifier (UID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_user_identifier[ 2 ];

	/* Reserved block group identifier (GID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_group_identifier[ 2 ];

	/* First non reserved inode
	 * Consists of 4 bytes
	 */
	uint8_t first_non_reserved_inode[ 4 ];

	/* Inode size
	 * Consists of 2 bytes
	 */
	uint8_t inode_size[ 2 ];

	/* Block group
	 * Consists of 2 bytes
	 */
	uint8_t block_group[ 2 ];

	/* Compatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t compatible_features_flags[ 4 ];

	/* Incompatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t incompatible_features_flags[ 4 ];

	/* Read only compatible features flags
	 * Consists of 4 bytes
	 */
	uint8_t read_only_compatible_features_flags[ 4 ];

	/* File system identifier
	 * Consists of 16 bytes
	 */
	uint8_t file_system_identifier[ 16 ];

	/* Volume label
	 * Consists of 16 bytes
	 */
	uint8_t volume_label[ 16 ];

	/* Last mount path
	 * Consists of 64 bytes
	 */
	uint8_t last_mount_path[ 64 ];

	/* Algorithm usage bitmap
	 * Consists of 4 bytes
	 */
	uint8_t algorithm_usage_bitmap[ 4 ];

	/* Number of pre allocated blocks per file
	 * Consists of 1 byte
	 */
	uint8_t number_of_pre_allocated_blocks_per_file;

	/* Number of pre allocated blocks per directory
	 * Consists of 1 byte
	 */
	uint8_t number_of_pre_allocated_blocks_per_directory;

	/* Padding1
	 * Consists of 2 bytes
	 */
	uint8_t padding1[ 2 ];

	/* Journal identifier
	 * Consists of 16 bytes
	 */
	uint8_t journal_identifier[ 16 ];

	/* Journal inode number
	 * Consists of 4 bytes
	 */
	uint8_t journal_inode_number[ 4 ];

	/* Journal device
	 * Consists of 4 bytes
	 */
	uint8_t journal_device[ 4 ];

	/* Orphan inode list head
	 * Consists of 4 bytes
	 */
	uint8_t orphan_inode_list_head[ 4 ];

	/* HTREE hash seed
	 * Consists of 16 bytes
	 */
	uint8_t htree_hash_seed[ 16 ];

	/* Default hash version
	 * Consists of 1 byte
	 */
	uint8_t default_hash_version;

	/* Journal backup type
	 * Consists of 1 byte
	 */
	uint8_t journal_backup_type;

	/* Group descriptor size
	 * Consists of 2 bytes
	 */
	uint8_t group_descriptor_size[ 2 ];

	/* Default mount options
	 * Consists of 4 bytes
	 */
	uint8_t default_mount_options[ 4 ];

	/* First metadata block group
	 * Consists of 4 bytes
	 */
	uint8_t first_metadata_block_group[ 4 ];

	/* File system creation time
	 * Consists of 4 bytes
	 */
	uint8_t file_system_creation_time[ 4 ];

	/* Backup journal inodes
	 * Consists of 68 bytes
	 */
	uint8_t backup_journal_inodes[ 68 ];

	/* Number of blocks upper
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks_upper[ 4 ];

	/* Number of reserved blocks upper
	 * Consists of 4 bytes
	 */
	uint8_t number_of_reserved_blocks_upper[ 4 ];

	/* Number of unallocated blocks upper
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unallocated_blocks_upper[ 4 ];

	/* Minimum inode size
	 * Consists of 2 bytes
	 */
	uint8_t minimum_inode_size[ 2 ];

	/* Reserved inode size
	 * Consists of 2 bytes
	 */
	uint8_t reserved_inode_size[ 2 ];

	/* Flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Read stride
	 * Consists of 2 bytes
	 */
	uint8_t read_stride[ 2 ];

	/* Multi mount protection update interval
	 * Consists of 2 bytes
	 */
	uint8_t multi_mount_protection_update_interval[ 2 ];

	/* Multi mount protection block
	 * Consists of 8 bytes
	 */
	uint8_t multi_mount_protection_block[ 8 ];

	/* Raid stripe width
	 * Consists of 4 bytes
	 */
	uint8_t raid_stripe_width[ 4 ];

	/* Number of block groups per flex (block) group
	 * Consists of 1 byte
	 */
	uint8_t number_of_block_groups_per_flex_group;

	/* Checksum type
	 * Consists of 1 byte
	 */
	uint8_t checksum_type;

	/* Encryption level
	 * Consists of 1 byte
	 */
	uint8_t encryption_level;

	/* Padding2
	 * Consists of 1 byte
	 */
	uint8_t padding2;

	/* Write count
	 * Consists of 8 bytes
	 */
	uint8_t write_count[ 8 ];

	/* Snapshot inode number
	 * Consists of 4 bytes
	 */
	uint8_t snapshot_inode_number[ 4 ];

	/* Snapshot sequential identifier
	 * Consists of 4 bytes
	 */
	uint8_t snapshot_sequential_identifier[ 4 ];

	/* Snapshot number of reserved blocks
	 * Consists of 8 bytes
	 */
	uint8_t snapshot_number_of_reserved_blocks[ 8 ];

	/* Snapshot inode list
	 * Consists of 4 bytes
	 */
	uint8_t snapshot_inode_list[ 4 ];

	/* Number of errors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_errors[ 4 ];

	/* First error time
	 * Consists of 4 bytes
	 */
	uint8_t first_error_time[ 4 ];

	/* First error inode number
	 * Consists of 4 bytes
	 */
	uint8_t first_error_inode_number[ 4 ];

	/* First error block number
	 * Consists of 8 bytes
	 */
	uint8_t first_error_block_number[ 8 ];

	/* First error function
	 * Consists of 32 bytes
	 */
	uint8_t first_error_function[ 32 ];

	/* First error function line number
	 * Consists of 4 bytes
	 */
	uint8_t first_error_function_line_number[ 4 ];

	/* Last error time
	 * Consists of 4 bytes
	 */
	uint8_t last_error_time[ 4 ];

	/* Last error inode number
	 * Consists of 4 bytes
	 */
	uint8_t last_error_inode_number[ 4 ];

	/* Last error function line number
	 * Consists of 4 bytes
	 */
	uint8_t last_error_function_line_number[ 4 ];

	/* Last error block number
	 * Consists of 8 bytes
	 */
	uint8_t last_error_block_number[ 8 ];

	/* Last error function
	 * Consists of 32 bytes
	 */
	uint8_t last_error_function[ 32 ];

	/* Mount options
	 * Consists of 64 bytes
	 */
	uint8_t mount_options[ 64 ];

	/* User quota inode number
	 * Consists of 4 bytes
	 */
	uint8_t user_quota_inode_number[ 4 ];

	/* Group quota inode number
	 * Consists of 4 bytes
	 */
	uint8_t group_quota_inode_number[ 4 ];

	/* Overhead number of clusters
	 * Consists of 4 bytes
	 */
	uint8_t overhead_number_of_clusters[ 4 ];

	/* First backup block group
	 * Consists of 4 bytes
	 */
	uint8_t backup_block_group1[ 4 ];

	/* Second backup block group
	 * Consists of 4 bytes
	 */
	uint8_t backup_block_group2[ 4 ];

	/* Encryption algorithms
	 * Consists of 4 bytes
	 */
	uint8_t encryption_algorithms[ 4 ];

	/* Encryption password salt
	 * Consists of 16 bytes
	 */
	uint8_t encryption_password_salt[ 16 ];

	/* Lost and found inode number
	 * Consists of 4 bytes
	 */
	uint8_t lost_and_found_inode_number[ 4 ];

	/* Project quota inode number
	 * Consists of 4 bytes
	 */
	uint8_t project_quota_inode_number[ 4 ];

	/* Checksum seed
	 * Consists of 4 bytes
	 */
	uint8_t checksum_seed[ 4 ];

	/* Padding3
	 * Consists of 392 bytes
	 */
	uint8_t padding3[ 392 ];

	/* Checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_SUPERBLOCK_H ) */

