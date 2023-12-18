#pragma once

#include <GameData/Enums/MapleStats.h>
#include <GameData/Data/BasicStat.h>
#include <vector>
#include <GameData/Data/DyeColor.h>
#include <GameData/Data/SpecialStat.h>
#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>
#include <string>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Enums/MaplePlayer.h>
#include <GameData/Data/SkillTreePageData.h>

namespace Maple
{
	namespace Game
	{
		struct SkillTreeData
		{
			Enum::JobCode JobCode = (Enum::JobCode)0;
			Enum::JobId Job = (Enum::JobId)0;
			Enum::JobTier JobTier = (Enum::JobTier)0;
			SkillTreePageData Active;
			SkillTreePageData Passive;
			SkillTreePageData Special;
			SkillTreePageData Consumable;
		};
		
		struct StateSyncData
		{
		};
		
		struct MasteryData
		{
			int Fishing = 0;
			int Performance = 0;
			int Mining = 0;
			int Foraging = 0;
			int Ranching = 0;
			int Farming = 0;
			int Smithing = 0;
			int Handicraft = 0;
			int Alchemy = 0;
			int Cooking = 0;
			int PetTaming = 0;
		};
		
		struct EffectStats
		{
			unsigned int StartTime = 0;
			unsigned int EndTime = 0;
			Enum::EffectId EffectId = (Enum::EffectId)0;
			Enum::EffectLevel EffectLevel = (Enum::EffectLevel)0;
			unsigned int Stacks = 0;
		};
		
		struct ItemCouple
		{
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Name;
			bool IsCreator = false;
		};
		
		struct ItemMusic
		{
			unsigned int Length = 0;
			unsigned int Instrument = 0;
			std::wstring Title;
			std::wstring Author;
			Enum::CharacterId AuthorId = (Enum::CharacterId)0;
			bool IsLocked = false;
		};
		
		struct ItemBadge
		{
			Enum::BadgeType Type = (Enum::BadgeType)0;
			std::wstring Id;
			Enum::BadgeId BadgeId = (Enum::BadgeId)0;
			bool Transparency[10] = {};
			Enum::PetId PetSkinId = (Enum::PetId)0;
		};
		
		struct ItemPet
		{
			std::wstring Name;
			unsigned long long Exp = 0;
			unsigned int EvolvePoints = 0;
			unsigned int Level = 0;
			bool HasItems = false;
		};
		
		struct ItemBlueprint
		{
		};
		
		struct ItemEnchantment
		{
			unsigned int Level = 0;
			unsigned int EnchantExp = 0;
			unsigned char EnchantCharges = 0;
			bool CanRepackage = false;
			unsigned int Charges = 0;
			std::vector<BasicStat> Basic;
		};
		
		struct BonusStats
		{
			std::vector<BasicStat> Basic;
			std::vector<SpecialStat> Special;
			Enum::ItemId EmpowermentItemId = (Enum::ItemId)0;
		};
		
		struct ItemDecalCustomization
		{
			Vector3S Position1;
			Vector3S Position2;
			Vector3S Position3;
			Vector3S Position4;
		};
		
		struct ActorSpecialStat
		{
			Enum::StatAttributeSpecial Type = (Enum::StatAttributeSpecial)0;
			float Rate = 0;
			float Value = 0;
		};
		
		struct ItemCapCustomization
		{
			Vector3S Position1;
			Vector3S Position2;
			Vector3S Position3;
			Vector3S Position4;
		};
		
		struct ItemBinding
		{
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Name;
		};
		
		struct ItemHairCustomization
		{
			float BackLength = 0;
			Vector3S BackPosition1;
			Vector3S BackPosition2;
			float FrontLength = 0;
			Vector3S FrontPosition1;
			Vector3S FrontPosition2;
		};
		
		struct ItemUgc
		{
			std::wstring FileName;
			std::wstring Name;
			Enum::AccountId AccountId = (Enum::AccountId)0;
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Author;
			unsigned long long CreationTime = 0;
			std::wstring Url;
		};
		
		struct ActorBasicStat
		{
			Enum::StatAttributeBasic Type = (Enum::StatAttributeBasic)0;
			unsigned long long Max = 0;
			unsigned long long Base = 0;
			unsigned long long Current = 0;
			float Rate = 0;
		};
		
		struct ActorStats
		{
			std::vector<ActorBasicStat> Basic;
			std::vector<ActorSpecialStat> Special;
		};
		
		struct ItemStats
		{
			BonusStats Constant;
			BonusStats Static;
			BonusStats Random;
			BonusStats Title;
			BonusStats Empowerment1;
			BonusStats Empowerment2;
			BonusStats Empowerment3;
			BonusStats Empowerment4;
			BonusStats Empowerment5;
		};
		
		struct ItemLimitBreak
		{
			unsigned int Level = 0;
			BonusStats Stats;
		};
		
		struct ItemTransfer
		{
			unsigned int TransferFlags = 0;
			unsigned int RemainingTrades = 0;
			unsigned int RemainingPackages = 0;
			bool IsBound = false;
			ItemBinding Binding;
		};
		
		struct ItemSocket
		{
			struct Slot
			{
				struct GemData
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					bool IsBound = false;
					ItemBinding Binding;
					bool IsLocked = false;
					unsigned long long UnlockTime = 0;
				};
				
				bool HasGem = false;
				GemData Gem;
			};
			
			unsigned char MaxSlots = 0;
			unsigned char UnlockedSlots = 0;
			std::vector<Slot> Sockets;
		};
		
		struct AdditionalEffect
		{
			Enum::ActorId TargetId = (Enum::ActorId)0;
			Enum::EffectInstanceId InstanceId = (Enum::EffectInstanceId)0;
			Enum::ActorId SourceId = (Enum::ActorId)0;
			EffectStats Stats;
			bool Enabled = false;
			long long ShieldHealth = 0;
		};
		
		struct CubeItemData
		{
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			bool IsUgc = false;
			ItemUgc Ugc;
		};
		
		struct MountData
		{
			struct UnknownEntry
			{
			};
			
			Enum::RideMode RideMode = (Enum::RideMode)0;
			Enum::MountId MountId = (Enum::MountId)0;
			Enum::ActorId MountObjectId = (Enum::ActorId)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			ItemUgc Ugc;
			Enum::EffectId EffectId = (Enum::EffectId)0;
			Enum::EffectLevel EffectLevel = (Enum::EffectLevel)0;
			std::vector<UnknownEntry> UnknownData;
		};
		
		struct ItemCustomization
		{
			DyeColor DyeColor;
			ItemCapCustomization Cap;
			ItemHairCustomization Hair;
			ItemDecalCustomization Decal;
		};
		
		struct CharacterData
		{
			struct ClubEntry
			{
				bool HasClub = false;
				Enum::ClubId ClubId = (Enum::ClubId)0;
				std::wstring ClubName;
			};
			
			struct UnknownItem
			{
				long long HasClub = 0;
			};
			
			Enum::AccountId AccountId = (Enum::AccountId)0;
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Name;
			Enum::Gender Gender = (Enum::Gender)0;
			Enum::MapId MapId = (Enum::MapId)0;
			Enum::MapInstanceId MapInstanceId = (Enum::MapInstanceId)0;
			unsigned short Level = 0;
			Enum::ChannelId Channel = (Enum::ChannelId)0;
			Enum::JobCode JobCode = (Enum::JobCode)0;
			Enum::JobId Job = (Enum::JobId)0;
			ActorBasicStat Hp = {
				.Type = Enum::StatAttributeBasic::Hp
			};
			long StorageCooldown;
			long DoctorCooldown;
			Enum::MapId ReturnMapId = (Enum::MapId)0;
			Vector3S ReturnPosition;
			int GearScore = 0;
			DyeColor SkinColor;
			long CreationTime;
			int CombatTrophyCount = 0;
			int AdventureTrophyCount = 0;
			int LifestyleTrophyCount = 0;
			Enum::GuildId GuildId = (Enum::GuildId)0;
			std::wstring GuildName;
			std::wstring GuildMotto;
			std::wstring ProfileUrl;
			std::vector<ClubEntry> Clubs;
			MasteryData Mastery;
			std::wstring Username;
			Enum::SessionId SessionId = (Enum::SessionId)0;
			std::vector<UnknownItem> UnknownItems;
			long Birthday;
			int PrestigeLevel = 0;
			std::vector<UnknownItem> UnknownItems2;
			std::vector<UnknownItem> UnknownItems3;
		};
		
		struct ItemData
		{
			unsigned int Amount = 0;
			unsigned long long CreationTime = 0;
			unsigned long long ExpirationTime = 0;
			unsigned int TimesChanged = 0;
			unsigned int RemainingUses = 0;
			bool IsLocked = false;
			bool UnlockTime = false;
			bool GlamorForges = false;
			ItemCustomization Customization;
			ItemStats Stats;
			ItemEnchantment Enchantment;
			ItemLimitBreak LimitBreak;
			ItemUgc Ugc;
			ItemBlueprint Blueprint;
			ItemPet Pet;
			ItemMusic Music;
			ItemBadge Badge;
			ItemTransfer ItemTransfer;
			ItemSocket ItemSocket;
			ItemCouple ItemCouple;
			ItemBinding Binding;
		};
		
		struct Pet
		{
			Enum::ActorId ActorId = (Enum::ActorId)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			ItemData ItemData;
		};
		
		struct EquipmentData
		{
			Enum::SlotType Slot = (Enum::SlotType)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			std::wstring SlotName;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			ItemData Data;
		};
		
		struct CharacterEquipment
		{
			std::vector<EquipmentData> Equipment;
			std::vector<EquipmentData> Badges;
			bool HasSkin = false;
			bool HasFashion = false;
			std::vector<EquipmentData> Skins;
			std::vector<EquipmentData> Fashion;
		};
	}
}
