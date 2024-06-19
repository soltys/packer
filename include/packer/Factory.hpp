#pragma once

#include <packer/Packer.hpp>
#include <packer/PackerArgument.hpp>
#include <packer/sources/PackSource.hpp>
#include <packer/sinks/PackSink.hpp>
namespace packer
{
    packer::SourceCollection get_sources(const PackerArgument& packer_argument);
    packer::SinkCollection get_sinks(const PackerArgument& packer_argument);
}