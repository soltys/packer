#include <fstream>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <schema.sql.hpp>
#include <packer/private/config.h>
#include "options/Flags.hpp"
#include "json.hpp"
#include "Pack.h"
#include "Utils.h"
int main(int argc, char** argv) {

	std::string input_file_name;
	std::string output_file_name;
	std::string base_path;
	bool help;
	bool version;
	bool force;
	Flags flags;
	flags.Var(input_file_name, 'i', std::string("input"), std::string(""), std::string("input file to be processed"));
	flags.Var(output_file_name, 'o', std::string("output"), std::string(""), std::string("output pack file"));
	flags.Var(base_path, 'b', std::string("base-path"), std::string(""), std::string("base path"));
	flags.Bool(help, 'h', "help", "show this help and exit");
	flags.Bool(version, 'v', "version", "shows version and exit");
	flags.Bool(force, 'f', "force", "overwrite output file if already exists");
	if (!flags.Parse(argc, argv))
	{
		flags.PrintHelp(argv[0]);
		return 1;
	}
	if (input_file_name.empty())
	{
		std::cerr << "input file is empty" << std::endl;
	}

	if (help) {
		flags.PrintHelp(argv[0]);
		return EXIT_SUCCESS;
	}
	if (version)
	{
		std::cout << "packer version " << PROJECT_VERSION << std::endl;
		return EXIT_SUCCESS;
	}

	auto file_content = read_file_into_string(input_file_name);
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


	if (root.contains("files"))
	{
		packer::packFiles(db, root["files"]);
	}
	else if (root.contains("store"))
	{
		packer::packStore(db, root["store"]);
	}

	std::cout << "Hello World!";
	return 0;
}