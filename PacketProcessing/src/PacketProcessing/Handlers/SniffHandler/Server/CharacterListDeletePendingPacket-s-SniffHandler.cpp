#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePendingPacket>(const Server::CharacterListDeletePendingPacket& packet)
		{
			
		}
	}
}
