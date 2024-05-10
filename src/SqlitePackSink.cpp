#include "SqlitePackSink.h"

#include "create_file_table.sql.hpp"
#include "create_store_table.sql.hpp"
#include "insert_key_value.sql.hpp"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Transaction.h"

void packer::SqlitePackSink::Initialize(packer::PackerArgument packer_argument)
{
	auto output_file = packer_argument.output_file();
	if (std::filesystem::exists(output_file))
	{
		if (packer_argument.is_force_set())
		{
			std::filesystem::remove(output_file);
		}
	}

	this->db_ = std::make_unique<SQLite::Database>(output_file, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

	const auto create_file_table_text = LOAD_RESOURCE(create_file_table_sql);
	SQLite::Statement create_file_table_stmt(*this->db_, create_file_table_text.data());
	create_file_table_stmt.exec();

	const auto create_store_table_text = LOAD_RESOURCE(create_store_table_sql);
	SQLite::Statement create_store_table_stmt(*this->db_, create_store_table_text.data());
	create_store_table_stmt.exec();
}

void packer::SqlitePackSink::Insert(KeyValueCollection key_value_collection)
{
	const auto insert_stmt_text = LOAD_RESOURCE(insert_key_value_sql);
	try
	{
		SQLite::Transaction transaction(*this->db_);

		for (const auto &key_value : key_value_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, insert_stmt_text.data());
			insert_stmt.bind("$Key", std::get<0>(key_value));
			insert_stmt.bind("$Value", std::get<1>(key_value));
			insert_stmt.exec();
		}

		transaction.commit();
	}
	catch (SQLite::Exception &e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return;
	}
}
