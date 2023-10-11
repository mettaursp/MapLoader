#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ChangeAttributesData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesPreviewPacket>(const Server::ChangeAttributesPreviewPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				//*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "previewing attribute changes attributes on " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
					std::cout << PrintItemDataStats{ Field, &packet.ItemData };
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to changing binding on unregistered item instance " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesAddPacket>(const Server::ChangeAttributesAddPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "change attributes selecting item " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to changing binding on unregistered item instance " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesApplyPacket>(const Server::ChangeAttributesApplyPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "changing attributes on " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
					std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to changing binding on unregistered item instance " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesErrorPacket>(const Server::ChangeAttributesErrorPacket& packet)
		{
			
		}
	}
}
