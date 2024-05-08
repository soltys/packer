#include <fstream>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <schema.sql.hpp>
#include <packer/private/config.h>

#include "json.hpp"
#include "Packer.h"
#include "PackerArgument.h"
#include "Utils.h"
int main(int argc, char** argv) {

	
	packer::PackerArgument packer_argument;
	if(packer_argument.Parse(argc, argv) != 0)
	{
		packer_argument.PrintHelp();
		return EXIT_FAILURE;
	}

	if (packer_argument.input_file().empty())
	{
		std::cerr << "input file is empty" << std::endl;
	}

	if (packer_argument.is_help_set()) {
		packer_argument.PrintHelp();
		return EXIT_SUCCESS;
	}
	if (packer_argument.is_version_set())
	{
		std::cout << "packer version " << PROJECT_VERSION << std::endl;
		return EXIT_SUCCESS;
	}


	auto file_content = read_file_into_string(packer_argument.input_file());
	auto root = nlohmann::json::parse(file_content);
	if(!root.contains("files") && !root.contains("store"))
	{
		std::cerr << "Nothing to pack!" << std::endl;
		return EXIT_FAILURE;
	}

	const auto db = SQLite::Database(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

	const auto schema_resource = LOAD_RESOURCE(schema_sql);
	SQLite::Statement create_schema(db, schema_resource.data());
	create_schema.exec();


	packer::Packer packer(db, root);
	packer.pack();


	std::cout << "Hello World!";
	return 0;
}