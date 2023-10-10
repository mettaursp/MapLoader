#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>
#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncTickPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				int ServerTick = 0;
			};
			
			struct SkillCancelPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
			};
			
			struct SkillDamagePacket
			{
				struct HitEntity
				{
					Enum::ActorId EntityId = (Enum::ActorId)0;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
				Vector3S Position;
				Vector3S HitPoint;
				Vector3S Rotation;
				unsigned char AttackPoint = 0;
				std::vector<HitEntity> Hits;
			};
			
			struct SkillRegionSkillPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				unsigned char AttackPoint = 0;
				int AttackCounter = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
			
			struct SkillSyncDamagePacket
			{
				struct Projectile
				{
					struct ChainTarget
					{
						Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
						Enum::ActorId TargetId = (Enum::ActorId)0;
						unsigned char Index = 0;
					};
					
					Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
					Enum::ActorId TargetId = (Enum::ActorId)0;
					unsigned char Index = 0;
					std::vector<ChainTarget> ChainTargets;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
				std::vector<Projectile> Projectiles;
			};
			
			struct SkillCastPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				int ServerTick = 0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				Vector3S Rotation;
				int ClientTick = 0;
				bool Flag = false;
			};
			
			struct SkillSyncPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char MotionPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
