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
	/bin/rm -f libfsext.h
	/bin/rm -f libfsext/definitions.h
	/bin/rm -f libfsext/features.h
	/bin/rm -f libfsext/types.h
	/bin/rm -f Makefile

