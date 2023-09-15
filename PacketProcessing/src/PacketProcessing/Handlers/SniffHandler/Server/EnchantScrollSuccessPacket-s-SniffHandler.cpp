#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollSuccessPacket>(const Server::EnchantScrollSuccessPacket& packet)
		{
			
		}
	}
}
