#pragma once

#include <string>
#include <vector>

namespace packer
{
	class TranslationPackType
	{
	private:
		std::string key_;
		std::string value_;
		std::string locale_;

	public:
		TranslationPackType(std::string key, std::string value, std::string locale) : key_(std::move(key)),
																					  value_(std::move(value)),
																					  locale_(std::move(locale))
		{
		}
		[[nodiscard]] const std::string &key() const { return this->key_; }
		[[nodiscard]] const std::string &value() const { return this->value_; }
		[[nodiscard]] const std::string &locale() const { return this->locale_; }

		static void from_json(nlohmann::json root, std::vector<TranslationPackType> &collection)
		{
			for (const auto &group : root.items())
			{
				std::string key = group.key();

				for (const auto &el : group.value().items())
				{
					const auto locale = el.key();
					const auto value = el.value().get<std::string>();
					collection.emplace_back(key, value, locale);
				}
			}
		}
	};

	typedef TranslationPackType Translation;
	typedef std::vector<Translation> TranslationCollection;
}
