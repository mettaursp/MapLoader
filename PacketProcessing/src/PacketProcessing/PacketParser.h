#pragma once

#include "PacketParserBase.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void ParsePacket<12, ClientPacket, 0x21>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x2>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(ParserUtils::DataStream& stream);

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(ParserUtils::DataStream& stream);

	}
}
