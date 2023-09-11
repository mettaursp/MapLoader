#pragma once

#include <unordered_map>

#include <ParserUtils/DataStream.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Player.h>
#include <GameData/Data/ActorStats.h>

namespace Networking
{
	namespace Packets
	{
		extern const std::string JobSuffixes[3];
		extern const std::unordered_map<unsigned short, std::string> JobNames;
		extern const std::unordered_map<Enum::StatAttributeBasic, std::string> StatNames;

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
		};

		struct Metadata
		{
			std::unordered_map<Enum::NpcId, NpcData> Npcs;
			std::unordered_map<Enum::MapId, MapData> Maps;
			std::unordered_map<Enum::ItemId, ItemData> Items;
		};

		struct ActorStats
		{
			std::unordered_map<Enum::StatAttributeBasic, Maple::Game::ActorBasicStat> Basic;
			std::unordered_map<Enum::StatAttributeSpecial, Maple::Game::ActorSpecialStat> Special;
		};

		struct Actor
		{
			Enum::ActorId ActorId = Enum::ActorId::Null;
			unsigned short Level = 0;
			ActorStats Stats;
		};

		struct Npc
		{
			std::string Name;
			Enum::NpcId NpcId = Enum::NpcId::Null;
			const NpcData* Data = nullptr;
			Actor* Actor = nullptr;
		};

		struct Pet;

		struct Player
		{
			std::wstring Name;
			Enum::JobId Job = Enum::JobId(0);
			Enum::JobCode JobCode = Enum::JobCode(0);
			Pet* Pet = nullptr;
			Actor* Actor = nullptr;
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


		struct FieldState
		{
			bool PrintedMap = false;
			Enum::MapId MapId = Enum::MapId::Null;
			const MapData* CurrentMap = nullptr;
			std::unordered_map<Enum::ActorId, Npc> Npcs;
			std::unordered_map<Enum::ActorId, Actor> Actors;
			std::unordered_map<Enum::ActorId, Player> Players;
			std::unordered_map<Enum::ActorId, Pet> Pets;
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

			unsigned short Version = 0;
			unsigned short Feature = 0;
			std::string Locale;

			Enum::ActorId PlayerId = Enum::ActorId::Null;
			Enum::AccountId AccountId = Enum::AccountId::Null;
			Enum::CharacterId CharacterId = Enum::CharacterId::Null;

			std::vector<StackEntry> StreamStack;
			std::stringstream FoundValues;
			Metadata* Data = nullptr;
			bool HasReconnected = false;
			FieldState Field;
			bool ReportPackets = true;
			std::string MsbPath;

			template <typename T>
			void PacketParsed(const T& packet);

			ParserUtils::DataStream& ResetPacketStream();
			ParserUtils::DataStream& PacketStream() { return StreamStack.back().PacketStream; }
			const ParserUtils::DataStream& PacketStream() const { return StreamStack.back().PacketStream; }
			void PushStream(size_t size, bool isDeflated);
			void PopStream();
			void CheckStreamStatus();
			bool Succeeded() const;
			void DiscardPacket();

			bool IsNpcBoss(Enum::NpcId npcId) const;
			bool NpcHasHiddenHp(Enum::NpcId npcId) const;
			unsigned char GetItemExtraDataType(unsigned int itemId) const;
			unsigned short GetItemCategory(Enum::ItemId itemId) const;
			unsigned short GetItemCategory(unsigned int itemId) const;
			bool StatIntToFloat(float& rate) const;
			unsigned char GetActorType(Enum::ActorId actorId);

		private:

		};
	}
}