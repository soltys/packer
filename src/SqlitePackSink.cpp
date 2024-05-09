#include "SqlitePackSink.h"

#include "schema.sql.hpp"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"

void packer::SqlitePackSink::Initialize(packer::PackerArgument packer_argument)
{
	const auto db = SQLite::Database(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

	const auto schema_resource = LOAD_RESOURCE(schema_sql);
	SQLite::Statement create_schema(db, schema_resource.data());
	create_schema.exec();
}
