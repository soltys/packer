#include "Packer.h"
#include <iostream>
using namespace  packer;

void Packer::Pack() const
{
	KeyValueCollection key_value_collection;
	FileCollection file_collection;
	TranslationCollection translation_collection;
	for (const auto& source : this->sources)
	{
		const auto& source_kv_collection = source->key_value_collection();
		std::copy(source_kv_collection.begin(), source_kv_collection.end(), std::back_inserter(key_value_collection));

		const auto& source_file_collection = source->file_collection();
		std::copy(source_file_collection.begin(), source_file_collection.end(), std::back_inserter(file_collection));

		const auto& source_translation_collection = source->translation_collection();
		std::copy(source_translation_collection.begin(), source_translation_collection.end(), std::back_inserter(translation_collection));
	}

	for (const auto& sink : this->sinks)
	{
		sink->Insert(key_value_collection);
		sink->Insert(file_collection);
		sink->Insert(translation_collection);
	}

}
