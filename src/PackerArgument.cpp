#include "PackerArgument.h"
#include <packer/private/config.hpp>
using namespace packer;

ParseResult PackerArgument::Parse(int argc, char** argv)
{
	args::ArgumentParser parser(PROJECT_DESCRIPTION);
	args::HelpFlag help_flag(parser, "help", "Display this help menu", { 'h', "help" });
	args::Flag version_flag(parser, "version", "shows version and exit", { 'v', "version" });
	args::ValueFlag<std::string> input_file_flag(parser, "input", "input file to be processed", { 'i',"input" });
	args::ValueFlag<std::string> output_file_flag(parser, "output", "output file to be processed", { 'o',"output" });
	args::Flag forceFlag(parser, "force", "overwrite output file if already exists", { 'f',"force" });

	try
	{
		parser.ParseCLI(argc, argv);
	}
	catch (args::Help)
	{
		std::cout << parser;
		return ExitWithSuccess;
	}
	catch (args::ParseError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return ExitWithFailure;
	}
	catch (args::ValidationError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return ExitWithFailure;
	}

	if (version_flag)
	{
		std::cout << "packer version " << PROJECT_VERSION << " " << PROJECT_VERSION_SHA1 << std::endl;
		return ExitWithSuccess;
	}

	if (!input_file_flag)
	{
		std::cerr << "input file is empty" << std::endl;
		std::cerr << parser;
		return ExitWithFailure;
	}
	input_file_ = args::get(input_file_flag);

	if (!output_file_flag)
	{
		std::cerr << "output file name is empty" << std::endl;
		std::cerr << parser;
		return ExitWithFailure;
	}
	output_file_ = args::get(output_file_flag);
	
	force_ = args::get(forceFlag);

	return Continue;
}