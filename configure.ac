AC_INIT([xdrpp], [0.1], [chris@rorvick.com])
AC_CONFIG_SRCDIR([xdrpp/xdrpp.cpp])
AM_INIT_AUTOMAKE
LT_INIT

AC_PROG_CXX
AC_LANG(C++)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile xdrpp/Makefile])

AC_OUTPUT

echo \
"------------------------------------------------
${PACKAGE_NAME} Version ${PACKAGE_VERSION}

Prefix        : ${prefix}
Compiler      : ${CXX} ${CXXFLAGS} ${CPPFLAGS}
------------------------------------------------"
