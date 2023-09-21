#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/PetPotionSettingsData.h>

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
