#pragma once
#include "json.hpp"
#include "SQLiteCpp/Database.h"

namespace packer
{
	class Packer
	{
	private:
		const SQLite::Database& db;
		const nlohmann::json& root;
		

		void packFiles(const nlohmann::json& files_json);
		void packStore(const nlohmann::json& store_json);

	public:
		Packer(const SQLite::Database& db, const nlohmann::json& root) : db(db), root(root) {  }
		void pack();	

	};
	
}
