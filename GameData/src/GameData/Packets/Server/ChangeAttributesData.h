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
			
			struct ChangeAttributesScrollApplyPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesScrollUseOnItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesScrollUseScrollPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct ChangeAttributesErrorPacket
			{
			};
			
			struct ChangeAttributesAddPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesPreviewPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct ChangeAttributesScrollPreviewItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
