#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/PetProfileData.h>
#include <GameData/Data/PetPotionSettingsData.h>
#include <GameData/Data/PetLootSettingsData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetInfoPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetProfileData PetProfile;
				Maple::Game::PetPotionSettingsData PetPotionSettings;
				Maple::Game::PetLootSettingsData PetLootSettings;
			};
		}
	}
}
