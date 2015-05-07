dnl Function to detect if libfsext dependencies are available
AC_DEFUN([AX_LIBFSEXT_CHECK_LOCAL],
 [dnl Check for internationalization functions in libfsext/libfsext_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

