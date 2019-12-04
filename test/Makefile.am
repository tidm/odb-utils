ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CFLAGS = --pedantic
AM_CXXFLAGS = --pedantic
AM_CPPFLAGS = -I../src/ -Wall -Werror -Wno-unknown-pragmas\
    $(OI_EXCEPTION_CFLAGS) \
	$(OI_COMMON_CFLAGS) \
	$(ODB_CFLAGS) \
	$(ODB_ORACLE_CFLAGS) \
	$(BOOST_SYSTEM_CFLAGS)


LDADD=../src/.libs/liboi_odb_utils.la \
	$(ODB_LIBS) \
	$(ODB_ORACLE_LIBS) \
	$(OI_COMMON_LIBS) \
	$(OI_EXCEPTION_LIBS) \
	$(BOOST_SYSTEM_LIBS)

check_PROGRAMS = test_post_callback blocking_mode blocking_small_tbs blocking_small_tbs_drop_failed
test_post_callback_SOURCES= test_post_handler.cpp student-odb.cxx
blocking_mode_SOURCES = blocking_mode.cpp req_agent_odb.cpp  db_util.cpp
blocking_small_tbs_SOURCES = blocking_small_tbs.cpp req_agent_odb.cpp db_util.cpp
blocking_small_tbs_drop_failed_SOURCES = blocking_small_tbs_drop_failed.cpp req_agent_odb.cpp  db_util.cpp

TESTS = $(check_PROGRAMS)
#TESTS = test_post_callback

