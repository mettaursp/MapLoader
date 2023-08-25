#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageHealPacket>(const Server::SkillDamageHealPacket& packet)
		{
			
		}
	}
}
