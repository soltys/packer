#pragma once

#include "../PackerArgument.h"
#include "../packTypes/PackTypes.h"

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
		virtual void Insert(KeyValueCollection key_value) = 0;
		virtual void Insert(FileCollection file_collection) = 0;
		virtual void Insert(TranslationCollection translation_collection) = 0;
		virtual void Insert(ToggleCollection toggle_collection) = 0;
	};

	typedef std::vector<std::unique_ptr<PackSink>> SinkCollection;
}
