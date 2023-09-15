#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BindItemPacket>(const Server::BindItemPacket& packet)
		{
			
		}
	}
}
