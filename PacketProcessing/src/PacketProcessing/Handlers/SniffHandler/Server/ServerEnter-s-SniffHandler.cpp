#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ServerEnterData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ServerEnterPacket>(const Server::ServerEnterPacket& packet)
		{
			PlayerId = packet.PlayerActorId;
			CharacterId = packet.CharacterId;
		}
	}
}
