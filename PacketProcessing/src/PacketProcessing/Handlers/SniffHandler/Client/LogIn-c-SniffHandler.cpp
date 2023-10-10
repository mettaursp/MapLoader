#include "./../SniffHandler.h"

#include <GameData/Packets\Client/LogInData.h>
#include <GameData/Packets\Client/LogInAuthTokenData.h>

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
