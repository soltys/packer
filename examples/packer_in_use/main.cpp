#include <iostream>
#include <packer/Reader.h>
int main(){
    std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    packer::Reader pack_reader("pack.db");

    std::cout << "value returned for key1 is " << pack_reader.get_key_value("key1") << std::endl;
}