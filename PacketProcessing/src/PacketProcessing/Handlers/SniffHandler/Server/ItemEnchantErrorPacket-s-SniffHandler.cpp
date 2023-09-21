#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantErrorPacket>(const Server::ItemEnchantErrorPacket& packet)
		{
			
		}
	}
}
