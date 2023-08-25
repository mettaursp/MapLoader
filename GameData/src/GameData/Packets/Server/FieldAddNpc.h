#pragma once

#include <Engine/Math/Vector3S.h>
#include <string>
#include <vector>
#include <GameData/Packets\Server/FieldAddNpc.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Data/Stat.h>
#include <GameData/Enums/NpcId.h>
#include <GameData/Data/StatLong.h>
#include <GameData/Enums/ItemInstanceId.h>
#include <GameData/Enums/EffectInstanceId.h>
#include <GameData/Enums/EffectId.h>
#include <GameData/Enums/EffectLevel.h>
#include <GameData/Enums/SkillId.h>
#include <GameData/Enums/SkillLevel.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddNpc
			{
				struct Effect
				{
					Enum::ActorId OwnerId;
					Enum::EffectInstanceId InstanceId;
					Enum::ActorId CasterId;
					int StartTick = 0;
					int EndTick = 0;
					Enum::EffectId EffectId;
					Enum::EffectLevel EffectLevel;
					int Stacks = 0;
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
				Enum::ItemInstanceId PetItemIstanceId;
				unsigned short Level = 0;
				std::wstring SpawnEffect;
				std::vector<Skill> Skills;
				long long HiddenHpAdd = 0;
			};
		}
	}
}
