#pragma once
#include "options/Flags.hpp"


namespace packer
{
	class PackerArgument
	{
	private:
		std::string program_name;

		Flags flags;
		std::string input_file_name;
		std::string output_file_name;
		std::string base_path;
		bool help;
		bool version;
		bool force;

	public:
		PackerArgument();
		int Parse(int argc, char** argv);
		void PrintHelp();

		const std::string& output_file() const { return this->output_file_name; }
		const std::string& input_file() const { return this->input_file_name; }
		const bool& is_help_set() const { return this->help; }
		const bool& is_version_set() const { return this->version; }
		const bool& is_force_set() const { return this->force; }
	};
}