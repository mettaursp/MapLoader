#include "./../SniffHandler.h"

#include <GameData/Packets\Server/MailLoadPacket.h>
#include <GameData/Packets\Server/MailSendCustomConfirmPacket.h>
#include <GameData/Packets\Server/MailReadPacket.h>
#include <GameData/Packets\Server/MailErrorPacket.h>
#include <GameData/Packets\Server/MailCollectingPacket.h>
#include <GameData/Packets\Server/MailUpdateReadTimePacket.h>
#include <GameData/Packets\Server/MailDeletePacket.h>
#include <GameData/Packets\Server/MailReceivePacket.h>
#include <GameData/Packets\Server/MailExpireNotificationPacket.h>
#include <GameData/Packets\Server/MailStartListPacket.h>
#include <GameData/Packets\Server/MailEndListPacket.h>
#include <GameData/Packets\Server/MailError2Packet.h>
#include <GameData/Packets\Server/MailReceiveGiftNotificationPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailLoadPacket>(const Server::MailLoadPacket& packet)
		{
			
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
