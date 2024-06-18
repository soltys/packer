#include <packer/Packer.hpp>

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
	SQLite::Statement stmt(*this->database_, R"sql(SELECT Value from Store WHERE Key=$Key;)sql");
	stmt.bind("$Key", key);
	stmt.executeStep();
	return std::string(stmt.getColumn(0).getText());
}

std::vector<char> packer::Packer::get_file(const std::string &name) const
{
	std::vector<char> blob;

	SQLite::Statement stmt(*this->database_, R"sql(SELECT Content, Size FROM File WHERE Name = $Name;)sql");
	stmt.bind("$Name", name);
	stmt.executeStep();

	const auto size = stmt.getColumn("Size").getInt();
	blob.reserve(size);
	const auto content_column = stmt.getColumn("Content");
	auto blob_begin = (const char *)content_column.getBlob();

	std::copy(blob_begin, blob_begin + size, std::back_inserter(blob));

	return blob;
}

bool packer::Packer::is_on(const std::string &name) const
{
	SQLite::Statement stmt(*this->database_, R"sql(SELECT IsOn FROM Toggle WHERE Name=$Name;)sql");
	stmt.bind("$Name", name);
	stmt.executeStep();
	return stmt.getColumn(0).getInt() != 0;
}
std::string packer::Packer::get_translation(const std::string &key, const std::string &locale) const
{
	SQLite::Statement stmt(*this->database_, R"sql(SELECT Value FROM translation WHERE Key=$Key AND Locale=$Locale;)sql");
	stmt.bind("$Key", key);
	stmt.bind("$Locale", locale);
	stmt.executeStep();
	return std::string(stmt.getColumn(0).getText());
}

void packer::Packer::ExecuteStatement(const char *stmt_text) const
{
	SQLite::Statement statement(*this->database_, stmt_text);
	statement.executeStep();
}

static int64_t get_timestamp_microseconds()
{
	using namespace std::chrono;
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

void packer::Packer::insert_log(const std::string &level, const std::string &logger, const std::string &message) const
{
	SQLite::Statement stmt(*this->database_, R"sql(INSERT INTO Log (Level, Date, Logger, Message) VALUES ($Level, $Date, $Logger, $Message);)sql");
	stmt.bind("$Level", level);
	stmt.bind("$Date", (int64_t)get_timestamp_microseconds());
	stmt.bind("$Logger", logger);
	stmt.bind("$Message", message);
	stmt.executeStep();
}

std::vector<packer::LogEntry> packer::Packer::get_latest_logs(const int &limit) const
{
	std::vector<packer::LogEntry> collection;
	SQLite::Statement stmt(*this->database_, R"sql(SELECT Level, Date, Logger, Message FROM Log ORDER BY Date DESC, Id ASC LIMIT $Limit;)sql");
	stmt.bind("$Limit", limit);

	while (stmt.executeStep())
	{
		collection.emplace_back(packer::LogEntry(
			stmt.getColumn(0).getText(),
			stmt.getColumn(1).getInt64(),
			stmt.getColumn(2).getText(),
			stmt.getColumn(3).getText()));
	}

	return collection;
}

std::vector<packer::Toggle> packer::Packer::get_toggles() const
{
	std::vector<packer::Toggle> collection;
	SQLite::Statement stmt(*this->database_, R"sql(SELECT Name, IsOn FROM Toggle;)sql");

	while (stmt.executeStep())
	{
		collection.emplace_back(packer::Toggle(
			stmt.getColumn(0).getText(),
			stmt.getColumn(1).getInt() == 1));
	}
	return collection;
}