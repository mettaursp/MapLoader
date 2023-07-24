#pragma once

#include <string_view>

namespace SchemaTypes
{
	struct Int
	{
		static bool ValidateValue(const std::string_view& value);
	};

	struct String
	{
		static bool ValidateValue(const std::string_view& value);
	};
}