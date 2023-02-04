/*
 * Python object wrapper of libfsext_file_entry_t
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

#if !defined( _PYFSEXT_FILE_ENTRY_H )
#define _PYFSEXT_FILE_ENTRY_H

#include <common.h>
#include <types.h>

#include "pyfsext_libfsext.h"
#include "pyfsext_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfsext_file_entry pyfsext_file_entry_t;

struct pyfsext_file_entry
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfsext file entry
	 */
	libfsext_file_entry_t *file_entry;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfsext_file_entry_object_methods[];
extern PyTypeObject pyfsext_file_entry_type_object;

PyObject *pyfsext_file_entry_new(
           libfsext_file_entry_t *file_entry,
           PyObject *parent_object );

int pyfsext_file_entry_init(
     pyfsext_file_entry_t *pyfsext_file_entry );

void pyfsext_file_entry_free(
      pyfsext_file_entry_t *pyfsext_file_entry );

PyObject *pyfsext_file_entry_is_empty(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_inode_number(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_access_time(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_access_time_as_integer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_creation_time(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_creation_time_as_integer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_inode_change_time(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_inode_change_time_as_integer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_modification_time(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_modification_time_as_integer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_deletion_time(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_deletion_time_as_integer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_file_mode(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_number_of_links(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_owner_identifier(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_group_identifier(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_device_number(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_name(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_symbolic_link_target(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_number_of_extended_attributes(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_extended_attribute_by_index(
           PyObject *pyfsext_file_entry,
           int extended_attribute_index );

PyObject *pyfsext_file_entry_get_extended_attribute(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_get_extended_attributes(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_has_extended_attribute_by_name(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_get_extended_attribute_by_name(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_get_number_of_sub_file_entries(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_sub_file_entry_by_index(
           PyObject *pyfsext_file_entry,
           int sub_file_entry_index );

PyObject *pyfsext_file_entry_get_sub_file_entry(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_get_sub_file_entries(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_sub_file_entry_by_name(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_read_buffer(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_read_buffer_at_offset(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_seek_offset(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_file_entry_get_offset(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_size(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_number_of_extents(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments );

PyObject *pyfsext_file_entry_get_extent_by_index(
           pyfsext_file_entry_t *pyfsext_file_entry,
           int extent_index );

PyObject *pyfsext_file_entry_get_extent(
           pyfsext_file_entry_t *pyfsext_file_entry,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFSEXT_FILE_ENTRY_H ) */

