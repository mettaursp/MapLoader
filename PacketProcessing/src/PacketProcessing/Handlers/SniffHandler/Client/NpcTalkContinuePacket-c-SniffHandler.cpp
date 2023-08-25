#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkContinuePacket>(const Client::NpcTalkContinuePacket& packet)
		{
			
		}
	}
}
