#pragma once
#include <nlohmann/json.hpp>
#include <packer/sources/PackSource.hpp>

#include <vector>
namespace packer
{
	class JsonPackSource : public PackSource
	{
		std::vector<nlohmann::json> roots;
	public:
		JsonPackSource() = default;
		void Initialize(PackerArgument packer_argument) override;
		bool Validate() override;
		const std::string name() override { return std::string("Json Pack Source"); }
		const KeyValueCollection key_value_collection() override;
		const FileCollection file_collection() override;
		const TranslationCollection translation_collection() override;
		const ToggleCollection toggle_collection() override;
	};
}