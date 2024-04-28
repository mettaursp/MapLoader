#pragma once

#include <iostream>
#include <source_location>
#include <vector>
#include <iomanip>

#include "DataStream.h"

std::string toString(const std::wstring& wstr);

std::ostream& operator<<(std::ostream& out, const std::wstring& string);

template <typename T> requires std::is_enum_v<T>
std::ostream& operator<<(std::ostream& out, T value)
{
	return out << (unsigned long long)value;
}

template <typename T, typename U> requires std::is_enum_v<T>
bool operator==(T left, U right)
{
	return (U)left == right;
}

template <typename T, typename U> requires std::is_enum_v<T>
bool operator<(T left, U right)
{
	return (U)left < right;
}

template <typename T, typename U> requires std::is_enum_v<T>
bool operator>(T left, U right)
{
	return (U)left > right;
}

template <typename T, typename U> requires std::is_enum_v<T>
bool operator<=(T left, U right)
{
	return (U)left <= right;
}

template <typename T, typename U> requires std::is_enum_v<T>
bool operator>=(T left, U right)
{
	return (U)left >= right;
}

namespace ParserUtils
{
	namespace Packets
	{
		const bool PrintOutput = false;
		const bool PrintPacketOutput = false;
		const bool PrintErrors = true;
		const bool PrintUnknownValues = true;

		template <typename VectorType, typename Size, typename HandlerType>
		void ResizeVector(HandlerType& handler, VectorType& vector, Size size, const std::source_location location = std::source_location::current())
		{
			DataStream& stream = handler.PacketStream();

			if (stream.HasRecentlyFailed)
			{
				return;
			}

			if constexpr (std::is_signed_v<Size>)
			{
				if (size < 0)
				{
					stream.Failed();

					if constexpr (PrintErrors)
					{
						if (!stream.SuppressErrors)
						{
							std::cout << location.file_name() << "[" << location.line() << "," << location.column() << "] " << location.function_name() << ": attempt to set vector to a negative size: " << size << std::endl;
						}
					}

					return;
				}
			}

			size_t remaining = stream.Data.size() - stream.Index;

			if (size > remaining)
			{
				stream.Failed();

				if constexpr (PrintErrors)
				{
					if (!stream.SuppressErrors)
					{
						std::cout << location.file_name() << "[" << location.line() << "," << location.column() << "] " << location.function_name() << ": attempt to set vector to a size larger than the remaining number of bytes : " << size << "; remaining: " << remaining << std::endl;
					}
				}

				return;
			}

			vector.resize(size);
		}

		template <typename T, typename HandlerType>
		void ReadValue(const char* name, HandlerType& handler, T& value, const std::source_location location = std::source_location::current())
		{
			DataStream& stream = handler.PacketStream();

			if (stream.HasRecentlyFailed)
			{
				return;
			}

			size_t lastIndex = stream.Index;
			bool succeeded = stream.Read<T>(value);

			if (!succeeded)
			{
				if constexpr (PrintErrors)
				{
					if (!stream.SuppressErrors)
					{
						std::cout << location.file_name() << "[" << location.line() << "," << location.column() << "] " << location.function_name() << ": failed to load packet value '" << name << "'" << std::endl;
					}
				}

				return;
			}

			if constexpr (PrintOutput || PrintErrors)
			{
				if (!(!PrintOutput && !stream.DiscardErrors && (stream.SuppressErrors || !stream.PrintOutput)))
				{
					std::ostream& out = PrintOutput ? std::cout : handler.FoundValues;

					out << handler.Tabs() << "[" << (stream.Index - lastIndex) << "] " << std::hex;

					if (stream.Index - lastIndex <= 8)
					{
						for (size_t i = lastIndex; i < stream.Index; ++i)
						{
							out << std::setw(2) << std::setfill('0') << (unsigned short)(unsigned char)stream.Data[i] << " ";
						}

						out << std::dec << " | ";
					}

					out << name << ": ";

					if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char> || std::is_same_v<T, signed char>)
					{
						out << (int)value;
					}
					else
					{
						out << value;
					}

					out << std::endl;

					if (stream.Index - lastIndex > 8)
					{
						for (size_t i = lastIndex; i < stream.Index; ++i)
						{
							out << std::setw(2) << std::setfill('0') << (unsigned short)(unsigned char)stream.Data[i] << " ";
						}

						out << std::dec << std::endl;
					}
				}
			}
		}

		template <typename T, typename HandlerType, typename VarType>
		void Read(const char* name, HandlerType& handler, VarType& value, const std::source_location location = std::source_location::current())
		{
			if constexpr (std::is_same_v<T, VarType>)
			{
				ReadValue<T>(name, handler, value, location);

				return;
			}
			else
			{
				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}

				T tempValue = {};

				ReadValue<T>(name, handler, tempValue, location);

				value = (VarType)tempValue;
			}
		}

		template <typename T>
		void Write(std::vector<char>& buffer, const T& value)
		{
			ParserUtils::WriteStream<T>(buffer, value);
		}

		template <typename T>
		concept IntegerType = requires(T param)
		{
			{ std::is_integral_v<T> };
		};

		template <IntegerType T>
		bool GetBit(T value, unsigned char bitIndex)
		{
			return ((value >> bitIndex) & 1) != 0;
		}
		
		template <typename T, typename HandlerType, typename... Types>
		void ValidateValues(HandlerType& handler, const char* name, const T& value, const Types&... expected)
		{
			if constexpr (PrintUnknownValues)
			{
				DataStream& stream = handler.PacketStream();

				bool found = stream.SuppressErrors || stream.DiscardErrors || stream.IgnoreUnknownValues || ((value == expected) || ...);

				if (!found)
				{
					std::ostream& out = (PrintOutput || !stream.PrintOutput) ? std::cout : handler.FoundValues;

					out << handler.Tabs() << "'" << name << "' unknown value: ";

					if constexpr (std::is_integral_v<T> && !std::is_floating_point_v<T>)
					{
						if constexpr(std::is_signed_v<T>)
						{
							out << (long long)value << std::endl;
						}
						else
						{
							out << (unsigned long long)value << std::endl;
						}
					}
					else
					{
						out << value << std::endl;
					}

					stream.FoundUnknownValue = true;
				}
			}
		}

		template <typename T>
		void PrintValues(std::ostream& out, const T& value)
		{
			out << value;
		}

		template <typename T, typename... Types>
		void PrintValues(std::ostream& out, const T& value, const Types&... values)
		{
			out << value << ", ";

			PrintValues(out, values...);
		}

		template <typename T, typename HandlerType, typename... Types>
		void CalledFunction(HandlerType& handler, const char* name, const char* outputName, const T& value, const Types&... values)
		{
			if constexpr (PrintOutput || PrintErrors)
			{
				DataStream& stream = handler.PacketStream();

				if (!(!PrintOutput && !stream.DiscardErrors && (stream.SuppressErrors || !stream.PrintOutput)))
				{
					std::ostream& out = PrintOutput ? std::cout : handler.FoundValues;

					out << handler.Tabs() << name << "(";

					if (sizeof...(values) > 0)
					{
						PrintValues(out, values...);
					}

					out << ") -> ";

					if constexpr (std::is_integral_v<T> && !std::is_floating_point_v<T>)
					{
						if constexpr (std::is_signed_v<T>)
						{
							out << (long long)value;
						}
						else
						{
							out << (unsigned long long)value;
						}
					}
					else
					{
						out << value;
					}

					out << " " << outputName << std::endl;
				}
			}
		}

		template <typename T>
		std::ostream& operator<(std::ostream& out, const T& value)
		{
			typedef std::remove_cvref_t<T> Type;

			if constexpr (std::is_same_v<Type, unsigned char> || std::is_same_v<Type, char>)
			{
				return out << (unsigned int)value;
			}
			else if constexpr (std::is_integral_v<Type> && !std::is_floating_point_v<T>)
			{
				if constexpr (std::is_signed_v<Type>)
				{
					return out << (long long)value;
				}
				else
				{
					return out << (unsigned long long)value;
				}
			}
			else
			{
				return out << value;
			}
		}

		template <typename HandlerType>
		struct StackWatch
		{
			HandlerType& Handler;

			StackWatch(HandlerType& handler, const char* name) : Handler(handler)
			{
				Push(name);
			}

			~StackWatch()
			{
				--Handler.StackDepth;
			}

			template <typename T1, typename... T>
			StackWatch(HandlerType& handler, const char* name, const T1& arg1, const T&... args) : Handler(handler)
			{
				std::stringstream out;
				((out << name < arg1) < ... < args);

				Push(out.str().c_str());
			}

			void Push(const char* name)
			{
				if constexpr (PrintOutput || PrintErrors)
				{
					DataStream& stream = Handler.PacketStream();

					if (!(!PrintOutput && !stream.DiscardErrors && (stream.SuppressErrors || !stream.PrintOutput)))
					{
						std::ostream& out = PrintOutput ? std::cout : Handler.FoundValues;

						out << Handler.Tabs() << name << std::endl;
					}
				}

				++Handler.StackDepth;
			}
		};
	}
}