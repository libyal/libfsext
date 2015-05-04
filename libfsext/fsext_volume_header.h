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

	/* The major version
	 * Consists of 4 bytes
	 */
	uint8_t major_version[ 4 ];

	/* The reserved block user identifier (UID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_uid[ 2 ];

	/* The reserved block group identifier (GID)
	 * Consists of 2 bytes
	 */
	uint8_t reserved_block_gid[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif

