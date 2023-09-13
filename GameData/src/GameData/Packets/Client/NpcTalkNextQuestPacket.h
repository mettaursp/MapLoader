#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Packets\Client/NpcTalkNextQuestPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
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
		}
	}
}
