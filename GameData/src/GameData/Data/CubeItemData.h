#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/ItemUgc.h>

namespace Maple
{
	namespace Game
	{
		struct CubeItemData
		{
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			bool IsUgc = false;
			ItemUgc Ugc;
		};
	}
}
