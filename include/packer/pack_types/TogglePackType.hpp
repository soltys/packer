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
		TogglePackType(std::string name, bool isOn) :name_(std::move(name)), isOn_(std::move(isOn)) {}
		[[nodiscard]] const std::string& name()  const { return this->name_; }
		[[nodiscard]] const bool isOn() const { return this->isOn_; }
	};

	typedef TogglePackType Toggle;
	typedef std::vector<Toggle> ToggleCollection;
}