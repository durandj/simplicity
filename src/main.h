#pragma once

#include "config.h"

#define BOOST_LOG_DYN_LINK

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

int main(int argc, char **argv);
boost::log::sources::severity_logger<boost::log::trivial::severity_level> &get_global_logger(void); // TOOD: Make const

