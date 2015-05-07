/*
 * The ext group descriptor definition
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

#if !defined( _FSEXT_GROUP_DESCRIPTOR_H )
#define _FSEXT_GROUP_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_group_descriptor fsext_group_descriptor_t;

struct fsext_group_descriptor
{
	/* The block bitmap block number
	 * Consists of 4 bytes
	 */
	uint8_t block_bitmap_block_number[ 4 ];

	/* The inode bitmap block number
	 * Consists of 4 bytes
	 */
	uint8_t inode_bitmap_block_number[ 4 ];

	/* The inode table block number
	 * Consists of 4 bytes
	 */
	uint8_t inode_table_block_number[ 4 ];

	/* The number of unallocated blocks
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_blocks[ 2 ];

	/* The number of unallocated inodes
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unallocated_inodes[ 2 ];

	/* The number of directories
	 * Consists of 2 bytes
	 */
	uint8_t number_of_directories[ 2 ];

	/* Padding
	 * Consists of 2 bytes
	 */
	uint8_t padding[ 2 ];

	/* Unknown (reserved)
	 * Consists of 12 bytes
	 */
	uint8_t unknown1[ 12 ];
};

#if defined( __cplusplus )
}
#endif

#endif

