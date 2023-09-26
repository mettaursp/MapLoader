#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ChangeAttributesPreviewPacket.h>
#include <GameData/Packets\Server/ChangeAttributesAddPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollPreviewItemPacket.h>
#include <GameData/Packets\Server/ChangeAttributesErrorPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesPreviewPacket>(const Server::ChangeAttributesPreviewPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesAddPacket>(const Server::ChangeAttributesAddPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollPreviewItemPacket>(const Server::ChangeAttributesScrollPreviewItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesErrorPacket>(const Server::ChangeAttributesErrorPacket& packet)
		{
			
		}
	}
}
