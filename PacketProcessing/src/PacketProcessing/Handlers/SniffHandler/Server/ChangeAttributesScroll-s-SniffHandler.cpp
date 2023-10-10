#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ChangeAttributesData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(const Server::ChangeAttributesScrollUseScrollPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollUseOnItemPacket>(const Server::ChangeAttributesScrollUseOnItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollApplyPacket>(const Server::ChangeAttributesScrollApplyPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollErrorPacket>(const Server::ChangeAttributesScrollErrorPacket& packet)
		{
			
		}
	}
}
