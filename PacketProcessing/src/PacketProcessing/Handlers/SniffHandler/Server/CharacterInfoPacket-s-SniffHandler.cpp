#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet)
		{
			
		}
	}
}
