#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/FieldPetData.h>

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
