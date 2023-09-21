#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/PetProfileData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetRenamePacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::PetProfileData PetProfile;
			};
		}
	}
}
