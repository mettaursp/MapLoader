#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(const Client::NpcTalkAllianceQuestAcceptPacket& packet)
		{
			
		}
	}
}
