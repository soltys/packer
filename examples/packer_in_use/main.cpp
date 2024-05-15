#include <iostream>
#include <packer/unpacker.h>
int main(){
    std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    packer::Unpacker unpacker("pack.db");

    std::cout << "value returned for key1 is " << unpacker.get_key_value("key1") << std::endl;
}