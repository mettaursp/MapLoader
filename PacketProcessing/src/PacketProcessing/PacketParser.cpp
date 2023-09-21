#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void ParseBasicStat_v12(PacketHandler& handler, Maple::Game::BasicStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");
			Read<float>("rate", handler, blockOutput.Rate, "\t\t");
		}

		void ParseSpecialStat_v12(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");
			Read<float>("rate", handler, blockOutput.Rate, "\t\t");
		}

		void ParseBasicAndSpecialStats_v12(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseBasicStat_v12(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseSpecialStat_v12(handler, blockOutput.Special[i]);
			}

			Read<int>("empowermentItemId", handler, blockOutput.EmpowermentItemId, "\t\t");
		}

		void ParseAllStatsMyPlayer_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char statCount_i = 0; statCount_i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++statCount_i)
			{
				auto& statCount_array0 = blockOutput.Basic[statCount_i];

				unsigned char statType_var1 = statCount_i;

				statCount_array0.Type = (Enum::StatAttributeBasic)statType_var1;

				if (statType_var1 == 4)
				{
					Read<unsigned long long>("max", handler, statCount_array0.Max, "\t\t\t\t");
					Read<unsigned long long>("base", handler, statCount_array0.Base, "\t\t\t\t");
					Read<unsigned long long>("current", handler, statCount_array0.Current, "\t\t\t\t");
				}

				else
				{
					Read<unsigned int>("max", handler, statCount_array0.Max, "\t\t\t\t");
					Read<unsigned int>("base", handler, statCount_array0.Base, "\t\t\t\t");
					Read<unsigned int>("current", handler, statCount_array0.Current, "\t\t\t\t");
				}
			}
		}

		void ParseAllStatsOtherPlayers_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char basicStatCount_var0 = 5;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			short health_var1 = 4;

			blockOutput.Basic[0].Type = (Enum::StatAttributeBasic)health_var1;

			short attackSpeed_var2 = 13;

			blockOutput.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var2;

			short moveSpeed_var3 = 14;

			blockOutput.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var3;

			short mountMoveSpeed_var4 = 22;

			blockOutput.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var4;

			short jumpHeight_var5 = 32;

			blockOutput.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var5;

			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Max, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Max, "\t\t");
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Max, "\t\t");
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Max, "\t\t");
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Max, "\t\t");
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Base, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Base, "\t\t");
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Base, "\t\t");
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Base, "\t\t");
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Base, "\t\t");
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Current, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Current, "\t\t");
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Current, "\t\t");
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Current, "\t\t");
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Current, "\t\t");
		}

		void ParseAllStatsNpc_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char basicStatCount_var0 = 2;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			short health_var1 = 4;

			blockOutput.Basic[0].Type = (Enum::StatAttributeBasic)health_var1;

			short attackSpeed_var2 = 13;

			blockOutput.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var2;

			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Max, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Max, "\t\t");
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Base, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Base, "\t\t");
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Current, "\t\t");
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Current, "\t\t");
		}

		void ParseSpecificStat_v12(PacketHandler& handler, Maple::Game::ActorBasicStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("statType", handler, blockOutput.Type, "\t\t");

			if (blockOutput.Type == (Enum::StatAttributeBasic)4)
			{
				Read<unsigned long long>("max", handler, blockOutput.Max, "\t\t\t");
				Read<unsigned long long>("base", handler, blockOutput.Base, "\t\t\t");
				Read<unsigned long long>("current", handler, blockOutput.Current, "\t\t\t");
			}

			if (blockOutput.Type != (Enum::StatAttributeBasic)4)
			{
				Read<unsigned int>("max", handler, blockOutput.Max, "\t\t\t");
				Read<unsigned int>("base", handler, blockOutput.Base, "\t\t\t");
				Read<unsigned int>("current", handler, blockOutput.Current, "\t\t\t");
			}
		}

		void ParseSpecificStats_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput, unsigned char statCount_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ResizeVector(handler, blockOutput.Basic, statCount_param0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < statCount_param0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseSpecificStat_v12(handler, blockOutput.Basic[i]);
			}
		}

		void ParseItemBinding_v12(PacketHandler& handler, Maple::Game::ItemBinding& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
		}

		void ParseItemCustomization_v12(PacketHandler& handler, Maple::Game::ItemCustomization& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();


			{
				Color4I_BGRA dyeColorPrimary_var0;
				Read<Color4I_BGRA>("dyeColorPrimary", handler, dyeColorPrimary_var0, "\t\t\t");

				blockOutput.DyeColor.Primary = (Color4I)dyeColorPrimary_var0;

				Color4I_BGRA dyeColorSecondary_var1;
				Read<Color4I_BGRA>("dyeColorSecondary", handler, dyeColorSecondary_var1, "\t\t\t");

				blockOutput.DyeColor.Secondary = (Color4I)dyeColorSecondary_var1;

				Color4I_BGRA dyeColorTertiary_var2;
				Read<Color4I_BGRA>("dyeColorTertiary", handler, dyeColorTertiary_var2, "\t\t\t");

				blockOutput.DyeColor.Tertiary = (Color4I)dyeColorTertiary_var2;

				Read<int>("dyeColorIndex", handler, blockOutput.DyeColor.Index, "\t\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t\t");
			}

			short itemCategory_var5 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemCategory_var5 = handler.GetItemCategory(itemId_param0);
			}

			if (itemCategory_var5 == 113)
			{

				{
					Read<Vector3S>("position1", handler, blockOutput.Cap.Position1, "\t\t\t\t");
					Read<Vector3S>("position2", handler, blockOutput.Cap.Position2, "\t\t\t\t");
					Read<Vector3S>("position3", handler, blockOutput.Cap.Position3, "\t\t\t\t");
					Read<Vector3S>("position4", handler, blockOutput.Cap.Position4, "\t\t\t\t");

					float unknown_var10 = 0;
					Read<float>("unknown", handler, unknown_var10, "\t\t\t\t");
				}
			}

			if (itemCategory_var5 == 102)
			{

				{
					Read<float>("backLength", handler, blockOutput.Hair.BackLength, "\t\t\t\t");
					Read<Vector3S>("backPosition1", handler, blockOutput.Hair.BackPosition1, "\t\t\t\t");
					Read<Vector3S>("backPosition2", handler, blockOutput.Hair.BackPosition2, "\t\t\t\t");
					Read<float>("frontLength", handler, blockOutput.Hair.FrontLength, "\t\t\t\t");
					Read<Vector3S>("frontPosition1", handler, blockOutput.Hair.FrontPosition1, "\t\t\t\t");
					Read<Vector3S>("frontPosition2", handler, blockOutput.Hair.FrontPosition2, "\t\t\t\t");
				}
			}

			if (itemCategory_var5 == 104)
			{

				{
					float position1_var17 = 0;
					Read<float>("position1", handler, position1_var17, "\t\t\t\t");

					float position2_var18 = 0;
					Read<float>("position2", handler, position2_var18, "\t\t\t\t");

					float position3_var19 = 0;
					Read<float>("position3", handler, position3_var19, "\t\t\t\t");

					float position4_var20 = 0;
					Read<float>("position4", handler, position4_var20, "\t\t\t\t");
				}
			}
		}

		void ParseItemEnchantmentHeader_v12(PacketHandler& handler, Maple::Game::ItemEnchantment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("enchantLevel", handler, blockOutput.Level, "\t\t");
			Read<int>("enchantExp", handler, blockOutput.EnchantExp, "\t\t");
			Read<unsigned char>("enchantCharges", handler, blockOutput.EnchantCharges, "\t\t");

			long long unknown_var3 = 0;
			Read<long long>("unknown", handler, unknown_var3, "\t\t");

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");
			Read<bool>("canRepackage", handler, blockOutput.CanRepackage, "\t\t");

			ValidateValues(stream, "canRepackage", "\t\t", blockOutput.CanRepackage, (bool)0, (bool)1);

			Read<int>("charges", handler, blockOutput.Charges, "\t\t");
		}

		void ParseItemEnchantment_v12(PacketHandler& handler, Maple::Game::ItemEnchantment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ParseItemEnchantmentHeader_v12(handler, blockOutput);

			unsigned char basicStatCount_var0 = 0;
			Read<unsigned char>("basicStatCount", handler, basicStatCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("type", handler, blockOutput.Basic[i].Type, "\t\t\t");
				Read<int>("value", handler, blockOutput.Basic[i].Value, "\t\t\t");
				Read<float>("rate", handler, blockOutput.Basic[i].Rate, "\t\t\t");
			}
		}

		void ParseItemUgc_v12(PacketHandler& handler, Maple::Game::ItemUgc& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			long long unknown_var0 = 0;
			Read<long long>("unknown", handler, unknown_var0, "\t\t");
			Read<std::wstring>("fileName", handler, blockOutput.FileName, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t\t");

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4, "\t\t");
			Read<long long>("accountId", handler, blockOutput.AccountId, "\t\t");
			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("author", handler, blockOutput.Author, "\t\t");
			Read<long long>("creationTime", handler, blockOutput.CreationTime, "\t\t");
			Read<std::wstring>("url", handler, blockOutput.Url, "\t\t");

			unsigned char unknown_var10 = 0;
			Read<unsigned char>("unknown", handler, unknown_var10, "\t\t");
		}

		void ParseItemBlueprint_v12(PacketHandler& handler, Maple::Game::ItemBlueprint& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			long long unknown_var0 = 0;
			Read<long long>("unknown", handler, unknown_var0, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3, "\t\t");

			long long unknown_var4 = 0;
			Read<long long>("unknown", handler, unknown_var4, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");

			long long unknown_var6 = 0;
			Read<long long>("unknown", handler, unknown_var6, "\t\t");

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7, "\t\t");

			std::wstring unknown_var8;
			Read<std::wstring>("unknown", handler, unknown_var8, "\t\t");
		}

		void ParseItemPet_v12(PacketHandler& handler, Maple::Game::ItemPet& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
			Read<long long>("exp", handler, blockOutput.Exp, "\t\t");
			Read<int>("evolvePoints", handler, blockOutput.EvolvePoints, "\t\t");
			Read<int>("level", handler, blockOutput.Level, "\t\t");
			Read<bool>("hasItems", handler, blockOutput.HasItems, "\t\t");

			ValidateValues(stream, "hasItems", "\t\t", blockOutput.HasItems, (bool)0, (bool)1);
		}

		void ParseItemMusic_v12(PacketHandler& handler, Maple::Game::ItemMusic& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("length", handler, blockOutput.Length, "\t\t");
			Read<int>("instrument", handler, blockOutput.Instrument, "\t\t");
			Read<std::wstring>("title", handler, blockOutput.Title, "\t\t");
			Read<std::wstring>("author", handler, blockOutput.Author, "\t\t");

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var4, (int)1);

			Read<long long>("authorId", handler, blockOutput.AuthorId, "\t\t");
			Read<bool>("isLocked", handler, blockOutput.IsLocked, "\t\t");

			ValidateValues(stream, "isLocked", "\t\t", blockOutput.IsLocked, (bool)0, (bool)1);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7, "\t\t");

			long long unknown_var8 = 0;
			Read<long long>("unknown", handler, unknown_var8, "\t\t");
		}

		void ParseItemBadgeTransparency_v12(PacketHandler& handler, Maple::Game::ItemBadge& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("transparency", handler, blockOutput.Transparency[0], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[0], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[1], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[1], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[2], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[2], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[3], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[3], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[4], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[4], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[5], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[5], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[6], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[6], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[7], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[7], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[8], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[8], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[9], "\t\t");

			ValidateValues(stream, "transparency", "\t\t", blockOutput.Transparency[9], (bool)0, (bool)1);
		}

		void ParseItemBadge_v12(PacketHandler& handler, Maple::Game::ItemBadge& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var0, (unsigned char)1);

			Read<unsigned char>("type", handler, blockOutput.Type, "\t\t");

			ValidateValues(stream, "type", "\t\t", blockOutput.Type, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			Read<std::wstring>("id", handler, blockOutput.Id, "\t\t");

			if (blockOutput.Type == (Enum::BadgeType)1)
			{
				ParseItemBadgeTransparency_v12(handler, blockOutput);
			}

			if (blockOutput.Type == (Enum::BadgeType)11)
			{
				Read<int>("petSkinId", handler, blockOutput.PetSkinId, "\t\t\t");
			}
		}

		void ParseItemTransfer_v12(PacketHandler& handler, Maple::Game::ItemTransfer& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("transferFlags", handler, blockOutput.TransferFlags, "\t\t");

			bool unknown_var1 = false;
			Read<bool>("unknown", handler, unknown_var1, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var1, (bool)0, (bool)1);

			Read<int>("remainingTrades", handler, blockOutput.RemainingTrades, "\t\t");
			Read<int>("remainingPackages", handler, blockOutput.RemainingPackages, "\t\t");

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");

			bool unknown_var5 = false;
			Read<bool>("unknown", handler, unknown_var5, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var5, (bool)0, (bool)1);

			Read<bool>("isBound", handler, blockOutput.IsBound, "\t\t");

			ValidateValues(stream, "isBound", "\t\t", blockOutput.IsBound, (bool)0, (bool)1);

			if (blockOutput.IsBound)
			{
				ParseItemBinding_v12(handler, blockOutput.Binding);
			}
		}

		void ParseItemSocket_v12(PacketHandler& handler, Maple::Game::ItemSocket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("maxSlots", handler, blockOutput.MaxSlots, "\t\t");
			Read<unsigned char>("unlockedSlots", handler, blockOutput.UnlockedSlots, "\t\t");

			ResizeVector(handler, blockOutput.Sockets, blockOutput.UnlockedSlots);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < blockOutput.UnlockedSlots && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<bool>("hasGem", handler, blockOutput.Sockets[i].HasGem, "\t\t\t");

				ValidateValues(stream, "hasGem", "\t\t\t", blockOutput.Sockets[i].HasGem, (bool)0, (bool)1);

				if (blockOutput.Sockets[i].HasGem)
				{

					{
						Read<int>("itemId", handler, blockOutput.Sockets[i].Gem.ItemId, "\t\t\t\t\t");
						Read<bool>("isBound", handler, blockOutput.Sockets[i].Gem.IsBound, "\t\t\t\t\t");

						ValidateValues(stream, "isBound", "\t\t\t\t\t", blockOutput.Sockets[i].Gem.IsBound, (bool)0, (bool)1);

						if (blockOutput.Sockets[i].Gem.IsBound)
						{
							ParseItemBinding_v12(handler, blockOutput.Sockets[i].Gem.Binding);
						}

						Read<bool>("isLocked", handler, blockOutput.Sockets[i].Gem.IsLocked, "\t\t\t\t\t");

						ValidateValues(stream, "isLocked", "\t\t\t\t\t", blockOutput.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

						if (blockOutput.Sockets[i].Gem.IsLocked)
						{
							unsigned char unknown_var6 = 0;
							Read<unsigned char>("unknown", handler, unknown_var6, "\t\t\t\t\t\t");
							Read<long long>("unlockTime", handler, blockOutput.Sockets[i].Gem.UnlockTime, "\t\t\t\t\t\t");
						}
					}
				}
			}
		}

		void ParseItemCouple_v12(PacketHandler& handler, Maple::Game::ItemCouple& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");

			if (blockOutput.CharacterId != (Enum::CharacterId)0)
			{
				Read<std::wstring>("name", handler, blockOutput.Name, "\t\t\t");
				Read<bool>("isCreator", handler, blockOutput.IsCreator, "\t\t\t");

				ValidateValues(stream, "isCreator", "\t\t\t", blockOutput.IsCreator, (bool)0, (bool)1);
			}
		}

		void ParseItemHeader_v12(PacketHandler& handler, Maple::Game::ItemData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("creationTime", handler, blockOutput.CreationTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2, "\t\t");
			Read<int>("timesChanged", handler, blockOutput.TimesChanged, "\t\t");
			Read<int>("remainingUses", handler, blockOutput.RemainingUses, "\t\t");
			Read<bool>("isLocked", handler, blockOutput.IsLocked, "\t\t");

			ValidateValues(stream, "isLocked", "\t\t", blockOutput.IsLocked, (bool)0, (bool)1);

			Read<long long>("unlockTime", handler, blockOutput.UnlockTime, "\t\t");
			Read<short>("glamorForges", handler, blockOutput.GlamorForges, "\t\t");

			unsigned char unknownBool_var8 = 0;
			Read<unsigned char>("unknownBool", handler, unknownBool_var8, "\t\t");

			ValidateValues(stream, "unknownBool", "\t\t", unknownBool_var8, (unsigned char)0);
		}

		void ParseItemData_v12(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var2, (int)18446744073709551615);
			ParseItemHeader_v12(handler, blockOutput);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3, "\t\t");
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{

				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Constant);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Static);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Random);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Title);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment1);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment2);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment3);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment4);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment5);
			}
			ParseItemEnchantment_v12(handler, blockOutput.Enchantment);

			{

				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var6 = 0;
					Read<int>("statCount", handler, statCount_var6, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var6);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var6, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var6);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var7 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var7 = handler.GetItemExtraDataType(itemId_param0);
			}

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var7, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var7 == 1)
			{
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var7 == 2)
			{
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var7 == 3)
			{
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var7 == 4)
			{
				ParseItemBadge_v12(handler, blockOutput.Badge);
			}
			ParseItemTransfer_v12(handler, blockOutput.ItemTransfer);
			ParseItemSocket_v12(handler, blockOutput.ItemSocket);
			ParseItemCouple_v12(handler, blockOutput.ItemCouple);
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		void ParseEffectStats_v12(PacketHandler& handler, Maple::Game::EffectStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("startTime", handler, blockOutput.StartTime, "\t\t");
			Read<int>("endTime", handler, blockOutput.EndTime, "\t\t");
			Read<int>("effectId", handler, blockOutput.EffectId, "\t\t");
			Read<short>("effectLevel", handler, blockOutput.EffectLevel, "\t\t");
			Read<int>("stacks", handler, blockOutput.Stacks, "\t\t");
		}

		void ParseCharacterData_v12(PacketHandler& handler, Maple::Game::CharacterData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("accountId", handler, blockOutput.AccountId, "\t\t");
			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
			Read<unsigned char>("gender", handler, blockOutput.Gender, "\t\t");

			ValidateValues(stream, "gender", "\t\t", blockOutput.Gender, (unsigned char)0, (unsigned char)1);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");
			Read<int>("mapId", handler, blockOutput.MapId, "\t\t");
			Read<int>("mapInstanceId", handler, blockOutput.MapInstanceId, "\t\t");

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9, "\t\t");
			Read<unsigned short>("level", handler, blockOutput.Level, "\t\t");
			Read<unsigned short>("channel", handler, blockOutput.Channel, "\t\t");
			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			Read<int>("job", handler, blockOutput.Job, "\t\t");
			Read<int>("currentHp", handler, blockOutput.Hp.Current, "\t\t");
			Read<int>("maxHp", handler, blockOutput.Hp.Max, "\t\t");

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16, "\t\t");

			long long unknown_var17 = 0;
			Read<long long>("unknown", handler, unknown_var17, "\t\t");

			long long storageCooldown_var18 = 0;
			Read<long long>("storageCooldown", handler, storageCooldown_var18, "\t\t");

			blockOutput.StorageCooldown = (long)storageCooldown_var18;

			long long doctorCooldown_var19 = 0;
			Read<long long>("doctorCooldown", handler, doctorCooldown_var19, "\t\t");

			blockOutput.DoctorCooldown = (long)doctorCooldown_var19;

			Read<int>("returnMapId", handler, blockOutput.ReturnMapId, "\t\t");
			Read<Vector3S>("returnPosition", handler, blockOutput.ReturnPosition, "\t\t");
			Read<int>("gearScore", handler, blockOutput.GearScore, "\t\t");

			Color4I_BGRA skinColorPrimary_var23;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var23, "\t\t");

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var23;

			Color4I_BGRA skinColorSecondary_var24;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var24, "\t\t");

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var24;

			long long creationTime_var25 = 0;
			Read<long long>("creationTime", handler, creationTime_var25, "\t\t");

			blockOutput.CreationTime = (long)creationTime_var25;

			Read<int>("combatTrophyCount", handler, blockOutput.CombatTrophyCount, "\t\t");
			Read<int>("adventureTrophyCount", handler, blockOutput.AdventureTrophyCount, "\t\t");
			Read<int>("lifestyleTrophyCount", handler, blockOutput.LifestyleTrophyCount, "\t\t");
			Read<long long>("guildId", handler, blockOutput.GuildId, "\t\t");
			Read<std::wstring>("guildName", handler, blockOutput.GuildName, "\t\t");
			Read<std::wstring>("guildMotto", handler, blockOutput.GuildMotto, "\t\t");
			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");

			unsigned char clubCount_var33 = 0;
			Read<unsigned char>("clubCount", handler, clubCount_var33, "\t\t");

			ResizeVector(handler, blockOutput.Clubs, clubCount_var33);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < clubCount_var33 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<bool>("hasClub", handler, blockOutput.Clubs[i].HasClub, "\t\t\t");

				ValidateValues(stream, "hasClub", "\t\t\t", blockOutput.Clubs[i].HasClub, (bool)0, (bool)1);

				if (blockOutput.Clubs[i].HasClub)
				{
					Read<long long>("clubId", handler, blockOutput.Clubs[i].ClubId, "\t\t\t\t");
					Read<std::wstring>("clubName", handler, blockOutput.Clubs[i].ClubName, "\t\t\t\t");
				}
			}

			unsigned char unknown_var37 = 0;
			Read<unsigned char>("unknown", handler, unknown_var37, "\t\t");

			{

				int placeholderMastery_var38 = 0;
				Read<int>("placeholderMastery", handler, placeholderMastery_var38, "\t\t\t");

				ValidateValues(stream, "placeholderMastery", "\t\t\t", placeholderMastery_var38, (int)0);

				Read<int>("fishingMastery", handler, blockOutput.Mastery.Fishing, "\t\t\t");
				Read<int>("performanceMastery", handler, blockOutput.Mastery.Performance, "\t\t\t");
				Read<int>("miningMastery", handler, blockOutput.Mastery.Mining, "\t\t\t");
				Read<int>("foragingMastery", handler, blockOutput.Mastery.Foraging, "\t\t\t");
				Read<int>("ranchingMastery", handler, blockOutput.Mastery.Ranching, "\t\t\t");
				Read<int>("farmingMastery", handler, blockOutput.Mastery.Farming, "\t\t\t");
				Read<int>("smithingMastery", handler, blockOutput.Mastery.Smithing, "\t\t\t");
				Read<int>("handicraftMastery", handler, blockOutput.Mastery.Handicraft, "\t\t\t");
				Read<int>("alchemyMastery", handler, blockOutput.Mastery.Alchemy, "\t\t\t");
				Read<int>("cookingMastery", handler, blockOutput.Mastery.Cooking, "\t\t\t");
				Read<int>("petTamingMastery", handler, blockOutput.Mastery.PetTaming, "\t\t\t");
			}
			Read<std::wstring>("username", handler, blockOutput.Username, "\t\t");
			Read<long long>("sessionId", handler, blockOutput.SessionId, "\t\t");

			long long unknown_var52 = 0;
			Read<long long>("unknown", handler, unknown_var52, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var52, (long long)0, (long long)2000);

			long long unknown_var53 = 0;
			Read<long long>("unknown", handler, unknown_var53, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var53, (long long)0, (long long)3000);

			int unknownCount_var54 = 0;
			Read<int>("unknownCount", handler, unknownCount_var54, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems, unknownCount_var54);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var54 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var55 = 0;
				Read<long long>("unknown", handler, unknown_var55, "\t\t\t");
			}

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t\t");

			bool unknown_var57 = false;
			Read<bool>("unknown", handler, unknown_var57, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var57, (bool)0, (bool)1);

			long long birthday_var58 = 0;
			Read<long long>("birthday", handler, birthday_var58, "\t\t");

			blockOutput.Birthday = (long)birthday_var58;

			int unknown_var59 = 0;
			Read<int>("unknown", handler, unknown_var59, "\t\t");

			int unknown_var60 = 0;
			Read<int>("unknown", handler, unknown_var60, "\t\t");

			long long unknownTime_var61 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var61, "\t\t");
			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel, "\t\t");

			long long unknownTime_var63 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var63, "\t\t");

			int unknownCount2_var64 = 0;
			Read<int>("unknownCount2", handler, unknownCount2_var64, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems2, unknownCount2_var64);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount2_var64 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var65 = 0;
				Read<long long>("unknown", handler, unknown_var65, "\t\t\t");
			}

			int unknownCount3_var66 = 0;
			Read<int>("unknownCount3", handler, unknownCount3_var66, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems3, unknownCount3_var66);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount3_var66 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var67 = 0;
				Read<long long>("unknown", handler, unknown_var67, "\t\t\t");
			}

			short unknown_var68 = 0;
			Read<short>("unknown", handler, unknown_var68, "\t\t");

			long long unknown_var69 = 0;
			Read<long long>("unknown", handler, unknown_var69, "\t\t");
		}

		void ParseSkillDamagePacket_v12(PacketHandler& handler, Server::SkillDamagePacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("skillSn", handler, blockOutput.SkillSn, "\t\t");
			Read<long long>("skillAttack", handler, blockOutput.SkillAttack, "\t\t");
			Read<int>("casterId", handler, blockOutput.CasterId, "\t\t");
			Read<unsigned int>("skillId", handler, blockOutput.SkillId, "\t\t");
			Read<unsigned short>("skillLevel", handler, blockOutput.SkillLevel, "\t\t");
			Read<unsigned char>("motionPoint", handler, blockOutput.MotionPoint, "\t\t");
			Read<unsigned char>("attackPoint", handler, blockOutput.AttackPoint, "\t\t");
			Read<Vector3Short>("position", handler, blockOutput.Position, "\t\t");
			Read<Vector3Short>("direction", handler, blockOutput.Direction, "\t\t");

			unsigned char count_var9 = 0;
			Read<unsigned char>("count", handler, count_var9, "\t\t");

			ResizeVector(handler, blockOutput.DamagedTargets, count_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId, "\t\t\t");

				unsigned char damageCount_var11 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var11, "\t\t\t");

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var11);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var11 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

					ValidateValues(stream, "hitType", "\t\t\t\t", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
				}
			}
		}

		void ParseSkillDamageDotPacket_v12(PacketHandler& handler, Server::SkillDamageDotPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("casterId", handler, blockOutput.CasterId, "\t\t");
			Read<int>("targetId", handler, blockOutput.TargetId, "\t\t");
			Read<int>("serverTick", handler, blockOutput.ServerTick, "\t\t");
			Read<unsigned char>("hitType", handler, blockOutput.HitType, "\t\t");

			ValidateValues(stream, "hitType", "\t\t", blockOutput.HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);
		}

		void ParseSkillDamageHealPacket_v12(PacketHandler& handler, Server::SkillDamageHealPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("casterId", handler, blockOutput.CasterId, "\t\t");
			Read<int>("targetId", handler, blockOutput.TargetId, "\t\t");
			Read<int>("serverTick", handler, blockOutput.ServerTick, "\t\t");
			Read<int>("hpAmount", handler, blockOutput.HpAmount, "\t\t");
			Read<int>("spAmount", handler, blockOutput.SpAmount, "\t\t");
			Read<int>("epAmount", handler, blockOutput.EpAmount, "\t\t");
			Read<bool>("isVisible", handler, blockOutput.IsVisible, "\t\t");

			ValidateValues(stream, "isVisible", "\t\t", blockOutput.IsVisible, (bool)0, (bool)1);
		}

		void ParseSkillDamageRegionPacket_v12(PacketHandler& handler, Server::SkillDamageRegionPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("skillSn", handler, blockOutput.SkillSn, "\t\t");
			Read<int>("casterId", handler, blockOutput.CasterId, "\t\t");
			Read<int>("regionSkillObjectId", handler, blockOutput.RegionSkillObjectId, "\t\t");
			Read<unsigned char>("attackPoint", handler, blockOutput.AttackPoint, "\t\t");

			unsigned char count_var4 = 0;
			Read<unsigned char>("count", handler, count_var4, "\t\t");

			ResizeVector(handler, blockOutput.DamagedTargets, count_var4);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId, "\t\t\t");

				unsigned char damageCount_var6 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var6, "\t\t\t");
				Read<Vector3Short>("position", handler, blockOutput.DamagedTargets[i].Position, "\t\t\t");
				Read<Vector3S>("direction", handler, blockOutput.DamagedTargets[i].Direction, "\t\t\t");

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

					ValidateValues(stream, "hitType", "\t\t\t\t", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
				}
			}
		}

		void ParseSkillDamageTilePacket_v12(PacketHandler& handler, Server::SkillDamageTilePacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("skillSn", handler, blockOutput.SkillSn, "\t\t");
			Read<unsigned int>("skillId", handler, blockOutput.SkillId, "\t\t");
			Read<unsigned short>("skillLevel", handler, blockOutput.SkillLevel, "\t\t");

			unsigned char count_var3 = 0;
			Read<unsigned char>("count", handler, count_var3, "\t\t");

			ResizeVector(handler, blockOutput.DamagedTargets, count_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId, "\t\t\t");

				unsigned char damageCount_var5 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var5, "\t\t\t");
				Read<Vector3Short>("position", handler, blockOutput.DamagedTargets[i].Position, "\t\t\t");
				Read<Vector3S>("direction", handler, blockOutput.DamagedTargets[i].Direction, "\t\t\t");

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var5 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

					ValidateValues(stream, "hitType", "\t\t\t\t", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
				}
			}
		}

		void ParseEquipmentData_v12(PacketHandler& handler, Maple::Game::EquipmentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<std::wstring>("slot", handler, blockOutput.SlotName, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
			ParseItemData_v12(handler, blockOutput.Data, (unsigned int)blockOutput.ItemId);
		}

		void ParseCharacterEquipmentItems_v12(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v12(handler, blockOutput.Equipment[i]);
			}
		}

		void ParseCharacterEquipmentBadges_v12(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot, "\t\t\t");
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, blockOutput.Badges[i].Data, (unsigned int)blockOutput.Badges[i].ItemId);
			}
		}

		void ParseCharacterEquipmentSkins_v12(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v12(handler, blockOutput.Skins[i]);
				}
			}
		}

		void ParseCharacterEquipmentFashion_v12(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFashion", handler, blockOutput.HasFashion, "\t\t");

			ValidateValues(stream, "hasFashion", "\t\t", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v12(handler, blockOutput.Fashion[i]);
				}
			}
		}

		void ParseCharacterEquipmentSkinsMandatory_v12(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			long long unknown_var1 = 0;
			Read<long long>("unknown", handler, unknown_var1, "\t\t");

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2, "\t\t");

			unsigned char skinCount_var3 = 0;
			Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t");

			ResizeVector(handler, blockOutput.Skins, skinCount_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v12(handler, blockOutput.Skins[i]);
			}
		}

		void ParseCharacterListEntry_v12(PacketHandler& handler, Maple::Game::CharacterListEntry& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ParseCharacterData_v12(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime, "\t\t");
			ParseCharacterEquipmentItems_v12(handler, blockOutput.Equipment);
			ParseCharacterEquipmentBadges_v12(handler, blockOutput.Equipment);
			ParseCharacterEquipmentSkins_v12(handler, blockOutput.Equipment);
		}

		void ParseSkillTreePageData_v12(PacketHandler& handler, Maple::Game::SkillTreePageData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0, "\t\t");

			ResizeVector(handler, blockOutput.Skills, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<bool>("notify", handler, blockOutput.Skills[i].Notify, "\t\t\t");

				ValidateValues(stream, "notify", "\t\t\t", blockOutput.Skills[i].Notify, (bool)0, (bool)1);

				Read<bool>("enabled", handler, blockOutput.Skills[i].Enabled, "\t\t\t");

				ValidateValues(stream, "enabled", "\t\t\t", blockOutput.Skills[i].Enabled, (bool)0, (bool)1);

				Read<int>("skillId", handler, blockOutput.Skills[i].SkillId, "\t\t\t");
				Read<int>("skillLevel", handler, blockOutput.Skills[i].SkillLevel, "\t\t\t");

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var5, (bool)0, (bool)1);
			}
		}

		void ParseSkillTreeData_v12(PacketHandler& handler, Maple::Game::SkillTreeData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("job", handler, blockOutput.Job, "\t\t");

			unsigned char unknownCount_var1 = 0;
			Read<unsigned char>("unknownCount", handler, unknownCount_var1, "\t\t");

			ValidateValues(stream, "unknownCount", "\t\t", unknownCount_var1, (unsigned char)1);

			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			ParseSkillTreePageData_v12(handler, blockOutput.Active);
			ParseSkillTreePageData_v12(handler, blockOutput.Passive);
			ParseSkillTreePageData_v12(handler, blockOutput.Special);
			ParseSkillTreePageData_v12(handler, blockOutput.Consumable);
		}

		void ParseNpcDialog_v12(PacketHandler& handler, Maple::Game::NpcDialogData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("scriptId", handler, blockOutput.ScriptId, "\t\t");
			Read<int>("scriptIndex", handler, blockOutput.ScriptIndex, "\t\t");
			Read<int>("Options", handler, blockOutput.Options, "\t\t");
		}

		void ParseScriptContent_v12(PacketHandler& handler, Maple::Game::ScriptContentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<std::wstring>("text", handler, blockOutput.Text, "\t\t");
			Read<std::wstring>("voiceId", handler, blockOutput.VoiceId, "\t\t");
			Read<std::wstring>("illustration", handler, blockOutput.Illustration, "\t\t");
		}

		void ParseShopData_v12(PacketHandler& handler, Server::ShopOpenPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("npcId", handler, blockOutput.NpcId, "\t\t");
			Read<int>("shopId", handler, blockOutput.ShopId, "\t\t");
			Read<long long>("resetTime", handler, blockOutput.ResetTime, "\t\t");
			Read<int>("remainingSeconds", handler, blockOutput.RemainingSeconds, "\t\t");
			Read<short>("itemCount", handler, blockOutput.ItemCount, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t\t");

			bool unknown_var7 = false;
			Read<bool>("unknown", handler, unknown_var7, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var7, (bool)0, (bool)1);

			Read<bool>("canRestock", handler, blockOutput.CanRestock, "\t\t");

			ValidateValues(stream, "canRestock", "\t\t", blockOutput.CanRestock, (bool)0, (bool)1);

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var9, (bool)0, (bool)1);

			unsigned char unknown_var10 = 0;
			Read<unsigned char>("unknown", handler, unknown_var10, "\t\t");

			bool unknown_var11 = false;
			Read<bool>("unknown", handler, unknown_var11, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

			bool unknown_var12 = false;
			Read<bool>("unknown", handler, unknown_var12, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var12, (bool)0, (bool)1);

			bool unknown_var13 = false;
			Read<bool>("unknown", handler, unknown_var13, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var13, (bool)0, (bool)1);

			bool unknown_var14 = false;
			Read<bool>("unknown", handler, unknown_var14, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var14, (bool)0, (bool)1);

			Read<std::string>("shopName", handler, blockOutput.ShopName, "\t\t");

			if (blockOutput.CanRestock)
			{
				unsigned char unknown_var16 = 0;
				Read<unsigned char>("unknown", handler, unknown_var16, "\t\t\t");

				unsigned char unknown_var17 = 0;
				Read<unsigned char>("unknown", handler, unknown_var17, "\t\t\t");

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18, "\t\t\t");
				Read<int>("instantRestockCost", handler, blockOutput.InstantRestockCost, "\t\t\t");

				bool unknown_var20 = false;
				Read<bool>("unknown", handler, unknown_var20, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var20, (bool)0, (bool)1);

				int unknown_var21 = 0;
				Read<int>("unknown", handler, unknown_var21, "\t\t\t");
				Read<unsigned char>("shopType", handler, blockOutput.ShopType, "\t\t\t");

				bool unknown_var23 = false;
				Read<bool>("unknown", handler, unknown_var23, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var23, (bool)0, (bool)1);

				bool unknown_var24 = false;
				Read<bool>("unknown", handler, unknown_var24, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var24, (bool)0, (bool)1);
			}
		}

		void ParseBuyPeriodData_v12(PacketHandler& handler, Maple::Game::BuyPeriodData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSpecificTime", handler, blockOutput.HasSpecificTime, "\t\t");

			ValidateValues(stream, "hasSpecificTime", "\t\t", blockOutput.HasSpecificTime, (bool)0, (bool)1);

			if (blockOutput.HasSpecificTime)
			{
				Read<long long>("startTime", handler, blockOutput.StartTime, "\t\t\t");
				Read<long long>("endTime", handler, blockOutput.EndTime, "\t\t\t");
			}
			Read<bool>("hasSpecificDays", handler, blockOutput.HasSpecificDays, "\t\t");

			ValidateValues(stream, "hasSpecificDays", "\t\t", blockOutput.HasSpecificDays, (bool)0, (bool)1);

			if (blockOutput.HasSpecificDays)
			{
				unsigned char timeCount_var4 = 0;
				Read<unsigned char>("timeCount", handler, timeCount_var4, "\t\t\t");

				ResizeVector(handler, blockOutput.DayTimes, timeCount_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < timeCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("startTime", handler, blockOutput.DayTimes[i].StartTime, "\t\t\t\t");
					Read<int>("endTime", handler, blockOutput.DayTimes[i].EndTime, "\t\t\t\t");
				}

				unsigned char dayCount_var7 = 0;
				Read<unsigned char>("dayCount", handler, dayCount_var7, "\t\t\t");

				ResizeVector(handler, blockOutput.Days, dayCount_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < dayCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<unsigned char>("dayOfWeek", handler, blockOutput.Days[i].DayOfWeek, "\t\t\t\t");

					ValidateValues(stream, "dayOfWeek", "\t\t\t\t", blockOutput.Days[i].DayOfWeek, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);
				}
			}
		}

		void ParseShopItemData_v12(PacketHandler& handler, Server::ShopLoadItemsPacket::ItemEntry& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0, "\t\t");
			Read<int>("currencyId", handler, blockOutput.CurrencyId, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			Read<int>("price", handler, blockOutput.Price, "\t\t");
			Read<int>("price2", handler, blockOutput.Price2, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");
			Read<int>("maxStock", handler, blockOutput.MaxStock, "\t\t");
			Read<int>("totalSold", handler, blockOutput.TotalSold, "\t\t");

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9, "\t\t");
			Read<std::string>("shopCategory", handler, blockOutput.ShopCategory, "\t\t");
			Read<int>("achievementRequired", handler, blockOutput.AchievementRequired, "\t\t");

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12, "\t\t");

			unsigned char unknown_var13 = 0;
			Read<unsigned char>("unknown", handler, unknown_var13, "\t\t");

			short unknown_var14 = 0;
			Read<short>("unknown", handler, unknown_var14, "\t\t");

			unsigned char unknown_var15 = 0;
			Read<unsigned char>("unknown", handler, unknown_var15, "\t\t");

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16, "\t\t");

			bool unknown_var17 = false;
			Read<bool>("unknown", handler, unknown_var17, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var17, (bool)0, (bool)1);

			Read<short>("bundleSize", handler, blockOutput.BundleSize, "\t\t");

			unsigned char unknown_var19 = 0;
			Read<unsigned char>("unknown", handler, unknown_var19, "\t\t");

			unsigned char unknown_var20 = 0;
			Read<unsigned char>("unknown", handler, unknown_var20, "\t\t");
			Read<std::string>("currencyIdString", handler, blockOutput.CurrencyIdString, "\t\t");

			short unknown_var22 = 0;
			Read<short>("unknown", handler, unknown_var22, "\t\t");

			int unknown_var23 = 0;
			Read<int>("unknown", handler, unknown_var23, "\t\t");

			bool unknown_var24 = false;
			Read<bool>("unknown", handler, unknown_var24, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var24, (bool)0, (bool)1);

			Read<bool>("hasBuyPeriod", handler, blockOutput.HasBuyPeriod, "\t\t");

			ValidateValues(stream, "hasBuyPeriod", "\t\t", blockOutput.HasBuyPeriod, (bool)0, (bool)1);

			if (blockOutput.HasBuyPeriod)
			{
				ParseBuyPeriodData_v12(handler, blockOutput.BuyPeriod);
			}
		}

		void ParseMeretShopPremiumItem_v12(PacketHandler& handler, Maple::Game::MeretShopPremiumItemData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("entryId", handler, blockOutput.EntryId, "\t\t");

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var3, (bool)0, (bool)1);

			Read<int>("parentId", handler, blockOutput.ParentId, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7, "\t\t");
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel, "\t\t");
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType, "\t\t");
			Read<long long>("price", handler, blockOutput.Price, "\t\t");
			Read<long long>("SalePrice", handler, blockOutput.SalePrice, "\t\t");

			unsigned char unknown_var12 = 0;
			Read<unsigned char>("unknown", handler, unknown_var12, "\t\t");
			Read<long long>("sellBeginTime", handler, blockOutput.SellBeginTime, "\t\t");
			Read<long long>("sellEndTime", handler, blockOutput.SellEndTime, "\t\t");

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15, "\t\t");

			int unknown_var16 = 0;
			Read<int>("unknown", handler, unknown_var16, "\t\t");
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable, "\t\t");

			ValidateValues(stream, "restockUnavailable", "\t\t", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var18 = 0;
			Read<int>("unknown", handler, unknown_var18, "\t\t");

			unsigned char unknown_var19 = 0;
			Read<unsigned char>("unknown", handler, unknown_var19, "\t\t");
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel, "\t\t");
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel, "\t\t");
			Read<int>("requiredJob", handler, blockOutput.RequiredJob, "\t\t");
			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");
			Read<int>("itemDuration", handler, blockOutput.ItemDuration, "\t\t");
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity, "\t\t");
			Read<int>("tabId", handler, blockOutput.TabId, "\t\t");

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29, "\t\t");

			int unknown_var30 = 0;
			Read<int>("unknown", handler, unknown_var30, "\t\t");

			unsigned char unknown_var31 = 0;
			Read<unsigned char>("unknown", handler, unknown_var31, "\t\t");
			Read<int>("marketBannerLabel", handler, blockOutput.MarketBannerLabel, "\t\t");
			Read<std::string>("bannerName", handler, blockOutput.BannerName, "\t\t");

			std::string unknown_var34;
			Read<std::string>("unknown", handler, unknown_var34, "\t\t");

			bool unknown_var35 = false;
			Read<bool>("unknown", handler, unknown_var35, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var35, (bool)0, (bool)1);

			unsigned char unknown_var36 = 0;
			Read<unsigned char>("unknown", handler, unknown_var36, "\t\t");

			int unknown_var37 = 0;
			Read<int>("unknown", handler, unknown_var37, "\t\t");

			bool unknown_var38 = false;
			Read<bool>("unknown", handler, unknown_var38, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var38, (bool)0, (bool)1);

			Read<int>("requiredAchievementId", handler, blockOutput.RequiredAchievementId, "\t\t");
			Read<int>("requiredAchievementRank", handler, blockOutput.RequiredAchievementRank, "\t\t");

			int unknown_var41 = 0;
			Read<int>("unknown", handler, unknown_var41, "\t\t");
			Read<bool>("pcCafe", handler, blockOutput.PcCafe, "\t\t");

			ValidateValues(stream, "pcCafe", "\t\t", blockOutput.PcCafe, (bool)0, (bool)1);

			bool unknown_var43 = false;
			Read<bool>("unknown", handler, unknown_var43, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var43, (bool)0, (bool)1);

			int unknown_var44 = 0;
			Read<int>("unknown", handler, unknown_var44, "\t\t");
		}

		void ParseMailAdData_v12(PacketHandler& handler, Maple::Game::MailAdData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3, "\t\t");

			long long unknown_var4 = 0;
			Read<long long>("unknown", handler, unknown_var4, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			long long unknown_var6 = 0;
			Read<long long>("unknown", handler, unknown_var6, "\t\t");
		}

		void ParseMailAttachData_v12(PacketHandler& handler, Maple::Game::MailAttachData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("index", handler, blockOutput.Index, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7, "\t\t");
			ParseItemData_v12(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseMailData_v12(PacketHandler& handler, Maple::Game::MailData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("type", handler, blockOutput.Type, "\t\t");

			ValidateValues(stream, "type", "\t\t", blockOutput.Type, (unsigned char)1, (unsigned char)101, (unsigned char)102, (unsigned char)200, (unsigned char)104, (unsigned char)107);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId, "\t\t");
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId, "\t\t");
			Read<std::wstring>("senderName", handler, blockOutput.SenderName, "\t\t");
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle, "\t\t");
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent, "\t\t");
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey, "\t\t");
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue, "\t\t");

			if (blockOutput.Type == 200)
			{
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8, "\t\t\t");

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10, "\t\t\t");

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11, "\t\t\t");
			}

			else
			{
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12, "\t\t\t");

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAttachData_v12(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos, "\t\t");
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp, "\t\t");
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets, "\t\t");

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16, "\t\t");
			Read<long long>("redMerets", handler, blockOutput.RedMerets, "\t\t");

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18, "\t\t");

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19, "\t\t");

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20, "\t\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t\t");

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22, "\t\t\t");

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23, "\t\t\t");
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");
			Read<long long>("sentTime", handler, blockOutput.SentTime, "\t\t");

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27, "\t\t");
		}

		void ParseMeretShopPremiumItemEntry_v12(PacketHandler& handler, Maple::Game::MeretShopPremiumItemEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("entryId", handler, blockOutput.EntryId, "\t\t");

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var3, (bool)0, (bool)1);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t\t");
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel, "\t\t");
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType, "\t\t");
			Read<long long>("price", handler, blockOutput.Price, "\t\t");
			Read<long long>("SalePrice", handler, blockOutput.SalePrice, "\t\t");

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11, "\t\t");

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12, "\t\t");

			int unknown_var13 = 0;
			Read<int>("unknown", handler, unknown_var13, "\t\t");
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable, "\t\t");

			ValidateValues(stream, "restockUnavailable", "\t\t", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15, "\t\t");

			unsigned char unknown_var16 = 0;
			Read<unsigned char>("unknown", handler, unknown_var16, "\t\t");
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel, "\t\t");
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel, "\t\t");
			Read<int>("requiredJob", handler, blockOutput.RequiredJob, "\t\t");
			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");
			Read<int>("itemDuration", handler, blockOutput.ItemDuration, "\t\t");
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity, "\t\t");
			Read<int>("tabId", handler, blockOutput.TabId, "\t\t");

			int unknown_var26 = 0;
			Read<int>("unknown", handler, unknown_var26, "\t\t");

			bool unknown_var27 = false;
			Read<bool>("unknown", handler, unknown_var27, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var27, (bool)0, (bool)1);

			unsigned char unknown_var28 = 0;
			Read<unsigned char>("unknown", handler, unknown_var28, "\t\t");

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29, "\t\t");

			unsigned char count_var30 = 0;
			Read<unsigned char>("count", handler, count_var30, "\t\t");

			ResizeVector(handler, blockOutput.AdditionalQuantities, count_var30);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<bool>("hasEntry", handler, blockOutput.AdditionalQuantities[i].HasEntry, "\t\t\t");

				ValidateValues(stream, "hasEntry", "\t\t\t", blockOutput.AdditionalQuantities[i].HasEntry, (bool)0, (bool)1);

				if (blockOutput.AdditionalQuantities[i].HasEntry)
				{
					ParseMeretShopPremiumItem_v12(handler, blockOutput.AdditionalQuantities[i].EntryData);

					Read<bool>("hasUnknown", handler, blockOutput.AdditionalQuantities[i].HasUnknown, "\t\t\t\t");

					ValidateValues(stream, "hasUnknown", "\t\t\t\t", blockOutput.AdditionalQuantities[i].HasUnknown, (bool)0, (bool)1);

					if (blockOutput.AdditionalQuantities[i].HasUnknown)
					{
						std::string unknown_var33;
						Read<std::string>("unknown", handler, unknown_var33, "\t\t\t\t\t");

						long long unknown_var34 = 0;
						Read<long long>("unknown", handler, unknown_var34, "\t\t\t\t\t");

						long long unknown_var35 = 0;
						Read<long long>("unknown", handler, unknown_var35, "\t\t\t\t\t");
					}

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36, "\t\t\t\t");

					bool unknown_var37 = false;
					Read<bool>("unknown", handler, unknown_var37, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var37, (bool)0, (bool)1);
				}
			}
		}

		void ParseCharacterDetailsHeader_v12(PacketHandler& handler, Server::CharacterInfoPacket::CharacterDetails& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("accountId", handler, blockOutput.AccountId, "\t\t");
			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("characterName", handler, blockOutput.Name, "\t\t");
			Read<short>("level", handler, blockOutput.Level, "\t\t");
			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			Read<int>("job", handler, blockOutput.Job, "\t\t");
			Read<int>("gender", handler, blockOutput.Gender, "\t\t");

			ValidateValues(stream, "gender", "\t\t", blockOutput.Gender, (int)0, (int)1);

			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel, "\t\t");

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var8, (unsigned char)0);
		}

		void ParseCharacterDetailsBody_v12(PacketHandler& handler, Server::CharacterInfoPacket::CharacterDetails& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");
			Read<std::wstring>("motto", handler, blockOutput.Motto, "\t\t");
			Read<std::wstring>("guildName", handler, blockOutput.GuildName, "\t\t");
			Read<std::wstring>("guildRank", handler, blockOutput.GuildRank, "\t\t");
			Read<std::wstring>("houseName", handler, blockOutput.HouseName, "\t\t");
			Read<int>("plotMapId", handler, blockOutput.PlotMapId, "\t\t");
			Read<int>("plotNumber", handler, blockOutput.PlotNumber, "\t\t");
			Read<int>("apartmentNumber", handler, blockOutput.ApartmentNumber, "\t\t");
			Read<int>("characterTitle", handler, blockOutput.CharacterTitle, "\t\t");

			int unlockedTitles_var9 = 0;
			Read<int>("unlockedTitles", handler, unlockedTitles_var9, "\t\t");

			ResizeVector(handler, blockOutput.UnlockedTitles, unlockedTitles_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unlockedTitles_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("titleId", handler, blockOutput.UnlockedTitles[i].TitleId, "\t\t\t");
			}
			Read<int>("trophyCount", handler, blockOutput.TrophyCount, "\t\t");
			Read<int>("gearScore", handler, blockOutput.GearScore, "\t\t");
			Read<long long>("lastLoggedIn", handler, blockOutput.LastLoggedIn, "\t\t");

			long long unknown_var14 = 0;
			Read<long long>("unknown", handler, unknown_var14, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var14, (long long)0, (long long)1, (long long)30);

			Color4I_BGRA skinColorPrimary_var15;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var15, "\t\t");

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var15;

			Color4I_BGRA skinColorSecondary_var16;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var16, "\t\t");

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var16;

			Read<short>("maritalStatus", handler, blockOutput.MaritalStatus, "\t\t");
			Read<std::wstring>("spouse1Name", handler, blockOutput.Spouse1Name, "\t\t");
			Read<std::wstring>("spouse2Name", handler, blockOutput.Spouse2Name, "\t\t");
			Read<long long>("proposalTimestamp", handler, blockOutput.ProposalTimestamp, "\t\t");
		}

		void ParseCharacterDetailsBasicStats_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("max", handler, blockOutput.Basic[i].Max, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("base", handler, blockOutput.Basic[i].Base, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("current", handler, blockOutput.Basic[i].Current, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<float>("rate", handler, blockOutput.Basic[i].Rate, "\t\t\t");
			}
		}

		void ParseCharacterDetailsSpecialStats_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char specialStatCount_var0 = 180;

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<float>("rate", handler, blockOutput.Special[i].Rate, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<float>("value", handler, blockOutput.Special[i].Value, "\t\t\t");
			}
		}

		void ParseCubeItemData_v12(PacketHandler& handler, Maple::Game::CubeItemData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2, "\t\t");
			Read<bool>("isUgc", handler, blockOutput.IsUgc, "\t\t");

			ValidateValues(stream, "isUgc", "\t\t", blockOutput.IsUgc, (bool)0, (bool)1);

			if (blockOutput.IsUgc)
			{
				ParseItemUgc_v12(handler, blockOutput.Ugc);
			}
		}

		void ParseMountData_v12(PacketHandler& handler, Maple::Game::MountData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("rideMode", handler, blockOutput.RideMode, "\t\t");

			ValidateValues(stream, "rideMode", "\t\t", blockOutput.RideMode, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			Read<int>("mountId", handler, blockOutput.MountId, "\t\t");
			Read<int>("mountObjectId", handler, blockOutput.MountObjectId, "\t\t");

			if (blockOutput.RideMode == (Enum::RideMode)1)
			{
				Read<int>("itemId", handler, blockOutput.ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t\t");
				ParseItemUgc_v12(handler, blockOutput.Ugc);
			}

			if (blockOutput.RideMode == (Enum::RideMode)2)
			{
				Read<int>("effectId", handler, blockOutput.EffectId, "\t\t\t");
				Read<short>("effectLevel", handler, blockOutput.EffectLevel, "\t\t\t");
			}

			unsigned char count_var7 = 0;
			Read<unsigned char>("count", handler, count_var7, "\t\t");

			ResizeVector(handler, blockOutput.UnknownData, count_var7);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8, "\t\t\t");

				unsigned char unknown_var9 = 0;
				Read<unsigned char>("unknown", handler, unknown_var9, "\t\t\t");
			}
		}

		void ParseEnchantScrollEnchantUi_v12(PacketHandler& handler, Server::EnchantScrollEnchantUiPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<short>("scrollType", handler, blockOutput.ScrollType, "\t\t");

			ValidateValues(stream, "scrollType", "\t\t", blockOutput.ScrollType, (short)1, (short)2, (short)3, (short)4);

			Read<bool>("untradeableReminder", handler, blockOutput.UntradeableReminder, "\t\t");

			ValidateValues(stream, "untradeableReminder", "\t\t", blockOutput.UntradeableReminder, (bool)0, (bool)1);

			Read<int>("enchantLevel", handler, blockOutput.EnchantLevel, "\t\t");
			Read<int>("enchantRate", handler, blockOutput.EnchantRate, "\t\t");
			Read<short>("minLevel", handler, blockOutput.MinLevel, "\t\t");
			Read<short>("maxLevel", handler, blockOutput.MaxLevel, "\t\t");

			unsigned int itemTypeCount_var7 = 0;
			Read<unsigned int>("itemTypeCount", handler, itemTypeCount_var7, "\t\t");

			ResizeVector(handler, blockOutput.ItemTypes, itemTypeCount_var7);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned int i = 0; i < itemTypeCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("itemType", handler, blockOutput.ItemTypes[i].ItemType, "\t\t\t");
			}

			unsigned int itemRarityCount_var9 = 0;
			Read<unsigned int>("itemRarityCount", handler, itemRarityCount_var9, "\t\t");

			ResizeVector(handler, blockOutput.ItemRarities, itemRarityCount_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned int i = 0; i < itemRarityCount_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("itemRarity", handler, blockOutput.ItemRarities[i].ItemRarity, "\t\t\t");
			}

			if (blockOutput.ScrollType == (Server::EnchantScrollEnchantUiPacket::ScrollTypeEnum)3)
			{
				Read<int>("minEnchant", handler, blockOutput.MinEnchant, "\t\t\t");
				Read<int>("maxEnchant", handler, blockOutput.MaxEnchant, "\t\t\t");
			}
		}

		void ParseEnchantScrollStatUi_v12(PacketHandler& handler, Server::EnchantScrollStatUiPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<short>("scrollType", handler, blockOutput.ScrollType, "\t\t");

			ValidateValues(stream, "scrollType", "\t\t", blockOutput.ScrollType, (short)1, (short)2, (short)3, (short)4);

			if (blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)5)
			{
			}
			else if (blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)3)
			{
				unsigned int minStatCount_var2 = 0;
				Read<unsigned int>("minStatCount", handler, minStatCount_var2, "\t\t\t");

				ResizeVector(handler, blockOutput.MinStats, minStatCount_var2);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < minStatCount_var2 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<short>("statType", handler, blockOutput.MinStats[i].Type, "\t\t\t\t");
					Read<float>("minRate", handler, blockOutput.MinStats[i].Rate, "\t\t\t\t");
					Read<int>("minValue", handler, blockOutput.MinStats[i].Value, "\t\t\t\t");
				}

				unsigned int maxStatCount_var6 = 0;
				Read<unsigned int>("maxStatCount", handler, maxStatCount_var6, "\t\t\t");

				ResizeVector(handler, blockOutput.MaxStats, maxStatCount_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < maxStatCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<short>("statType", handler, blockOutput.MaxStats[i].Type, "\t\t\t\t");
					Read<float>("maxRate", handler, blockOutput.MaxStats[i].Rate, "\t\t\t\t");
					Read<int>("maxValue", handler, blockOutput.MaxStats[i].Value, "\t\t\t\t");
				}
			}

			else
			{
				unsigned int statCount_var10 = 0;
				Read<unsigned int>("statCount", handler, statCount_var10, "\t\t\t");

				ResizeVector(handler, blockOutput.Stats, statCount_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < statCount_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<short>("statType", handler, blockOutput.Stats[i].Type, "\t\t\t\t");
					Read<float>("rate", handler, blockOutput.Stats[i].Rate, "\t\t\t\t");
					Read<int>("value", handler, blockOutput.Stats[i].Value, "\t\t\t\t");
				}
			}
		}

		void ParseBlackMarketEntryData_v12(PacketHandler& handler, Maple::Game::BlackMarketEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId, "\t\t");
			Read<long long>("timeListed", handler, blockOutput.TimeListed, "\t\t");
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2, "\t\t");
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires, "\t\t");
			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem, "\t\t");

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId, "\t\t");
			ParseItemData_v12(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseFieldPetData_v12(PacketHandler& handler, Maple::Game::FieldPetData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet, "\t\t");

			ValidateValues(stream, "hasFieldPet", "\t\t", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				Read<int>("itemId", handler, blockOutput.ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
			}
		}

		void ParsePetProfileData_v12(PacketHandler& handler, Maple::Game::PetProfileData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
			Read<long long>("exp", handler, blockOutput.Exp, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			Read<short>("level", handler, blockOutput.Level, "\t\t");

			short unknown_var4 = 0;
			Read<short>("unknown", handler, unknown_var4, "\t\t");

			short unknown_var5 = 0;
			Read<short>("unknown", handler, unknown_var5, "\t\t");
		}

		void ParsePetPotionSettingsData_v12(PacketHandler& handler, Maple::Game::PetPotionSettingsData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0, "\t\t");

			ResizeVector(handler, blockOutput.Slots, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("thresholdIndex", handler, blockOutput.Slots[i].ThresholdIndex, "\t\t\t");
				Read<float>("threshold", handler, blockOutput.Slots[i].Threshold, "\t\t\t");
				Read<int>("itemId", handler, blockOutput.Slots[i].ItemId, "\t\t\t");
			}
		}

		void ParsePetLootSettingsData_v12(PacketHandler& handler, Maple::Game::PetLootSettingsData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("mesos", handler, blockOutput.Mesos, "\t\t");

			ValidateValues(stream, "mesos", "\t\t", blockOutput.Mesos, (bool)0, (bool)1);

			Read<bool>("merets", handler, blockOutput.Merets, "\t\t");

			ValidateValues(stream, "merets", "\t\t", blockOutput.Merets, (bool)0, (bool)1);

			Read<bool>("other", handler, blockOutput.Other, "\t\t");

			ValidateValues(stream, "other", "\t\t", blockOutput.Other, (bool)0, (bool)1);

			Read<bool>("currency", handler, blockOutput.Currency, "\t\t");

			ValidateValues(stream, "currency", "\t\t", blockOutput.Currency, (bool)0, (bool)1);

			Read<bool>("equipment", handler, blockOutput.Equipment, "\t\t");

			ValidateValues(stream, "equipment", "\t\t", blockOutput.Equipment, (bool)0, (bool)1);

			Read<bool>("consumable", handler, blockOutput.Consumable, "\t\t");

			ValidateValues(stream, "consumable", "\t\t", blockOutput.Consumable, (bool)0, (bool)1);

			Read<bool>("gemstone", handler, blockOutput.Gemstone, "\t\t");

			ValidateValues(stream, "gemstone", "\t\t", blockOutput.Gemstone, (bool)0, (bool)1);

			Read<bool>("dropped", handler, blockOutput.Dropped, "\t\t");

			ValidateValues(stream, "dropped", "\t\t", blockOutput.Dropped, (bool)0, (bool)1);

			Read<int>("minRarity", handler, blockOutput.MinRarity, "\t\t");

			ValidateValues(stream, "minRarity", "\t\t", blockOutput.MinRarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<bool>("enabled", handler, blockOutput.Enabled, "\t\t");

			ValidateValues(stream, "enabled", "\t\t", blockOutput.Enabled, (bool)0, (bool)1);
		}

		void ParseCharacterData_v13(PacketHandler& handler, Maple::Game::CharacterData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("accountId", handler, blockOutput.AccountId, "\t\t");
			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
			Read<unsigned char>("gender", handler, blockOutput.Gender, "\t\t");

			ValidateValues(stream, "gender", "\t\t", blockOutput.Gender, (unsigned char)0, (unsigned char)1);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");
			Read<int>("mapId", handler, blockOutput.MapId, "\t\t");
			Read<int>("mapInstanceId", handler, blockOutput.MapInstanceId, "\t\t");

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9, "\t\t");
			Read<unsigned short>("level", handler, blockOutput.Level, "\t\t");
			Read<unsigned short>("channel", handler, blockOutput.Channel, "\t\t");
			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			Read<int>("job", handler, blockOutput.Job, "\t\t");
			Read<int>("currentHp", handler, blockOutput.Hp.Current, "\t\t");
			Read<int>("maxHp", handler, blockOutput.Hp.Max, "\t\t");

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16, "\t\t");

			long long unknown_var17 = 0;
			Read<long long>("unknown", handler, unknown_var17, "\t\t");

			long long storageCooldown_var18 = 0;
			Read<long long>("storageCooldown", handler, storageCooldown_var18, "\t\t");

			blockOutput.StorageCooldown = (long)storageCooldown_var18;

			long long doctorCooldown_var19 = 0;
			Read<long long>("doctorCooldown", handler, doctorCooldown_var19, "\t\t");

			blockOutput.DoctorCooldown = (long)doctorCooldown_var19;

			Read<int>("returnMapId", handler, blockOutput.ReturnMapId, "\t\t");
			Read<Vector3S>("returnPosition", handler, blockOutput.ReturnPosition, "\t\t");
			Read<int>("gearScore", handler, blockOutput.GearScore, "\t\t");

			Color4I_BGRA skinColorPrimary_var23;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var23, "\t\t");

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var23;

			Color4I_BGRA skinColorSecondary_var24;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var24, "\t\t");

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var24;

			long long creationTime_var25 = 0;
			Read<long long>("creationTime", handler, creationTime_var25, "\t\t");

			blockOutput.CreationTime = (long)creationTime_var25;

			Read<int>("combatTrophyCount", handler, blockOutput.CombatTrophyCount, "\t\t");
			Read<int>("adventureTrophyCount", handler, blockOutput.AdventureTrophyCount, "\t\t");
			Read<int>("lifestyleTrophyCount", handler, blockOutput.LifestyleTrophyCount, "\t\t");
			Read<long long>("guildId", handler, blockOutput.GuildId, "\t\t");
			Read<std::wstring>("guildName", handler, blockOutput.GuildName, "\t\t");
			Read<std::wstring>("guildMotto", handler, blockOutput.GuildMotto, "\t\t");
			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");

			unsigned char clubCount_var33 = 0;
			Read<unsigned char>("clubCount", handler, clubCount_var33, "\t\t");

			ResizeVector(handler, blockOutput.Clubs, clubCount_var33);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < clubCount_var33 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<bool>("hasClub", handler, blockOutput.Clubs[i].HasClub, "\t\t\t");

				ValidateValues(stream, "hasClub", "\t\t\t", blockOutput.Clubs[i].HasClub, (bool)0, (bool)1);

				if (blockOutput.Clubs[i].HasClub)
				{
					Read<long long>("clubId", handler, blockOutput.Clubs[i].ClubId, "\t\t\t\t");
					Read<std::wstring>("clubName", handler, blockOutput.Clubs[i].ClubName, "\t\t\t\t");
				}
			}

			unsigned char unknown_var37 = 0;
			Read<unsigned char>("unknown", handler, unknown_var37, "\t\t");

			{

				int placeholderMastery_var38 = 0;
				Read<int>("placeholderMastery", handler, placeholderMastery_var38, "\t\t\t");

				ValidateValues(stream, "placeholderMastery", "\t\t\t", placeholderMastery_var38, (int)0);

				Read<int>("fishingMastery", handler, blockOutput.Mastery.Fishing, "\t\t\t");
				Read<int>("performanceMastery", handler, blockOutput.Mastery.Performance, "\t\t\t");
				Read<int>("miningMastery", handler, blockOutput.Mastery.Mining, "\t\t\t");
				Read<int>("foragingMastery", handler, blockOutput.Mastery.Foraging, "\t\t\t");
				Read<int>("ranchingMastery", handler, blockOutput.Mastery.Ranching, "\t\t\t");
				Read<int>("farmingMastery", handler, blockOutput.Mastery.Farming, "\t\t\t");
				Read<int>("smithingMastery", handler, blockOutput.Mastery.Smithing, "\t\t\t");
				Read<int>("handicraftMastery", handler, blockOutput.Mastery.Handicraft, "\t\t\t");
				Read<int>("alchemyMastery", handler, blockOutput.Mastery.Alchemy, "\t\t\t");
				Read<int>("cookingMastery", handler, blockOutput.Mastery.Cooking, "\t\t\t");
				Read<int>("petTamingMastery", handler, blockOutput.Mastery.PetTaming, "\t\t\t");
			}
			Read<std::wstring>("username", handler, blockOutput.Username, "\t\t");
			Read<long long>("sessionId", handler, blockOutput.SessionId, "\t\t");

			int unknownCount_var52 = 0;
			Read<int>("unknownCount", handler, unknownCount_var52, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems, unknownCount_var52);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var52 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var53 = 0;
				Read<long long>("unknown", handler, unknown_var53, "\t\t\t");
			}

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t\t");

			bool unknown_var55 = false;
			Read<bool>("unknown", handler, unknown_var55, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var55, (bool)0, (bool)1);

			long long birthday_var56 = 0;
			Read<long long>("birthday", handler, birthday_var56, "\t\t");

			blockOutput.Birthday = (long)birthday_var56;

			int unknown_var57 = 0;
			Read<int>("unknown", handler, unknown_var57, "\t\t");

			int unknown_var58 = 0;
			Read<int>("unknown", handler, unknown_var58, "\t\t");

			long long unknownTime_var59 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var59, "\t\t");
			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel, "\t\t");

			long long unknownTime_var61 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var61, "\t\t");

			int unknownCount2_var62 = 0;
			Read<int>("unknownCount2", handler, unknownCount2_var62, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems2, unknownCount2_var62);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount2_var62 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var63 = 0;
				Read<long long>("unknown", handler, unknown_var63, "\t\t\t");
			}

			int unknownCount3_var64 = 0;
			Read<int>("unknownCount3", handler, unknownCount3_var64, "\t\t");

			ResizeVector(handler, blockOutput.UnknownItems3, unknownCount3_var64);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount3_var64 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				long long unknown_var65 = 0;
				Read<long long>("unknown", handler, unknown_var65, "\t\t\t");
			}

			short unknown_var66 = 0;
			Read<short>("unknown", handler, unknown_var66, "\t\t");

			long long unknown_var67 = 0;
			Read<long long>("unknown", handler, unknown_var67, "\t\t");
		}

		void ParseMountData_v13(PacketHandler& handler, Maple::Game::MountData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("rideMode", handler, blockOutput.RideMode, "\t\t");

			ValidateValues(stream, "rideMode", "\t\t", blockOutput.RideMode, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			Read<int>("mountId", handler, blockOutput.MountId, "\t\t");
			Read<int>("mountObjectId", handler, blockOutput.MountObjectId, "\t\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var3, (unsigned char)0);

			if (blockOutput.RideMode == (Enum::RideMode)1)
			{
				Read<int>("itemId", handler, blockOutput.ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t\t");
				ParseItemUgc_v12(handler, blockOutput.Ugc);
			}

			if (blockOutput.RideMode == (Enum::RideMode)2)
			{
				Read<int>("effectId", handler, blockOutput.EffectId, "\t\t\t");
				Read<short>("effectLevel", handler, blockOutput.EffectLevel, "\t\t\t");
			}

			unsigned char count_var8 = 0;
			Read<unsigned char>("count", handler, count_var8, "\t\t");

			ResizeVector(handler, blockOutput.UnknownData, count_var8);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				int unknown_var9 = 0;
				Read<int>("unknown", handler, unknown_var9, "\t\t\t");

				unsigned char unknown_var10 = 0;
				Read<unsigned char>("unknown", handler, unknown_var10, "\t\t\t");
			}
		}

		void ParseItemBadge_v2486(PacketHandler& handler, Maple::Game::ItemBadge& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var0, (unsigned char)1);

			Read<unsigned char>("type", handler, blockOutput.Type, "\t\t");

			ValidateValues(stream, "type", "\t\t", blockOutput.Type, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			Read<int>("id", handler, blockOutput.BadgeId, "\t\t");

			if (blockOutput.Type == (Enum::BadgeType)1)
			{
				ParseItemBadgeTransparency_v12(handler, blockOutput);
			}

			if (blockOutput.Type == (Enum::BadgeType)11)
			{
				Read<int>("petSkinId", handler, blockOutput.PetSkinId, "\t\t\t");
			}
		}

		void ParseItemData_v2486(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			ParseItemHeader_v12(handler, blockOutput);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Constant);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Static);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Random);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Title);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment1);
			}
			ParseItemEnchantment_v12(handler, blockOutput.Enchantment);

			{

				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var4 = 0;
					Read<int>("statCount", handler, statCount_var4, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var4, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var5 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var5 = handler.GetItemExtraDataType(itemId_param0);
			}

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var5, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var5 == 1)
			{
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var5 == 2)
			{
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var5 == 3)
			{
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var5 == 4)
			{
				ParseItemBadge_v2486(handler, blockOutput.Badge);
			}
			ParseItemTransfer_v12(handler, blockOutput.ItemTransfer);
			ParseItemSocket_v12(handler, blockOutput.ItemSocket);
			ParseItemCouple_v12(handler, blockOutput.ItemCouple);
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		void ParseEquipmentData_v2486(PacketHandler& handler, Maple::Game::EquipmentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("slot", handler, blockOutput.Slot, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
			ParseItemData_v2486(handler, blockOutput.Data, (unsigned int)blockOutput.ItemId);
		}

		void ParseCharacterEquipmentItems_v2486(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v2486(handler, blockOutput.Equipment[i]);
			}
		}

		void ParseCharacterEquipmentBadges_v2486(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot, "\t\t\t");
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, blockOutput.Badges[i].Data, (unsigned int)blockOutput.Badges[i].ItemId);
			}
		}

		void ParseCharacterEquipmentSkins_v2486(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2486(handler, blockOutput.Skins[i]);
				}
			}
		}

		void ParseCharacterEquipmentFashion_v2486(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFashion", handler, blockOutput.HasFashion, "\t\t");

			ValidateValues(stream, "hasFashion", "\t\t", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2486(handler, blockOutput.Fashion[i]);
				}
			}
		}

		void ParseCharacterEquipmentSkinsMandatory_v2486(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			long long unknown_var1 = 0;
			Read<long long>("unknown", handler, unknown_var1, "\t\t");

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2, "\t\t");

			unsigned char skinCount_var3 = 0;
			Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t");

			ResizeVector(handler, blockOutput.Skins, skinCount_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v2486(handler, blockOutput.Skins[i]);
			}
		}

		void ParseCharacterListEntry_v2486(PacketHandler& handler, Maple::Game::CharacterListEntry& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime, "\t\t");
			ParseCharacterEquipmentItems_v2486(handler, blockOutput.Equipment);
			ParseCharacterEquipmentBadges_v2486(handler, blockOutput.Equipment);
			ParseCharacterEquipmentSkins_v2486(handler, blockOutput.Equipment);
		}

		void ParseMailAttachData_v2486(PacketHandler& handler, Maple::Game::MailAttachData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("index", handler, blockOutput.Index, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7, "\t\t");
			ParseItemData_v2486(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseMailData_v2486(PacketHandler& handler, Maple::Game::MailData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("type", handler, blockOutput.Type, "\t\t");

			ValidateValues(stream, "type", "\t\t", blockOutput.Type, (unsigned char)1, (unsigned char)101, (unsigned char)102, (unsigned char)200, (unsigned char)104, (unsigned char)107);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId, "\t\t");
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId, "\t\t");
			Read<std::wstring>("senderName", handler, blockOutput.SenderName, "\t\t");
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle, "\t\t");
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent, "\t\t");
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey, "\t\t");
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue, "\t\t");

			if (blockOutput.Type == 200)
			{
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8, "\t\t\t");

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10, "\t\t\t");

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11, "\t\t\t");
			}

			else
			{
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12, "\t\t\t");

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAttachData_v2486(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos, "\t\t");
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp, "\t\t");
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets, "\t\t");

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16, "\t\t");
			Read<long long>("redMerets", handler, blockOutput.RedMerets, "\t\t");

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18, "\t\t");

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19, "\t\t");

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20, "\t\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t\t");

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22, "\t\t\t");

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23, "\t\t\t");
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");
			Read<long long>("sentTime", handler, blockOutput.SentTime, "\t\t");

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27, "\t\t");
		}

		void ParseBlackMarketEntryData_v2486(PacketHandler& handler, Maple::Game::BlackMarketEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId, "\t\t");
			Read<long long>("timeListed", handler, blockOutput.TimeListed, "\t\t");
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2, "\t\t");
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires, "\t\t");
			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem, "\t\t");

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId, "\t\t");
			ParseItemData_v2486(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseFieldPetData_v2486(PacketHandler& handler, Maple::Game::FieldPetData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet, "\t\t");

			ValidateValues(stream, "hasFieldPet", "\t\t", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				Read<int>("itemId", handler, blockOutput.ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
			}
		}

		void ParseSkillTreeData_v2493(PacketHandler& handler, Maple::Game::SkillTreeData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("job", handler, blockOutput.Job, "\t\t");

			unsigned char unknownCount_var1 = 0;
			Read<unsigned char>("unknownCount", handler, unknownCount_var1, "\t\t");

			ValidateValues(stream, "unknownCount", "\t\t", unknownCount_var1, (unsigned char)1);

			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			ParseSkillTreePageData_v12(handler, blockOutput.Active);
		}

		void ParseBasicStat_v2497(PacketHandler& handler, Maple::Game::BasicStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");
		}

		void ParseSpecialStat_v2497(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");

			bool dummy_var2 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				dummy_var2 = handler.StatIntToFloat(blockOutput.Value);
			}

			ValidateValues(stream, "dummy", "\t\t", dummy_var2, (bool)0, (bool)1);
		}

		void ParseBasicAndSpecialStats_v2497(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseBasicStat_v2497(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseSpecialStat_v2497(handler, blockOutput.Special[i]);
			}

			Read<int>("empowermentItemId", handler, blockOutput.EmpowermentItemId, "\t\t");
		}

		void ParseItemData_v2497(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			ParseItemHeader_v12(handler, blockOutput);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Static);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Random);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Empowerment1);
			}

			{
				ParseItemEnchantmentHeader_v12(handler, blockOutput.Enchantment);

				unsigned char basicStatCount_var3 = 0;
				Read<unsigned char>("basicStatCount", handler, basicStatCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Enchantment.Basic, basicStatCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < basicStatCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("type", handler, blockOutput.Enchantment.Basic[i].Type, "\t\t\t\t");
					Read<int>("value", handler, blockOutput.Enchantment.Basic[i].Value, "\t\t\t\t");
				}
			}

			{
				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var7 = 0;
					Read<int>("statCount", handler, statCount_var7, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var7);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v2497(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var7, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var7);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v2497(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var8 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var8 = handler.GetItemExtraDataType(itemId_param0);
			}

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var8 == 1)
			{
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var8 == 2)
			{
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var8 == 3)
			{
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var8 == 4)
			{
				ParseItemBadge_v2486(handler, blockOutput.Badge);
			}
			ParseItemTransfer_v12(handler, blockOutput.ItemTransfer);
			ParseItemSocket_v12(handler, blockOutput.ItemSocket);
			ParseItemCouple_v12(handler, blockOutput.ItemCouple);
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		void ParseEquipmentData_v2497(PacketHandler& handler, Maple::Game::EquipmentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("slot", handler, blockOutput.Slot, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
			ParseItemData_v2497(handler, blockOutput.Data, (unsigned int)blockOutput.ItemId);
		}

		void ParseCharacterEquipmentItems_v2497(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v2497(handler, blockOutput.Equipment[i]);
			}
		}

		void ParseCharacterEquipmentBadges_v2497(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot, "\t\t\t");
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, blockOutput.Badges[i].Data, (unsigned int)blockOutput.Badges[i].ItemId);
			}
		}

		void ParseCharacterEquipmentSkins_v2497(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2497(handler, blockOutput.Skins[i]);
				}
			}
		}

		void ParseCharacterEquipmentFashion_v2497(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFashion", handler, blockOutput.HasFashion, "\t\t");

			ValidateValues(stream, "hasFashion", "\t\t", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2497(handler, blockOutput.Fashion[i]);
				}
			}
		}

		void ParseCharacterListEntry_v2497(PacketHandler& handler, Maple::Game::CharacterListEntry& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime, "\t\t");
			ParseCharacterEquipmentItems_v2497(handler, blockOutput.Equipment);
			ParseCharacterEquipmentBadges_v2497(handler, blockOutput.Equipment);
			ParseCharacterEquipmentSkins_v2497(handler, blockOutput.Equipment);
		}

		void ParseCharacterDetailsSpecialStats_v2497(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			int specialStatCount_var0 = 0;
			Read<int>("specialStatCount", handler, specialStatCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<short>("type", handler, blockOutput.Special[i].Type, "\t\t\t");
				Read<int>("value", handler, blockOutput.Special[i].Value, "\t\t\t");

				bool dummy_var3 = false;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					dummy_var3 = handler.StatIntToFloat(blockOutput.Special[i].Value);
				}

				ValidateValues(stream, "dummy", "\t\t\t", dummy_var3, (bool)0, (bool)1);
			}
		}

		void ParseMailAttachData_v2497(PacketHandler& handler, Maple::Game::MailAttachData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("index", handler, blockOutput.Index, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t\t");

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7, "\t\t");
			ParseItemData_v2497(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseMailData_v2497(PacketHandler& handler, Maple::Game::MailData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<unsigned char>("type", handler, blockOutput.Type, "\t\t");

			ValidateValues(stream, "type", "\t\t", blockOutput.Type, (unsigned char)1, (unsigned char)101, (unsigned char)102, (unsigned char)200, (unsigned char)104, (unsigned char)107);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId, "\t\t");
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId, "\t\t");
			Read<std::wstring>("senderName", handler, blockOutput.SenderName, "\t\t");
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle, "\t\t");
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent, "\t\t");
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey, "\t\t");
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue, "\t\t");

			if (blockOutput.Type == 200)
			{
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8, "\t\t\t");

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10, "\t\t\t");

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11, "\t\t\t");
			}

			else
			{
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12, "\t\t\t");

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailAttachData_v2497(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos, "\t\t");
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp, "\t\t");
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets, "\t\t");

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16, "\t\t");
			Read<long long>("redMerets", handler, blockOutput.RedMerets, "\t\t");

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18, "\t\t");

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19, "\t\t");

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20, "\t\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t\t");

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22, "\t\t\t");

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23, "\t\t\t");
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");
			Read<long long>("sentTime", handler, blockOutput.SentTime, "\t\t");

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27, "\t\t");
		}

		void ParseBlackMarketEntryData_v2497(PacketHandler& handler, Maple::Game::BlackMarketEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId, "\t\t");
			Read<long long>("timeListed", handler, blockOutput.TimeListed, "\t\t");
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2, "\t\t");
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires, "\t\t");
			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t\t");
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem, "\t\t");

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<unsigned char>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId, "\t\t");
			ParseItemData_v2497(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
		}

		void ParseFieldPetData_v2497(PacketHandler& handler, Maple::Game::FieldPetData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet, "\t\t");

			ValidateValues(stream, "hasFieldPet", "\t\t", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				Read<int>("itemId", handler, blockOutput.ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, blockOutput.ItemData, (unsigned int)blockOutput.ItemId);
			}
		}

		void ParseEquipmentData_v2509(PacketHandler& handler, Maple::Game::EquipmentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("itemId", handler, blockOutput.ItemId, "\t\t");
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId, "\t\t");
			Read<unsigned char>("slot", handler, blockOutput.Slot, "\t\t");
			Read<int>("rarity", handler, blockOutput.Rarity, "\t\t");

			ValidateValues(stream, "rarity", "\t\t", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
			ParseItemData_v2497(handler, blockOutput.Data, (unsigned int)blockOutput.ItemId);
		}

		void ParseCharacterEquipmentItems_v2509(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				ParseEquipmentData_v2509(handler, blockOutput.Equipment[i]);
			}
		}

		void ParseCharacterEquipmentBadges_v2509(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot, "\t\t\t");
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId, "\t\t\t");
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId, "\t\t\t");
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity, "\t\t\t");

				ValidateValues(stream, "rarity", "\t\t\t", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, blockOutput.Badges[i].Data, (unsigned int)blockOutput.Badges[i].ItemId);
			}
		}

		void ParseCharacterEquipmentSkins_v2509(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasSkin", handler, blockOutput.HasSkin, "\t\t");

			ValidateValues(stream, "hasSkin", "\t\t", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2509(handler, blockOutput.Skins[i]);
				}
			}
		}

		void ParseCharacterEquipmentFashion_v2509(PacketHandler& handler, Maple::Game::CharacterEquipment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<bool>("hasFashion", handler, blockOutput.HasFashion, "\t\t");

			ValidateValues(stream, "hasFashion", "\t\t", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1, "\t\t\t");

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2, "\t\t\t");

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3, "\t\t\t");

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseEquipmentData_v2509(handler, blockOutput.Fashion[i]);
				}
			}
		}

		void ParseCharacterListEntry_v2509(PacketHandler& handler, Maple::Game::CharacterListEntry& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl, "\t\t");
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime, "\t\t");
			ParseCharacterEquipmentItems_v2509(handler, blockOutput.Equipment);
			ParseCharacterEquipmentBadges_v2509(handler, blockOutput.Equipment);
			ParseCharacterEquipmentSkins_v2509(handler, blockOutput.Equipment);
		}

		void ParseCharacterDetailsBasicStats_v2509(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("max", handler, blockOutput.Basic[i].Max, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("base", handler, blockOutput.Basic[i].Base, "\t\t\t");
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("current", handler, blockOutput.Basic[i].Current, "\t\t\t");
			}
		}

		void ParseSkillTreePageData_v2509(PacketHandler& handler, Maple::Game::SkillTreePageData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0, "\t\t");

			ResizeVector(handler, blockOutput.Skills, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("skillId", handler, blockOutput.Skills[i].SkillId, "\t\t\t");
				Read<int>("skillLevel", handler, blockOutput.Skills[i].SkillLevel, "\t\t\t");
				Read<bool>("beginnerSkill", handler, blockOutput.Skills[i].BeginnerSkill, "\t\t\t");

				ValidateValues(stream, "beginnerSkill", "\t\t\t", blockOutput.Skills[i].BeginnerSkill, (bool)0, (bool)1);

				Read<bool>("enabled", handler, blockOutput.Skills[i].Enabled, "\t\t\t");

				ValidateValues(stream, "enabled", "\t\t\t", blockOutput.Skills[i].Enabled, (bool)0, (bool)1);

				Read<bool>("notify", handler, blockOutput.Skills[i].Notify, "\t\t\t");

				ValidateValues(stream, "notify", "\t\t\t", blockOutput.Skills[i].Notify, (bool)0, (bool)1);
			}
		}

		void ParseSkillTreeData_v2509(PacketHandler& handler, Maple::Game::SkillTreeData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Read<int>("jobTier", handler, blockOutput.JobTier, "\t\t");
			Read<int>("jobCode", handler, blockOutput.JobCode, "\t\t");
			ParseSkillTreePageData_v2509(handler, blockOutput.Active);
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", handler, output0.Version, "\t");
			Read<unsigned short>("feature", handler, output0.Feature, "\t");
			Read<unsigned short>("locale", handler, output0.Locale, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::ResponseVersionPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::ResponseHeartbeatPacket output0;

			Read<int>("serverTick", handler, output0.ServerTick, "\t");
			Read<int>("clientTick", handler, output0.ClientTick, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::ResponseHeartbeatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x2>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::HandshakePacket output0;

			Read<unsigned char>("function", handler, output0.Function, "\t");

			int count_var1 = 0;
			Read<int>("count", handler, count_var1, "\t");

			ResizeVector(handler, output0.Data, count_var1);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<std::wstring>("unknown", handler, output0.Data[i].String, "\t\t");

				long long unknown_var3 = 0;
				Read<long long>("unknown", handler, unknown_var3, "\t\t");
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::HandshakePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				Client::LogInPacket output0;

				Read<std::wstring>("username", handler, output0.Username, "\t\t");
				Read<std::wstring>("password", handler, output0.Password, "\t\t");

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3, "\t\t");
				Read<unsigned long long>("machineLow", handler, output0.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh, "\t\t");

				int unknownMachineIdPtr_var6 = 0;
				Read<int>("unknownMachineIdPtr", handler, unknownMachineIdPtr_var6, "\t\t");
				Read<int>("sessionKey", handler, output0.SessionKey, "\t\t");
				Read<std::string>("locale", handler, output0.Locale, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::LogInPacket>(output0);
				}


				return;
			}

			if (mode_var0 != 0)
			{
				Client::LogInAuthTokenPacket output1;

				long long unknown_var9 = 0;
				Read<long long>("unknown", handler, unknown_var9, "\t\t");

				std::string authToken_var10;
				Read<std::string>("authToken", handler, authToken_var10, "\t\t");

				short unknown_var11 = 0;
				Read<short>("unknown", handler, unknown_var11, "\t\t");

				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12, "\t\t");
				Read<unsigned long long>("machineLow", handler, output1.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output1.MachineHigh, "\t\t");

				int unknown_var15 = 0;
				Read<int>("unknown", handler, unknown_var15, "\t\t");

				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t");
				Read<std::string>("locale", handler, output1.Locale, "\t\t");

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::LogInAuthTokenPacket>(output1);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::ResponseKeyPacket output0;

			Read<long long>("accountId", handler, output0.AccountId, "\t");

			if (output0.AccountId != (Enum::AccountId)0)
			{
				Read<int>("tokenA", handler, output0.TokenA, "\t\t");
				Read<int>("tokenB", handler, output0.TokenB, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh, "\t\t");
				Read<unsigned long long>("machineLow", handler, output0.MachineLow, "\t\t");
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::ResponseKeyPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::RequestQuitPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::RequestQuitPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x5>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::ReconnectPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1);

			Read<long long>("accountId", handler, output0.AccountId, "\t");
			Read<long long>("characterId", handler, output0.CharacterId, "\t");

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3, "\t");

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4, "\t");

			std::wstring unknown_var5;
			Read<std::wstring>("unknown", handler, unknown_var5, "\t");

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6, "\t");

			std::string unknown_var7;
			Read<std::string>("unknown", handler, unknown_var7, "\t");

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::ReconnectPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output0.ServerTick, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t");
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				Read<bool>("flag", handler, output0.Flag, "\t\t");

				ValidateValues(stream, "flag", "\t\t", output0.Flag, (bool)0, (bool)1);

				if (output0.Flag)
				{
					int unknown_var14 = 0;
					Read<int>("unknown", handler, unknown_var14, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);

					std::string unknown_var15;
					Read<std::string>("unknown", handler, unknown_var15, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var16 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var16, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var16, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var16 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", handler, output1.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", handler, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output1.Rotation, "\t\t\t");

					unsigned char count_var21 = 0;
					Read<unsigned char>("count", handler, count_var21, "\t\t\t");

					int unknown_var22 = 0;
					Read<int>("unknown", handler, unknown_var22, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var22, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var21);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char projectile_i = 0; projectile_i < count_var21 && !handler.PacketStream().HasRecentlyFailed; ++projectile_i)
					{
						auto& projectile_array0 = output1.Projectiles[projectile_i];

						Read<long long>("skillAttack", handler, projectile_array0.SkillAttack, "\t\t\t\t");
						Read<int>("targetId", handler, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var26 = false;
						Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

						size_t nextTarget_j = 0;

						while (moreTargets_var26 && !handler.PacketStream().HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							if (handler.PacketStream().HasRecentlyFailed)
							{
								return;
							}

							auto& nextTarget_array1 = projectile_array0.ChainTargets[nextTarget_j];

							Read<long long>("skillAttack", handler, nextTarget_array1.SkillAttack, "\t\t\t\t\t");
							Read<int>("targetId", handler, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var30 = 0;
							Read<unsigned char>("unknown", handler, unknown_var30, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

							++nextTarget_j;
						}
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);
					}


					return;
				}

				if (damageMode_var16 == 1)
				{
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", handler, output2.SkillSn, "\t\t\t");
					Read<long long>("skillAttack", handler, output2.SkillAttack, "\t\t\t");
					Read<Vector3S>("position", handler, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", handler, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", handler, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint, "\t\t\t");

					unsigned char count_var37 = 0;
					Read<unsigned char>("count", handler, count_var37, "\t\t\t");

					int unknown_var38 = 0;
					Read<int>("unknown", handler, unknown_var38, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var38, (int)0);

					ResizeVector(handler, output2.Hits, count_var37);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char hitActor_i = 0; hitActor_i < count_var37 && !handler.PacketStream().HasRecentlyFailed; ++hitActor_i)
					{
						auto& hitActor_array2 = output2.Hits[hitActor_i];

						Read<int>("entityId", handler, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var40 = 0;
						Read<unsigned char>("unknown", handler, unknown_var40, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var40, (unsigned char)0);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);
					}


					return;
				}

				if (damageMode_var16 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", handler, output3.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output3.AttackPoint, "\t\t\t");

					int unknown_var43 = 0;
					Read<int>("unknown", handler, unknown_var43, "\t\t\t");
					Read<int>("attackCounter", handler, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", handler, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output3.Rotation, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn, "\t\t");
				Read<unsigned int>("skillId", handler, output4.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output4.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", handler, output4.Position, "\t\t");

				Vector3S unknown_var52;
				Read<Vector3S>("unknown", handler, unknown_var52, "\t\t");
				Read<Vector3S>("rotation", handler, output4.Rotation, "\t\t");

				Vector3S unknown_var54;
				Read<Vector3S>("unknown", handler, unknown_var54, "\t\t");

				bool unknown_var55 = false;
				Read<bool>("unknown", handler, unknown_var55, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var55, (bool)0, (bool)1);

				int unknown_var56 = 0;
				Read<int>("unknown", handler, unknown_var56, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var56, (int)0);

				unsigned char unknown_var57 = 0;
				Read<unsigned char>("unknown", handler, unknown_var57, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var57, (unsigned char)0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x21>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0);

			if (mode_var0 == 0)
			{
				Client::StateSkillPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<unsigned int>("serverTick", handler, output0.ServerTick, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t");

				ValidateValues(stream, "skillLevel", "\t\t", output0.SkillLevel, (unsigned short)1);

				Read<int>("animation", handler, output0.Animation, "\t\t");
				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				long long unknown_var7 = 0;
				Read<long long>("unknown", handler, unknown_var7, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::StateSkillPacket>(output0);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Client::NpcTalkClosePacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkClosePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Client::NpcTalkBeginPacket output1;

				Read<int>("actorId", handler, output1.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkBeginPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Client::NpcTalkContinuePacket output2;

				Read<int>("index", handler, output2.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Client::NpcTalkEnchantUnknownPacket output3;

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantUnknownPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Client::NpcTalkEnchantPacket output4;

				Read<int>("npcId", handler, output4.NpcId, "\t\t");
				Read<int>("scriptId", handler, output4.ScriptId, "\t\t");
				Read<short>("eventType", handler, output4.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output4.EventType, (short)1, (short)202, (short)2, (short)3);

				if (output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)1)
				{
					Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t\t");
				}

				if (output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)202)
				{
					short unknown_var8 = 0;
					Read<short>("unknown", handler, unknown_var8, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Client::NpcTalkNextQuestPacket output5;

				Read<int>("questId", handler, output5.QuestId, "\t\t");
				Read<short>("eventType", handler, output5.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output5.EventType, (short)0, (short)2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkNextQuestPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Client::NpcTalkAllianceQuestAcceptPacket output6;

				Read<int>("index", handler, output6.Index, "\t\t");
				Read<short>("eventType", handler, output6.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output6.EventType, (short)0, (short)2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Client::NpcTalkAllianceQuestTalkPacket output7;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Client::NpcTalkCinematicPacket output8;

				Read<int>("actorId", handler, output8.ActorId, "\t\t");
				Read<int>("index", handler, output8.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkCinematicPacket>(output8);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Client::SystemInfoPacket output0;

			Read<std::wstring>("info", handler, output0.Info, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::SystemInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldRemoveNpcPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveNpcPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v12(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					ParseAllStatsOtherPlayers_v12(handler, output0.Stats);
				}

				if (statCount_var4 != 35)
				{
					ParseSpecificStats_v12(handler, output0.Stats, statCount_var4);
				}
			}

			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7, "\t");

			Color4I_BGRA skinColorPrimary_var8;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var8, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var8;

			Color4I_BGRA skinColorSecondary_var9;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var9, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var9;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v12(handler, output0.Mount);
			}

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var16 = false;
			Read<bool>("isDeflated", handler, isDeflated_var16, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var16, (bool)0, (bool)1);

			int bufferSize_var17 = 0;
			Read<int>("bufferSize", handler, bufferSize_var17, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var16, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var16, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var17, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentFashion_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var16, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var16, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var17, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentBadges_v12(handler, output0.Equipment);
			}

			short effectCount_var18 = 0;
			Read<short>("effectCount", handler, effectCount_var18, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var18);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var18 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var24 = 0;
			Read<int>("unknown", handler, unknown_var24, "\t");

			int unknown_var25 = 0;
			Read<int>("unknown", handler, unknown_var25, "\t");

			unsigned char unknown_var26 = 0;
			Read<unsigned char>("unknown", handler, unknown_var26, "\t");

			int unknown_var27 = 0;
			Read<int>("unknown", handler, unknown_var27, "\t");

			unsigned char unknown_var28 = 0;
			Read<unsigned char>("unknown", handler, unknown_var28, "\t");

			unsigned char unknown_var29 = 0;
			Read<unsigned char>("unknown", handler, unknown_var29, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var39 = 0;
			Read<int>("unknown", handler, unknown_var39, "\t");

			unsigned char unknown_var40 = 0;
			Read<unsigned char>("unknown", handler, unknown_var40, "\t");

			int mushkingTailKillCount_var41 = 0;
			Read<int>("mushkingTailKillCount", handler, mushkingTailKillCount_var41, "\t");

			int unknownCount_var42 = 0;
			Read<int>("unknownCount", handler, unknownCount_var42, "\t");

			ResizeVector(handler, output0.UnknownData, unknownCount_var42);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var42 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				int unknown_var43 = 0;
				Read<int>("unknown", handler, unknown_var43, "\t\t");

				std::wstring unknown_var44;
				Read<std::wstring>("unknown", handler, unknown_var44, "\t\t");
			}

			short unknown_var45 = 0;
			Read<short>("unknown", handler, unknown_var45, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::Reconnect7Packet output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::Reconnect7Packet>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x4c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId, "\t\t");
				Read<unsigned char>("flags", handler, output1.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5, "\t\t");

				ValidateValues(stream, "actionMode", "\t\t", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6, "\t\t\t");
				}

				if (actionMode_var5 == 3)
				{
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8, "\t\t\t");

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10, "\t\t\t");

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t\t");
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t\t");

						ValidateValues(stream, "rarity", "\t\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount, "\t\t\t\t");
						ParseItemData_v12(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardItemPacket>(output5);
					}


					return;
				}

				if (actionMode_var5 == 6)
				{
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
				}
				if (actionMode_var5 == 10)
				{
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17, "\t\t\t");

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::NpcTalkUpdatePacket output10;
				ParseScriptContent_v12(handler, output10.ScriptContent);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkUpdatePacket>(output10);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags, "\t\t");

				ValidateValues(stream, "flags", "\t\t", output11.Flags, (unsigned char)255);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20, "\t\t");
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output12.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseCharacterListEntry_v12(handler, output0.Characters[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::CharacterListAddPacket output1;
				ParseCharacterListEntry_v12(handler, output1.Character);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("characterId", handler, output2.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
			}
			if (mode_var0 == 4)
			{
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");
			}

			if (mode_var0 == 5)
			{
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId, "\t\t");
				Read<int>("messageId", handler, output3.MessageId, "\t\t");
				Read<long long>("deleteTime", handler, output3.DeleteTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");
				Read<int>("messageId", handler, output4.MessageId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xdd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4, "\t\t");

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId, "\t\t\t");

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v12(handler, output2.Items[i].ItemData, (unsigned int)itemId_var6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockUpdateItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::UserChatPacket output0;

			Read<long long>("accountId", handler, output0.AccountId, "\t");
			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<std::wstring>("characterName", handler, output0.CharacterName, "\t");

			bool useStringId_var3 = false;
			Read<bool>("useStringId", handler, useStringId_var3, "\t");

			ValidateValues(stream, "useStringId", "\t", useStringId_var3, (bool)0, (bool)1);

			if (useStringId_var3)
			{
				Read<int>("stringId", handler, output0.StringId, "\t\t");
			}

			else
			{
				Read<std::wstring>("message", handler, output0.Message, "\t\t");
			}
			Read<int>("type", handler, output0.Type, "\t");

			ValidateValues(stream, "type", "\t", output0.Type, (int)8, (int)0, (int)3, (int)4, (int)5, (int)6, (int)7, (int)9, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)18, (int)19, (int)20, (int)23);

			bool unknown_var7 = false;
			Read<bool>("unknown", handler, unknown_var7, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var7, (bool)0, (bool)1);

			Read<int>("channelId", handler, output0.ChannelId, "\t");

			if (output0.Type == (Server::UserChatPacket::TypeEnum)3)
			{
				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9, "\t\t");
			}

			if (output0.Type == (Server::UserChatPacket::TypeEnum)16)
			{
				Read<int>("superChatId", handler, output0.SuperChatId, "\t\t");
			}

			if (output0.Type == (Server::UserChatPacket::TypeEnum)20)
			{
				Read<long long>("clubId", handler, output0.ClubId, "\t\t");
			}

			unsigned char unknown_var12 = 0;
			Read<unsigned char>("unknown", handler, unknown_var12, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x55>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailData_v12(handler, output0.Mail[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output2.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId, "\t\t");

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7, "\t\t");

				ValidateValues(stream, "unknownCondition", "\t\t", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output5.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12, "\t\t");

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount, "\t\t");
				Read<bool>("alert", handler, output7.Alert, "\t\t");

				ValidateValues(stream, "alert", "\t\t", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18, "\t\t");
				Read<unsigned char>("message", handler, output11.Message, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20, "\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23, "\t\t");

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24, "\t\t");

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25, "\t\t");

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceiveGiftNotificationPacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x15>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ServerEnterPacket output0;

			Read<int>("playerActorId", handler, output0.PlayerActorId, "\t");
			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<short>("channelId", handler, output0.ChannelId, "\t");
			Read<long long>("exp", handler, output0.Exp, "\t");
			Read<long long>("restExp", handler, output0.RestExp, "\t");
			Read<long long>("mesos", handler, output0.Mesos, "\t");
			Read<long long>("totalMerets", handler, output0.TotalMerets, "\t");
			Read<long long>("merets", handler, output0.Merets, "\t");
			Read<long long>("totalGameMerets", handler, output0.TotalGameMerets, "\t");
			Read<long long>("gameMerets", handler, output0.GameMerets, "\t");
			Read<long long>("eventMerets", handler, output0.EventMerets, "\t");
			Read<long long>("valorTokens", handler, output0.ValorTokens, "\t");
			Read<long long>("treva", handler, output0.Treva, "\t");
			Read<long long>("rue", handler, output0.Rue, "\t");
			Read<long long>("haviFruit", handler, output0.HaviFruit, "\t");
			Read<long long>("reverseCoin", handler, output0.ReverseCoin, "\t");
			Read<long long>("mentorToken", handler, output0.MentorToken, "\t");
			Read<long long>("menteeToken", handler, output0.MenteeToken, "\t");
			Read<long long>("starPoint", handler, output0.StarPoint, "\t");
			Read<long long>("mesoToken", handler, output0.MesoToken, "\t");
			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21, "\t");

			unsigned char unknown_var22 = 0;
			Read<unsigned char>("unknown", handler, unknown_var22, "\t");

			unsigned short unlockedMaps_var23 = 0;
			Read<unsigned short>("unlockedMaps", handler, unlockedMaps_var23, "\t");

			ResizeVector(handler, output0.UnlockedMaps, unlockedMaps_var23);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedMaps_var23 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("mapId", handler, output0.UnlockedMaps[i].MapId, "\t\t");
			}

			unsigned short unlockedTaxis_var25 = 0;
			Read<unsigned short>("unlockedTaxis", handler, unlockedTaxis_var25, "\t");

			ResizeVector(handler, output0.UnlockedTaxis, unlockedTaxis_var25);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedTaxis_var25 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("mapId", handler, output0.UnlockedTaxis[i].MapId, "\t\t");
			}

			long long unknown_var27 = 0;
			Read<long long>("unknown", handler, unknown_var27, "\t");

			std::wstring unknown_var28;
			Read<std::wstring>("unknown", handler, unknown_var28, "\t");
			Read<std::wstring>("mapleNewsUrl", handler, output0.MapleNewsUrl, "\t");

			std::wstring unknown_var30;
			Read<std::wstring>("unknown", handler, unknown_var30, "\t");

			std::wstring nxCacheUrl_var31;
			Read<std::wstring>("nxCacheUrl", handler, nxCacheUrl_var31, "\t");

			std::wstring unknown_var32;
			Read<std::wstring>("unknown", handler, unknown_var32, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ServerEnterPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0, "\t");

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t");
				Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t");
				Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatItemLinkPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddNpcPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("npcId", handler, output0.NpcId, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("rotation", handler, output0.Rotation, "\t");

			bool isBoss_var4 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				isBoss_var4 = handler.IsNpcBoss(output0.NpcId);
			}

			ValidateValues(stream, "isBoss", "\t", isBoss_var4, (bool)0, (bool)1);

			if (isBoss_var4)
			{
				Read<std::string>("kfmName", handler, output0.KfmName, "\t\t");
			}

			unsigned char defaultStatsMode_var6 = 0;
			Read<unsigned char>("defaultStatsMode", handler, defaultStatsMode_var6, "\t");

			ValidateValues(stream, "defaultStatsMode", "\t", defaultStatsMode_var6, (unsigned char)35);

			if (defaultStatsMode_var6 == 35)
			{
				Read<unsigned long long>("hpMax", handler, output0.Hp.Max, "\t\t");
				Read<unsigned int>("attackSpeedMax", handler, output0.AttackSpeed.Max, "\t\t");
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base, "\t\t");
				Read<unsigned int>("attackSpeedBase", handler, output0.AttackSpeed.Base, "\t\t");
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current, "\t\t");
				Read<unsigned int>("attackSpeedCurrent", handler, output0.AttackSpeed.Current, "\t\t");
			}
			Read<bool>("isDead", handler, output0.IsDead, "\t");

			ValidateValues(stream, "isDead", "\t", output0.IsDead, (bool)0, (bool)1);

			unsigned short effectCount_var14 = 0;
			Read<unsigned short>("effectCount", handler, effectCount_var14, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var14);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < effectCount_var14 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}
			Read<long long>("petItemInstanceId", handler, output0.PetItemInstanceId, "\t");

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21, "\t");
			Read<short>("level", handler, output0.Level, "\t");

			short petTaming_var23 = 0;
			Read<short>("petTaming", handler, petTaming_var23, "\t");

			ValidateValues(stream, "petTaming", "\t", petTaming_var23, (short)0);

			int unknown_var24 = 0;
			Read<int>("unknown", handler, unknown_var24, "\t");

			if (isBoss_var4)
			{
				Read<std::wstring>("spawnEffect", handler, output0.SpawnEffect, "\t\t");

				int skillCount_var26 = 0;
				Read<int>("skillCount", handler, skillCount_var26, "\t\t");

				ResizeVector(handler, output0.Skills, skillCount_var26);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < skillCount_var26 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("skillId", handler, output0.Skills[i].SkillId, "\t\t\t");
					Read<short>("skillLevel", handler, output0.Skills[i].SkillLevel, "\t\t\t");
				}

				int unknown_var29 = 0;
				Read<int>("unknown", handler, unknown_var29, "\t\t");
			}

			bool hasHiddenHp_var30 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				hasHiddenHp_var30 = handler.NpcHasHiddenHp(output0.NpcId);
			}

			ValidateValues(stream, "hasHiddenHp", "\t", hasHiddenHp_var30, (bool)0, (bool)1);

			if (hasHiddenHp_var30)
			{
				Read<long long>("hiddenHpAdd", handler, output0.HiddenHpAdd, "\t\t");
			}

			bool unknownBool_var32 = false;
			Read<bool>("unknownBool", handler, unknownBool_var32, "\t");

			ValidateValues(stream, "unknownBool", "\t", unknownBool_var32, (bool)0, (bool)1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddNpcPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x16>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char message_var0 = 0;
			Read<unsigned char>("message", handler, message_var0, "\t");

			ValidateValues(stream, "message", "\t", message_var0, (unsigned char)0);

			if (message_var0 == 0)
			{
				Server::RequestFieldEnterPacket output0;

				Read<int>("mapId", handler, output0.MapId, "\t\t");

				unsigned char unknown_var2 = 0;
				Read<unsigned char>("unknown", handler, unknown_var2, "\t\t");

				unsigned char unknown_var3 = 0;
				Read<unsigned char>("unknown", handler, unknown_var3, "\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t");

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::RequestFieldEnterPacket>(output0);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldRemovePlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemovePlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x23>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot, "\t\t");
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output4.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output5.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::FurnishingStorageEndListPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageEndListPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x25>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<std::wstring>("slotName", handler, output0.SlotName, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab, "\t");
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x26>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemPutOffPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemPutOffPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x27>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<long long>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot, "\t");
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x28>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemSkinPutOffPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOffPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var2);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemUpdatePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");

			bool hasUid_var3 = false;
			Read<bool>("hasUid", handler, hasUid_var3, "\t");

			ValidateValues(stream, "hasUid", "\t", hasUid_var3, (bool)0, (bool)1);

			if (hasUid_var3)
			{
				Read<long long>("uid", handler, output0.ItemInstanceId, "\t\t");
			}
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<int>("ownerId", handler, output0.OwnerId, "\t");

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7, "\t");

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var10 = 0;
			Read<short>("unknown", handler, unknown_var10, "\t");

			bool unknown_var11 = false;
			Read<bool>("unknown", handler, unknown_var11, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var11, (bool)0, (bool)1);

			bool unknown_var12 = false;
			Read<bool>("unknown", handler, unknown_var12, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var12, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x6c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			if (mode_var0 == 0)
			{
				Server::LoadCubesPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var1, (unsigned char)0);

				int count_var2 = 0;
				Read<int>("count", handler, count_var2, "\t\t");

				ResizeVector(handler, output0.CubeData, count_var2);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var2 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<Vector3Byte>("position", handler, output0.CubeData[i].Position, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output0.CubeData[i].ItemInstanceId, "\t\t\t");
					ParseCubeItemData_v12(handler, output0.CubeData[i].Data);

					Read<int>("plotNumber", handler, output0.CubeData[i].PlotNumber, "\t\t\t");

					int unknown_var6 = 0;
					Read<int>("unknown", handler, unknown_var6, "\t\t\t");

					unsigned char unknown_var7 = 0;
					Read<unsigned char>("unknown", handler, unknown_var7, "\t\t\t");
					Read<float>("RotationZ", handler, output0.CubeData[i].RotationZ, "\t\t\t");

					int unknown_var9 = 0;
					Read<int>("unknown", handler, unknown_var9, "\t\t\t");

					bool hasExtraData_var10 = false;
					Read<bool>("hasExtraData", handler, hasExtraData_var10, "\t\t\t");

					ValidateValues(stream, "hasExtraData", "\t\t\t", hasExtraData_var10, (bool)0, (bool)1);

					if (hasExtraData_var10)
					{
						std::wstring unknown_var11;
						Read<std::wstring>("unknown", handler, unknown_var11, "\t\t\t\t");

						unsigned char unknown_var12 = 0;
						Read<unsigned char>("unknown", handler, unknown_var12, "\t\t\t\t");
					}
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::LoadCubesAvailabilityPacket output1;

				int count_var13 = 0;
				Read<int>("count", handler, count_var13, "\t\t");

				ResizeVector(handler, output1.AvailabilityData, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("plotId", handler, output1.AvailabilityData[i].PlotId, "\t\t\t");
					Read<bool>("isTaken", handler, output1.AvailabilityData[i].IsTaken, "\t\t\t");

					ValidateValues(stream, "isTaken", "\t\t\t", output1.AvailabilityData[i].IsTaken, (bool)0, (bool)1);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesAvailabilityPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::LoadCubesPlotsPacket output2;

				int count_var16 = 0;
				Read<int>("count", handler, count_var16, "\t\t");

				ResizeVector(handler, output2.PlotData, count_var16);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var16 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("plotId", handler, output2.PlotData[i].PlotId, "\t\t\t");
					Read<int>("apartmentNumber", handler, output2.PlotData[i].ApartmentNumber, "\t\t\t");
					Read<std::wstring>("plotName", handler, output2.PlotData[i].PlotName, "\t\t\t");
					Read<long long>("accountId", handler, output2.PlotData[i].AccountId, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesPlotsPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::LoadCubesExpirationPacket output3;

				int count_var21 = 0;
				Read<int>("count", handler, count_var21, "\t\t");

				ResizeVector(handler, output3.SaleStateData, count_var21);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var21 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("plotId", handler, output3.SaleStateData[i].PlotId, "\t\t\t");
					Read<int>("apartmentNumber", handler, output3.SaleStateData[i].ApartmentNumber, "\t\t\t");
					Read<unsigned char>("state", handler, output3.SaleStateData[i].State, "\t\t\t");

					ValidateValues(stream, "state", "\t\t\t", output3.SaleStateData[i].State, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

					Read<long long>("expirationTime", handler, output3.SaleStateData[i].ExpirationTime, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesExpirationPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldRemoveItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::StatPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");

			bool unknown_var1 = false;
			Read<bool>("unknown", handler, unknown_var1, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var1, (bool)0, (bool)1);

			unsigned char statCount_var2 = 0;
			Read<unsigned char>("statCount", handler, statCount_var2, "\t");

			unsigned char actorType_var3 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				actorType_var3 = handler.GetActorType(output0.ActorId);
			}

			ValidateValues(stream, "actorType", "\t", actorType_var3, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)255);

			if (actorType_var3 == 255)
			{
				handler.DiscardPacket();

				return;

			}

			if (statCount_var2 == 1)
			{
				unsigned char basicStatCount_var4 = 1;

				ResizeVector(handler, output0.Stats.Basic, basicStatCount_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				ParseSpecificStat_v12(handler, output0.Stats.Basic[0]);
			}

			else if (actorType_var3 == 3)
			{
				ParseAllStatsNpc_v12(handler, output0.Stats);
			}

			else if (actorType_var3 == 4)
			{
				ParseAllStatsNpc_v12(handler, output0.Stats);
			}

			else if (statCount_var2 == 35)
			{
				if (actorType_var3 == 1)
				{
					ParseAllStatsMyPlayer_v12(handler, output0.Stats);
				}

				else
				{
					ParseAllStatsOtherPlayers_v12(handler, output0.Stats);
				}
			}

			else if (statCount_var2 == 255)
			{
				unsigned char basicStatCount_var5 = 35;
				ParseSpecificStats_v12(handler, output0.Stats, basicStatCount_var5);
			}

			else
			{
				ParseSpecificStats_v12(handler, output0.Stats, statCount_var2);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::StatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x38>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ExpUpPacket output0;

			Read<bool>("isRestExp", handler, output0.IsRestExp, "\t");

			ValidateValues(stream, "isRestExp", "\t", output0.IsRestExp, (bool)0, (bool)1);

			if (output0.IsRestExp == 0)
			{
				Read<long long>("expGained", handler, output0.ExpGained, "\t\t");

				short unknown_var2 = 0;
				Read<short>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("totalExp", handler, output0.TotalExp, "\t\t");
				Read<long long>("restExp", handler, output0.RestExp, "\t\t");
				Read<int>("message", handler, output0.Message, "\t\t");
				Read<bool>("additional", handler, output0.Additional, "\t\t");

				ValidateValues(stream, "additional", "\t\t", output0.Additional, (bool)0, (bool)1);
			}

			if (output0.IsRestExp)
			{
				Read<long long>("restExp", handler, output0.RestExp, "\t\t");
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ExpUpPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x39>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::LevelUpPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("level", handler, output0.Level, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::LevelUpPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x105>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BindItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<bool>("isChaining", handler, output0.IsChaining, "\t\t");

				ValidateValues(stream, "isChaining", "\t\t", output0.IsChaining, (bool)0, (bool)1);

				Read<int>("serverTick", handler, output0.ServerTick, "\t\t");

				unsigned char count_var11 = 0;
				Read<unsigned char>("count", handler, count_var11, "\t\t");

				ResizeVector(handler, output0.Hits, count_var11);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var11 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					long long unknown_var12 = 0;
					Read<long long>("unknown", handler, unknown_var12, "\t\t\t");
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack, "\t\t\t");
					Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t");
					Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;
				ParseSkillDamagePacket_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<int>("damage", handler, output2.Damage, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;
				ParseSkillDamageHealPacket_v12(handler, output3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;
				ParseSkillDamageRegionPacket_v12(handler, output4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;
				ParseSkillDamageTilePacket_v12(handler, output5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				int unknown_var17 = 0;
				Read<int>("unknown", handler, unknown_var17, "\t\t");

				int count_var18 = 0;
				Read<int>("count", handler, count_var18, "\t\t");

				for (int i = 0; i < count_var18 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var20 = 0;
				Read<long long>("skillSn", handler, skillSn_var20, "\t\t");

				bool hasTarget_var21 = false;
				Read<bool>("hasTarget", handler, hasTarget_var21, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var21, (bool)0, (bool)1);

				if (hasTarget_var21)
				{
					unsigned int skillId_var22 = 0;
					Read<unsigned int>("skillId", handler, skillId_var22, "\t\t\t");

					unsigned short skillLevel_var23 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var23, "\t\t\t");

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24, "\t\t\t");

					int npcId_var25 = 0;
					Read<int>("npcId", handler, npcId_var25, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			Read<int>("targetId", handler, output0.Effect.TargetId, "\t");
			Read<int>("instanceId", handler, output0.Effect.InstanceId, "\t");
			Read<int>("sourceId", handler, output0.Effect.SourceId, "\t");

			if (output0.Mode == (Server::BuffPacket::ModeEnum)0)
			{
				ParseEffectStats_v12(handler, output0.Effect.Stats);

				Read<bool>("enabled", handler, output0.Effect.Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effect.Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth, "\t\t");
			}

			if (output0.Mode == (Server::BuffPacket::ModeEnum)2)
			{
				int flags_var6 = 0;
				Read<int>("flags", handler, flags_var6, "\t\t");

				output0.UpdateEffect = GetBit(flags_var6, 0);
				output0.UpdateShield = GetBit(flags_var6, 1);

				if (GetBit(flags_var6, 0) == 1)
				{
					ParseEffectStats_v12(handler, output0.Effect.Stats);

					Read<bool>("enabled", handler, output0.Effect.Enabled, "\t\t\t");

					ValidateValues(stream, "enabled", "\t\t\t", output0.Effect.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var6, 1) == 1)
				{
					Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth, "\t\t\t");
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xca>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesPreviewPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesAddPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ChangeAttributesScrollPreviewItemPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");

				int itemId_var6 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var6 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
				}

				if (itemId_var6 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)itemId_var6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesErrorPacket output3;

				bool unknown_var7 = false;
				Read<bool>("unknown", handler, unknown_var7, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var7, (bool)0, (bool)1);

				int message_var8 = 0;
				Read<int>("message", handler, message_var8, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var8, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x4a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::JobPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x52>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				Server::ShopOpenPacket output0;
				ParseShopData_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopOpenPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("entryId", handler, output1.Items[i].EntryId, "\t\t\t");
					Read<int>("itemId", handler, output1.Items[i].ItemId, "\t\t\t");
					ParseShopItemData_v12(handler, output1.Items[i]);
					ParseItemData_v12(handler, output1.Items[i].ItemData, (unsigned int)output1.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadItemsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId, "\t\t");
				Read<int>("buyCount", handler, output2.BuyCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId, "\t\t");
				Read<int>("buyCount", handler, output3.BuyCount, "\t\t");
				Read<int>("totalPrice", handler, output3.TotalPrice, "\t\t");
				Read<unsigned char>("fontColor", handler, output3.FontColor, "\t\t");
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage, "\t\t");

				ValidateValues(stream, "toGuildStorage", "\t\t", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ShopAddBuyBackPacket output5;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12, "\t\t");

				ResizeVector(handler, output5.Items, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId, "\t\t\t");
					Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t");
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price, "\t\t\t");
					ParseItemData_v12(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopAddBuyBackPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock, "\t\t");

				ValidateValues(stream, "restock", "\t\t", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var19, (int)0);

					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var20, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				short unknown_var21 = 0;
				Read<short>("unknown", handler, unknown_var21, "\t\t");
			}

			if (mode_var0 == 12)
			{
				Server::ShopLoadMeretItemPacket output8;

				short count_var22 = 0;
				Read<short>("count", handler, count_var22, "\t\t");

				ResizeVector(handler, output8.Items, count_var22);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMeretShopPremiumItemEntry_v12(handler, output8.Items[i].MeretItemEntry);

					unsigned char unknown_var23 = 0;
					Read<unsigned char>("unknown", handler, unknown_var23, "\t\t\t");

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24, "\t\t\t");

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				int npcId_var26 = 0;
				Read<int>("npcId", handler, npcId_var26, "\t\t");

				int shopId_var27 = 0;
				Read<int>("shopId", handler, shopId_var27, "\t\t");

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28, "\t\t");

				short unknown_var29 = 0;
				Read<short>("unknown", handler, unknown_var29, "\t\t");
			}

			if (mode_var0 == 14)
			{
				Server::ShopLoadNewPacket output9;

				short count_var30 = 0;
				Read<short>("count", handler, count_var30, "\t\t");

				ResizeVector(handler, output9.Items, count_var30);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output9.Items[i].ItemId, "\t\t\t");

					bool unknown_var32 = false;
					Read<bool>("unknown", handler, unknown_var32, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var32, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output9.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output9.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var34;
					Read<std::string>("unknown", handler, unknown_var34, "\t\t\t");

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35, "\t\t\t");

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36, "\t\t\t");
					Read<bool>("hasBuyPeriod", handler, output9.Items[i].HasBuyPeriod, "\t\t\t");

					ValidateValues(stream, "hasBuyPeriod", "\t\t\t", output9.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output9.Items[i].HasBuyPeriod)
					{
						ParseBuyPeriodData_v12(handler, output9.Items[i].BuyPeriod);
					}
					ParseItemData_v12(handler, output9.Items[i].ItemData, (unsigned int)output9.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::ShopErrorPacket output10;

				Read<int>("message", handler, output10.Message, "\t\t");

				unsigned char unknown_var39 = 0;
				Read<unsigned char>("unknown", handler, unknown_var39, "\t\t");
				Read<int>("stringId", handler, output10.StringId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPetPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("petSkinId", handler, output0.PetSkinId, "\t");
			Read<int>("petNpcId", handler, output0.PetNpcId, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("rotation", handler, output0.Rotation, "\t");
			Read<float>("scale", handler, output0.Scale, "\t");
			Read<int>("ownerActorId", handler, output0.OwnerActorId, "\t");

			unsigned char defaultStatsMode_var7 = 0;
			Read<unsigned char>("defaultStatsMode", handler, defaultStatsMode_var7, "\t");

			ValidateValues(stream, "defaultStatsMode", "\t", defaultStatsMode_var7, (unsigned char)35);

			if (defaultStatsMode_var7 == 35)
			{
				Read<unsigned long long>("hpMax", handler, output0.Hp.Max, "\t\t");
				Read<unsigned int>("attackSpeedMax", handler, output0.AttackSpeed.Max, "\t\t");
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base, "\t\t");
				Read<unsigned int>("attackSpeedBase", handler, output0.AttackSpeed.Base, "\t\t");
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current, "\t\t");
				Read<unsigned int>("attackSpeedCurrent", handler, output0.AttackSpeed.Current, "\t\t");
			}
			Read<long long>("petItemInstanceId", handler, output0.PetItemInstanceId, "\t");

			unsigned char unknown_var15 = 0;
			Read<unsigned char>("unknown", handler, unknown_var15, "\t");
			Read<short>("level", handler, output0.Level, "\t");
			Read<short>("petTaming", handler, output0.PetTaming, "\t");

			int unknown_var18 = 0;
			Read<int>("unknown", handler, unknown_var18, "\t");
			Read<std::wstring>("name", handler, output0.Name, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPetPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldRemovePetPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemovePetPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::TrophyStartPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TrophyStartPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::TrophyContentPacket output1;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Trophies, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("trophyId", handler, output1.Trophies[i].TrophyId, "\t\t\t");

					int unknown_var3 = 0;
					Read<int>("unknown", handler, unknown_var3, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var3, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)9);

					Read<unsigned char>("status", handler, output1.Trophies[i].Status, "\t\t\t");

					ValidateValues(stream, "status", "\t\t\t", output1.Trophies[i].Status, (unsigned char)2, (unsigned char)3);

					Read<int>("isDone", handler, output1.Trophies[i].IsDone, "\t\t\t");
					Read<int>("nextGrade", handler, output1.Trophies[i].NextGrade, "\t\t\t");
					Read<int>("lastReward", handler, output1.Trophies[i].LastReward, "\t\t\t");
					Read<bool>("isFavorited", handler, output1.Trophies[i].IsFavorited, "\t\t\t");

					ValidateValues(stream, "isFavorited", "\t\t\t", output1.Trophies[i].IsFavorited, (bool)0, (bool)1);

					Read<long long>("counter", handler, output1.Trophies[i].Counter, "\t\t\t");

					int timestampsCount_var10 = 0;
					Read<int>("timestampsCount", handler, timestampsCount_var10, "\t\t\t");

					ResizeVector(handler, output1.Trophies[i].Timestamps, timestampsCount_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int j = 0; j < timestampsCount_var10 && !handler.PacketStream().HasRecentlyFailed; ++j)
					{
						Read<int>("index", handler, output1.Trophies[i].Timestamps[j].Index, "\t\t\t\t");
						Read<long long>("timestamp", handler, output1.Trophies[i].Timestamps[j].Time, "\t\t\t\t");
					}
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TrophyContentPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::TrophyUpdatePacket output2;

				Read<int>("trophyId", handler, output2.TrophyId, "\t\t");
				Read<unsigned char>("status", handler, output2.Status, "\t\t");

				ValidateValues(stream, "status", "\t\t", output2.Status, (unsigned char)2, (unsigned char)3);

				Read<int>("isDone", handler, output2.IsDone, "\t\t");
				Read<int>("nextGrade", handler, output2.NextGrade, "\t\t");
				Read<int>("lastReward", handler, output2.LastReward, "\t\t");
				Read<bool>("isFavorited", handler, output2.IsFavorited, "\t\t");

				ValidateValues(stream, "isFavorited", "\t\t", output2.IsFavorited, (bool)0, (bool)1);

				Read<long long>("counter", handler, output2.Counter, "\t\t");

				int timestampsCount_var20 = 0;
				Read<int>("timestampsCount", handler, timestampsCount_var20, "\t\t");

				ResizeVector(handler, output2.Timestamps, timestampsCount_var20);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < timestampsCount_var20 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("index", handler, output2.Timestamps[i].Index, "\t\t\t");
					Read<long long>("timestamp", handler, output2.Timestamps[i].Time, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TrophyUpdatePacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<bool>("found", handler, output0.Found, "\t");

			ValidateValues(stream, "found", "\t", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2, "\t\t");

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3, "\t\t");
				Read<long long>("currentTime", handler, output0.CurrentTime, "\t\t");

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer2(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentBadges_v12(handler, output0.Equipment);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CharacterInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId, "\t\t");
				Read<int>("dollItemId", handler, output0.DollItemId, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");
				Read<bool>("hasItems", handler, output0.HasItems, "\t\t");

				ValidateValues(stream, "hasItems", "\t\t", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7, "\t\t");

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t\t");
					Read<std::wstring>("slotName", handler, output0.Items[i].SlotName, "\t\t\t");
					Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v12(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");
			}

			if (mode_var0 == 6)
			{
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId, "\t\t");
				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output2.SlotName, "\t\t");
				Read<int>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output3.SlotName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");
			}

			if (mode_var0 == 11)
			{
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x84>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)13);

			if (mode_var0 == 0)
			{
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName, "\t\t");
				Read<long long>("characterId", handler, output0.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message, "\t\t");
				Read<std::wstring>("name", handler, output1.Name, "\t\t");
				Read<int>("itemId", handler, output1.ItemId, "\t\t");
				Read<int>("level", handler, output1.Level, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success, "\t\t");

				ValidateValues(stream, "success", "\t\t", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output6.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot, "\t\t");
				Read<int>("amount", handler, output6.Amount, "\t\t");
				Read<int>("tradeSlot2", handler, output6.TradeSlot2, "\t\t");
				ParseItemData_v12(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot, "\t\t");
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index, "\t\t");
				Read<long long>("mesos", handler, output8.Mesos, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				unsigned char index_var23 = 0;
				Read<unsigned char>("index", handler, index_var23, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::TradeFinalizeConfirmPacket output10;

				Read<unsigned char>("index", handler, output10.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 14)
			{
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x99>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType, "\t\t");

				ValidateValues(stream, "enchantType", "\t\t", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3, "\t\t");

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4, "\t\t\t");
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem, "\t\t\t");

					ValidateValues(stream, "requiredItem", "\t\t\t", output0.Ingredients[i].RequiredItem, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount, "\t\t\t");
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7, "\t\t");

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8, "\t\t");

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v12(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					Read<float>("successRate", handler, output0.SuccessRate, "\t\t\t");
					Read<float>("unknownRate2", handler, output0.UnknownRate2, "\t\t\t");
					Read<float>("unknownRate3", handler, output0.UnknownRate3, "\t\t\t");
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate, "\t\t\t");
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate, "\t\t\t");

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14, "\t\t\t");

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15, "\t\t\t");

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16, "\t\t\t");
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					Read<int>("itemId", handler, output0.ItemId, "\t\t\t");
					Read<short>("rarity", handler, output0.Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");
				Read<int>("enchantExp", handler, output1.EnchantExp, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount, "\t\t");
				Read<int>("catalystWeight", handler, output2.CatalystWeight, "\t\t");

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24, "\t\t");

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId, "\t\t\t");
				}
				Read<float>("successRate", handler, output2.SuccessRate, "\t\t");
				Read<float>("unknownRate2", handler, output2.UnknownRate2, "\t\t");
				Read<float>("unknownRate3", handler, output2.UnknownRate3, "\t\t");
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate, "\t\t");
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight, "\t\t");

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32, "\t\t");

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
			if (mode_var0 == 10)
			{
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36, "\t\t");

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v12(handler, output4.Stats[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantSuccessPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39, "\t\t");

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40, "\t\t");

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41, "\t\t");
				Read<int>("failStacks", handler, output5.FailStacks, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44, "\t\t");
			}

			if (mode_var0 == 16)
			{
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x9a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");
				Read<int>("errorCode", handler, output0.ErrorCode, "\t\t");
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId, "\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t");

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6, "\t\t");

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v12(handler, output1.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketMyListingsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::BlackMarketCreateListingPacket output2;
				ParseBlackMarketEntryData_v12(handler, output2.Listing);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCreateListingPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId, "\t\t");

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9, "\t\t");

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v12(handler, output4.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSearchResultsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId, "\t\t");
				Read<int>("amount", handler, output5.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12, "\t\t");

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14, "\t\t");
			}

			if (mode_var0 == 7)
			{
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId, "\t\t");
				Read<int>("rarity", handler, output7.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice, "\t\t");

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xc1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::EnchantScrollEnchantUiPacket output0;
				ParseEnchantScrollEnchantUi_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollEnchantUiPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::EnchantScrollStatUiPacket output1;
				ParseEnchantScrollStatUi_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollStatUiPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				short result_var1 = 0;
				Read<short>("result", handler, result_var1, "\t\t");

				ValidateValues(stream, "result", "\t\t", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t\t");

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v12(handler, output2.ItemData, (unsigned int)itemId_var3);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollSuccessPacket>(output2);
					}


					return;
				}

				else
				{
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);
					}

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollResultPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5, "\t\t");

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Data[i].ItemId, "\t\t\t");

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollRewardPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xc9>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition, "\t\t");
				Read<int>("gmId", handler, output0.GMId, "\t\t");
				Read<int>("percussionId", handler, output0.PercussionId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output1.ActorId, "\t\t");
				Read<int>("midiNote", handler, output1.MidiNote, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom, "\t\t");

				ValidateValues(stream, "isCustom", "\t\t", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output3.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition, "\t\t");
				Read<int>("instrumentTick", handler, output3.InstrumentTick, "\t\t");
				Read<int>("gmId", handler, output3.GMId, "\t\t");
				Read<int>("percussionId", handler, output3.PercussionId, "\t\t");

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					Read<std::string>("musicCode", handler, output3.MusicCode, "\t\t\t");
				}

				else
				{
					Read<std::wstring>("fileName", handler, output3.FileName, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output4.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output6.ItemData, (unsigned int)itemId_var24);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");
				Read<int>("remainingUses", handler, output7.RemainingUses, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId, "\t\t");
				Read<std::string>("musicCode", handler, output8.MusicCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xcb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesScrollUseOnItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseOnItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesScrollApplyPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)itemId_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesScrollErrorPacket output3;

				bool unknown_var6 = false;
				Read<bool>("unknown", handler, unknown_var6, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var6, (bool)0, (bool)1);

				int message_var7 = 0;
				Read<int>("message", handler, message_var7, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var7, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xce>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId, "\t\t");
				Read<int>("petActorId", handler, output0.PetActorId, "\t\t");
				ParseFieldPetData_v12(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId, "\t\t");
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId, "\t\t");
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10, "\t\t");

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("petId", handler, output6.Pets[i].PetId, "\t\t\t");
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity, "\t\t\t");

					ValidateValues(stream, "petRarity", "\t\t\t", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId, "\t\t");
				Read<short>("petRarity", handler, output7.PetRarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output8.PetProfile);
				ParsePetPotionSettingsData_v12(handler, output8.PetPotionSettings);
				ParsePetLootSettingsData_v12(handler, output8.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInfoPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId, "\t\t");
				Read<long long>("exp", handler, output9.Exp, "\t\t");
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId, "\t\t");
				Read<int>("level", handler, output10.Level, "\t\t");
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned, "\t\t");

				ValidateValues(stream, "isSummoned", "\t\t", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId, "\t\t");
				Read<int>("itemId", handler, output13.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output13.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output14.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount, "\t\t");

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output14.ItemData, (unsigned int)itemId_var32);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePacket>(output14);
				}


				return;
			}

			if (mode_var0 == 18)
			{
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId, "\t\t");
				Read<int>("points", handler, output15.Points, "\t\t");
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId, "\t\t");
				ParseFieldPetData_v12(handler, output18.FieldPet);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetUnknownFieldPetPacket>(output18);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xd0>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");
				Read<int>("rarity", handler, output0.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5, "\t\t");
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<int>("amount", handler, output2.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId, "\t\t");
				Read<short>("srcSlot", handler, output3.SourceSlot, "\t\t");
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId, "\t\t");
				Read<short>("dstSlot", handler, output3.DestinationSlot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetInventoryListItemsPacket output4;

				short count_var13 = 0;
				Read<short>("count", handler, count_var13, "\t\t");

				ResizeVector(handler, output4.Slots, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Slots[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId, "\t\t\t");
					Read<short>("slot", handler, output4.Slots[i].Slot, "\t\t\t");
					Read<int>("rarity", handler, output4.Slots[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v12(handler, output4.Slots[i].ItemData, (unsigned int)output4.Slots[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryListItemsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetInventoryStartListPacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStartListPacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xcc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId, "\t\t");
				Read<int>("petActorId", handler, output0.PetActorId, "\t\t");
				ParseFieldPetData_v2486(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId, "\t\t");
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId, "\t\t");
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10, "\t\t");

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("petId", handler, output6.Pets[i].PetId, "\t\t\t");
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity, "\t\t\t");

					ValidateValues(stream, "petRarity", "\t\t\t", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId, "\t\t");
				Read<short>("petRarity", handler, output7.PetRarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output8.PetProfile);
				ParsePetPotionSettingsData_v12(handler, output8.PetPotionSettings);
				ParsePetLootSettingsData_v12(handler, output8.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInfoPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId, "\t\t");
				Read<long long>("exp", handler, output9.Exp, "\t\t");
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId, "\t\t");
				Read<int>("level", handler, output10.Level, "\t\t");
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned, "\t\t");

				ValidateValues(stream, "isSummoned", "\t\t", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId, "\t\t");
				Read<int>("itemId", handler, output13.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output13.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output14.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount, "\t\t");

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output14.ItemData, (unsigned int)itemId_var32);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePacket>(output14);
				}


				return;
			}

			if (mode_var0 == 18)
			{
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId, "\t\t");
				Read<int>("points", handler, output15.Points, "\t\t");
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId, "\t\t");
				ParseFieldPetData_v2486(handler, output18.FieldPet);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetUnknownFieldPetPacket>(output18);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x4c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId, "\t\t");
				Read<unsigned char>("flags", handler, output1.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5, "\t\t");

				ValidateValues(stream, "actionMode", "\t\t", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6, "\t\t\t");
				}

				if (actionMode_var5 == 3)
				{
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8, "\t\t\t");

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10, "\t\t\t");

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t\t");
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t\t");

						ValidateValues(stream, "rarity", "\t\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount, "\t\t\t\t");
						ParseItemData_v2486(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardItemPacket>(output5);
					}


					return;
				}

				if (actionMode_var5 == 6)
				{
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
				}
				if (actionMode_var5 == 10)
				{
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17, "\t\t\t");

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::NpcTalkUpdatePacket output10;
				ParseScriptContent_v12(handler, output10.ScriptContent);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkUpdatePacket>(output10);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags, "\t\t");

				ValidateValues(stream, "flags", "\t\t", output11.Flags, (unsigned char)255);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20, "\t\t");
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output12.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseCharacterListEntry_v2486(handler, output0.Characters[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::CharacterListAddPacket output1;
				ParseCharacterListEntry_v2486(handler, output1.Character);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("characterId", handler, output2.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
			}
			if (mode_var0 == 4)
			{
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");
			}

			if (mode_var0 == 5)
			{
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId, "\t\t");
				Read<int>("messageId", handler, output3.MessageId, "\t\t");
				Read<long long>("deleteTime", handler, output3.DeleteTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");
				Read<int>("messageId", handler, output4.MessageId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x25>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<unsigned char>("slot", handler, output0.Slot, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab, "\t");
			ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x15>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ServerEnterPacket output0;

			Read<int>("playerActorId", handler, output0.PlayerActorId, "\t");
			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<short>("channelId", handler, output0.ChannelId, "\t");
			Read<long long>("exp", handler, output0.Exp, "\t");
			Read<long long>("restExp", handler, output0.RestExp, "\t");
			Read<long long>("mesos", handler, output0.Mesos, "\t");
			Read<long long>("totalMerets", handler, output0.TotalMerets, "\t");
			Read<long long>("merets", handler, output0.Merets, "\t");
			Read<long long>("totalGameMerets", handler, output0.TotalGameMerets, "\t");
			Read<long long>("gameMerets", handler, output0.GameMerets, "\t");
			Read<long long>("eventMerets", handler, output0.EventMerets, "\t");
			Read<long long>("valorTokens", handler, output0.ValorTokens, "\t");
			Read<long long>("treva", handler, output0.Treva, "\t");
			Read<long long>("rue", handler, output0.Rue, "\t");
			Read<long long>("haviFruit", handler, output0.HaviFruit, "\t");
			Read<long long>("reverseCoin", handler, output0.ReverseCoin, "\t");
			Read<long long>("mentorToken", handler, output0.MentorToken, "\t");
			Read<long long>("menteeToken", handler, output0.MenteeToken, "\t");
			Read<long long>("starPoint", handler, output0.StarPoint, "\t");
			Read<long long>("mesoToken", handler, output0.MesoToken, "\t");
			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21, "\t");

			unsigned short unlockedMaps_var22 = 0;
			Read<unsigned short>("unlockedMaps", handler, unlockedMaps_var22, "\t");

			ResizeVector(handler, output0.UnlockedMaps, unlockedMaps_var22);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedMaps_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("mapId", handler, output0.UnlockedMaps[i].MapId, "\t\t");
			}

			unsigned short unlockedTaxis_var24 = 0;
			Read<unsigned short>("unlockedTaxis", handler, unlockedTaxis_var24, "\t");

			ResizeVector(handler, output0.UnlockedTaxis, unlockedTaxis_var24);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedTaxis_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("mapId", handler, output0.UnlockedTaxis[i].MapId, "\t\t");
			}

			long long unknown_var26 = 0;
			Read<long long>("unknown", handler, unknown_var26, "\t");

			std::wstring unknown_var27;
			Read<std::wstring>("unknown", handler, unknown_var27, "\t");
			Read<std::wstring>("mapleNewsUrl", handler, output0.MapleNewsUrl, "\t");

			std::wstring unknown_var29;
			Read<std::wstring>("unknown", handler, unknown_var29, "\t");

			std::wstring nxCacheUrl_var30;
			Read<std::wstring>("nxCacheUrl", handler, nxCacheUrl_var30, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ServerEnterPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x27>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<long long>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot, "\t");
			ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					unsigned char basicStatCount_var5 = 5;

					ResizeVector(handler, output0.Stats.Basic, basicStatCount_var5);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}

					short health_var6 = 4;

					output0.Stats.Basic[0].Type = (Enum::StatAttributeBasic)health_var6;

					short attackSpeed_var7 = 13;

					output0.Stats.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var7;

					short moveSpeed_var8 = 14;

					output0.Stats.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var8;

					short mountMoveSpeed_var9 = 22;

					output0.Stats.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var9;

					short jumpHeight_var10 = 32;

					output0.Stats.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var10;

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current, "\t\t\t");
				}

				if (statCount_var4 != 35)
				{
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type, "\t\t\t\t");

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35, "\t");

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52, "\t");

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53, "\t");

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t");

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55, "\t");

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t");

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67, "\t");

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68, "\t");

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x1e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0, "\t");

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t");
				Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t");
				Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatItemLinkPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x23>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot, "\t\t");
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output4.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output5.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::FurnishingStorageEndListPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageEndListPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x2a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v2486(handler, output0.ItemData, (unsigned int)itemId_var2);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemUpdatePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");
			Read<long long>("uid", handler, output0.ItemInstanceId, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<int>("ownerId", handler, output0.OwnerId, "\t");

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8, "\t");

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var10, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<bool>("isChaining", handler, output0.IsChaining, "\t\t");

				ValidateValues(stream, "isChaining", "\t\t", output0.IsChaining, (bool)0, (bool)1);

				unsigned char count_var10 = 0;
				Read<unsigned char>("count", handler, count_var10, "\t\t");

				ResizeVector(handler, output0.Hits, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					long long unknown_var11 = 0;
					Read<long long>("unknown", handler, unknown_var11, "\t\t\t");
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack, "\t\t\t");
					Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t");
					Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;
				ParseSkillDamagePacket_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<int>("damage", handler, output2.Damage, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;
				ParseSkillDamageHealPacket_v12(handler, output3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;
				ParseSkillDamageRegionPacket_v12(handler, output4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;
				ParseSkillDamageTilePacket_v12(handler, output5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t");

				int count_var17 = 0;
				Read<int>("count", handler, count_var17, "\t\t");

				for (int i = 0; i < count_var17 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var18 = 0;
					Read<int>("unknown", handler, unknown_var18, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19, "\t\t");

				bool hasTarget_var20 = false;
				Read<bool>("hasTarget", handler, hasTarget_var20, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var20, (bool)0, (bool)1);

				if (hasTarget_var20)
				{
					unsigned int skillId_var21 = 0;
					Read<unsigned int>("skillId", handler, skillId_var21, "\t\t\t");

					unsigned short skillLevel_var22 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var22, "\t\t\t");

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23, "\t\t\t");

					int npcId_var24 = 0;
					Read<int>("npcId", handler, npcId_var24, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x37>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ExpUpPacket output0;

			Read<bool>("isRestExp", handler, output0.IsRestExp, "\t");

			ValidateValues(stream, "isRestExp", "\t", output0.IsRestExp, (bool)0, (bool)1);

			if (output0.IsRestExp == 0)
			{
				Read<long long>("expGained", handler, output0.ExpGained, "\t\t");

				short unknown_var2 = 0;
				Read<short>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("totalExp", handler, output0.TotalExp, "\t\t");
				Read<long long>("restExp", handler, output0.RestExp, "\t\t");
				Read<int>("message", handler, output0.Message, "\t\t");
				Read<bool>("additional", handler, output0.Additional, "\t\t");

				ValidateValues(stream, "additional", "\t\t", output0.Additional, (bool)0, (bool)1);
			}

			if (output0.IsRestExp)
			{
				Read<long long>("restExp", handler, output0.RestExp, "\t\t");
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ExpUpPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x51>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				Server::ShopOpenPacket output0;
				ParseShopData_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopOpenPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("entryId", handler, output1.Items[i].EntryId, "\t\t\t");
					Read<int>("itemId", handler, output1.Items[i].ItemId, "\t\t\t");
					ParseShopItemData_v12(handler, output1.Items[i]);
					ParseItemData_v2486(handler, output1.Items[i].ItemData, (unsigned int)output1.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadItemsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId, "\t\t");
				Read<int>("buyCount", handler, output2.BuyCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId, "\t\t");
				Read<int>("buyCount", handler, output3.BuyCount, "\t\t");
				Read<int>("totalPrice", handler, output3.TotalPrice, "\t\t");
				Read<unsigned char>("fontColor", handler, output3.FontColor, "\t\t");
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage, "\t\t");

				ValidateValues(stream, "toGuildStorage", "\t\t", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ShopAddBuyBackPacket output5;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12, "\t\t");

				ResizeVector(handler, output5.Items, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId, "\t\t\t");
					Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t");
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price, "\t\t\t");
					ParseItemData_v2486(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopAddBuyBackPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock, "\t\t");

				ValidateValues(stream, "restock", "\t\t", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var19, (int)0);

					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var20, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				short unknown_var21 = 0;
				Read<short>("unknown", handler, unknown_var21, "\t\t");
			}

			if (mode_var0 == 12)
			{
				Server::ShopLoadMeretItemPacket output8;

				short count_var22 = 0;
				Read<short>("count", handler, count_var22, "\t\t");

				ResizeVector(handler, output8.Items, count_var22);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMeretShopPremiumItemEntry_v12(handler, output8.Items[i].MeretItemEntry);

					unsigned char unknown_var23 = 0;
					Read<unsigned char>("unknown", handler, unknown_var23, "\t\t\t");

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24, "\t\t\t");

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				int npcId_var26 = 0;
				Read<int>("npcId", handler, npcId_var26, "\t\t");

				int shopId_var27 = 0;
				Read<int>("shopId", handler, shopId_var27, "\t\t");

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28, "\t\t");

				short unknown_var29 = 0;
				Read<short>("unknown", handler, unknown_var29, "\t\t");
			}

			if (mode_var0 == 14)
			{
				Server::ShopLoadNewPacket output9;

				short count_var30 = 0;
				Read<short>("count", handler, count_var30, "\t\t");

				ResizeVector(handler, output9.Items, count_var30);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output9.Items[i].ItemId, "\t\t\t");

					bool unknown_var32 = false;
					Read<bool>("unknown", handler, unknown_var32, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var32, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output9.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output9.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var34;
					Read<std::string>("unknown", handler, unknown_var34, "\t\t\t");

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35, "\t\t\t");

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36, "\t\t\t");
					Read<bool>("hasBuyPeriod", handler, output9.Items[i].HasBuyPeriod, "\t\t\t");

					ValidateValues(stream, "hasBuyPeriod", "\t\t\t", output9.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output9.Items[i].HasBuyPeriod)
					{
						ParseBuyPeriodData_v12(handler, output9.Items[i].BuyPeriod);
					}
					ParseItemData_v2486(handler, output9.Items[i].ItemData, (unsigned int)output9.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::ShopErrorPacket output10;

				Read<int>("message", handler, output10.Message, "\t\t");

				unsigned char unknown_var39 = 0;
				Read<unsigned char>("unknown", handler, unknown_var39, "\t\t");
				Read<int>("stringId", handler, output10.StringId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x54>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailData_v2486(handler, output0.Mail[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output2.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId, "\t\t");

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7, "\t\t");

				ValidateValues(stream, "unknownCondition", "\t\t", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output5.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12, "\t\t");

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount, "\t\t");
				Read<bool>("alert", handler, output7.Alert, "\t\t");

				ValidateValues(stream, "alert", "\t\t", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18, "\t\t");
				Read<unsigned char>("message", handler, output11.Message, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20, "\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23, "\t\t");

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24, "\t\t");

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25, "\t\t");

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceiveGiftNotificationPacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x78>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<bool>("found", handler, output0.Found, "\t");

			ValidateValues(stream, "found", "\t", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2, "\t\t");

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3, "\t\t");
				Read<long long>("currentTime", handler, output0.CurrentTime, "\t\t");

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer2(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CharacterInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x7b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId, "\t\t");
				Read<int>("dollItemId", handler, output0.DollItemId, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");
				Read<bool>("hasItems", handler, output0.HasItems, "\t\t");

				ValidateValues(stream, "hasItems", "\t\t", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7, "\t\t");

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t\t");
					Read<std::wstring>("slotName", handler, output0.Items[i].SlotName, "\t\t\t");
					Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v2486(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");
			}

			if (mode_var0 == 6)
			{
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId, "\t\t");
				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output2.SlotName, "\t\t");
				Read<int>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output3.SlotName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");
			}

			if (mode_var0 == 11)
			{
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x103>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v2486(handler, output0.ItemData, (unsigned int)itemId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BindItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x84>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)13);

			if (mode_var0 == 0)
			{
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName, "\t\t");
				Read<long long>("characterId", handler, output0.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message, "\t\t");
				Read<std::wstring>("name", handler, output1.Name, "\t\t");
				Read<int>("itemId", handler, output1.ItemId, "\t\t");
				Read<int>("level", handler, output1.Level, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success, "\t\t");

				ValidateValues(stream, "success", "\t\t", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output6.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot, "\t\t");
				Read<int>("amount", handler, output6.Amount, "\t\t");
				Read<int>("tradeSlot2", handler, output6.TradeSlot2, "\t\t");
				ParseItemData_v2486(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot, "\t\t");
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index, "\t\t");
				Read<long long>("mesos", handler, output8.Mesos, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				unsigned char index_var23 = 0;
				Read<unsigned char>("index", handler, index_var23, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::TradeFinalizeConfirmPacket output10;

				Read<unsigned char>("index", handler, output10.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 14)
			{
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x99>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType, "\t\t");

				ValidateValues(stream, "enchantType", "\t\t", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3, "\t\t");

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4, "\t\t\t");
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem, "\t\t\t");

					ValidateValues(stream, "requiredItem", "\t\t\t", output0.Ingredients[i].RequiredItem, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount, "\t\t\t");
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7, "\t\t");

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8, "\t\t");

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v12(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					Read<float>("successRate", handler, output0.SuccessRate, "\t\t\t");
					Read<float>("unknownRate2", handler, output0.UnknownRate2, "\t\t\t");
					Read<float>("unknownRate3", handler, output0.UnknownRate3, "\t\t\t");
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate, "\t\t\t");
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate, "\t\t\t");

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14, "\t\t\t");

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15, "\t\t\t");

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16, "\t\t\t");
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					Read<int>("itemId", handler, output0.ItemId, "\t\t\t");
					Read<short>("rarity", handler, output0.Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");
				Read<int>("enchantExp", handler, output1.EnchantExp, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount, "\t\t");
				Read<int>("catalystWeight", handler, output2.CatalystWeight, "\t\t");

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24, "\t\t");

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId, "\t\t\t");
				}
				Read<float>("successRate", handler, output2.SuccessRate, "\t\t");
				Read<float>("unknownRate2", handler, output2.UnknownRate2, "\t\t");
				Read<float>("unknownRate3", handler, output2.UnknownRate3, "\t\t");
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate, "\t\t");
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight, "\t\t");

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32, "\t\t");

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
			if (mode_var0 == 10)
			{
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36, "\t\t");

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v12(handler, output4.Stats[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantSuccessPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39, "\t\t");

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40, "\t\t");

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41, "\t\t");
				Read<int>("failStacks", handler, output5.FailStacks, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44, "\t\t");
			}

			if (mode_var0 == 16)
			{
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x98>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");
				Read<int>("errorCode", handler, output0.ErrorCode, "\t\t");
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId, "\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t");

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6, "\t\t");

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v2486(handler, output1.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketMyListingsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::BlackMarketCreateListingPacket output2;
				ParseBlackMarketEntryData_v2486(handler, output2.Listing);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCreateListingPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId, "\t\t");

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9, "\t\t");

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v2486(handler, output4.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSearchResultsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId, "\t\t");
				Read<int>("amount", handler, output5.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12, "\t\t");

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14, "\t\t");
			}

			if (mode_var0 == 7)
			{
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId, "\t\t");
				Read<int>("rarity", handler, output7.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice, "\t\t");

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xbf>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::EnchantScrollEnchantUiPacket output0;
				ParseEnchantScrollEnchantUi_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollEnchantUiPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::EnchantScrollStatUiPacket output1;
				ParseEnchantScrollStatUi_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollStatUiPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				short result_var1 = 0;
				Read<short>("result", handler, result_var1, "\t\t");

				ValidateValues(stream, "result", "\t\t", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t\t");

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v2486(handler, output2.ItemData, (unsigned int)itemId_var3);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollSuccessPacket>(output2);
					}


					return;
				}

				else
				{
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);
					}

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollResultPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5, "\t\t");

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Data[i].ItemId, "\t\t\t");

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollRewardPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xc7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition, "\t\t");
				Read<int>("gmId", handler, output0.GMId, "\t\t");
				Read<int>("percussionId", handler, output0.PercussionId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output1.ActorId, "\t\t");
				Read<int>("midiNote", handler, output1.MidiNote, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom, "\t\t");

				ValidateValues(stream, "isCustom", "\t\t", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output3.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition, "\t\t");
				Read<int>("instrumentTick", handler, output3.InstrumentTick, "\t\t");
				Read<int>("gmId", handler, output3.GMId, "\t\t");
				Read<int>("percussionId", handler, output3.PercussionId, "\t\t");

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					Read<std::string>("musicCode", handler, output3.MusicCode, "\t\t\t");
				}

				else
				{
					Read<std::wstring>("fileName", handler, output3.FileName, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output4.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output6.ItemData, (unsigned int)itemId_var24);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");
				Read<int>("remainingUses", handler, output7.RemainingUses, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId, "\t\t");
				Read<std::string>("musicCode", handler, output8.MusicCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xc8>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesPreviewPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesAddPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesErrorPacket output2;

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var5, (bool)0, (bool)1);

				int message_var6 = 0;
				Read<int>("message", handler, message_var6, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var6, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesErrorPacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xc9>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesScrollUseOnItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseOnItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesScrollPreviewItemPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)itemId_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ChangeAttributesScrollApplyPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");

				int itemId_var7 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var7 = handler.GetItemIdFromInstance(output3.ItemInstanceId);
				}

				if (itemId_var7 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output3.ItemData, (unsigned int)itemId_var7);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesScrollErrorPacket output4;

				bool unknown_var8 = false;
				Read<bool>("unknown", handler, unknown_var8, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var8, (bool)0, (bool)1);

				int message_var9 = 0;
				Read<int>("message", handler, message_var9, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xce>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");
				Read<int>("rarity", handler, output0.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5, "\t\t");
				ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<int>("amount", handler, output2.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId, "\t\t");
				Read<short>("srcSlot", handler, output3.SourceSlot, "\t\t");
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId, "\t\t");
				Read<short>("dstSlot", handler, output3.DestinationSlot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetInventoryListItemsPacket output4;

				int count_var13 = 0;
				Read<int>("count", handler, count_var13, "\t\t");

				ResizeVector(handler, output4.Slots, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Slots[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId, "\t\t\t");
					Read<short>("slot", handler, output4.Slots[i].Slot, "\t\t\t");
					Read<int>("rarity", handler, output4.Slots[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v2486(handler, output4.Slots[i].ItemData, (unsigned int)output4.Slots[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryListItemsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetInventoryStartListPacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStartListPacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xdb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4, "\t\t");

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId, "\t\t\t");

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v2486(handler, output2.Items[i].ItemData, (unsigned int)itemId_var6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockUpdateItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x105>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BindItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			std::wstring auth1_var1;
			Read<std::wstring>("auth1", handler, auth1_var1, "\t");

			std::wstring auth2_var2;
			Read<std::wstring>("auth2", handler, auth2_var2, "\t");

			unsigned long long unknown_var3 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var3, "\t");

			unsigned long long unknown_var4 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var4, "\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t");

			short unknown_var6 = 0;
			Read<short>("unknown", handler, unknown_var6, "\t");

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7, "\t");

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8, "\t");
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			Read<int>("targetId", handler, output0.Effect.TargetId, "\t");
			Read<int>("instanceId", handler, output0.Effect.InstanceId, "\t");
			Read<int>("sourceId", handler, output0.Effect.SourceId, "\t");

			if (output0.Mode == (Server::BuffPacket::ModeEnum)0)
			{
				ParseEffectStats_v12(handler, output0.Effect.Stats);

				Read<bool>("enabled", handler, output0.Effect.Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effect.Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth, "\t\t");
			}

			if (output0.Mode == (Server::BuffPacket::ModeEnum)2)
			{
				int flags_var6 = 0;
				Read<int>("flags", handler, flags_var6, "\t\t");

				output0.UpdateEffect = GetBit(flags_var6, 0);
				output0.UpdateShield = GetBit(flags_var6, 1);

				if (GetBit(flags_var6, 0) == 1)
				{
					ParseEffectStats_v12(handler, output0.Effect.Stats);

					Read<bool>("enabled", handler, output0.Effect.Enabled, "\t\t\t");

					ValidateValues(stream, "enabled", "\t\t\t", output0.Effect.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var6, 1) == 1)
				{
					Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth, "\t\t\t");
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					unsigned char basicStatCount_var5 = 5;

					ResizeVector(handler, output0.Stats.Basic, basicStatCount_var5);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}

					short health_var6 = 4;

					output0.Stats.Basic[0].Type = (Enum::StatAttributeBasic)health_var6;

					short attackSpeed_var7 = 13;

					output0.Stats.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var7;

					short moveSpeed_var8 = 14;

					output0.Stats.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var8;

					short mountMoveSpeed_var9 = 22;

					output0.Stats.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var9;

					short jumpHeight_var10 = 32;

					output0.Stats.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var10;

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current, "\t\t\t");
				}

				if (statCount_var4 != 35)
				{
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type, "\t\t\t\t");

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35, "\t");

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v12(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52, "\t");

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53, "\t");

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t");

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55, "\t");

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t");

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67, "\t");

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68, "\t");

			int mushkingTailKillCount_var69 = 0;
			Read<int>("mushkingTailKillCount", handler, mushkingTailKillCount_var69, "\t");

			int unknownCount_var70 = 0;
			Read<int>("unknownCount", handler, unknownCount_var70, "\t");

			ResizeVector(handler, output0.UnknownData, unknownCount_var70);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var70 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				int unknown_var71 = 0;
				Read<int>("unknown", handler, unknown_var71, "\t\t");

				std::wstring unknown_var72;
				Read<std::wstring>("unknown", handler, unknown_var72, "\t\t");
			}

			short unknown_var73 = 0;
			Read<short>("unknown", handler, unknown_var73, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xcc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId, "\t\t");
				Read<int>("petActorId", handler, output0.PetActorId, "\t\t");
				ParseFieldPetData_v2497(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId, "\t\t");
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId, "\t\t");
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10, "\t\t");

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("petId", handler, output6.Pets[i].PetId, "\t\t\t");
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity, "\t\t\t");

					ValidateValues(stream, "petRarity", "\t\t\t", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId, "\t\t");
				Read<short>("petRarity", handler, output7.PetRarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId, "\t\t");
				ParsePetProfileData_v12(handler, output8.PetProfile);
				ParsePetPotionSettingsData_v12(handler, output8.PetPotionSettings);
				ParsePetLootSettingsData_v12(handler, output8.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInfoPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId, "\t\t");
				Read<long long>("exp", handler, output9.Exp, "\t\t");
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId, "\t\t");
				Read<int>("level", handler, output10.Level, "\t\t");
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned, "\t\t");

				ValidateValues(stream, "isSummoned", "\t\t", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId, "\t\t");
				Read<int>("itemId", handler, output13.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output13.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId, "\t\t");
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output14.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount, "\t\t");

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output14.ItemData, (unsigned int)itemId_var32);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePacket>(output14);
				}


				return;
			}

			if (mode_var0 == 18)
			{
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId, "\t\t");
				Read<int>("points", handler, output15.Points, "\t\t");
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId, "\t\t");
				ParseFieldPetData_v2497(handler, output18.FieldPet);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetUnknownFieldPetPacket>(output18);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x4c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId, "\t\t");
				Read<unsigned char>("flags", handler, output1.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5, "\t\t");

				ValidateValues(stream, "actionMode", "\t\t", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6, "\t\t\t");
				}

				if (actionMode_var5 == 3)
				{
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8, "\t\t\t");

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10, "\t\t\t");

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t\t");
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t\t");

						ValidateValues(stream, "rarity", "\t\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount, "\t\t\t\t");
						ParseItemData_v2497(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardItemPacket>(output5);
					}


					return;
				}

				if (actionMode_var5 == 6)
				{
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
				}
				if (actionMode_var5 == 10)
				{
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17, "\t\t\t");

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::NpcTalkUpdatePacket output10;
				ParseScriptContent_v12(handler, output10.ScriptContent);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkUpdatePacket>(output10);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags, "\t\t");

				ValidateValues(stream, "flags", "\t\t", output11.Flags, (unsigned char)255);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20, "\t\t");
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags, "\t\t");
				ParseNpcDialog_v12(handler, output12.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseCharacterListEntry_v2497(handler, output0.Characters[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::CharacterListAddPacket output1;
				ParseCharacterListEntry_v2497(handler, output1.Character);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("characterId", handler, output2.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
			}
			if (mode_var0 == 4)
			{
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");
			}

			if (mode_var0 == 5)
			{
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId, "\t\t");
				Read<int>("messageId", handler, output3.MessageId, "\t\t");
				Read<long long>("deleteTime", handler, output3.DeleteTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");
				Read<int>("messageId", handler, output4.MessageId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x27>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<long long>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot, "\t");
			ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2493(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					unsigned char basicStatCount_var5 = 5;

					ResizeVector(handler, output0.Stats.Basic, basicStatCount_var5);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}

					short health_var6 = 4;

					output0.Stats.Basic[0].Type = (Enum::StatAttributeBasic)health_var6;

					short attackSpeed_var7 = 13;

					output0.Stats.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var7;

					short moveSpeed_var8 = 14;

					output0.Stats.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var8;

					short mountMoveSpeed_var9 = 22;

					output0.Stats.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var9;

					short jumpHeight_var10 = 32;

					output0.Stats.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var10;

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current, "\t\t\t");
				}

				if (statCount_var4 != 35)
				{
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type, "\t\t\t\t");

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35, "\t");

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2497(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2497(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2497(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2497(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52, "\t");

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53, "\t");

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t");

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55, "\t");

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t");

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67, "\t");

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68, "\t");

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x1e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0, "\t");

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t");
				Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t");
				Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatItemLinkPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");
			Read<long long>("uid", handler, output0.ItemInstanceId, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<int>("ownerId", handler, output0.OwnerId, "\t");

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8, "\t");

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var10, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x23>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<unsigned char>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot, "\t\t");
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output4.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");
				Read<int>("count", handler, output5.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::FurnishingStorageEndListPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageEndListPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x25>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");
			Read<unsigned char>("slot", handler, output0.Slot, "\t");
			Read<int>("rarity", handler, output0.Rarity, "\t");

			ValidateValues(stream, "rarity", "\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab, "\t");
			ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x2a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v2497(handler, output0.ItemData, (unsigned int)itemId_var2);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemUpdatePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x51>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				Server::ShopOpenPacket output0;
				ParseShopData_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopOpenPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("entryId", handler, output1.Items[i].EntryId, "\t\t\t");
					Read<int>("itemId", handler, output1.Items[i].ItemId, "\t\t\t");
					ParseShopItemData_v12(handler, output1.Items[i]);
					ParseItemData_v2497(handler, output1.Items[i].ItemData, (unsigned int)output1.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadItemsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId, "\t\t");
				Read<int>("buyCount", handler, output2.BuyCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId, "\t\t");
				Read<int>("buyCount", handler, output3.BuyCount, "\t\t");
				Read<int>("totalPrice", handler, output3.TotalPrice, "\t\t");
				Read<unsigned char>("fontColor", handler, output3.FontColor, "\t\t");
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage, "\t\t");

				ValidateValues(stream, "toGuildStorage", "\t\t", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ShopAddBuyBackPacket output5;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12, "\t\t");

				ResizeVector(handler, output5.Items, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId, "\t\t\t");
					Read<int>("itemId", handler, output5.Items[i].ItemId, "\t\t\t");
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price, "\t\t\t");
					ParseItemData_v2497(handler, output5.Items[i].ItemData, (unsigned int)output5.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopAddBuyBackPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock, "\t\t");

				ValidateValues(stream, "restock", "\t\t", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var19, (int)0);

					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var20, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				short unknown_var21 = 0;
				Read<short>("unknown", handler, unknown_var21, "\t\t");
			}

			if (mode_var0 == 12)
			{
				Server::ShopLoadMeretItemPacket output8;

				short count_var22 = 0;
				Read<short>("count", handler, count_var22, "\t\t");

				ResizeVector(handler, output8.Items, count_var22);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMeretShopPremiumItemEntry_v12(handler, output8.Items[i].MeretItemEntry);

					unsigned char unknown_var23 = 0;
					Read<unsigned char>("unknown", handler, unknown_var23, "\t\t\t");

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24, "\t\t\t");

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				int npcId_var26 = 0;
				Read<int>("npcId", handler, npcId_var26, "\t\t");

				int shopId_var27 = 0;
				Read<int>("shopId", handler, shopId_var27, "\t\t");

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28, "\t\t");

				short unknown_var29 = 0;
				Read<short>("unknown", handler, unknown_var29, "\t\t");
			}

			if (mode_var0 == 14)
			{
				Server::ShopLoadNewPacket output9;

				short count_var30 = 0;
				Read<short>("count", handler, count_var30, "\t\t");

				ResizeVector(handler, output9.Items, count_var30);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output9.Items[i].ItemId, "\t\t\t");

					bool unknown_var32 = false;
					Read<bool>("unknown", handler, unknown_var32, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var32, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output9.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output9.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var34;
					Read<std::string>("unknown", handler, unknown_var34, "\t\t\t");

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35, "\t\t\t");

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36, "\t\t\t");
					Read<bool>("hasBuyPeriod", handler, output9.Items[i].HasBuyPeriod, "\t\t\t");

					ValidateValues(stream, "hasBuyPeriod", "\t\t\t", output9.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output9.Items[i].HasBuyPeriod)
					{
						ParseBuyPeriodData_v12(handler, output9.Items[i].BuyPeriod);
					}
					ParseItemData_v2497(handler, output9.Items[i].ItemData, (unsigned int)output9.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::ShopErrorPacket output10;

				Read<int>("message", handler, output10.Message, "\t\t");

				unsigned char unknown_var39 = 0;
				Read<unsigned char>("unknown", handler, unknown_var39, "\t\t");
				Read<int>("stringId", handler, output10.StringId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x54>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseMailData_v2497(handler, output0.Mail[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output2.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId, "\t\t");

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7, "\t\t");

				ValidateValues(stream, "unknownCondition", "\t\t", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId, "\t\t");
				Read<long long>("readTime", handler, output5.ReadTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12, "\t\t");

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount, "\t\t");
				Read<bool>("alert", handler, output7.Alert, "\t\t");

				ValidateValues(stream, "alert", "\t\t", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18, "\t\t");
				Read<unsigned char>("message", handler, output11.Message, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20, "\t\t");

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23, "\t\t");

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24, "\t\t");

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25, "\t\t");

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceiveGiftNotificationPacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x78>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<bool>("found", handler, output0.Found, "\t");

			ValidateValues(stream, "found", "\t", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2, "\t\t");

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3, "\t\t");
				Read<long long>("currentTime", handler, output0.CurrentTime, "\t\t");

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v2497(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6, "\t\t\t");
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2497(handler, output0.Equipment);
					ParseCharacterEquipmentSkins_v2497(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer2(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentBadges_v2497(handler, output0.Equipment);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CharacterInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x7b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId, "\t\t");
				Read<int>("dollItemId", handler, output0.DollItemId, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");
				Read<bool>("hasItems", handler, output0.HasItems, "\t\t");

				ValidateValues(stream, "hasItems", "\t\t", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7, "\t\t");

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output0.Items[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId, "\t\t\t");
					Read<std::wstring>("slotName", handler, output0.Items[i].SlotName, "\t\t\t");
					Read<int>("rarity", handler, output0.Items[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v2497(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");
			}

			if (mode_var0 == 6)
			{
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId, "\t\t");
				Read<int>("itemId", handler, output2.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output2.SlotName, "\t\t");
				Read<int>("rarity", handler, output2.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId, "\t\t");
				Read<std::wstring>("slotName", handler, output3.SlotName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21, "\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t");
			}

			if (mode_var0 == 11)
			{
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x103>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v2497(handler, output0.ItemData, (unsigned int)itemId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BindItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x84>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)13);

			if (mode_var0 == 0)
			{
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName, "\t\t");
				Read<long long>("characterId", handler, output0.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message, "\t\t");
				Read<std::wstring>("name", handler, output1.Name, "\t\t");
				Read<int>("itemId", handler, output1.ItemId, "\t\t");
				Read<int>("level", handler, output1.Level, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success, "\t\t");

				ValidateValues(stream, "success", "\t\t", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");
				Read<int>("rarity", handler, output6.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot, "\t\t");
				Read<int>("amount", handler, output6.Amount, "\t\t");
				Read<int>("tradeSlot2", handler, output6.TradeSlot2, "\t\t");
				ParseItemData_v2497(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index, "\t\t");

				ValidateValues(stream, "index", "\t\t", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot, "\t\t");
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index, "\t\t");
				Read<long long>("mesos", handler, output8.Mesos, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				unsigned char index_var23 = 0;
				Read<unsigned char>("index", handler, index_var23, "\t\t");
			}

			if (mode_var0 == 13)
			{
				Server::TradeFinalizeConfirmPacket output10;

				Read<unsigned char>("index", handler, output10.Index, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 14)
			{
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x99>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType, "\t\t");

				ValidateValues(stream, "enchantType", "\t\t", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3, "\t\t");

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4, "\t\t\t");
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem, "\t\t\t");

					ValidateValues(stream, "requiredItem", "\t\t\t", output0.Ingredients[i].RequiredItem, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount, "\t\t\t");
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7, "\t\t");

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8, "\t\t");

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v2497(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					Read<float>("successRate", handler, output0.SuccessRate, "\t\t\t");
					Read<float>("unknownRate2", handler, output0.UnknownRate2, "\t\t\t");
					Read<float>("unknownRate3", handler, output0.UnknownRate3, "\t\t\t");
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate, "\t\t\t");
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate, "\t\t\t");

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14, "\t\t\t");

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15, "\t\t\t");

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16, "\t\t\t");
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					Read<int>("itemId", handler, output0.ItemId, "\t\t\t");
					Read<short>("rarity", handler, output0.Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");
				Read<int>("enchantExp", handler, output1.EnchantExp, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount, "\t\t");
				Read<int>("catalystWeight", handler, output2.CatalystWeight, "\t\t");

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24, "\t\t");

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId, "\t\t\t");
				}
				Read<float>("successRate", handler, output2.SuccessRate, "\t\t");
				Read<float>("unknownRate2", handler, output2.UnknownRate2, "\t\t");
				Read<float>("unknownRate3", handler, output2.UnknownRate3, "\t\t");
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate, "\t\t");
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight, "\t\t");

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32, "\t\t");

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
			if (mode_var0 == 10)
			{
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t");

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36, "\t\t");

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBasicStat_v2497(handler, output4.Stats[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantSuccessPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId, "\t\t");

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39, "\t\t");

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40, "\t\t");

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41, "\t\t");
				Read<int>("failStacks", handler, output5.FailStacks, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44, "\t\t");
			}

			if (mode_var0 == 16)
			{
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x98>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1, "\t\t");
				Read<int>("errorCode", handler, output0.ErrorCode, "\t\t");
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId, "\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t");

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6, "\t\t");

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v2497(handler, output1.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketMyListingsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::BlackMarketCreateListingPacket output2;
				ParseBlackMarketEntryData_v2497(handler, output2.Listing);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCreateListingPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId, "\t\t");

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9, "\t\t");

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseBlackMarketEntryData_v2497(handler, output4.Entries[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSearchResultsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId, "\t\t");
				Read<int>("amount", handler, output5.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12, "\t\t");

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14, "\t\t");
			}

			if (mode_var0 == 7)
			{
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId, "\t\t");
				Read<int>("rarity", handler, output7.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice, "\t\t");

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xbf>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::EnchantScrollEnchantUiPacket output0;
				ParseEnchantScrollEnchantUi_v12(handler, output0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollEnchantUiPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::EnchantScrollStatUiPacket output1;
				ParseEnchantScrollStatUi_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollStatUiPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				short result_var1 = 0;
				Read<short>("result", handler, result_var1, "\t\t");

				ValidateValues(stream, "result", "\t\t", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t\t");

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v2497(handler, output2.ItemData, (unsigned int)itemId_var3);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollSuccessPacket>(output2);
					}


					return;
				}

				else
				{
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);
					}

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::EnchantScrollResultPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5, "\t\t");

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Data[i].ItemId, "\t\t\t");

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EnchantScrollRewardPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output0.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition, "\t\t");
				Read<int>("gmId", handler, output0.GMId, "\t\t");
				Read<int>("percussionId", handler, output0.PercussionId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output1.ActorId, "\t\t");
				Read<int>("midiNote", handler, output1.MidiNote, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output2.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom, "\t\t");

				ValidateValues(stream, "isCustom", "\t\t", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output3.ActorId, "\t\t");
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition, "\t\t");
				Read<int>("instrumentTick", handler, output3.InstrumentTick, "\t\t");
				Read<int>("gmId", handler, output3.GMId, "\t\t");
				Read<int>("percussionId", handler, output3.PercussionId, "\t\t");

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					Read<std::string>("musicCode", handler, output3.MusicCode, "\t\t\t");
				}

				else
				{
					Read<std::wstring>("fileName", handler, output3.FileName, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId, "\t\t");
				Read<int>("actorId", handler, output4.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId, "\t\t");

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output6.ItemData, (unsigned int)itemId_var24);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId, "\t\t");
				Read<int>("remainingUses", handler, output7.RemainingUses, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId, "\t\t");
				Read<std::string>("musicCode", handler, output8.MusicCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc8>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesPreviewPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesAddPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ChangeAttributesScrollApplyPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");

				int itemId_var6 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var6 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
				}

				if (itemId_var6 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)itemId_var6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesErrorPacket output3;

				bool unknown_var7 = false;
				Read<bool>("unknown", handler, unknown_var7, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var7, (bool)0, (bool)1);

				int message_var8 = 0;
				Read<int>("message", handler, message_var8, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var8, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc9>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::ChangeAttributesScrollUseOnItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseOnItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ChangeAttributesScrollPreviewItemPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)itemId_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ChangeAttributesScrollErrorPacket output3;

				bool unknown_var6 = false;
				Read<bool>("unknown", handler, unknown_var6, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var6, (bool)0, (bool)1);

				int message_var7 = 0;
				Read<int>("message", handler, message_var7, "\t\t");

				ValidateValues(stream, "message", "\t\t", message_var7, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xce>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId, "\t\t");
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");
				Read<int>("rarity", handler, output0.Rarity, "\t\t");

				ValidateValues(stream, "rarity", "\t\t", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5, "\t\t");
				ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId, "\t\t");
				Read<int>("amount", handler, output2.Amount, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId, "\t\t");
				Read<short>("srcSlot", handler, output3.SourceSlot, "\t\t");
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId, "\t\t");
				Read<short>("dstSlot", handler, output3.DestinationSlot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::PetInventoryListItemsPacket output4;

				int count_var13 = 0;
				Read<int>("count", handler, count_var13, "\t\t");

				ResizeVector(handler, output4.Slots, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<int>("itemId", handler, output4.Slots[i].ItemId, "\t\t\t");
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId, "\t\t\t");
					Read<short>("slot", handler, output4.Slots[i].Slot, "\t\t\t");
					Read<int>("rarity", handler, output4.Slots[i].Rarity, "\t\t\t");

					ValidateValues(stream, "rarity", "\t\t\t", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
					ParseItemData_v2497(handler, output4.Slots[i].ItemData, (unsigned int)output4.Slots[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryListItemsPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::PetInventoryStartListPacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStartListPacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xdb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t\t");
				Read<short>("slot", handler, output0.Slot, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4, "\t\t");

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId, "\t\t\t");

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						handler.DiscardPacket();

						return;

					}
					ParseItemData_v2497(handler, output2.Items[i].ItemData, (unsigned int)itemId_var6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockUpdateItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x105>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId, "\t");

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				handler.DiscardPacket();

				return;

			}
			ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BindItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2493, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2493(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					unsigned char basicStatCount_var5 = 5;

					ResizeVector(handler, output0.Stats.Basic, basicStatCount_var5);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}

					short health_var6 = 4;

					output0.Stats.Basic[0].Type = (Enum::StatAttributeBasic)health_var6;

					short attackSpeed_var7 = 13;

					output0.Stats.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var7;

					short moveSpeed_var8 = 14;

					output0.Stats.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var8;

					short mountMoveSpeed_var9 = 22;

					output0.Stats.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var9;

					short jumpHeight_var10 = 32;

					output0.Stats.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var10;

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current, "\t\t\t");
				}

				if (statCount_var4 != 35)
				{
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type, "\t\t\t\t");

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35, "\t");

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52, "\t");

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53, "\t");

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t");

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55, "\t");

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t");

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67, "\t");

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68, "\t");

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2493, ServerPacket, 0x49>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
			ParseSkillTreeData_v2493(handler, output0.SkillTree);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::JobPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2496, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseCharacterListEntry_v2486(handler, output0.Characters[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::CharacterListAddPacket output1;
				ParseCharacterListEntry_v2486(handler, output1.Character);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("characterId", handler, output2.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
			}
			if (mode_var0 == 4)
			{
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");
			}

			if (mode_var0 == 5)
			{
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId, "\t\t");
				Read<int>("messageId", handler, output3.MessageId, "\t\t");
				Read<long long>("deleteTime", handler, output3.DeleteTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");
				Read<int>("messageId", handler, output4.MessageId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2496, ServerPacket, 0x78>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<bool>("found", handler, output0.Found, "\t");

			ValidateValues(stream, "found", "\t", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2, "\t\t");

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3, "\t\t");
				Read<long long>("currentTime", handler, output0.CurrentTime, "\t\t");

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6, "\t\t\t");
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer2(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CharacterInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output0.ServerTick, "\t\t");
				Read<int>("skillId", handler, output0.SkillId, "\t\t");
				Read<short>("skillLevel", handler, output0.SkillLevel, "\t\t");
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");
				Read<bool>("flag", handler, output0.Flag, "\t\t");

				ValidateValues(stream, "flag", "\t\t", output0.Flag, (bool)0, (bool)1);

				if (output0.Flag)
				{
					int unknown_var15 = 0;
					Read<int>("unknown", handler, unknown_var15, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)0);

					std::string unknown_var16;
					Read<std::string>("unknown", handler, unknown_var16, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var17 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var17, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var17, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var17 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", handler, output1.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", handler, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output1.Rotation, "\t\t\t");

					unsigned char count_var22 = 0;
					Read<unsigned char>("count", handler, count_var22, "\t\t\t");

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var23, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var22);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char projectile_i = 0; projectile_i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++projectile_i)
					{
						auto& projectile_array0 = output1.Projectiles[projectile_i];

						Read<long long>("skillAttack", handler, projectile_array0.SkillAttack, "\t\t\t\t");
						Read<int>("targetId", handler, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var27 = false;
						Read<bool>("moreTargets", handler, moreTargets_var27, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var27, (bool)0, (bool)1);

						size_t nextTarget_j = 0;

						while (moreTargets_var27 && !handler.PacketStream().HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							if (handler.PacketStream().HasRecentlyFailed)
							{
								return;
							}

							auto& nextTarget_array1 = projectile_array0.ChainTargets[nextTarget_j];

							Read<long long>("skillAttack", handler, nextTarget_array1.SkillAttack, "\t\t\t\t\t");
							Read<int>("targetId", handler, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var31 = 0;
							Read<unsigned char>("unknown", handler, unknown_var31, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var27, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var27, (bool)0, (bool)1);

							++nextTarget_j;
						}
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);
					}


					return;
				}

				if (damageMode_var17 == 1)
				{
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", handler, output2.SkillSn, "\t\t\t");
					Read<long long>("skillAttack", handler, output2.SkillAttack, "\t\t\t");
					Read<Vector3S>("position", handler, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", handler, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", handler, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint, "\t\t\t");

					unsigned char count_var38 = 0;
					Read<unsigned char>("count", handler, count_var38, "\t\t\t");

					int unknown_var39 = 0;
					Read<int>("unknown", handler, unknown_var39, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var39, (int)0);

					ResizeVector(handler, output2.Hits, count_var38);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char hitActor_i = 0; hitActor_i < count_var38 && !handler.PacketStream().HasRecentlyFailed; ++hitActor_i)
					{
						auto& hitActor_array2 = output2.Hits[hitActor_i];

						Read<int>("entityId", handler, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var41 = 0;
						Read<unsigned char>("unknown", handler, unknown_var41, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var41, (unsigned char)0);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);
					}


					return;
				}

				if (damageMode_var17 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", handler, output3.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output3.AttackPoint, "\t\t\t");

					int unknown_var44 = 0;
					Read<int>("unknown", handler, unknown_var44, "\t\t\t");
					Read<int>("attackCounter", handler, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", handler, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output3.Rotation, "\t\t\t");

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn, "\t\t");
				Read<int>("skillId", handler, output4.SkillId, "\t\t");
				Read<short>("skillLevel", handler, output4.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", handler, output4.Position, "\t\t");

				Vector3S unknown_var53;
				Read<Vector3S>("unknown", handler, unknown_var53, "\t\t");
				Read<Vector3S>("rotation", handler, output4.Rotation, "\t\t");

				Vector3S unknown_var55;
				Read<Vector3S>("unknown", handler, unknown_var55, "\t\t");

				bool unknown_var56 = false;
				Read<bool>("unknown", handler, unknown_var56, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var56, (bool)0, (bool)1);

				int unknown_var57 = 0;
				Read<int>("unknown", handler, unknown_var57, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var57, (int)0);

				unsigned char unknown_var58 = 0;
				Read<unsigned char>("unknown", handler, unknown_var58, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var58, (unsigned char)0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<bool>("isChaining", handler, output0.IsChaining, "\t\t");

				ValidateValues(stream, "isChaining", "\t\t", output0.IsChaining, (bool)0, (bool)1);

				unsigned char count_var10 = 0;
				Read<unsigned char>("count", handler, count_var10, "\t\t");

				ResizeVector(handler, output0.Hits, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					long long unknown_var11 = 0;
					Read<long long>("unknown", handler, unknown_var11, "\t\t\t");
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack, "\t\t\t");
					Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t");
					Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t");
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;
				ParseSkillDamagePacket_v12(handler, output1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<long long>("damage", handler, output2.Damage, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;
				ParseSkillDamageHealPacket_v12(handler, output3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;
				ParseSkillDamageRegionPacket_v12(handler, output4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;
				ParseSkillDamageTilePacket_v12(handler, output5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t");

				int count_var17 = 0;
				Read<int>("count", handler, count_var17, "\t\t");

				for (int i = 0; i < count_var17 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					int unknown_var18 = 0;
					Read<int>("unknown", handler, unknown_var18, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19, "\t\t");

				bool hasTarget_var20 = false;
				Read<bool>("hasTarget", handler, hasTarget_var20, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var20, (bool)0, (bool)1);

				if (hasTarget_var20)
				{
					unsigned int skillId_var21 = 0;
					Read<unsigned int>("skillId", handler, skillId_var21, "\t\t\t");

					unsigned short skillLevel_var22 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var22, "\t\t\t");

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23, "\t\t\t");

					int npcId_var24 = 0;
					Read<int>("npcId", handler, npcId_var24, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<2509, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					ParseCharacterListEntry_v2509(handler, output0.Characters[i]);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				Server::CharacterListAddPacket output1;
				ParseCharacterListEntry_v2509(handler, output1.Character);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListAddPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2, "\t\t");
				Read<long long>("characterId", handler, output2.CharacterId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
			}
			if (mode_var0 == 4)
			{
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4, "\t\t");
			}

			if (mode_var0 == 5)
			{
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId, "\t\t");
				Read<int>("messageId", handler, output3.MessageId, "\t\t");
				Read<long long>("deleteTime", handler, output3.DeleteTime, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId, "\t\t");
				Read<int>("messageId", handler, output4.MessageId, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm, "\t\t");
				Read<long long>("characterId", handler, output5.CharacterId, "\t\t");
				Read<std::wstring>("name", handler, output5.Name, "\t\t");

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2509, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2509(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("Rotation", handler, output0.Rotation, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");

			{

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4, "\t\t");

				if (statCount_var4 == 35)
				{
					unsigned char basicStatCount_var5 = 5;

					ResizeVector(handler, output0.Stats.Basic, basicStatCount_var5);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}

					short health_var6 = 4;

					output0.Stats.Basic[0].Type = (Enum::StatAttributeBasic)health_var6;

					short attackSpeed_var7 = 13;

					output0.Stats.Basic[1].Type = (Enum::StatAttributeBasic)attackSpeed_var7;

					short moveSpeed_var8 = 14;

					output0.Stats.Basic[2].Type = (Enum::StatAttributeBasic)moveSpeed_var8;

					short mountMoveSpeed_var9 = 22;

					output0.Stats.Basic[3].Type = (Enum::StatAttributeBasic)mountMoveSpeed_var9;

					short jumpHeight_var10 = 32;

					output0.Stats.Basic[4].Type = (Enum::StatAttributeBasic)jumpHeight_var10;

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base, "\t\t\t");
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current, "\t\t\t");
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current, "\t\t\t");
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current, "\t\t\t");
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current, "\t\t\t");
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current, "\t\t\t");
				}

				if (statCount_var4 != 35)
				{
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type, "\t\t\t\t");

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max, "\t\t\t\t\t");
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base, "\t\t\t\t\t");
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current, "\t\t\t\t\t");
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle, "\t");

			ValidateValues(stream, "inBattle", "\t", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34, "\t");
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35, "\t");

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36, "\t");

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37, "\t");

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl, "\t");
			Read<bool>("onMount", handler, output0.OnMount, "\t");

			ValidateValues(stream, "onMount", "\t", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40, "\t");
			Read<long long>("timestamp", handler, output0.Timestamp, "\t");
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore, "\t");
			Read<int>("architectScore", handler, output0.ArchitectScore, "\t");

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2509(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2509(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2509(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44, "\t");

			ValidateValues(stream, "isDeflated", "\t", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45, "\t");

			{
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2509(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46, "\t");

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				Read<int>("targetId", handler, output0.Effects[i].TargetId, "\t\t");
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId, "\t\t");
				Read<int>("sourceId", handler, output0.Effects[i].SourceId, "\t\t");
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth, "\t\t");
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52, "\t");

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53, "\t");

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54, "\t");

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55, "\t");

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56, "\t");

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57, "\t");
			Read<int>("titleId", handler, output0.TitleId, "\t");
			Read<short>("insigniaId", handler, output0.InsigniaId, "\t");
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue, "\t");
			Read<int>("petActorId", handler, output0.Pet.ActorId, "\t");
			Read<bool>("hasPet", handler, output0.HasPet, "\t");

			ValidateValues(stream, "hasPet", "\t", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				Read<int>("petItemId", handler, output0.Pet.ItemId, "\t\t");
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId, "\t\t");
				Read<int>("petRarity", handler, output0.Pet.Rarity, "\t\t");

				ValidateValues(stream, "petRarity", "\t\t", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime, "\t");

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67, "\t");

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68, "\t");

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69, "\t");

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2509, ServerPacket, 0x49>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
			ParseSkillTreeData_v2509(handler, output0.SkillTree);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::JobPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2509, ServerPacket, 0x78>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<bool>("found", handler, output0.Found, "\t");

			ValidateValues(stream, "found", "\t", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2, "\t\t");

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3, "\t\t");
				Read<long long>("currentTime", handler, output0.CurrentTime, "\t\t");

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						ParseCharacterDetailsBasicStats_v2509(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v2497(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6, "\t\t\t");
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2509(handler, output0.Equipment);
					ParseCharacterEquipmentSkins_v2509(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5, "\t\t");

				{
					Buffer buffer2(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentBadges_v2509(handler, output0.Equipment);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CharacterInfoPacket>(output0);
			}


			return;
		}

	}
}
