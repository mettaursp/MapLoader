#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SkillCastPacket>(const Client::SkillCastPacket& packet)
		{
			
		}
	}
}
