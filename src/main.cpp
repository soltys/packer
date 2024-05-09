#include <iostream>
#include <packer/private/config.h>

#include "Packer.h"
#include "PackerArgument.h"
#include "JsonPackSource.h"
#include "SqlitePackSink.h"

packer::SourceCollection get_sources()
{
	packer::SourceCollection sources;
	sources.push_back(std::make_unique<packer::JsonPackSource>());
	return sources;
}

packer::SinkCollection get_sinks()
{
	packer::SinkCollection sinks;
	sinks.push_back(std::make_unique<packer::SqlitePackSink>());
	return sinks;
}

int main(int argc, char** argv) {


	packer::PackerArgument packer_argument;
	if (packer_argument.Parse(argc, argv) != 0)
	{
		packer_argument.PrintHelp();
		return EXIT_FAILURE;
	}

	if (packer_argument.input_file().empty())
	{
		std::cerr << "input file is empty" << std::endl;
	}

	if (packer_argument.is_help_set()) {
		packer_argument.PrintHelp();
		return EXIT_SUCCESS;
	}
	if (packer_argument.is_version_set())
	{
		std::cout << "packer version " << PROJECT_VERSION << std::endl;
		return EXIT_SUCCESS;
	}

	const auto sources = get_sources();
	for (const auto& source : sources)
	{
		source->Initialize(packer_argument);
		if(!source->Validate())
		{
			std::cout << source->name() << " is not valid";
			return EXIT_FAILURE;
		}
	}

	const auto sinks = get_sinks();
	for(const auto& sink: sinks)
	{
		sink->Initialize(packer_argument);
	}


	packer::Packer packer(sources, sinks);
	packer.Pack();


	std::cout << "Hello World!";
	return 0;
}