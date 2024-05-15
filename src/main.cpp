#include <iostream>
#include <packer/private/config.h>

#include "Packer.h"
#include "PackerArgument.h"
#include "sources/JsonPackSource.h"
#include "sinks/SqlitePackSink.h"

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

int main(int argc, char** argv)
{
	packer::PackerArgument packer_argument;

	switch (packer_argument.Parse(argc, argv))
	{
	case packer::ParseResult::ExitWithFailure:
		return EXIT_FAILURE;
	case packer::ParseResult::ExitWithSuccess:
		return EXIT_SUCCESS;
	case packer::ParseResult::Continue:	
		break;
	}

	const auto sources = get_sources();
	for (const auto& source : sources)
	{
		source->Initialize(packer_argument);
		if (!source->Validate())
		{
			std::cout << source->name() << " is not valid";
			return EXIT_FAILURE;
		}
	}

	const auto sinks = get_sinks();
	for (const auto& sink : sinks)
	{
		sink->Initialize(packer_argument);
	}

	const packer::Packer packer(sources, sinks);
	packer.Pack();

	return 0;
}