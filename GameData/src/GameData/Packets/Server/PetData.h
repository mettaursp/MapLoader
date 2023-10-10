#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>
#include <string>
#include <vector>

namespace Maple
{
	namespace Game
	{
		struct PetLootSettingsData
		{
			bool Mesos = false;
			bool Merets = false;
			bool Other = false;
			bool Currency = false;
			bool Equipment = false;
			bool Consumable = false;
			bool Gemstone = false;
			bool Dropped = false;
			Enum::Rarity MinRarity = (Enum::Rarity)0;
			bool Enabled = false;
		};
		
		struct PetProfileData
		{
			std::wstring Name;
			unsigned long long Exp = 0;
			unsigned short Level = 0;
		};
		
		struct FieldPetData
		{
			bool HasFieldPet = false;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			ItemData ItemData;
		};
		
		struct PetPotionSettingsData
		{
			struct SlotEntry
			{
				unsigned int ThresholdIndex = 0;
				float Threshold = 0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
			};
			
			std::vector<SlotEntry> Slots;
		};
	}
}
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetInventoryStartListPacket
			{
			};
			
			struct PetInventoryListItemsPacket
			{
				struct SlotEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					unsigned short Slot = 0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<SlotEntry> Slots;
			};
			
			struct PetInventoryMoveItemPacket
			{
				Enum::ItemInstanceId SourceItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short SourceSlot = 0;
				Enum::ItemInstanceId DestinationItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short DestinationSlot = 0;
			};
			
			struct PetInventoryUpdateAmountPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned int Amount = 0;
			};
			
			struct PetInventoryRemoveItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetInventoryStoreItemPacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short Slot = 0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct PetLapisSnarePacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
			};
			
			struct PetErrorPacket
			{
			};
			
			struct PetEvolvePointsPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				unsigned int Points = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetEvolvePacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int Amount = 0;
				Maple::Game::ItemData ItemData;
			};
			
			struct PetOtherPetInfoPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct PetSummonedNoticePacket
			{
				bool IsSummoned = false;
			};
			
			struct PetLevelUpPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				unsigned int Level = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetFusionPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				unsigned long long Exp = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetInfoPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetProfileData PetProfile;
				Maple::Game::PetPotionSettingsData PetPotionSettings;
				Maple::Game::PetLootSettingsData PetLootSettings;
			};
			
			struct PetLoadCollectionPacket
			{
				struct PetEntry
				{
					Enum::PetId PetId = (Enum::PetId)0;
					Enum::Rarity PetRarity = (Enum::Rarity)0;
				};
				
				std::vector<PetEntry> Pets;
			};
			
			struct PetPotionPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetPotionSettingsData PetPotionSettings;
			};
			
			struct PetAddCollectionPacket
			{
				Enum::PetId PetId = (Enum::PetId)0;
				Enum::Rarity PetRarity = (Enum::Rarity)0;
			};
			
			struct PetUnknownFieldPetPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::FieldPetData FieldPet;
			};
			
			struct PetLootPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetLootSettingsData PetLootSettings;
			};
			
			struct PetRenamePacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetProfileData PetProfile;
			};
			
			struct PetRemovePacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetFusionDialogPacket
			{
				unsigned int FusionCount = 0;
			};
			
			struct PetAddPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ActorId PetActorId = (Enum::ActorId)0;
				Maple::Game::FieldPetData FieldPet;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetSoundPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
			};
		}
	}
}
