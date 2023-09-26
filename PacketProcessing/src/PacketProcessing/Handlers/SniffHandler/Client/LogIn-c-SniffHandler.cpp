#include "./../SniffHandler.h"

#include <GameData/Packets\Client/LogInPacket.h>
#include <GameData/Packets\Client/LogInAuthTokenPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::LogInPacket>(const Client::LogInPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::LogInAuthTokenPacket>(const Client::LogInAuthTokenPacket& packet)
		{
			
		}
	}
}
