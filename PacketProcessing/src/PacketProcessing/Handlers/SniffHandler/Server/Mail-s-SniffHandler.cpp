#include "./../SniffHandler.h"

#include <GameData/Packets\Server/MailData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailLoadPacket>(const Server::MailLoadPacket& packet)
		{
			for (const auto& entry : packet.Mail)
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					if (entry.AttachedItems.size())
					{
						std::cout << TimeStamp << "listing mail" << std::endl;
					}
				}

				for (const auto& attachment : entry.AttachedItems)
				{
					Item* item = RegisterItem(attachment.ItemInstanceId, attachment.ItemId);

					item->Amount = attachment.Amount;
					item->Rarity = attachment.Rarity;

					if constexpr (ParserUtils::Packets::PrintPacketOutput)
					{
						std::cout << "\twith attachment " << PrintItem{ Field, attachment.ItemInstanceId } << std::endl;
						std::cout << PrintItemStats{ Field, attachment.ItemInstanceId, 2 };
					}
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailSendCustomConfirmPacket>(const Server::MailSendCustomConfirmPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailReadPacket>(const Server::MailReadPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailErrorPacket>(const Server::MailErrorPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailCollectingPacket>(const Server::MailCollectingPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailUpdateReadTimePacket>(const Server::MailUpdateReadTimePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailDeletePacket>(const Server::MailDeletePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailReceivePacket>(const Server::MailReceivePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailExpireNotificationPacket>(const Server::MailExpireNotificationPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailStartListPacket>(const Server::MailStartListPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailEndListPacket>(const Server::MailEndListPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailError2Packet>(const Server::MailError2Packet& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::MailReceiveGiftNotificationPacket>(const Server::MailReceiveGiftNotificationPacket& packet)
		{
			
		}
	}
}
