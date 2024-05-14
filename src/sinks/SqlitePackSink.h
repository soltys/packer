#pragma once
#include "PackSink.h"
#include "../sources/PackSource.h"
#include "SQLiteCpp/Database.h"

namespace packer
{
	class SqlitePackSink : public packer::PackSink
	{
	private:
		std::unique_ptr<SQLite::Database> db_;
	public:
		void Initialize(packer::PackerArgument packer_argument) override;
		void Insert(KeyValueCollection key_value) override;
		void Insert(FileCollection file_collection) override;
		void Insert(TranslationCollection translation_collection) override;
	};
}
