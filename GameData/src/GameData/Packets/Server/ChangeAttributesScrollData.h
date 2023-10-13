#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ChangeAttributesScrollErrorPacket
			{
			};
			
			struct ChangeAttributesScrollPreviewChangePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesScrollApplyPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesScrollUseScrollPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
