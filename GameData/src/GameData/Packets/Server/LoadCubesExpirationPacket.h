#pragma once

#include <vector>
#include <GameData/Packets\Server/LoadCubesExpirationPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LoadCubesExpirationPacket
			{
				enum class StateEnum
				{
					Default = 0,
					Taken = 1,
					Unknown = 2,
					Pending = 4
				};
				
				struct SaleState
				{
					unsigned int PlotId = 0;
					unsigned int ApartmentNumber = 0;
					StateEnum State = (StateEnum)0;
					unsigned long long ExpirationTime = 0;
				};
				
				std::vector<SaleState> SaleStateData;
			};
		}
	}
}
