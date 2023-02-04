/*
 * Python object definition of the sequence and iterator object of file entries
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

#if !defined( _PYFSEXT_FILE_ENTRIES_H )
#define _PYFSEXT_FILE_ENTRIES_H

#include <common.h>
#include <types.h>

#include "pyfsext_libfsext.h"
#include "pyfsext_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfsext_file_entries pyfsext_file_entries_t;

struct pyfsext_file_entries
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyfsext_file_entries_type_object;

PyObject *pyfsext_file_entries_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyfsext_file_entries_init(
     pyfsext_file_entries_t *sequence_object );

void pyfsext_file_entries_free(
      pyfsext_file_entries_t *sequence_object );

Py_ssize_t pyfsext_file_entries_len(
            pyfsext_file_entries_t *sequence_object );

PyObject *pyfsext_file_entries_getitem(
           pyfsext_file_entries_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyfsext_file_entries_iter(
           pyfsext_file_entries_t *sequence_object );

PyObject *pyfsext_file_entries_iternext(
           pyfsext_file_entries_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFSEXT_FILE_ENTRIES_H ) */

