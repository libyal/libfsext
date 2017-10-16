/*
 * Inode table functions
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

#if !defined( _LIBFSEXT_INODE_TABLE_H )
#define _LIBFSEXT_INODE_TABLE_H

#include <common.h>
#include <types.h>

#include "libfsext_io_handle.h"
#include "libfsext_libcdata.h"
#include "libfsext_libbfio.h"
#include "libfsext_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsext_inode_table libfsext_inode_table_t;

struct libfsext_inode_table
{
	/* Inodes array
	 */
	libcdata_array_t *inodes_array;
};

int libfsext_inode_table_initialize(
     libfsext_inode_table_t **inode_table,
     libcerror_error_t **error );

int libfsext_inode_table_free(
     libfsext_inode_table_t **inode_table,
     libcerror_error_t **error );

int libfsext_inode_table_read_data(
     libfsext_inode_table_t *inode_table,
     const uint8_t *data,
     size_t data_size,
     off64_t file_offset,
     libcerror_error_t **error );

int libfsext_inode_table_read_file_io_handle(
     libfsext_inode_table_t *inode_table,
     libfsext_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_INODE_TABLE_H ) */

