AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYFSEXT = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_fsextinfo.sh \
	$(TESTS_PYFSEXT)

check_SCRIPTS = \
	pyfsext_test_support.py \
	test_fsextinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsext_test_bitmap \
	fsext_test_block \
	fsext_test_block_vector \
	fsext_test_directory \
	fsext_test_directory_entry \
	fsext_test_error \
	fsext_test_extent \
	fsext_test_extents_header \
	fsext_test_file_entry \
	fsext_test_group_descriptor \
	fsext_test_inode \
	fsext_test_inode_table \
	fsext_test_io_handle \
	fsext_test_notify \
	fsext_test_superblock \
	fsext_test_support \
	fsext_test_volume

fsext_test_bitmap_SOURCES = \
	fsext_test_bitmap.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_bitmap_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_block_SOURCES = \
	fsext_test_block.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_block_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_block_vector_SOURCES = \
	fsext_test_block_vector.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libfcache.h \
	fsext_test_libfdata.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_block_vector_LDADD = \
	@LIBFDATA_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_directory_SOURCES = \
	fsext_test_directory.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_directory_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_directory_entry_SOURCES = \
	fsext_test_directory_entry.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_directory_entry_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_error_SOURCES = \
	fsext_test_error.c \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_unused.h

fsext_test_error_LDADD = \
	../libfsext/libfsext.la

fsext_test_extent_SOURCES = \
	fsext_test_extent.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_extent_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_extents_header_SOURCES = \
	fsext_test_extents_header.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_extents_header_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_file_entry_SOURCES = \
	fsext_test_file_entry.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_file_entry_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_group_descriptor_SOURCES = \
	fsext_test_group_descriptor.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_group_descriptor_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_inode_SOURCES = \
	fsext_test_inode.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_inode_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_inode_table_SOURCES = \
	fsext_test_inode_table.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_inode_table_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

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
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_notify.c \
	fsext_test_unused.h

fsext_test_notify_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_superblock_SOURCES = \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_superblock.c \
	fsext_test_unused.h

fsext_test_superblock_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_support_SOURCES = \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_getopt.c fsext_test_getopt.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libcnotify.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_support.c \
	fsext_test_unused.h

fsext_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_volume_SOURCES = \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_getopt.c fsext_test_getopt.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libcnotify.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_volume.c \
	fsext_test_unused.h

fsext_test_volume_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
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

