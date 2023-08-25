#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkNextQuestPacket>(const Client::NpcTalkNextQuestPacket& packet)
		{
			
		}
	}
}
