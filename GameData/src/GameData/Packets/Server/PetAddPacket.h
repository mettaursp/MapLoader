#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/FieldPetData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetAddPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::ActorId PetActorId = (Enum::ActorId)0;
				Maple::Game::FieldPetData FieldPet;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
