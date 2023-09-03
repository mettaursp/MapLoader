#pragma once

#include <GameData/Data/CharacterEquipment.h>
#include <GameData/Packets\Server/CharacterInfoPacket.h>
#include <GameData/Data/DyeColor.h>
#include <vector>
#include <GameData/Enums/StatAttributeSpecial.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Enums/JobId.h>
#include <GameData/Enums/JobCode.h>
#include <GameData/Enums/Gender.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterInfoPacket
			{
				struct CharacterBasicStat
				{
					unsigned long long Max = 0;
					unsigned long long Base = 0;
					unsigned long long Current = 0;
					float Rate = 0;
				};
				
				struct CharacterSpecialStat
				{
					Enum::StatAttributeSpecial Type;
					float Rate = 0;
					float Value = 0;
				};
				
				struct CharacterStats
				{
					std::vector<CharacterBasicStat> Basic;
					std::vector<CharacterSpecialStat> Special;
				};
				
				struct CharacterUnlockedTitle
				{
					unsigned int TitleId = 0;
				};
				
				struct CharacterDetails
				{
					Enum::AccountId AccountId;
					Enum::CharacterId CharacterId;
					std::wstring Name;
					unsigned short Level = 0;
					Enum::JobCode JobCode;
					Enum::JobId Job;
					Enum::Gender Gender;
					unsigned int PrestigeLevel = 0;
					CharacterStats Stats;
					std::wstring ProfileUrl;
					std::wstring Motto;
					std::wstring GuildName;
					std::wstring GuildRank;
					std::wstring HouseName;
					Enum::MapId PlotMapId;
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
				
				Enum::CharacterId CharacterId;
				bool Found = false;
				unsigned long long CurrentTime = 0;
				CharacterDetails Details;
				Maple::Game::CharacterEquipment CharacterEquipment;
			};
		}
	}
}
