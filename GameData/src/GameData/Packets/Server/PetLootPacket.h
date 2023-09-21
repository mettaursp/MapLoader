#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/PetLootSettingsData.h>

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
