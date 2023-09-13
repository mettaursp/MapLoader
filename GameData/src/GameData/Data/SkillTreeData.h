#pragma once

#include <GameData/Enums/Player.h>
#include <GameData/Data/SkillTreePageData.h>

namespace Maple
{
	namespace Game
	{
		struct SkillTreeData
		{
			Enum::JobCode JobCode = (Enum::JobCode)0;
			Enum::JobId Job = (Enum::JobId)0;
			Enum::JobTier JobTier = (Enum::JobTier)0;
			SkillTreePageData Active;
			SkillTreePageData Passive;
			SkillTreePageData Special;
			SkillTreePageData Consumable;
		};
	}
}
