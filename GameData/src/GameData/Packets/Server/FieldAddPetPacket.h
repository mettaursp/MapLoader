#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Data/ActorBasicStat.h>
#include <GameData/Enums/Handles.h>
#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddPetPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::NpcId PetSkinId = (Enum::NpcId)0;
				Enum::NpcId PetNpcId = (Enum::NpcId)0;
				Vector3S Position;
				Vector3S Rotation;
				float Scale = 0;
				Enum::ActorId OwnerActorId = (Enum::ActorId)0;
				Maple::Game::ActorBasicStat Hp = {
					.Type = Enum::StatAttributeBasic::Hp
				};
				Maple::Game::ActorBasicStat AttackSpeed = {
					.Type = Enum::StatAttributeBasic::AttackSpeed
				};
				Enum::ItemInstanceId PetItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short Level = 0;
				unsigned short PetTaming = 0;
				std::wstring Name;
			};
		}
	}
}
