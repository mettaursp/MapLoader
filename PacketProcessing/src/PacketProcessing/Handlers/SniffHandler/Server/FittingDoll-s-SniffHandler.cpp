#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FittingDollLoadPacket.h>
#include <GameData/Packets\Server/FittingDollRemovePacket.h>
#include <GameData/Packets\Server/FittingDollPutOnItemPacket.h>
#include <GameData/Packets\Server/FittingDollRemoveItemPacket.h>
#include <GameData/Packets\Server/FittingDollErrorPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FittingDollLoadPacket>(const Server::FittingDollLoadPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemovePacket>(const Server::FittingDollRemovePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollPutOnItemPacket>(const Server::FittingDollPutOnItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemoveItemPacket>(const Server::FittingDollRemoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollErrorPacket>(const Server::FittingDollErrorPacket& packet)
		{
			
		}
	}
}
