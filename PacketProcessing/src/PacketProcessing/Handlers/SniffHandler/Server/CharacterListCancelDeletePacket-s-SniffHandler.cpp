#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListCancelDeletePacket>(const Server::CharacterListCancelDeletePacket& packet)
		{
			
		}
	}
}
