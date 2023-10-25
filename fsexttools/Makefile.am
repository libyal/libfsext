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
	@LIBHMAC_CPPFLAGS@ \
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	fsextinfo \
	fsextmount

fsextinfo_SOURCES = \
	digest_hash.c digest_hash.h \
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
	fsexttools_libhmac.h \
	fsexttools_libuna.h \
	fsexttools_output.c fsexttools_output.h \
	fsexttools_signal.c fsexttools_signal.h \
	fsexttools_unused.h \
	info_handle.c info_handle.h

fsextinfo_LDADD = \
	@LIBHMAC_LIBADD@ \
	@LIBCRYPTO_LIBADD@ \
	@LIBDL_LIBADD@ \
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
	@LIBINTL@ \
	@PTHREAD_LIBADD@

fsextmount_SOURCES = \
	fsextmount.c \
	fsexttools_getopt.c fsexttools_getopt.h \
	fsexttools_i18n.h \
	fsexttools_libbfio.h \
	fsexttools_libcerror.h \
	fsexttools_libclocale.h \
	fsexttools_libcnotify.h \
	fsexttools_libcpath.h \
	fsexttools_libfsext.h \
	fsexttools_libuna.h \
	fsexttools_output.c fsexttools_output.h \
	fsexttools_signal.c fsexttools_signal.h \
	fsexttools_unused.h \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h

fsextmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

splint-local:
	@echo "Running splint on fsextinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(fsextinfo_SOURCES)

