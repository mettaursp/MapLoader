#include "./../SniffHandler.h"

#include <GameData/Packets\Server/VersionResultData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::VersionResultPacket>(const Server::VersionResultPacket& packet)
		{
			
		}
	}
}
