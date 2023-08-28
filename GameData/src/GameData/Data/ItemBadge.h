#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Enums/BadgeType.h>
#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemBadge
		{
			Enum::BadgeType Type;
			std::wstring Id;
			Enum::BadgeId BadgeId;
			bool Transparency[10] = {};
			Enum::PetId PetSkinId;
		};
	}
}
