#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillRegionSkillPacket>(const Client::SkillRegionSkillPacket& packet)
		{
			
		}
	}
}
