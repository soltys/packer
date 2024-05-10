#include "PackerArgument.h"

using namespace packer;

PackerArgument::PackerArgument()
{	
	flags.Var(input_file_, 'i', std::string("input"), std::string(""), std::string("input file to be processed"));
	flags.Var(output_file_, 'o', std::string("output"), std::string(""), std::string("output pack file"));
	flags.Var(base_path_, 'b', std::string("base-path"), std::string(""), std::string("base path"));
	flags.Bool(help_, 'h', "help", "show this help and exit");
	flags.Bool(version_, 'v', "version", "shows version and exit");
	flags.Bool(force_, 'f', "force", "overwrite output file if already exists");
}
int PackerArgument::Parse(int argc, char** argv)
{
	this->program_name = argv[0];
	if (!flags.Parse(argc, argv))
	{
		flags.PrintHelp(this->program_name.c_str());
		return 1;
	}

	return 0;
}

void PackerArgument::PrintHelp()
{
	flags.PrintHelp(this->program_name.c_str());
}