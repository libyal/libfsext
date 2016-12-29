AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsext_test_error \
	fsext_test_io_handle \
	fsext_test_notify \
	fsext_test_support \
	fsext_test_volume

fsext_test_error_SOURCES = \
	fsext_test_error.c \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_unused.h

fsext_test_error_LDADD = \
	../libfsext/libfsext.la

fsext_test_io_handle_SOURCES = \
	fsext_test_io_handle.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_io_handle_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_notify_SOURCES = \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_notify.c \
	fsext_test_unused.h

fsext_test_notify_LDADD = \
	../libfsext/libfsext.la

fsext_test_support_SOURCES = \
	fsext_test_getopt.c fsext_test_getopt.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libcnotify.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_support.c

fsext_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_volume_SOURCES = \
	fsext_test_getopt.c fsext_test_getopt.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libcnotify.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_volume.c

fsext_test_volume_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

