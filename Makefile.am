ACLOCAL_AMFLAGS     = -I m4
AM_LDFLAGS          = -lboost_date_time$(BOOST_LIB_SUFFIX) -lboost_log$(BOOST_LIB_SUFFIX) -lboost_log_setup$(BOOST_LIB_SUFFIX) -lboost_program_options$(BOOST_LIB_SUFFIX) -lboost_system$(BOOST_LIB_SUFFIX) -lboost_thread$(BOOST_LIB_SUFFIX)
bin_PROGRAMS        = simplicity
LIBS                = -stdlib=libc++ $(DEPS_LIBS)
simplicity_CPPFLAGS = $(DEPS_CFLAGS)
simplicity_SOURCES  = src/main.h src/main.cpp src/application.h src/application.cpp
SUBDIRS             = \
	src

