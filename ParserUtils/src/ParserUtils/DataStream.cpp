#include "DataStream.h"

#include <Engine/Math/Vector3S.h>

namespace ParserUtils
{
	template <>
	bool DataStream::Read<bool>(bool& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(bool) > Data.size())
		{
			HasRecentlyFailed = true;

			return false;
		}

		value = Data[Index] != 0;

		Index += sizeof(bool);

		return true;
	}

	template <>
	bool DataStream::Read<std::string>(std::string& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(unsigned short) > Data.size())
		{
			HasRecentlyFailed = true;

			return false;
		}

		unsigned short length = 0;

		Read<unsigned short>(length);

		if (HasRecentlyFailed || length == 0 || Index + length > Data.size())
		{
			return !HasRecentlyFailed;
		}

		value.resize(length);

		for (size_t i = 0; !HasRecentlyFailed && i < length; ++i)
		{
			Read<char>(value[i]);
		}

		return true;
	}

	template <>
	bool DataStream::Read<std::wstring>(std::wstring& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(unsigned short) > Data.size())
		{
			HasRecentlyFailed = true;

			return false;
		}

		unsigned short length = 0;

		Read<unsigned short>(length);

		if (HasRecentlyFailed || length == 0 || Index + length * 2 > Data.size())
		{
			return !HasRecentlyFailed;
		}

		value.resize(length);

		for (size_t i = 0; !HasRecentlyFailed && i < length; ++i)
		{
			char16_t character = 0;

			Read<char16_t>(character);

			value[i] = (wchar_t)character;
		}

		return true;
	}

	template <>
	bool DataStream::Read<Vector3S>(Vector3S& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(Vector3S) > Data.size())
		{
			HasRecentlyFailed = true;

			return false;
		}

		Read<float>(value.X);
		Read<float>(value.Y);
		Read<float>(value.Z);

		return true;
	}
}