#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListAddPacket>(const Server::CharacterListAddPacket& packet)
		{
			
		}
	}
}
