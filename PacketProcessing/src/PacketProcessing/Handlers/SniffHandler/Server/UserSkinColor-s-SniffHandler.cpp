#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserSkinColorData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserSkinColorPacket>(const Server::UserSkinColorPacket& packet)
		{
			
		}
	}
}
