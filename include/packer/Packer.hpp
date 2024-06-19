#pragma once
#include <packer/sinks/PackSink.hpp>
#include <packer/sources/PackSource.hpp>

namespace packer
{
	class Packer
	{
	private:
		const SourceCollection& sources;
		const SinkCollection& sinks;

	public:
		Packer(const SourceCollection& pack_sources, const SinkCollection& pack_sinks) :
			sources(pack_sources), sinks(pack_sinks) {  }
		void Pack() const;
	};
}
