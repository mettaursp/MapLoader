#pragma once

#include <string>
#include <GameData/Data/DyeColor.h>
#include <GameData/Data/CharacterEquipment.h>
#include <GameData/Packets\Server/CharacterInfoPacket.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/ActorStats.h>
#include <GameData/Enums/MaplePlayer.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterInfoPacket
			{
				struct CharacterUnlockedTitle
				{
					Enum::TitleId TitleId = (Enum::TitleId)0;
				};
				
				struct CharacterDetails
				{
					Enum::AccountId AccountId = (Enum::AccountId)0;
					Enum::CharacterId CharacterId = (Enum::CharacterId)0;
					std::wstring Name;
					unsigned short Level = 0;
					Enum::JobCode JobCode = (Enum::JobCode)0;
					Enum::JobId Job = (Enum::JobId)0;
					Enum::Gender Gender = (Enum::Gender)0;
					unsigned int PrestigeLevel = 0;
					Maple::Game::ActorStats Stats;
					std::wstring ProfileUrl;
					std::wstring Motto;
					std::wstring GuildName;
					std::wstring GuildRank;
					std::wstring HouseName;
					Enum::MapId PlotMapId = (Enum::MapId)0;
					unsigned int PlotNumber = 0;
					unsigned int ApartmentNumber = 0;
					unsigned int CharacterTitle = 0;
					std::vector<CharacterUnlockedTitle> UnlockedTitles;
					unsigned int TrophyCount = 0;
					unsigned int GearScore = 0;
					unsigned long long LastLoggedIn = 0;
					Maple::Game::DyeColor SkinColor;
					unsigned short MaritalStatus = 0;
					std::wstring Spouse1Name;
					std::wstring Spouse2Name;
					unsigned long long ProposalTimestamp = 0;
				};
				
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				bool Found = false;
				unsigned long long CurrentTime = 0;
				CharacterDetails Details;
				Maple::Game::CharacterEquipment Equipment;
			};
		}
	}
}
