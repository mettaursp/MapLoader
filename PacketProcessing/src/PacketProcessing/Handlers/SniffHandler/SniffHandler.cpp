#include "SniffHandler-decl.h"

#include <zlib.h>

#include <ParserUtils/PacketParsing.h>
#include <ArchiveParser/ArchiveParser.h>
#include <Engine/Assets/ParserUtils.h>

namespace Networking
{
	namespace Packets
	{
		const std::string JobSuffixes[3] = { "", " II" };
		const std::unordered_map<unsigned short, std::string> JobNames = {
			{ 1, "Beginner" },
			{ 10, "Knight" },
			{ 20, "Berserker" },
			{ 30, "Wizard" },
			{ 40, "Priest" },
			{ 50, "Archer" },
			{ 60, "HeavyGunner" },
			{ 70, "Thief" },
			{ 80, "Assassin" },
			{ 90, "Runeblade" },
			{ 100, "Striker" },
			{ 110, "Soulbinder" },
			{ 999, "GameMaster" },
		};

		const std::unordered_map<Enum::StatAttributeBasic, std::string> StatNames = {
			{ Enum::StatAttributeBasic::Hp, "Hp" },
			{ Enum::StatAttributeBasic::Str, "Str" },
			{ Enum::StatAttributeBasic::Dex, "Dex" },
			{ Enum::StatAttributeBasic::Int, "Int" },
			{ Enum::StatAttributeBasic::Luk, "Luk" },
			{ Enum::StatAttributeBasic::PhysicalAtk, "PhysicalAtk" },
			{ Enum::StatAttributeBasic::PhysicalRes, "PhysicalRes" },
			{ Enum::StatAttributeBasic::MagicAtk, "MagicAtk" },
			{ Enum::StatAttributeBasic::MagicRes, "MagicRes" },
			{ Enum::StatAttributeBasic::Defense, "Defense" },
			{ Enum::StatAttributeBasic::SpRegen, "SpRegen" },
			{ Enum::StatAttributeBasic::SpRegenInterval, "SpRegenInterval" }
		};

		void AddStats(ActorStats& stats, const Maple::Game::ActorStats& packetStats)
		{
			for (const auto& packetStat : packetStats.Basic)
			{
				AddStat(stats, packetStat);
			}

			for (const auto& packetStat : packetStats.Special)
			{
				AddStat(stats, packetStat);
			}
		}

		void AddStat(ActorStats& stats, const Maple::Game::ActorBasicStat& packetStat)
		{
			if (packetStat.Base || packetStat.Current || packetStat.Max)
			{
				stats.Basic[packetStat.Type] = packetStat;
			}
		}

		void AddStat(ActorStats& stats, const Maple::Game::ActorSpecialStat& packetStat)
		{
			if (packetStat.Value || packetStat.Rate)
			{
				stats.Special[packetStat.Type] = packetStat;
			}
		}

		std::unordered_map<Enum::JobCode, std::unordered_map<unsigned short, ActorStats>> Gms2JobBaseStats;
		std::unordered_map<Enum::JobCode, std::unordered_map<unsigned short, ActorStats>> Kms2JobBaseStats;

		void CheckBaseStats(Enum::JobCode jobCode, unsigned short level, const Maple::Game::ActorBasicStat& stat, bool isKms2)
		{
			auto& entry = (isKms2 ? Kms2JobBaseStats : Gms2JobBaseStats)[jobCode][level].Basic[stat.Type];

			if (entry.Base && entry.Base != stat.Base)
			{
				//std::cout << "mismatching base for stat " << (int)stat.Type << std::endl;
			}

			entry = stat;
		}

		void CheckBaseStats(Enum::JobCode jobCode, unsigned short level, const Maple::Game::ActorStats& stats, Enum::StatAttributeBasic attribute, bool isKms2)
		{
			for (const auto& stat : stats.Basic)
			{
				if (stat.Type == attribute && stat.Base)
				{
					CheckBaseStats(jobCode, level, stat, true);

					return;
				}
			}
		}

		void CheckBaseStats(Enum::JobCode jobCode, unsigned short level, const Maple::Game::ActorStats& stats, bool isKms2)
		{
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Hp, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Str, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Dex, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Int, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Luk, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::PhysicalAtk, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::PhysicalRes, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::MagicAtk, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::MagicRes, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::Defense, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::SpRegenInterval, isKms2);
			CheckBaseStats(jobCode, level, stats, Enum::StatAttributeBasic::SpRegen, isKms2);
		}

		ParserUtils::DataStream& SniffHandler::ResetPacketStream()
		{
			StreamStack.clear();
			StreamStack.push_back({});

			return PacketStream();
		}

		bool handleZlibResult(int result)
		{
			switch (result)
			{
			case Z_OK:
				return true;
			case Z_STREAM_ERROR:
				std::cout << "unhandled zlib stream error" << std::endl;

				break;
			case Z_DATA_ERROR:
				std::cout << "unhandled zlib data error" << std::endl;

				break;
			case Z_MEM_ERROR:
				std::cout << "unhandled zlib memory error" << std::endl;

				break;
			case Z_BUF_ERROR:
				std::cout << "unhandled zlib buffer error" << std::endl;

				break;
			default:
				std::cout << "unhandled zlib error" << std::endl;
			}

			return false;
		}

		void SniffHandler::PushStream(size_t size, bool isDeflated)
		{
			{
				ParserUtils::DataStream& oldTop = PacketStream();

				if (oldTop.HasRecentlyFailed)
				{
					return;
				}

				if (oldTop.Index + size > oldTop.Data.size())
				{
					oldTop.Failed();

					std::cout << "attempt to read buffer of size " << size << " when only " << (oldTop.Data.size() - oldTop.Index) << " bytes are left" << std::endl;

					return;
				}
			}

			StreamStack.push_back({});

			StackEntry& entry = StreamStack.back();

			ParserUtils::DataStream& oldTop = StreamStack[StreamStack.size() - 2].PacketStream;

			std::string_view bufferData = { oldTop.Data.data() + oldTop.Index, size };

			if (!isDeflated)
			{
				entry.PacketStream = ParserUtils::DataStream{ bufferData };
			}
			else
			{
				if (size < sizeof(unsigned int))
				{
					entry.PacketStream.Failed();

					std::cout << "buffer too small to contain decompressed size" << std::endl;

					return;
				}

				auto& deflated = entry.DeflatedData;

				Endian endian(std::endian::big);

				unsigned int length = endian.read<unsigned int>(bufferData.data());

				bufferData = { bufferData.data() + sizeof(unsigned int), size - sizeof(unsigned int)};

				uLongf sizeUncompressed = (uLongf)decompressionBufferSize((size_t)length);
				int written = (int)size;
				
				deflated.resize(sizeUncompressed);
				
				int result = uncompress(reinterpret_cast<Bytef*>(deflated.data()), &sizeUncompressed, reinterpret_cast<const Bytef*>(bufferData.data()), written);

				entry.PacketStream = ParserUtils::DataStream{ { deflated.data(), sizeUncompressed }};

				if (!handleZlibResult(result))
				{
					entry.PacketStream.Failed();
				
					return;
				}
			}

			ParserUtils::DataStream& newTop = PacketStream();

			newTop.IgnoreUnknownValues = oldTop.IgnoreUnknownValues;
			newTop.SuppressErrors = oldTop.SuppressErrors;
			newTop.DiscardErrors = oldTop.DiscardErrors;
			newTop.PrintOutput = oldTop.PrintOutput;

			oldTop.Index += size;
		}

		void SniffHandler::PopStream()
		{
			if (StreamStack.size() == 1)
			{
				PacketStream().Failed();

				std::cout << "attempt to pop packet stream buffer when no buffers are left to pop" << std::endl;

				return;
			}

			ParserUtils::DataStream& oldTop = PacketStream();
			ParserUtils::DataStream& newTop = StreamStack[StreamStack.size() - 2].PacketStream;

			if (!newTop.HasRecentlyFailed && oldTop.Index < oldTop.Data.size())
			{
				std::cout << "popping buffer when not all bytes have been read from it. bytes remaining: " << (oldTop.Data.size() - oldTop.Index) << std::endl;

				if constexpr (ParserUtils::Packets::PrintOutput || ParserUtils::Packets::PrintErrors)
				{
					if (!(!ParserUtils::Packets::PrintOutput && !PacketStream().DiscardErrors && (PacketStream().SuppressErrors || !PacketStream().PrintOutput)))
					{
						std::ostream& out = ParserUtils::Packets::PrintOutput ? std::cout : FoundValues;
						const ParserUtils::DataStream& stream = PacketStream();

						size_t size = stream.Data.size();
						size_t printAmount = size - stream.Index;
						size_t printCount = 16 * ((printAmount / 16) + (printAmount % 16 ? 1 : 0));

						out << "remaining stream data [" << (printAmount) << "]\n" << std::hex;

						for (size_t i = 0; i <= printCount; ++i)
						{
							size_t index = stream.Index + i;

							if (i && (i % 16) == 0)
							{
								out << " |  " << std::dec;

								for (size_t j = 0; j < 16 && index - 16 + j < size; ++j)
									out << (stream.Data[index - 16 + j] >= 32 && stream.Data[index - 16 + j] <= 126 ? stream.Data[index - 16 + j] : '.');

								out << "\n" << std::hex;
							}

							if (index < size)
							{
								out << std::setw(2) << std::setfill('0') << (int)(unsigned char)stream.Data[index] << " ";
							}
							else if (i < printCount)
							{
								out << "   ";
							}
						}

						out << std::endl;
					}
				}

				newTop.Index -= oldTop.Data.size() - oldTop.Index;
			}

			newTop.HasRecentlyFailed = oldTop.HasRecentlyFailed || oldTop.Index < oldTop.Data.size();
			newTop.FoundUnknownValue = oldTop.FoundUnknownValue;

			StreamStack.pop_back();
		}

		void SniffHandler::CheckStreamStatus()
		{
			if (!StreamStack.size())
			{
				ResetPacketStream();
			}

			if (StreamStack.size() == 1)
			{
				return;
			}

			PacketStream().HasRecentlyFailed = true;

			while (StreamStack.size() > 1)
			{
				PopStream();
			}
		}

		bool SniffHandler::Succeeded() const
		{
			return ReportPackets && PacketStream().Succeeded();
		}

		bool SniffHandler::IsNpcBoss(Enum::NpcId npcId) const
		{
			if (Data == nullptr)
			{
				return false;
			}

			const auto npcHandle = Data->Npcs.find(npcId);

			if (npcHandle == Data->Npcs.end())
			{
				return false;
			}

			return npcHandle->second.Class >= 3 && npcHandle->second.NpcType == 0;
		}

		bool SniffHandler::NpcHasHiddenHp(Enum::NpcId npcId) const
		{
			return false;

			if (Data == nullptr)
			{
				return false;
			}

			const auto npcHandle = Data->Npcs.find(npcId);

			if (npcHandle == Data->Npcs.end())
			{
				return false;
			}

			return npcHandle->second.HasHiddenHp;
		}

		unsigned char SniffHandler::GetItemExtraDataType(unsigned int itemId) const
		{
			if (Data == nullptr)
			{
				return 0;
			}

			const auto itemHandle = Data->Items.find((Enum::ItemId)itemId);

			if (itemHandle == Data->Items.end())
			{
				return 0;
			}

			if (itemHandle->second.HasBlueprint || itemHandle->second.HasTemplate)
			{
				return 1;
			}

			if (itemHandle->second.PetId != 0)
			{
				return 2;
			}

			if (itemHandle->second.IsCustomNote)
			{
				return 3;
			}

			if (itemHandle->second.IsBadge)
			{
				return 4;
			}

			return 0;
		}

		unsigned short SniffHandler::GetItemCategory(Enum::ItemId itemId) const
		{
			return (unsigned short)((unsigned int)itemId / 100000);
		}

		unsigned short SniffHandler::GetItemCategory(unsigned int itemId) const
		{
			return (unsigned short)(itemId / 100000);
		}

		bool SniffHandler::StatIntToFloat(float& rate) const
		{
			rate /= 100;

			return true;
		}

		unsigned char SniffHandler::GetActorType(Enum::ActorId actorId)
		{
			const unsigned char Unknown = 0xFF;
			const unsigned char Unidentified = 0;
			const unsigned char Player = 1;
			const unsigned char OtherPlayer = 2;
			const unsigned char Pet = 3;
			const unsigned char Npc = 4;

			if (actorId == Enum::ActorId::Null)
			{
				return Unknown;
			}

			if (actorId == PlayerId)
			{
				return Player;
			}

			if (Field.Players.contains(actorId))
			{
				if (CharacterId == Enum::ActorId::Null)
				{
					// Bad sniff, character was never sent so player type is ambiguous

					DiscardPacket();
				}

				return OtherPlayer;
			}

			if (Field.Pets.contains(actorId))
			{
				return Pet;
			}

			if (Field.Npcs.contains(actorId))
			{
				return Npc;
			}

			if (Field.Actors.contains(actorId))
			{
				return Unidentified;
			}

			if (Field.MapId == Enum::MapId::Null)
			{
				// Read in from reconnect based sniff where uninitialized actors are found before the next map load
				DiscardPacket();
			}

			return Unknown;
		}

		void SniffHandler::DiscardPacket()
		{
			PacketStream().SuppressErrors = true;
			PacketStream().DiscardErrors = true;
			PacketStream().HasRecentlyFailed = true;
		}
	}
}