#pragma once

#include <GameData/Packets\Server/PetProfileData.h>
#include <GameData/Enums/MapleHandles.h>

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
