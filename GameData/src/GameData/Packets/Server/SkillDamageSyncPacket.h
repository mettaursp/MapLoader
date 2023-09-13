#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/Handles.h>
#include <GameData/Packets\Server/SkillDamageSyncPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageSyncPacket
			{
				struct HitEntity
				{
					Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
					Enum::ActorId TargetId = (Enum::ActorId)0;
					short Animation = 0;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char MotionPoint = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				bool IsChaining = false;
				unsigned int ServerTick = 0;
				std::vector<HitEntity> Hits;
			};
		}
	}
}
