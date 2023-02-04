/*
 * Extents of an Extended File System
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

#if !defined( _FSEXT_EXTENT_H )
#define _FSEXT_EXTENT_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_extents_header_ext4 fsext_extents_header_ext4_t;

struct fsext_extents_header_ext4
{
	/* Signature
	 * Consists of 2 bytes
	 */
	uint8_t signature[ 2 ];

	/* Number of extents
	 * Consists of 2 bytes
	 */
	uint8_t number_of_extents[ 2 ];

	/* Maximum number of extents
	 * Consists of 2 bytes
	 */
	uint8_t maximum_number_of_extents[ 2 ];

	/* Depth
	 * Consists of 2 bytes
	 */
	uint8_t depth[ 2 ];

	/* Generation
	 * Consists of 4 bytes
	 */
	uint8_t generation[ 4 ];
};

typedef struct fsext_extent_ext4 fsext_extent_ext4_t;

struct fsext_extent_ext4
{
	/* Logical block number
	 * Consists of 4 bytes
	 */
	uint8_t logical_block_number[ 4 ];

	/* Number of blocks
	 * Consists of 2 bytes
	 */
	uint8_t number_of_blocks[ 2 ];

	/* Physical block number (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t physical_block_number_upper[ 2 ];

	/* Physical block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t physical_block_number_lower[ 4 ];
};

typedef struct fsext_extent_index_ext4 fsext_extent_index_ext4_t;

struct fsext_extent_index_ext4
{
	/* Logical block number
	 * Consists of 4 bytes
	 */
	uint8_t logical_block_number[ 4 ];

	/* Physical block number (lower 32-bit)
	 * Consists of 4 bytes
	 */
	uint8_t physical_block_number_lower[ 4 ];

	/* Physical block number (upper 16-bit)
	 * Consists of 2 bytes
	 */
	uint8_t physical_block_number_upper[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];
};

typedef struct fsext_extents_footer_ext4 fsext_extents_footer_ext4_t;

struct fsext_extents_footer_ext4
{
	/* Checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_EXTENT_H ) */

