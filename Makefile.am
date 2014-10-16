ACLOCAL_AMFLAGS     = -I m4
AM_LDFLAGS          =  -lboost_program_options$(BOOST_LIB_SUFFIX)
bin_PROGRAMS        = simplicity
simplicity_CPPFLAGS = $(DEPS_CFLAGS)
simplicity_LIBS     = $(DEPS_LIBS)
simplicity_SOURCES  = src/main.h src/main.cpp
SUBDIRS             = \
	src

