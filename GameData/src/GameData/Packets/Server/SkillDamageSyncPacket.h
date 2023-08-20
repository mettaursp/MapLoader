#pragma once

#include <GameData/Enums/SkillLevel.h>
#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/SkillId.h>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Enums/SkillAttackId.h>
#include <GameData/Enums/ActorId.h>
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
					Enum::SkillAttackId SkillAttack;
					Enum::ActorId TargetId;
					short Animation = 0;
				};
				
				Enum::SkillSn SkillSn;
				Enum::ActorId CasterId;
				Enum::SkillId SkillId;
				Enum::SkillLevel SkillLevel;
				unsigned char MotionPoint = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				bool IsChaining = false;
				std::vector<HitEntity> Hits;
			};
		}
	}
}
