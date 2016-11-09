AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

TESTS = \
	test_api_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsext_test_error \
	fsext_test_support

fsext_test_error_SOURCES = \
	fsext_test_error.c \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_unused.h

fsext_test_error_LDADD = \
	../libfsext/libfsext.la

fsext_test_support_SOURCES = \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_support.c \
	fsext_test_unused.h

fsext_test_support_LDADD = \
	@LIBCERROR_LIBADD@ \
	../libfsext/libfsext.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

