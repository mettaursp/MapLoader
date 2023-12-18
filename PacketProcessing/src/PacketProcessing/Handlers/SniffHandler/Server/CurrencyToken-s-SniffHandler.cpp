#include "./../SniffHandler.h"

#include <GameData/Packets\Server/CurrencyTokenData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CurrencyTokenPacket>(const Server::CurrencyTokenPacket& packet)
		{
			
		}
	}
}
