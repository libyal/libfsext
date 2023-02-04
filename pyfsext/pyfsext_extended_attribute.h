/*
 * Python object wrapper of libfsext_extended_attribute_t
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

#if !defined( _PYFSEXT_EXTENDED_ATTRIBUTE_H )
#define _PYFSEXT_EXTENDED_ATTRIBUTE_H

#include <common.h>
#include <types.h>

#include "pyfsext_libfsext.h"
#include "pyfsext_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfsext_extended_attribute pyfsext_extended_attribute_t;

struct pyfsext_extended_attribute
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfsext extended attribute
	 */
	libfsext_extended_attribute_t *extended_attribute;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfsext_extended_attribute_object_methods[];
extern PyTypeObject pyfsext_extended_attribute_type_object;

PyObject *pyfsext_extended_attribute_new(
           libfsext_extended_attribute_t *extended_attribute,
           PyObject *parent_object );

int pyfsext_extended_attribute_init(
     pyfsext_extended_attribute_t *pyfsext_extended_attribute );

void pyfsext_extended_attribute_free(
      pyfsext_extended_attribute_t *pyfsext_extended_attribute );

PyObject *pyfsext_extended_attribute_get_name(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments );

PyObject *pyfsext_extended_attribute_read_buffer(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_extended_attribute_read_buffer_at_offset(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_extended_attribute_seek_offset(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_extended_attribute_get_offset(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments );

PyObject *pyfsext_extended_attribute_get_size(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments );

PyObject *pyfsext_extended_attribute_get_number_of_extents(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments );

PyObject *pyfsext_extended_attribute_get_extent_by_index(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           int extent_index );

PyObject *pyfsext_extended_attribute_get_extent(
           pyfsext_extended_attribute_t *pyfsext_extended_attribute,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFSEXT_EXTENDED_ATTRIBUTE_H ) */

