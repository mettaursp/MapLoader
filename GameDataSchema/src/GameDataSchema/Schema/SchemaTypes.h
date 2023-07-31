#pragma once

#include <string_view>

namespace SchemaTypes
{
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

	struct Vector3
	{
		static bool ValidateValue(const std::string_view& value);
	};
}