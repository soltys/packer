#include "JsonPackSource.h"

#include "json.hpp"
#include "Utils.h"

void packer::JsonPackSource::Initialize(PackerArgument packer_argument)
{
	auto file_content = read_file_into_string(packer_argument.input_file());
	this->root = nlohmann::json::parse(file_content);
	
}

bool packer::JsonPackSource::Validate()
{
	if (!root.contains("files") && !root.contains("store"))
	{
		return false;
	}
	return true;
}
