#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePacket>(const Server::CharacterListDeletePacket& packet)
		{
			
		}
	}
}
