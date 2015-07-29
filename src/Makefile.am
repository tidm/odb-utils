ACLCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CPPFLAGS = \
	--pedantic -Wall -Werror -Wno-unknown-parallel\
	$(ODB_CFLAGS) \
	$(ODB_ORACLE_CFLAGS) \
	$(OI_COMMON_CFLAGS) \
	$(OI_EXCEPTION_CFLAGS)

lib_LTLIBRARIES = liboi_odb_utils.la

liboi_odb_utils_la_SOURCES = \
    type_traits/std_chrono.hpp \
	type_traits/std_chrono_oracle.hpp \
	odb_stat.cpp \
	odb_worker.cpp \
	odb_async_worker.cpp

liboi_odb_utils_la_LDFLAGS = -version-info $(OI_ODB_UTILS_SO_VERSION)

liboi_odb_utils_la_LIBADD = \
	$(ODB_LIBS) \
	$(ODB_ORACLE_LIBS) \
	$(OI_COMMON_LIBS) \
	$(OI_EXCEPTION_LIBS) 

oi_odb_utils_includedir = $(includedir)/oi/utils/odb_utils/type_traits
oi_odb_utils_include_HEADERS = \
	type_traits/std_chrono.hpp \
	type_traits/std_chrono_oracle.hpp
