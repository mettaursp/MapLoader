#pragma once

#include <Engine/Math/Vector3S.h>
#include <string>
#include <vector>
#include <GameData/Data/DyeColor.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldAddPlayerPacket
			{
				struct UnknownEntry
				{
				};
				
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Maple::Game::CharacterData Character;
				Maple::Game::SkillTreeData SkillTree;
				Vector3S Position;
				Vector3S Rotation;
				Maple::Game::ActorStats Stats;
				bool InBattle = false;
				Maple::Game::CubeItemData HeldCube;
				Maple::Game::DyeColor SkinColor;
				std::wstring ProfileUrl;
				bool OnMount = false;
				Maple::Game::MountData Mount;
				unsigned long long Timestamp = 0;
				unsigned int WeeklyArchitectScore = 0;
				unsigned int ArchitectScore = 0;
				Maple::Game::CharacterEquipment Equipment;
				std::vector<Maple::Game::AdditionalEffect> Effects;
				Enum::TitleId TitleId = (Enum::TitleId)0;
				Enum::InsigniaId InsigniaId = (Enum::InsigniaId)0;
				unsigned short InsigniaValue = 0;
				bool HasPet = false;
				Maple::Game::Pet Pet;
				unsigned long long PremiumExpirationTime = 0;
				std::vector<UnknownEntry> UnknownData;
			};
		}
	}
}
