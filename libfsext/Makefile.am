AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@

lib_LTLIBRARIES = libfsext.la

libfsext_la_SOURCES = \
	fsext_group_descriptor.h \
	fsext_volume_header.h \
	libfsext.c \
	libfsext_debug.c libfsext_debug.h \
	libfsext_definitions.h \
	libfsext_error.c libfsext_error.h \
	libfsext_extern.h \
	libfsext_io_handle.c libfsext_io_handle.h \
	libfsext_libbfio.h \
	libfsext_libcdata.h \
	libfsext_libcerror.h \
	libfsext_libclocale.h \
	libfsext_libcnotify.h \
	libfsext_libcstring.h \
	libfsext_libfcache.h \
	libfsext_libfdata.h \
	libfsext_libfdatetime.h \
	libfsext_libfguid.h \
	libfsext_libuna.h \
	libfsext_notify.c libfsext_notify.h \
	libfsext_support.c libfsext_support.h \
	libfsext_types.h \
	libfsext_unused.h \
	libfsext_volume.c libfsext_volume.h

libfsext_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@

libfsext_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfsext_definitions.h.in \
	libfsext.rc \
	libfsext.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libfsext_definitions.h
	/bin/rm -f libfsext.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfsext ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfsext_la_SOURCES)

