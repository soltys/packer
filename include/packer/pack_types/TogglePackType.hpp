#pragma once
#include <string>
namespace packer
{
	class TogglePackType
	{
	private:
		std::string name_;
		bool isOn_;

	public:
		TogglePackType(std::string name, bool isOn) : name_(std::move(name)), isOn_(std::move(isOn)) {}
		[[nodiscard]] const std::string &name() const { return this->name_; }
		[[nodiscard]] const bool isOn() const { return this->isOn_; }

		static void from_json(nlohmann::json root, std::vector<TogglePackType> &collection)
		{
			for (const auto &entry : root.items())
			{
				std::string name = entry.key();
				auto value = entry.value().get<bool>();
				collection.emplace_back(name, value);
			}
		}
	};

	typedef TogglePackType Toggle;
	typedef std::vector<Toggle> ToggleCollection;
}