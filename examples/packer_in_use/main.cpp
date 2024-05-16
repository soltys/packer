#include <iostream>
#include <packer/Reader.h>
int main()
{
    std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    packer::Reader pack_reader("my_own_pack.sqlite");

    // key value store
    std::cout << "value returned for key1 is " << pack_reader.get_key_value("key1") << std::endl;

    // getting file
    const auto file = pack_reader.get_file("f1");
    std::cout << "Content of the file 'f1': " << std::endl;
    for (char i : file)
    {
        std::cout << i;
    }
    std::cout << std::endl;

    // getting translation
    const auto translation = pack_reader.get_translation("HELLO_MESSAGE", "pl");
    std::cout << "Translation (pl): " << translation << std::endl;

    // getting toggle
    const auto toggle1 = pack_reader.get_toggle("feature1");
    const auto toggle2 = pack_reader.get_toggle("feature2");
    std::cout << "feature1: " << toggle1 << "   feature2: " << toggle2 << std::endl;
}
