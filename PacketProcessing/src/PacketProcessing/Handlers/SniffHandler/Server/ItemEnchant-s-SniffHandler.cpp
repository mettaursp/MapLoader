#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemEnchantBeginPacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateExpPacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateChargesPacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateIngredientsPacket.h>
#include <GameData/Packets\Server/ItemEnchantSuccessPacket.h>
#include <GameData/Packets\Server/ItemEnchantFailPacket.h>
#include <GameData/Packets\Server/ItemEnchantErrorPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantBeginPacket>(const Server::ItemEnchantBeginPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateExpPacket>(const Server::ItemEnchantUpdateExpPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateChargesPacket>(const Server::ItemEnchantUpdateChargesPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(const Server::ItemEnchantUpdateIngredientsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantSuccessPacket>(const Server::ItemEnchantSuccessPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantFailPacket>(const Server::ItemEnchantFailPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantErrorPacket>(const Server::ItemEnchantErrorPacket& packet)
		{
			
		}
	}
}
