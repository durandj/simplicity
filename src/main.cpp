#include "main.h"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char **argv)
{
	po::options_description program_desc("Simplicity window manager");

	program_desc.add_options()
		("help", "Display usage")
	;

	po::variables_map args;
	po::store(po::parse_command_line(argc, argv, program_desc), args);
	po::notify(args);

	if (args.count("help"))
	{
		cout << program_desc << endl;
		return 1;
	}

	return 0;
}
