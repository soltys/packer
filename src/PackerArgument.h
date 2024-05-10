#pragma once
#include "options/Flags.hpp"


namespace packer
{
	class PackerArgument
	{
	private:
		std::string program_name;

		Flags flags;
		std::string input_file_;
		std::string output_file_;
		std::string base_path_;
		bool help_;
		bool version_;
		bool force_;

	public:
		PackerArgument();
		int Parse(int argc, char** argv);
		void PrintHelp();

		const std::string& output_file() const { return this->output_file_; }
		const std::string& input_file() const { return this->input_file_; }
		const std::string& base_path() const { return this->base_path_; }
		const bool& help() const { return this->help_; }
		const bool& version() const { return this->version_; }
		const bool& force() const { return this->force_; }
	};
}