/*
 * Inode table functions
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

#if !defined( _LIBFSEXT_INODE_TABLE_H )
#define _LIBFSEXT_INODE_TABLE_H

#include <common.h>
#include <types.h>

#include "libfsext_inode.h"
#include "libfsext_io_handle.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"
#include "libfsext_libcdata.h"
#include "libfsext_libfcache.h"
#include "libfsext_libfdata.h"
#include "libfsext_superblock.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_inode_table libfsext_inode_table_t;

struct libfsext_inode_table
{
	/* The inode data size
	 */
	size_t inode_data_size;

	/* The inodes vector
	 */
	libfdata_vector_t *inodes_vector;

	/* The inodes cache
	 */
	libfcache_cache_t *inodes_cache;
};

int libfsext_inode_table_initialize(
     libfsext_inode_table_t **inode_table,
     uint16_t inode_size,
     libfsext_io_handle_t *io_handle,
     libfsext_superblock_t *superblock,
     libcdata_array_t *group_descriptors_array,
     libcerror_error_t **error );

int libfsext_inode_table_free(
     libfsext_inode_table_t **inode_table,
     libcerror_error_t **error );

int libfsext_inode_table_get_inode_by_number(
     libfsext_inode_table_t *inode_table,
     libbfio_handle_t *file_io_handle,
     uint32_t inode_number,
     libfsext_inode_t **inode,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_INODE_TABLE_H ) */

