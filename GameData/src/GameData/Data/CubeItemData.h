#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/ItemUgc.h>

namespace Maple
{
	namespace Game
	{
		struct CubeItemData
		{
			Enum::ItemId ItemId;
			Enum::ItemInstanceId ItemInstanceId;
			bool IsUgc = false;
			ItemUgc Ugc;
		};
	}
}
