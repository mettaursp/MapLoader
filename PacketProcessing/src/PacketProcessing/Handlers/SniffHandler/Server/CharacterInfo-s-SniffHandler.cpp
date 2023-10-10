#include "./../SniffHandler.h"

#include <GameData/Packets\Server/CharacterInfoData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet)
		{
			CheckBaseStats(packet.Details.JobCode, packet.Details.Level, packet.Details.Stats, Version != 12);
		}
	}
}
