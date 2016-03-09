AC_PREREQ(2.69)

AC_INIT([forex], [1.0])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11

#fxcm checks
AC_CHECK_LIB([ForexConnect],[getenv],[],[AC_MSG_ERROR([Please install fxcm-connect-api from http://www.fxcodebase.com/wiki/index.php/Download])])
AC_CHECK_LIB([pdas],[getenv],[],[AC_MSG_ERROR([Please install fxcm-connect-api from http://www.fxcodebase.com/wiki/index.php/Download])])
AC_CHECK_HEADER([ForexConnect.h],[],[AC_MSG_ERROR([Please install fxcm-connect-api headers from http://www.fxcodebase.com/wiki/index.php/Download])])

#boost checks
AX_BOOST_BASE([1.59.0])
AX_BOOST_DATE_TIME
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_TEST_EXEC_MONITOR

#add boost flags
AM_CPPFLAGS="$AM_CPPFLAGS $BOOST_CPPFLAGS"
AM_LDFLAGS="$AM_LDFLAGS $BOOST_DATE_TIME_LIB $BOOST_SYSTEM_LIB $BOOST_THREAD_LIB"
AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_LDFLAGS])

#glog checks
AC_CHECK_LIB([glog],[openlog],[],[AC_MSG_ERROR([Please install glog from https://github.com/google/glog])])

#gflags checks
AC_CHECK_LIB([gflags],[getenv],[],AC_MSG_ERROR(
             [Please install gflags library https://github.com/gflags/gflags ]))

#folly check
AC_CHECK_LIB([folly],[getenv],[],[AC_MSG_ERROR([Please install folly from https://github.com/facebook/folly])])

#wangle
AC_CHECK_LIB([wangle], [getenv], [], [AC_MSG_ERROR(
  [Please install wangle library https://github.com/facebook/wangle])])

#voltdb-client
AC_CHECK_HEADER([Client.h],[],[AC_MSG_ERROR([Please install voltdb-client headers from https://github.com/VoltDB/voltdb-client-cpp under voltdb-client])])
AC_CHECK_LIB([voltdbcpp],[getenv],[],[AC_MSG_ERROR([Please install voltdbcpp lib from https://github.com/VoltDB/voltdb-client-cpp])])
AC_CHECK_LIB([event],[event_set],[],[AC_MSG_ERROR([Please install all dependencies for voltdb-client from https://github.com/VoltDB/voltdb-client-cpp])])
AC_CHECK_LIB([event_pthreads],[evthread_use_pthreads],[],[AC_MSG_ERROR([Please install all dependencies for voltdb-client from https://github.com/VoltDB/voltdb-client-cpp])])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

