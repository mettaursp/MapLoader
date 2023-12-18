#include "./../SniffHandler.h"

#include <GameData/Packets\Server/SkillUseData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillUsePacket>(const Server::SkillUsePacket& packet)
		{
			
		}
	}
}
