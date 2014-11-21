#pragma once

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <glibmm.h>

#include "config.h"
#include "setup.h"

namespace simplicity
{
	class SimplicityApplication
	{
	private:
		boost::log::sources::severity_logger<boost::log::trivial::severity_level> m_GlobalLogger;
		boost::asio::io_service m_IOService;
		boost::asio::signal_set m_Signals;
		boost::thread m_ServiceThread;
		Glib::RefPtr<Glib::MainLoop> m_pMainLoop;
		string m_sDisplayName;

		SimplicityApplication(void);

		void initialize_logging(void);
		void handler_sig_hup(const boost::system::error_code &error, int signal_number);
		void handler_sig_int(const boost::system::error_code &error, int signal_number);
		void handler_sig_term(const boost::system::error_code &error, int signal_number);

	public:
		static const char *ENV_VAR_DISPLAY_NAME;

		static SimplicityApplication &get_instance(void);

		~SimplicityApplication(void);
		boost::log::sources::severity_logger<boost::log::trivial::severity_level> &get_global_logger(void);
		void run(void);
		void quit(void);
		string get_display_name(void) const;
		void set_display_name(string sDisplay);
		void handler_sig(const boost::system::error_code &error, int signal_number);
	};
}

