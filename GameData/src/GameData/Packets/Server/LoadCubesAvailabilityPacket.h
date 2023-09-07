#pragma once

#include <vector>
#include <GameData/Packets\Server/LoadCubesAvailabilityPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LoadCubesAvailabilityPacket
			{
				struct PlotAvailability
				{
					unsigned int PlotId = 0;
					bool IsTaken = false;
				};
				
				std::vector<PlotAvailability> AvailabilityData;
			};
		}
	}
}
