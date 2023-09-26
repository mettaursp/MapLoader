#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PetAddPacket.h>
#include <GameData/Packets\Server/PetRemovePacket.h>
#include <GameData/Packets\Server/PetSoundPacket.h>
#include <GameData/Packets\Server/PetRenamePacket.h>
#include <GameData/Packets\Server/PetPotionPacket.h>
#include <GameData/Packets\Server/PetLootPacket.h>
#include <GameData/Packets\Server/PetLoadCollectionPacket.h>
#include <GameData/Packets\Server/PetAddCollectionPacket.h>
#include <GameData/Packets\Server/PetInfoPacket.h>
#include <GameData/Packets\Server/PetFusionPacket.h>
#include <GameData/Packets\Server/PetLevelUpPacket.h>
#include <GameData/Packets\Server/PetFusionDialogPacket.h>
#include <GameData/Packets\Server/PetSummonedNoticePacket.h>
#include <GameData/Packets\Server/PetOtherPetInfoPacket.h>
#include <GameData/Packets\Server/PetEvolvePacket.h>
#include <GameData/Packets\Server/PetEvolvePointsPacket.h>
#include <GameData/Packets\Server/PetErrorPacket.h>
#include <GameData/Packets\Server/PetLapisSnarePacket.h>
#include <GameData/Packets\Server/PetUnknownFieldPetPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetAddPacket>(const Server::PetAddPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetRemovePacket>(const Server::PetRemovePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetSoundPacket>(const Server::PetSoundPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetRenamePacket>(const Server::PetRenamePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetPotionPacket>(const Server::PetPotionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetLootPacket>(const Server::PetLootPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetLoadCollectionPacket>(const Server::PetLoadCollectionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetAddCollectionPacket>(const Server::PetAddCollectionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInfoPacket>(const Server::PetInfoPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionPacket>(const Server::PetFusionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetLevelUpPacket>(const Server::PetLevelUpPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionDialogPacket>(const Server::PetFusionDialogPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetSummonedNoticePacket>(const Server::PetSummonedNoticePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetOtherPetInfoPacket>(const Server::PetOtherPetInfoPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePacket>(const Server::PetEvolvePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePointsPacket>(const Server::PetEvolvePointsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetErrorPacket>(const Server::PetErrorPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetLapisSnarePacket>(const Server::PetLapisSnarePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetUnknownFieldPetPacket>(const Server::PetUnknownFieldPetPacket& packet)
		{
			
		}
	}
}
