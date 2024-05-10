#pragma once
#include <string>
#include <vector>

namespace packer
{
	class FilePackType
	{
	private:
		std::string name_;
		std::string file_;
	public:
		FilePackType(std::string name, std::string file) :name_(std::move(name)), file_(std::move(file)) {}
		[[nodiscard]] const std::string& name()  const { return this->name_; }
	};

	typedef FilePackType PackFile;
	typedef std::vector<PackFile> PackFileCollection;
}