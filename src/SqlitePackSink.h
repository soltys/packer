#pragma once
#include "PackSink.h"
#include "PackSource.h"
#include "SQLiteCpp/Backup.h"

namespace packer
{
	class SqlitePackSink : public packer::PackSink
	{
	private:
		std::unique_ptr<SQLite::Database> db_;

		std::string base_path_;
	public:
		void Initialize(packer::PackerArgument packer_argument) override;
		void Insert(KeyValueCollection key_value) override;
		void Insert(FileCollection file_collection) override;
	};
}
