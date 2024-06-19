#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace packer
{
	class KeyValuePackType
	{

	private:
		std::string key_;
		std::string value_;

	public:
		KeyValuePackType(std::string k, std::string v) : key_(std::move(k)), value_(std::move(v)) {}
		[[nodiscard]] const std::string &key() const { return this->key_; }
		[[nodiscard]] const std::string &value() const { return this->value_; }
		static void from_json(nlohmann::json root, std::vector<KeyValuePackType> &collection)
		{
			for (auto &el : root.items())
			{
				auto key = el.key();
				if (el.value().is_string())
				{
					auto value = el.value().get<std::string>();
					collection.emplace_back(key, value);
				}
				else
				{
					auto value = el.value().dump();
					collection.emplace_back(key, value);
				}
			}
		}
	};
	typedef KeyValuePackType KeyValue;
	typedef std::vector<KeyValue> KeyValueCollection;
}