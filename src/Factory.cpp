#include <packer/Factory.hpp>
#include <packer/sources/JsonPackSource.hpp>
#include <packer/sinks/SqlitePackSink.hpp>
packer::SourceCollection packer::get_sources(const packer::PackerArgument &packer_argument)
{
    packer::SourceCollection sources;
    switch (packer_argument.input_type())
    {
    case InputType::JSON:
        sources.push_back(std::make_unique<packer::JsonPackSource>());
        break;
    }
    return sources;
}

packer::SinkCollection packer::get_sinks(const packer::PackerArgument &packer_argument)
{
    packer::SinkCollection sinks;
    sinks.push_back(std::make_unique<packer::SqlitePackSink>());
    return sinks;
}