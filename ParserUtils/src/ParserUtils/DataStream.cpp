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
			Failed();

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
			Failed();

			return false;
		}

		unsigned short length = 0;

		Read<unsigned short>(length);

		if (HasRecentlyFailed || length == 0 || Index + length > Data.size())
		{
			HasRecentlyFailed |= length != 0;

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
			Failed();

			return false;
		}

		unsigned short length = 0;

		Read<unsigned short>(length);

		if (HasRecentlyFailed || length == 0 || Index + length * 2 > Data.size())
		{
			HasRecentlyFailed |= length != 0;

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
			Failed();

			return false;
		}

		Read<float>(value.X);
		Read<float>(value.Y);
		Read<float>(value.Z);

		return true;
	}

	template <>
	bool DataStream::Read<Vector3Short>(Vector3Short& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(Vector3Short) > Data.size())
		{
			Failed();

			return false;
		}

		Read<short>(value.X);
		Read<short>(value.Y);
		Read<short>(value.Z);

		return true;
	}

	template <>
	bool DataStream::Read<Color4I_BGRA>(Color4I_BGRA& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(Vector3Short) > Data.size())
		{
			Failed();

			return false;
		}

		Read<unsigned char>(value.B);
		Read<unsigned char>(value.G);
		Read<unsigned char>(value.R);
		Read<unsigned char>(value.A);

		return true;
	}

	void DataStream::Failed()
	{
		HasRecentlyFailed = true;
	}
}

std::ostream& operator<<(std::ostream& out, const Vector3Short& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Color4I_BGRA& vector)
{
	return out << "{ R: " << (int)vector.R << "; G: " << (int)vector.G << "; B: " << (int)vector.B << "; A: " << (int)vector.A << " }";
}