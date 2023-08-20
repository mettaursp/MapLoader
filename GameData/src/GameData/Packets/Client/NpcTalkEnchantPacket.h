#pragma once

#include <GameData/Enums/NpcId.h>
#include <GameData/Enums/ScriptId.h>
#include <GameData/Packets\Client/NpcTalkEnchantPacket.h>
#include <GameData/Enums/ItemInstanceId.h>

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
