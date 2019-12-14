/*
 * Python object wrapper of libfsext_volume_t
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYFSEXT_VOLUME_H )
#define _PYFSEXT_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyfsext_libbfio.h"
#include "pyfsext_libfsext.h"
#include "pyfsext_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfsext_volume pyfsext_volume_t;

struct pyfsext_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfsext volume
	 */
	libfsext_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyfsext_volume_object_methods[];
extern PyTypeObject pyfsext_volume_type_object;

PyObject *pyfsext_volume_new(
           void );

PyObject *pyfsext_volume_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_volume_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyfsext_volume_init(
     pyfsext_volume_t *pyfsext_volume );

void pyfsext_volume_free(
      pyfsext_volume_t *pyfsext_volume );

PyObject *pyfsext_volume_signal_abort(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments );

PyObject *pyfsext_volume_open(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_volume_open_file_object(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfsext_volume_close(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments );

PyObject *pyfsext_volume_get_label(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFSEXT_VOLUME_H ) */

