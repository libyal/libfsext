AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBHMAC_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFSEXT_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYFSEXT = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_fsextinfo.sh \
	$(TESTS_PYFSEXT)

check_SCRIPTS = \
	pyfsext_test_support.py \
	pyfsext_test_volume.py \
	test_fsextinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fsext_test_attribute_values \
	fsext_test_bitmap \
	fsext_test_block \
	fsext_test_block_data_handle \
	fsext_test_block_vector \
	fsext_test_buffer_data_handle \
	fsext_test_directory \
	fsext_test_directory_entry \
	fsext_test_error \
	fsext_test_extended_attribute \
	fsext_test_extent \
	fsext_test_extent_index \
	fsext_test_extents_footer \
	fsext_test_extents_header \
	fsext_test_file_entry \
	fsext_test_group_descriptor \
	fsext_test_inode \
	fsext_test_inode_table \
	fsext_test_io_handle \
	fsext_test_notify \
	fsext_test_superblock \
	fsext_test_support \
	fsext_test_tools_info_handle \
	fsext_test_tools_output \
	fsext_test_tools_signal \
	fsext_test_volume

fsext_test_attribute_values_SOURCES = \
	fsext_test_attribute_values.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_attribute_values_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_bitmap_SOURCES = \
	fsext_test_bitmap.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
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
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
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

fsext_test_block_data_handle_SOURCES = \
	fsext_test_block_data_handle.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_block_data_handle_LDADD = \
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
	fsext_test_libclocale.h \
	fsext_test_libfcache.h \
	fsext_test_libfdata.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
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

fsext_test_buffer_data_handle_SOURCES = \
	fsext_test_buffer_data_handle.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_buffer_data_handle_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_directory_SOURCES = \
	fsext_test_directory.c \
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
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

fsext_test_extended_attribute_SOURCES = \
	fsext_test_extended_attribute.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_extended_attribute_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

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

fsext_test_extent_index_SOURCES = \
	fsext_test_extent_index.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_extent_index_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_extents_footer_SOURCES = \
	fsext_test_extents_footer.c \
	fsext_test_libcerror.h \
	fsext_test_libfsext.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_extents_footer_LDADD = \
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
	fsext_test_functions.c fsext_test_functions.h \
	fsext_test_libbfio.h \
	fsext_test_group_descriptor.c \
	fsext_test_libcerror.h \
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_unused.h

fsext_test_group_descriptor_LDADD = \
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
	fsext_test_libclocale.h \
	fsext_test_libfsext.h \
	fsext_test_libuna.h \
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

fsext_test_tools_info_handle_SOURCES = \
	../fsexttools/digest_hash.c ../fsexttools/digest_hash.h \
	../fsexttools/info_handle.c ../fsexttools/info_handle.h \
	fsext_test_libcerror.h \
	fsext_test_macros.h \
	fsext_test_memory.c fsext_test_memory.h \
	fsext_test_tools_info_handle.c \
	fsext_test_unused.h

fsext_test_tools_info_handle_LDADD = \
	@LIBHMAC_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
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
	@LIBCRYPTO_LIBADD@ \
	@LIBDL_LIBADD@

fsext_test_tools_output_SOURCES = \
	../fsexttools/fsexttools_output.c ../fsexttools/fsexttools_output.h \
	fsext_test_libcerror.h \
	fsext_test_macros.h \
	fsext_test_tools_output.c \
	fsext_test_unused.h

fsext_test_tools_output_LDADD = \
	../libfsext/libfsext.la \
	@LIBCERROR_LIBADD@

fsext_test_tools_signal_SOURCES = \
	../fsexttools/fsexttools_signal.c ../fsexttools/fsexttools_signal.h \
	fsext_test_libcerror.h \
	fsext_test_macros.h \
	fsext_test_tools_signal.c \
	fsext_test_unused.h

fsext_test_tools_signal_LDADD = \
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
	-rm -f Makefile

