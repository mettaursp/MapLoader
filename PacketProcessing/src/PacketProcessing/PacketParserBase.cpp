#include "PacketParserBase.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void ParsePacket<0, false, 0>(PacketHandler& handler) { }

		void ParsePacket(PacketHandler& handler, unsigned short version, bool isServer, unsigned short opcode)
		{
			size_t versionIndex = version == 12 ? 0 : VersionIndices[std::min(39, std::max(version, (unsigned short)2464) - 2464)];
			const PacketVersionData& versionData = Versions[versionIndex];
		
			size_t minOpcode = isServer ? versionData.MinServerOpcode : versionData.MinClientOpcode;
		
			const auto& opcodes = isServer ? versionData.ServerCallbacks : versionData.ClientCallbacks;
		
			if (opcode < minOpcode || opcode - minOpcode >= opcodes.size())
			{
				return;
			}
		
			if constexpr (ParserUtils::Packets::PrintOutput)
			{
				std::cout << "[" << version << "] Packet Opcode 0x" << std::hex << opcode << std::dec << ": " << opcodes[opcode - minOpcode].Name << std::endl;
			}
		
			opcodes[opcode - minOpcode].Callback(handler);
		}
	}
}