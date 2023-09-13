#pragma once

#include <vector>
#include <GameData/Data/SkillTreePageData.h>
#include <GameData/Enums/Handles.h>

namespace Maple
{
	namespace Game
	{
		struct SkillTreePageData
		{
			struct SkillEntry
			{
				bool Notify = false;
				bool Enabled = false;
				bool CoreSkill = false;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
			};
			
			std::vector<SkillEntry> Skills;
		};
	}
}
