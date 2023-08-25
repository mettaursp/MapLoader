#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantUnknownPacket>(const Client::NpcTalkEnchantUnknownPacket& packet)
		{
			
		}
	}
}
