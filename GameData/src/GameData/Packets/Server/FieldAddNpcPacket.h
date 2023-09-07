#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Data/ActorBasicStat.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <vector>
#include <GameData/Packets\Server/FieldAddNpcPacket.h>
#include <GameData/Data/AdditionalEffect.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddNpcPacket
			{
				struct Skill
				{
					Enum::SkillId SkillId;
					Enum::SkillLevel SkillLevel;
				};
				
				Enum::ActorId ActorId;
				Enum::NpcId NpcId;
				Vector3S Position;
				Vector3S Rotation;
				std::string KfmName;
				Maple::Game::ActorBasicStat Hp = {
					.Type = Enum::StatAttributeBasic::Hp
				};
				Maple::Game::ActorBasicStat MoveSpeed = {
					.Type = Enum::StatAttributeBasic::MoveSpeed
				};
				bool IsDead = false;
				std::vector<Maple::Game::AdditionalEffect> Effects;
				Enum::ItemInstanceId PetItemInstanceId;
				unsigned short Level = 0;
				std::wstring SpawnEffect;
				std::vector<Skill> Skills;
				long long HiddenHpAdd = 0;
			};
		}
	}
}
