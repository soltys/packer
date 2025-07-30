#include <packer/PackerArgument.hpp>
#include <packer/Utils.hpp>
#include <packer/private/config.hpp>
using namespace packer;

ParseResult PackerArgument::Parse(int argc, char **argv)
{
	args::ArgumentParser parser(PROJECT_DESCRIPTION);
	args::HelpFlag help_flag(parser, "help", "Display this help menu", {'h', "help"});
	args::Flag version_flag(parser, "version", "shows version and exit", {'v', "version"});
	args::PositionalList<std::string> input_file_flag(parser, "input", "input source to be processed");
	args::ValueFlag<std::string> output_file_flag(parser, "output", "output file to be processed", {'o', "output"});
	args::Flag forceFlag(parser, "force", "overwrite output file if already exists", {'f', "force"});

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
		get_version_string(std::cout);
		return ExitWithSuccess;
	}

	if (!input_file_flag)
	{
		std::cerr << "input source is empty" << std::endl;
		std::cerr << parser;
		return ExitWithFailure;
	}
	input_ = args::get(input_file_flag);
	input_type_ = parse_input_source();
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

InputType PackerArgument::parse_input_source()
{
	for (const auto &i : input_)
	{
		if (i.find("json") != std::string::npos)
		{
			return InputType::JSON;
		}
	}
	return InputType::UNKNOWN;
}