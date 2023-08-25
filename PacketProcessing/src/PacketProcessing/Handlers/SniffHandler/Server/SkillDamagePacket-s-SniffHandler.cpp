#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillDamagePacket>(const Server::SkillDamagePacket& packet)
		{
			
		}
	}
}
