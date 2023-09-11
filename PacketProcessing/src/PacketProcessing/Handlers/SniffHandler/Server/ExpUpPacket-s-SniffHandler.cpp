#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ExpUpPacket>(const Server::ExpUpPacket& packet)
		{
			
		}
	}
}
