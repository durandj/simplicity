#include "application.h"

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <iostream>

#include "log.h"

namespace asio    = boost::asio;
namespace logging = boost::log;

namespace simplicity
{
	SimplicityApplication &SimplicityApplication::get_instance(void)
	{
		static SimplicityApplication singleton;

		return singleton;
	}

	SimplicityApplication::SimplicityApplication(void) :
		m_GlobalLogger(),
		m_IOService(),
		m_Signals(m_IOService, SIGINT, SIGTERM, SIGHUP),
		m_pMainLoop(Glib::MainLoop::create())
	{
		initialize_logging();

		m_Signals.async_wait(boost::bind(&SimplicityApplication::handler_sig, this, _1, _2));

		m_ServiceThread = boost::thread(boost::bind(&asio::io_service::run, &m_IOService));
	}

	SimplicityApplication::~SimplicityApplication(void)
	{
		global_log_trace << "Destroying application singleton";
	}

	logging::sources::severity_logger<logging::trivial::severity_level> &SimplicityApplication::get_global_logger(void)
	{
		return m_GlobalLogger;
	}

	void SimplicityApplication::run(void)
	{
		global_log_trace << "Starting main GLib loop";

		m_pMainLoop->run();
	}

	void SimplicityApplication::quit(void)
	{
		global_log_trace << "Ending main GLib loop";

		m_pMainLoop->quit();
		m_IOService.stop();
	}

	void SimplicityApplication::handler_sig(const boost::system::error_code &error, int signal_number)
	{
		global_log_trace << "Received OS signal: " << signal_number;

		switch (signal_number)
		{
		case SIGHUP:
			handler_sig_hup(error, signal_number);
			break;
		case SIGINT:
			handler_sig_int(error, signal_number);
			return;
		case SIGTERM:
			handler_sig_term(error, signal_number);
			return;
		default:
			global_log_debug << "Unhandled signal: " << signal_number;
		}

		m_Signals.async_wait(boost::bind(&SimplicityApplication::handler_sig, this, _1, _2));
	}

	void SimplicityApplication::SimplicityApplication::initialize_logging(void)
	{
		logging::add_common_attributes();

		logging::add_console_log(
			std::cerr,
			logging::keywords::format = (
				logging::expressions::stream
					<< "(" << logging::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M%S") << ") "
					<< "[" << logging::trivial::severity << "]: "
					<< logging::expressions::smessage
			),
			logging::keywords::auto_flush = true
		);
	}

	void SimplicityApplication::handler_sig_hup(const boost::system::error_code &error, int signal_number)
	{
		// TODO: reload config

		global_log_debug << "SIGHUP received";
	}

	void SimplicityApplication::handler_sig_int(const boost::system::error_code &error, int signal_number)
	{
		quit();
	}

	void SimplicityApplication::handler_sig_term(const boost::system::error_code &error, int signal_number)
	{
		quit();
	}
}

