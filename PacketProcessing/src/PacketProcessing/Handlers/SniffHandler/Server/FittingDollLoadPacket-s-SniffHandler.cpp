#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FittingDollLoadPacket>(const Server::FittingDollLoadPacket& packet)
		{
			
		}
	}
}
