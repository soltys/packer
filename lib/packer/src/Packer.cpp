#include <packer/Packer.h>

#include <get_key.sql.hpp>
#include <get_file.sql.hpp>
#include <get_toggle.sql.hpp>
#include <get_translation.sql.hpp>
#include <insert_log.sql.hpp>
#include <get_latest_logs.sql.hpp>

#include <iostream>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Transaction.h"

packer::Packer::Packer(std::string file_name)
{
	this->database_ = std::make_unique<SQLite::Database>(file_name, SQLite::OPEN_READWRITE);

	ExecuteStatement("pragma page_size = 32768;");
	ExecuteStatement("pragma journal_mode = WAL;");
	ExecuteStatement("pragma synchronous = normal;");
	ExecuteStatement("pragma temp_store = memory;");
	ExecuteStatement("pragma mmap_size = 30000000000;");
}

std::string packer::Packer::get_key_value(const std::string &key) const
{
	const auto get_key_sql_text = LOAD_RESOURCE(sql_get_key_sql);
	try
	{
		SQLite::Statement get_key_stmt(*this->database_, get_key_sql_text.data());
		get_key_stmt.bind("$Key", key);
		get_key_stmt.executeStep();
		return std::string(get_key_stmt.getColumn(0).getText());
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return "";
	}
}

std::vector<char> packer::Packer::get_file(const std::string &name) const
{
	std::vector<char> blob;
	const auto get_file_sql_text = LOAD_RESOURCE(sql_get_file_sql);
	try
	{
		SQLite::Statement get_file_stmt(*this->database_, get_file_sql_text.data());
		get_file_stmt.bind("$Name", name);
		get_file_stmt.executeStep();

		const auto size = get_file_stmt.getColumn("Size").getInt();
		blob.reserve(size);
		const auto content_column = get_file_stmt.getColumn("Content");
		auto blob_begin = (const char *)content_column.getBlob();

		std::copy(blob_begin, blob_begin + size, std::back_inserter(blob));

		return blob;
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return blob;
	}
}

bool packer::Packer::get_toggle(const std::string &name) const
{
	const auto get_toggle_sql_text = LOAD_RESOURCE(sql_get_toggle_sql);
	try
	{
		SQLite::Statement get_toggle_stmt(*this->database_, get_toggle_sql_text.data());
		get_toggle_stmt.bind("$Name", name);
		get_toggle_stmt.executeStep();
		return get_toggle_stmt.getColumn(0).getInt() != 0;
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return false;
	}
}
std::string packer::Packer::get_translation(const std::string &key, const std::string &locale) const
{
	const auto get_translation_sql_text = LOAD_RESOURCE(sql_get_translation_sql);
	try
	{
		SQLite::Statement get_translation_stmt(*this->database_, get_translation_sql_text.data());
		get_translation_stmt.bind("$Key", key);
		get_translation_stmt.bind("$Locale", locale);
		get_translation_stmt.executeStep();
		return std::string(get_translation_stmt.getColumn(0).getText());
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return "";
	}
}

void packer::Packer::ExecuteStatement(const char *stmt_text) const
{
	try
	{
		SQLite::Statement statement(*this->database_, stmt_text);
		statement.executeStep();
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

static int64_t get_timestamp_milliseconds()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void packer::Packer::insert_log(const std::string &level, const std::string &logger, const std::string &message) const
{
	const auto insert_log_sql_text = LOAD_RESOURCE(sql_insert_log_sql);
	try
	{
		SQLite::Statement insert_log_stmt(*this->database_, insert_log_sql_text.data());
		insert_log_stmt.bind("$Level", level);
		insert_log_stmt.bind("$Date", (int64_t)get_timestamp_milliseconds());
		insert_log_stmt.bind("$Logger", logger);
		insert_log_stmt.bind("$Message", message);
		insert_log_stmt.executeStep();
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

std::vector<packer::LogEntry> packer::Packer::get_latest_logs(const int &limit) const
{
	std::vector<packer::LogEntry> collection;
	const auto get_latest_logs_sql_text = LOAD_RESOURCE(sql_get_latest_logs_sql);
	try
	{
		SQLite::Statement get_latest_logs_stmt(*this->database_, get_latest_logs_sql_text.data());
		get_latest_logs_stmt.bind("$Limit", limit);

		while (get_latest_logs_stmt.executeStep())
		{
			collection.emplace_back(packer::LogEntry(
				get_latest_logs_stmt.getColumn(0).getText(),
				get_latest_logs_stmt.getColumn(1).getInt64(),
				get_latest_logs_stmt.getColumn(2).getText(),
				get_latest_logs_stmt.getColumn(3).getText()
			));
		}

		return collection;
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return std::vector<packer::LogEntry>();
	}
}