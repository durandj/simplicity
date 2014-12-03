#pragma once

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <xcb/xcb.h>

#include "config.hpp"
#include "setup.hpp"

namespace simplicity
{
	class SimplicityApplication
	{
	private:
		bool m_bRunning;
		xcb_connection_t *m_pXConnection;
		xcb_screen_t *m_pRootScreen;
		boost::log::sources::severity_logger<boost::log::trivial::severity_level> m_GlobalLogger;
		boost::asio::io_service m_IOService;
		boost::asio::signal_set m_Signals;
		boost::thread m_ServiceThread;
		string m_sDisplayName;

		SimplicityApplication(void);

		void initialize(void);
		void initialize_logging(void);
		void handler_sig_hup(const boost::system::error_code &error, int nSignal);
		void handler_sig_int(const boost::system::error_code &error, int nSignal);
		void handler_sig_term(const boost::system::error_code &error, int nSignal);

	public:
		static const string ENV_VAR_DISPLAY_NAME;

		static SimplicityApplication &get_instance(void);

		~SimplicityApplication(void);
		boost::log::sources::severity_logger<boost::log::trivial::severity_level> &get_global_logger(void);
		bool run(void);
		void quit(void);
		string get_display_name(void) const;
		void set_display_name(string sDisplay);
		void handler_sig(const boost::system::error_code &error, int nSignal);
		xcb_atom_t get_atom(string sAtomName);
	};
}

