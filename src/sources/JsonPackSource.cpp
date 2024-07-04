#include <packer/sources/JsonPackSource.hpp>

#include <nlohmann/json.hpp>
#include <packer/Utils.hpp>
#include <glob/glob.hpp>

#define PACKER_JSON_SOURCE_KV "kv"
#define PACKER_JSON_SOURCE_STRINGS "strings"
#define PACKER_JSON_SOURCE_OPTIONS "options"

void packer::JsonPackSource::Initialize(PackerArgument packer_argument)
{
	for (auto i : packer_argument.input())
	{
		auto file_content = read_file_into_string(i);
		this->roots.push_back(nlohmann::json::parse(file_content));
	}
}

bool packer::JsonPackSource::Validate()
{
	return true;
}

const packer::KeyValueCollection packer::JsonPackSource::key_value_collection()
{
	packer::KeyValueCollection collection;
	for (const auto root : this->roots)
	{
		if (!root.contains(PACKER_JSON_SOURCE_KV))
		{
			continue;
		}

		const auto &store = root[PACKER_JSON_SOURCE_KV];
		if (!store.is_object())
		{
			continue;
		}
		KeyValuePackType::from_json(store, collection);
	}
	return collection;
}

const packer::FileCollection packer::JsonPackSource::file_collection()
{
	packer::FileCollection collection;
	for (const auto root : this->roots)
	{
		if (!root.contains("files"))
		{
			continue;
		}

		const auto &files_array = root["files"];
		if (!files_array.is_array())
		{
			continue;
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
	}
	return collection;
}

const packer::TranslationCollection packer::JsonPackSource::translation_collection()
{
	packer::TranslationCollection collection;
	for (const auto root : this->roots)
	{
		if (!root.contains(PACKER_JSON_SOURCE_STRINGS))
		{
			continue;
		}

		const auto &translations_object = root[PACKER_JSON_SOURCE_STRINGS];
		if (!translations_object.is_object())
		{
			continue;
		}

		TranslationPackType::from_json(translations_object, collection);
	}
	return collection;
}

const packer::ToggleCollection packer::JsonPackSource::toggle_collection()
{
	packer::ToggleCollection collection;
	for (const auto root : this->roots)
	{
		if (!root.contains(PACKER_JSON_SOURCE_OPTIONS))
		{
			continue;
		}

		const auto &toggles_object = root[PACKER_JSON_SOURCE_OPTIONS];
		if (!toggles_object.is_object())
		{
			continue;
		}
		TogglePackType::from_json(toggles_object, collection);
	}
	return collection;
}
