#include "./../SniffHandler.h"

#include <GameData/Packets\Client/StateSkillPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::StateSkillPacket>(const Client::StateSkillPacket& packet)
		{
			
		}
	}
}