#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantPacket>(const Client::NpcTalkEnchantPacket& packet)
		{
			
		}
	}
}
