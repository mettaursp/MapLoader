#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncDamagePacket>(const Client::SkillSyncDamagePacket& packet)
		{
			
		}
	}
}
