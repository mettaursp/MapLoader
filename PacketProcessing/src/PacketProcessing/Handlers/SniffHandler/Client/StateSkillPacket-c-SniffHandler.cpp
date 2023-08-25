#include "./../SniffHandler.h"

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
