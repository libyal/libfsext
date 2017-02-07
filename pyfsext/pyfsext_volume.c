/*
 * Python object definition of the libfsext volume
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfsext_error.h"
#include "pyfsext_file_object_io_handle.h"
#include "pyfsext_integer.h"
#include "pyfsext_libbfio.h"
#include "pyfsext_libcerror.h"
#include "pyfsext_libfsext.h"
#include "pyfsext_python.h"
#include "pyfsext_unused.h"
#include "pyfsext_volume.h"

#if !defined( LIBFSEXT_HAVE_BFIO )

LIBFSEXT_EXTERN \
int libfsext_volume_open_file_io_handle(
     libfsext_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libfsext_error_t **error );

#endif /* !defined( LIBFSEXT_HAVE_BFIO ) */

PyMethodDef pyfsext_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyfsext_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

	/* Functions to access the volume */

	{ "open",
	  (PyCFunction) pyfsext_volume_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyfsext_volume_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	{ "close",
	  (PyCFunction) pyfsext_volume_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a volume." },

	/* Functions to access the volume values */

	{ "get_label",
	  (PyCFunction) pyfsext_volume_get_label,
	  METH_NOARGS,
	  "get_label() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the label." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfsext_volume_object_get_set_definitions[] = {

	{ "label",
	  (getter) pyfsext_volume_get_label,
	  (setter) 0,
	  "The label.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfsext_volume_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfsext.volume",
	/* tp_basicsize */
	sizeof( pyfsext_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfsext_volume_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyfsext volume object (wraps libfsext_volume_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyfsext_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfsext_volume_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyfsext_volume_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new volume object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_new(
           void )
{
	pyfsext_volume_t *pyfsext_volume = NULL;
	static char *function            = "pyfsext_volume_new";

	pyfsext_volume = PyObject_New(
	                   struct pyfsext_volume,
	                   &pyfsext_volume_type_object );

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	if( pyfsext_volume_init(
	     pyfsext_volume ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyfsext_volume );

on_error:
	if( pyfsext_volume != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfsext_volume );
	}
	return( NULL );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_new_open(
           PyObject *self PYFSEXT_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyfsext_volume = NULL;

	PYFSEXT_UNREFERENCED_PARAMETER( self )

	pyfsext_volume = pyfsext_volume_new();

	pyfsext_volume_open(
	 (pyfsext_volume_t *) pyfsext_volume,
	 arguments,
	 keywords );

	return( pyfsext_volume );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_new_open_file_object(
           PyObject *self PYFSEXT_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyfsext_volume = NULL;

	PYFSEXT_UNREFERENCED_PARAMETER( self )

	pyfsext_volume = pyfsext_volume_new();

	pyfsext_volume_open_file_object(
	 (pyfsext_volume_t *) pyfsext_volume,
	 arguments,
	 keywords );

	return( pyfsext_volume );
}

/* Intializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyfsext_volume_init(
     pyfsext_volume_t *pyfsext_volume )
{
	static char *function    = "pyfsext_volume_init";
	libcerror_error_t *error = NULL;

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	pyfsext_volume->volume         = NULL;
	pyfsext_volume->file_io_handle = NULL;

	if( libfsext_volume_initialize(
	     &( pyfsext_volume->volume ),
	     &error ) != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a volume object
 */
void pyfsext_volume_free(
      pyfsext_volume_t *pyfsext_volume )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyfsext_volume_free";
	int result                  = 0;

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	if( pyfsext_volume->volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - missing libfsext volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfsext_volume );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_free(
	          &( pyfsext_volume->volume ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free libfsext volume.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pyfsext_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_signal_abort(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments PYFSEXT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfsext_volume_signal_abort";
	int result               = 0;

	PYFSEXT_UNREFERENCED_PARAMETER( arguments )

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_signal_abort(
	          pyfsext_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_open(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pyfsext_volume_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	const char *filename_narrow  = NULL;
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyfsext_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libfsext_volume_open_wide(
		          pyfsext_volume->volume,
	                  filename_wide,
		          LIBFSEXT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyfsext_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
				   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libfsext_volume_open(
		          pyfsext_volume->volume,
	                  filename_narrow,
		          LIBFSEXT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyfsext_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyfsext_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   string_object );
#else
		filename_narrow = PyString_AsString(
				   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libfsext_volume_open(
		          pyfsext_volume->volume,
	                  filename_narrow,
		          LIBFSEXT_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfsext_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_open_file_object(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pyfsext_volume_open_file_object";
	int result                  = 0;

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pyfsext_file_object_initialize(
	     &( pyfsext_volume->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_open_file_io_handle(
	          pyfsext_volume->volume,
	          pyfsext_volume->file_io_handle,
	          LIBFSEXT_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open volume.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyfsext_volume->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyfsext_volume->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_close(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments PYFSEXT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfsext_volume_close";
	int result               = 0;

	PYFSEXT_UNREFERENCED_PARAMETER( arguments )

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_close(
	          pyfsext_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyfsext_volume->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyfsext_volume->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfsext_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the label
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsext_volume_get_label(
           pyfsext_volume_t *pyfsext_volume,
           PyObject *arguments PYFSEXT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *label           = NULL;
	static char *function    = "pyfsext_volume_get_label";
	size_t label_size        = 0;
	int result               = 0;

	PYFSEXT_UNREFERENCED_PARAMETER( arguments )

	if( pyfsext_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_get_utf8_label_size(
	          pyfsext_volume->volume,
	          &label_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve label size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( label_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	label = (uint8_t *) PyMem_Malloc(
	                     sizeof( uint8_t ) * label_size );

	if( label == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create label.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsext_volume_get_utf8_label(
		  pyfsext_volume->volume,
		  label,
		  label_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsext_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve label.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) label,
			 (Py_ssize_t) label_size - 1,
			 errors );

	PyMem_Free(
	 label );

	return( string_object );

on_error:
	if( label != NULL )
	{
		PyMem_Free(
		 label );
	}
	return( NULL );
}

