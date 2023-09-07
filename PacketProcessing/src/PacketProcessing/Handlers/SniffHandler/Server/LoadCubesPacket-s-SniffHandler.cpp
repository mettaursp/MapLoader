#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPacket>(const Server::LoadCubesPacket& packet)
		{
			
		}
	}
}
