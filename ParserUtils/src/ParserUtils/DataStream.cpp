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
	bool DataStream::Read<Vector3Byte>(Vector3Byte& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(Vector3Byte) + sizeof(unsigned char) > Data.size())
		{
			Failed();

			return false;
		}

		Read<unsigned char>(value.X);
		Read<unsigned char>(value.Y);
		Read<unsigned char>(value.Z);

		unsigned char data = 0;

		Read<unsigned char>(data);

		return true;
	}

	template <>
	bool DataStream::Read<Color4I_BGRA>(Color4I_BGRA& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(Color4I_BGRA) > Data.size())
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

	template <>
	void WriteStream<bool>(std::vector<char>& buffer, const bool& value)
	{
		bool* data = GrowStream<bool>(buffer, sizeof(bool));

		*data = value;
	}

	template <>
	void WriteStream<std::string>(std::vector<char>& buffer, const std::string& value)
	{
		char* data = GrowStream<char>(buffer, sizeof(unsigned short) + value.size());
		short* length = reinterpret_cast<short*>(data);

		*length = (unsigned short)value.size();

		std::memcpy(data + 2, value.c_str(), value.size());
	}

	template <>
	void WriteStream<std::wstring>(std::vector<char>& buffer, const std::wstring& value)
	{
		char* data = GrowStream<char>(buffer, sizeof(unsigned short) + 2 * value.size());
		short* length = reinterpret_cast<short*>(data);

		*length = (unsigned short)value.size();

		static_assert(sizeof(value[0]) == 2);

		std::memcpy(data + 2, value.c_str(), 2 * value.size());
	}

	template <>
	void WriteStream<Vector3S>(std::vector<char>& buffer, const Vector3S& value)
	{
		float* data = GrowStream<float>(buffer, 3 * sizeof(float));

		data[0] = value.X;
		data[1] = value.Y;
		data[2] = value.Z;
	}

	template <>
	void WriteStream<Vector3Short>(std::vector<char>& buffer, const Vector3Short& value)
	{
		short* data = GrowStream<short>(buffer, 3 * sizeof(short));

		data[0] = value.X;
		data[1] = value.Y;
		data[2] = value.Z;
	}

	template <>
	void WriteStream<Vector3Byte>(std::vector<char>& buffer, const Vector3Byte& value)
	{
		unsigned char* data = GrowStream<unsigned char>(buffer, 3 * sizeof(unsigned char));

		data[0] = value.X;
		data[1] = value.Y;
		data[2] = value.Z;
	}

	template <>
	void WriteStream<Color4I_BGRA>(std::vector<char>& buffer, const Color4I_BGRA& value)
	{
		unsigned char* data = GrowStream<unsigned char>(buffer, 4 * sizeof(unsigned char));

		data[0] = value.B;
		data[1] = value.G;
		data[2] = value.R;
		data[3] = value.A;
	}
}

std::ostream& operator<<(std::ostream& out, const Vector3Short& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector3Byte& vector)
{
	return out << "< " << (unsigned int)vector.X << ", " << (unsigned int)vector.Y << ", " << (unsigned int)vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Color4I_BGRA& vector)
{
	return out << "{ R: " << (int)vector.R << "; G: " << (int)vector.G << "; B: " << (int)vector.B << "; A: " << (int)vector.A << " }";
}