#include "./../SniffHandler.h"

#include <GameData/Packets\Server/CharacterInfoData.h>
#include <PacketProcessing/PacketLogging.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet)
		{
			CheckBaseStats(packet.Details.JobCode, packet.Details.Level, packet.Details.Stats, Version != 12);

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "logging equipment for character " << packet.Details.Name << std::endl;
			}

			LogEquipment(this, packet.Equipment);
		}
	}
}
