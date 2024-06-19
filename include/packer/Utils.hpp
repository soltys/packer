#pragma once
#include <string>
#include <ostream>
std::string read_file_into_string(const std::string& file_name);
void get_version_string(std::ostream &out);