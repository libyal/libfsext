#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfsext/.libs/libfsext.1.dylib && test -f ./pyfsext/.libs/pyfsext.so;
then
	install_name_tool -change /usr/local/lib/libfsext.1.dylib ${PWD}/libfsext/.libs/libfsext.1.dylib ./pyfsext/.libs/pyfsext.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

