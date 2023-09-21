#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FittingDollErrorPacket>(const Server::FittingDollErrorPacket& packet)
		{
			
		}
	}
}
