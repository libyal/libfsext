/*
 * Extended attributes of an Extended File System
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

#if !defined( _FSEXT_ATTRIBUTES_H )
#define _FSEXT_ATTRIBUTES_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_attributes_header_ext2 fsext_attributes_header_ext2_t;

struct fsext_attributes_header_ext2
{
	/* Signature
	 * Consists of 4 bytes
	 */
	uint8_t signature[ 4 ];

	/* Reference count
	 * Consists of 4 bytes
	 */
	uint8_t reference_count[ 4 ];

	/* Number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Attributes hash
	 * Consists of 4 bytes
	 */
	uint8_t attributes_hash[ 4 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown1[ 16 ];
};

typedef struct fsext_attributes_header_ext4 fsext_attributes_header_ext4_t;

struct fsext_attributes_header_ext4
{
	/* Signature
	 * Consists of 4 bytes
	 */
	uint8_t signature[ 4 ];

	/* Reference count
	 * Consists of 4 bytes
	 */
	uint8_t reference_count[ 4 ];

	/* Number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Attributes hash
	 * Consists of 4 bytes
	 */
	uint8_t attributes_hash[ 4 ];

	/* Checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* Unknown
	 * Consists of 12 bytes
	 */
	uint8_t unknown1[ 12 ];
};

typedef struct fsext_attributes_entry fsext_attributes_entry_t;

struct fsext_attributes_entry
{
	/* Name size
	 * Consists of 1 byte
	 */
	uint8_t name_size;

	/* Name index
	 * Consists of 1 byte
	 */
	uint8_t name_index;

	/* Value data offset
	 * Consists of 2 bytes
	 */
	uint8_t value_data_offset[ 2 ];

	/* Value data inode number
	 * Consists of 4 bytes
	 */
	uint8_t value_data_inode_number[ 4 ];

	/* Value data size
	 * Consists of 4 bytes
	 */
	uint8_t value_data_size[ 4 ];

	/* Attribute hash
	 * Consists of 4 bytes
	 */
	uint8_t attribute_hash[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_ATTRIBUTES_H ) */

