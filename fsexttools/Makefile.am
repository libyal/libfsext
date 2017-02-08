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

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	fsextinfo

fsextinfo_SOURCES = \
	fsextinfo.c \
	fsexttools_getopt.c fsexttools_getopt.h \
	fsexttools_i18n.h \
	fsexttools_libbfio.h \
	fsexttools_libcerror.h \
	fsexttools_libclocale.h \
	fsexttools_libcnotify.h \
	fsexttools_libfcache.h \
	fsexttools_libfdata.h \
	fsexttools_libfdatetime.h \
	fsexttools_libfguid.h \
	fsexttools_libfsext.h \
	fsexttools_libuna.h \
	fsexttools_output.c fsexttools_output.h \
	fsexttools_signal.c fsexttools_signal.h \
	fsexttools_unused.h \
	info_handle.c info_handle.h

fsextinfo_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on fsextinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(fsextinfo_SOURCES)

