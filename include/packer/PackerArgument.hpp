#pragma once
#include <args/args.hxx>
#include <vector>
namespace packer
{
	enum ParseResult
	{
		Continue,
		ExitWithSuccess,
		ExitWithFailure
	};

	enum InputType
	{
		UNKNOWN = -1,
		JSON,
		HTTP
	};

	class PackerArgument
	{
	private:
		std::vector<std::string> input_;
		std::string output_file_;
		bool force_;
		InputType input_type_;
		InputType parse_input_source();

	public:
		PackerArgument() = default;
		ParseResult Parse(int argc, char **argv);

		[[nodiscard]] const std::string &output_file() const { return this->output_file_; }
		[[nodiscard]] const std::vector<std::string> &input() const { return this->input_; }
		[[nodiscard]] const InputType input_type() const { return this->input_type_; }
		[[nodiscard]] const bool &force() const { return this->force_; }
	};
}