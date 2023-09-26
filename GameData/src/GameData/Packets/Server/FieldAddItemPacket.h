#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddItemPacket
			{
				Enum::ItemEntityId ObjectId = (Enum::ItemEntityId)0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				unsigned int Amount = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Vector3S Position;
				Enum::CharacterId OwnerId = (Enum::CharacterId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
