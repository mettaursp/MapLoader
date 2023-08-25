#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillDamagePacket>(const Client::SkillDamagePacket& packet)
		{
			
		}
	}
}
