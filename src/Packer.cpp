#include "Packer.h"
#include <iostream>
using namespace  packer;

void Packer::Pack()
{

	
}
//void Packer::packFiles(const nlohmann::json& files_json)
//{
//	for (auto& array_item : files_json.items()) {
//		std::cout << array_item.key() << " : " << array_item.value() << "\n";
//		for (auto& kv: array_item.value().items())
//		{
//			std::string v;
//			std::cout << kv.key() << " : " << kv.value().get_to(v) << "\n";
//			std::cout << v << "\n";
//		}
//	}
//}
//
//void Packer::packStore(const nlohmann::json& store_json)
//{
//	for (auto& store_item : store_json.items()) {
//		std::cout << store_item.key() << " : " << store_item.value() << "\n";	
//	}
//}