#pragma once

#include <boost/log/trivial.hpp>

#include "main.h"

#define log_trace(logger)   BOOST_LOG_SEV(logger, boost::log::trivial::trace)
#define log_debug(logger)   BOOST_LOG_SEV(logger, boost::log::trivial::debug)
#define log_info(logger)    BOOST_LOG_SEV(logger, boost::log::trivial::info)
#define log_warning(logger) BOOST_LOG_SEV(logger, boost::log::trivial::warning)
#define log_error(logger)   BOOST_LOG_SEV(logger, boost::log::trivial::error)

#define global_log_trace   log_trace(get_global_logger())
#define global_log_debug   log_debug(get_global_logger())
#define global_log_info    log_info(get_global_logger())
#define global_log_warning log_warning(get_global_logger())
#define global_log_error   log_error(get_global_logger())

