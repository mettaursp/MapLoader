#pragma once

#include <unordered_map>

#include <ParserUtils/DataStream.h>

namespace Networking
{
	namespace Packets
	{
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
		};

		struct Metadata
		{
			std::unordered_map<unsigned int, NpcData> Npcs;
			std::unordered_map<unsigned int, MapData> Maps;
			std::unordered_map<unsigned int, ItemData> Items;
		};

		struct Actor
		{
			unsigned int ActorId = 0;
		};

		struct Npc
		{
			unsigned int NpcId = 0;
			const NpcData* Data = nullptr;
			Actor* Actor = nullptr;
		};

		struct Player
		{
			unsigned int NpcId = 0;
			const NpcData* Data = nullptr;
			Actor* Actor = nullptr;
		};

		struct Pet
		{
			unsigned int OwnerId = 0;
			Actor* Actor = nullptr;
			Player* Owner = nullptr;
			Npc* Npc = nullptr;
			unsigned long long ItemId = 0;
		};


		struct FieldState
		{
			bool PrintedMap = false;
			unsigned int MapId = 0;
			const MapData* CurrentMap = nullptr;
			std::unordered_map<unsigned int, Npc> Npcs;
			std::unordered_map<unsigned int, Actor> Actors;
			std::unordered_map<unsigned int, Player> Players;
			std::unordered_map<unsigned int, Pet> Pets;
		};

		class SniffHandler
		{
		public:
			ParserUtils::DataStream PacketStream;
			std::stringstream FoundValues;
			Metadata* Data = nullptr;
			bool HasReconnected = false;
			FieldState Field;

			template <typename T>
			void PacketParsed(const T& packet);

			bool IsNpcBoss(unsigned int npcId) const;
			bool NpcHasHiddenHp(unsigned int npcId) const;
			unsigned char GetItemExtraDataType(unsigned int itemId) const;
			unsigned short GetItemCategory(unsigned int itemId) const;

		private:

		};
	}
}