include_HEADERS = \
	libfsext.h

pkginclude_HEADERS = \
	libfsext/codepage.h \
	libfsext/definitions.h \
	libfsext/error.h \
	libfsext/extern.h \
	libfsext/features.h \
	libfsext/types.h

EXTRA_DIST = \
	libfsext.h.in \
	libfsext/definitions.h.in \
	libfsext/features.h.in \
	libfsext/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfsext.h
	-rm -f libfsext/definitions.h
	-rm -f libfsext/features.h
	-rm -f libfsext/types.h
	-rm -f Makefile

