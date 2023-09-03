#pragma once

#include <GameData/Enums/JobId.h>
#include <GameData/Enums/JobCode.h>
#include <GameData/Data/SkillTreePageData.h>

namespace Maple
{
	namespace Game
	{
		struct SkillTreeData
		{
			Enum::JobCode JobCode;
			Enum::JobId Job;
			SkillTreePageData Active;
			SkillTreePageData Passive;
			SkillTreePageData Special;
			SkillTreePageData Consumable;
		};
	}
}
