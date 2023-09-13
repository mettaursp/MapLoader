#pragma once

#include "PacketParserBase.h"

namespace Networking
{
	namespace Packets
	{
		const size_t MinVersion = 2464;
		const size_t MaxVersion = 2509;

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x2>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x5>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x21>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x15>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x16>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x6c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x38>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x39>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x4a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5b>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x7a>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x15>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x37>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x78>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x78>(PacketHandler& handler);

		template <>
		void ParsePacket<2493, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2493, ServerPacket, 0x49>(PacketHandler& handler);

		template <>
		void ParsePacket<2496, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2496, ServerPacket, 0x78>(PacketHandler& handler);

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(PacketHandler& handler);

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(PacketHandler& handler);

		template <>
		void ParsePacket<2509, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2509, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2509, ServerPacket, 0x49>(PacketHandler& handler);

		template <>
		void ParsePacket<2509, ServerPacket, 0x78>(PacketHandler& handler);

	}
}
