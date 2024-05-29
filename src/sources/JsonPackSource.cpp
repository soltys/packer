#include "JsonPackSource.h"

#include "../utils/json.hpp"
#include "../utils/Utils.h"
#include "../utils/glob.hpp"

#define PACKER_JSON_SOURCE_KV "kv"
#define PACKER_JSON_SOURCE_STRINGS "strings"
#define PACKER_JSON_SOURCE_OPTIONS "options"

void packer::JsonPackSource::Initialize(PackerArgument packer_argument)
{
	auto file_content = read_file_into_string(packer_argument.input_file());
	this->root = nlohmann::json::parse(file_content);
}

bool packer::JsonPackSource::Validate()
{
	if (!root.contains("files") && !root.contains(PACKER_JSON_SOURCE_KV))
	{
		return false;
	}
	return true;
}

const packer::KeyValueCollection packer::JsonPackSource::key_value_collection()
{
	packer::KeyValueCollection collection;

	if (!root.contains(PACKER_JSON_SOURCE_KV))
	{
		return collection;
	}

	const auto &store = root[PACKER_JSON_SOURCE_KV];
	if (!store.is_object())
	{
		return collection;
	}

	for (const auto &el : store.items())
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

	return collection;
}

const packer::FileCollection packer::JsonPackSource::file_collection()
{
	packer::FileCollection collection;

	if (!root.contains("files"))
	{
		return collection;
	}

	const auto &files_array = root["files"];
	if (!files_array.is_array())
	{
		return collection;
	}

	for (const auto &item : files_array.items())
	{
		auto &file_object = item.value();
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

			for (const auto &path : paths)
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

	if (!root.contains(PACKER_JSON_SOURCE_STRINGS))
	{
		return collection;
	}

	const auto &translations_object = root[PACKER_JSON_SOURCE_STRINGS];
	if (!translations_object.is_object())
	{
		return collection;
	}

	for (const auto &group : translations_object.items())
	{
		std::string key = group.key();

		for (const auto &el : group.value().items())
		{
			const auto locale = el.key();
			const auto value = el.value().get<std::string>();
			collection.emplace_back(key, value, locale);
		}
	}

	return collection;
}

const packer::ToggleCollection packer::JsonPackSource::toggle_collection()
{
	packer::ToggleCollection collection;

	if (!root.contains(PACKER_JSON_SOURCE_OPTIONS))
	{
		return collection;
	}

	const auto &toggles_object = root[PACKER_JSON_SOURCE_OPTIONS];
	if (!toggles_object.is_object())
	{
		return collection;
	}

	for (const auto &entry : toggles_object.items())
	{
		std::string name = entry.key();

		auto value = entry.value().get<bool>();
		collection.emplace_back(name, value);
	}

	return collection;
}
