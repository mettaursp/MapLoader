#include "./../SniffHandler.h"

#include <GameData/Packets\Server/SkillSyncData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillSyncPacket>(const Server::SkillSyncPacket& packet)
		{
			
		}
	}
}
