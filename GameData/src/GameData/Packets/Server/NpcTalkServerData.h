#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <string>
#include <vector>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Maple
{
	namespace Game
	{
		struct ScriptContentData
		{
			std::wstring Text;
			std::wstring VoiceId;
			std::wstring Illustration;
		};
		
		struct NpcDialogData
		{
			Enum::ScriptId ScriptId = (Enum::ScriptId)0;
			unsigned int ScriptIndex = 0;
			unsigned int Options = 0;
		};
	}
}
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkActionCutscenePacket
			{
			};
			
			struct NpcTalkActionAddOptionPacket
			{
				unsigned int AddOption = 0;
			};
			
			struct NpcTalkActionRewardExpPacket
			{
				unsigned long long Exp = 0;
			};
			
			struct NpcTalkActionMovePlayerPacket
			{
				Enum::PortalId PortalId = (Enum::PortalId)0;
			};
			
			struct NpcTalkActionRewardItemPacket
			{
				struct ItemEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					unsigned int Amount = 0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
			
			struct NpcTalkActionOpenDialogPacket
			{
			};
			
			struct NpcTalkRespondPacket
			{
				unsigned char Flags = 0;
				Enum::QuestId QuestId = (Enum::QuestId)0;
				Maple::Game::NpcDialogData Dialog;
			};
			
			struct NpcTalkUpdatePacket
			{
				Maple::Game::ScriptContentData ScriptContent;
			};
			
			struct NpcTalkContinuePacket
			{
				unsigned char Flags = 0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Maple::Game::NpcDialogData Dialog;
			};
			
			struct NpcTalkAlliancePacket
			{
				unsigned char Flags = 0;
				Maple::Game::NpcDialogData Dialog;
			};
			
			struct NpcTalkActionRewardMesoPacket
			{
				unsigned long long Meso = 0;
			};
			
			struct NpcTalkEndPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				unsigned char Flags = 0;
				Maple::Game::NpcDialogData Dialog;
			};
		}
	}
}
