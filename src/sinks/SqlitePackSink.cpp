#include "SqlitePackSink.h"

#include <sql/create_file_table.sql.hpp>
#include <sql/create_store_table.sql.hpp>
#include <sql/create_translation_table.sql.hpp>
#include <sql/insert_key_value.sql.hpp>
#include <sql/insert_file.sql.hpp>
#include <sql/insert_translation.sql.hpp>

#include "../utils/Utils.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Transaction.h"

void packer::SqlitePackSink::Initialize(const packer::PackerArgument packer_argument)
{
	auto output_file = packer_argument.output_file();
	if (std::filesystem::exists(output_file))
	{
		if (packer_argument.force())
		{
			std::filesystem::remove(output_file);
		}
	}

	this->db_ = std::make_unique<SQLite::Database>(output_file, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
	try
	{
		const auto create_file_table_text = LOAD_RESOURCE(sql_create_file_table_sql);
		SQLite::Statement create_file_table_stmt(*this->db_, create_file_table_text.data());
		create_file_table_stmt.exec();
	}
	catch (SQLite::Exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
	try
	{
		const auto create_store_table_text = LOAD_RESOURCE(sql_create_store_table_sql);
		SQLite::Statement create_store_table_stmt(*this->db_, create_store_table_text.data());
		create_store_table_stmt.exec();
	}
	catch (SQLite::Exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}

	try
	{
		const auto create_translation_table_text = LOAD_RESOURCE(sql_create_translation_table_sql);
		SQLite::Statement create_translation_table_stmt(*this->db_, create_translation_table_text.data());
		create_translation_table_stmt.exec();
	}
	catch (SQLite::Exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

void packer::SqlitePackSink::Insert(const KeyValueCollection key_value_collection)
{
	const auto insert_stmt_text = LOAD_RESOURCE(sql_insert_key_value_sql);
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto& key_value : key_value_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, insert_stmt_text.data());
			insert_stmt.bind("$Key", key_value.key());
			insert_stmt.bind("$Value", key_value.value());
			insert_stmt.exec();
		}

		transaction.commit();
	}
	catch (SQLite::Exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return;
	}
}

void packer::SqlitePackSink::Insert(const FileCollection file_collection)
{
	const auto insert_file_stmt_text = LOAD_RESOURCE(sql_insert_file_sql);
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto& file : file_collection)
		{
			auto file_content = read_file_into_string(file.file_path());

			SQLite::Statement insert_stmt(*this->db_, insert_file_stmt_text.data());
			insert_stmt.bind("$Name", file.name());
			insert_stmt.bindNoCopy("$Content", file_content.c_str(), static_cast<int>(file_content.length()));
			insert_stmt.bind("$Size", static_cast<int64_t>(file_content.length()));
			insert_stmt.exec();
		}

		transaction.commit();
	}
	catch (SQLite::Exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return;
	}
}

void packer::SqlitePackSink::Insert(TranslationCollection translation_collection)
{
	const auto insert_translation_stmt_text = LOAD_RESOURCE(sql_insert_translation_sql);
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto& translation : translation_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, insert_translation_stmt_text.data());
			insert_stmt.bind("$Key", translation.key());
			insert_stmt.bind("$Value", translation.value());
			insert_stmt.bind("$Locale", translation.locale());
			insert_stmt.exec();
		}

		transaction.commit();
	}
	catch (SQLite::Exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return;
	}

}

