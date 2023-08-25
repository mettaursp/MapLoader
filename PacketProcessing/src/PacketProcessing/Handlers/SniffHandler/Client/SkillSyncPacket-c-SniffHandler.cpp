#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncPacket>(const Client::SkillSyncPacket& packet)
		{
			
		}
	}
}
