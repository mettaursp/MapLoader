#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::LogInPacket>(const Client::LogInPacket& packet)
		{
			
		}
	}
}
