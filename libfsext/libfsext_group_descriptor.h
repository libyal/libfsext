/*
 * Group descriptor functions
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

#if !defined( _LIBFSEXT_GROUP_DESCRIPTOR_H )
#define _LIBFSEXT_GROUP_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_group_descriptor libfsext_group_descriptor_t;

struct libfsext_group_descriptor
{
	/* Block bitmap block number
	 */
	uint64_t block_bitmap_block_number;

	/* Inode bitmap block number
	 */
	uint64_t inode_bitmap_block_number;

	/* Inode table block number
	 */
	uint64_t inode_table_block_number;

	/* Number of unallocated blocks
	 */
	uint32_t number_of_unallocated_blocks;

	/* Number of unallocated inodes
	 */
	uint32_t number_of_unallocated_inodes;

	/* Number of directories
	 */
	uint32_t number_of_directories;

	/* Block group flags
	 */
	uint16_t block_group_flags;

	/* Exclude bitmap block number
	 */
	uint64_t exclude_bitmap_block_number;

	/* Block bitmap checksum
	 */
	uint32_t block_bitmap_checksum;

	/* Inode bitmap checksum
	 */
	uint32_t inode_bitmap_checksum;

	/* Number of unused inodes
	 */
	uint32_t number_of_unused_inodes;
};

int libfsext_group_descriptor_initialize(
     libfsext_group_descriptor_t **group_descriptor,
     libcerror_error_t **error );

int libfsext_group_descriptor_free(
     libfsext_group_descriptor_t **group_descriptor,
     libcerror_error_t **error );

int libfsext_group_descriptor_read_data(
     libfsext_group_descriptor_t *group_descriptor,
     libfsext_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfsext_group_descriptor_read_file_io_handle(
     libfsext_group_descriptor_t *group_descriptor,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_GROUP_DESCRIPTOR_H ) */

