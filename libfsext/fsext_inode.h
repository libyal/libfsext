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

typedef struct fsext_inode fsext_inode_t;

struct fsext_inode
{
	/* File mode
	 * Consists of 2 bytes
	 */
	uint8_t file_mode[ 2 ];

	/* User identifier
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier[ 2 ];

	/* Data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Last access time
	 * Consists of 4 bytes
	 */
	uint8_t last_access_time[ 4 ];

	/* Last inode change time
	 * Consists of 4 bytes
	 */
	uint8_t last_inode_change_time[ 4 ];

	/* Last modification time
	 * Consists of 4 bytes
	 */
	uint8_t last_modification_time[ 4 ];

	/* Deletion time
	 * Consists of 4 bytes
	 */
	uint8_t deletion_time[ 4 ];

	/* Group identifier
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier[ 2 ];

	/* Link count
	 * Consists of 2 bytes
	 */
	uint8_t link_count[ 2 ];

	/* Sector count
	 * Consists of 4 bytes
	 */
	uint8_t sector_count[ 4 ];

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

	/* Nfs generation number
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

	/* User identifier 32bit
	 * Consists of 2 bytes
	 */
	uint8_t user_identifier_32bit[ 2 ];

	/* Group identifier 32bit
	 * Consists of 2 bytes
	 */
	uint8_t group_identifier_32bit[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_INODE_H ) */

