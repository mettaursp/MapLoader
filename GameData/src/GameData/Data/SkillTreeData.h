#pragma once

#include <GameData/Enums/Player.h>
#include <GameData/Data/SkillTreePageData.h>

namespace Maple
{
	namespace Game
	{
		struct SkillTreeData
		{
			Enum::JobCode JobCode;
			Enum::JobId Job;
			Enum::JobTier JobTier;
			SkillTreePageData Active;
			SkillTreePageData Passive;
			SkillTreePageData Special;
			SkillTreePageData Consumable;
		};
	}
}
