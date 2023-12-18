#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserBattleData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserBattlePacket>(const Server::UserBattlePacket& packet)
		{
			
		}
	}
}
