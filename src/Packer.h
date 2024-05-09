#pragma once
#include "PackSink.h"
#include "PackSource.h"

namespace packer
{
	class Packer
	{
	private:
		const SourceCollection& pack_sources;
		const SinkCollection& pack_sinks;

	public:
		Packer(const SourceCollection& pack_sources, const SinkCollection& pack_sinks) :
			pack_sources(pack_sources), pack_sinks(pack_sinks) {  }
		void Pack();

	};

}
