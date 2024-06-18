#pragma once
#include <memory>
#include <string>

#include <SQLiteCpp/Database.h>

#include <packer/LogEntry.hpp>
#include <packer/Toggle.hpp>

namespace packer
{
	class Packer
	{
		std::unique_ptr<SQLite::Database> database_;
		void ExecuteStatement(const char *stmt_text) const;

	public:
		Packer(std::string file_name);
		std::vector<char> get_file(const std::string &name) const;
		std::string get_key_value(const std::string &key) const;
		std::string get_translation(const std::string &key, const std::string &locale) const;

		//logs
		void insert_log(const std::string &level, const std::string &logger, const std::string &message) const;
		std::vector<LogEntry> get_latest_logs(const int &limit) const;

		//Toggles
		bool is_on(const std::string &toggle_name) const;
		std::vector<Toggle> get_toggles() const;
	};
}
