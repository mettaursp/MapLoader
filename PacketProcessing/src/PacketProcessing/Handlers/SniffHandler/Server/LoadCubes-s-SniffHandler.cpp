#include "./../SniffHandler.h"

#include <GameData/Packets\Server/LoadCubesData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPacket>(const Server::LoadCubesPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesAvailabilityPacket>(const Server::LoadCubesAvailabilityPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPlotsPacket>(const Server::LoadCubesPlotsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesExpirationPacket>(const Server::LoadCubesExpirationPacket& packet)
		{
			
		}
	}
}
