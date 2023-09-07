#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Data/MountData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Data/ItemUgc.h>

namespace Maple
{
	namespace Game
	{
		struct MountData
		{
			struct UnknownEntry
			{
			};
			
			Enum::RideMode RideMode;
			Enum::MountId MountId;
			Enum::ActorId MountObjectId;
			Enum::ItemId ItemId;
			Enum::ItemInstanceId ItemInstanceId;
			ItemUgc Ugc;
			Enum::EffectId EffectId;
			Enum::EffectLevel EffectLevel;
			std::vector<UnknownEntry> UnknownData;
		};
	}
}
