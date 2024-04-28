#pragma once

#include <string_view>
#include <sstream>
#include <vector>

#include <Engine/Math/Vector3S-decl.h>
#include <Engine/Math/Color4I.h>

struct Vector3Short
{
	short X = 0;
	short Y = 0;
	short Z = 0;

	Vector3Short() {}

	Vector3Short(const Vector3S& vector)
	{
		X = (short)vector.X;
		Y = (short)vector.Y;
		Z = (short)vector.Z;
	}

	operator Vector3S()
	{
		return { (Float)X, (Float)Y, (Float)Z };
	}
};

struct Vector3Byte
{
	unsigned char X = 0;
	unsigned char Y = 0;
	unsigned char Z = 0;

	Vector3Byte() {}

	Vector3Byte(const Vector3S& vector)
	{
		X = (unsigned char)vector.X;
		Y = (unsigned char)vector.Y;
		Z = (unsigned char)vector.Z;
	}

	operator Vector3S()
	{
		return { (Float)X, (Float)Y, (Float)Z };
	}
};

struct Color4I_BGRA
{
	unsigned char B = 0;
	unsigned char G = 0;
	unsigned char R = 0;
	unsigned char A = 0;

	Color4I_BGRA() {}

	Color4I_BGRA(const Color4I& vector)
	{
		B = vector.B;
		G = vector.G;
		R = vector.R;
		A = vector.A;
	}

	operator Color4I()
	{
		return { R, G, B, A };
	}
};

struct StringCharLen
{
	std::string& String;

	StringCharLen(std::string& string) : String(string) {}

	operator std::string& ()
	{
		return String;
	}
};

struct WStringCharLen
{
	std::wstring& String;

	WStringCharLen(std::wstring& string) : String(string) {}

	operator std::wstring& ()
	{
		return String;
	}
};

std::ostream& operator<<(std::ostream& out, const Vector3Short& vector);
std::ostream& operator<<(std::ostream& out, const Vector3Byte& vector);
std::ostream& operator<<(std::ostream& out, const Color4I_BGRA& vector);

namespace ParserUtils
{
	template <typename T>
	concept Numeric = requires(T param)
	{
		{ std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool> };
	};

	struct DataStream
	{
		std::string_view Data;
		size_t Index = 0;
		bool HasRecentlyFailed = false;
		bool FoundUnknownValue = false;
		bool IgnoreUnknownValues = false;
		bool SuppressErrors = false;
		bool DiscardErrors = false;
		bool PrintOutput = false;

		template <typename T>
		bool Read(T& value);

		template <Numeric T>
		bool Read(T& value);

		bool Succeeded() const { return !HasRecentlyFailed; }
		void Failed();
	};

	template <typename T>
	bool DataStream::Read(T& value)
	{
		//static_assert(false, "attempt to read in unimplemented type");

		return false;
	}

	template <Numeric T>
	bool DataStream::Read(T& value)
	{
		if (HasRecentlyFailed)
		{
			return false;
		}

		if (Index + sizeof(T) > Data.size())
		{
			Failed();

			return false;
		}

		value = *reinterpret_cast<const T*>(Data.data() + Index);

		Index += sizeof(T);

		return true;
	}

	template <>
	bool DataStream::Read<bool>(bool& value);

	template <>
	bool DataStream::Read<std::string>(std::string& value);

	template <>
	bool DataStream::Read<std::wstring>(std::wstring& value);

	template <>
	bool DataStream::Read<StringCharLen>(StringCharLen& value);

	template <>
	bool DataStream::Read<WStringCharLen>(WStringCharLen& value);

	template <>
	bool DataStream::Read<Vector3S>(Vector3S& value);

	template <>
	bool DataStream::Read<Vector3Short>(Vector3Short& value);

	template <>
	bool DataStream::Read<Vector3Byte>(Vector3Byte& value);

	template <>
	bool DataStream::Read<Color4I_BGRA>(Color4I_BGRA& value);

	template <typename T>
	void WriteStream(std::vector<char>& buffer, const T& value)
	{
		//static_assert(false, "attempt to read in unimplemented type");
	}

	template <typename T>
	T* GrowStream(std::vector<char>& buffer, size_t amount)
	{
		size_t size = buffer.size();
		size_t capacity = buffer.capacity();

		if (size + amount > capacity)
		{
			buffer.reserve(std::max(2 * capacity, size + amount));
		}

		buffer.resize(size + amount);

		return reinterpret_cast<T*>(buffer.data() + size);
	}

	template <Numeric T>
	void WriteStream(std::vector<char>& buffer, const T& value)
	{
		T* data = GrowStream<T>(buffer, sizeof(T));

		*data = value;
	}

	template <>
	void WriteStream<bool>(std::vector<char>& buffer, const bool& value);

	template <>
	void WriteStream<std::string>(std::vector<char>& buffer, const std::string& value);

	template <>
	void WriteStream<std::wstring>(std::vector<char>& buffer, const std::wstring& value);

	template <>
	void WriteStream<Vector3S>(std::vector<char>& buffer, const Vector3S& value);

	template <>
	void WriteStream<Vector3Short>(std::vector<char>& buffer, const Vector3Short& value);

	template <>
	void WriteStream<Vector3Byte>(std::vector<char>& buffer, const Vector3Byte& value);

	template <>
	void WriteStream<Color4I_BGRA>(std::vector<char>& buffer, const Color4I_BGRA& value);
}