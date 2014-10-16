#include "main.h"

#include <boost/program_options.hpp>
#include <glibmm/main.h>
#include <iostream>

namespace po = boost::program_options;
using namespace std;

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

	Glib::RefPtr<Glib::MainLoop> pMainLoop(Glib::MainLoop::create());
	pMainLoop->run();
	pMainLoop->quit();

	return 0;
}

void print_version(void)
{
	cout << PACKAGE_STRING << endl;
	cout << "Copyright (C) 2014 James Durand\n"
			"This is free software; see the source for copying conditions.\n"
			"There is NO warranty." << endl;
}

