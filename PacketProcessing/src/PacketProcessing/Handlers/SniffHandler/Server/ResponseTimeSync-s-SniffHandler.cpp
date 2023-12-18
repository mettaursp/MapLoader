#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ResponseTimeSyncData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncInitializePacket>(const Server::ResponseTimeSyncInitializePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncResetFieldsPacket>(const Server::ResponseTimeSyncResetFieldsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncRequestPacket>(const Server::ResponseTimeSyncRequestPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncSetTimePacket>(const Server::ResponseTimeSyncSetTimePacket& packet)
		{
			
		}
	}
}
