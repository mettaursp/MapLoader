#pragma once

#include <bit>
#include <istream>

void advanceStream(std::string_view& stream, size_t amount);

struct Endian
{
	bool ShouldSwap = false;

	Endian(std::endian order = std::endian::native) : ShouldSwap(order != std::endian::native) {}

	template <typename T>
	T read(const char* bytes) const
	{
		char out[sizeof(T)] = {};

		if (ShouldSwap)
			for (size_t i = 0; i < sizeof(T); ++i)
				out[i] = bytes[sizeof(T) - i - 1];
		else
			for (size_t i = 0; i < sizeof(T); ++i)
				out[i] = bytes[i];

		return *reinterpret_cast<const T*>(out);
	}

	template <typename T>
	T read(std::istream& input) const
	{
		char bytes[sizeof(T)] = {};

		input.read(bytes, sizeof(T));

		return read<T>(bytes);
	}
	
	template <typename T>
	T read(std::string_view& input) const
	{
		const char* bytes = input.data();

		advanceStream(input, sizeof(T));

		return read<T>(bytes);
	}
};