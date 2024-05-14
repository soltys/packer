#pragma once
#include "sinks/PackSink.h"
#include "sources/PackSource.h"

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
