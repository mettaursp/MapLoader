#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Packets\Server/LoadCubesPacket.h>
#include <GameData/Data/CubeItemData.h>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LoadCubesPacket
			{
				struct PlotCube
				{
					Vector3S Position;
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					Maple::Game::CubeItemData Data;
					int PlotNumber = 0;
					float RotationZ = 0;
				};
				
				std::vector<PlotCube> CubeData;
			};
		}
	}
}
