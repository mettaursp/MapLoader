#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <vector>
#include <GameData/Packets\Server/FieldAddNpcPacket.h>
#include <GameData/Data/StatLong.h>
#include <GameData/Data/Stat.h>
#include <GameData/Data/EffectStats.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddNpcPacket
			{
				struct Effect
				{
					Enum::ActorId OwnerId;
					Enum::EffectInstanceId InstanceId;
					Enum::ActorId CasterId;
					Maple::Game::EffectStats Stats;
					bool Enabled = false;
					long long ShieldHealth = 0;
				};
				
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
				Maple::Game::StatLong Hp = {
					.Type = Enum::StatAttributeBasic::Hp
				};
				Maple::Game::Stat MoveSpeed = {
					.Type = Enum::StatAttributeBasic::MoveSpeed
				};
				bool IsDead = false;
				std::vector<Effect> AdditionalEffects;
				Enum::ItemInstanceId PetItemInstanceId;
				unsigned short Level = 0;
				std::wstring SpawnEffect;
				std::vector<Skill> Skills;
				long long HiddenHpAdd = 0;
			};
		}
	}
}
