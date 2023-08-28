#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Packets\Client/NpcTalkEnchantPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkEnchantPacket
			{
				enum class EventTypeEnum
				{
					Begin = 1,
					InProgress = 2,
					Result = 3
				};
				
				Enum::NpcId NpcId;
				Enum::ScriptId ScriptId;
				EventTypeEnum EventType = EventTypeEnum::Begin;
				Enum::ItemInstanceId ItemInstanceId;
			};
		}
	}
}
