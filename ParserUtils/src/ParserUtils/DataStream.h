#pragma once

#include <string_view>

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

		template <typename T>
		bool Read(T& value);

		template <Numeric T>
		bool Read(T& value);

		bool Succeeded() const { return !HasRecentlyFailed; }
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
			HasRecentlyFailed = true;

			return false;
		}

		value = *reinterpret_cast<const T*>(Data.data() + Index);

		Index += sizeof(T);

		return true;
	}
}