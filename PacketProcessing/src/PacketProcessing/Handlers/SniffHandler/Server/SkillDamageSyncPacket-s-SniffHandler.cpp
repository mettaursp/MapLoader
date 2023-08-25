#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageSyncPacket>(const Server::SkillDamageSyncPacket& packet)
		{
			
		}
	}
}
