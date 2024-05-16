#include <packer/reader.h>

#include <get_key.sql.hpp>
#include <iostream>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Transaction.h"

packer::Reader::Reader(std::string file_name)
{
	this->database_ = std::make_unique<SQLite::Database>(file_name, SQLite::OPEN_READWRITE );
}


std::string packer::Reader::get_key_value(const std::string& key)
{
	const auto get_key_sql_text = LOAD_RESOURCE(sql_get_key_sql);
	try
	{
		SQLite::Statement get_key_stmt(*this->database_, get_key_sql_text.data());
		get_key_stmt.bind("$Key", key);
		get_key_stmt.executeStep();
		return get_key_stmt.getColumn(0);
	}
	catch (SQLite::Exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return "";
	}	
}
