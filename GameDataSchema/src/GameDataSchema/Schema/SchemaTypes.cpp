#include "SchemaTypes.h"

namespace SchemaTypes
{
	bool validateInt(const std::string_view& value)
	{
		bool hasNegative = (value.size() && value[0] == '-');

		for (size_t i = hasNegative ? 1 : 0; i < value.size() && value[i] != ','; ++i)
		{
			char character = value[i];

			if (character < '0' || character > '9')
			{
				return false;
			}
		}

		return value.size() >= (hasNegative ? 2 : 1);
	}
	bool Int::ValidateValue(const std::string_view& value)
	{
		if (!validateInt(value))
		{
			return false;
		}
		
		long long number = atoll(value.data());

		return number >= (long long)std::numeric_limits<int>::min() && number <= (long long)std::numeric_limits<int>::max();
	}

	bool Short::ValidateValue(const std::string_view& value)
	{
		if (!validateInt(value))
		{
			return false;
		}

		long long number = atoll(value.data());

		return number >= (long long)std::numeric_limits<short>::min() && number <= (long long)std::numeric_limits<short>::max();
	}

	bool Long::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool Enum::ValidateValue(const std::string_view& value)
	{
		return validateInt(value);
	}

	bool StringEnum::ValidateValue(const std::string_view& value)
	{
		return true;
	}

	bool MixedEnum::ValidateValue(const std::string_view& value)
	{
		return true;
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

			if (character == '.')
			{
				if (hasPeriod)
				{
					return false;
				}

				hasPeriod = true;

				continue;
			}

			if (character < '0' || character > '9')
			{
				return false;
			}
		}

		return value.size() >= (1 + (size_t)hasPeriod + (size_t)hasNegative);
	}

	bool Float::ValidateValue(const std::string_view& value)
	{
		return validateFloat(value);
	}

	bool Bool::ValidateValue(const std::string_view& value)
	{
		return value.size() == 1 && (value[0] == '0' || value[0] == '1');
	}

	bool StringBool::ValidateValue(const std::string_view& value)
	{
		return strncmp(value.data(), "true", value.size()) == 0 || strncmp(value.data(), "false", value.size()) == 0;
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

	bool ValidateArray(const std::string_view& value, ValidationCallback callback)
	{
		size_t start = 0;
		size_t i = 0;

		for (i; i < value.size(); ++i)
		{
			if (value[i] == ',')
			{
				if (start == i || !callback({ value.data() + start, i - start }))
				{
					return false;
				}

				start = i + 1;
			}
		}

		if (start == i && !(start > 0 && value[start - 1] == ','))
		{
			return true;
		}

		if (start == i || !callback({ value.data() + start, i - start }))
		{
			return false;
		}

		return true;
	}

	bool ValidateMap(const std::string_view& value, ValidationCallback keyCallback, ValidationCallback valueCallback)
	{
		size_t start = 0;
		size_t valueStart = 0;
		size_t i = 0;

		for (i; i < value.size(); ++i)
		{
			if (value[i] == '=')
			{
				if (valueStart > start)
				{
					return false;
				}

				valueStart = i + 1;
			}

			if (value[i] == ',')
			{
				if (start == i || valueStart == i || valueStart - 1 <= start)
				{
					return false;
				}

				if (!keyCallback({ value.data() + start, valueStart - 1 - start }))
				{
					return false;
				}

				if (!valueCallback({ value.data() + valueStart, i - valueStart }))
				{
					return false;
				}

				start = i + 1;
			}
		}

		if (start == i && !(start > 0 && value[start - 1] == ','))
		{
			return true;
		}

		if (start == i || valueStart == i || valueStart - 1 <= start)
		{
			return false;
		}

		if (!keyCallback({ value.data() + start, valueStart - 1 - start }))
		{
			return false;
		}

		if (!valueCallback({ value.data() + valueStart, i - valueStart }))
		{
			return false;
		}

		return true;
	}
}