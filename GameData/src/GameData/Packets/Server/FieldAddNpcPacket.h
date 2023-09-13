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
					Enum::SkillId SkillId = (Enum::SkillId)0;
					Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				};
				
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::NpcId NpcId = (Enum::NpcId)0;
				Vector3S Position;
				Vector3S Rotation;
				std::string KfmName;
				Maple::Game::ActorBasicStat Hp = {
					.Type = Enum::StatAttributeBasic::Hp
				};
				Maple::Game::ActorBasicStat AttackSpeed = {
					.Type = Enum::StatAttributeBasic::AttackSpeed
				};
				bool IsDead = false;
				std::vector<Maple::Game::AdditionalEffect> Effects;
				Enum::ItemInstanceId PetItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short Level = 0;
				std::wstring SpawnEffect;
				std::vector<Skill> Skills;
				long long HiddenHpAdd = 0;
			};
		}
	}
}
