#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageUpdatePacket>(const Server::FurnishingStorageUpdatePacket& packet)
		{
			
		}
	}
}
