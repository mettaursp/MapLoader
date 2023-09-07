#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Item.h>

namespace Maple
{
	namespace Game
	{
		struct Pet
		{
			Enum::ActorId ActorId;
			Enum::ItemId ItemId;
			Enum::ItemInstanceId ItemInstanceId;
			Enum::Rarity Rarity;
			ItemData ItemData;
		};
	}
}
