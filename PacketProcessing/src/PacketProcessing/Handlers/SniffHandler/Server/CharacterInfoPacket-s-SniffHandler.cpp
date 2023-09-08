#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet)
		{
			CheckBaseStats(packet.Details.JobCode, packet.Details.Level, packet.Details.Stats, Version != 12);
		}
	}
}
