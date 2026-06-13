#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfsext/.libs/libfsext.1.dylib && test -f ./pyfsext/.libs/pyfsext.so
then
	install_name_tool -change /usr/local/lib/libfsext.1.dylib ${PWD}/libfsext/.libs/libfsext.1.dylib ./pyfsext/.libs/pyfsext.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

