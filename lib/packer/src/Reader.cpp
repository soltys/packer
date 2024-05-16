#include <packer/reader.h>

#include <get_key.sql.hpp>
#include <get_file.sql.hpp>
#include <get_toggle.sql.hpp>
#include <get_translation.sql.hpp>
#include <iostream>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Transaction.h"

packer::Reader::Reader(std::string file_name)
{
	this->database_ = std::make_unique<SQLite::Database>(file_name, SQLite::OPEN_READWRITE);
}

std::string packer::Reader::get_key_value(const std::string &key) const
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

std::vector<char> packer::Reader::get_file(const std::string &name) const
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

bool packer::Reader::get_toggle(const std::string &name) const
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
std::string packer::Reader::get_translation(const std::string &key, const std::string &locale) const
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