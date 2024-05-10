#include "Packer.h"
#include <iostream>
using namespace  packer;

void Packer::Pack() const
{
	KeyValueCollection kvCollection;
	for (const auto& source: this->sources )
	{
		const auto& kvSourceCollection = source->key_value_collection();
		std::copy(kvSourceCollection.begin(), kvSourceCollection.end(), std::back_inserter(kvCollection));
	}

	for (const auto& sink: this->sinks)
	{
		sink->Insert(kvCollection);
	}
	
}
