#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesExpirationPacket>(const Server::LoadCubesExpirationPacket& packet)
		{
			
		}
	}
}