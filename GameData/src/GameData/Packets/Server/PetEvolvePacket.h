#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetEvolvePacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int Amount = 0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
