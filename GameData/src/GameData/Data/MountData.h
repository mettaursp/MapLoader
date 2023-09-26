#pragma once

#include <vector>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemUgc.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/MountData.h>

namespace Maple
{
	namespace Game
	{
		struct MountData
		{
			struct UnknownEntry
			{
			};
			
			Enum::RideMode RideMode = (Enum::RideMode)0;
			Enum::MountId MountId = (Enum::MountId)0;
			Enum::ActorId MountObjectId = (Enum::ActorId)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			ItemUgc Ugc;
			Enum::EffectId EffectId = (Enum::EffectId)0;
			Enum::EffectLevel EffectLevel = (Enum::EffectLevel)0;
			std::vector<UnknownEntry> UnknownData;
		};
	}
}
