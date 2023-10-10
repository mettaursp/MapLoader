#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/PacketCommon.h>
#include <string>

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
			
			struct LoadCubesAvailabilityPacket
			{
				struct PlotAvailability
				{
					unsigned int PlotId = 0;
					bool IsTaken = false;
				};
				
				std::vector<PlotAvailability> AvailabilityData;
			};
			
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
