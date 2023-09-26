#pragma once

#include <vector>
#include <GameData/Packets\Server/BuyPeriodData.h>

namespace Maple
{
	namespace Game
	{
		struct BuyPeriodData
		{
			enum class DayOfWeekEnum : unsigned char
			{
				Sunday = 1,
				Monday = 2,
				Tuesday = 3,
				Wednesday = 4,
				Thursday = 5,
				Friday = 6,
				Saturday = 7
			};
			
			struct DayTimeEntry
			{
				unsigned int StartTime = 0;
				unsigned int EndTime = 0;
			};
			
			struct DayEntry
			{
				DayOfWeekEnum DayOfWeek = (DayOfWeekEnum)0;
			};
			
			bool HasSpecificTime = false;
			unsigned long long StartTime = 0;
			unsigned long long EndTime = 0;
			bool HasSpecificDays = false;
			std::vector<DayTimeEntry> DayTimes;
			std::vector<DayEntry> Days;
		};
	}
}
