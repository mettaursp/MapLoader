#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantFailPacket>(const Server::ItemEnchantFailPacket& packet)
		{
			
		}
	}
}
