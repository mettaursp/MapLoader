#include "./../SniffHandler.h"

#include <GameData/Packets\Server/TrophyStartPacket.h>
#include <GameData/Packets\Server/TrophyContentPacket.h>
#include <GameData/Packets\Server/TrophyUpdatePacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TrophyStartPacket>(const Server::TrophyStartPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TrophyContentPacket>(const Server::TrophyContentPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TrophyUpdatePacket>(const Server::TrophyUpdatePacket& packet)
		{
			
		}
	}
}
