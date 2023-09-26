#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/PetLootSettingsData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetLootPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetLootSettingsData PetLootSettings;
			};
		}
	}
}
