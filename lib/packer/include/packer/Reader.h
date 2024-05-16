#pragma once
#include <memory>
#include <string>

#include "SQLiteCpp/Database.h"

namespace packer
{
	class Reader
	{
		std::unique_ptr<SQLite::Database> database_;
	public:
		Reader(std::string file_name);
		std::string get_key_value(const std::string& key);
	};
}
