#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/PetPotionSettingsData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetPotionPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetPotionSettingsData PetPotionSettings;
			};
		}
	}
}
