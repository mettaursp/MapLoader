#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PlayInstrumentStartImprovisePacket.h>
#include <GameData/Packets\Server/PlayInstrumentPlayNotePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStopImprovisePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStartScorePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStopScorePacket.h>
#include <GameData/Packets\Server/PlayInstrumentLeaveEnsemblePacket.h>
#include <GameData/Packets\Server/PlayInstrumentCreateScoreResponsePacket.h>
#include <GameData/Packets\Server/PlayInstrumentUpdateScoreUsesPacket.h>
#include <GameData/Packets\Server/PlayInstrumentViewMusicPacket.h>
#include <GameData/Packets\Server/PlayInstrumentEffectPacket.h>
#include <GameData/Packets\Server/PlayInstrumentWritePlayDialogPacket.h>

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
