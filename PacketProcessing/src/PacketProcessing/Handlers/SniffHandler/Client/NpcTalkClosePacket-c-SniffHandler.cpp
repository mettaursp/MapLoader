#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkClosePacket>(const Client::NpcTalkClosePacket& packet)
		{
			
		}
	}
}
