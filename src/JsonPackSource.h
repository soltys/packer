#pragma once
#include "json.hpp"
#include "PackSource.h"

namespace packer
{
	class JsonPackSource : public PackSource
	{
		nlohmann::json root;
	public:
		JsonPackSource() = default;
		void Initialize(PackerArgument packer_argument) override;
		bool Validate() override;
		const std::string name() override { return std::string("Json Pack Source"); }
		const KeyValueCollection key_value_collection() override;
	};
}