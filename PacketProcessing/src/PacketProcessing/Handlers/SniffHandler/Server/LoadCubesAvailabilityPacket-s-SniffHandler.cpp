#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesAvailabilityPacket>(const Server::LoadCubesAvailabilityPacket& packet)
		{
			
		}
	}
}
