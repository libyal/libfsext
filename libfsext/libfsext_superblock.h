/*
 * Superblock functions
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

#if !defined( _LIBFSEXT_SUPERBLOCK_H )
#define _LIBFSEXT_SUPERBLOCK_H

#include <common.h>
#include <types.h>

#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *fsext_superblock_signature;

typedef struct libfsext_superblock libfsext_superblock_t;

struct libfsext_superblock
{
	/* Number of inodes
	 */
	uint32_t number_of_inodes;

	/* Number of blocks
	 */
	uint64_t number_of_blocks;

	/* Number of reserved blocks
	 */
	uint64_t number_of_reserved_blocks;

	/* Number of unallocated blocks
	 */
	uint64_t number_of_unallocated_blocks;

	/* Number of unallocated inodes
	 */
	uint32_t number_of_unallocated_inodes;

	/* First data block number
	 */
	uint32_t first_data_block_number;

	/* Block size
	 */
	uint32_t block_size;

	/* Fragment size
	 */
	uint32_t fragment_size;

	/* Number of blocks per block group
	 */
	uint32_t number_of_blocks_per_block_group;

	/* Number of fragments per block group
	 */
	uint32_t number_of_fragments_per_block_group;

	/* Number of inodes per block group
	 */
	uint32_t number_of_inodes_per_block_group;

	/* Number of blocks per flex group
	 */
	uint32_t number_of_blocks_per_flex_group;

	/* Last mount time
	 */
	uint32_t last_mount_time;

	/* Last written time
	 */
	uint32_t last_written_time;

	/* Mount count
	 */
	uint16_t mount_count;

	/* Maximum mount count
	 */
	uint16_t maximum_mount_count;

	/* File system state flags
	 */
	uint16_t file_system_state_flags;

	/* Error handling status
	 */
	uint16_t error_handling_status;

	/* Minor format revision
	 */
	uint16_t minor_format_revision;

	/* Last consistency check time
	 */
	uint32_t last_consistency_check_time;

	/* Consistency check interval
	 */
	uint32_t consistency_check_interval;

	/* Creator operating system
	 */
	uint32_t creator_operating_system;

	/* Format revision
	 */
	uint32_t format_revision;

	/* Reserved block user identifier
	 */
	uint16_t reserved_block_user_identifier;

	/* Reserved block group identifier
	 */
	uint16_t reserved_block_group_identifier;

	/* First non reserved inode
	 */
	uint32_t first_non_reserved_inode;

	/* Inode size
	 */
	uint16_t inode_size;

	/* Block group
	 */
	uint16_t block_group;

	/* Compatible features flags
	 */
	uint32_t compatible_features_flags;

	/* Incompatible features flags
	 */
	uint32_t incompatible_features_flags;

	/* Read only compatible features flags
	 */
	uint32_t read_only_compatible_features_flags;

	/* File system identifier
	 */
	uint8_t file_system_identifier[ 16 ];

	/* Volume label
	 */
	uint8_t volume_label[ 16 ];

	/* Last mount path
	 */
	uint8_t last_mount_path[ 64 ];

	/* Algorithm usage bitmap
	 */
	uint32_t algorithm_usage_bitmap;

	/* Number of pre allocated blocks per file
	 */
	uint8_t number_of_pre_allocated_blocks_per_file;

	/* Number of pre allocated blocks per directory
	 */
	uint8_t number_of_pre_allocated_blocks_per_directory;

	/* Journal identifier
	 */
	/* TODO: implement */

	/* Journal inode
	 */
	uint32_t journal_inode;

	/* Journal device
	 */
	uint32_t journal_device;

	/* Head of orphan inode list
	 */
	uint32_t head_of_orphan_inode_list;

	/* Htree hash seed
	 */
	/* TODO: implement */

	/* Default hash version
	 */
	uint8_t default_hash_version;

	/* Journal backup type
	 */
	uint8_t journal_backup_type;

	/* Group descriptor size
	 */
	uint16_t group_descriptor_size;

	/* First metadata block group
	 */
	uint32_t first_metadata_block_group;

	/* File system creation time
	 */
	uint32_t file_system_creation_time;

	/* Backup journal inodes
	 */
/* TODO: implement */

	/* Format version
	 */
	int format_version;

	/* Number of block groups
	 */
	uint32_t number_of_block_groups;

	/* Block group size
	 */
	size64_t block_group_size;

	/* Flex group size
	 */
	size64_t flex_group_size;
};

int libfsext_superblock_initialize(
     libfsext_superblock_t **superblock,
     libcerror_error_t **error );

int libfsext_superblock_free(
     libfsext_superblock_t **superblock,
     libcerror_error_t **error );

int libfsext_superblock_read_data(
     libfsext_superblock_t *superblock,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_superblock_read_file_io_handle(
     libfsext_superblock_t *superblock,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libfsext_superblock_get_file_system_identifier(
     libfsext_superblock_t *superblock,
     uint8_t *uuid_data,
     size_t uuid_data_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf8_volume_label_size(
     libfsext_superblock_t *superblock,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf8_volume_label(
     libfsext_superblock_t *superblock,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf16_volume_label_size(
     libfsext_superblock_t *superblock,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf16_volume_label(
     libfsext_superblock_t *superblock,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf8_last_mount_path_size(
     libfsext_superblock_t *superblock,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf8_last_mount_path(
     libfsext_superblock_t *superblock,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf16_last_mount_path_size(
     libfsext_superblock_t *superblock,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfsext_superblock_get_utf16_last_mount_path(
     libfsext_superblock_t *superblock,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_SUPERBLOCK_H ) */

