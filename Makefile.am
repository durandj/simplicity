ACLOCAL_AMFLAGS     = -I m4
AM_LDFLAGS          =  -lboost_program_options$(BOOST_LIB_SUFFIX)
bin_PROGRAMS        = simplicity
LIBS                = $(DEPS_LIBS) -stdlib=libc++
simplicity_CPPFLAGS = $(DEPS_CFLAGS)
simplicity_SOURCES  = src/main.h src/main.cpp
SUBDIRS             = \
	src

