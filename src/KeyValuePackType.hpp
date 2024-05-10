#pragma once
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
		KeyValuePackType(std::string k, std::string v) :key_(std::move(k)), value_(std::move(v)) {}
		[[nodiscard]] const std::string& key()  const { return this->key_; }
		[[nodiscard]] const std::string& value() const { return this->value_; }
	};

	typedef KeyValuePackType KeyValue;
	typedef std::vector<KeyValue> KeyValueCollection;
}