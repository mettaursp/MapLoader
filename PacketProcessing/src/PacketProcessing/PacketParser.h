#pragma once

#include <ParserUtils/DataStream.h>

namespace Networking
{
	namespace Packets
	{
		void ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode);

		const bool Server = true;
		const bool Client = false;

		template <short Version, bool IsServer, short Opcode>
		void ParsePacket(ParserUtils::DataStream& stream)
		{
		}

		template <>
		void ParsePacket<0, false, 0>(ParserUtils::DataStream& stream);

		typedef void (*PacketParserCallback)(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<2546, Server, 0x47>(ParserUtils::DataStream& stream);

	}
}
