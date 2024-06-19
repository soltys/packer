#pragma once
#include <args/args.hxx>

namespace packer
{
	enum ParseResult
	{
		Continue,
		ExitWithSuccess,
		ExitWithFailure
	};

	class PackerArgument
	{
	private:
		std::string input_file_;
		std::string output_file_;
		bool force_;

	public:
		PackerArgument() = default;
		ParseResult Parse(int argc, char** argv);

		[[nodiscard]] const std::string& output_file() const { return this->output_file_; }
		[[nodiscard]] const std::string& input_file() const { return this->input_file_; }
		[[nodiscard]] const bool& force() const { return this->force_; }
	};
}