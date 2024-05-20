#pragma once
#include <memory>
#include <string>

#include <SQLiteCpp/Database.h>

namespace packer
{
	class Reader
	{
		std::unique_ptr<SQLite::Database> database_;
		void ExecuteStatement(const char* stmt_text) const;
	public:
		Reader(std::string file_name);
		std::vector<char> get_file(const std::string& name) const;
		std::string get_key_value(const std::string& key) const;
		bool get_toggle(const std::string& name) const;
		std::string get_translation(const std::string& key, const std::string& locale) const;
	};
}
