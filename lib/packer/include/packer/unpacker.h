#pragma once
#include <string>

#include "SQLiteCpp/Database.h"

namespace packer
{
	class Unpacker
	{
		std::unique_ptr<SQLite::Database> database_;
	public:
		Unpacker(std::string file_name);
		std::string get_key_value(std::string key);
	};
}
