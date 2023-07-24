#include "SchemaTypes.h"

namespace SchemaTypes
{
	bool Int::ValidateValue(const std::string_view& value)
	{
		for (char character : value)
		{
			if (!(character >= '0' && character <= '9'))
			{
				return false;
			}
		}

		return true;
	}

	bool String::ValidateValue(const std::string_view& value)
	{
		return true;
	}
}