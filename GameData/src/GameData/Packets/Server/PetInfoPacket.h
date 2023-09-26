#pragma once

#include <GameData/Packets\Server/PetProfileData.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/PetPotionSettingsData.h>
#include <GameData/Packets\Server/PetLootSettingsData.h>

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
