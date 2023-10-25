if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

pyexec_LTLIBRARIES = pyfsext.la

pyfsext_la_SOURCES = \
	pyfsext.c pyfsext.h \
	pyfsext_datetime.c pyfsext_datetime.h \
	pyfsext_error.c pyfsext_error.h \
	pyfsext_extended_attribute.c pyfsext_extended_attribute.h \
	pyfsext_extended_attributes.c pyfsext_extended_attributes.h \
	pyfsext_file_entries.c pyfsext_file_entries.h \
	pyfsext_file_entry.c pyfsext_file_entry.h \
	pyfsext_file_object_io_handle.c pyfsext_file_object_io_handle.h \
	pyfsext_integer.c pyfsext_integer.h \
	pyfsext_libbfio.h \
	pyfsext_libcerror.h \
	pyfsext_libfsext.h \
	pyfsext_python.h \
	pyfsext_unused.h \
	pyfsext_volume.c pyfsext_volume.h

pyfsext_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyfsext_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyfsext_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f setup.py
	-rm -f Makefile

