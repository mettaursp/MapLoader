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
			
			const auto& entry = Data->Maps.find((unsigned int)packet.MapId);

			Field.MapId = (unsigned int)packet.MapId;

			if (entry != Data->Maps.end())
			{
				Field.CurrentMap = &entry->second;

				if constexpr (ParserUtils::Packets::PrintOutput)
				{
					Field.PrintedMap = true;

					std::cout << "entered map [" << (unsigned int)packet.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintOutput)
				{
					Field.PrintedMap = true;

					std::cout << "entered map [" << (unsigned int)packet.MapId << "]" << std::endl;
				}
			}
		}
	}
}
