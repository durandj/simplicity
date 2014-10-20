#include "main.h"

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/program_options.hpp>
#include <glibmm/main.h>
#include <iostream>

namespace logging = boost::log;
namespace po      = boost::program_options;
using namespace std;

static logging::sources::severity_logger<logging::trivial::severity_level> GLOBAL_LOGGER;

void init_logging(void);
void print_version(void);

int main(int argc, char **argv)
{
	po::options_description program_desc("Simplicity window manager");

	program_desc.add_options()
		("help",    "Display usage")
		("version", "Print simplicity version")
	;

	po::variables_map args;
	po::store(po::parse_command_line(argc, argv, program_desc), args);
	po::notify(args);

	if (args.count("help"))
	{
		cout << program_desc << endl;
		return 1;
	}

	if (args.count("version"))
	{
		print_version();
		return 1;
	}

	init_logging();

	BOOST_LOG_SEV(GLOBAL_LOGGER, logging::trivial::debug) << "Starting main GLib loop";

	Glib::RefPtr<Glib::MainLoop> pMainLoop(Glib::MainLoop::create());
	pMainLoop->run();
	pMainLoop->quit();

	BOOST_LOG_SEV(GLOBAL_LOGGER, logging::trivial::debug) << "Ending main GLib loop";

	return 0;
}

logging::sources::severity_logger<logging::trivial::severity_level> &get_global_logger(void)
{
	return GLOBAL_LOGGER;
}

void init_logging(void)
{
	logging::add_common_attributes();

	logging::add_console_log(
		cout,
		logging::keywords::format = (
			logging::expressions::stream
				<< "(" << logging::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") << ") "
				<< "[" << logging::trivial::severity << "]: "
				<< logging::expressions::smessage
		),
		logging::keywords::auto_flush = true
	);
}

void print_version(void)
{
	cout << PACKAGE_STRING << endl;
	cout << "Copyright (C) 2014 James Durand\n"
			"This is free software; see the source for copying conditions.\n"
			"There is NO warranty." << endl;
}
