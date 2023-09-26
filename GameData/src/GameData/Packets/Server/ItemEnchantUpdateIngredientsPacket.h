#pragma once

#include <vector>
#include <GameData/Packets\Server/ItemEnchantUpdateIngredientsPacket.h>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemEnchantUpdateIngredientsPacket
			{
				struct CatalystEntry
				{
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				};
				
				unsigned int CatalystWeight = 0;
				std::vector<CatalystEntry> Catalysts;
			};
		}
	}
}
