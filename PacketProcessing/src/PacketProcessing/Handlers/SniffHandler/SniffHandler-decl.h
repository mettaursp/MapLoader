#pragma once

#include <unordered_map>
#include <unordered_set>
#include <ostream>

#include <ParserUtils/DataStream.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MaplePlayer.h>
#include <GameData/Data/PacketCommon.h>
#include <GameData/Enums/MapleItem.h>

namespace Maple
{
	namespace Game
	{
		struct ItemData;
	}
}

namespace Networking
{
	namespace Packets
	{
		extern const std::string JobSuffixes[3];
		extern const std::unordered_map<unsigned short, std::string> JobNames;
		extern const std::unordered_map<Enum::StatAttributeBasic, std::string> StatBasicNames;
		extern const std::unordered_map<Enum::StatAttributeSpecial, std::string> StatSpecialNames;

		const std::string& GetStatName(Enum::StatAttributeBasic stat);
		const std::string& GetStatName(Enum::StatAttributeSpecial stat);
		std::string GetJobName(Enum::JobCode jobCode, Enum::JobId job);
		std::string GetJobName(Enum::JobCode jobCode, unsigned int rank);

		struct NpcData
		{
			std::string Name;
			bool HasHiddenHp = false;
			int Class = 0;
			int NpcType = 0;
		};

		struct MapData
		{
			std::string Name;
		};

		struct SkillData
		{
			std::string Name;
		};

		struct EffectData
		{
			std::string Name;
			std::unordered_map<Enum::EffectLevel, std::string> Names;
		};

		struct ItemData
		{
			std::string Name;
			std::string Class;
			bool HasTemplate = false;
			bool HasBlueprint = false;
			unsigned int PetId = 0;
			bool IsMusicScore = false;
			bool IsCustomNote = false;
			unsigned char BadgeType = 0;
			unsigned int BadgeId = 0;
			bool IsBadge = false;
			unsigned short Level = 0;
		};

		struct Metadata
		{
			std::unordered_map<Enum::NpcId, NpcData> Npcs;
			std::unordered_map<Enum::MapId, MapData> Maps;
			std::unordered_map<Enum::ItemId, ItemData> Items;
			std::unordered_map<Enum::EffectId, EffectData> Effects;
			std::unordered_map<Enum::SkillId, SkillData> Skills;
		};

		struct ActorStats
		{
			std::unordered_map<Enum::StatAttributeBasic, Maple::Game::ActorBasicStat> Basic;
			std::unordered_map<Enum::StatAttributeSpecial, Maple::Game::ActorSpecialStat> Special;
		};

		enum class ActorType
		{
			Actor,
			Player,
			Pet,
			Npc
		};

		class SniffHandler;

		struct Actor
		{
			struct FieldState* Field = nullptr;
			Enum::ActorId ActorId = Enum::ActorId::Null;
			unsigned short Level = 0;
			ActorStats Stats;
			std::vector<Maple::Game::AdditionalEffect> Effects;
			std::unordered_map<Enum::EffectInstanceId, size_t> EffectIndices;
			ActorType Type = ActorType::Actor;

			void AddEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect);
			void AddEffects(SniffHandler& handler, const std::vector<Maple::Game::AdditionalEffect>& effects);
			void RemoveEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect);
			void UpdateEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect);
			void UpdateEffect(SniffHandler& handler, Enum::EffectInstanceId effectHandle, const Maple::Game::EffectStats& stats, bool enabled);
			void UpdateEffect(SniffHandler& handler, Enum::EffectInstanceId effectHandle, long long shieldHealth);
		};

		struct Npc
		{
			std::string Name;
			Enum::NpcId NpcId = Enum::NpcId::Null;
			const NpcData* Data = nullptr;
			Actor* Actor = nullptr;
		};

		struct Pet;

		struct SkillTreePage
		{
			std::unordered_map<Enum::SkillId, Enum::SkillLevel> Skills;
		};

		struct SkillTree
		{
			SkillTreePage Active;
			SkillTreePage Passive;
			SkillTreePage Special;
			SkillTreePage Consumable;
		};

		struct Player
		{
			std::wstring Name;
			Enum::JobId Job = Enum::JobId(0);
			Enum::JobCode JobCode = Enum::JobCode(0);
			Pet* Pet = nullptr;
			Actor* Actor = nullptr;
			bool IsCurrentPlayer = false;
			SkillTree Skills;

			void AddSkills(SniffHandler& handler, const Maple::Game::SkillTreeData& skillTree);
			void AddSkills(SniffHandler& handler, SkillTreePage& tree, const Maple::Game::SkillTreePageData& skillTree);
		};

		struct Pet
		{
			std::wstring Name;
			std::string NpcName;
			Enum::ActorId OwnerId = Enum::ActorId::Null;
			Enum::NpcId NpcId = Enum::NpcId::Null;
			Enum::NpcId SkinNpcId = Enum::NpcId::Null;
			Actor* Actor = nullptr;
			Player* Owner = nullptr;
			Npc* Npc = nullptr;
			Enum::ItemInstanceId ItemId = Enum::ItemInstanceId::Null;
		};

		struct ItemStats
		{

		};

		struct Item
		{
			Enum::ItemId ItemId = Enum::ItemId::Null;
			Enum::ItemInstanceId InstanceId = Enum::ItemInstanceId::Null;
			Enum::Rarity Rarity = Enum::Rarity::None;
			Enum::BadgeType BadgeType = Enum::BadgeType::None;
			unsigned int Amount = 0;
			const ItemData* Meta = nullptr;
			Maple::Game::ItemData* Data = nullptr;
		};

		struct FieldItem
		{
			Enum::ItemId ItemId = Enum::ItemId::Null;
			Enum::ItemInstanceId InstanceId = Enum::ItemInstanceId::Null;
		};

		struct FieldState
		{
			const Metadata* GameData = nullptr;
			bool PrintedMap = false;
			Enum::MapId MapId = Enum::MapId::Null;
			const MapData* CurrentMap = nullptr;
			std::unordered_map<Enum::ActorId, Npc> Npcs;
			std::unordered_map<Enum::ActorId, Actor> Actors;
			std::unordered_map<Enum::ActorId, Player> Players;
			std::unordered_map<Enum::ActorId, Pet> Pets;
			std::unordered_map<Enum::ItemInstanceId, Item> Items;
			std::unordered_map<Enum::ItemInstanceId, Maple::Game::ItemData> ItemStats;
			std::unordered_map<Enum::ItemEntityId, FieldItem> FieldItems;

			Actor* GetActor(Enum::ActorId actor);
			const Actor* GetActor(Enum::ActorId actor) const;
			Pet* GetPet(Enum::ActorId actor);
			const Pet* GetPet(Enum::ActorId actor) const;
			Npc* GetNpc(Enum::ActorId actor);
			const Npc* GetNpc(Enum::ActorId actor) const;
			Player* GetPlayer(Enum::ActorId actor);
			const Player* GetPlayer(Enum::ActorId actor) const;
		};

		struct PrintActor
		{
			const FieldState& Field;
			Enum::ActorId Actor;
			ActorType Type = ActorType::Actor;
		};

		struct PrintEffect
		{
			const FieldState& Field;
			const Maple::Game::AdditionalEffect& Effect;
			Enum::ActorId OwnerId = Enum::ActorId::Null;
		};

		struct PrintSkill
		{
			const FieldState& Field;
			Enum::SkillId SkillId = Enum::SkillId::Null;
			Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
		};

		struct PrintItem
		{
			const FieldState& Field;
			Enum::ItemInstanceId ItemInstanceId = Enum::ItemInstanceId::Null;
		};

		struct PrintItemStats
		{
			const FieldState& Field;
			Enum::ItemInstanceId ItemInstanceId = Enum::ItemInstanceId::Null;
			size_t Tabs = 1;
		};

		struct PrintItemDataStats
		{
			const FieldState& Field;
			const Maple::Game::ItemData* Data = nullptr;
			size_t Tabs = 1;
		};

		extern std::unordered_map<Enum::JobCode, std::unordered_map<unsigned short, ActorStats>> Gms2JobBaseStats;
		extern std::unordered_map<Enum::JobCode, std::unordered_map<unsigned short, ActorStats>> Kms2JobBaseStats;

		void AddStats(ActorStats& stats, const Maple::Game::ActorStats& packetStats);
		void AddStat(ActorStats& stats, const Maple::Game::ActorBasicStat& packetStat);
		void AddStat(ActorStats& stats, const Maple::Game::ActorSpecialStat& packetStat);
		void CheckBaseStats(Enum::JobCode jobCode, unsigned short level, const Maple::Game::ActorStats& stats, bool isKms2);

		class SniffHandler
		{
		public:
			struct StackEntry
			{
				ParserUtils::DataStream PacketStream;
				std::string DeflatedData;
			};

			struct FindValueEntry
			{
				size_t BufferStart = (size_t)-1;
				size_t BufferLength = 0;
				size_t PacketIndex = 0;
			};

			unsigned short Version = 0;
			unsigned short Feature = 0;
			std::string Locale;
			std::string LastPacketName;
			size_t StackDepth = 0;
			size_t DiscardedItemPackets = 0;
			size_t PacketIndex = 0;
			std::vector<char> FindValuesBuffer;
			std::vector<FindValueEntry> FindValues;

			const char* Tabs() const;

			Enum::ActorId PlayerId = Enum::ActorId::Null;
			Enum::AccountId AccountId = Enum::AccountId::Null;
			Enum::CharacterId CharacterId = Enum::CharacterId::Null;

			std::string TimeStamp;
			std::vector<StackEntry> StreamStack;
			std::stringstream FoundValues;
			Metadata* Data = nullptr;
			bool HasReconnected = false;
			FieldState Field;
			bool ReportPackets = true;
			bool AllowValueSearch = false;
			std::string MsbPath;

			std::unordered_set<size_t> IdAmountStates;

			template <typename T>
			void PacketParsed(const T& value);

			ParserUtils::DataStream& ResetPacketStream();
			ParserUtils::DataStream& PacketStream() { return StreamStack.back().PacketStream; }
			const ParserUtils::DataStream& PacketStream() const { return StreamStack.back().PacketStream; }
			void PushStream(size_t size, bool isDeflated);
			void PopStream();
			void CheckStreamStatus();
			bool Succeeded() const;
			void DiscardPacket();
			void FoundUnknownValue();

			template <typename T>
			void FindValueReferences(const T& value);

			template <typename T, typename U>
			void FindTypeValueReferences(const U& value);

			bool IsNpcBoss(Enum::NpcId npcId) const;
			bool NpcHasHiddenHp(Enum::NpcId npcId) const;
			unsigned char GetItemExtraDataType(unsigned int itemId) const;
			unsigned short GetItemCategory(Enum::ItemId itemId) const;
			unsigned short GetItemCategory(unsigned int itemId) const;
			bool StatIntToFloat(float& rate) const;
			unsigned char GetActorType(Enum::ActorId actorId);
			int GetItemIdFromInstance(Enum::ItemInstanceId instanceId);
			unsigned int GetFieldItemType(Enum::ItemEntityId instanceId);
			unsigned int GetFieldItemType(unsigned int instanceId);
			unsigned int GetFieldItemId(Enum::ItemEntityId instanceId);
			unsigned int GetFieldItemId(unsigned int instanceId);
			unsigned int GetClassFromNpc(unsigned int actorId);
			unsigned int GetClassFromNpc(Enum::ActorId actorId);
			bool IsNpcFriendly(unsigned int actorId);
			bool IsNpcFriendly(Enum::ActorId actorId);

			Item* RegisterItem(Enum::ItemInstanceId instanceId, Enum::ItemId itemId);
			Item* GetItem(Enum::ItemInstanceId instanceId);

			template <typename T>
			const T& Copy(const T& value) { return value; }

		private:

			void FindValueReferencesInternal(size_t lastBufferEnd);
		};

		template <typename T>
		void SniffHandler::FindValueReferences(const T& value)
		{
			if (!AllowValueSearch)
			{
				return;
			}

			size_t bufferEnd = FindValuesBuffer.size();

			ParserUtils::WriteStream(FindValuesBuffer, value);

			FindValueReferencesInternal(bufferEnd);
		}

		template <typename T, typename U>
		void SniffHandler::FindTypeValueReferences(const U& value)
		{
			T castedValue = (T)value;

			FindValueReferences<T>(castedValue);
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintActor& actor);
std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintEffect& effect);
std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintSkill& effect);
std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItem& item);
std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItemStats& item);
std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItemDataStats& item);