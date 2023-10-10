#pragma once

#include <string>
#include <GameData/Data/PacketCommon.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>

namespace Maple
{
	namespace Game
	{
		struct CharacterListEntry
		{
			CharacterData Character;
			std::wstring ProfileUrl;
			unsigned long long DeleteTime = 0;
			CharacterEquipment Equipment;
		};
	}
}
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListCancelDeletePacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				unsigned int MessageId = 0;
			};
			
			struct CharacterListDeletePendingPacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				unsigned int MessageId = 0;
				unsigned long long DeleteTime = 0;
			};
			
			struct CharacterListAddPacket
			{
				Maple::Game::CharacterListEntry Character;
			};
			
			struct CharacterListDeletePacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
			
			struct CharacterListChangeNamePacket
			{
				unsigned int Confirm = 0;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				std::wstring Name;
			};
			
			struct CharacterListLoadPacket
			{
				std::vector<Maple::Game::CharacterListEntry> Characters;
			};
		}
	}
}
