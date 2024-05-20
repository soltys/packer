#include <iostream>
#include <packer/Packer.h>
int main()
{
    std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    packer::Packer pack("my_own_pack.sqlite");

    // key value store
    std::cout << "value returned for key1 is " << pack.get_key_value("key1") << std::endl;

    // getting file
    const auto file = pack.get_file("f1");
    std::cout << "Content of the file 'f1': " << std::endl;
    for (char i : file)
    {
        std::cout << i;
    }
    std::cout << std::endl;

    // getting translation
    const auto translation = pack.get_translation("HELLO_MESSAGE", "pl");
    std::cout << "Translation (pl): " << translation << std::endl;

    // getting toggle
    const auto toggle1 = pack.get_toggle("feature1");
    const auto toggle2 = pack.get_toggle("feature2");
    std::cout << "feature1: " << toggle1 << "   feature2: " << toggle2 << std::endl;

    std::cout << "Inserting  log into packer" << std::endl;
    pack.insert_log("INFO", "packer_in_use", "{\"message\":\"Log1\"}");
    pack.insert_log("INFO", "packer_in_use", "{\"message\":\"Log2\"}");
    pack.insert_log("INFO", "packer_in_use", "{\"message\":\"Log3\"}");

    std::cout << "getting logs from pack" << std::endl;
    for (const auto l : pack.get_latest_logs(3))
    {
        std::cout << "Level: " << l.level() 
                  << "\tDate: " << l.date() 
                  << "\tLogger: " << l.logger() 
                  << "\tMessage: " << l.message() << std::endl;
    }
}
