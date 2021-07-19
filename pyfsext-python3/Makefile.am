# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

am_pyfsext_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pyfsext.la

nodist_pyfsext_la_SOURCES = $(BUILT_SOURCES)

pyfsext_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyfsext_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyfsext_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyfsext/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyfsext*.[ch]

distclean: clean
	/bin/rm -f Makefile

