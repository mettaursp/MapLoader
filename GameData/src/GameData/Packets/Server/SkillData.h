#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleCombat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageTilePacket
			{
				struct DamagedTarget
				{
					struct DamageInstance
					{
						Enum::HitType HitType = Enum::HitType::Normal;
						long long Damage = 0;
					};
					
					Enum::ActorId TargetId = (Enum::ActorId)0;
					Vector3S Position;
					Vector3S Direction;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				std::vector<DamagedTarget> DamagedTargets;
			};
			
			struct SkillDamageHealPacket
			{
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::ActorId TargetId = (Enum::ActorId)0;
				int ServerTick = 0;
				int HpAmount = 0;
				int SpAmount = 0;
				int EpAmount = 0;
				bool IsVisible = false;
			};
			
			struct SkillDamageDotPacket
			{
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::ActorId TargetId = (Enum::ActorId)0;
				int ServerTick = 0;
				Enum::HitType HitType = Enum::HitType::Normal;
				long long Damage = 0;
			};
			
			struct SkillDamagePacket
			{
				struct DamagedTarget
				{
					struct DamageInstance
					{
						Enum::HitType HitType = Enum::HitType::Normal;
						long long Damage = 0;
					};
					
					Enum::ActorId TargetId = (Enum::ActorId)0;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char MotionPoint = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				int ServerTick = 0;
				std::vector<DamagedTarget> DamagedTargets;
			};
			
			struct SkillDamageRegionPacket
			{
				struct DamagedTarget
				{
					struct DamageInstance
					{
						Enum::HitType HitType = Enum::HitType::Normal;
						long long Damage = 0;
					};
					
					Enum::ActorId TargetId = (Enum::ActorId)0;
					Vector3S Position;
					Vector3S Direction;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::ActorId RegionSkillObjectId = (Enum::ActorId)0;
				unsigned char AttackPoint = 0;
				std::vector<DamagedTarget> DamagedTargets;
			};
			
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
