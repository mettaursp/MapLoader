#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListChangeNamePacket>(const Server::CharacterListChangeNamePacket& packet)
		{
			
		}
	}
}
