AC_INIT([newton], [2.0], [joakomusanti@gmail.com])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

CXXFLAGS="$CXXFLAGS -std=c++0x -Wall -g"

AC_PROG_CXX
AC_PROG_CXXCPP

AM_INIT_AUTOMAKE([1.12])

AC_LANG([C++])

AC_HEADER_STDC
AC_CHECK_HEADER([iostream], [], [AC_MSG_ERROR([iostream is not present])])
AC_CHECK_HEADER([string], [], [AC_MSG_ERROR([string is not present])])
AC_CHECK_HEADER([vector], [], [AC_MSG_ERROR([vector is not present])])
AC_CHECK_HEADER([fstream], [], [AC_MSG_ERROR([fstream is not present])])
AC_CHECK_HEADER([algorithm], [], [AC_MSG_ERROR([algorithm is not present])])
AC_CHECK_HEADER([sstream], [], [AC_MSG_ERROR([sstream is not present])])
AC_CHECK_HEADER([cmath], [], [AC_MSG_ERROR([cmath is not present])])
AC_CHECK_HEADER([boost/thread/thread.hpp], [], [AC_MSG_ERROR([boost/thread/thread.hpp is not present])])
AC_CHECK_HEADER([GL/glfw.h], [], [AC_MSG_ERROR([GL/glfw.h is not present])])

AC_CONFIG_HEADERS([src/config.h])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT
