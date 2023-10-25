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
	@LIBFSEXT_DLL_EXPORT@

lib_LTLIBRARIES = libfsext.la

libfsext_la_SOURCES = \
	fsext_attributes.h \
	fsext_directory_entry.h \
	fsext_extents.h \
	fsext_inode.h \
	fsext_group_descriptor.h \
	fsext_superblock.h \
	libfsext.c \
	libfsext_attributes_block.c libfsext_attributes_block.h \
	libfsext_attribute_values.c libfsext_attribute_values.h \
	libfsext_bitmap.c libfsext_bitmap.h \
	libfsext_block.c libfsext_block.h \
	libfsext_block_data_handle.c libfsext_block_data_handle.h \
	libfsext_block_stream.c libfsext_block_stream.h \
	libfsext_block_vector.c libfsext_block_vector.h \
	libfsext_buffer_data_handle.c libfsext_buffer_data_handle.h \
	libfsext_data_blocks.c libfsext_data_blocks.h \
	libfsext_debug.c libfsext_debug.h \
	libfsext_definitions.h \
	libfsext_directory.c libfsext_directory.h \
	libfsext_directory_entry.c libfsext_directory_entry.h \
	libfsext_error.c libfsext_error.h \
	libfsext_extended_attribute.c libfsext_extended_attribute.h \
	libfsext_extent.c libfsext_extent.h \
	libfsext_extent_index.c libfsext_extent_index.h \
	libfsext_extents.c libfsext_extents.h \
	libfsext_extents_header.c libfsext_extents_header.h \
	libfsext_extents_footer.c libfsext_extents_footer.h \
	libfsext_extern.h \
	libfsext_file_entry.c libfsext_file_entry.h \
	libfsext_group_descriptor.c libfsext_group_descriptor.h \
	libfsext_inode.c libfsext_inode.h \
	libfsext_inode_table.c libfsext_inode_table.h \
	libfsext_io_handle.c libfsext_io_handle.h \
	libfsext_libbfio.h \
	libfsext_libcdata.h \
	libfsext_libcerror.h \
	libfsext_libclocale.h \
	libfsext_libcnotify.h \
	libfsext_libcthreads.h \
	libfsext_libfcache.h \
	libfsext_libfdata.h \
	libfsext_libfdatetime.h \
	libfsext_libfguid.h \
	libfsext_libuna.h \
	libfsext_notify.c libfsext_notify.h \
	libfsext_superblock.c libfsext_superblock.h \
	libfsext_support.c libfsext_support.h \
	libfsext_types.h \
	libfsext_unused.h \
	libfsext_volume.c libfsext_volume.h

libfsext_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
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
	@LIBFGUID_LIBADD@ \
	@PTHREAD_LIBADD@

libfsext_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfsext_definitions.h.in \
	libfsext.rc \
	libfsext.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfsext_definitions.h
	-rm -f libfsext.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libfsext ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfsext_la_SOURCES)

