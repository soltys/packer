#pragma once
#include "PackerArgument.h"

namespace packer
{
	
	class PackSource
	{

	public:
		PackSource() = default;
		PackSource(const PackSource&) = default;
		PackSource(const PackSource&&) = delete;
		PackSource& operator=(const PackSource&) = default;
		PackSource& operator=(PackSource&&) = delete;
		virtual ~PackSource() = default;
		virtual void Initialize(PackerArgument packer_argument) = 0;
		virtual bool Validate() = 0;

		virtual const std::string name() = 0;
	};

	typedef std::vector<std::unique_ptr<PackSource>> SourceCollection;
}
