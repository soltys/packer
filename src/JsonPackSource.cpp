#include "JsonPackSource.h"

#include "json.hpp"
#include "Utils.h"
#include "glob.hpp"

void packer::JsonPackSource::Initialize(PackerArgument packer_argument)
{
	auto file_content = read_file_into_string(packer_argument.input_file());
	this->root = nlohmann::json::parse(file_content);

}

bool packer::JsonPackSource::Validate()
{
	if (!root.contains("files") && !root.contains("store"))
	{
		return false;
	}
	return true;
}

const packer::KeyValueCollection packer::JsonPackSource::key_value_collection()
{
	packer::KeyValueCollection collection;

	if (!root.contains("store"))
	{
		return collection;
	}

	const auto& store_array = root["store"];
	if (!store_array.is_array())
	{
		return collection;
	}

	for (const auto& array_item : store_array.items())
	{
		auto& kv_object = array_item.value();
		if (kv_object.contains("key") && kv_object.contains("value"))
		{
			collection.emplace_back(kv_object["key"], kv_object["value"]);
		}
	}

	return collection;
}

const packer::FileCollection packer::JsonPackSource::file_collection()
{
	packer::FileCollection collection;

	if (!root.contains("files"))
	{
		return collection;
	}

	const auto& files_array = root["files"];
	if (!files_array.is_array())
	{
		return collection;
	}

	for (const auto& item : files_array.items())
	{
		auto& file_object = item.value();
		if (file_object.contains("name") && file_object.contains("path"))
		{
			collection.emplace_back(file_object["name"], file_object["path"]);
		}
		else if (file_object.contains("glob"))
		{
			std::string glob = file_object["glob"].get<std::string>();
			auto paths = glob::glob(glob);

			std::string prefix;
			if (file_object.contains("prefix"))
			{
				file_object["prefix"].get_to(prefix);
			}

			for (const auto& path : paths)
			{
				collection.emplace_back(prefix + path.generic_string(), path.generic_string());
			}
		}
	}

	return collection;
}

const packer::TranslationCollection packer::JsonPackSource::translation_collection()
{
	packer::TranslationCollection collection;

	if (!root.contains("translations"))
	{
		return collection;
	}

	const auto& translations_object = root["translations"];
	if (!translations_object.is_object())
	{
		return collection;
	}

	for (const auto& group : translations_object.items())
	{
		std::string locale = group.key();

		for (const auto& el : group.value().items())
		{
			const auto& translation = el.value();
			if (translation.contains("key") && translation.contains("value"))
			{
				collection.emplace_back(translation["key"], translation["value"], locale);
			}
		}
	}

	return collection;
}

