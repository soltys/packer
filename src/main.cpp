#include <iostream>

#include <packer/Packer.hpp>
#include <packer/PackerArgument.hpp>
#include <packer/Factory.hpp>

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

	const auto sources = packer::get_sources(packer_argument);
	for (const auto& source : sources)
	{
		source->Initialize(packer_argument);
		if (!source->Validate())
		{
			std::cout << source->name() << " is not valid";
			return EXIT_FAILURE;
		}
	}

	const auto sinks = packer::get_sinks(packer_argument);
	for (const auto& sink : sinks)
	{
		sink->Initialize(packer_argument);
	}

	const packer::Packer packer(sources, sinks);
	packer.Pack();

	return 0;
}