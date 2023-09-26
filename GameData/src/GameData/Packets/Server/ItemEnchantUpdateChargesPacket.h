#pragma once

#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ItemEnchantUpdateChargesPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemEnchantUpdateChargesPacket
			{
				struct CatalystEntry
				{
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				};
				
				unsigned int ChargeCount = 0;
				unsigned int CatalystWeight = 0;
				std::vector<CatalystEntry> Catalysts;
				float SuccessRate = 0;
				float UnknownRate2 = 0;
				float UnknownRate3 = 0;
				float CatalystTotalRate = 0;
				float ChargeTotalRate = 0;
			};
		}
	}
}
