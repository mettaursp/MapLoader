#include "ParserUtils.h"

#include <iostream>

#include "XmlReader.h"

std::unordered_map<std::string, int> features;
std::string locale;

int strcmp(const std::string_view& first, const char* second)
{
	return strncmp(first.data(), second, first.size());
}

char lower(char character)
{
	return character + (int)(character >= 'A' && character <= 'Z') * ('a' - 'A');
}

std::string lower(const std::string& text)
{
	std::string lower = text;

	for (size_t i = 0; i < lower.size(); ++i)
		if (lower[i] >= 'A' && lower[i] <= 'Z')
			lower[i] += 'a' - 'A';

	return lower;
}

bool matchesCaseInsensitive(const std::string_view& text1, const std::string_view& text2)
{
	if (text1.size() != text2.size()) return false;

	for (size_t i = 0; i < text1.size(); ++i)
	{
		if (lower(text1[i]) != lower(text2[i])) return false;
	}

	return true;
}

bool matches(const std::string_view& text1, const std::string_view& text2, bool isCaseInsensitive)
{
	if (text1.size() != text2.size()) return false;

	if (isCaseInsensitive) return matchesCaseInsensitive(text1, text2);

	for (size_t i = 0; i < text1.size(); ++i)
	{
		if (text1[i] != text2[i]) return false;
	}

	return true;
}

bool containsCaseInsensitive(const std::string& text, const std::string& inner)
{
	if (text.size() < inner.size()) return false;

	size_t rangeEnd = text.size() - inner.size() + 1;

	for (size_t i = 0; i < rangeEnd; ++i)
	{
		bool found = true;

		for (size_t j = 0; j < inner.size() && found; ++j)
			found = lower(text[i + j]) == lower(inner[j]);

		if (found) return true;
	}

	return false;
}

std::string padId(std::string id)
{
	while (id.size() > 0 && id.size() < 8)
		id = "0" + id;

	return id;
}

template <>
int readValue<int>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
unsigned int readValue<unsigned int>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
short readValue<short>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
unsigned short readValue<unsigned short>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
unsigned char readValue<unsigned char>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
signed char readValue<signed char>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
bool readValue<bool>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->IntValue();
}

template <>
long long readValue<long long>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->Int64Value();
}

template <>
unsigned long long readValue<unsigned long long>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->Int64Value();
}

template <>
float readValue<float>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->FloatValue();
}

template <>
double readValue<double>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->DoubleValue();
}

template <>
std::string readValue<std::string>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->Value();
}

template <>
const char* readValue<const char*>(const tinyxml2::XMLAttribute* attribute)
{
	return attribute->Value();
}

template <>
float readValue<float>(const char* value)
{
	return (float)atof(value);
}

template <>
double readValue<double>(const char* value)
{
	return atof(value);
}

template <>
long long readValue<long long>(const char* value)
{
	return atoll(value);
}

template <>
unsigned long long readValue<unsigned long long>(const char* value)
{
	return atoll(value);
}

int featureIsActive(const char* feature)
{
	if (strcmp(feature, "") == 0)
		return 1;

	const auto& support = features.find(feature);

	return support != features.end() ? support->second : -1;
}

int featureIsActive(const std::string_view& feature)
{
	if (feature.size() == 0)
		return 1;

	const auto& support = features.find(std::string(feature));

	return support != features.end() ? support->second : -1;
}

SupportLevel matchesLocale(const char* nodeLocale)
{
	if (strcmp(nodeLocale, "") == 0)
		return SupportLevel::Default;

	return locale == nodeLocale ? SupportLevel::Override : SupportLevel::None;
}

SupportLevel matchesLocale(const std::string_view& nodeLocale)
{
	if (nodeLocale.size() == 0)
		return SupportLevel::Default;

	return locale == nodeLocale ? SupportLevel::Override : SupportLevel::None;
}

SupportSettings featureIsActive(tinyxml2::XMLElement* node, SupportSettings& settings)
{
	const tinyxml2::XMLAttribute* attribute = node->FindAttribute("feature");

	int support = 0;
	const char* feature = "";

	if (attribute != nullptr)
	{
		feature = attribute->Value();
		support = featureIsActive(feature);
	}

	if (settings.OverriddenBy(support))
		return SupportSettings{ feature, SupportLevel::Default, support };

	return SupportSettings{ "", SupportLevel::None };
}

SupportSettings featureIsActive(XmlLite::XmlReader& document, SupportSettings& settings)
{
	std::string_view feature;

	bool hasFeature = document.ReadAttribute<std::string_view>("feature", feature);

	int support = 0;

	if (hasFeature)
	{
		support = featureIsActive(feature);
	}

	if (settings.OverriddenBy(support))
		return SupportSettings{ std::string(feature), SupportLevel::Default, support };

	return SupportSettings{ "", SupportLevel::None };
}

SupportSettings matchesLocale(tinyxml2::XMLElement* node, SupportSettings& settings)
{
	const tinyxml2::XMLAttribute* attribute = node->FindAttribute("locale");

	SupportLevel support = SupportLevel::Default;
	const char* locale = "";

	if (attribute != nullptr)
	{
		locale = attribute->Value();
		support = matchesLocale(locale);
	}

	if (settings.OverriddenBy(support))
		return SupportSettings{ locale, support };

	return SupportSettings{ "", SupportLevel::None };
}

SupportSettings matchesLocale(XmlLite::XmlReader& document, SupportSettings& settings)
{
	std::string_view locale;

	bool hasLocale = document.ReadAttribute<std::string_view>("locale", locale);

	SupportLevel support = SupportLevel::Default;

	if (hasLocale)
	{
		support = matchesLocale(locale);
	}

	if (settings.OverriddenBy(support))
		return SupportSettings{ std::string(locale), support };

	return SupportSettings{ "", SupportLevel::None };
}

bool isNodeEnabled(tinyxml2::XMLElement* node, SupportSettings* feature, SupportSettings* locale)
{
	SupportSettings featureFound;
	SupportSettings localeFound;

	if (feature != nullptr)
		featureFound = featureIsActive(node, *feature);

	if (locale != nullptr)
		localeFound = matchesLocale(node, *locale);

	if (featureFound.Version == -1 || featureFound.Version == 99 || featureFound.Version < feature->Version || localeFound.Level == SupportLevel::None || featureFound.Level == SupportLevel::None)
		return false;

	if (feature != nullptr)
		*feature = featureFound;

	if (locale != nullptr)
		*locale = localeFound;

	return true;
}

bool isNodeEnabled(XmlLite::XmlReader& document, SupportSettings* feature, SupportSettings* locale)
{
	SupportSettings featureFound;
	SupportSettings localeFound;

	if (feature != nullptr)
		featureFound = featureIsActive(document, *feature);

	if (locale != nullptr)
		localeFound = matchesLocale(document, *locale);

	if (featureFound.Version == -1 || featureFound.Version == 99 || featureFound.Version < feature->Version || localeFound.Level == SupportLevel::None || featureFound.Level == SupportLevel::None)
		return false;

	if (feature != nullptr)
		*feature = featureFound;

	if (locale != nullptr)
		*locale = localeFound;

	return true;
}

bool loadFeatures(const Archive::ArchivePath& tablePath, const char* locale, const char* env, std::string& buffer)
{
	Archive::ArchivePath featureSettingPath = tablePath.Child("feature_setting.xml");
	Archive::ArchivePath featurePath = tablePath.Child("feature.xml");

	::locale = locale;

	if (!featureSettingPath.Loaded() || !featurePath.Loaded())
	{
		if (!featurePath.Loaded())
		{
			std::string featurePathText = featurePath.GetPath().string();

			if (featurePathText.size() == 0)
				featurePathText = tablePath.GetPath().string() + "/" + "feature.xml";

			std::cout << "failed to find feature.xml: \"" << featurePathText << "\"" << std::endl;
		}

		if (!featureSettingPath.Loaded())
		{
			std::string featureSettingPathText = featureSettingPath.GetPath().string();

			if (featureSettingPathText.size() == 0)
				featureSettingPathText = tablePath.GetPath().string() + "/" + "feature_setting.xml";

			std::cout << "failed to find feature_setting.xml: \"" << featureSettingPathText << "\"" << std::endl;
		}

		return false;
	}

	int featureLevel = -1;

	{
		tinyxml2::XMLDocument document;

		featureSettingPath.Read(buffer);

		document.Parse(buffer.data(), buffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* settingElement = rootElement->FirstChildElement(); settingElement; settingElement = settingElement->NextSiblingElement())
		{
			const tinyxml2::XMLAttribute* typeAttribute = settingElement->FindAttribute("type");

			if (typeAttribute == nullptr || strcmp(typeAttribute->Value(), env) != 0)
				continue;

			const tinyxml2::XMLAttribute* featureLevelAttribute = settingElement->FindAttribute(locale);

			if (featureLevelAttribute != nullptr)
				featureLevel = featureLevelAttribute->IntValue();

			std::cout << "env: " << env << "; locale: " << locale << "; level: " << featureLevel << std::endl;

			break;
		}
	}

	if (featureLevel == -1)
		return false;

	tinyxml2::XMLDocument document;

	featurePath.Read(buffer);

	document.Parse(buffer.data(), buffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* featureElement = rootElement->FirstChildElement(); featureElement; featureElement = featureElement->NextSiblingElement())
	{
		const tinyxml2::XMLAttribute* featureLevelAttribute = featureElement->FindAttribute(locale);

		if (featureLevelAttribute == nullptr)
			continue;

		const tinyxml2::XMLAttribute* featureNameAttribute = featureElement->FindAttribute("name");

		if (featureNameAttribute == nullptr)
			continue;

		int level = featureLevelAttribute->IntValue();

		if (level <= featureLevel)
		{
			features[featureNameAttribute->Value()] = level;

			std::cout << featureNameAttribute->Value() << ": " << level << std::endl;
		}
	}

	return true;
}

bool loadFeatures(const Archive::ArchivePath& tablePath, const char* locale, const char* env)
{
	std::string buffer;
	return loadFeatures(tablePath, locale, env, buffer);
}