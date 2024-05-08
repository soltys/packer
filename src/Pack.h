#pragma once
#include "json.hpp"
#include "SQLiteCpp/Database.h"

namespace packer
{
	void packFiles(const SQLite::Database& db, const nlohmann::json& files_json);
	void packStore(const SQLite::Database& db, const nlohmann::json& store_json);
}
