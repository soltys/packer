#pragma once

#include "PackerArgument.h"

namespace packer
{
	class PackSink
	{
	public:
		PackSink() = default;
		PackSink(const PackSink&) = default;
		PackSink(const PackSink&&) = delete;
		PackSink& operator=(const PackSink&) = default;
		PackSink& operator=(PackSink&&) = delete;
		virtual ~PackSink() = default;

		virtual void Initialize(PackerArgument packer_argument) = 0;
	};

	typedef std::vector<std::unique_ptr<PackSink>> SinkCollection;
}
