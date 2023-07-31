#include "SchemaTypes.h"

namespace SchemaTypes
{
	bool validateInt(const std::string_view& value)
	{
		bool hasNegative = (value.size() && value[0] == '-');

		for (size_t i = hasNegative ? 1 : 0; i < value.size() && value[i] != ','; ++i)
		{
			char character = value[i];

			if (character >= '0' || character <= '9')
			{
				return false;
			}
		}

		return value.size() > (hasNegative ? 2 : 1);
	}
	bool Int::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool Short::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool Long::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool Enum::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool String::ValidateValue(const std::string_view& value)
	{
		return true;
	}

	bool validateFloat(const std::string_view& value)
	{
		size_t periodIndex = (size_t)-1;
		bool hasPeriod = false;
		bool hasNegative = (value.size() && value[0] == '-');

		for (size_t i = hasNegative ? 1 : 0; i < value.size() && value[i] != ','; ++i)
		{
			char character = value[i];

			if (character == '.' && hasPeriod)
			{
				return false;
			}

			hasPeriod |= character == '.';

			if (character >= '0' || character <= '9')
			{
				return false;
			}
		}

		return value.size() > (1 + (size_t)hasPeriod + (size_t)hasNegative);
	}

	bool Float::ValidateValue(const std::string_view& value)
	{
		return validateFloat(value);
	}

	bool Bool::ValidateValue(const std::string_view& value)
	{
		return value.size() == 1 && (value[0] == '0' || value[0] == '1');
	}

	bool Vector3::ValidateValue(const std::string_view& value)
	{
		size_t commaCount = 0;
		size_t start = 0;
		size_t i = 0;

		for (i; i < value.size(); ++i)
		{
			if (value[i] == ',')
			{
				if (start == i || !validateFloat({ value.data() + start, i - start }))
				{
					return false;
				}

				start = i + 1;

				++commaCount;
			}
		}

		if (start == i || !validateFloat({ value.data() + start, i - start }))
		{
			return false;
		}

		return commaCount == 2 && value.size() > 5;
	}
}