#pragma once

#include <string_view>

namespace SchemaTypes
{
	typedef bool (*ValidationCallback)(const std::string_view& value);

	struct Int
	{
		static bool ValidateValue(const std::string_view& value);
	};
	
	struct Short
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct Long
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct Enum
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct StringEnum
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct MixedEnum
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct String
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct Float
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct Bool
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct StringBool
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct Vector3
	{
		static bool ValidateValue(const std::string_view& value);
	};

	bool ValidateArray(const std::string_view& value, ValidationCallback callback);
	bool ValidateMap(const std::string_view& value, ValidationCallback keyCallback, ValidationCallback valueCallback);
}