#include "./../SniffHandler.h"
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestFieldEnterPacket>(const Server::RequestFieldEnterPacket& packet)
		{
			Field = {};
			
			const auto& entry = Data->Maps.find(packet.MapId);
		
			Field.MapId = packet.MapId;
			Field.GameData = Data;
		
			if (entry != Data->Maps.end())
			{
				Field.CurrentMap = &entry->second;
		
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					Field.PrintedMap = true;
		
					std::cout << TimeStamp << "entered map [" << (unsigned int)packet.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					Field.PrintedMap = true;
		
					std::cout << TimeStamp << "entered map [" << (unsigned int)packet.MapId << "]" << std::endl;
				}
			}
		}
	}
}
