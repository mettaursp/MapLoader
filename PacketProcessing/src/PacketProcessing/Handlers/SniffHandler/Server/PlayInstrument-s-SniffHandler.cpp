#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PlayInstrumentData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartImprovisePacket>(const Server::PlayInstrumentStartImprovisePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentPlayNotePacket>(const Server::PlayInstrumentPlayNotePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopImprovisePacket>(const Server::PlayInstrumentStopImprovisePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartScorePacket>(const Server::PlayInstrumentStartScorePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopScorePacket>(const Server::PlayInstrumentStopScorePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(const Server::PlayInstrumentLeaveEnsemblePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(const Server::PlayInstrumentCreateScoreResponsePacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "created score " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to create score " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(const Server::PlayInstrumentUpdateScoreUsesPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentViewMusicPacket>(const Server::PlayInstrumentViewMusicPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentEffectPacket>(const Server::PlayInstrumentEffectPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(const Server::PlayInstrumentWritePlayDialogPacket& packet)
		{
			
		}
	}
}
