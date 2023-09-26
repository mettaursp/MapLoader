#pragma once

#include <GameData/Data/ActorBasicStat.h>
#include <string>
#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Data/DyeColor.h>
#include <GameData/Data/CharacterData.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MaplePlayer.h>
#include <GameData/Data/MasteryData.h>

namespace Maple
{
	namespace Game
	{
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
	}
}
