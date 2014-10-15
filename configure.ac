#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

m4_define([simplicity_version_major], [0])
m4_define([simplicity_version_minor], [0])
m4_define([simplicity_version_patch], [0])
m4_define([simplicity_version_build], [0]) # TODO: auto replace this

m4_define(
	[simplicity_version],
	[simplicity_version_major.simplicity_version_minor.simplicity_version_patch.simplicity_version_build])

AC_INIT(
	[simplicity],
	[simplicity_version],
	[https://github.com/durandj/simplicity],
	[simplicity],
	[https://github.com/durandj/simplicity])

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.14.1 no-dist-gzip dist-xz])
AC_CONFIG_FILES([
	Makefile
	src/Makefile])

GETTEXT_PACKAGE=simplicity
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Package name for gettext]])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_HEADER_STDC
AX_BOOST_BASE
AX_BOOST_PROGRAM_OPTIONS

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT

