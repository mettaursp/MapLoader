#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PetData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void printFieldPetData(SniffHandler* handler, const Maple::Game::FieldPetData& fieldPetData)
		{
			Item* item = handler->RegisterItem(fieldPetData.ItemInstanceId, fieldPetData.ItemId);

			item->Amount = 1;
			item->Rarity = fieldPetData.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler->TimeStamp << "adding field pet " << PrintItem{ handler->Field, fieldPetData.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ handler->Field, fieldPetData.ItemInstanceId };
			}
		}

		template <>
		void SniffHandler::PacketParsed<Server::PetAddPacket>(const Server::PetAddPacket& packet)
		{
			printFieldPetData(this, packet.FieldPet);
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
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "inspecting other player's pet " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePacket>(const Server::PetEvolvePacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "successfully evolved pet " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
					std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to evolve pet " << packet.ItemInstanceId << std::endl;
				}
			}
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
			printFieldPetData(this, packet.FieldPet);
		}
	}
}
