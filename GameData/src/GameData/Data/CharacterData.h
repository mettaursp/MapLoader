#pragma once

#include <GameData/Data/ActorBasicStat.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Player.h>
#include <string>
#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Data/DyeColor.h>
#include <GameData/Data/CharacterData.h>
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
				Enum::ClubId ClubId;
				std::wstring ClubName;
			};
			
			struct UnknownItem
			{
				long long HasClub = 0;
			};
			
			Enum::AccountId AccountId;
			Enum::CharacterId CharacterId;
			std::wstring Name;
			Enum::Gender Gender;
			Enum::MapId MapId;
			Enum::MapInstanceId MapInstanceId;
			unsigned short Level = 0;
			Enum::ChannelId Channel;
			Enum::JobCode JobCode;
			Enum::JobId Job;
			ActorBasicStat Hp = {
				.Type = Enum::StatAttributeBasic::Hp
			};
			long StorageCooldown;
			long DoctorCooldown;
			Enum::MapId ReturnMapId;
			Vector3S ReturnPosition;
			int GearScore = 0;
			DyeColor SkinColor;
			long CreationTime;
			int CombatTrophyCount = 0;
			int AdventureTrophyCount = 0;
			int LifestyleTrophyCount = 0;
			Enum::GuildId GuildId;
			std::wstring GuildName;
			std::wstring GuildMotto;
			std::wstring ProfileUrl;
			std::vector<ClubEntry> Clubs;
			MasteryData Mastery;
			std::wstring Username;
			Enum::SessionId SessionId;
			std::vector<UnknownItem> UnknownItems;
			long Birthday;
			int PrestigeLevel = 0;
			std::vector<UnknownItem> UnknownItems2;
			std::vector<UnknownItem> UnknownItems3;
		};
	}
}
