#pragma once

#include <string>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/LoadCubesPlotsPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LoadCubesPlotsPacket
			{
				struct PlotInfo
				{
					unsigned int PlotId = 0;
					unsigned int ApartmentNumber = 0;
					std::wstring PlotName;
					Enum::AccountId AccountId = (Enum::AccountId)0;
				};
				
				std::vector<PlotInfo> PlotData;
			};
		}
	}
}
