#pragma once

#include <iostream>
#include <source_location>

#include "DataStream.h"

namespace ParserUtils
{
	namespace Packets
	{
		const bool PrintOutput = true;
		const bool PrintErrors = true;

		template <typename T>
		void Read(const char* name, DataStream& stream, T& value, const char* tabs, const std::source_location location = std::source_location::current())
		{
			if (stream.HasRecentlyFailed)
			{
				return;
			}

			bool succeeded = stream.Read<T>(value);

			if (!succeeded)
			{
				if constexpr (PrintErrors)
				{
					std::cout << location.file_name() << "[" << location.line() << "," << location.column() << "] " << location.function_name() << ": failed to load packet value '" << name << "'" << std::endl;
				}

				return;
			}

			if constexpr (PrintOutput)
			{
				std::cout << tabs << name << ": ";

				if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char> || std::is_same_v<T, signed char>)
				{
					std::cout << (int)value;
				}
				else
				{
					std::cout << value;
				}

				std::cout << std::endl;
			}
		}
	}
}