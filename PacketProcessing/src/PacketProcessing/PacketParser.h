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
		void ParsePacket<12, ServerPacket, 0x1>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x4>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x6>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x8>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x9>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x4a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xa>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xb>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x4c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xd>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xe>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xf>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x10>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x11>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x52>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x12>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x13>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x14>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x55>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x15>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x16>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x19>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x1c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x1e>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x1f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x20>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x23>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x24>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x25>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x26>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x27>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x28>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2d>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2e>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x2f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x30>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x31>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x33>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x34>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x35>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x36>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x37>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x38>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x39>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3b>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3d>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x3f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5b>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x6c>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x7a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x7d>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x84>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x99>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x9a>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xc1>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xc9>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xca>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xcb>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xce>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xd0>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0xdd>(PacketHandler& handler);

		template <>
		void ParsePacket<12, ServerPacket, 0x105>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xcc>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x25>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x15>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x27>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x97>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x1e>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x23>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x2a>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x37>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x4b>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x51>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x54>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x78>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x7b>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x82>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x98>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xbf>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xc7>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xc8>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xc9>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xce>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0xdb>(PacketHandler& handler);

		template <>
		void ParsePacket<2486, ServerPacket, 0x103>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0xb>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<13, ServerPacket, 0x1c>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xcc>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x27>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x97>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x1e>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x2b>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x23>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x25>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x2a>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x4b>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x51>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x54>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x78>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x7b>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x82>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x98>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xbf>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xc7>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xc8>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xc9>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xce>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0xdb>(PacketHandler& handler);

		template <>
		void ParsePacket<2497, ServerPacket, 0x103>(PacketHandler& handler);

		template <>
		void ParsePacket<2465, ServerPacket, 0x3e>(PacketHandler& handler);

		template <>
		void ParsePacket<2493, ServerPacket, 0x17>(PacketHandler& handler);

		template <>
		void ParsePacket<2493, ServerPacket, 0x49>(PacketHandler& handler);

		template <>
		void ParsePacket<2496, ServerPacket, 0xc>(PacketHandler& handler);

		template <>
		void ParsePacket<2496, ServerPacket, 0x51>(PacketHandler& handler);

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
