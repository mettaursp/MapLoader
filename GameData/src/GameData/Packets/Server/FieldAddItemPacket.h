#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Rarity.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddItemPacket
			{
				Enum::ItemEntityId ObjectId;
				Enum::ItemId ItemId;
				unsigned int Amount = 0;
				Enum::ItemInstanceId ItemInstanceId;
				Vector3S Position;
				Enum::CharacterId OwnerId;
				Enum::Rarity Rarity;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
