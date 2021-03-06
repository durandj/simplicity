#include "main.hpp"

#include <boost/program_options.hpp>
#include <iostream>

#include "application.hpp"

namespace po = boost::program_options;

using namespace simplicity;
using namespace std;

void print_version(void);

int main(int argc, char **argv)
{
	string sDisplayName;

	po::options_description program_desc("Simplicity window manager");
	program_desc.add_options()
		("help",      "Display usage")
		("version",   "Print simplicity version")
		("display",   po::value<string>(&sDisplayName)->default_value(""), "The display name to use. 0.0 by default")
	;

	po::variables_map args;
	po::store(po::parse_command_line(argc, argv, program_desc), args);
	po::notify(args);

	if (args.count("help"))
	{
		cerr << program_desc << endl;
		return 1;
	}

	if (args.count("version"))
	{
		print_version();
		return 1;
	}

	SimplicityApplication *pApp = &SimplicityApplication::get_instance();
	pApp->initialize(sDisplayName);
	return pApp->run();
}

void print_version(void)
{
	cerr << "simplicity" << endl;
	cerr << "Copyright (C) 2014 James Durand\n"
			"This is free software; see the source for copying conditions.\n"
			"There is NO warranty." << endl;
}

