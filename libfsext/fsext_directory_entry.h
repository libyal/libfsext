/*
 * Directory entry of an Extended File System
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

#if !defined( _FSEXT_DIRECTORY_ENTRY_H )
#define _FSEXT_DIRECTORY_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fsext_directory_entry fsext_directory_entry_t;

struct fsext_directory_entry
{
	/* Inode number
	 * Consists of 4 bytes
	 */
	uint8_t inode_number[ 4 ];

	/* Size
	 * Consists of 2 bytes
	 */
	uint8_t size[ 2 ];

	/* Name size
	 * Consists of 1 byte
	 */
	uint8_t name_size;

	/* File type
	 * Consists of 1 byte
	 */
	uint8_t file_type;

	/* Name
	 */
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXT_DIRECTORY_ENTRY_H ) */

