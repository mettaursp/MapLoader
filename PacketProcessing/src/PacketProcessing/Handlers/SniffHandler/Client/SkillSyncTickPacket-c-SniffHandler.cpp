#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncTickPacket>(const Client::SkillSyncTickPacket& packet)
		{
			
		}
	}
}
