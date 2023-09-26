#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/FieldPetData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetUnknownFieldPetPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Maple::Game::FieldPetData FieldPet;
			};
		}
	}
}
