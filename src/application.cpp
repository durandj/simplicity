#include "application.hpp"

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <iostream>
#include <cstdlib>

#include "log.hpp"

namespace asio    = boost::asio;
namespace logging = boost::log;

namespace simplicity
{
	bool check_xcb_connection(xcb_connection_t *pConnection);

	const string SimplicityApplication::ENV_VAR_DISPLAY_NAME = "DISPLAY";

	SimplicityApplication &SimplicityApplication::get_instance(void)
	{
		static SimplicityApplication singleton;

		return singleton;
	}

	SimplicityApplication::SimplicityApplication(void) :
		m_bRunning(false),
		m_pXConnection(nullptr),
		m_GlobalLogger(),
		m_IOService(),
		m_Signals(m_IOService, SIGINT, SIGTERM, SIGHUP),
		m_sDisplayName("")
	{
		initialize();

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

	bool SimplicityApplication::run(void)
	{
		global_log_trace << "Starting main application loop";

		int nScreenNum = 0;
		m_pXConnection = xcb_connect(m_sDisplayName.c_str(), &nScreenNum);

		if (check_xcb_connection(m_pXConnection))
		{
			xcb_disconnect(m_pXConnection);
			return 1;
		}

		xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(m_pXConnection));
		for (int i = 0; i != nScreenNum; i++)
			xcb_screen_next(&iter);

		m_pRootScreen = iter.data;
		if (m_pRootScreen == nullptr)
		{
			global_log_error << "Could not get the current screen. Exiting";
			xcb_disconnect(m_pXConnection);
			return 1;
		}

		global_log_debug << "Root screen dimensions: "
						 << m_pRootScreen->width_in_pixels
						 << "x"
						 << m_pRootScreen->height_in_pixels
						 << "Root window: "
						 << m_pRootScreen->root;

		xcb_generic_event_t *pEvent;

		m_bRunning = true;
		while (m_bRunning && (pEvent = xcb_wait_for_event(m_pXConnection)))
		{
			delete pEvent; // TODO: necessary?
		}

		if (m_bRunning && pEvent == nullptr)
			global_log_error << "A fatal error occurred";

		xcb_disconnect(m_pXConnection);

		return 0;
	}

	void SimplicityApplication::quit(void)
	{
		global_log_trace << "Ending main application loop";

		m_bRunning = false;
		m_IOService.stop();
	}

	string SimplicityApplication::get_display_name(void) const
	{
		return m_sDisplayName;
	}

	void SimplicityApplication::set_display_name(string sDisplay)
	{
		if (sDisplay.empty())
		{
			char *pEnvVar = std::getenv(SimplicityApplication::ENV_VAR_DISPLAY_NAME.c_str());
			if (pEnvVar)
				m_sDisplayName = pEnvVar;
			else
				m_sDisplayName = ":0.0";

			global_log_trace << "No display set. Defaulting to " << m_sDisplayName;
		}
		else
		{
			m_sDisplayName = sDisplay;

			global_log_trace << "Display set to " << sDisplay;
		}

		putenv((char *)(SimplicityApplication::ENV_VAR_DISPLAY_NAME + "=" + m_sDisplayName).c_str());
	}

	void SimplicityApplication::handler_sig(const boost::system::error_code &error, int nSignal)
	{
		global_log_trace << "Received OS signal: " << nSignal;

		switch (nSignal)
		{
		case SIGHUP:
			global_log_trace << "Received OS SIGHUP";
			handler_sig_hup(error, nSignal);
			break;
		case SIGINT:
			global_log_trace << "Received OS SIGINT";
			handler_sig_int(error, nSignal);
			return;
		case SIGTERM:
			global_log_trace << "Received OS SIGTERM";
			handler_sig_term(error, nSignal);
			return;
		default:
			global_log_debug << "Unhandled signal: " << nSignal;
		}

		m_Signals.async_wait(boost::bind(&SimplicityApplication::handler_sig, this, _1, _2));
	}

	xcb_atom_t SimplicityApplication::get_atom(string sAtomName)
	{
		xcb_intern_atom_cookie_t xcbCookie = xcb_intern_atom(
			m_pXConnection,
			0,
			sAtomName.length(),
			sAtomName.c_str()
		);

		xcb_intern_atom_reply_t *pxcbReply = xcb_intern_atom_reply(
			m_pXConnection,
			xcbCookie,
			NULL
		);

		if (pxcbReply == nullptr)
			return 0;

		xcb_atom_t xcbAtom = pxcbReply->atom;
		delete pxcbReply;

		return xcbAtom;
	}

	void SimplicityApplication::initialize(void)
	{
		initialize_logging();
	}

	void SimplicityApplication::initialize_logging(void)
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

	void SimplicityApplication::handler_sig_hup(const boost::system::error_code &error, int nSignal)
	{
		// TODO: reload config

		global_log_debug << "SIGHUP received";
	}

	void SimplicityApplication::handler_sig_int(const boost::system::error_code &error, int nSignal)
	{
		quit();
	}

	void SimplicityApplication::handler_sig_term(const boost::system::error_code &error, int nSignal)
	{
		quit();
	}

	bool check_xcb_connection(xcb_connection_t *pConnection)
	{
		switch (xcb_connection_has_error(pConnection))
		{
		case XCB_CONN_ERROR:
			global_log_error << "Socket, pipe, or stream error prevented connetion to X server";
			return true;
		case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
			global_log_error << "Extension not supported. Could not connect to X server";
			return true;
		case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
			global_log_error << "Not enough memory. Could not connect to X server";
			return true;
		case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
			global_log_error << "Exceeded request length. Could not connect to X server";
			return true;
		case XCB_CONN_CLOSED_PARSE_ERR:
			global_log_error << "Could not parse display string. Could not connect to X server";
			return true;
		case XCB_CONN_CLOSED_INVALID_SCREEN:
			global_log_error << "Could not connect to X server because an invalid screen was selected";
			return true;
		default:
			return false;
		}
	}
}

