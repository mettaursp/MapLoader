#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ChangeAttributesErrorPacket
			{
			};
			
			struct ChangeAttributesPreviewChangePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesApplyPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
