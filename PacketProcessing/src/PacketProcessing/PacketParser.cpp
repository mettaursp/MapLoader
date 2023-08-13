#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void ParsePacket<0, false, 0>(ParserUtils::DataStream& stream) { }

		void ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode)
		{
			struct PacketVersionData
			{
				size_t MinServerOpcode = 0;
				size_t MinClientOpcode = 0;
				std::vector<PacketParserCallback> ServerCallbacks;
				std::vector<PacketParserCallback> ClientCallbacks;
			};

			static const std::vector<PacketVersionData> versions = {
				{
					71, 65535,
					{
						&ParsePacket<2546, Server, 71>
					},
					{ }
				}
			};

			if (version < 2546 || version > 2546)
			{
				return;
			}

			const PacketVersionData& versionData = versions[version - 2546];

			size_t minOpcode = isServer ? versionData.MinServerOpcode : versionData.MinClientOpcode;

			const auto& opcodes = isServer ? versionData.ServerCallbacks : versionData.ClientCallbacks;

			if (opcode < minOpcode || opcode - minOpcode >= opcodes.size())
			{
				return;
			}

			if constexpr (ParserUtils::Packets::PrintOutput)
			{
				std::cout << "[" << version << "] Packet Opcode 0x" << std::hex << opcode << std::dec << std::endl; 
			}

			opcodes[opcode - minOpcode](stream);
		}

		template <>
		void ParsePacket<2546, Server, 0x47>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");
			int targetActor_var1 = 0;
			Read<int>("targetActor", stream, targetActor_var1, "\t");
			int instanceId_var2 = 0;
			Read<int>("instanceId", stream, instanceId_var2, "\t");
			int sourceActor_var3 = 0;
			Read<int>("sourceActor", stream, sourceActor_var3, "\t");

			if (mode_var0 == 0)
			{
				int startTime_var4 = 0;
				Read<int>("startTime", stream, startTime_var4, "\t\t");
				int endTime_var5 = 0;
				Read<int>("endTime", stream, endTime_var5, "\t\t");
				int effectId_var6 = 0;
				Read<int>("effectId", stream, effectId_var6, "\t\t");
				short effectLevel_var7 = 0;
				Read<short>("effectLevel", stream, effectLevel_var7, "\t\t");
				int stacks_var8 = 0;
				Read<int>("stacks", stream, stacks_var8, "\t\t");
			}

			if (mode_var0 == 2)
			{
				int flags_var9 = 0;
				Read<int>("flags", stream, flags_var9, "\t\t");

				if ((1 & (flags_var9 >> 0)) == 1)
				{
					int startTime_var10 = 0;
					Read<int>("startTime", stream, startTime_var10, "\t\t\t");
					int endTime_var11 = 0;
					Read<int>("endTime", stream, endTime_var11, "\t\t\t");
					int effectId_var12 = 0;
					Read<int>("effectId", stream, effectId_var12, "\t\t\t");
					short effectLevel_var13 = 0;
					Read<short>("effectLevel", stream, effectLevel_var13, "\t\t\t");
					int stacks_var14 = 0;
					Read<int>("stacks", stream, stacks_var14, "\t\t\t");
				}

				if ((1 & (flags_var9 >> 1)) == 1)
				{
					long long shieldHealth_var15 = 0;
					Read<long long>("shieldHealth", stream, shieldHealth_var15, "\t\t\t");
				}
			}
		}

	}
}
