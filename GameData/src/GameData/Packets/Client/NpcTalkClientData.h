#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkCinematicPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				int Index = 0;
			};
			
			struct NpcTalkAllianceQuestTalkPacket
			{
			};
			
			struct NpcTalkContinuePacket
			{
				int Index = 0;
			};
			
			struct NpcTalkEnchantUnknownPacket
			{
			};
			
			struct NpcTalkEnchantPacket
			{
				enum class EventTypeEnum
				{
					Begin = 1,
					InProgress = 2,
					Result = 3
				};
				
				Enum::NpcId NpcId = (Enum::NpcId)0;
				Enum::ScriptId ScriptId = (Enum::ScriptId)0;
				EventTypeEnum EventType = EventTypeEnum::Begin;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct NpcTalkBeginPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
			
			struct NpcTalkNextQuestPacket
			{
				enum class EventTypeEnum
				{
					Complete = 0,
					Start = 2
				};
				
				Enum::QuestId QuestId = (Enum::QuestId)0;
				EventTypeEnum EventType = EventTypeEnum::Start;
			};
			
			struct NpcTalkAllianceQuestAcceptPacket
			{
				enum class EventTypeEnum
				{
					Complete = 0,
					Start = 2
				};
				
				int Index = 0;
				EventTypeEnum EventType = EventTypeEnum::Start;
			};
			
			struct NpcTalkClosePacket
			{
			};
		}
	}
}
