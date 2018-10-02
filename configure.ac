AC_PREREQ([2.67])
AC_INIT([liboi-odb-utils], [7.0.0], [oi@tidm.ir])
LT_INIT
LT_LANG([C++])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

PKG_CHECK_MODULES([ODB], [libodb >= 2.4])
PKG_CHECK_MODULES([ODB_ORACLE], [libodb-oracle >= 2.4])
PKG_CHECK_MODULES([ODB_BOOST], [libodb-boost >= 2.4])
PKG_CHECK_MODULES([OI_COMMON], [oi_common >= 7.1])
PKG_CHECK_MODULES([OI_EXCEPTION], [oi_exception >= 7.0])

AC_CONFIG_FILES([Makefile
                src/Makefile
                test/Makefile
                oi_odb_utils.pc])

AC_SUBST([OI_ODB_UTILS_SO_VERSION], [7:0:0])
AC_SUBST([OI_ODB_UTILS_API_VERSION], [7.0.0])

AC_OUTPUT
