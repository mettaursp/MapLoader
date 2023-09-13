#pragma once

#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Enums/Item.h>

namespace Maple
{
	namespace Game
	{
		struct ItemBadge
		{
			Enum::BadgeType Type = (Enum::BadgeType)0;
			std::wstring Id;
			Enum::BadgeId BadgeId = (Enum::BadgeId)0;
			bool Transparency[10] = {};
			Enum::PetId PetSkinId = (Enum::PetId)0;
		};
	}
}
