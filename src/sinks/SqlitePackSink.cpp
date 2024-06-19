#include <packer/sinks/SqlitePackSink.hpp>
#include <packer/Utils.hpp>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Transaction.h>

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

	ExecuteStatement("pragma page_size = 32768;");
	ExecuteStatement("pragma journal_mode = WAL;");
	ExecuteStatement("pragma synchronous = normal;");
	ExecuteStatement("pragma temp_store = memory;");
	ExecuteStatement("pragma mmap_size = 30000000000;");

	ExecuteStatement(R"sql(
	CREATE TABLE IF NOT EXISTS "File" (
		"Name" TEXT NOT NULL,
		"Content" BLOB NOT NULL,
		"Size" INTEGER NOT NULL,
		PRIMARY KEY("Name")
	);
	)sql");

	ExecuteStatement(R"sql(
	CREATE TABLE IF NOT EXISTS "Store" (
		"Key" TEXT NOT NULL,
		"Value" BLOB NOT NULL,
		PRIMARY KEY("Key")
	);
	)sql");

	ExecuteStatement(R"sql(
	CREATE TABLE IF NOT EXISTS "Translation" (
		"Key" TEXT NOT NULL,
		"Value" TEXT NOT NULL,
		"Locale" TExt NOT NULL,
		PRIMARY KEY("Key", "Locale")
	);
	)sql");

	ExecuteStatement(R"sql(
	CREATE TABLE IF NOT EXISTS "Toggle" (
		"Name" TEXT NOT NULL,
		"IsOn" BOOLEAN NOT NULL,
		PRIMARY KEY("Name")
	);
	)sql");

	ExecuteStatement(R"sql(
	CREATE TABLE IF NOT EXISTS "Log" (
		"Id"	INTEGER NOT NULL,
		"Level"	TEXT NOT NULL,
		"Date"	INTEGER NOT NULL,
		"Logger"	TEXT,
		"Message"	TEXT,
		PRIMARY KEY("Id" AUTOINCREMENT)
	);
	)sql");
}

void packer::SqlitePackSink::ExecuteStatement(const char *stmt_text) const
{
	try
	{
		SQLite::Statement statement(*this->db_, stmt_text);
		statement.executeStep();
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

void packer::SqlitePackSink::Insert(const KeyValueCollection key_value_collection)
{
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto &key_value : key_value_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, R"sql(INSERT INTO Store VALUES ($Key, $Value);)sql");
			insert_stmt.bind("$Key", key_value.key());
			insert_stmt.bind("$Value", key_value.value());
			insert_stmt.exec();
		}

		transaction.commit();
	}
	catch (SQLite::Exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
		return;
	}
}

void packer::SqlitePackSink::Insert(const FileCollection file_collection)
{
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto &file : file_collection)
		{
			auto file_content = read_file_into_string(file.file_path());

			SQLite::Statement insert_stmt(*this->db_, R"sql(INSERT INTO File VALUES ($Name, $Content, $Size);)sql");
			insert_stmt.bind("$Name", file.name());
			insert_stmt.bindNoCopy("$Content", file_content.c_str(), static_cast<int>(file_content.length()));
			insert_stmt.bind("$Size", static_cast<int64_t>(file_content.length()));
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

void packer::SqlitePackSink::Insert(TranslationCollection translation_collection)
{
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto &translation : translation_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, R"sql(INSERT INTO Translation VALUES ($Key, $Value, $Locale);)sql");
			insert_stmt.bind("$Key", translation.key());
			insert_stmt.bind("$Value", translation.value());
			insert_stmt.bind("$Locale", translation.locale());
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

void packer::SqlitePackSink::Insert(ToggleCollection toggle_collection)
{
	try
	{
		SQLite::Transaction transaction(*this->db_);
		for (const auto &translation : toggle_collection)
		{
			SQLite::Statement insert_stmt(*this->db_, R"sql(INSERT INTO Toggle VALUES ($Name, $IsOn);)sql");
			insert_stmt.bind("$Name", translation.name());
			insert_stmt.bind("$IsOn", translation.isOn());
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

void packer::SqlitePackSink::Finalize()
{
	try
	{
		ExecuteStatement("pragma vacuum;");
		ExecuteStatement("pragma optimize;");
	}
	catch (SQLite::Exception &e)
	{
		std::cout << "exception: " << e.what() << std::endl;
		return;
	}
}