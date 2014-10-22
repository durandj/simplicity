#include "main.h"

#include <boost/asio.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <glibmm/main.h>
#include <iostream>

#include "log.h"
#include "setup.h"

namespace asio    = boost::asio;
namespace logging = boost::log;
namespace po      = boost::program_options;

using namespace simplicity;
using namespace std;

static logging::sources::severity_logger<logging::trivial::severity_level> GLOBAL_LOGGER;
static Glib::RefPtr<Glib::MainLoop> pMainLoop;

void init_logging(void);
void handler_sig(const boost::system::error_code &error, int signal_number);
void handler_sig_hup(const boost::system::error_code &error, int signal_number);
void handler_sig_int(const boost::system::error_code &error, int signal_number);
void handler_sig_term(const boost::system::error_code &error, int signal_number);
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

	global_log_trace << "Registering OS signal handlers...";
	asio::io_service io_service;
	asio::signal_set signals(io_service, SIGINT, SIGTERM, SIGHUP);
	signals.async_wait(handler_sig);

	boost::thread service_thread(boost::bind(&asio::io_service::run, &io_service));

	global_log_trace << "Starting main GLib loop";

	pMainLoop = Glib::RefPtr<Glib::MainLoop>(Glib::MainLoop::create());
	pMainLoop->run();

	io_service.stop();

	global_log_trace << "Ending main GLib loop";

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

void handler_sig(const boost::system::error_code &error, int signal_number)
{
	switch (signal_number)
	{
	case SIGHUP:
		handler_sig_hup(error, signal_number);
		break;
	case SIGINT:
		handler_sig_int(error, signal_number);
		break;
	case SIGTERM:
		handler_sig_term(error, signal_number);
		break;
	}
}

void handler_sig_hup(const boost::system::error_code &error, int signal_number)
{
}

void handler_sig_int(const boost::system::error_code &error, int signal_number)
{
	pMainLoop->quit();
}

void handler_sig_term(const boost::system::error_code &error, int signal_number)
{
	pMainLoop->quit();
}

void print_version(void)
{
	cout << PACKAGE_STRING << endl;
	cout << "Copyright (C) 2014 James Durand\n"
			"This is free software; see the source for copying conditions.\n"
			"There is NO warranty." << endl;
}

