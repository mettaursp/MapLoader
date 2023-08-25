#pragma once

#include <vector>

#include <ParserUtils/DataStream.h>

#include "Handlers/SniffHandler/SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		typedef SniffHandler PacketHandler;

		void ParsePacket(PacketHandler& handler, unsigned short version, bool isServer, unsigned short opcode);

		const bool ServerPacket = true;
		const bool ClientPacket = false;

		template <short Version, bool IsServer, short Opcode>
		void ParsePacket(PacketHandler& handler) { }

		template <>
		void ParsePacket<0, false, 0>(PacketHandler& handler);

		typedef void (*PacketParserCallback)(PacketHandler& handler);

		struct PacketOpcodeData
		{
			const char* Name = nullptr;
			PacketParserCallback Callback = nullptr;
		};

		struct PacketVersionData
		{
			size_t MinServerOpcode = 0;
			size_t MinClientOpcode = 0;
			std::vector<PacketOpcodeData> ServerCallbacks;
			std::vector<PacketOpcodeData> ClientCallbacks;
		};

		template <typename T>
		void PacketParsed(const T& packet) {}
	}
}