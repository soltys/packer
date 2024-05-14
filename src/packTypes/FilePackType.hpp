#pragma once
#include <string>
#include <vector>

namespace packer
{
	class FilePackType
	{
	private:
		std::string name_;
		std::string file_path_;
	public:
		FilePackType(std::string name, std::string file_path) :name_(std::move(name)), file_path_(std::move(file_path)) {}
		[[nodiscard]] const std::string& name()  const { return this->name_; }
		[[nodiscard]] const std::string& file_path()  const { return this->file_path_; }
	};

	typedef FilePackType File;
	typedef std::vector<File> FileCollection;
}