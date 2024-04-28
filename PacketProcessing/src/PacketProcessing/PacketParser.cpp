#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

#include "PacketParserOutputs.h"

namespace Networking
{
	namespace Packets
	{
		void ParseStateSyncData_v12(PacketHandler& handler, Maple::Game::StateSyncData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "StateSyncData_v12(", ")");

			unsigned char state_var0 = 0;
			Read<unsigned char>("state", handler, state_var0);

			unsigned char subState_var1 = 0;
			Read<unsigned char>("subState", handler, subState_var1);

			unsigned char flags_var2 = 0;
			Read<unsigned char>("flags", handler, flags_var2);

			if (GetBit(flags_var2, 0) == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if GetBit(flags_var2, 0) == 1");
				int unknown_var3 = 0;
				Read<int>("unknown", handler, unknown_var3);

				short unknown_var4 = 0;
				Read<short>("unknown", handler, unknown_var4);
			}

			Vector3Short position_var5;
			Read<Vector3Short>("position", handler, position_var5);

			short rotation_var6 = 0;
			Read<short>("rotation", handler, rotation_var6);

			unsigned char animation3_var7 = 0;
			Read<unsigned char>("animation3", handler, animation3_var7);

			if (animation3_var7 > 127)
			{
				StackWatch<PacketHandler> watch_9(handler, "if animation3_var7 > 127");
				float unknown_var8 = 0;
				Read<float>("unknown", handler, unknown_var8);

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9);
			}

			Vector3Short speed_var10;
			Read<Vector3Short>("speed", handler, speed_var10);

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11);

			short rotation2Div10_var12 = 0;
			Read<short>("rotation2Div10", handler, rotation2Div10_var12);

			short coordsDiv1000_var13 = 0;
			Read<short>("coordsDiv1000", handler, coordsDiv1000_var13);

			if (GetBit(flags_var2, 1) == 1)
			{
				StackWatch<PacketHandler> watch_16(handler, "if GetBit(flags_var2, 1) == 1");
				Vector3S unknown_var14;
				Read<Vector3S>("unknown", handler, unknown_var14);

				std::wstring unknown_var15;
				Read<std::wstring>("unknown", handler, unknown_var15);
			}

			if (GetBit(flags_var2, 2) == 1)
			{
				StackWatch<PacketHandler> watch_19(handler, "if GetBit(flags_var2, 2) == 1");
				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16);

				std::wstring unknown_var17;
				Read<std::wstring>("unknown", handler, unknown_var17);
			}

			if (GetBit(flags_var2, 3) == 1)
			{
				StackWatch<PacketHandler> watch_22(handler, "if GetBit(flags_var2, 3) == 1");
				std::wstring animationString_var18;
				Read<std::wstring>("animationString", handler, animationString_var18);
			}

			if (GetBit(flags_var2, 4) == 1)
			{
				StackWatch<PacketHandler> watch_24(handler, "if GetBit(flags_var2, 4) == 1");
				int unknown_var19 = 0;
				Read<int>("unknown", handler, unknown_var19);

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20);
			}

			if (GetBit(flags_var2, 5) == 1)
			{
				StackWatch<PacketHandler> watch_27(handler, "if GetBit(flags_var2, 5) == 1");
				int unknown_var21 = 0;
				Read<int>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23);

				Vector3S unknown_var24;
				Read<Vector3S>("unknown", handler, unknown_var24);

				Vector3S unknown_var25;
				Read<Vector3S>("unknown", handler, unknown_var25);
			}

			int unknown_var26 = 0;
			Read<int>("unknown", handler, unknown_var26);
		}

		void ParseBasicStat_v12(PacketHandler& handler, Maple::Game::BasicStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "BasicStat_v12(", ")");

			Read<short>("type", handler, blockOutput.Type);
			Read<int>("value", handler, blockOutput.Value);
			Read<float>("rate", handler, blockOutput.Rate);
		}

		void ParseSpecialStat_v12(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SpecialStat_v12(", ")");

			Read<short>("type", handler, blockOutput.Type);
			Read<int>("value", handler, blockOutput.Value);
			Read<float>("rate", handler, blockOutput.Rate);
		}

		void ParseBasicAndSpecialStats_v12(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "BasicAndSpecialStats_v12(", ")");

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0);

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Basic[", i, "]"); 
				ParseBasicStat_v12(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0);

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_4(handler, "blockOutput.Special[", i, "]"); 
				ParseSpecialStat_v12(handler, blockOutput.Special[i]);
			}

			Read<int>("empowermentItemId", handler, blockOutput.EmpowermentItemId);
		}

		void ParseAllStatsMyPlayer_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "AllStatsMyPlayer_v12(", ")");

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char statCount_i = 0; statCount_i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++statCount_i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Basic[", statCount_i, "]"); 
				auto& statCount_array0 = blockOutput.Basic[statCount_i];

				unsigned char statType_var1 = statCount_i;

				statCount_array0.Type = (Enum::StatAttributeBasic)statType_var1;

				if (statType_var1 == 4)
				{
					StackWatch<PacketHandler> watch_3(handler, "if statType_var1 == 4");
					Read<unsigned long long>("max", handler, statCount_array0.Max);
					Read<unsigned long long>("base", handler, statCount_array0.Base);
					Read<unsigned long long>("current", handler, statCount_array0.Current);
				}

				else
				{
					StackWatch<PacketHandler> watch_7(handler, "else");
					Read<unsigned int>("max", handler, statCount_array0.Max);
					Read<unsigned int>("base", handler, statCount_array0.Base);
					Read<unsigned int>("current", handler, statCount_array0.Current);
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

				StackWatch<PacketHandler> watch_block(handler, "AllStatsOtherPlayers_v12(", ")");

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

			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Max);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Max);
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Max);
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Max);
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Max);
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Base);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Base);
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Base);
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Base);
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Base);
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Current);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Current);
			Read<unsigned int>("moveSpeed", handler, blockOutput.Basic[2].Current);
			Read<unsigned int>("mountMoveSpeed", handler, blockOutput.Basic[3].Current);
			Read<unsigned int>("jumpHeight", handler, blockOutput.Basic[4].Current);
		}

		void ParseAllStatsNpc_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "AllStatsNpc_v12(", ")");

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

			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Max);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Max);
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Base);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Base);
			Read<unsigned long long>("health", handler, blockOutput.Basic[0].Current);
			Read<unsigned int>("attackSpeed", handler, blockOutput.Basic[1].Current);
		}

		void ParseSpecificStat_v12(PacketHandler& handler, Maple::Game::ActorBasicStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SpecificStat_v12(", ")");

			Read<unsigned char>("statType", handler, blockOutput.Type);

			if (blockOutput.Type == (Enum::StatAttributeBasic)4)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.Type == (Enum::StatAttributeBasic)4");
				Read<unsigned long long>("max", handler, blockOutput.Max);
				Read<unsigned long long>("base", handler, blockOutput.Base);
				Read<unsigned long long>("current", handler, blockOutput.Current);
			}

			if (blockOutput.Type != (Enum::StatAttributeBasic)4)
			{
				StackWatch<PacketHandler> watch_5(handler, "if blockOutput.Type != (Enum::StatAttributeBasic)4");
				Read<unsigned int>("max", handler, blockOutput.Max);
				Read<unsigned int>("base", handler, blockOutput.Base);
				Read<unsigned int>("current", handler, blockOutput.Current);
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

				StackWatch<PacketHandler> watch_block(handler, "SpecificStats_v12(", "statCount: ", statCount_param0, ")");

			ResizeVector(handler, blockOutput.Basic, statCount_param0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < statCount_param0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_0(handler, "blockOutput.Basic[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "ItemBinding_v12(", ")");

			Read<long long>("characterId", handler, blockOutput.CharacterId);
			Read<std::wstring>("name", handler, blockOutput.Name);
		}

		void ParseItemCustomization_v12(PacketHandler& handler, Maple::Game::ItemCustomization& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemCustomization_v12(", "itemId: ", itemId_param0, ")");


			{
				StackWatch<PacketHandler> watch_0(handler, "blockOutput.DyeColor");
				Color4I_BGRA dyeColorPrimary_var0;
				Read<Color4I_BGRA>("dyeColorPrimary", handler, dyeColorPrimary_var0);

				blockOutput.DyeColor.Primary = (Color4I)dyeColorPrimary_var0;

				Color4I_BGRA dyeColorSecondary_var1;
				Read<Color4I_BGRA>("dyeColorSecondary", handler, dyeColorSecondary_var1);

				blockOutput.DyeColor.Secondary = (Color4I)dyeColorSecondary_var1;

				Color4I_BGRA dyeColorTertiary_var2;
				Read<Color4I_BGRA>("dyeColorTertiary", handler, dyeColorTertiary_var2);

				blockOutput.DyeColor.Tertiary = (Color4I)dyeColorTertiary_var2;

				Read<int>("dyeColorIndex", handler, blockOutput.DyeColor.Index);

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4);
			}

			short itemCategory_var5 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemCategory_var5 = handler.GetItemCategory(itemId_param0);

				CalledFunction(handler, "GetItemCategory", "itemCategory_var5", itemCategory_var5, itemId_param0);
			}

			if (itemCategory_var5 == 113)
			{
				StackWatch<PacketHandler> watch_8(handler, "if itemCategory_var5 == 113");

				{
					StackWatch<PacketHandler> watch_9(handler, "blockOutput.Cap");
					Read<Vector3S>("position1", handler, blockOutput.Cap.Position1);
					Read<Vector3S>("position2", handler, blockOutput.Cap.Position2);
					Read<Vector3S>("position3", handler, blockOutput.Cap.Position3);
					Read<Vector3S>("position4", handler, blockOutput.Cap.Position4);

					float unknown_var10 = 0;
					Read<float>("unknown", handler, unknown_var10);
				}
			}

			if (itemCategory_var5 == 102)
			{
				StackWatch<PacketHandler> watch_15(handler, "if itemCategory_var5 == 102");

				{
					StackWatch<PacketHandler> watch_16(handler, "blockOutput.Hair");
					Read<float>("backLength", handler, blockOutput.Hair.BackLength);
					Read<Vector3S>("backPosition1", handler, blockOutput.Hair.BackPosition1);
					Read<Vector3S>("backPosition2", handler, blockOutput.Hair.BackPosition2);
					Read<float>("frontLength", handler, blockOutput.Hair.FrontLength);
					Read<Vector3S>("frontPosition1", handler, blockOutput.Hair.FrontPosition1);
					Read<Vector3S>("frontPosition2", handler, blockOutput.Hair.FrontPosition2);
				}
			}

			if (itemCategory_var5 == 104)
			{
				StackWatch<PacketHandler> watch_23(handler, "if itemCategory_var5 == 104");

				{
					StackWatch<PacketHandler> watch_24(handler, "blockOutput.Decal");
					float position1_var17 = 0;
					Read<float>("position1", handler, position1_var17);

					float position2_var18 = 0;
					Read<float>("position2", handler, position2_var18);

					float position3_var19 = 0;
					Read<float>("position3", handler, position3_var19);

					float position4_var20 = 0;
					Read<float>("position4", handler, position4_var20);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemEnchantmentHeader_v12(", ")");

			Read<int>("enchantLevel", handler, blockOutput.Level);
			Read<int>("enchantExp", handler, blockOutput.EnchantExp);
			Read<unsigned char>("enchantCharges", handler, blockOutput.EnchantCharges);

			long long unknown_var3 = 0;
			Read<long long>("unknown", handler, unknown_var3);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);
			Read<bool>("canRepackage", handler, blockOutput.CanRepackage);

			ValidateValues(handler, "canRepackage", blockOutput.CanRepackage, (bool)0, (bool)1);

			Read<int>("charges", handler, blockOutput.Charges);
		}

		void ParseItemEnchantment_v12(PacketHandler& handler, Maple::Game::ItemEnchantment& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemEnchantment_v12(", ")");

			ParseItemEnchantmentHeader_v12(handler, blockOutput);

			unsigned char basicStatCount_var0 = 0;
			Read<unsigned char>("basicStatCount", handler, basicStatCount_var0);

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_2(handler, "blockOutput.Basic[", i, "]"); 
				Read<int>("type", handler, blockOutput.Basic[i].Type);
				Read<int>("value", handler, blockOutput.Basic[i].Value);
				Read<float>("rate", handler, blockOutput.Basic[i].Rate);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemUgc_v12(", ")");

			long long unknown_var0 = 0;
			Read<long long>("unknown", handler, unknown_var0);
			Read<std::wstring>("fileName", handler, blockOutput.FileName);
			Read<std::wstring>("name", handler, blockOutput.Name);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);
			Read<long long>("accountId", handler, blockOutput.AccountId);
			Read<long long>("characterId", handler, blockOutput.CharacterId);
			Read<std::wstring>("author", handler, blockOutput.Author);
			Read<long long>("creationTime", handler, blockOutput.CreationTime);
			Read<std::wstring>("url", handler, blockOutput.Url);

			unsigned char unknown_var10 = 0;
			Read<unsigned char>("unknown", handler, unknown_var10);
		}

		void ParseItemBlueprint_v12(PacketHandler& handler, Maple::Game::ItemBlueprint& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemBlueprint_v12(", ")");

			long long unknown_var0 = 0;
			Read<long long>("unknown", handler, unknown_var0);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3);

			long long unknown_var4 = 0;
			Read<long long>("unknown", handler, unknown_var4);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			long long unknown_var6 = 0;
			Read<long long>("unknown", handler, unknown_var6);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7);

			std::wstring unknown_var8;
			Read<std::wstring>("unknown", handler, unknown_var8);
		}

		void ParseItemPet_v12(PacketHandler& handler, Maple::Game::ItemPet& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemPet_v12(", ")");

			Read<std::wstring>("name", handler, blockOutput.Name);
			Read<long long>("exp", handler, blockOutput.Exp);
			Read<int>("evolvePoints", handler, blockOutput.EvolvePoints);
			Read<int>("level", handler, blockOutput.Level);
			Read<bool>("hasItems", handler, blockOutput.HasItems);

			ValidateValues(handler, "hasItems", blockOutput.HasItems, (bool)0, (bool)1);
		}

		void ParseItemMusic_v12(PacketHandler& handler, Maple::Game::ItemMusic& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemMusic_v12(", ")");

			Read<int>("length", handler, blockOutput.Length);
			Read<int>("instrument", handler, blockOutput.Instrument);
			Read<std::wstring>("title", handler, blockOutput.Title);
			Read<std::wstring>("author", handler, blockOutput.Author);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);

			ValidateValues(handler, "unknown", unknown_var4, (int)0, (int)1);

			Read<long long>("authorId", handler, blockOutput.AuthorId);
			Read<bool>("isLocked", handler, blockOutput.IsLocked);

			ValidateValues(handler, "isLocked", blockOutput.IsLocked, (bool)0, (bool)1);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7);

			long long unknown_var8 = 0;
			Read<long long>("unknown", handler, unknown_var8);
		}

		void ParseItemBadgeTransparency_v12(PacketHandler& handler, Maple::Game::ItemBadge& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemBadgeTransparency_v12(", ")");

			Read<bool>("transparency", handler, blockOutput.Transparency[0]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[0], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[1]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[1], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[2]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[2], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[3]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[3], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[4]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[4], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[5]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[5], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[6]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[6], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[7]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[7], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[8]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[8], (bool)0, (bool)1);

			Read<bool>("transparency", handler, blockOutput.Transparency[9]);

			ValidateValues(handler, "transparency", blockOutput.Transparency[9], (bool)0, (bool)1);
		}

		void ParseItemBadge_v12(PacketHandler& handler, Maple::Game::ItemBadge& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemBadge_v12(", ")");

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0);

			ValidateValues(handler, "unknown", unknown_var0, (unsigned char)1);

			Read<unsigned char>("type", handler, blockOutput.Type);

			ValidateValues(handler, "type", blockOutput.Type, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			Read<std::wstring>("id", handler, blockOutput.Id);

			if (blockOutput.Type == (Enum::BadgeType)1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if blockOutput.Type == (Enum::BadgeType)1");
				ParseItemBadgeTransparency_v12(handler, blockOutput);
			}

			if (blockOutput.Type == (Enum::BadgeType)11)
			{
				StackWatch<PacketHandler> watch_5(handler, "if blockOutput.Type == (Enum::BadgeType)11");
				Read<int>("petSkinId", handler, blockOutput.PetSkinId);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemTransfer_v12(", ")");

			Read<int>("transferFlags", handler, blockOutput.TransferFlags);

			bool unknown_var1 = false;
			Read<bool>("unknown", handler, unknown_var1);

			ValidateValues(handler, "unknown", unknown_var1, (bool)0, (bool)1);

			Read<int>("remainingTrades", handler, blockOutput.RemainingTrades);
			Read<int>("remainingPackages", handler, blockOutput.RemainingPackages);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4);

			bool unknown_var5 = false;
			Read<bool>("unknown", handler, unknown_var5);

			ValidateValues(handler, "unknown", unknown_var5, (bool)0, (bool)1);

			Read<bool>("isBound", handler, blockOutput.IsBound);

			ValidateValues(handler, "isBound", blockOutput.IsBound, (bool)0, (bool)1);

			if (blockOutput.IsBound)
			{
				StackWatch<PacketHandler> watch_7(handler, "if blockOutput.IsBound");
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

				StackWatch<PacketHandler> watch_block(handler, "ItemSocket_v12(", ")");

			Read<unsigned char>("maxSlots", handler, blockOutput.MaxSlots);
			Read<unsigned char>("unlockedSlots", handler, blockOutput.UnlockedSlots);

			ResizeVector(handler, blockOutput.Sockets, blockOutput.UnlockedSlots);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < blockOutput.UnlockedSlots && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_2(handler, "blockOutput.Sockets[", i, "]"); 
				Read<bool>("hasGem", handler, blockOutput.Sockets[i].HasGem);

				ValidateValues(handler, "hasGem", blockOutput.Sockets[i].HasGem, (bool)0, (bool)1);

				if (blockOutput.Sockets[i].HasGem)
				{
					StackWatch<PacketHandler> watch_4(handler, "if blockOutput.Sockets[i].HasGem");

					{
						StackWatch<PacketHandler> watch_5(handler, "blockOutput.Sockets[i].Gem");
						Read<int>("itemId", handler, blockOutput.Sockets[i].Gem.ItemId);
						Read<bool>("isBound", handler, blockOutput.Sockets[i].Gem.IsBound);

						ValidateValues(handler, "isBound", blockOutput.Sockets[i].Gem.IsBound, (bool)0, (bool)1);

						if (blockOutput.Sockets[i].Gem.IsBound)
						{
							StackWatch<PacketHandler> watch_8(handler, "if blockOutput.Sockets[i].Gem.IsBound");
							ParseItemBinding_v12(handler, blockOutput.Sockets[i].Gem.Binding);
						}

						Read<bool>("isLocked", handler, blockOutput.Sockets[i].Gem.IsLocked);

						ValidateValues(handler, "isLocked", blockOutput.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

						if (blockOutput.Sockets[i].Gem.IsLocked)
						{
							StackWatch<PacketHandler> watch_11(handler, "if blockOutput.Sockets[i].Gem.IsLocked");
							unsigned char unknown_var6 = 0;
							Read<unsigned char>("unknown", handler, unknown_var6);
							Read<long long>("unlockTime", handler, blockOutput.Sockets[i].Gem.UnlockTime);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemCouple_v12(", ")");

			Read<long long>("characterId", handler, blockOutput.CharacterId);

			if (blockOutput.CharacterId != (Enum::CharacterId)0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.CharacterId != (Enum::CharacterId)0");
				Read<std::wstring>("name", handler, blockOutput.Name);
				Read<bool>("isCreator", handler, blockOutput.IsCreator);

				ValidateValues(handler, "isCreator", blockOutput.IsCreator, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemHeader_v12(", ")");

			Read<long long>("creationTime", handler, blockOutput.CreationTime);
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime);

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2);
			Read<int>("timesChanged", handler, blockOutput.TimesChanged);
			Read<int>("remainingUses", handler, blockOutput.RemainingUses);
			Read<bool>("isLocked", handler, blockOutput.IsLocked);

			ValidateValues(handler, "isLocked", blockOutput.IsLocked, (bool)0, (bool)1);

			Read<long long>("unlockTime", handler, blockOutput.UnlockTime);
			Read<short>("glamorForges", handler, blockOutput.GlamorForges);

			unsigned char unknownBool_var8 = 0;
			Read<unsigned char>("unknownBool", handler, unknownBool_var8);

			ValidateValues(handler, "unknownBool", unknownBool_var8, (unsigned char)0);
		}

		void ParseItemData_v12(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemData_v12(", "itemId: ", itemId_param0, ")");

			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);

			ValidateValues(handler, "unknown", unknown_var2, (int)18446744073709551615);
			ParseItemHeader_v12(handler, blockOutput);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				StackWatch<PacketHandler> watch_6(handler, "blockOutput.Stats");

				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
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
				StackWatch<PacketHandler> watch_18(handler, "blockOutput.LimitBreak");

				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level);

				{
					StackWatch<PacketHandler> watch_20(handler, "blockOutput.LimitBreak.Stats");

					int statCount_var6 = 0;
					Read<int>("statCount", handler, statCount_var6);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var6);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_22(handler, "blockOutput.LimitBreak.Stats.Basic[", i, "]"); 
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var6);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var6);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_25(handler, "blockOutput.LimitBreak.Stats.Special[", i, "]"); 
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var7 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var7 = handler.GetItemExtraDataType(itemId_param0);

				CalledFunction(handler, "GetItemExtraDataType", "extraDataType_var7", extraDataType_var7, itemId_param0);
			}

			ValidateValues(handler, "extraDataType", extraDataType_var7, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var7 == 1)
			{
				StackWatch<PacketHandler> watch_29(handler, "if extraDataType_var7 == 1");
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var7 == 2)
			{
				StackWatch<PacketHandler> watch_32(handler, "if extraDataType_var7 == 2");
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var7 == 3)
			{
				StackWatch<PacketHandler> watch_34(handler, "if extraDataType_var7 == 3");
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var7 == 4)
			{
				StackWatch<PacketHandler> watch_36(handler, "if extraDataType_var7 == 4");
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

				StackWatch<PacketHandler> watch_block(handler, "EffectStats_v12(", ")");

			Read<int>("startTime", handler, blockOutput.StartTime);
			Read<int>("endTime", handler, blockOutput.EndTime);
			Read<int>("effectId", handler, blockOutput.EffectId);
			Read<short>("effectLevel", handler, blockOutput.EffectLevel);
			Read<int>("stacks", handler, blockOutput.Stacks);
		}

		void ParseCharacterData_v12(PacketHandler& handler, Maple::Game::CharacterData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "CharacterData_v12(", ")");

			Read<long long>("accountId", handler, blockOutput.AccountId);
			Read<long long>("characterId", handler, blockOutput.CharacterId);
			Read<std::wstring>("name", handler, blockOutput.Name);
			Read<unsigned char>("gender", handler, blockOutput.Gender);

			ValidateValues(handler, "gender", blockOutput.Gender, (unsigned char)0, (unsigned char)1);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);
			Read<int>("mapId", handler, blockOutput.MapId);
			Read<int>("mapInstanceId", handler, blockOutput.MapInstanceId);

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9);
			Read<unsigned short>("level", handler, blockOutput.Level);
			Read<unsigned short>("channel", handler, blockOutput.Channel);
			Read<int>("jobCode", handler, blockOutput.JobCode);
			Read<int>("job", handler, blockOutput.Job);
			Read<int>("currentHp", handler, blockOutput.Hp.Current);
			Read<int>("maxHp", handler, blockOutput.Hp.Max);

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16);

			long long unknown_var17 = 0;
			Read<long long>("unknown", handler, unknown_var17);

			long long storageCooldown_var18 = 0;
			Read<long long>("storageCooldown", handler, storageCooldown_var18);

			blockOutput.StorageCooldown = (long)storageCooldown_var18;

			long long doctorCooldown_var19 = 0;
			Read<long long>("doctorCooldown", handler, doctorCooldown_var19);

			blockOutput.DoctorCooldown = (long)doctorCooldown_var19;

			Read<int>("returnMapId", handler, blockOutput.ReturnMapId);
			Read<Vector3S>("returnPosition", handler, blockOutput.ReturnPosition);
			Read<int>("gearScore", handler, blockOutput.GearScore);

			Color4I_BGRA skinColorPrimary_var23;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var23);

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var23;

			Color4I_BGRA skinColorSecondary_var24;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var24);

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var24;

			long long creationTime_var25 = 0;
			Read<long long>("creationTime", handler, creationTime_var25);

			blockOutput.CreationTime = (long)creationTime_var25;

			Read<int>("combatTrophyCount", handler, blockOutput.CombatTrophyCount);
			Read<int>("adventureTrophyCount", handler, blockOutput.AdventureTrophyCount);
			Read<int>("lifestyleTrophyCount", handler, blockOutput.LifestyleTrophyCount);
			Read<long long>("guildId", handler, blockOutput.GuildId);
			Read<std::wstring>("guildName", handler, blockOutput.GuildName);
			Read<std::wstring>("guildMotto", handler, blockOutput.GuildMotto);
			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);

			unsigned char clubCount_var33 = 0;
			Read<unsigned char>("clubCount", handler, clubCount_var33);

			ResizeVector(handler, blockOutput.Clubs, clubCount_var33);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < clubCount_var33 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_34(handler, "blockOutput.Clubs[", i, "]"); 
				Read<bool>("hasClub", handler, blockOutput.Clubs[i].HasClub);

				ValidateValues(handler, "hasClub", blockOutput.Clubs[i].HasClub, (bool)0, (bool)1);

				if (blockOutput.Clubs[i].HasClub)
				{
					StackWatch<PacketHandler> watch_36(handler, "if blockOutput.Clubs[i].HasClub");
					Read<long long>("clubId", handler, blockOutput.Clubs[i].ClubId);
					Read<std::wstring>("clubName", handler, blockOutput.Clubs[i].ClubName);
				}
			}

			unsigned char unknown_var37 = 0;
			Read<unsigned char>("unknown", handler, unknown_var37);

			{
				StackWatch<PacketHandler> watch_40(handler, "blockOutput.Mastery");

				int placeholderMastery_var38 = 0;
				Read<int>("placeholderMastery", handler, placeholderMastery_var38);

				ValidateValues(handler, "placeholderMastery", placeholderMastery_var38, (int)0);

				Read<int>("fishingMastery", handler, blockOutput.Mastery.Fishing);
				Read<int>("performanceMastery", handler, blockOutput.Mastery.Performance);
				Read<int>("miningMastery", handler, blockOutput.Mastery.Mining);
				Read<int>("foragingMastery", handler, blockOutput.Mastery.Foraging);
				Read<int>("ranchingMastery", handler, blockOutput.Mastery.Ranching);
				Read<int>("farmingMastery", handler, blockOutput.Mastery.Farming);
				Read<int>("smithingMastery", handler, blockOutput.Mastery.Smithing);
				Read<int>("handicraftMastery", handler, blockOutput.Mastery.Handicraft);
				Read<int>("alchemyMastery", handler, blockOutput.Mastery.Alchemy);
				Read<int>("cookingMastery", handler, blockOutput.Mastery.Cooking);
				Read<int>("petTamingMastery", handler, blockOutput.Mastery.PetTaming);
			}
			Read<std::wstring>("username", handler, blockOutput.Username);
			Read<long long>("sessionId", handler, blockOutput.SessionId);

			long long unknown_var52 = 0;
			Read<long long>("unknown", handler, unknown_var52);

			ValidateValues(handler, "unknown", unknown_var52, (long long)0, (long long)2000);

			long long unknown_var53 = 0;
			Read<long long>("unknown", handler, unknown_var53);

			ValidateValues(handler, "unknown", unknown_var53, (long long)0, (long long)3000);

			int unknownCount_var54 = 0;
			Read<int>("unknownCount", handler, unknownCount_var54);

			ResizeVector(handler, blockOutput.UnknownItems, unknownCount_var54);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var54 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_58(handler, "blockOutput.UnknownItems[", i, "]"); 
				long long unknown_var55 = 0;
				Read<long long>("unknown", handler, unknown_var55);
			}

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			bool unknown_var57 = false;
			Read<bool>("unknown", handler, unknown_var57);

			ValidateValues(handler, "unknown", unknown_var57, (bool)0, (bool)1);

			long long birthday_var58 = 0;
			Read<long long>("birthday", handler, birthday_var58);

			blockOutput.Birthday = (long)birthday_var58;

			int unknown_var59 = 0;
			Read<int>("unknown", handler, unknown_var59);

			int unknown_var60 = 0;
			Read<int>("unknown", handler, unknown_var60);

			long long unknownTime_var61 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var61);
			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel);

			long long unknownTime_var63 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var63);

			int unknownCount2_var64 = 0;
			Read<int>("unknownCount2", handler, unknownCount2_var64);

			ResizeVector(handler, blockOutput.UnknownItems2, unknownCount2_var64);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount2_var64 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_69(handler, "blockOutput.UnknownItems2[", i, "]"); 
				long long unknown_var65 = 0;
				Read<long long>("unknown", handler, unknown_var65);
			}

			int unknownCount3_var66 = 0;
			Read<int>("unknownCount3", handler, unknownCount3_var66);

			ResizeVector(handler, blockOutput.UnknownItems3, unknownCount3_var66);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount3_var66 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_72(handler, "blockOutput.UnknownItems3[", i, "]"); 
				long long unknown_var67 = 0;
				Read<long long>("unknown", handler, unknown_var67);
			}

			short unknown_var68 = 0;
			Read<short>("unknown", handler, unknown_var68);

			long long unknown_var69 = 0;
			Read<long long>("unknown", handler, unknown_var69);
		}

		void ParseSkillDamagePacket_v12(PacketHandler& handler, Server::SkillDamagePacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SkillDamagePacket_v12(", ")");

			Read<long long>("skillSn", handler, blockOutput.SkillSn);
			Read<long long>("skillAttack", handler, blockOutput.SkillAttack);
			Read<int>("casterId", handler, blockOutput.CasterId);
			Read<unsigned int>("skillId", handler, blockOutput.SkillId);
			Read<unsigned short>("skillLevel", handler, blockOutput.SkillLevel);
			Read<unsigned char>("motionPoint", handler, blockOutput.MotionPoint);
			Read<unsigned char>("attackPoint", handler, blockOutput.AttackPoint);
			Read<Vector3Short>("position", handler, blockOutput.Position);
			Read<Vector3Short>("direction", handler, blockOutput.Direction);

			unsigned char count_var9 = 0;
			Read<unsigned char>("count", handler, count_var9);

			ResizeVector(handler, blockOutput.DamagedTargets, count_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_10(handler, "blockOutput.DamagedTargets[", i, "]"); 
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId);

				unsigned char damageCount_var11 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var11);

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var11);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var11 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					StackWatch<PacketHandler> watch_13(handler, "blockOutput.DamagedTargets[i].Damages[", j, "]"); 
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType);

					ValidateValues(handler, "hitType", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillDamageDotPacket_v12(", ")");

			Read<int>("casterId", handler, blockOutput.CasterId);
			Read<int>("targetId", handler, blockOutput.TargetId);
			Read<int>("serverTick", handler, blockOutput.ServerTick);
			Read<unsigned char>("hitType", handler, blockOutput.HitType);

			ValidateValues(handler, "hitType", blockOutput.HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);
		}

		void ParseSkillDamageHealPacket_v12(PacketHandler& handler, Server::SkillDamageHealPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SkillDamageHealPacket_v12(", ")");

			Read<int>("casterId", handler, blockOutput.CasterId);
			Read<int>("targetId", handler, blockOutput.TargetId);
			Read<int>("serverTick", handler, blockOutput.ServerTick);
			Read<int>("hpAmount", handler, blockOutput.HpAmount);
			Read<int>("spAmount", handler, blockOutput.SpAmount);
			Read<int>("epAmount", handler, blockOutput.EpAmount);
			Read<bool>("isVisible", handler, blockOutput.IsVisible);

			ValidateValues(handler, "isVisible", blockOutput.IsVisible, (bool)0, (bool)1);
		}

		void ParseSkillDamageRegionPacket_v12(PacketHandler& handler, Server::SkillDamageRegionPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SkillDamageRegionPacket_v12(", ")");

			Read<long long>("skillSn", handler, blockOutput.SkillSn);
			Read<int>("casterId", handler, blockOutput.CasterId);
			Read<int>("regionSkillObjectId", handler, blockOutput.RegionSkillObjectId);
			Read<unsigned char>("attackPoint", handler, blockOutput.AttackPoint);

			unsigned char count_var4 = 0;
			Read<unsigned char>("count", handler, count_var4);

			ResizeVector(handler, blockOutput.DamagedTargets, count_var4);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_5(handler, "blockOutput.DamagedTargets[", i, "]"); 
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId);

				unsigned char damageCount_var6 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var6);
				Read<Vector3Short>("position", handler, blockOutput.DamagedTargets[i].Position);
				Read<Vector3S>("direction", handler, blockOutput.DamagedTargets[i].Direction);

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					StackWatch<PacketHandler> watch_10(handler, "blockOutput.DamagedTargets[i].Damages[", j, "]"); 
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType);

					ValidateValues(handler, "hitType", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillDamageTilePacket_v12(", ")");

			Read<long long>("skillSn", handler, blockOutput.SkillSn);
			Read<unsigned int>("skillId", handler, blockOutput.SkillId);
			Read<unsigned short>("skillLevel", handler, blockOutput.SkillLevel);

			unsigned char count_var3 = 0;
			Read<unsigned char>("count", handler, count_var3);

			ResizeVector(handler, blockOutput.DamagedTargets, count_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_4(handler, "blockOutput.DamagedTargets[", i, "]"); 
				Read<int>("targetId", handler, blockOutput.DamagedTargets[i].TargetId);

				unsigned char damageCount_var5 = 0;
				Read<unsigned char>("damageCount", handler, damageCount_var5);
				Read<Vector3Short>("position", handler, blockOutput.DamagedTargets[i].Position);
				Read<Vector3S>("direction", handler, blockOutput.DamagedTargets[i].Direction);

				ResizeVector(handler, blockOutput.DamagedTargets[i].Damages, damageCount_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char j = 0; j < damageCount_var5 && !handler.PacketStream().HasRecentlyFailed; ++j)
				{
					StackWatch<PacketHandler> watch_9(handler, "blockOutput.DamagedTargets[i].Damages[", j, "]"); 
					Read<unsigned char>("hitType", handler, blockOutput.DamagedTargets[i].Damages[j].HitType);

					ValidateValues(handler, "hitType", blockOutput.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					Read<long long>("damage", handler, blockOutput.DamagedTargets[i].Damages[j].Damage);
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

				StackWatch<PacketHandler> watch_block(handler, "EquipmentData_v12(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<std::wstring>("slot", handler, blockOutput.SlotName);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentItems_v12(", ")");

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0);

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Equipment[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentBadges_v12(", ")");

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0);

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Badges[", i, "]"); 
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot);
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity);

				ValidateValues(handler, "rarity", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkins_v12(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasSkin");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3);

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentFashion_v12(", ")");

			Read<bool>("hasFashion", handler, blockOutput.HasFashion);

			ValidateValues(handler, "hasFashion", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFashion");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3);

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Fashion[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkinsMandatory_v12(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			long long unknown_var1 = 0;
			Read<long long>("unknown", handler, unknown_var1);

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2);

			unsigned char skinCount_var3 = 0;
			Read<unsigned char>("skinCount", handler, skinCount_var3);

			ResizeVector(handler, blockOutput.Skins, skinCount_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_4(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterListEntry_v12(", ")");

			ParseCharacterData_v12(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillTreePageData_v12(", ")");

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0);

			ResizeVector(handler, blockOutput.Skills, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Skills[", i, "]"); 
				Read<bool>("notify", handler, blockOutput.Skills[i].Notify);

				ValidateValues(handler, "notify", blockOutput.Skills[i].Notify, (bool)0, (bool)1);

				Read<bool>("enabled", handler, blockOutput.Skills[i].Enabled);

				ValidateValues(handler, "enabled", blockOutput.Skills[i].Enabled, (bool)0, (bool)1);

				Read<int>("skillId", handler, blockOutput.Skills[i].SkillId);
				Read<int>("skillLevel", handler, blockOutput.Skills[i].SkillLevel);

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5);

				ValidateValues(handler, "unknown", unknown_var5, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillTreeData_v12(", ")");

			Read<int>("job", handler, blockOutput.Job);

			unsigned char unknownCount_var1 = 0;
			Read<unsigned char>("unknownCount", handler, unknownCount_var1);

			ValidateValues(handler, "unknownCount", unknownCount_var1, (unsigned char)1);

			Read<int>("jobCode", handler, blockOutput.JobCode);
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

				StackWatch<PacketHandler> watch_block(handler, "NpcDialog_v12(", ")");

			Read<int>("scriptId", handler, blockOutput.ScriptId);
			Read<int>("scriptIndex", handler, blockOutput.ScriptIndex);
			Read<int>("Options", handler, blockOutput.Options);
		}

		void ParseScriptContent_v12(PacketHandler& handler, Maple::Game::ScriptContentData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ScriptContent_v12(", ")");

			Read<std::wstring>("text", handler, blockOutput.Text);
			Read<std::wstring>("voiceId", handler, blockOutput.VoiceId);
			Read<std::wstring>("illustration", handler, blockOutput.Illustration);
		}

		void ParseShopData_v12(PacketHandler& handler, Server::ShopOpenPacket& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ShopData_v12(", ")");

			Read<int>("npcId", handler, blockOutput.NpcId);
			Read<int>("shopId", handler, blockOutput.ShopId);
			Read<long long>("resetTime", handler, blockOutput.ResetTime);
			Read<int>("remainingSeconds", handler, blockOutput.RemainingSeconds);
			Read<short>("itemCount", handler, blockOutput.ItemCount);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);

			bool unknown_var7 = false;
			Read<bool>("unknown", handler, unknown_var7);

			ValidateValues(handler, "unknown", unknown_var7, (bool)0, (bool)1);

			Read<bool>("canRestock", handler, blockOutput.CanRestock);

			ValidateValues(handler, "canRestock", blockOutput.CanRestock, (bool)0, (bool)1);

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9);

			ValidateValues(handler, "unknown", unknown_var9, (bool)0, (bool)1);

			unsigned char unknown_var10 = 0;
			Read<unsigned char>("unknown", handler, unknown_var10);

			bool unknown_var11 = false;
			Read<bool>("unknown", handler, unknown_var11);

			ValidateValues(handler, "unknown", unknown_var11, (bool)0, (bool)1);

			bool unknown_var12 = false;
			Read<bool>("unknown", handler, unknown_var12);

			ValidateValues(handler, "unknown", unknown_var12, (bool)0, (bool)1);

			bool unknown_var13 = false;
			Read<bool>("unknown", handler, unknown_var13);

			ValidateValues(handler, "unknown", unknown_var13, (bool)0, (bool)1);

			bool unknown_var14 = false;
			Read<bool>("unknown", handler, unknown_var14);

			ValidateValues(handler, "unknown", unknown_var14, (bool)0, (bool)1);

			Read<std::string>("shopName", handler, blockOutput.ShopName);

			if (blockOutput.CanRestock)
			{
				StackWatch<PacketHandler> watch_16(handler, "if blockOutput.CanRestock");
				unsigned char unknown_var16 = 0;
				Read<unsigned char>("unknown", handler, unknown_var16);

				unsigned char unknown_var17 = 0;
				Read<unsigned char>("unknown", handler, unknown_var17);

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18);
				Read<int>("instantRestockCost", handler, blockOutput.InstantRestockCost);

				bool unknown_var20 = false;
				Read<bool>("unknown", handler, unknown_var20);

				ValidateValues(handler, "unknown", unknown_var20, (bool)0, (bool)1);

				int unknown_var21 = 0;
				Read<int>("unknown", handler, unknown_var21);
				Read<unsigned char>("shopType", handler, blockOutput.ShopType);

				bool unknown_var23 = false;
				Read<bool>("unknown", handler, unknown_var23);

				ValidateValues(handler, "unknown", unknown_var23, (bool)0, (bool)1);

				bool unknown_var24 = false;
				Read<bool>("unknown", handler, unknown_var24);

				ValidateValues(handler, "unknown", unknown_var24, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "BuyPeriodData_v12(", ")");

			Read<bool>("hasSpecificTime", handler, blockOutput.HasSpecificTime);

			ValidateValues(handler, "hasSpecificTime", blockOutput.HasSpecificTime, (bool)0, (bool)1);

			if (blockOutput.HasSpecificTime)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasSpecificTime");
				Read<long long>("startTime", handler, blockOutput.StartTime);
				Read<long long>("endTime", handler, blockOutput.EndTime);
			}
			Read<bool>("hasSpecificDays", handler, blockOutput.HasSpecificDays);

			ValidateValues(handler, "hasSpecificDays", blockOutput.HasSpecificDays, (bool)0, (bool)1);

			if (blockOutput.HasSpecificDays)
			{
				StackWatch<PacketHandler> watch_5(handler, "if blockOutput.HasSpecificDays");
				unsigned char timeCount_var4 = 0;
				Read<unsigned char>("timeCount", handler, timeCount_var4);

				ResizeVector(handler, blockOutput.DayTimes, timeCount_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < timeCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "blockOutput.DayTimes[", i, "]"); 
					Read<int>("startTime", handler, blockOutput.DayTimes[i].StartTime);
					Read<int>("endTime", handler, blockOutput.DayTimes[i].EndTime);
				}

				unsigned char dayCount_var7 = 0;
				Read<unsigned char>("dayCount", handler, dayCount_var7);

				ResizeVector(handler, blockOutput.Days, dayCount_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < dayCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "blockOutput.Days[", i, "]"); 
					Read<unsigned char>("dayOfWeek", handler, blockOutput.Days[i].DayOfWeek);

					ValidateValues(handler, "dayOfWeek", blockOutput.Days[i].DayOfWeek, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);
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

				StackWatch<PacketHandler> watch_block(handler, "ShopItemData_v12(", ")");

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0);
			Read<int>("currencyId", handler, blockOutput.CurrencyId);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);
			Read<int>("price", handler, blockOutput.Price);
			Read<int>("price2", handler, blockOutput.Price2);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);
			Read<int>("maxStock", handler, blockOutput.MaxStock);
			Read<int>("totalSold", handler, blockOutput.TotalSold);

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9);
			Read<std::string>("shopCategory", handler, blockOutput.ShopCategory);
			Read<int>("achievementRequired", handler, blockOutput.AchievementRequired);

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12);

			unsigned char unknown_var13 = 0;
			Read<unsigned char>("unknown", handler, unknown_var13);

			short unknown_var14 = 0;
			Read<short>("unknown", handler, unknown_var14);

			unsigned char unknown_var15 = 0;
			Read<unsigned char>("unknown", handler, unknown_var15);

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16);

			bool unknown_var17 = false;
			Read<bool>("unknown", handler, unknown_var17);

			ValidateValues(handler, "unknown", unknown_var17, (bool)0, (bool)1);

			Read<short>("bundleSize", handler, blockOutput.BundleSize);

			unsigned char unknown_var19 = 0;
			Read<unsigned char>("unknown", handler, unknown_var19);

			unsigned char unknown_var20 = 0;
			Read<unsigned char>("unknown", handler, unknown_var20);
			Read<std::string>("currencyIdString", handler, blockOutput.CurrencyIdString);

			short unknown_var22 = 0;
			Read<short>("unknown", handler, unknown_var22);

			int unknown_var23 = 0;
			Read<int>("unknown", handler, unknown_var23);

			bool unknown_var24 = false;
			Read<bool>("unknown", handler, unknown_var24);

			ValidateValues(handler, "unknown", unknown_var24, (bool)0, (bool)1);

			Read<bool>("hasBuyPeriod", handler, blockOutput.HasBuyPeriod);

			ValidateValues(handler, "hasBuyPeriod", blockOutput.HasBuyPeriod, (bool)0, (bool)1);

			if (blockOutput.HasBuyPeriod)
			{
				StackWatch<PacketHandler> watch_26(handler, "if blockOutput.HasBuyPeriod");
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

				StackWatch<PacketHandler> watch_block(handler, "MeretShopPremiumItem_v12(", ")");

			Read<int>("entryId", handler, blockOutput.EntryId);

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1);
			Read<std::wstring>("name", handler, blockOutput.Name);

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3);

			ValidateValues(handler, "unknown", unknown_var3, (bool)0, (bool)1);

			Read<int>("parentId", handler, blockOutput.ParentId);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7);
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel);
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType);
			Read<long long>("price", handler, blockOutput.Price);
			Read<long long>("SalePrice", handler, blockOutput.SalePrice);

			unsigned char unknown_var12 = 0;
			Read<unsigned char>("unknown", handler, unknown_var12);
			Read<long long>("sellBeginTime", handler, blockOutput.SellBeginTime);
			Read<long long>("sellEndTime", handler, blockOutput.SellEndTime);

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15);

			int unknown_var16 = 0;
			Read<int>("unknown", handler, unknown_var16);
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable);

			ValidateValues(handler, "restockUnavailable", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var18 = 0;
			Read<int>("unknown", handler, unknown_var18);

			unsigned char unknown_var19 = 0;
			Read<unsigned char>("unknown", handler, unknown_var19);
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel);
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel);
			Read<int>("requiredJob", handler, blockOutput.RequiredJob);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount);
			Read<int>("itemDuration", handler, blockOutput.ItemDuration);
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity);
			Read<int>("tabId", handler, blockOutput.TabId);

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29);

			int unknown_var30 = 0;
			Read<int>("unknown", handler, unknown_var30);

			unsigned char unknown_var31 = 0;
			Read<unsigned char>("unknown", handler, unknown_var31);
			Read<int>("marketBannerLabel", handler, blockOutput.MarketBannerLabel);
			Read<std::string>("bannerName", handler, blockOutput.BannerName);

			std::string unknown_var34;
			Read<std::string>("unknown", handler, unknown_var34);

			bool unknown_var35 = false;
			Read<bool>("unknown", handler, unknown_var35);

			ValidateValues(handler, "unknown", unknown_var35, (bool)0, (bool)1);

			unsigned char unknown_var36 = 0;
			Read<unsigned char>("unknown", handler, unknown_var36);

			int unknown_var37 = 0;
			Read<int>("unknown", handler, unknown_var37);

			bool unknown_var38 = false;
			Read<bool>("unknown", handler, unknown_var38);

			ValidateValues(handler, "unknown", unknown_var38, (bool)0, (bool)1);

			Read<int>("requiredAchievementId", handler, blockOutput.RequiredAchievementId);
			Read<int>("requiredAchievementRank", handler, blockOutput.RequiredAchievementRank);

			int unknown_var41 = 0;
			Read<int>("unknown", handler, unknown_var41);
			Read<bool>("pcCafe", handler, blockOutput.PcCafe);

			ValidateValues(handler, "pcCafe", blockOutput.PcCafe, (bool)0, (bool)1);

			bool unknown_var43 = false;
			Read<bool>("unknown", handler, unknown_var43);

			ValidateValues(handler, "unknown", unknown_var43, (bool)0, (bool)1);

			int unknown_var44 = 0;
			Read<int>("unknown", handler, unknown_var44);
		}

		void ParseMailAdData_v12(PacketHandler& handler, Maple::Game::MailAdData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MailAdData_v12(", ")");

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3);

			long long unknown_var4 = 0;
			Read<long long>("unknown", handler, unknown_var4);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			long long unknown_var6 = 0;
			Read<long long>("unknown", handler, unknown_var6);
		}

		void ParseMailAttachData_v12(PacketHandler& handler, Maple::Game::MailAttachData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MailAttachData_v12(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("index", handler, blockOutput.Index);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "MailData_v12(", ")");

			Read<unsigned char>("type", handler, blockOutput.Type);

			ValidateValues(handler, "type", blockOutput.Type, (unsigned char)1, (unsigned char)106, (unsigned char)2, (unsigned char)101, (unsigned char)102, (unsigned char)112, (unsigned char)104, (unsigned char)107, (unsigned char)200);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId);
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId);
			Read<std::wstring>("senderName", handler, blockOutput.SenderName);
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle);
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent);
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey);
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue);

			if (blockOutput.Type == 200)
			{
				StackWatch<PacketHandler> watch_8(handler, "if blockOutput.Type == 200");
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8);

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "blockOutput.Ads[", i, "]"); 
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9);

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10);

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11);
			}

			else
			{
				StackWatch<PacketHandler> watch_15(handler, "else");
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12);

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_17(handler, "blockOutput.AttachedItems[", i, "]"); 
					ParseMailAttachData_v12(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos);
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp);
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets);

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16);
			Read<long long>("redMerets", handler, blockOutput.RedMerets);

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18);

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19);

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_26(handler, "blockOutput.Ads[", i, "]"); 
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22);

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23);
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime);
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime);
			Read<long long>("sentTime", handler, blockOutput.SentTime);

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27);
		}

		void ParseMeretShopPremiumItemEntry_v12(PacketHandler& handler, Maple::Game::MeretShopPremiumItemEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MeretShopPremiumItemEntry_v12(", ")");

			Read<int>("entryId", handler, blockOutput.EntryId);

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1);
			Read<std::wstring>("name", handler, blockOutput.Name);

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3);

			ValidateValues(handler, "unknown", unknown_var3, (bool)0, (bool)1);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel);
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType);
			Read<long long>("price", handler, blockOutput.Price);
			Read<long long>("SalePrice", handler, blockOutput.SalePrice);

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11);

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12);

			int unknown_var13 = 0;
			Read<int>("unknown", handler, unknown_var13);
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable);

			ValidateValues(handler, "restockUnavailable", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15);

			unsigned char unknown_var16 = 0;
			Read<unsigned char>("unknown", handler, unknown_var16);
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel);
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel);
			Read<int>("requiredJob", handler, blockOutput.RequiredJob);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount);
			Read<int>("itemDuration", handler, blockOutput.ItemDuration);
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity);
			Read<int>("tabId", handler, blockOutput.TabId);

			int unknown_var26 = 0;
			Read<int>("unknown", handler, unknown_var26);

			bool unknown_var27 = false;
			Read<bool>("unknown", handler, unknown_var27);

			ValidateValues(handler, "unknown", unknown_var27, (bool)0, (bool)1);

			unsigned char unknown_var28 = 0;
			Read<unsigned char>("unknown", handler, unknown_var28);

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29);

			unsigned char count_var30 = 0;
			Read<unsigned char>("count", handler, count_var30);

			ResizeVector(handler, blockOutput.AdditionalQuantities, count_var30);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_31(handler, "blockOutput.AdditionalQuantities[", i, "]"); 
				Read<bool>("hasEntry", handler, blockOutput.AdditionalQuantities[i].HasEntry);

				ValidateValues(handler, "hasEntry", blockOutput.AdditionalQuantities[i].HasEntry, (bool)0, (bool)1);

				if (blockOutput.AdditionalQuantities[i].HasEntry)
				{
					StackWatch<PacketHandler> watch_33(handler, "if blockOutput.AdditionalQuantities[i].HasEntry");
					ParseMeretShopPremiumItem_v12(handler, blockOutput.AdditionalQuantities[i].EntryData);

					Read<bool>("hasUnknown", handler, blockOutput.AdditionalQuantities[i].HasUnknown);

					ValidateValues(handler, "hasUnknown", blockOutput.AdditionalQuantities[i].HasUnknown, (bool)0, (bool)1);

					if (blockOutput.AdditionalQuantities[i].HasUnknown)
					{
						StackWatch<PacketHandler> watch_36(handler, "if blockOutput.AdditionalQuantities[i].HasUnknown");
						std::string unknown_var33;
						Read<std::string>("unknown", handler, unknown_var33);

						long long unknown_var34 = 0;
						Read<long long>("unknown", handler, unknown_var34);

						long long unknown_var35 = 0;
						Read<long long>("unknown", handler, unknown_var35);
					}

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36);

					bool unknown_var37 = false;
					Read<bool>("unknown", handler, unknown_var37);

					ValidateValues(handler, "unknown", unknown_var37, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsHeader_v12(", ")");

			Read<long long>("accountId", handler, blockOutput.AccountId);
			Read<long long>("characterId", handler, blockOutput.CharacterId);
			Read<std::wstring>("characterName", handler, blockOutput.Name);
			Read<short>("level", handler, blockOutput.Level);
			Read<int>("jobCode", handler, blockOutput.JobCode);
			Read<int>("job", handler, blockOutput.Job);
			Read<int>("gender", handler, blockOutput.Gender);

			ValidateValues(handler, "gender", blockOutput.Gender, (int)0, (int)1);

			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel);

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8);

			ValidateValues(handler, "unknown", unknown_var8, (unsigned char)0);
		}

		void ParseCharacterDetailsBody_v12(PacketHandler& handler, Server::CharacterInfoPacket::CharacterDetails& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsBody_v12(", ")");

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);
			Read<std::wstring>("motto", handler, blockOutput.Motto);
			Read<std::wstring>("guildName", handler, blockOutput.GuildName);
			Read<std::wstring>("guildRank", handler, blockOutput.GuildRank);
			Read<std::wstring>("houseName", handler, blockOutput.HouseName);
			Read<int>("plotMapId", handler, blockOutput.PlotMapId);
			Read<int>("plotNumber", handler, blockOutput.PlotNumber);
			Read<int>("apartmentNumber", handler, blockOutput.ApartmentNumber);
			Read<int>("characterTitle", handler, blockOutput.CharacterTitle);

			int unlockedTitles_var9 = 0;
			Read<int>("unlockedTitles", handler, unlockedTitles_var9);

			ResizeVector(handler, blockOutput.UnlockedTitles, unlockedTitles_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unlockedTitles_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_10(handler, "blockOutput.UnlockedTitles[", i, "]"); 
				Read<int>("titleId", handler, blockOutput.UnlockedTitles[i].TitleId);
			}
			Read<int>("trophyCount", handler, blockOutput.TrophyCount);
			Read<int>("gearScore", handler, blockOutput.GearScore);
			Read<long long>("lastLoggedIn", handler, blockOutput.LastLoggedIn);

			long long unknown_var14 = 0;
			Read<long long>("unknown", handler, unknown_var14);

			ValidateValues(handler, "unknown", unknown_var14, (long long)0, (long long)1, (long long)30);

			Color4I_BGRA skinColorPrimary_var15;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var15);

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var15;

			Color4I_BGRA skinColorSecondary_var16;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var16);

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var16;

			Read<short>("maritalStatus", handler, blockOutput.MaritalStatus);
			Read<std::wstring>("spouse1Name", handler, blockOutput.Spouse1Name);
			Read<std::wstring>("spouse2Name", handler, blockOutput.Spouse2Name);
			Read<long long>("proposalTimestamp", handler, blockOutput.ProposalTimestamp);
		}

		void ParseCharacterDetailsBasicStats_v12(PacketHandler& handler, Maple::Game::ActorStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsBasicStats_v12(", ")");

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("max", handler, blockOutput.Basic[i].Max);
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("base", handler, blockOutput.Basic[i].Base);
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_5(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("current", handler, blockOutput.Basic[i].Current);
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_7(handler, "blockOutput.Basic[", i, "]"); 
				Read<float>("rate", handler, blockOutput.Basic[i].Rate);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsSpecialStats_v12(", ")");

			unsigned char specialStatCount_var0 = 180;

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Special[", i, "]"); 
				Read<float>("rate", handler, blockOutput.Special[i].Rate);
			}

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "blockOutput.Special[", i, "]"); 
				Read<float>("value", handler, blockOutput.Special[i].Value);
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

				StackWatch<PacketHandler> watch_block(handler, "CubeItemData_v12(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2);
			Read<bool>("isUgc", handler, blockOutput.IsUgc);

			ValidateValues(handler, "isUgc", blockOutput.IsUgc, (bool)0, (bool)1);

			if (blockOutput.IsUgc)
			{
				StackWatch<PacketHandler> watch_4(handler, "if blockOutput.IsUgc");
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

				StackWatch<PacketHandler> watch_block(handler, "MountData_v12(", ")");

			Read<unsigned char>("rideMode", handler, blockOutput.RideMode);

			ValidateValues(handler, "rideMode", blockOutput.RideMode, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			Read<int>("mountId", handler, blockOutput.MountId);
			Read<int>("mountObjectId", handler, blockOutput.MountObjectId);

			if (blockOutput.RideMode == (Enum::RideMode)1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if blockOutput.RideMode == (Enum::RideMode)1");
				Read<int>("itemId", handler, blockOutput.ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
				ParseItemUgc_v12(handler, blockOutput.Ugc);
			}

			if (blockOutput.RideMode == (Enum::RideMode)2)
			{
				StackWatch<PacketHandler> watch_7(handler, "if blockOutput.RideMode == (Enum::RideMode)2");
				Read<int>("effectId", handler, blockOutput.EffectId);
				Read<short>("effectLevel", handler, blockOutput.EffectLevel);
			}

			unsigned char count_var7 = 0;
			Read<unsigned char>("count", handler, count_var7);

			ResizeVector(handler, blockOutput.UnknownData, count_var7);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_11(handler, "blockOutput.UnknownData[", i, "]"); 
				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8);

				unsigned char unknown_var9 = 0;
				Read<unsigned char>("unknown", handler, unknown_var9);
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

				StackWatch<PacketHandler> watch_block(handler, "EnchantScrollEnchantUi_v12(", ")");

			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<short>("scrollType", handler, blockOutput.ScrollType);

			ValidateValues(handler, "scrollType", blockOutput.ScrollType, (short)1, (short)2, (short)3, (short)4);

			Read<bool>("untradeableReminder", handler, blockOutput.UntradeableReminder);

			ValidateValues(handler, "untradeableReminder", blockOutput.UntradeableReminder, (bool)0, (bool)1);

			Read<int>("enchantLevel", handler, blockOutput.EnchantLevel);
			Read<int>("enchantRate", handler, blockOutput.EnchantRate);
			Read<short>("minLevel", handler, blockOutput.MinLevel);
			Read<short>("maxLevel", handler, blockOutput.MaxLevel);

			unsigned int itemTypeCount_var7 = 0;
			Read<unsigned int>("itemTypeCount", handler, itemTypeCount_var7);

			ResizeVector(handler, blockOutput.ItemTypes, itemTypeCount_var7);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned int i = 0; i < itemTypeCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_8(handler, "blockOutput.ItemTypes[", i, "]"); 
				Read<int>("itemType", handler, blockOutput.ItemTypes[i].ItemType);
			}

			unsigned int itemRarityCount_var9 = 0;
			Read<unsigned int>("itemRarityCount", handler, itemRarityCount_var9);

			ResizeVector(handler, blockOutput.ItemRarities, itemRarityCount_var9);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned int i = 0; i < itemRarityCount_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_11(handler, "blockOutput.ItemRarities[", i, "]"); 
				Read<int>("itemRarity", handler, blockOutput.ItemRarities[i].ItemRarity);
			}

			if (blockOutput.ScrollType == (Server::EnchantScrollEnchantUiPacket::ScrollTypeEnum)3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if blockOutput.ScrollType == (Server::EnchantScrollEnchantUiPacket::ScrollTypeEnum)3");
				Read<int>("minEnchant", handler, blockOutput.MinEnchant);
				Read<int>("maxEnchant", handler, blockOutput.MaxEnchant);
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

				StackWatch<PacketHandler> watch_block(handler, "EnchantScrollStatUi_v12(", ")");

			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<short>("scrollType", handler, blockOutput.ScrollType);

			ValidateValues(handler, "scrollType", blockOutput.ScrollType, (short)1, (short)2, (short)3, (short)4);

			if (blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)5)
			{
				StackWatch<PacketHandler> watch_2(handler, "if blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)5");
			}
			else if (blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)3)
			{
				StackWatch<PacketHandler> watch_3(handler, "else if blockOutput.ScrollType == (Server::EnchantScrollStatUiPacket::ScrollTypeEnum)3");
				unsigned int minStatCount_var2 = 0;
				Read<unsigned int>("minStatCount", handler, minStatCount_var2);

				ResizeVector(handler, blockOutput.MinStats, minStatCount_var2);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < minStatCount_var2 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.MinStats[", i, "]"); 
					Read<short>("statType", handler, blockOutput.MinStats[i].Type);
					Read<float>("minRate", handler, blockOutput.MinStats[i].Rate);
					Read<int>("minValue", handler, blockOutput.MinStats[i].Value);
				}

				unsigned int maxStatCount_var6 = 0;
				Read<unsigned int>("maxStatCount", handler, maxStatCount_var6);

				ResizeVector(handler, blockOutput.MaxStats, maxStatCount_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < maxStatCount_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "blockOutput.MaxStats[", i, "]"); 
					Read<short>("statType", handler, blockOutput.MaxStats[i].Type);
					Read<float>("maxRate", handler, blockOutput.MaxStats[i].Rate);
					Read<int>("maxValue", handler, blockOutput.MaxStats[i].Value);
				}
			}

			else
			{
				StackWatch<PacketHandler> watch_14(handler, "else");
				unsigned int statCount_var10 = 0;
				Read<unsigned int>("statCount", handler, statCount_var10);

				ResizeVector(handler, blockOutput.Stats, statCount_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < statCount_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_16(handler, "blockOutput.Stats[", i, "]"); 
					Read<short>("statType", handler, blockOutput.Stats[i].Type);
					Read<float>("rate", handler, blockOutput.Stats[i].Rate);
					Read<int>("value", handler, blockOutput.Stats[i].Value);
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

				StackWatch<PacketHandler> watch_block(handler, "BlackMarketEntryData_v12(", ")");

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId);
			Read<long long>("timeListed", handler, blockOutput.TimeListed);
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2);
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires);
			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem);

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId);
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

				StackWatch<PacketHandler> watch_block(handler, "FieldPetData_v12(", ")");

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet);

			ValidateValues(handler, "hasFieldPet", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFieldPet");
				Read<int>("itemId", handler, blockOutput.ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Rarity);

				ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "PetProfileData_v12(", ")");

			Read<std::wstring>("name", handler, blockOutput.Name);
			Read<long long>("exp", handler, blockOutput.Exp);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);
			Read<short>("level", handler, blockOutput.Level);

			short unknown_var4 = 0;
			Read<short>("unknown", handler, unknown_var4);

			short unknown_var5 = 0;
			Read<short>("unknown", handler, unknown_var5);
		}

		void ParsePetPotionSettingsData_v12(PacketHandler& handler, Maple::Game::PetPotionSettingsData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "PetPotionSettingsData_v12(", ")");

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0);

			ResizeVector(handler, blockOutput.Slots, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Slots[", i, "]"); 
				Read<int>("thresholdIndex", handler, blockOutput.Slots[i].ThresholdIndex);
				Read<float>("threshold", handler, blockOutput.Slots[i].Threshold);
				Read<int>("itemId", handler, blockOutput.Slots[i].ItemId);
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

				StackWatch<PacketHandler> watch_block(handler, "PetLootSettingsData_v12(", ")");

			Read<bool>("mesos", handler, blockOutput.Mesos);

			ValidateValues(handler, "mesos", blockOutput.Mesos, (bool)0, (bool)1);

			Read<bool>("merets", handler, blockOutput.Merets);

			ValidateValues(handler, "merets", blockOutput.Merets, (bool)0, (bool)1);

			Read<bool>("other", handler, blockOutput.Other);

			ValidateValues(handler, "other", blockOutput.Other, (bool)0, (bool)1);

			Read<bool>("currency", handler, blockOutput.Currency);

			ValidateValues(handler, "currency", blockOutput.Currency, (bool)0, (bool)1);

			Read<bool>("equipment", handler, blockOutput.Equipment);

			ValidateValues(handler, "equipment", blockOutput.Equipment, (bool)0, (bool)1);

			Read<bool>("consumable", handler, blockOutput.Consumable);

			ValidateValues(handler, "consumable", blockOutput.Consumable, (bool)0, (bool)1);

			Read<bool>("gemstone", handler, blockOutput.Gemstone);

			ValidateValues(handler, "gemstone", blockOutput.Gemstone, (bool)0, (bool)1);

			Read<bool>("dropped", handler, blockOutput.Dropped);

			ValidateValues(handler, "dropped", blockOutput.Dropped, (bool)0, (bool)1);

			Read<int>("minRarity", handler, blockOutput.MinRarity);

			ValidateValues(handler, "minRarity", blockOutput.MinRarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<bool>("enabled", handler, blockOutput.Enabled);

			ValidateValues(handler, "enabled", blockOutput.Enabled, (bool)0, (bool)1);
		}

		void ParseStateSyncData_v13(PacketHandler& handler, Maple::Game::StateSyncData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "StateSyncData_v13(", ")");

			unsigned char state_var0 = 0;
			Read<unsigned char>("state", handler, state_var0);

			unsigned char subState_var1 = 0;
			Read<unsigned char>("subState", handler, subState_var1);

			Vector3Short position_var2;
			Read<Vector3Short>("position", handler, position_var2);

			short rotation_var3 = 0;
			Read<short>("rotation", handler, rotation_var3);

			unsigned char animation3_var4 = 0;
			Read<unsigned char>("animation3", handler, animation3_var4);

			if (animation3_var4 > 127)
			{
				StackWatch<PacketHandler> watch_5(handler, "if animation3_var4 > 127");
				float unknown_var5 = 0;
				Read<float>("unknown", handler, unknown_var5);

				float unknown_var6 = 0;
				Read<float>("unknown", handler, unknown_var6);
			}

			Vector3Short speed_var7;
			Read<Vector3Short>("speed", handler, speed_var7);

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8);

			short rotation2Div10_var9 = 0;
			Read<short>("rotation2Div10", handler, rotation2Div10_var9);

			short coordsDiv1000_var10 = 0;
			Read<short>("coordsDiv1000", handler, coordsDiv1000_var10);

			unsigned char flags_var11 = 0;
			Read<unsigned char>("flags", handler, flags_var11);

			if (GetBit(flags_var11, 0) == 1)
			{
				StackWatch<PacketHandler> watch_22(handler, "if GetBit(flags_var11, 0) == 1");
				int unknown;
				Read<int>("unknownInt", handler, unknown);
			}

			if (GetBit(flags_var11, 1) == 1)
			{
				StackWatch<PacketHandler> watch_22(handler, "if GetBit(flags_var11, 1) == 1");
				int unknown;
				Read<int>("unknownInt", handler, unknown);
			}

			if (GetBit(flags_var11, 2) == 1)
			{
				StackWatch<PacketHandler> watch_22(handler, "if GetBit(flags_var11, 2) == 1");
				short unknown;
				Read<short>("unknownShort", handler, unknown);
			}

			if (GetBit(flags_var11, 3) == 1)
			{
				StackWatch<PacketHandler> watch_22(handler, "if GetBit(flags_var11, 3) == 1");
				std::wstring animationString_var18;
				Read<std::wstring>("animationString", handler, animationString_var18);
			}

			if (GetBit(flags_var11, 4) == 1)
			{
				StackWatch<PacketHandler> watch_16(handler, "if GetBit(flags_var11, 4) == 1");
				Vector3S unknown_var14;
				Read<Vector3S>("unknownVector", handler, unknown_var14);

				std::wstring unknown_var15;
				Read<std::wstring>("unknown", handler, unknown_var15);
			}

			if (GetBit(flags_var11, 5) == 1)
			{
				StackWatch<PacketHandler> watch_16(handler, "if GetBit(flags_var11, 5) == 1");

				short unknown1;
				Read<short>("unknownShort", handler, unknown1);

				short unknown2;
				Read<short>("unknownShort", handler, unknown2);

				std::wstring unknown_var15;
				Read<std::wstring>("unknown", handler, unknown_var15);
			}

			int unknown_var26 = 0;
			Read<int>("unknown", handler, unknown_var26);

			if (flags_var11 == 0 && (unknown_var8 & 0x10))
			{
				handler.PacketStream().HasRecentlyFailed = true;
				return;
				StackWatch<PacketHandler> watch_22(handler, "if flags_var11 == 0");

				Vector3Short unknown;
				Read<Vector3Short>("unknownVector", handler, unknown);

				std::wstring animationString_var18;
				WStringCharLen animationString_var18_wrapper = animationString_var18;

				Read<WStringCharLen>("animationString", handler, animationString_var18_wrapper);
			}
		}

		void ParseCharacterData_v13(PacketHandler& handler, Maple::Game::CharacterData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "CharacterData_v13(", ")");

			Read<long long>("accountId", handler, blockOutput.AccountId);
			Read<long long>("characterId", handler, blockOutput.CharacterId);
			Read<std::wstring>("name", handler, blockOutput.Name);
			Read<unsigned char>("gender", handler, blockOutput.Gender);

			ValidateValues(handler, "gender", blockOutput.Gender, (unsigned char)0, (unsigned char)1);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);
			Read<int>("mapId", handler, blockOutput.MapId);
			Read<int>("mapInstanceId", handler, blockOutput.MapInstanceId);

			int unknown_var9 = 0;
			Read<int>("unknown", handler, unknown_var9);
			Read<unsigned short>("level", handler, blockOutput.Level);
			Read<unsigned short>("channel", handler, blockOutput.Channel);
			Read<int>("jobCode", handler, blockOutput.JobCode);
			Read<int>("job", handler, blockOutput.Job);
			Read<int>("currentHp", handler, blockOutput.Hp.Current);
			Read<int>("maxHp", handler, blockOutput.Hp.Max);

			short unknown_var16 = 0;
			Read<short>("unknown", handler, unknown_var16);

			long long unknown_var17 = 0;
			Read<long long>("unknown", handler, unknown_var17);

			long long storageCooldown_var18 = 0;
			Read<long long>("storageCooldown", handler, storageCooldown_var18);

			blockOutput.StorageCooldown = (long)storageCooldown_var18;

			long long doctorCooldown_var19 = 0;
			Read<long long>("doctorCooldown", handler, doctorCooldown_var19);

			blockOutput.DoctorCooldown = (long)doctorCooldown_var19;

			Read<int>("returnMapId", handler, blockOutput.ReturnMapId);
			Read<Vector3S>("returnPosition", handler, blockOutput.ReturnPosition);
			Read<int>("gearScore", handler, blockOutput.GearScore);

			Color4I_BGRA skinColorPrimary_var23;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var23);

			blockOutput.SkinColor.Primary = (Color4I)skinColorPrimary_var23;

			Color4I_BGRA skinColorSecondary_var24;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var24);

			blockOutput.SkinColor.Secondary = (Color4I)skinColorSecondary_var24;

			long long creationTime_var25 = 0;
			Read<long long>("creationTime", handler, creationTime_var25);

			blockOutput.CreationTime = (long)creationTime_var25;

			Read<int>("combatTrophyCount", handler, blockOutput.CombatTrophyCount);
			Read<int>("adventureTrophyCount", handler, blockOutput.AdventureTrophyCount);
			Read<int>("lifestyleTrophyCount", handler, blockOutput.LifestyleTrophyCount);
			Read<long long>("guildId", handler, blockOutput.GuildId);
			Read<std::wstring>("guildName", handler, blockOutput.GuildName);
			Read<std::wstring>("guildMotto", handler, blockOutput.GuildMotto);
			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);

			unsigned char clubCount_var33 = 0;
			Read<unsigned char>("clubCount", handler, clubCount_var33);

			ResizeVector(handler, blockOutput.Clubs, clubCount_var33);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < clubCount_var33 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_34(handler, "blockOutput.Clubs[", i, "]"); 
				Read<bool>("hasClub", handler, blockOutput.Clubs[i].HasClub);

				ValidateValues(handler, "hasClub", blockOutput.Clubs[i].HasClub, (bool)0, (bool)1);

				if (blockOutput.Clubs[i].HasClub)
				{
					StackWatch<PacketHandler> watch_36(handler, "if blockOutput.Clubs[i].HasClub");
					Read<long long>("clubId", handler, blockOutput.Clubs[i].ClubId);
					Read<std::wstring>("clubName", handler, blockOutput.Clubs[i].ClubName);
				}
			}

			unsigned char unknown_var37 = 0;
			Read<unsigned char>("unknown", handler, unknown_var37);

			{
				StackWatch<PacketHandler> watch_40(handler, "blockOutput.Mastery");

				int placeholderMastery_var38 = 0;
				Read<int>("placeholderMastery", handler, placeholderMastery_var38);

				ValidateValues(handler, "placeholderMastery", placeholderMastery_var38, (int)0);

				Read<int>("fishingMastery", handler, blockOutput.Mastery.Fishing);
				Read<int>("performanceMastery", handler, blockOutput.Mastery.Performance);
				Read<int>("miningMastery", handler, blockOutput.Mastery.Mining);
				Read<int>("foragingMastery", handler, blockOutput.Mastery.Foraging);
				Read<int>("ranchingMastery", handler, blockOutput.Mastery.Ranching);
				Read<int>("farmingMastery", handler, blockOutput.Mastery.Farming);
				Read<int>("smithingMastery", handler, blockOutput.Mastery.Smithing);
				Read<int>("handicraftMastery", handler, blockOutput.Mastery.Handicraft);
				Read<int>("alchemyMastery", handler, blockOutput.Mastery.Alchemy);
				Read<int>("cookingMastery", handler, blockOutput.Mastery.Cooking);
				Read<int>("petTamingMastery", handler, blockOutput.Mastery.PetTaming);
			}
			Read<std::wstring>("username", handler, blockOutput.Username);
			Read<long long>("sessionId", handler, blockOutput.SessionId);

			int unknownCount_var52 = 0;
			Read<int>("unknownCount", handler, unknownCount_var52);

			ResizeVector(handler, blockOutput.UnknownItems, unknownCount_var52);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var52 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_56(handler, "blockOutput.UnknownItems[", i, "]"); 
				long long unknown_var53 = 0;
				Read<long long>("unknown", handler, unknown_var53);
			}

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			bool unknown_var55 = false;
			Read<bool>("unknown", handler, unknown_var55);

			ValidateValues(handler, "unknown", unknown_var55, (bool)0, (bool)1);

			long long birthday_var56 = 0;
			Read<long long>("birthday", handler, birthday_var56);

			blockOutput.Birthday = (long)birthday_var56;

			int unknown_var57 = 0;
			Read<int>("unknown", handler, unknown_var57);

			int unknown_var58 = 0;
			Read<int>("unknown", handler, unknown_var58);

			long long unknownTime_var59 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var59);
			Read<int>("prestigeLevel", handler, blockOutput.PrestigeLevel);

			long long unknownTime_var61 = 0;
			Read<long long>("unknownTime", handler, unknownTime_var61);

			int unknownCount2_var62 = 0;
			Read<int>("unknownCount2", handler, unknownCount2_var62);

			ResizeVector(handler, blockOutput.UnknownItems2, unknownCount2_var62);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount2_var62 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_67(handler, "blockOutput.UnknownItems2[", i, "]"); 
				long long unknown_var63 = 0;
				Read<long long>("unknown", handler, unknown_var63);
			}

			int unknownCount3_var64 = 0;
			Read<int>("unknownCount3", handler, unknownCount3_var64);

			ResizeVector(handler, blockOutput.UnknownItems3, unknownCount3_var64);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount3_var64 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_70(handler, "blockOutput.UnknownItems3[", i, "]"); 
				long long unknown_var65 = 0;
				Read<long long>("unknown", handler, unknown_var65);
			}

			short unknown_var66 = 0;
			Read<short>("unknown", handler, unknown_var66);

			long long unknown_var67 = 0;
			Read<long long>("unknown", handler, unknown_var67);
		}

		void ParseMountData_v13(PacketHandler& handler, Maple::Game::MountData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MountData_v13(", ")");

			Read<unsigned char>("rideMode", handler, blockOutput.RideMode);

			ValidateValues(handler, "rideMode", blockOutput.RideMode, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			Read<int>("mountId", handler, blockOutput.MountId);
			Read<int>("mountObjectId", handler, blockOutput.MountObjectId);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			ValidateValues(handler, "unknown", unknown_var3, (unsigned char)0);

			if (blockOutput.RideMode == (Enum::RideMode)1)
			{
				StackWatch<PacketHandler> watch_4(handler, "if blockOutput.RideMode == (Enum::RideMode)1");
				Read<int>("itemId", handler, blockOutput.ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
				ParseItemUgc_v12(handler, blockOutput.Ugc);
			}

			if (blockOutput.RideMode == (Enum::RideMode)2)
			{
				StackWatch<PacketHandler> watch_8(handler, "if blockOutput.RideMode == (Enum::RideMode)2");
				Read<int>("effectId", handler, blockOutput.EffectId);
				Read<short>("effectLevel", handler, blockOutput.EffectLevel);
			}

			unsigned char count_var8 = 0;
			Read<unsigned char>("count", handler, count_var8);

			ResizeVector(handler, blockOutput.UnknownData, count_var8);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_12(handler, "blockOutput.UnknownData[", i, "]"); 
				int unknown_var9 = 0;
				Read<int>("unknown", handler, unknown_var9);

				unsigned char unknown_var10 = 0;
				Read<unsigned char>("unknown", handler, unknown_var10);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemBadge_v2486(", ")");

			unsigned char unknown_var0 = 0;
			Read<unsigned char>("unknown", handler, unknown_var0);

			ValidateValues(handler, "unknown", unknown_var0, (unsigned char)1);

			Read<unsigned char>("type", handler, blockOutput.Type);

			ValidateValues(handler, "type", blockOutput.Type, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			Read<int>("id", handler, blockOutput.BadgeId);

			if (blockOutput.Type == (Enum::BadgeType)1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if blockOutput.Type == (Enum::BadgeType)1");
				ParseItemBadgeTransparency_v12(handler, blockOutput);
			}

			if (blockOutput.Type == (Enum::BadgeType)11)
			{
				StackWatch<PacketHandler> watch_5(handler, "if blockOutput.Type == (Enum::BadgeType)11");
				Read<int>("petSkinId", handler, blockOutput.PetSkinId);
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

				StackWatch<PacketHandler> watch_block(handler, "ItemData_v2486(", "itemId: ", itemId_param0, ")");

			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			ValidateValues(handler, "unknown", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);
			ParseItemHeader_v12(handler, blockOutput);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				StackWatch<PacketHandler> watch_5(handler, "blockOutput.Stats");
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Constant);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Static);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Random);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Title);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment1);
			}
			ParseItemEnchantment_v12(handler, blockOutput.Enchantment);

			{
				StackWatch<PacketHandler> watch_12(handler, "blockOutput.LimitBreak");

				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level);

				{
					StackWatch<PacketHandler> watch_14(handler, "blockOutput.LimitBreak.Stats");

					int statCount_var4 = 0;
					Read<int>("statCount", handler, statCount_var4);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_16(handler, "blockOutput.LimitBreak.Stats.Basic[", i, "]"); 
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var4);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_19(handler, "blockOutput.LimitBreak.Stats.Special[", i, "]"); 
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var5 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var5 = handler.GetItemExtraDataType(itemId_param0);

				CalledFunction(handler, "GetItemExtraDataType", "extraDataType_var5", extraDataType_var5, itemId_param0);
			}

			ValidateValues(handler, "extraDataType", extraDataType_var5, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var5 == 1)
			{
				StackWatch<PacketHandler> watch_23(handler, "if extraDataType_var5 == 1");
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var5 == 2)
			{
				StackWatch<PacketHandler> watch_26(handler, "if extraDataType_var5 == 2");
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var5 == 3)
			{
				StackWatch<PacketHandler> watch_28(handler, "if extraDataType_var5 == 3");
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var5 == 4)
			{
				StackWatch<PacketHandler> watch_30(handler, "if extraDataType_var5 == 4");
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

				StackWatch<PacketHandler> watch_block(handler, "EquipmentData_v2486(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("slot", handler, blockOutput.Slot);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentItems_v2486(", ")");

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0);

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Equipment[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentBadges_v2486(", ")");

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0);

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Badges[", i, "]"); 
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot);
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity);

				ValidateValues(handler, "rarity", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkins_v2486(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasSkin");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3);

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentFashion_v2486(", ")");

			Read<bool>("hasFashion", handler, blockOutput.HasFashion);

			ValidateValues(handler, "hasFashion", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFashion");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3);

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Fashion[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkinsMandatory_v2486(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			long long unknown_var1 = 0;
			Read<long long>("unknown", handler, unknown_var1);

			long long unknown_var2 = 0;
			Read<long long>("unknown", handler, unknown_var2);

			unsigned char skinCount_var3 = 0;
			Read<unsigned char>("skinCount", handler, skinCount_var3);

			ResizeVector(handler, blockOutput.Skins, skinCount_var3);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_4(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterListEntry_v2486(", ")");

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime);
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

				StackWatch<PacketHandler> watch_block(handler, "MailAttachData_v2486(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("index", handler, blockOutput.Index);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "MailData_v2486(", ")");

			Read<unsigned char>("type", handler, blockOutput.Type);

			ValidateValues(handler, "type", blockOutput.Type, (unsigned char)1, (unsigned char)106, (unsigned char)2, (unsigned char)101, (unsigned char)102, (unsigned char)112, (unsigned char)104, (unsigned char)107, (unsigned char)200);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId);
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId);
			Read<std::wstring>("senderName", handler, blockOutput.SenderName);
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle);
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent);
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey);
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue);

			if (blockOutput.Type == 200)
			{
				StackWatch<PacketHandler> watch_8(handler, "if blockOutput.Type == 200");
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8);

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "blockOutput.Ads[", i, "]"); 
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9);

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10);

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11);
			}

			else
			{
				StackWatch<PacketHandler> watch_15(handler, "else");
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12);

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_17(handler, "blockOutput.AttachedItems[", i, "]"); 
					ParseMailAttachData_v2486(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos);
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp);
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets);

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16);
			Read<long long>("redMerets", handler, blockOutput.RedMerets);

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18);

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19);

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_26(handler, "blockOutput.Ads[", i, "]"); 
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22);

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23);
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime);
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime);
			Read<long long>("sentTime", handler, blockOutput.SentTime);

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27);
		}

		void ParseMeretShopPremiumItem_v2486(PacketHandler& handler, Maple::Game::MeretShopPremiumItemData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MeretShopPremiumItem_v2486(", ")");

			Read<int>("entryId", handler, blockOutput.EntryId);

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1);
			Read<std::wstring>("name", handler, blockOutput.Name);

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3);

			ValidateValues(handler, "unknown", unknown_var3, (bool)0, (bool)1);

			Read<int>("parentId", handler, blockOutput.ParentId);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7);
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel);
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType);
			Read<long long>("price", handler, blockOutput.Price);
			Read<long long>("SalePrice", handler, blockOutput.SalePrice);

			unsigned char unknown_var12 = 0;
			Read<unsigned char>("unknown", handler, unknown_var12);
			Read<long long>("sellBeginTime", handler, blockOutput.SellBeginTime);
			Read<long long>("sellEndTime", handler, blockOutput.SellEndTime);

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15);

			int unknown_var16 = 0;
			Read<int>("unknown", handler, unknown_var16);
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable);

			ValidateValues(handler, "restockUnavailable", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var18 = 0;
			Read<int>("unknown", handler, unknown_var18);

			unsigned char unknown_var19 = 0;
			Read<unsigned char>("unknown", handler, unknown_var19);
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel);
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel);
			Read<int>("requiredJob", handler, blockOutput.RequiredJob);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount);
			Read<int>("itemDuration", handler, blockOutput.ItemDuration);
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity);
			Read<int>("tabId", handler, blockOutput.TabId);

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29);

			int unknown_var30 = 0;
			Read<int>("unknown", handler, unknown_var30);

			unsigned char unknown_var31 = 0;
			Read<unsigned char>("unknown", handler, unknown_var31);
			Read<int>("marketBannerLabel", handler, blockOutput.MarketBannerLabel);
			Read<std::string>("bannerName", handler, blockOutput.BannerName);

			std::string unknown_var34;
			Read<std::string>("unknown", handler, unknown_var34);

			bool unknown_var35 = false;
			Read<bool>("unknown", handler, unknown_var35);

			ValidateValues(handler, "unknown", unknown_var35, (bool)0, (bool)1);

			int unknown_var36 = 0;
			Read<int>("unknown", handler, unknown_var36);

			bool unknown_var37 = false;
			Read<bool>("unknown", handler, unknown_var37);

			ValidateValues(handler, "unknown", unknown_var37, (bool)0, (bool)1);

			Read<int>("requiredAchievementId", handler, blockOutput.RequiredAchievementId);
			Read<int>("requiredAchievementRank", handler, blockOutput.RequiredAchievementRank);

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);

			bool unknown_var41 = false;
			Read<bool>("unknown", handler, unknown_var41);

			ValidateValues(handler, "unknown", unknown_var41, (bool)0, (bool)1);

			int unknown_var42 = 0;
			Read<int>("unknown", handler, unknown_var42);
		}

		void ParseMeretShopPremiumItemEntry_v2486(PacketHandler& handler, Maple::Game::MeretShopPremiumItemEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "MeretShopPremiumItemEntry_v2486(", ")");

			Read<int>("entryId", handler, blockOutput.EntryId);

			unsigned char unknown_var1 = 0;
			Read<unsigned char>("unknown", handler, unknown_var1);
			Read<std::wstring>("name", handler, blockOutput.Name);

			bool unknown_var3 = false;
			Read<bool>("unknown", handler, unknown_var3);

			ValidateValues(handler, "unknown", unknown_var3, (bool)0, (bool)1);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);
			Read<unsigned char>("marketItemLabel", handler, blockOutput.MarketItemLabel);
			Read<unsigned char>("currencyType", handler, blockOutput.CurrencyType);
			Read<long long>("price", handler, blockOutput.Price);
			Read<long long>("SalePrice", handler, blockOutput.SalePrice);

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11);

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12);

			int unknown_var13 = 0;
			Read<int>("unknown", handler, unknown_var13);
			Read<bool>("restockUnavailable", handler, blockOutput.RestockUnavailable);

			ValidateValues(handler, "restockUnavailable", blockOutput.RestockUnavailable, (bool)0, (bool)1);

			int unknown_var15 = 0;
			Read<int>("unknown", handler, unknown_var15);

			unsigned char unknown_var16 = 0;
			Read<unsigned char>("unknown", handler, unknown_var16);
			Read<short>("requiredMinLevel", handler, blockOutput.RequiredMinLevel);
			Read<short>("requiredMaxLevel", handler, blockOutput.RequiredMaxLevel);
			Read<int>("requiredJob", handler, blockOutput.RequiredJob);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<int>("amount", handler, blockOutput.Amount);
			Read<int>("itemDuration", handler, blockOutput.ItemDuration);
			Read<int>("bonusQuantity", handler, blockOutput.BonusQuantity);
			Read<int>("tabId", handler, blockOutput.TabId);

			int unknown_var26 = 0;
			Read<int>("unknown", handler, unknown_var26);

			bool unknown_var27 = false;
			Read<bool>("unknown", handler, unknown_var27);

			ValidateValues(handler, "unknown", unknown_var27, (bool)0, (bool)1);

			int unknown_var28 = 0;
			Read<int>("unknown", handler, unknown_var28);

			unsigned char unknown_var29 = 0;
			Read<unsigned char>("unknown", handler, unknown_var29);

			int unknown_var30 = 0;
			Read<int>("unknown", handler, unknown_var30);

			unsigned char count_var31 = 0;
			Read<unsigned char>("count", handler, count_var31);

			ResizeVector(handler, blockOutput.AdditionalQuantities, count_var31);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var31 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_32(handler, "blockOutput.AdditionalQuantities[", i, "]"); 
				Read<bool>("hasEntry", handler, blockOutput.AdditionalQuantities[i].HasEntry);

				ValidateValues(handler, "hasEntry", blockOutput.AdditionalQuantities[i].HasEntry, (bool)0, (bool)1);

				if (blockOutput.AdditionalQuantities[i].HasEntry)
				{
					StackWatch<PacketHandler> watch_34(handler, "if blockOutput.AdditionalQuantities[i].HasEntry");
					ParseMeretShopPremiumItem_v2486(handler, blockOutput.AdditionalQuantities[i].EntryData);

					Read<bool>("hasUnknown", handler, blockOutput.AdditionalQuantities[i].HasUnknown);

					ValidateValues(handler, "hasUnknown", blockOutput.AdditionalQuantities[i].HasUnknown, (bool)0, (bool)1);

					if (blockOutput.AdditionalQuantities[i].HasUnknown)
					{
						StackWatch<PacketHandler> watch_37(handler, "if blockOutput.AdditionalQuantities[i].HasUnknown");
						std::string unknown_var34;
						Read<std::string>("unknown", handler, unknown_var34);

						long long unknown_var35 = 0;
						Read<long long>("unknown", handler, unknown_var35);

						long long unknown_var36 = 0;
						Read<long long>("unknown", handler, unknown_var36);
					}

					unsigned char unknown_var37 = 0;
					Read<unsigned char>("unknown", handler, unknown_var37);

					bool unknown_var38 = false;
					Read<bool>("unknown", handler, unknown_var38);

					ValidateValues(handler, "unknown", unknown_var38, (bool)0, (bool)1);
				}
			}
		}

		void ParseBlackMarketEntryData_v2486(PacketHandler& handler, Maple::Game::BlackMarketEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "BlackMarketEntryData_v2486(", ")");

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId);
			Read<long long>("timeListed", handler, blockOutput.TimeListed);
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2);
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires);
			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem);

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId);
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

				StackWatch<PacketHandler> watch_block(handler, "FieldPetData_v2486(", ")");

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet);

			ValidateValues(handler, "hasFieldPet", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFieldPet");
				Read<int>("itemId", handler, blockOutput.ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Rarity);

				ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillTreeData_v2493(", ")");

			Read<int>("job", handler, blockOutput.Job);

			unsigned char unknownCount_var1 = 0;
			Read<unsigned char>("unknownCount", handler, unknownCount_var1);

			ValidateValues(handler, "unknownCount", unknownCount_var1, (unsigned char)1);

			Read<int>("jobCode", handler, blockOutput.JobCode);
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

				StackWatch<PacketHandler> watch_block(handler, "BasicStat_v2497(", ")");

			Read<short>("type", handler, blockOutput.Type);
			Read<int>("value", handler, blockOutput.Value);
		}

		void ParseSpecialStat_v2497(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "SpecialStat_v2497(", ")");

			Read<short>("type", handler, blockOutput.Type);
			Read<int>("value", handler, blockOutput.Value);

			bool dummy_var2 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				dummy_var2 = handler.StatIntToFloat(blockOutput.Value);

				CalledFunction(handler, "StatIntToFloat", "dummy_var2", dummy_var2, blockOutput.Value);
			}

			ValidateValues(handler, "dummy", dummy_var2, (bool)0, (bool)1);
		}

		void ParseBasicAndSpecialStats_v2497(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "BasicAndSpecialStats_v2497(", ")");

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0);

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Basic[", i, "]"); 
				ParseBasicStat_v2497(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0);

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < statCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_4(handler, "blockOutput.Special[", i, "]"); 
				ParseSpecialStat_v2497(handler, blockOutput.Special[i]);
			}

			Read<int>("empowermentItemId", handler, blockOutput.EmpowermentItemId);
		}

		void ParseItemData_v2497(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "ItemData_v2497(", "itemId: ", itemId_param0, ")");

			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			ValidateValues(handler, "unknown", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);
			ParseItemHeader_v12(handler, blockOutput);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				StackWatch<PacketHandler> watch_5(handler, "blockOutput.Stats");
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Static);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Random);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Empowerment1);
			}

			{
				StackWatch<PacketHandler> watch_9(handler, "blockOutput.Enchantment");
				ParseItemEnchantmentHeader_v12(handler, blockOutput.Enchantment);

				unsigned char basicStatCount_var3 = 0;
				Read<unsigned char>("basicStatCount", handler, basicStatCount_var3);

				ResizeVector(handler, blockOutput.Enchantment.Basic, basicStatCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < basicStatCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_12(handler, "blockOutput.Enchantment.Basic[", i, "]"); 
					Read<int>("type", handler, blockOutput.Enchantment.Basic[i].Type);
					Read<int>("value", handler, blockOutput.Enchantment.Basic[i].Value);
				}
			}

			{
				StackWatch<PacketHandler> watch_15(handler, "blockOutput.LimitBreak");
				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level);

				{
					StackWatch<PacketHandler> watch_17(handler, "blockOutput.LimitBreak.Stats");

					int statCount_var7 = 0;
					Read<int>("statCount", handler, statCount_var7);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var7);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_19(handler, "blockOutput.LimitBreak.Stats.Basic[", i, "]"); 
						ParseBasicStat_v2497(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var7);

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var7);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < statCount_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_22(handler, "blockOutput.LimitBreak.Stats.Special[", i, "]"); 
						ParseSpecialStat_v2497(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var8 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				extraDataType_var8 = handler.GetItemExtraDataType(itemId_param0);

				CalledFunction(handler, "GetItemExtraDataType", "extraDataType_var8", extraDataType_var8, itemId_param0);
			}

			ValidateValues(handler, "extraDataType", extraDataType_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var8 == 1)
			{
				StackWatch<PacketHandler> watch_26(handler, "if extraDataType_var8 == 1");
				ParseItemUgc_v12(handler, blockOutput.Ugc);
				ParseItemBlueprint_v12(handler, blockOutput.Blueprint);
			}

			if (extraDataType_var8 == 2)
			{
				StackWatch<PacketHandler> watch_29(handler, "if extraDataType_var8 == 2");
				ParseItemPet_v12(handler, blockOutput.Pet);
			}

			if (extraDataType_var8 == 3)
			{
				StackWatch<PacketHandler> watch_31(handler, "if extraDataType_var8 == 3");
				ParseItemMusic_v12(handler, blockOutput.Music);
			}

			if (extraDataType_var8 == 4)
			{
				StackWatch<PacketHandler> watch_33(handler, "if extraDataType_var8 == 4");
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

				StackWatch<PacketHandler> watch_block(handler, "EquipmentData_v2497(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("slot", handler, blockOutput.Slot);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentItems_v2497(", ")");

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0);

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Equipment[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentBadges_v2497(", ")");

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0);

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Badges[", i, "]"); 
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot);
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity);

				ValidateValues(handler, "rarity", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkins_v2497(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasSkin");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3);

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentFashion_v2497(", ")");

			Read<bool>("hasFashion", handler, blockOutput.HasFashion);

			ValidateValues(handler, "hasFashion", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFashion");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3);

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Fashion[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterListEntry_v2497(", ")");

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsSpecialStats_v2497(", ")");

			int specialStatCount_var0 = 0;
			Read<int>("specialStatCount", handler, specialStatCount_var0);

			ResizeVector(handler, blockOutput.Special, specialStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < specialStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Special[", i, "]"); 
				Read<short>("type", handler, blockOutput.Special[i].Type);
				Read<int>("value", handler, blockOutput.Special[i].Value);

				bool dummy_var3 = false;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					dummy_var3 = handler.StatIntToFloat(blockOutput.Special[i].Value);

					CalledFunction(handler, "StatIntToFloat", "dummy_var3", dummy_var3, blockOutput.Special[i].Value);
				}

				ValidateValues(handler, "dummy", dummy_var3, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "MailAttachData_v2497(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("index", handler, blockOutput.Index);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<int>("amount", handler, blockOutput.Amount);

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			long long unknown_var7 = 0;
			Read<long long>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "MailData_v2497(", ")");

			Read<unsigned char>("type", handler, blockOutput.Type);

			ValidateValues(handler, "type", blockOutput.Type, (unsigned char)1, (unsigned char)106, (unsigned char)2, (unsigned char)101, (unsigned char)102, (unsigned char)112, (unsigned char)104, (unsigned char)107, (unsigned char)200);

			Read<long long>("mailInstanceId", handler, blockOutput.MailInstanceId);
			Read<long long>("senderCharacterId", handler, blockOutput.SenderCharacterId);
			Read<std::wstring>("senderName", handler, blockOutput.SenderName);
			Read<std::wstring>("mailTitle", handler, blockOutput.MailTitle);
			Read<std::wstring>("mailContent", handler, blockOutput.MailContent);
			Read<std::wstring>("metadataKey", handler, blockOutput.MetadataKey);
			Read<std::wstring>("metadataValue", handler, blockOutput.MetadataValue);

			if (blockOutput.Type == 200)
			{
				StackWatch<PacketHandler> watch_8(handler, "if blockOutput.Type == 200");
				unsigned char adCount_var8 = 0;
				Read<unsigned char>("adCount", handler, adCount_var8);

				ResizeVector(handler, blockOutput.Ads, adCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < adCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "blockOutput.Ads[", i, "]"); 
					ParseMailAdData_v12(handler, blockOutput.Ads[i]);
				}

				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9);

				long long unknown_var10 = 0;
				Read<long long>("unknown", handler, unknown_var10);

				unsigned char unknown_var11 = 0;
				Read<unsigned char>("unknown", handler, unknown_var11);
			}

			else
			{
				StackWatch<PacketHandler> watch_15(handler, "else");
				unsigned char attachCount_var12 = 0;
				Read<unsigned char>("attachCount", handler, attachCount_var12);

				ResizeVector(handler, blockOutput.AttachedItems, attachCount_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < attachCount_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_17(handler, "blockOutput.AttachedItems[", i, "]"); 
					ParseMailAttachData_v2497(handler, blockOutput.AttachedItems[i]);
				}
			}

			Read<long long>("mesos", handler, blockOutput.Mesos);
			Read<long long>("lastPurchaseTimestamp", handler, blockOutput.LastPurchaseTimestamp);
			Read<long long>("blueMerets", handler, blockOutput.BlueMerets);

			long long unknown_var16 = 0;
			Read<long long>("unknown", handler, unknown_var16);
			Read<long long>("redMerets", handler, blockOutput.RedMerets);

			long long unknown_var18 = 0;
			Read<long long>("unknown", handler, unknown_var18);

			unsigned char count_var19 = 0;
			Read<unsigned char>("count", handler, count_var19);

			ResizeVector(handler, blockOutput.Ads, count_var19);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var19 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_26(handler, "blockOutput.Ads[", i, "]"); 
				unsigned char unknown_var20 = 0;
				Read<unsigned char>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				long long unknown_var22 = 0;
				Read<long long>("unknown", handler, unknown_var22);

				long long unknown_var23 = 0;
				Read<long long>("unknown", handler, unknown_var23);
			}
			Read<long long>("readTime", handler, blockOutput.ReadTime);
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime);
			Read<long long>("sentTime", handler, blockOutput.SentTime);

			std::wstring unkown_var27;
			Read<std::wstring>("unkown", handler, unkown_var27);
		}

		void ParseBlackMarketEntryData_v2497(PacketHandler& handler, Maple::Game::BlackMarketEntryData& blockOutput)
		{
			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}

			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "BlackMarketEntryData_v2497(", ")");

			Read<long long>("listingInstanceId", handler, blockOutput.ListingInstanceId);
			Read<long long>("timeListed", handler, blockOutput.TimeListed);
			Read<long long>("timeListed2", handler, blockOutput.TimeListed2);
			Read<long long>("timeExpires", handler, blockOutput.TimeExpires);
			Read<int>("amount", handler, blockOutput.Amount);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);
			Read<long long>("costPerItem", handler, blockOutput.CostPerItem);

			unsigned char unknown_var7 = 0;
			Read<unsigned char>("unknown", handler, unknown_var7);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<unsigned char>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

			Read<long long>("listerAccountId", handler, blockOutput.ListerAccountId);
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

				StackWatch<PacketHandler> watch_block(handler, "FieldPetData_v2497(", ")");

			Read<bool>("hasFieldPet", handler, blockOutput.HasFieldPet);

			ValidateValues(handler, "hasFieldPet", blockOutput.HasFieldPet, (bool)0, (bool)1);

			if (blockOutput.HasFieldPet)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFieldPet");
				Read<int>("itemId", handler, blockOutput.ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Rarity);

				ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "EquipmentData_v2509(", ")");

			Read<int>("itemId", handler, blockOutput.ItemId);
			Read<long long>("itemInstanceId", handler, blockOutput.ItemInstanceId);
			Read<unsigned char>("slot", handler, blockOutput.Slot);
			Read<int>("rarity", handler, blockOutput.Rarity);

			ValidateValues(handler, "rarity", blockOutput.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentItems_v2509(", ")");

			unsigned char equipmentCount_var0 = 0;
			Read<unsigned char>("equipmentCount", handler, equipmentCount_var0);

			ResizeVector(handler, blockOutput.Equipment, equipmentCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < equipmentCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Equipment[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentBadges_v2509(", ")");

			unsigned char badgeCount_var0 = 0;
			Read<unsigned char>("badgeCount", handler, badgeCount_var0);

			ResizeVector(handler, blockOutput.Badges, badgeCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < badgeCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Badges[", i, "]"); 
				Read<unsigned char>("slot", handler, blockOutput.Badges[i].Slot);
				Read<int>("itemId", handler, blockOutput.Badges[i].ItemId);
				Read<long long>("itemInstanceId", handler, blockOutput.Badges[i].ItemInstanceId);
				Read<int>("rarity", handler, blockOutput.Badges[i].Rarity);

				ValidateValues(handler, "rarity", blockOutput.Badges[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentSkins_v2509(", ")");

			Read<bool>("hasSkin", handler, blockOutput.HasSkin);

			ValidateValues(handler, "hasSkin", blockOutput.HasSkin, (bool)0, (bool)1);

			if (blockOutput.HasSkin)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasSkin");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char skinCount_var3 = 0;
				Read<unsigned char>("skinCount", handler, skinCount_var3);

				ResizeVector(handler, blockOutput.Skins, skinCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < skinCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Skins[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterEquipmentFashion_v2509(", ")");

			Read<bool>("hasFashion", handler, blockOutput.HasFashion);

			ValidateValues(handler, "hasFashion", blockOutput.HasFashion, (bool)0, (bool)1);

			if (blockOutput.HasFashion)
			{
				StackWatch<PacketHandler> watch_1(handler, "if blockOutput.HasFashion");
				long long unknown_var1 = 0;
				Read<long long>("unknown", handler, unknown_var1);

				long long unknown_var2 = 0;
				Read<long long>("unknown", handler, unknown_var2);

				unsigned char fashionCount_var3 = 0;
				Read<unsigned char>("fashionCount", handler, fashionCount_var3);

				ResizeVector(handler, blockOutput.Fashion, fashionCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < fashionCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "blockOutput.Fashion[", i, "]"); 
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterListEntry_v2509(", ")");

			ParseCharacterData_v13(handler, blockOutput.Character);

			Read<std::wstring>("profileUrl", handler, blockOutput.ProfileUrl);
			Read<long long>("deleteTime", handler, blockOutput.DeleteTime);
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

				StackWatch<PacketHandler> watch_block(handler, "CharacterDetailsBasicStats_v2509(", ")");

			unsigned char basicStatCount_var0 = 35;

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("max", handler, blockOutput.Basic[i].Max);
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("base", handler, blockOutput.Basic[i].Base);
			}

			ResizeVector(handler, blockOutput.Basic, basicStatCount_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < basicStatCount_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_5(handler, "blockOutput.Basic[", i, "]"); 
				Read<long long>("current", handler, blockOutput.Basic[i].Current);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillTreePageData_v2509(", ")");

			unsigned char count_var0 = 0;
			Read<unsigned char>("count", handler, count_var0);

			ResizeVector(handler, blockOutput.Skills, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_1(handler, "blockOutput.Skills[", i, "]"); 
				Read<int>("skillId", handler, blockOutput.Skills[i].SkillId);
				Read<int>("skillLevel", handler, blockOutput.Skills[i].SkillLevel);
				Read<bool>("beginnerSkill", handler, blockOutput.Skills[i].BeginnerSkill);

				ValidateValues(handler, "beginnerSkill", blockOutput.Skills[i].BeginnerSkill, (bool)0, (bool)1);

				Read<bool>("enabled", handler, blockOutput.Skills[i].Enabled);

				ValidateValues(handler, "enabled", blockOutput.Skills[i].Enabled, (bool)0, (bool)1);

				Read<bool>("notify", handler, blockOutput.Skills[i].Notify);

				ValidateValues(handler, "notify", blockOutput.Skills[i].Notify, (bool)0, (bool)1);
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

				StackWatch<PacketHandler> watch_block(handler, "SkillTreeData_v2509(", ")");

			Read<int>("jobTier", handler, blockOutput.JobTier);
			Read<int>("jobCode", handler, blockOutput.JobCode);
			ParseSkillTreePageData_v2509(handler, blockOutput.Active);
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x1 'ResponseVersion' v12");

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", handler, output0.Version);
			Read<unsigned short>("feature", handler, output0.Feature);
			Read<unsigned short>("locale", handler, output0.Locale);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0xa 'ResponseHeartbeat' v12");

			Client::ResponseHeartbeatPacket output0;

			Read<int>("serverTick", handler, output0.ServerTick);
			Read<int>("clientTick", handler, output0.ClientTick);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x2 'Handshake' v12");

			Client::HandshakePacket output0;

			Read<unsigned char>("function", handler, output0.Function);

			int count_var1 = 0;
			Read<int>("count", handler, count_var1);

			ResizeVector(handler, output0.Data, count_var1);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "output0.Data[", i, "]"); 
				Read<std::wstring>("unknown", handler, output0.Data[i].String);

				long long unknown_var3 = 0;
				Read<long long>("unknown", handler, unknown_var3);
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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x3 'LogIn' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Client::LogInPacket output0;

				Read<std::wstring>("username", handler, output0.Username);
				Read<std::wstring>("password", handler, output0.Password);

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3);
				Read<unsigned long long>("machineLow", handler, output0.MachineLow);
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh);

				int unknownMachineIdPtr_var6 = 0;
				Read<int>("unknownMachineIdPtr", handler, unknownMachineIdPtr_var6);
				Read<int>("sessionKey", handler, output0.SessionKey);
				Read<std::string>("locale", handler, output0.Locale);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::LogInPacket>(output0);
				}


				return;
			}

			if (mode_var0 != 0)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 != 0");
				Client::LogInAuthTokenPacket output1;

				long long unknown_var9 = 0;
				Read<long long>("unknown", handler, unknown_var9);

				std::string authToken_var10;
				Read<std::string>("authToken", handler, authToken_var10);

				short unknown_var11 = 0;
				Read<short>("unknown", handler, unknown_var11);

				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12);
				Read<unsigned long long>("machineLow", handler, output1.MachineLow);
				Read<unsigned long long>("machineHigh", handler, output1.MachineHigh);

				int unknown_var15 = 0;
				Read<int>("unknown", handler, unknown_var15);

				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16);
				Read<std::string>("locale", handler, output1.Locale);

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x4 'ResponseKey' v12");

			Client::ResponseKeyPacket output0;

			Read<long long>("accountId", handler, output0.AccountId);

			if (output0.AccountId != (Enum::AccountId)0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if output0.AccountId != (Enum::AccountId)0");
				Read<int>("tokenA", handler, output0.TokenA);
				Read<int>("tokenB", handler, output0.TokenB);
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh);
				Read<unsigned long long>("machineLow", handler, output0.MachineLow);
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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0xd 'RequestQuit' v12");

			Client::RequestQuitPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)0, (unsigned char)1);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x5 'Reconnect' v12");

			Client::ReconnectPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1);

			Read<long long>("accountId", handler, output0.AccountId);
			Read<long long>("characterId", handler, output0.CharacterId);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3);

			int unknown_var4 = 0;
			Read<int>("unknown", handler, unknown_var4);

			std::wstring unknown_var5;
			Read<std::wstring>("unknown", handler, unknown_var5);

			int unknown_var6 = 0;
			Read<int>("unknown", handler, unknown_var6);

			std::string unknown_var7;
			Read<std::string>("unknown", handler, unknown_var7);

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x20 'Skill' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<int>("serverTick", handler, output0.ServerTick);
				Read<unsigned int>("skillId", handler, output0.SkillId);
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel);
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("direction", handler, output0.Direction);
				Read<Vector3S>("rotation", handler, output0.Rotation);

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9);

				ValidateValues(handler, "unknown", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick);

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11);

				ValidateValues(handler, "unknown", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12);

				ValidateValues(handler, "unknown", unknown_var12, (long long)0);

				Read<bool>("flag", handler, output0.Flag);

				ValidateValues(handler, "flag", output0.Flag, (bool)0, (bool)1);

				if (output0.Flag)
				{
					StackWatch<PacketHandler> watch_16(handler, "if output0.Flag");
					int unknown_var14 = 0;
					Read<int>("unknown", handler, unknown_var14);

					ValidateValues(handler, "unknown", unknown_var14, (int)0);

					std::string unknown_var15;
					Read<std::string>("unknown", handler, unknown_var15);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 1");
				unsigned char damageMode_var16 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var16);

				ValidateValues(handler, "damageMode", damageMode_var16, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var16 == 0)
				{
					StackWatch<PacketHandler> watch_21(handler, "if damageMode_var16 == 0");
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", handler, output1.SkillSn);
					Read<unsigned char>("attackPoint", handler, output1.AttackPoint);
					Read<Vector3S>("position", handler, output1.Position);
					Read<Vector3S>("rotation", handler, output1.Rotation);

					unsigned char count_var21 = 0;
					Read<unsigned char>("count", handler, count_var21);

					int unknown_var22 = 0;
					Read<int>("unknown", handler, unknown_var22);

					ValidateValues(handler, "unknown", unknown_var22, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var21);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char projectile_i = 0; projectile_i < count_var21 && !handler.PacketStream().HasRecentlyFailed; ++projectile_i)
					{
						StackWatch<PacketHandler> watch_29(handler, "output1.Projectiles[", projectile_i, "]"); 
						auto& projectile_array0 = output1.Projectiles[projectile_i];

						Read<long long>("skillAttack", handler, projectile_array0.SkillAttack);
						Read<int>("targetId", handler, projectile_array0.TargetId);
						Read<unsigned char>("index", handler, projectile_array0.Index);

						bool moreTargets_var26 = false;
						Read<bool>("moreTargets", handler, moreTargets_var26);

						ValidateValues(handler, "moreTargets", moreTargets_var26, (bool)0, (bool)1);

						size_t nextTarget_j = 0;

						while (moreTargets_var26 && !handler.PacketStream().HasRecentlyFailed)
						{
							StackWatch<PacketHandler> watch_34(handler, "projectile_array0.ChainTargets[", nextTarget_j, "]"); 
							projectile_array0.ChainTargets.push_back({});

							if (handler.PacketStream().HasRecentlyFailed)
							{
								return;
							}

							auto& nextTarget_array1 = projectile_array0.ChainTargets[nextTarget_j];

							Read<long long>("skillAttack", handler, nextTarget_array1.SkillAttack);
							Read<int>("targetId", handler, nextTarget_array1.TargetId);
							Read<unsigned char>("index", handler, nextTarget_array1.Index);

							unsigned char unknown_var30 = 0;
							Read<unsigned char>("unknown", handler, unknown_var30);

							Read<bool>("moreTargets", handler, moreTargets_var26);

							ValidateValues(handler, "moreTargets", moreTargets_var26, (bool)0, (bool)1);

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
					StackWatch<PacketHandler> watch_40(handler, "if damageMode_var16 == 1");
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", handler, output2.SkillSn);
					Read<long long>("skillAttack", handler, output2.SkillAttack);
					Read<Vector3S>("position", handler, output2.Position);
					Read<Vector3S>("hitPoint", handler, output2.HitPoint);
					Read<Vector3S>("rotation", handler, output2.Rotation);
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint);

					unsigned char count_var37 = 0;
					Read<unsigned char>("count", handler, count_var37);

					int unknown_var38 = 0;
					Read<int>("unknown", handler, unknown_var38);

					ValidateValues(handler, "unknown", unknown_var38, (int)0);

					ResizeVector(handler, output2.Hits, count_var37);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char hitActor_i = 0; hitActor_i < count_var37 && !handler.PacketStream().HasRecentlyFailed; ++hitActor_i)
					{
						StackWatch<PacketHandler> watch_50(handler, "output2.Hits[", hitActor_i, "]"); 
						auto& hitActor_array2 = output2.Hits[hitActor_i];

						Read<int>("entityId", handler, hitActor_array2.EntityId);

						unsigned char unknown_var40 = 0;
						Read<unsigned char>("unknown", handler, unknown_var40);

						ValidateValues(handler, "unknown", unknown_var40, (unsigned char)0);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);
					}


					return;
				}

				if (damageMode_var16 == 2)
				{
					StackWatch<PacketHandler> watch_53(handler, "if damageMode_var16 == 2");
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", handler, output3.SkillSn);
					Read<unsigned char>("attackPoint", handler, output3.AttackPoint);

					int unknown_var43 = 0;
					Read<int>("unknown", handler, unknown_var43);
					Read<int>("attackCounter", handler, output3.AttackCounter);
					Read<Vector3S>("position", handler, output3.Position);
					Read<Vector3S>("rotation", handler, output3.Rotation);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_61(handler, "if mode_var0 == 2");
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn);
				Read<unsigned int>("skillId", handler, output4.SkillId);
				Read<unsigned short>("skillLevel", handler, output4.SkillLevel);
				Read<unsigned char>("motionPoint", handler, output4.MotionPoint);
				Read<Vector3S>("position", handler, output4.Position);

				Vector3S unknown_var52;
				Read<Vector3S>("unknown", handler, unknown_var52);
				Read<Vector3S>("rotation", handler, output4.Rotation);

				Vector3S unknown_var54;
				Read<Vector3S>("unknown", handler, unknown_var54);

				bool unknown_var55 = false;
				Read<bool>("unknown", handler, unknown_var55);

				ValidateValues(handler, "unknown", unknown_var55, (bool)0, (bool)1);

				int unknown_var56 = 0;
				Read<int>("unknown", handler, unknown_var56);

				ValidateValues(handler, "unknown", unknown_var56, (int)0);

				unsigned char unknown_var57 = 0;
				Read<unsigned char>("unknown", handler, unknown_var57);

				ValidateValues(handler, "unknown", unknown_var57, (unsigned char)0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_74(handler, "if mode_var0 == 3");
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn);
				Read<int>("serverTick", handler, output5.ServerTick);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_78(handler, "if mode_var0 == 4");
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x21 'StateSkill' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Client::StateSkillPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<unsigned int>("serverTick", handler, output0.ServerTick);
				Read<unsigned int>("skillId", handler, output0.SkillId);
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel);

				ValidateValues(handler, "skillLevel", output0.SkillLevel, (unsigned short)1);

				Read<int>("animation", handler, output0.Animation);
				Read<int>("clientTick", handler, output0.ClientTick);

				long long unknown_var7 = 0;
				Read<long long>("unknown", handler, unknown_var7);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x22 'NpcTalk' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Client::NpcTalkClosePacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkClosePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 1");
				Client::NpcTalkBeginPacket output1;

				Read<int>("actorId", handler, output1.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkBeginPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 2");
				Client::NpcTalkContinuePacket output2;

				Read<int>("index", handler, output2.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 4");
				Client::NpcTalkEnchantUnknownPacket output3;

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantUnknownPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 6");
				Client::NpcTalkEnchantPacket output4;

				Read<int>("npcId", handler, output4.NpcId);
				Read<int>("scriptId", handler, output4.ScriptId);
				Read<short>("eventType", handler, output4.EventType);

				ValidateValues(handler, "eventType", output4.EventType, (short)1, (short)202, (short)2, (short)3);

				if (output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)1)
				{
					StackWatch<PacketHandler> watch_17(handler, "if output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)1");
					Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);
				}

				if (output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)202)
				{
					StackWatch<PacketHandler> watch_19(handler, "if output4.EventType == (Client::NpcTalkEnchantPacket::EventTypeEnum)202");
					short unknown_var8 = 0;
					Read<short>("unknown", handler, unknown_var8);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 7");
				Client::NpcTalkNextQuestPacket output5;

				Read<int>("questId", handler, output5.QuestId);
				Read<short>("eventType", handler, output5.EventType);

				ValidateValues(handler, "eventType", output5.EventType, (short)0, (short)2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkNextQuestPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 8");
				Client::NpcTalkAllianceQuestAcceptPacket output6;

				Read<int>("index", handler, output6.Index);
				Read<short>("eventType", handler, output6.EventType);

				ValidateValues(handler, "eventType", output6.EventType, (short)0, (short)2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 9");
				Client::NpcTalkAllianceQuestTalkPacket output7;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 11");
				Client::NpcTalkCinematicPacket output8;

				Read<int>("actorId", handler, output8.ActorId);
				Read<int>("index", handler, output8.Index);

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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0xb7 'SystemInfo' v12");

			Client::SystemInfoPacket output0;

			Read<std::wstring>("info", handler, output0.Info);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Client::SystemInfoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1 'RequestVersion' v12");

			Server::RequestVersionPacket output0;

			int ms2Version_var0 = 0;
			Read<int>("ms2Version", handler, ms2Version_var0);

			int localIV_var1 = 0;
			Read<int>("localIV", handler, localIV_var1);

			int remoteIV_var2 = 0;
			Read<int>("remoteIV", handler, remoteIV_var2);

			int blockIV_var3 = 0;
			Read<int>("blockIV", handler, blockIV_var3);

			unsigned char patchType_var4 = 0;
			Read<unsigned char>("patchType", handler, patchType_var4);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RequestVersionPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2 'VersionResult' v12");

			Server::VersionResultPacket output0;

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::VersionResultPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3 'PatchFile' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)5);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::PatchFileDeletePacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PatchFileDeletePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 2");
			}
			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 3");
				Server::PatchFileDownloadOnlinePacket output1;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output1.UnknownData, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output1.UnknownData[", i, "]"); 
					std::string unknown_var2;
					Read<std::string>("unknown", handler, unknown_var2);

					long long unknown_var3 = 0;
					Read<long long>("unknown", handler, unknown_var3);

					std::string unknown_var4;
					Read<std::string>("unknown", handler, unknown_var4);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PatchFileDownloadOnlinePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 5");
				Server::PatchFileDownloadPacketPacket output2;

				std::string unknown_var5;
				Read<std::string>("unknown", handler, unknown_var5);

				long long unknown_var6 = 0;
				Read<long long>("unknown", handler, unknown_var6);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				std::string unknown_var9;
				Read<std::string>("unknown", handler, unknown_var9);

				ResizeVector(handler, output2.UnknownData, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_18(handler, "output2.UnknownData[", i, "]"); 
					unsigned char unknown_var10 = 0;
					Read<unsigned char>("unknown", handler, unknown_var10);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PatchFileDownloadPacketPacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x4>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x4 'RequestKey' v12");

			Server::RequestKeyPacket output0;

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RequestKeyPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x5 'Reconnect' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				int unknown_var1 = 0;
				Read<int>("unknown", handler, unknown_var1);

				std::string unknownKey_var2;
				Read<std::string>("unknownKey", handler, unknownKey_var2);

				int key_var3 = 0;
				Read<int>("key", handler, key_var3);
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 1");
			}
			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 2");
				int code_var4 = 0;
				Read<int>("code", handler, code_var4);
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x6>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x6 'Ping' v12");

			Server::PingPacket output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::PingPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x7 'Reconnect7' v12");

			Server::Reconnect7Packet output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::Reconnect7Packet>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x48 'Buff' v12");

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			Read<int>("targetId", handler, output0.Effect.TargetId);
			Read<int>("instanceId", handler, output0.Effect.InstanceId);
			Read<int>("sourceId", handler, output0.Effect.SourceId);

			if (output0.Mode == (Server::BuffPacket::ModeEnum)0)
			{
				StackWatch<PacketHandler> watch_5(handler, "if output0.Mode == (Server::BuffPacket::ModeEnum)0");
				ParseEffectStats_v12(handler, output0.Effect.Stats);

				Read<bool>("enabled", handler, output0.Effect.Enabled);

				ValidateValues(handler, "enabled", output0.Effect.Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth);
			}

			if (output0.Mode == (Server::BuffPacket::ModeEnum)2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if output0.Mode == (Server::BuffPacket::ModeEnum)2");
				int flags_var6 = 0;
				Read<int>("flags", handler, flags_var6);

				output0.UpdateEffect = GetBit(flags_var6, 0);
				output0.UpdateShield = GetBit(flags_var6, 1);

				if (GetBit(flags_var6, 0) == 1)
				{
					StackWatch<PacketHandler> watch_11(handler, "if GetBit(flags_var6, 0) == 1");
					ParseEffectStats_v12(handler, output0.Effect.Stats);

					Read<bool>("enabled", handler, output0.Effect.Enabled);

					ValidateValues(handler, "enabled", output0.Effect.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var6, 1) == 1)
				{
					StackWatch<PacketHandler> watch_14(handler, "if GetBit(flags_var6, 1) == 1");
					Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x8>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x8 'FinalizeReconnect' v12");

			Server::FinalizeReconnectPacket output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0);

			int unknownKey_var1 = 0;
			Read<int>("unknownKey", handler, unknownKey_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FinalizeReconnectPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x9>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x9 'RequestLogin' v12");

			Server::RequestLoginPacket output0;

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RequestLoginPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x4a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x4a 'Job' v12");

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::JobPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xa>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xa 'LoginResult' v12");

			Server::LoginResultPacket output0;

			unsigned char code_var0 = 0;
			Read<unsigned char>("code", handler, code_var0);

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1);

			std::wstring banReason_var2;
			Read<std::wstring>("banReason", handler, banReason_var2);

			long long accountId_var3 = 0;
			Read<long long>("accountId", handler, accountId_var3);

			long long syncTime_var4 = 0;
			Read<long long>("syncTime", handler, syncTime_var4);

			int timeOffset_var5 = 0;
			Read<int>("timeOffset", handler, timeOffset_var5);

			unsigned char timeZone_var6 = 0;
			Read<unsigned char>("timeZone", handler, timeZone_var6);

			unsigned char mode_var7 = 0;
			Read<unsigned char>("mode", handler, mode_var7);

			ValidateValues(handler, "mode", mode_var7, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8);

			ValidateValues(handler, "unknown", unknown_var8, (int)0);

			long long unknown_var9 = 0;
			Read<long long>("unknown", handler, unknown_var9);

			ValidateValues(handler, "unknown", unknown_var9, (long long)0);

			if (mode_var7 == 1)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var7 == 1");
				long long timestamp_var10 = 0;
				Read<long long>("timestamp", handler, timestamp_var10);
			}

			if (mode_var7 == 2)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var7 == 2");
				long long timestamp_var11 = 0;
				Read<long long>("timestamp", handler, timestamp_var11);

				long long currentTimestamp_var12 = 0;
				Read<long long>("currentTimestamp", handler, currentTimestamp_var12);
			}

			int unknownStatus_var13 = 0;
			Read<int>("unknownStatus", handler, unknownStatus_var13);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::LoginResultPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xb 'ServerList' v12");

			Server::ServerListPacket output0;

			bool loadServers_var0 = false;
			Read<bool>("loadServers", handler, loadServers_var0);

			ValidateValues(handler, "loadServers", loadServers_var0, (bool)0, (bool)1);

			if (loadServers_var0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if loadServers_var0");
				int unknown_var1 = 0;
				Read<int>("unknown", handler, unknown_var1);

				std::wstring serverName_var2;
				Read<std::wstring>("serverName", handler, serverName_var2);

				unsigned char unknown_var3 = 0;
				Read<unsigned char>("unknown", handler, unknown_var3);

				short count_var4 = 0;
				Read<short>("count", handler, count_var4);

				ResizeVector(handler, output0.Servers, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output0.Servers[", i, "]"); 
					std::wstring ipAddress_var5;
					Read<std::wstring>("ipAddress", handler, ipAddress_var5);

					short port_var6 = 0;
					Read<short>("port", handler, port_var6);
				}

				int unknown_var7 = 0;
				Read<int>("unknown", handler, unknown_var7);

				short count2_var8 = 0;
				Read<short>("count2", handler, count2_var8);

				ResizeVector(handler, output0.Channels, count2_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count2_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_12(handler, "output0.Channels[", i, "]"); 
					short channel_var9 = 0;
					Read<short>("channel", handler, channel_var9);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ServerListPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x4c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x4c 'NpcTalk' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 1");
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId);
				Read<unsigned char>("flags", handler, output1.Flags);
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 2");
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags);
				Read<int>("actorId", handler, output2.ActorId);
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5);

				ValidateValues(handler, "actionMode", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					StackWatch<PacketHandler> watch_15(handler, "if actionMode_var5 == 1");
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6);
				}

				if (actionMode_var5 == 3)
				{
					StackWatch<PacketHandler> watch_17(handler, "if actionMode_var5 == 3");
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					StackWatch<PacketHandler> watch_20(handler, "if actionMode_var5 == 4");
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8);

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					StackWatch<PacketHandler> watch_24(handler, "if actionMode_var5 == 5");
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10);

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_27(handler, "output5.Items[", i, "]"); 
						Read<int>("itemId", handler, output5.Items[i].ItemId);
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

						ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount);
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
					StackWatch<PacketHandler> watch_32(handler, "if actionMode_var5 == 6");
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					StackWatch<PacketHandler> watch_35(handler, "if actionMode_var5 == 7");
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					StackWatch<PacketHandler> watch_38(handler, "if actionMode_var5 == 8");
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
					StackWatch<PacketHandler> watch_41(handler, "if actionMode_var5 == 9");
				}
				if (actionMode_var5 == 10)
				{
					StackWatch<PacketHandler> watch_42(handler, "if actionMode_var5 == 10");
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17);

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_46(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 8");
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20);
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_54(handler, "if mode_var0 == 9");
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc 'CharacterList' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Characters[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);
				Read<long long>("characterId", handler, output2.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
			}
			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId);
				Read<int>("messageId", handler, output3.MessageId);
				Read<long long>("deleteTime", handler, output3.DeleteTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);
				Read<int>("messageId", handler, output4.MessageId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 7");
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xd 'MoveResult' v12");

			Server::MoveResultPacket output0;

			unsigned char message_var0 = 0;
			Read<unsigned char>("message", handler, message_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::MoveResultPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xe>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xe 'LoginToGame' v12");

			Server::LoginToGamePacket output0;

			unsigned char message_var0 = 0;
			Read<unsigned char>("message", handler, message_var0);

			if (message_var0 == 0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if message_var0 == 0");
				int ipAddress_var1 = 0;
				Read<int>("ipAddress", handler, ipAddress_var1);

				short port_var2 = 0;
				Read<short>("port", handler, port_var2);

				long long migrationToken_var3 = 0;
				Read<long long>("migrationToken", handler, migrationToken_var3);

				int mapId_var4 = 0;
				Read<int>("mapId", handler, mapId_var4);
			}

			else
			{
				StackWatch<PacketHandler> watch_7(handler, "else");
				std::wstring messageString_var5;
				Read<std::wstring>("messageString", handler, messageString_var5);
			}

			if (message_var0 == 49)
			{
				StackWatch<PacketHandler> watch_9(handler, "if message_var0 == 49");
				long long unknown_var6 = 0;
				Read<long long>("unknown", handler, unknown_var6);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::LoginToGamePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xf>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xf 'GameToLogin' v12");

			Server::GameToLoginPacket output0;

			bool message_var0 = false;
			Read<bool>("message", handler, message_var0);

			ValidateValues(handler, "message", message_var0, (bool)0, (bool)1);

			if (message_var0 == 0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if message_var0 == 0");
				int ipAddress_var1 = 0;
				Read<int>("ipAddress", handler, ipAddress_var1);

				short port_var2 = 0;
				Read<short>("port", handler, port_var2);

				long long migrationToken_var3 = 0;
				Read<long long>("migrationToken", handler, migrationToken_var3);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::GameToLoginPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x10>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x10 'GameToGame' v12");

			Server::GameToGamePacket output0;

			bool message_var0 = false;
			Read<bool>("message", handler, message_var0);

			ValidateValues(handler, "message", message_var0, (bool)0, (bool)1);

			if (message_var0 == 0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if message_var0 == 0");
				int migrationTokenA_var1 = 0;
				Read<int>("migrationTokenA", handler, migrationTokenA_var1);

				int migrationTokenB_var2 = 0;
				Read<int>("migrationTokenB", handler, migrationTokenB_var2);

				int ipAddress_var3 = 0;
				Read<int>("ipAddress", handler, ipAddress_var3);

				short port_var4 = 0;
				Read<short>("port", handler, port_var4);

				int mapId_var5 = 0;
				Read<int>("mapId", handler, mapId_var5);

				unsigned char unknown_var6 = 0;
				Read<unsigned char>("unknown", handler, unknown_var6);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::GameToGamePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x11>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x11 'ResponseTimeSync' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::ResponseTimeSyncInitializePacket output0;

				int serverTick_var1 = 0;
				Read<int>("serverTick", handler, serverTick_var1);

				long long timestamp_var2 = 0;
				Read<long long>("timestamp", handler, timestamp_var2);

				int timeOffset_var3 = 0;
				Read<int>("timeOffset", handler, timeOffset_var3);

				unsigned char timezone_var4 = 0;
				Read<unsigned char>("timezone", handler, timezone_var4);

				int key_var5 = 0;
				Read<int>("key", handler, key_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ResponseTimeSyncInitializePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::ResponseTimeSyncResetFieldsPacket output1;

				int serverTick_var6 = 0;
				Read<int>("serverTick", handler, serverTick_var6);

				long long timestamp_var7 = 0;
				Read<long long>("timestamp", handler, timestamp_var7);

				int timeOffset_var8 = 0;
				Read<int>("timeOffset", handler, timeOffset_var8);

				unsigned char timezone_var9 = 0;
				Read<unsigned char>("timezone", handler, timezone_var9);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ResponseTimeSyncResetFieldsPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 2");
				Server::ResponseTimeSyncRequestPacket output2;

				int serverTick_var10 = 0;
				Read<int>("serverTick", handler, serverTick_var10);

				long long timestamp_var11 = 0;
				Read<long long>("timestamp", handler, timestamp_var11);

				int timeOffset_var12 = 0;
				Read<int>("timeOffset", handler, timeOffset_var12);

				unsigned char timezone_var13 = 0;
				Read<unsigned char>("timezone", handler, timezone_var13);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ResponseTimeSyncRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 3");
				Server::ResponseTimeSyncSetTimePacket output3;

				long long timestamp_var14 = 0;
				Read<long long>("timestamp", handler, timestamp_var14);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ResponseTimeSyncSetTimePacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x52>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x52 'Shop' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11, (unsigned char)12, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output1.Items[", i, "]"); 
					Read<int>("entryId", handler, output1.Items[i].EntryId);
					Read<int>("itemId", handler, output1.Items[i].ItemId);
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
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 2");
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId);
				Read<int>("buyCount", handler, output2.BuyCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 4");
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId);
				Read<int>("buyCount", handler, output3.BuyCount);
				Read<int>("totalPrice", handler, output3.TotalPrice);
				Read<unsigned char>("fontColor", handler, output3.FontColor);
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage);

				ValidateValues(handler, "toGuildStorage", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_23(handler, "if mode_var0 == 6");
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 7");
				Server::ShopAddBuyBackPacket output5;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12);

				ResizeVector(handler, output5.Items, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output5.Items[", i, "]"); 
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId);
					Read<int>("itemId", handler, output5.Items[i].ItemId);
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

					ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price);
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
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 8");
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_38(handler, "if mode_var0 == 9");
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock);

				ValidateValues(handler, "restock", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					StackWatch<PacketHandler> watch_41(handler, "if output7.Restock");
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19);

					ValidateValues(handler, "unknown", unknown_var19, (int)0);

					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20);

					ValidateValues(handler, "unknown", unknown_var20, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_44(handler, "if mode_var0 == 11");
				Server::ShopMeretItemCountPacket output8;

				Read<short>("count", handler, output8.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopMeretItemCountPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 12");
				Server::ShopLoadMeretItemPacket output9;

				short count_var22 = 0;
				Read<short>("count", handler, count_var22);

				ResizeVector(handler, output9.Items, count_var22);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_50(handler, "output9.Items[", i, "]"); 
					ParseMeretShopPremiumItemEntry_v12(handler, output9.Items[i].MeretItemEntry);

					unsigned char unknown_var23 = 0;
					Read<unsigned char>("unknown", handler, unknown_var23);

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24);

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 13");
				int npcId_var26 = 0;
				Read<int>("npcId", handler, npcId_var26);

				int shopId_var27 = 0;
				Read<int>("shopId", handler, shopId_var27);

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28);

				short unknown_var29 = 0;
				Read<short>("unknown", handler, unknown_var29);
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_60(handler, "if mode_var0 == 14");
				Server::ShopLoadNewPacket output10;

				short count_var30 = 0;
				Read<short>("count", handler, count_var30);

				ResizeVector(handler, output10.Items, count_var30);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_63(handler, "output10.Items[", i, "]"); 
					Read<int>("itemId", handler, output10.Items[i].ItemId);

					bool unknown_var32 = false;
					Read<bool>("unknown", handler, unknown_var32);

					ValidateValues(handler, "unknown", unknown_var32, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output10.Items[i].Rarity);

					ValidateValues(handler, "rarity", output10.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var34;
					Read<std::string>("unknown", handler, unknown_var34);

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35);

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36);
					Read<bool>("hasBuyPeriod", handler, output10.Items[i].HasBuyPeriod);

					ValidateValues(handler, "hasBuyPeriod", output10.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output10.Items[i].HasBuyPeriod)
					{
						StackWatch<PacketHandler> watch_71(handler, "if output10.Items[i].HasBuyPeriod");
						ParseBuyPeriodData_v12(handler, output10.Items[i].BuyPeriod);
					}
					ParseItemData_v12(handler, output10.Items[i].ItemData, (unsigned int)output10.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_74(handler, "if mode_var0 == 15");
				Server::ShopErrorPacket output11;

				Read<int>("message", handler, output11.Message);

				unsigned char unknown_var39 = 0;
				Read<unsigned char>("unknown", handler, unknown_var39);
				Read<int>("stringId", handler, output11.StringId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output11);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x12>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x12 'RequestHeartbeat' v12");

			Server::RequestHeartbeatPacket output0;

			int heartbeat_var0 = 0;
			Read<int>("heartbeat", handler, heartbeat_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RequestHeartbeatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x13>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x13 'RequestClientTickSync' v12");

			Server::RequestClientTickSyncPacket output0;

			int serverTick_var0 = 0;
			Read<int>("serverTick", handler, serverTick_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RequestClientTickSyncPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x14>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x14 'SyncNumber' v12");

			Server::SyncNumberPacket output0;

			unsigned char syncNumber_var0 = 0;
			Read<unsigned char>("syncNumber", handler, syncNumber_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::SyncNumberPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x55>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x55 'Mail' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Mail[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId);
				Read<long long>("readTime", handler, output2.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 10");
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId);

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7);

				ValidateValues(handler, "unknownCondition", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				ValidateValues(handler, "unknown", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 11");
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId);
				Read<long long>("readTime", handler, output5.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 12");
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12);

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13);
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 13");
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 14");
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount);
				Read<bool>("alert", handler, output7.Alert);

				ValidateValues(handler, "alert", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 15");
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 16");
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 17");
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 20");
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18);
				Read<unsigned char>("message", handler, output11.Message);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 22");
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23);

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24);

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25);

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x15 'ServerEnter' v12");

			Server::ServerEnterPacket output0;

			Read<int>("playerActorId", handler, output0.PlayerActorId);
			Read<long long>("characterId", handler, output0.CharacterId);
			Read<short>("channelId", handler, output0.ChannelId);
			Read<long long>("exp", handler, output0.Exp);
			Read<long long>("restExp", handler, output0.RestExp);
			Read<long long>("mesos", handler, output0.Mesos);
			Read<long long>("totalMerets", handler, output0.TotalMerets);
			Read<long long>("merets", handler, output0.Merets);
			Read<long long>("totalGameMerets", handler, output0.TotalGameMerets);
			Read<long long>("gameMerets", handler, output0.GameMerets);
			Read<long long>("eventMerets", handler, output0.EventMerets);
			Read<long long>("valorTokens", handler, output0.ValorTokens);
			Read<long long>("treva", handler, output0.Treva);
			Read<long long>("rue", handler, output0.Rue);
			Read<long long>("haviFruit", handler, output0.HaviFruit);
			Read<long long>("reverseCoin", handler, output0.ReverseCoin);
			Read<long long>("mentorToken", handler, output0.MentorToken);
			Read<long long>("menteeToken", handler, output0.MenteeToken);
			Read<long long>("starPoint", handler, output0.StarPoint);
			Read<long long>("mesoToken", handler, output0.MesoToken);
			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21);

			unsigned char unknown_var22 = 0;
			Read<unsigned char>("unknown", handler, unknown_var22);

			unsigned short unlockedMaps_var23 = 0;
			Read<unsigned short>("unlockedMaps", handler, unlockedMaps_var23);

			ResizeVector(handler, output0.UnlockedMaps, unlockedMaps_var23);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedMaps_var23 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_25(handler, "output0.UnlockedMaps[", i, "]"); 
				Read<int>("mapId", handler, output0.UnlockedMaps[i].MapId);
			}

			unsigned short unlockedTaxis_var25 = 0;
			Read<unsigned short>("unlockedTaxis", handler, unlockedTaxis_var25);

			ResizeVector(handler, output0.UnlockedTaxis, unlockedTaxis_var25);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedTaxis_var25 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_28(handler, "output0.UnlockedTaxis[", i, "]"); 
				Read<int>("mapId", handler, output0.UnlockedTaxis[i].MapId);
			}

			long long unknown_var27 = 0;
			Read<long long>("unknown", handler, unknown_var27);

			std::wstring unknown_var28;
			Read<std::wstring>("unknown", handler, unknown_var28);
			Read<std::wstring>("mapleNewsUrl", handler, output0.MapleNewsUrl);

			std::wstring unknown_var30;
			Read<std::wstring>("unknown", handler, unknown_var30);

			std::wstring nxCacheUrl_var31;
			Read<std::wstring>("nxCacheUrl", handler, nxCacheUrl_var31);

			std::wstring unknown_var32;
			Read<std::wstring>("unknown", handler, unknown_var32);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ServerEnterPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x56 'FieldAddNpc' v12");

			Server::FieldAddNpcPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("npcId", handler, output0.NpcId);
			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("rotation", handler, output0.Rotation);

			bool isBoss_var4 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				isBoss_var4 = handler.IsNpcBoss(output0.NpcId);

				CalledFunction(handler, "IsNpcBoss", "isBoss_var4", isBoss_var4, output0.NpcId);
			}

			ValidateValues(handler, "isBoss", isBoss_var4, (bool)0, (bool)1);

			if (isBoss_var4)
			{
				StackWatch<PacketHandler> watch_7(handler, "if isBoss_var4");
				Read<std::string>("kfmName", handler, output0.KfmName);
			}

			unsigned char defaultStatsMode_var6 = 0;
			Read<unsigned char>("defaultStatsMode", handler, defaultStatsMode_var6);

			ValidateValues(handler, "defaultStatsMode", defaultStatsMode_var6, (unsigned char)35);

			if (defaultStatsMode_var6 == 35)
			{
				StackWatch<PacketHandler> watch_10(handler, "if defaultStatsMode_var6 == 35");
				Read<unsigned long long>("hpMax", handler, output0.Hp.Max);
				Read<unsigned int>("attackSpeedMax", handler, output0.AttackSpeed.Max);
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base);
				Read<unsigned int>("attackSpeedBase", handler, output0.AttackSpeed.Base);
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current);
				Read<unsigned int>("attackSpeedCurrent", handler, output0.AttackSpeed.Current);
			}
			Read<bool>("isDead", handler, output0.IsDead);

			ValidateValues(handler, "isDead", output0.IsDead, (bool)0, (bool)1);

			unsigned short effectCount_var14 = 0;
			Read<unsigned short>("effectCount", handler, effectCount_var14);

			ResizeVector(handler, output0.Effects, effectCount_var14);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < effectCount_var14 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_19(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}
			Read<long long>("petItemInstanceId", handler, output0.PetItemInstanceId);

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21);
			Read<short>("level", handler, output0.Level);

			short petTaming_var23 = 0;
			Read<short>("petTaming", handler, petTaming_var23);

			ValidateValues(handler, "petTaming", petTaming_var23, (short)0);

			int unknown_var24 = 0;
			Read<int>("unknown", handler, unknown_var24);

			if (isBoss_var4)
			{
				StackWatch<PacketHandler> watch_31(handler, "if isBoss_var4");
				Read<std::wstring>("spawnEffect", handler, output0.SpawnEffect);

				int skillCount_var26 = 0;
				Read<int>("skillCount", handler, skillCount_var26);

				ResizeVector(handler, output0.Skills, skillCount_var26);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < skillCount_var26 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_34(handler, "output0.Skills[", i, "]"); 
					Read<int>("skillId", handler, output0.Skills[i].SkillId);
					Read<short>("skillLevel", handler, output0.Skills[i].SkillLevel);
				}

				int unknown_var29 = 0;
				Read<int>("unknown", handler, unknown_var29);
			}

			bool hasHiddenHp_var30 = false;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				hasHiddenHp_var30 = handler.NpcHasHiddenHp(output0.NpcId);

				CalledFunction(handler, "NpcHasHiddenHp", "hasHiddenHp_var30", hasHiddenHp_var30, output0.NpcId);
			}

			ValidateValues(handler, "hasHiddenHp", hasHiddenHp_var30, (bool)0, (bool)1);

			if (hasHiddenHp_var30)
			{
				StackWatch<PacketHandler> watch_40(handler, "if hasHiddenHp_var30");
				Read<long long>("hiddenHpAdd", handler, output0.HiddenHpAdd);
			}

			bool unknownBool_var32 = false;
			Read<bool>("unknownBool", handler, unknownBool_var32);

			ValidateValues(handler, "unknownBool", unknownBool_var32, (bool)0, (bool)1);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x16 'RequestFieldEnter' v12");

			unsigned char message_var0 = 0;
			Read<unsigned char>("message", handler, message_var0);

			ValidateValues(handler, "message", message_var0, (unsigned char)0);

			if (message_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if message_var0 == 0");
				Server::RequestFieldEnterPacket output0;

				Read<int>("mapId", handler, output0.MapId);

				unsigned char unknown_var2 = 0;
				Read<unsigned char>("unknown", handler, unknown_var2);

				unsigned char unknown_var3 = 0;
				Read<unsigned char>("unknown", handler, unknown_var3);

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4);

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("rotation", handler, output0.Rotation);

				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::RequestFieldEnterPacket>(output0);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x57 'FieldRemoveNpc' v12");

			Server::FieldRemoveNpcPacket output0;

			Read<int>("actorId", handler, output0.ActorId);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v12");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v12(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
					ParseAllStatsOtherPlayers_v12(handler, output0.Stats);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_11(handler, "if statCount_var4 != 35");
					ParseSpecificStats_v12(handler, output0.Stats, statCount_var4);
				}
			}

			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7);

			Color4I_BGRA skinColorPrimary_var8;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var8);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var8;

			Color4I_BGRA skinColorSecondary_var9;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var9);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var9;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_21(handler, "if output0.OnMount");
				ParseMountData_v12(handler, output0.Mount);
			}

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var16 = false;
			Read<bool>("isDeflated", handler, isDeflated_var16);

			ValidateValues(handler, "isDeflated", isDeflated_var16, (bool)0, (bool)1);

			int bufferSize_var17 = 0;
			Read<int>("bufferSize", handler, bufferSize_var17);

			{
				StackWatch<PacketHandler> watch_29(handler, "buffer[", bufferSize_var17, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var16);

			ValidateValues(handler, "isDeflated", isDeflated_var16, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var17);

			{
				StackWatch<PacketHandler> watch_34(handler, "buffer[", bufferSize_var17, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentFashion_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var16);

			ValidateValues(handler, "isDeflated", isDeflated_var16, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var17);

			{
				StackWatch<PacketHandler> watch_38(handler, "buffer[", bufferSize_var17, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var17, isDeflated_var16);
				ParseCharacterEquipmentBadges_v12(handler, output0.Equipment);
			}

			short effectCount_var18 = 0;
			Read<short>("effectCount", handler, effectCount_var18);

			ResizeVector(handler, output0.Effects, effectCount_var18);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var18 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_41(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var24 = 0;
			Read<int>("unknown", handler, unknown_var24);

			int unknown_var25 = 0;
			Read<int>("unknown", handler, unknown_var25);

			unsigned char unknown_var26 = 0;
			Read<unsigned char>("unknown", handler, unknown_var26);

			int unknown_var27 = 0;
			Read<int>("unknown", handler, unknown_var27);

			unsigned char unknown_var28 = 0;
			Read<unsigned char>("unknown", handler, unknown_var28);

			unsigned char unknown_var29 = 0;
			Read<unsigned char>("unknown", handler, unknown_var29);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_59(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var39 = 0;
			Read<int>("unknown", handler, unknown_var39);

			unsigned char unknown_var40 = 0;
			Read<unsigned char>("unknown", handler, unknown_var40);

			int mushkingTailKillCount_var41 = 0;
			Read<int>("mushkingTailKillCount", handler, mushkingTailKillCount_var41);

			int unknownCount_var42 = 0;
			Read<int>("unknownCount", handler, unknownCount_var42);

			ResizeVector(handler, output0.UnknownData, unknownCount_var42);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var42 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_69(handler, "output0.UnknownData[", i, "]"); 
				int unknown_var43 = 0;
				Read<int>("unknown", handler, unknown_var43);

				std::wstring unknown_var44;
				Read<std::wstring>("unknown", handler, unknown_var44);
			}

			short unknown_var45 = 0;
			Read<short>("unknown", handler, unknown_var45);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x18 'FieldRemovePlayer' v12");

			Server::FieldRemovePlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemovePlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x19>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x19 'DungeonList' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::DungeonListEntriesPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output0.Dungeons, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Dungeons[", i, "]"); 
					int dungeonId_var2 = 0;
					Read<int>("dungeonId", handler, dungeonId_var2);

					bool eligibility_var3 = false;
					Read<bool>("eligibility", handler, eligibility_var3);

					ValidateValues(handler, "eligibility", eligibility_var3, (bool)0, (bool)1);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::DungeonListEntriesPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 1");
			}
			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 2");
				unsigned char message_var4 = 0;
				Read<unsigned char>("message", handler, message_var4);

				int dungeonRoomId_var5 = 0;
				Read<int>("dungeonRoomId", handler, dungeonRoomId_var5);
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1c 'UserSync' v12");

			Server::UserSyncPacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			unsigned char count_var1 = 0;
			Read<unsigned char>("count", handler, count_var1);

			ResizeVector(handler, output0.StateData, count_var1);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "output0.StateData[", i, "]"); 
				ParseStateSyncData_v12(handler, output0.StateData[i]);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserSyncPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1d 'UserChat' v12");

			Server::UserChatPacket output0;

			Read<long long>("accountId", handler, output0.AccountId);
			Read<long long>("characterId", handler, output0.CharacterId);
			Read<std::wstring>("characterName", handler, output0.CharacterName);

			bool useStringId_var3 = false;
			Read<bool>("useStringId", handler, useStringId_var3);

			ValidateValues(handler, "useStringId", useStringId_var3, (bool)0, (bool)1);

			if (useStringId_var3)
			{
				StackWatch<PacketHandler> watch_5(handler, "if useStringId_var3");
				Read<int>("stringId", handler, output0.StringId);
			}

			else
			{
				StackWatch<PacketHandler> watch_7(handler, "else");
				Read<std::wstring>("message", handler, output0.Message);
			}
			Read<int>("type", handler, output0.Type);

			ValidateValues(handler, "type", output0.Type, (int)8, (int)0, (int)3, (int)4, (int)5, (int)6, (int)7, (int)9, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)18, (int)19, (int)20, (int)23);

			bool unknown_var7 = false;
			Read<bool>("unknown", handler, unknown_var7);

			ValidateValues(handler, "unknown", unknown_var7, (bool)0, (bool)1);

			Read<int>("channelId", handler, output0.ChannelId);

			if (output0.Type == (Server::UserChatPacket::TypeEnum)3)
			{
				StackWatch<PacketHandler> watch_12(handler, "if output0.Type == (Server::UserChatPacket::TypeEnum)3");
				std::wstring unknown_var9;
				Read<std::wstring>("unknown", handler, unknown_var9);
			}

			if (output0.Type == (Server::UserChatPacket::TypeEnum)16)
			{
				StackWatch<PacketHandler> watch_14(handler, "if output0.Type == (Server::UserChatPacket::TypeEnum)16");
				Read<int>("superChatId", handler, output0.SuperChatId);
			}

			if (output0.Type == (Server::UserChatPacket::TypeEnum)20)
			{
				StackWatch<PacketHandler> watch_16(handler, "if output0.Type == (Server::UserChatPacket::TypeEnum)20");
				Read<long long>("clubId", handler, output0.ClubId);
			}

			unsigned char unknown_var12 = 0;
			Read<unsigned char>("unknown", handler, unknown_var12);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1e 'UserChatItemLink' v12");

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0);

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_2(handler, "output0.Items[", i, "]"); 
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
				Read<int>("itemId", handler, output0.Items[i].ItemId);
				Read<int>("rarity", handler, output0.Items[i].Rarity);

				ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Items[i].ItemData, (unsigned int)output0.Items[i].ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserChatItemLinkPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1f 'Emotion' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::EmotionLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output0.Emotes, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Emotes[", i, "]"); 
					int emoteId_var2 = 0;
					Read<int>("emoteId", handler, emoteId_var2);

					int unknown_var3 = 0;
					Read<int>("unknown", handler, unknown_var3);

					long long unknown_var4 = 0;
					Read<long long>("unknown", handler, unknown_var4);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EmotionLoadPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::EmotionLearnPacket output1;

				int emoteId_var5 = 0;
				Read<int>("emoteId", handler, emoteId_var5);

				int unknown_var6 = 0;
				Read<int>("unknown", handler, unknown_var6);

				long long unknown_var7 = 0;
				Read<long long>("unknown", handler, unknown_var7);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EmotionLearnPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				Server::EmotionErrorPacket output2;

				unsigned char message_var8 = 0;
				Read<unsigned char>("message", handler, message_var8);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::EmotionErrorPacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x20 'ItemPutOnOrOff' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)2, (unsigned char)3, (unsigned char)5);

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 2");
				long long itemInstanceId_var1 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var1);
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 3");
				long long itemInstanceId_var2 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var2);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 5");
				int unknown_var3 = 0;
				Read<int>("unknown", handler, unknown_var3);

				long long itemInstanceId_var4 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var4);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5);

				unsigned char unknown_var6 = 0;
				Read<unsigned char>("unknown", handler, unknown_var6);
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x23>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x23 'FurnishingStorage' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 2");
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 3");
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot);
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);
				Read<int>("count", handler, output4.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 7");
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);
				Read<int>("count", handler, output5.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 8");
				Server::FurnishingStorageEndListPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageEndListPacket>(output6);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x24>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x24 'FurnishingInventory' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
			}
			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_2(handler, "if mode_var0 == 1");
				Server::FurnishingInventoryUnknownPacket output0;

				int itemId_var1 = 0;
				Read<int>("itemId", handler, itemId_var1);

				long long itemInstanceId_var2 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var2);

				long long unknown_var3 = 0;
				Read<long long>("unknown", handler, unknown_var3);

				bool isTemplate_var4 = false;
				Read<bool>("isTemplate", handler, isTemplate_var4);

				ValidateValues(handler, "isTemplate", isTemplate_var4, (bool)0, (bool)1);

				if (isTemplate_var4)
				{
					StackWatch<PacketHandler> watch_8(handler, "if isTemplate_var4");
					ParseItemUgc_v12(handler, output0.Ugc);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingInventoryUnknownPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_10(handler, "if mode_var0 == 2");
				long long itemInstanceId_var5 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var5);
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 3");
				long long itemInstanceId_var6 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var6);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7);
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_15(handler, "if mode_var0 == 4");
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x25>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x25 'ItemPutOn' v12");

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<std::wstring>("slotName", handler, output0.SlotName);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x26 'ItemPutOff' v12");

			Server::ItemPutOffPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x27 'ItemSkinPutOn' v12");

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<long long>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x28 'ItemSkinPutOff' v12");

			Server::ItemSkinPutOffPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2a 'ItemUpdate' v12");

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				StackWatch<PacketHandler> watch_5(handler, "if itemId_var2 == 0");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2b 'FieldAddItem' v12");

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<int>("amount", handler, output0.Amount);

			bool hasUid_var3 = false;
			Read<bool>("hasUid", handler, hasUid_var3);

			ValidateValues(handler, "hasUid", hasUid_var3, (bool)0, (bool)1);

			if (hasUid_var3)
			{
				StackWatch<PacketHandler> watch_5(handler, "if hasUid_var3");
				Read<long long>("uid", handler, output0.ItemInstanceId);
			}
			Read<Vector3S>("position", handler, output0.Position);
			Read<int>("ownerId", handler, output0.OwnerId);

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7);

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var10 = 0;
			Read<short>("unknown", handler, unknown_var10);

			bool unknown_var11 = false;
			Read<bool>("unknown", handler, unknown_var11);

			ValidateValues(handler, "unknown", unknown_var11, (bool)0, (bool)1);

			bool unknown_var12 = false;
			Read<bool>("unknown", handler, unknown_var12);

			ValidateValues(handler, "unknown", unknown_var12, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				StackWatch<PacketHandler> watch_15(handler, "if output0.ItemId < 90000001 || output0.ItemId > 90000003");
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2c 'FieldRemoveItem' v12");

			Server::FieldRemoveItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2d 'FieldPickUpItem' v12");

			Server::FieldPickUpItemPacket output0;

			bool pickedUp_var0 = false;
			Read<bool>("pickedUp", handler, pickedUp_var0);

			ValidateValues(handler, "pickedUp", pickedUp_var0, (bool)0, (bool)1);

			Read<int>("objectId", handler, output0.ObjectId);

			if (pickedUp_var0)
			{
				StackWatch<PacketHandler> watch_3(handler, "if pickedUp_var0");
				int actorId_var2 = 0;
				Read<int>("actorId", handler, actorId_var2);
			}

			unsigned int itemType_var3 = 0;

			if (pickedUp_var0)
			{
				StackWatch<PacketHandler> watch_6(handler, "if pickedUp_var0");
				unsigned int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemType_var3 = handler.GetFieldItemType(output0.ObjectId);

					CalledFunction(handler, "GetFieldItemType", "itemType_var3", itemType_var3, output0.ObjectId);
				}

				ValidateValues(handler, "itemType", itemType_var3, (unsigned int)0, (unsigned int)1, (unsigned int)2);

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetFieldItemId(output0.ObjectId);

					CalledFunction(handler, "GetFieldItemId", "itemId_var4", itemId_var4, output0.ObjectId);
				}

				if (itemType_var3 == 1)
				{
					StackWatch<PacketHandler> watch_10(handler, "if itemType_var3 == 1");
					long long amount_var5 = 0;
					Read<long long>("amount", handler, amount_var5);
				}

				if (itemType_var3 == 2)
				{
					StackWatch<PacketHandler> watch_12(handler, "if itemType_var3 == 2");
					int amount_var6 = 0;
					Read<int>("amount", handler, amount_var6);
				}
			}

			else
			{
				StackWatch<PacketHandler> watch_14(handler, "else");
				int unknown_var7 = 0;
				Read<int>("unknown", handler, unknown_var7);

				ValidateValues(handler, "unknown", unknown_var7, (int)1);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldPickUpItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2e 'FieldMutateItem' v12");

			Server::FieldMutateItemPacket output0;

			int objectId_var0 = 0;
			Read<int>("objectId", handler, objectId_var0);

			int mutationId_var1 = 0;
			Read<int>("mutationId", handler, mutationId_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldMutateItemPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2f 'Stat' v12");

			Server::StatPacket output0;

			Read<int>("actorId", handler, output0.ActorId);

			bool unknown_var1 = false;
			Read<bool>("unknown", handler, unknown_var1);

			ValidateValues(handler, "unknown", unknown_var1, (bool)0, (bool)1);

			unsigned char statCount_var2 = 0;
			Read<unsigned char>("statCount", handler, statCount_var2);

			unsigned char actorType_var3 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				actorType_var3 = handler.GetActorType(output0.ActorId);

				CalledFunction(handler, "GetActorType", "actorType_var3", actorType_var3, output0.ActorId);
			}

			ValidateValues(handler, "actorType", actorType_var3, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)255);

			if (actorType_var3 == 255)
			{
				StackWatch<PacketHandler> watch_6(handler, "if actorType_var3 == 255");
				handler.DiscardPacket();

				return;

			}

			if (statCount_var2 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if statCount_var2 == 1");
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
				StackWatch<PacketHandler> watch_12(handler, "else if actorType_var3 == 3");
				ParseAllStatsNpc_v12(handler, output0.Stats);
			}

			else if (actorType_var3 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "else if actorType_var3 == 4");
				ParseAllStatsNpc_v12(handler, output0.Stats);
			}

			else if (statCount_var2 == 35)
			{
				StackWatch<PacketHandler> watch_16(handler, "else if statCount_var2 == 35");
				if (actorType_var3 == 1)
				{
					StackWatch<PacketHandler> watch_17(handler, "if actorType_var3 == 1");
					ParseAllStatsMyPlayer_v12(handler, output0.Stats);
				}

				else
				{
					StackWatch<PacketHandler> watch_19(handler, "else");
					ParseAllStatsOtherPlayers_v12(handler, output0.Stats);
				}
			}

			else if (statCount_var2 == 255)
			{
				StackWatch<PacketHandler> watch_21(handler, "else if statCount_var2 == 255");
				unsigned char basicStatCount_var5 = 35;
				ParseSpecificStats_v12(handler, output0.Stats, basicStatCount_var5);
			}

			else
			{
				StackWatch<PacketHandler> watch_24(handler, "else");
				ParseSpecificStats_v12(handler, output0.Stats, statCount_var2);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::StatPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x30>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x30 'UserBattle' v12");

			Server::UserBattlePacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			bool inBattle_var1 = false;
			Read<bool>("inBattle", handler, inBattle_var1);

			ValidateValues(handler, "inBattle", inBattle_var1, (bool)0, (bool)1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserBattlePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x31>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x31 'UserSkinColor' v12");

			Server::UserSkinColorPacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			Color4I_BGRA skinColorPrimary_var1;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var1);

			Color4I_BGRA skinColorSecondary_var2;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var2);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserSkinColorPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x33>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x33 'AdventurerBar' v12");

			Server::AdventurerBarPacket output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::AdventurerBarPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x34>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x34 'RevivalConfirm' v12");

			Server::RevivalConfirmPacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			int serverTick_var1 = 0;
			Read<int>("serverTick", handler, serverTick_var1);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RevivalConfirmPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x35>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x35 'Revival' v12");

			Server::RevivalPacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			unsigned char revival_var1 = 0;
			Read<unsigned char>("revival", handler, revival_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RevivalPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x36>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x36 'RevivalCount' v12");

			Server::RevivalCountPacket output0;

			int revivalCount_var0 = 0;
			Read<int>("revivalCount", handler, revivalCount_var0);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::RevivalCountPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x37>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x37 'UserState' v12");

			Server::UserStatePacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			unsigned char state_var1 = 0;
			Read<unsigned char>("state", handler, state_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserStatePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x38>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x38 'ExpUp' v12");

			Server::ExpUpPacket output0;

			Read<bool>("isRestExp", handler, output0.IsRestExp);

			ValidateValues(handler, "isRestExp", output0.IsRestExp, (bool)0, (bool)1);

			if (output0.IsRestExp == 0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if output0.IsRestExp == 0");
				Read<long long>("expGained", handler, output0.ExpGained);

				short unknown_var2 = 0;
				Read<short>("unknown", handler, unknown_var2);
				Read<long long>("totalExp", handler, output0.TotalExp);
				Read<long long>("restExp", handler, output0.RestExp);
				Read<int>("message", handler, output0.Message);
				Read<bool>("additional", handler, output0.Additional);

				ValidateValues(handler, "additional", output0.Additional, (bool)0, (bool)1);
			}

			if (output0.IsRestExp)
			{
				StackWatch<PacketHandler> watch_9(handler, "if output0.IsRestExp");
				Read<long long>("restExp", handler, output0.RestExp);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x39 'LevelUp' v12");

			Server::LevelUpPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("level", handler, output0.Level);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::LevelUpPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3a 'Meso' v12");

			Server::MesoPacket output0;

			long long mesos_var0 = 0;
			Read<long long>("mesos", handler, mesos_var0);

			int pcbang_var1 = 0;
			Read<int>("pcbang", handler, pcbang_var1);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::MesoPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3b 'Meret' v12");

			Server::MeretPacket output0;

			long long merets_var0 = 0;
			Read<long long>("merets", handler, merets_var0);

			long long merets2_var1 = 0;
			Read<long long>("merets2", handler, merets2_var1);

			long long gameMerets_var2 = 0;
			Read<long long>("gameMerets", handler, gameMerets_var2);

			long long gameMerets2_var3 = 0;
			Read<long long>("gameMerets2", handler, gameMerets2_var3);

			long long deductMerets_var4 = 0;
			Read<long long>("deductMerets", handler, deductMerets_var4);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::MeretPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3c 'CurrencyToken' v12");

			Server::CurrencyTokenPacket output0;

			unsigned char type_var0 = 0;
			Read<unsigned char>("type", handler, type_var0);

			long long amount_var1 = 0;
			Read<long long>("amount", handler, amount_var1);

			long long deduct_var2 = 0;
			Read<long long>("deduct", handler, deduct_var2);

			int unknown_var3 = 0;
			Read<int>("unknown", handler, unknown_var3);

			long long overflow_var4 = 0;
			Read<long long>("overflow", handler, overflow_var4);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::CurrencyTokenPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3d 'SkillUse' v12");

			Server::SkillUsePacket output0;

			long long skillSn_var0 = 0;
			Read<long long>("skillSn", handler, skillSn_var0);

			int serverTick_var1 = 0;
			Read<int>("serverTick", handler, serverTick_var1);

			int actorId_var2 = 0;
			Read<int>("actorId", handler, actorId_var2);

			int skillId_var3 = 0;
			Read<int>("skillId", handler, skillId_var3);

			short skillLevel_var4 = 0;
			Read<short>("skillLevel", handler, skillLevel_var4);

			unsigned char motionPoint_var5 = 0;
			Read<unsigned char>("motionPoint", handler, motionPoint_var5);

			Vector3Short position_var6;
			Read<Vector3Short>("position", handler, position_var6);

			Vector3S direction_var7;
			Read<Vector3S>("direction", handler, direction_var7);

			Vector3S rotation_var8;
			Read<Vector3S>("rotation", handler, rotation_var8);

			short posDiv10_var9 = 0;
			Read<short>("posDiv10", handler, posDiv10_var9);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10);

			ValidateValues(handler, "unknown", unknown_var10, (bool)0, (bool)1);

			bool isHold_var11 = false;
			Read<bool>("isHold", handler, isHold_var11);

			ValidateValues(handler, "isHold", isHold_var11, (bool)0, (bool)1);

			if (isHold_var11)
			{
				StackWatch<PacketHandler> watch_13(handler, "if isHold_var11");
				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12);

				std::wstring unknown_var13;
				Read<std::wstring>("unknown", handler, unknown_var13);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::SkillUsePacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3e 'SkillDamage' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<int>("casterId", handler, output0.CasterId);
				Read<unsigned int>("skillId", handler, output0.SkillId);
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel);
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint);
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint);
				Read<Vector3Short>("position", handler, output0.Position);
				Read<Vector3S>("direction", handler, output0.Direction);
				Read<bool>("isChaining", handler, output0.IsChaining);

				ValidateValues(handler, "isChaining", output0.IsChaining, (bool)0, (bool)1);

				Read<int>("serverTick", handler, output0.ServerTick);

				unsigned char count_var11 = 0;
				Read<unsigned char>("count", handler, count_var11);

				ResizeVector(handler, output0.Hits, count_var11);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var11 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_14(handler, "output0.Hits[", i, "]"); 
					long long unknown_var12 = 0;
					Read<long long>("unknown", handler, unknown_var12);
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack);
					Read<int>("targetId", handler, output0.Hits[i].TargetId);
					Read<short>("animation", handler, output0.Hits[i].Animation);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 3");
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<int>("damage", handler, output2.Damage);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 5");
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
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 6");
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
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 7");
				int unknown_var17 = 0;
				Read<int>("unknown", handler, unknown_var17);

				int count_var18 = 0;
				Read<int>("count", handler, count_var18);

				for (int i = 0; i < count_var18 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_38(handler, "array1[", i, "]"); 
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19);
				}
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_40(handler, "if mode_var0 == 8");
				long long skillSn_var20 = 0;
				Read<long long>("skillSn", handler, skillSn_var20);

				bool hasTarget_var21 = false;
				Read<bool>("hasTarget", handler, hasTarget_var21);

				ValidateValues(handler, "hasTarget", hasTarget_var21, (bool)0, (bool)1);

				if (hasTarget_var21)
				{
					StackWatch<PacketHandler> watch_43(handler, "if hasTarget_var21");
					unsigned int skillId_var22 = 0;
					Read<unsigned int>("skillId", handler, skillId_var22);

					unsigned short skillLevel_var23 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var23);

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24);

					int npcId_var25 = 0;
					Read<int>("npcId", handler, npcId_var25);
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3f 'SkillSync' v12");

			Server::SkillSyncPacket output0;

			long long skillSn_var0 = 0;
			Read<long long>("skillSn", handler, skillSn_var0);

			int actorId_var1 = 0;
			Read<int>("actorId", handler, actorId_var1);

			int skillId_var2 = 0;
			Read<int>("skillId", handler, skillId_var2);

			short skillLevel_var3 = 0;
			Read<short>("skillLevel", handler, skillLevel_var3);

			Vector3S position_var4;
			Read<Vector3S>("position", handler, position_var4);

			Vector3S direction_var5;
			Read<Vector3S>("direction", handler, direction_var5);

			Vector3S rotation_var6;
			Read<Vector3S>("rotation", handler, rotation_var6);

			Vector3S unknown_var7;
			Read<Vector3S>("unknown", handler, unknown_var7);

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8);

			unsigned char attackPoint_var9 = 0;
			Read<unsigned char>("attackPoint", handler, attackPoint_var9);

			int unknown_var10 = 0;
			Read<int>("unknown", handler, unknown_var10);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::SkillSyncPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x5b 'FieldAddPet' v12");

			Server::FieldAddPetPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("petSkinId", handler, output0.PetSkinId);
			Read<int>("petNpcId", handler, output0.PetNpcId);
			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("rotation", handler, output0.Rotation);
			Read<float>("scale", handler, output0.Scale);
			Read<int>("ownerActorId", handler, output0.OwnerActorId);

			unsigned char defaultStatsMode_var7 = 0;
			Read<unsigned char>("defaultStatsMode", handler, defaultStatsMode_var7);

			ValidateValues(handler, "defaultStatsMode", defaultStatsMode_var7, (unsigned char)35);

			if (defaultStatsMode_var7 == 35)
			{
				StackWatch<PacketHandler> watch_9(handler, "if defaultStatsMode_var7 == 35");
				Read<unsigned long long>("hpMax", handler, output0.Hp.Max);
				Read<unsigned int>("attackSpeedMax", handler, output0.AttackSpeed.Max);
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base);
				Read<unsigned int>("attackSpeedBase", handler, output0.AttackSpeed.Base);
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current);
				Read<unsigned int>("attackSpeedCurrent", handler, output0.AttackSpeed.Current);
			}
			Read<long long>("petItemInstanceId", handler, output0.PetItemInstanceId);

			unsigned char unknown_var15 = 0;
			Read<unsigned char>("unknown", handler, unknown_var15);
			Read<short>("level", handler, output0.Level);
			Read<short>("petTaming", handler, output0.PetTaming);

			int unknown_var18 = 0;
			Read<int>("unknown", handler, unknown_var18);
			Read<std::wstring>("name", handler, output0.Name);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x5c 'FieldRemovePet' v12");

			Server::FieldRemovePetPacket output0;

			Read<int>("actorId", handler, output0.ActorId);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x5f 'Trophy' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::TrophyStartPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TrophyStartPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 1");
				Server::TrophyContentPacket output1;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output1.Trophies, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_6(handler, "output1.Trophies[", i, "]"); 
					Read<int>("trophyId", handler, output1.Trophies[i].TrophyId);

					int unknown_var3 = 0;
					Read<int>("unknown", handler, unknown_var3);

					ValidateValues(handler, "unknown", unknown_var3, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)9);

					Read<unsigned char>("status", handler, output1.Trophies[i].Status);

					ValidateValues(handler, "status", output1.Trophies[i].Status, (unsigned char)2, (unsigned char)3);

					Read<int>("isDone", handler, output1.Trophies[i].IsDone);
					Read<int>("nextGrade", handler, output1.Trophies[i].NextGrade);
					Read<int>("lastReward", handler, output1.Trophies[i].LastReward);
					Read<bool>("isFavorited", handler, output1.Trophies[i].IsFavorited);

					ValidateValues(handler, "isFavorited", output1.Trophies[i].IsFavorited, (bool)0, (bool)1);

					Read<long long>("counter", handler, output1.Trophies[i].Counter);

					int timestampsCount_var10 = 0;
					Read<int>("timestampsCount", handler, timestampsCount_var10);

					ResizeVector(handler, output1.Trophies[i].Timestamps, timestampsCount_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int j = 0; j < timestampsCount_var10 && !handler.PacketStream().HasRecentlyFailed; ++j)
					{
						StackWatch<PacketHandler> watch_16(handler, "output1.Trophies[i].Timestamps[", j, "]"); 
						Read<int>("index", handler, output1.Trophies[i].Timestamps[j].Index);
						Read<long long>("timestamp", handler, output1.Trophies[i].Timestamps[j].Time);
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
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 2");
				Server::TrophyUpdatePacket output2;

				Read<int>("trophyId", handler, output2.TrophyId);
				Read<unsigned char>("status", handler, output2.Status);

				ValidateValues(handler, "status", output2.Status, (unsigned char)2, (unsigned char)3);

				Read<int>("isDone", handler, output2.IsDone);
				Read<int>("nextGrade", handler, output2.NextGrade);
				Read<int>("lastReward", handler, output2.LastReward);
				Read<bool>("isFavorited", handler, output2.IsFavorited);

				ValidateValues(handler, "isFavorited", output2.IsFavorited, (bool)0, (bool)1);

				Read<long long>("counter", handler, output2.Counter);

				int timestampsCount_var20 = 0;
				Read<int>("timestampsCount", handler, timestampsCount_var20);

				ResizeVector(handler, output2.Timestamps, timestampsCount_var20);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < timestampsCount_var20 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output2.Timestamps[", i, "]"); 
					Read<int>("index", handler, output2.Timestamps[i].Index);
					Read<long long>("timestamp", handler, output2.Timestamps[i].Time);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TrophyUpdatePacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x6c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x6c 'LoadCubes' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::LoadCubesPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1);

				ValidateValues(handler, "unknown", unknown_var1, (unsigned char)0);

				int count_var2 = 0;
				Read<int>("count", handler, count_var2);

				ResizeVector(handler, output0.CubeData, count_var2);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var2 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_5(handler, "output0.CubeData[", i, "]"); 
					Read<Vector3Byte>("position", handler, output0.CubeData[i].Position);
					Read<long long>("itemInstanceId", handler, output0.CubeData[i].ItemInstanceId);
					ParseCubeItemData_v12(handler, output0.CubeData[i].Data);

					Read<int>("plotNumber", handler, output0.CubeData[i].PlotNumber);

					int unknown_var6 = 0;
					Read<int>("unknown", handler, unknown_var6);

					unsigned char unknown_var7 = 0;
					Read<unsigned char>("unknown", handler, unknown_var7);
					Read<float>("RotationZ", handler, output0.CubeData[i].RotationZ);

					int unknown_var9 = 0;
					Read<int>("unknown", handler, unknown_var9);

					bool hasExtraData_var10 = false;
					Read<bool>("hasExtraData", handler, hasExtraData_var10);

					ValidateValues(handler, "hasExtraData", hasExtraData_var10, (bool)0, (bool)1);

					if (hasExtraData_var10)
					{
						StackWatch<PacketHandler> watch_15(handler, "if hasExtraData_var10");
						std::wstring unknown_var11;
						Read<std::wstring>("unknown", handler, unknown_var11);

						unsigned char unknown_var12 = 0;
						Read<unsigned char>("unknown", handler, unknown_var12);
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
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 1");
				Server::LoadCubesAvailabilityPacket output1;

				int count_var13 = 0;
				Read<int>("count", handler, count_var13);

				ResizeVector(handler, output1.AvailabilityData, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_21(handler, "output1.AvailabilityData[", i, "]"); 
					Read<int>("plotId", handler, output1.AvailabilityData[i].PlotId);
					Read<bool>("isTaken", handler, output1.AvailabilityData[i].IsTaken);

					ValidateValues(handler, "isTaken", output1.AvailabilityData[i].IsTaken, (bool)0, (bool)1);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesAvailabilityPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 2");
				Server::LoadCubesPlotsPacket output2;

				int count_var16 = 0;
				Read<int>("count", handler, count_var16);

				ResizeVector(handler, output2.PlotData, count_var16);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var16 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_27(handler, "output2.PlotData[", i, "]"); 
					Read<int>("plotId", handler, output2.PlotData[i].PlotId);
					Read<int>("apartmentNumber", handler, output2.PlotData[i].ApartmentNumber);
					Read<std::wstring>("plotName", handler, output2.PlotData[i].PlotName);
					Read<long long>("accountId", handler, output2.PlotData[i].AccountId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesPlotsPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 3");
				Server::LoadCubesExpirationPacket output3;

				int count_var21 = 0;
				Read<int>("count", handler, count_var21);

				ResizeVector(handler, output3.SaleStateData, count_var21);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var21 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_35(handler, "output3.SaleStateData[", i, "]"); 
					Read<int>("plotId", handler, output3.SaleStateData[i].PlotId);
					Read<int>("apartmentNumber", handler, output3.SaleStateData[i].ApartmentNumber);
					Read<unsigned char>("state", handler, output3.SaleStateData[i].State);

					ValidateValues(handler, "state", output3.SaleStateData[i].State, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

					Read<long long>("expirationTime", handler, output3.SaleStateData[i].ExpirationTime);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::LoadCubesExpirationPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x7a 'CharacterInfo' v12");

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId);
			Read<bool>("found", handler, output0.Found);

			ValidateValues(handler, "found", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				StackWatch<PacketHandler> watch_3(handler, "if output0.Found");
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2);

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3);
				Read<long long>("currentTime", handler, output0.CurrentTime);

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_8(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						StackWatch<PacketHandler> watch_10(handler, "output0.Details.Stats");
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_15(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_19(handler, "buffer[", bufferSize_var5, "]");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x7d 'FittingDoll' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId);
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId);
				Read<int>("dollItemId", handler, output0.DollItemId);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("rotation", handler, output0.Rotation);
				Read<bool>("hasItems", handler, output0.HasItems);

				ValidateValues(handler, "hasItems", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7);

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "output0.Items[", i, "]"); 
					Read<int>("itemId", handler, output0.Items[i].ItemId);
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
					Read<std::wstring>("slotName", handler, output0.Items[i].SlotName);
					Read<int>("rarity", handler, output0.Items[i].Rarity);

					ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 1");
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 4");
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId);
				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<std::wstring>("slotName", handler, output2.SlotName);
				Read<int>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 7");
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);
				Read<std::wstring>("slotName", handler, output3.SlotName);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 8");
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 11");
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x84 'Trade' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)13);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName);
				Read<long long>("characterId", handler, output0.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 1");
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message);
				Read<std::wstring>("name", handler, output1.Name);
				Read<int>("itemId", handler, output1.ItemId);
				Read<int>("level", handler, output1.Level);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 6");
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success);

				ValidateValues(handler, "success", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 8");
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index);

				ValidateValues(handler, "index", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId);
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);
				Read<int>("rarity", handler, output6.Rarity);

				ValidateValues(handler, "rarity", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot);
				Read<int>("amount", handler, output6.Amount);
				Read<int>("tradeSlot2", handler, output6.TradeSlot2);
				ParseItemData_v12(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 9");
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index);

				ValidateValues(handler, "index", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot);
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 10");
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index);
				Read<long long>("mesos", handler, output8.Mesos);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 11");
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_44(handler, "if mode_var0 == 12");
				Server::TradeChangeOfferPacket output10;

				Read<unsigned char>("index", handler, output10.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeChangeOfferPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 13");
				Server::TradeFinalizeConfirmPacket output11;

				Read<unsigned char>("index", handler, output11.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 14");
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x99>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x99 'ItemEnchant' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 5");
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType);

				ValidateValues(handler, "enchantType", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3);

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_6(handler, "output0.Ingredients[", i, "]"); 
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4);
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem);

					ValidateValues(handler, "requiredItem", output0.Ingredients[i].RequiredItem, (int)96, (int)97, (int)98, (int)99, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount);
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7);

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8);

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_12(handler, "output0.Stats[", i, "]"); 
					ParseBasicStat_v12(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					StackWatch<PacketHandler> watch_14(handler, "if output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1");
					Read<float>("successRate", handler, output0.SuccessRate);
					Read<float>("unknownRate2", handler, output0.UnknownRate2);
					Read<float>("unknownRate3", handler, output0.UnknownRate3);
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate);
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate);

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14);

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15);

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16);
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					StackWatch<PacketHandler> watch_23(handler, "if output0.EnchantType >= 1 && output0.EnchantType <= 2");
					Read<int>("itemId", handler, output0.ItemId);
					Read<short>("rarity", handler, output0.Rarity);

					ValidateValues(handler, "rarity", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_27(handler, "if mode_var0 == 6");
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);
				Read<int>("enchantExp", handler, output1.EnchantExp);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 7");
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount);
				Read<int>("catalystWeight", handler, output2.CatalystWeight);

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24);

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_36(handler, "output2.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId);
				}
				Read<float>("successRate", handler, output2.SuccessRate);
				Read<float>("unknownRate2", handler, output2.UnknownRate2);
				Read<float>("unknownRate3", handler, output2.UnknownRate3);
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate);
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 8");
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight);

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32);

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_47(handler, "output3.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 9");
			}
			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 10");
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var35", itemId_var35, output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					StackWatch<PacketHandler> watch_55(handler, "if itemId_var35 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36);

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_59(handler, "output4.Stats[", i, "]"); 
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
				StackWatch<PacketHandler> watch_61(handler, "if mode_var0 == 11");
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var38", itemId_var38, output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					StackWatch<PacketHandler> watch_66(handler, "if itemId_var38 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39);

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40);

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41);
				Read<int>("failStacks", handler, output5.FailStacks);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_73(handler, "if mode_var0 == 12");
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 15");
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44);
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_78(handler, "if mode_var0 == 16");
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x9a>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x9a 'BlackMarket' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1);
				Read<int>("errorCode", handler, output0.ErrorCode);
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId);

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4);

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6);

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output1.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 3");
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9);

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_23(handler, "output4.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 5");
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId);
				Read<int>("amount", handler, output5.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 6");
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14);
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 7");
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 8");
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId);
				Read<int>("rarity", handler, output7.Rarity);

				ValidateValues(handler, "rarity", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice);

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 9");
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xc1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc1 'EnchantScroll' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 3");
				short result_var1 = 0;
				Read<short>("result", handler, result_var1);

				ValidateValues(handler, "result", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if result_var1 == 0");
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						StackWatch<PacketHandler> watch_14(handler, "if itemId_var3 == 0");
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
					StackWatch<PacketHandler> watch_17(handler, "else");
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);

						CalledFunction(handler, "Copy", "output3.Result", output3.Result, result_var1);
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
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 4");
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5);

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_24(handler, "output4.Data[", i, "]"); 
					Read<int>("itemId", handler, output4.Data[i].ItemId);

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc9 'PlayInstrument' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId);
				Read<int>("actorId", handler, output0.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition);
				Read<int>("gmId", handler, output0.GMId);
				Read<int>("percussionId", handler, output0.PercussionId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId);
				Read<int>("actorId", handler, output1.ActorId);
				Read<int>("midiNote", handler, output1.MidiNote);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId);
				Read<int>("actorId", handler, output2.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 3");
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom);

				ValidateValues(handler, "isCustom", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId);
				Read<int>("actorId", handler, output3.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition);
				Read<int>("instrumentTick", handler, output3.InstrumentTick);
				Read<int>("gmId", handler, output3.GMId);
				Read<int>("percussionId", handler, output3.PercussionId);

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18);

				ValidateValues(handler, "unknown", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					StackWatch<PacketHandler> watch_27(handler, "if output3.IsCustom");
					Read<std::string>("musicCode", handler, output3.MusicCode);
				}

				else
				{
					StackWatch<PacketHandler> watch_29(handler, "else");
					Read<std::wstring>("fileName", handler, output3.FileName);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 4");
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId);
				Read<int>("actorId", handler, output4.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 6");
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 8");
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var24", itemId_var24, output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					StackWatch<PacketHandler> watch_42(handler, "if itemId_var24 == 0");
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
				StackWatch<PacketHandler> watch_45(handler, "if mode_var0 == 9");
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);
				Read<int>("remainingUses", handler, output7.RemainingUses);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 10");
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId);
				Read<std::string>("musicCode", handler, output8.MusicCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_53(handler, "if mode_var0 == 14");
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_56(handler, "if mode_var0 == 17");
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30);

				ValidateValues(handler, "unknown", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xca>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xca 'ChangeAttributes' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ChangeAttributesPreviewChangePacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					StackWatch<PacketHandler> watch_6(handler, "if itemId_var2 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewChangePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::ChangeAttributesApplyPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var4", itemId_var4, output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					StackWatch<PacketHandler> watch_14(handler, "if itemId_var4 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesApplyPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 4");
				Server::ChangeAttributesErrorPacket output2;

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5);

				ValidateValues(handler, "unknown", unknown_var5, (bool)0, (bool)1);

				int message_var6 = 0;
				Read<int>("message", handler, message_var6);

				ValidateValues(handler, "message", message_var6, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesErrorPacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xcb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xcb 'ChangeAttributesScroll' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 2");
				Server::ChangeAttributesScrollPreviewChangePacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if itemId_var3 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v12(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewChangePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 3");
				Server::ChangeAttributesScrollApplyPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var5", itemId_var5, output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					StackWatch<PacketHandler> watch_17(handler, "if itemId_var5 == 0");
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
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::ChangeAttributesScrollErrorPacket output3;

				bool unknown_var6 = false;
				Read<bool>("unknown", handler, unknown_var6);

				ValidateValues(handler, "unknown", unknown_var6, (bool)0, (bool)1);

				int message_var7 = 0;
				Read<int>("message", handler, message_var7);

				ValidateValues(handler, "message", message_var7, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xce 'Pet' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId);
				Read<int>("petActorId", handler, output0.PetActorId);
				ParseFieldPetData_v12(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 1");
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId);
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 5");
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId);
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 6");
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId);
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 7");
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10);

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output6.Pets[", i, "]"); 
					Read<int>("petId", handler, output6.Pets[i].PetId);
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity);

					ValidateValues(handler, "petRarity", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 8");
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId);
				Read<short>("petRarity", handler, output7.PetRarity);

				ValidateValues(handler, "petRarity", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 9");
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId);
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
				StackWatch<PacketHandler> watch_42(handler, "if mode_var0 == 10");
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId);
				Read<long long>("exp", handler, output9.Exp);
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 11");
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId);
				Read<int>("level", handler, output10.Level);
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_52(handler, "if mode_var0 == 12");
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 15");
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned);

				ValidateValues(handler, "isSummoned", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_58(handler, "if mode_var0 == 16");
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId);
				Read<int>("itemId", handler, output13.ItemId);
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId);
				Read<int>("rarity", handler, output13.Rarity);

				ValidateValues(handler, "rarity", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_65(handler, "if mode_var0 == 17");
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output14.Rarity);

				ValidateValues(handler, "rarity", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount);

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var32", itemId_var32, output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					StackWatch<PacketHandler> watch_73(handler, "if itemId_var32 == 0");
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
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 18");
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId);
				Read<int>("points", handler, output15.Points);
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				StackWatch<PacketHandler> watch_81(handler, "if mode_var0 == 19");
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36);

				ValidateValues(handler, "message", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_84(handler, "if mode_var0 == 20");
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				StackWatch<PacketHandler> watch_87(handler, "if mode_var0 == 21");
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xd0 'PetInventory' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId);
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);
				Read<int>("rarity", handler, output0.Rarity);

				ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5);
				ParseItemData_v12(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 1");
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 2");
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<int>("amount", handler, output2.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 3");
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId);
				Read<short>("srcSlot", handler, output3.SourceSlot);
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId);
				Read<short>("dstSlot", handler, output3.DestinationSlot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 4");
				Server::PetInventoryListItemsPacket output4;

				short count_var13 = 0;
				Read<short>("count", handler, count_var13);

				ResizeVector(handler, output4.Slots, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_25(handler, "output4.Slots[", i, "]"); 
					Read<int>("itemId", handler, output4.Slots[i].ItemId);
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId);
					Read<short>("slot", handler, output4.Slots[i].Slot);
					Read<int>("rarity", handler, output4.Slots[i].Rarity);

					ValidateValues(handler, "rarity", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 6");
				Server::PetInventoryStartListPacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStartListPacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0xdd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xdd 'ItemLock' v12");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 2");
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 3");
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4);

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output2.Items[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId);

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var6", itemId_var6, output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						StackWatch<PacketHandler> watch_15(handler, "if itemId_var6 == 0");
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
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 4");
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x105>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x105 'BindItem' v12");

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var1", itemId_var1, output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				StackWatch<PacketHandler> watch_4(handler, "if itemId_var1 == 0");
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
		void ParsePacket<2486, ServerPacket, 0xcc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xcc 'Pet' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId);
				Read<int>("petActorId", handler, output0.PetActorId);
				ParseFieldPetData_v2486(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 1");
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId);
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 5");
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId);
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 6");
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId);
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 7");
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10);

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output6.Pets[", i, "]"); 
					Read<int>("petId", handler, output6.Pets[i].PetId);
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity);

					ValidateValues(handler, "petRarity", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 8");
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId);
				Read<short>("petRarity", handler, output7.PetRarity);

				ValidateValues(handler, "petRarity", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 9");
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId);
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
				StackWatch<PacketHandler> watch_42(handler, "if mode_var0 == 10");
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId);
				Read<long long>("exp", handler, output9.Exp);
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 11");
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId);
				Read<int>("level", handler, output10.Level);
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_52(handler, "if mode_var0 == 12");
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 15");
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned);

				ValidateValues(handler, "isSummoned", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_58(handler, "if mode_var0 == 16");
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId);
				Read<int>("itemId", handler, output13.ItemId);
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId);
				Read<int>("rarity", handler, output13.Rarity);

				ValidateValues(handler, "rarity", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_65(handler, "if mode_var0 == 17");
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output14.Rarity);

				ValidateValues(handler, "rarity", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount);

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var32", itemId_var32, output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					StackWatch<PacketHandler> watch_73(handler, "if itemId_var32 == 0");
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
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 18");
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId);
				Read<int>("points", handler, output15.Points);
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				StackWatch<PacketHandler> watch_81(handler, "if mode_var0 == 19");
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36);

				ValidateValues(handler, "message", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_84(handler, "if mode_var0 == 20");
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				StackWatch<PacketHandler> watch_87(handler, "if mode_var0 == 21");
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId);
				ParseFieldPetData_v2486(handler, output18.FieldPet);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetUnknownFieldPetPacket>(output18);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc 'CharacterList' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Characters[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);
				Read<long long>("characterId", handler, output2.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
			}
			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId);
				Read<int>("messageId", handler, output3.MessageId);
				Read<long long>("deleteTime", handler, output3.DeleteTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);
				Read<int>("messageId", handler, output4.MessageId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 7");
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x25 'ItemPutOn' v2486");

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<unsigned char>("slot", handler, output0.Slot);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x15 'ServerEnter' v2486");

			Server::ServerEnterPacket output0;

			Read<int>("playerActorId", handler, output0.PlayerActorId);
			Read<long long>("characterId", handler, output0.CharacterId);
			Read<short>("channelId", handler, output0.ChannelId);
			Read<long long>("exp", handler, output0.Exp);
			Read<long long>("restExp", handler, output0.RestExp);
			Read<long long>("mesos", handler, output0.Mesos);
			Read<long long>("totalMerets", handler, output0.TotalMerets);
			Read<long long>("merets", handler, output0.Merets);
			Read<long long>("totalGameMerets", handler, output0.TotalGameMerets);
			Read<long long>("gameMerets", handler, output0.GameMerets);
			Read<long long>("eventMerets", handler, output0.EventMerets);
			Read<long long>("valorTokens", handler, output0.ValorTokens);
			Read<long long>("treva", handler, output0.Treva);
			Read<long long>("rue", handler, output0.Rue);
			Read<long long>("haviFruit", handler, output0.HaviFruit);
			Read<long long>("reverseCoin", handler, output0.ReverseCoin);
			Read<long long>("mentorToken", handler, output0.MentorToken);
			Read<long long>("menteeToken", handler, output0.MenteeToken);
			Read<long long>("starPoint", handler, output0.StarPoint);
			Read<long long>("mesoToken", handler, output0.MesoToken);
			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);

			unsigned char unknown_var21 = 0;
			Read<unsigned char>("unknown", handler, unknown_var21);

			unsigned short unlockedMaps_var22 = 0;
			Read<unsigned short>("unlockedMaps", handler, unlockedMaps_var22);

			ResizeVector(handler, output0.UnlockedMaps, unlockedMaps_var22);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedMaps_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_24(handler, "output0.UnlockedMaps[", i, "]"); 
				Read<int>("mapId", handler, output0.UnlockedMaps[i].MapId);
			}

			unsigned short unlockedTaxis_var24 = 0;
			Read<unsigned short>("unlockedTaxis", handler, unlockedTaxis_var24);

			ResizeVector(handler, output0.UnlockedTaxis, unlockedTaxis_var24);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned short i = 0; i < unlockedTaxis_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_27(handler, "output0.UnlockedTaxis[", i, "]"); 
				Read<int>("mapId", handler, output0.UnlockedTaxis[i].MapId);
			}

			long long unknown_var26 = 0;
			Read<long long>("unknown", handler, unknown_var26);

			std::wstring unknown_var27;
			Read<std::wstring>("unknown", handler, unknown_var27);
			Read<std::wstring>("mapleNewsUrl", handler, output0.MapleNewsUrl);

			std::wstring unknown_var29;
			Read<std::wstring>("unknown", handler, unknown_var29);

			std::wstring nxCacheUrl_var30;
			Read<std::wstring>("nxCacheUrl", handler, nxCacheUrl_var30);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x27 'ItemSkinPutOn' v2486");

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<long long>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot);
			ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x97>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x97 'ItemEnchant' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 5");
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType);

				ValidateValues(handler, "enchantType", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3);

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_6(handler, "output0.Ingredients[", i, "]"); 
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4);
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem);

					ValidateValues(handler, "requiredItem", output0.Ingredients[i].RequiredItem, (int)96, (int)97, (int)98, (int)99, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount);
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7);

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8);

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_12(handler, "output0.Stats[", i, "]"); 
					ParseBasicStat_v12(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					StackWatch<PacketHandler> watch_14(handler, "if output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1");
					Read<float>("successRate", handler, output0.SuccessRate);
					Read<float>("unknownRate2", handler, output0.UnknownRate2);
					Read<float>("unknownRate3", handler, output0.UnknownRate3);
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate);
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate);

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14);

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15);

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16);
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					StackWatch<PacketHandler> watch_23(handler, "if output0.EnchantType >= 1 && output0.EnchantType <= 2");
					Read<int>("itemId", handler, output0.ItemId);
					Read<short>("rarity", handler, output0.Rarity);

					ValidateValues(handler, "rarity", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_27(handler, "if mode_var0 == 6");
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);
				Read<int>("enchantExp", handler, output1.EnchantExp);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 7");
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount);
				Read<int>("catalystWeight", handler, output2.CatalystWeight);

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24);

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_36(handler, "output2.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId);
				}
				Read<float>("successRate", handler, output2.SuccessRate);
				Read<float>("unknownRate2", handler, output2.UnknownRate2);
				Read<float>("unknownRate3", handler, output2.UnknownRate3);
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate);
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 8");
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight);

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32);

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_47(handler, "output3.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 9");
			}
			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 10");
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var35", itemId_var35, output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					StackWatch<PacketHandler> watch_55(handler, "if itemId_var35 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36);

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_59(handler, "output4.Stats[", i, "]"); 
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
				StackWatch<PacketHandler> watch_61(handler, "if mode_var0 == 11");
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var38", itemId_var38, output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					StackWatch<PacketHandler> watch_66(handler, "if itemId_var38 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39);

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40);

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41);
				Read<int>("failStacks", handler, output5.FailStacks);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_73(handler, "if mode_var0 == 12");
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 15");
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44);
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_78(handler, "if mode_var0 == 16");
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v2486");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
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

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_32(handler, "if statCount_var4 != 35");
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_33(handler, "output0.Stats.Basic[", i, "]"); 
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type);

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_35(handler, "if output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4");
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current);
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_39(handler, "if output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4");
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current);
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35);

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_51(handler, "if output0.OnMount");
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_59(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_64(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_68(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46);

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_71(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52);

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53);

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55);

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_89(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67);

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68);

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1e 'UserChatItemLink' v2486");

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0);

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_2(handler, "output0.Items[", i, "]"); 
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
				Read<int>("itemId", handler, output0.Items[i].ItemId);
				Read<int>("rarity", handler, output0.Items[i].Rarity);

				ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x23 'FurnishingStorage' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 2");
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 3");
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot);
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);
				Read<int>("count", handler, output4.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 7");
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);
				Read<int>("count", handler, output5.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 8");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2a 'ItemUpdate' v2486");

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				StackWatch<PacketHandler> watch_5(handler, "if itemId_var2 == 0");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2b 'FieldAddItem' v2486");

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<int>("amount", handler, output0.Amount);
			Read<long long>("uid", handler, output0.ItemInstanceId);
			Read<Vector3S>("position", handler, output0.Position);
			Read<int>("ownerId", handler, output0.OwnerId);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8);

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9);

			ValidateValues(handler, "unknown", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10);

			ValidateValues(handler, "unknown", unknown_var10, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				StackWatch<PacketHandler> watch_12(handler, "if output0.ItemId < 90000001 || output0.ItemId > 90000003");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3d 'SkillDamage' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<int>("casterId", handler, output0.CasterId);
				Read<unsigned int>("skillId", handler, output0.SkillId);
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel);
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint);
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint);
				Read<Vector3Short>("position", handler, output0.Position);
				Read<Vector3S>("direction", handler, output0.Direction);
				Read<bool>("isChaining", handler, output0.IsChaining);

				ValidateValues(handler, "isChaining", output0.IsChaining, (bool)0, (bool)1);

				unsigned char count_var10 = 0;
				Read<unsigned char>("count", handler, count_var10);

				ResizeVector(handler, output0.Hits, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_13(handler, "output0.Hits[", i, "]"); 
					long long unknown_var11 = 0;
					Read<long long>("unknown", handler, unknown_var11);
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack);
					Read<int>("targetId", handler, output0.Hits[i].TargetId);
					Read<short>("animation", handler, output0.Hits[i].Animation);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 3");
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<int>("damage", handler, output2.Damage);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_28(handler, "if mode_var0 == 5");
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
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 6");
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
				StackWatch<PacketHandler> watch_34(handler, "if mode_var0 == 7");
				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16);

				int count_var17 = 0;
				Read<int>("count", handler, count_var17);

				for (int i = 0; i < count_var17 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_37(handler, "array1[", i, "]"); 
					int unknown_var18 = 0;
					Read<int>("unknown", handler, unknown_var18);
				}
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 8");
				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19);

				bool hasTarget_var20 = false;
				Read<bool>("hasTarget", handler, hasTarget_var20);

				ValidateValues(handler, "hasTarget", hasTarget_var20, (bool)0, (bool)1);

				if (hasTarget_var20)
				{
					StackWatch<PacketHandler> watch_42(handler, "if hasTarget_var20");
					unsigned int skillId_var21 = 0;
					Read<unsigned int>("skillId", handler, skillId_var21);

					unsigned short skillLevel_var22 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var22);

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23);

					int npcId_var24 = 0;
					Read<int>("npcId", handler, npcId_var24);
				}
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x37>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x37 'ExpUp' v2486");

			Server::ExpUpPacket output0;

			Read<bool>("isRestExp", handler, output0.IsRestExp);

			ValidateValues(handler, "isRestExp", output0.IsRestExp, (bool)0, (bool)1);

			if (output0.IsRestExp == 0)
			{
				StackWatch<PacketHandler> watch_2(handler, "if output0.IsRestExp == 0");
				Read<long long>("expGained", handler, output0.ExpGained);

				short unknown_var2 = 0;
				Read<short>("unknown", handler, unknown_var2);
				Read<long long>("totalExp", handler, output0.TotalExp);
				Read<long long>("restExp", handler, output0.RestExp);
				Read<int>("message", handler, output0.Message);
				Read<bool>("additional", handler, output0.Additional);

				ValidateValues(handler, "additional", output0.Additional, (bool)0, (bool)1);
			}

			if (output0.IsRestExp)
			{
				StackWatch<PacketHandler> watch_9(handler, "if output0.IsRestExp");
				Read<long long>("restExp", handler, output0.RestExp);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ExpUpPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x4b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x4b 'NpcTalk' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 1");
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId);
				Read<unsigned char>("flags", handler, output1.Flags);
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 2");
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags);
				Read<int>("actorId", handler, output2.ActorId);
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5);

				ValidateValues(handler, "actionMode", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					StackWatch<PacketHandler> watch_15(handler, "if actionMode_var5 == 1");
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6);
				}

				if (actionMode_var5 == 3)
				{
					StackWatch<PacketHandler> watch_17(handler, "if actionMode_var5 == 3");
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					StackWatch<PacketHandler> watch_20(handler, "if actionMode_var5 == 4");
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8);

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					StackWatch<PacketHandler> watch_24(handler, "if actionMode_var5 == 5");
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10);

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_27(handler, "output5.Items[", i, "]"); 
						Read<int>("itemId", handler, output5.Items[i].ItemId);
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

						ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount);
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
					StackWatch<PacketHandler> watch_32(handler, "if actionMode_var5 == 6");
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					StackWatch<PacketHandler> watch_35(handler, "if actionMode_var5 == 7");
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					StackWatch<PacketHandler> watch_38(handler, "if actionMode_var5 == 8");
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
					StackWatch<PacketHandler> watch_41(handler, "if actionMode_var5 == 9");
				}
				if (actionMode_var5 == 10)
				{
					StackWatch<PacketHandler> watch_42(handler, "if actionMode_var5 == 10");
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17);

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_46(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 8");
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20);
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_54(handler, "if mode_var0 == 9");
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags);
				ParseNpcDialog_v12(handler, output12.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x51>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x51 'Shop' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11, (unsigned char)12, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output1.Items[", i, "]"); 
					Read<int>("entryId", handler, output1.Items[i].EntryId);
					Read<int>("itemId", handler, output1.Items[i].ItemId);
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
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 2");
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId);
				Read<int>("buyCount", handler, output2.BuyCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 4");
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId);
				Read<int>("buyCount", handler, output3.BuyCount);
				Read<int>("totalPrice", handler, output3.TotalPrice);
				Read<unsigned char>("fontColor", handler, output3.FontColor);
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage);

				ValidateValues(handler, "toGuildStorage", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_23(handler, "if mode_var0 == 6");
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 7");
				Server::ShopAddBuyBackPacket output5;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12);

				ResizeVector(handler, output5.Items, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output5.Items[", i, "]"); 
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId);
					Read<int>("itemId", handler, output5.Items[i].ItemId);
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

					ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price);
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
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 8");
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_38(handler, "if mode_var0 == 9");
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock);

				ValidateValues(handler, "restock", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					StackWatch<PacketHandler> watch_41(handler, "if output7.Restock");
					int unknown_var19 = 0;
					Read<int>("unknown", handler, unknown_var19);

					ValidateValues(handler, "unknown", unknown_var19, (int)0);

					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20);

					ValidateValues(handler, "unknown", unknown_var20, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_44(handler, "if mode_var0 == 11");
				Server::ShopMeretItemCountPacket output8;

				Read<short>("count", handler, output8.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopMeretItemCountPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 12");
				Server::ShopLoadMeretItemPacket output9;

				unsigned char count_var22 = 0;
				Read<unsigned char>("count", handler, count_var22);

				ResizeVector(handler, output9.Items, count_var22);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_50(handler, "output9.Items[", i, "]"); 
					ParseMeretShopPremiumItemEntry_v2486(handler, output9.Items[i].MeretItemEntry);

					unsigned char unknown_var23 = 0;
					Read<unsigned char>("unknown", handler, unknown_var23);

					int unknown_var24 = 0;
					Read<int>("unknown", handler, unknown_var24);

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 13");
				int npcId_var26 = 0;
				Read<int>("npcId", handler, npcId_var26);

				int shopId_var27 = 0;
				Read<int>("shopId", handler, shopId_var27);

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28);

				short unknown_var29 = 0;
				Read<short>("unknown", handler, unknown_var29);
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_60(handler, "if mode_var0 == 14");
				Server::ShopLoadNewPacket output10;

				short count_var30 = 0;
				Read<short>("count", handler, count_var30);

				ResizeVector(handler, output10.Items, count_var30);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var30 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_63(handler, "output10.Items[", i, "]"); 
					Read<int>("itemId", handler, output10.Items[i].ItemId);

					bool unknown_var32 = false;
					Read<bool>("unknown", handler, unknown_var32);

					ValidateValues(handler, "unknown", unknown_var32, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output10.Items[i].Rarity);

					ValidateValues(handler, "rarity", output10.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var34;
					Read<std::string>("unknown", handler, unknown_var34);

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35);

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36);
					Read<bool>("hasBuyPeriod", handler, output10.Items[i].HasBuyPeriod);

					ValidateValues(handler, "hasBuyPeriod", output10.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output10.Items[i].HasBuyPeriod)
					{
						StackWatch<PacketHandler> watch_71(handler, "if output10.Items[i].HasBuyPeriod");
						ParseBuyPeriodData_v12(handler, output10.Items[i].BuyPeriod);
					}
					ParseItemData_v2486(handler, output10.Items[i].ItemData, (unsigned int)output10.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_74(handler, "if mode_var0 == 15");
				Server::ShopErrorPacket output11;

				Read<int>("message", handler, output11.Message);

				unsigned char unknown_var39 = 0;
				Read<unsigned char>("unknown", handler, unknown_var39);
				Read<int>("stringId", handler, output11.StringId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output11);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x54>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x54 'Mail' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Mail[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId);
				Read<long long>("readTime", handler, output2.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 10");
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId);

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7);

				ValidateValues(handler, "unknownCondition", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				ValidateValues(handler, "unknown", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 11");
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId);
				Read<long long>("readTime", handler, output5.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 12");
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12);

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13);
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 13");
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 14");
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount);
				Read<bool>("alert", handler, output7.Alert);

				ValidateValues(handler, "alert", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 15");
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 16");
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 17");
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 20");
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18);
				Read<unsigned char>("message", handler, output11.Message);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 22");
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23);

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24);

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25);

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x78 'CharacterInfo' v2486");

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId);
			Read<bool>("found", handler, output0.Found);

			ValidateValues(handler, "found", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				StackWatch<PacketHandler> watch_3(handler, "if output0.Found");
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2);

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3);
				Read<long long>("currentTime", handler, output0.CurrentTime);

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_8(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						StackWatch<PacketHandler> watch_10(handler, "output0.Details.Stats");
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_15(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_19(handler, "buffer[", bufferSize_var5, "]");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x7b 'FittingDoll' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId);
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId);
				Read<int>("dollItemId", handler, output0.DollItemId);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("rotation", handler, output0.Rotation);
				Read<bool>("hasItems", handler, output0.HasItems);

				ValidateValues(handler, "hasItems", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7);

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "output0.Items[", i, "]"); 
					Read<int>("itemId", handler, output0.Items[i].ItemId);
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
					Read<unsigned char>("slot", handler, output0.Items[i].Slot);
					Read<int>("rarity", handler, output0.Items[i].Rarity);

					ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 1");
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 4");
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId);
				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<unsigned char>("slot", handler, output2.Slot);
				Read<int>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 7");
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);
				Read<unsigned char>("slot", handler, output3.Slot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 8");
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 11");
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x82>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x82 'Trade' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)13);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName);
				Read<long long>("characterId", handler, output0.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 1");
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message);
				Read<std::wstring>("name", handler, output1.Name);
				Read<int>("itemId", handler, output1.ItemId);
				Read<int>("level", handler, output1.Level);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 6");
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success);

				ValidateValues(handler, "success", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 8");
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index);

				ValidateValues(handler, "index", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId);
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);
				Read<int>("rarity", handler, output6.Rarity);

				ValidateValues(handler, "rarity", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot);
				Read<int>("amount", handler, output6.Amount);
				Read<int>("tradeSlot2", handler, output6.TradeSlot2);
				ParseItemData_v2486(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 9");
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index);

				ValidateValues(handler, "index", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot);
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 10");
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index);
				Read<long long>("mesos", handler, output8.Mesos);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 11");
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_44(handler, "if mode_var0 == 12");
				Server::TradeChangeOfferPacket output10;

				Read<unsigned char>("index", handler, output10.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeChangeOfferPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 13");
				Server::TradeFinalizeConfirmPacket output11;

				Read<unsigned char>("index", handler, output11.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 14");
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x98>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x98 'BlackMarket' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1);
				Read<int>("errorCode", handler, output0.ErrorCode);
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId);

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4);

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6);

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output1.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 3");
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9);

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_23(handler, "output4.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 5");
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId);
				Read<int>("amount", handler, output5.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 6");
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14);
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 7");
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 8");
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId);
				Read<int>("rarity", handler, output7.Rarity);

				ValidateValues(handler, "rarity", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice);

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 9");
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xbf>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xbf 'EnchantScroll' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 3");
				short result_var1 = 0;
				Read<short>("result", handler, result_var1);

				ValidateValues(handler, "result", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if result_var1 == 0");
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						StackWatch<PacketHandler> watch_14(handler, "if itemId_var3 == 0");
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
					StackWatch<PacketHandler> watch_17(handler, "else");
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);

						CalledFunction(handler, "Copy", "output3.Result", output3.Result, result_var1);
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
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 4");
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5);

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_24(handler, "output4.Data[", i, "]"); 
					Read<int>("itemId", handler, output4.Data[i].ItemId);

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc7 'PlayInstrument' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId);
				Read<int>("actorId", handler, output0.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition);
				Read<int>("gmId", handler, output0.GMId);
				Read<int>("percussionId", handler, output0.PercussionId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId);
				Read<int>("actorId", handler, output1.ActorId);
				Read<int>("midiNote", handler, output1.MidiNote);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId);
				Read<int>("actorId", handler, output2.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 3");
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom);

				ValidateValues(handler, "isCustom", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId);
				Read<int>("actorId", handler, output3.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition);
				Read<int>("instrumentTick", handler, output3.InstrumentTick);
				Read<int>("gmId", handler, output3.GMId);
				Read<int>("percussionId", handler, output3.PercussionId);

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18);

				ValidateValues(handler, "unknown", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					StackWatch<PacketHandler> watch_27(handler, "if output3.IsCustom");
					Read<std::string>("musicCode", handler, output3.MusicCode);
				}

				else
				{
					StackWatch<PacketHandler> watch_29(handler, "else");
					Read<std::wstring>("fileName", handler, output3.FileName);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 4");
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId);
				Read<int>("actorId", handler, output4.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 6");
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 8");
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var24", itemId_var24, output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					StackWatch<PacketHandler> watch_42(handler, "if itemId_var24 == 0");
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
				StackWatch<PacketHandler> watch_45(handler, "if mode_var0 == 9");
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);
				Read<int>("remainingUses", handler, output7.RemainingUses);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 10");
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId);
				Read<std::string>("musicCode", handler, output8.MusicCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_53(handler, "if mode_var0 == 14");
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_56(handler, "if mode_var0 == 17");
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30);

				ValidateValues(handler, "unknown", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc8 'ChangeAttributes' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ChangeAttributesPreviewChangePacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					StackWatch<PacketHandler> watch_6(handler, "if itemId_var2 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewChangePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::ChangeAttributesApplyPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var4", itemId_var4, output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					StackWatch<PacketHandler> watch_14(handler, "if itemId_var4 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesApplyPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 4");
				Server::ChangeAttributesErrorPacket output2;

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5);

				ValidateValues(handler, "unknown", unknown_var5, (bool)0, (bool)1);

				int message_var6 = 0;
				Read<int>("message", handler, message_var6);

				ValidateValues(handler, "message", message_var6, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc9 'ChangeAttributesScroll' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 2");
				Server::ChangeAttributesScrollPreviewChangePacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if itemId_var3 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewChangePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 3");
				Server::ChangeAttributesScrollApplyPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var5", itemId_var5, output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					StackWatch<PacketHandler> watch_17(handler, "if itemId_var5 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2486(handler, output2.ItemData, (unsigned int)itemId_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::ChangeAttributesScrollErrorPacket output3;

				bool unknown_var6 = false;
				Read<bool>("unknown", handler, unknown_var6);

				ValidateValues(handler, "unknown", unknown_var6, (bool)0, (bool)1);

				int message_var7 = 0;
				Read<int>("message", handler, message_var7);

				ValidateValues(handler, "message", message_var7, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0xce>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xce 'PetInventory' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId);
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);
				Read<int>("rarity", handler, output0.Rarity);

				ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				std::wstring unknown_var5;
				Read<std::wstring>("unknown", handler, unknown_var5);
				ParseItemData_v2486(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 1");
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 2");
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<int>("amount", handler, output2.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 3");
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId);
				Read<short>("srcSlot", handler, output3.SourceSlot);
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId);
				Read<short>("dstSlot", handler, output3.DestinationSlot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 4");
				Server::PetInventoryListItemsPacket output4;

				int count_var13 = 0;
				Read<int>("count", handler, count_var13);

				ResizeVector(handler, output4.Slots, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_25(handler, "output4.Slots[", i, "]"); 
					Read<int>("itemId", handler, output4.Slots[i].ItemId);
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId);
					Read<short>("slot", handler, output4.Slots[i].Slot);
					Read<int>("rarity", handler, output4.Slots[i].Rarity);

					ValidateValues(handler, "rarity", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 6");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xdb 'ItemLock' v2486");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 2");
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 3");
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4);

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output2.Items[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId);

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var6", itemId_var6, output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						StackWatch<PacketHandler> watch_15(handler, "if itemId_var6 == 0");
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
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 4");
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x103>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x103 'BindItem' v2486");

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var1", itemId_var1, output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				StackWatch<PacketHandler> watch_4(handler, "if itemId_var1 == 0");
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
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x3 'LogIn' v13");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			std::wstring auth1_var1;
			Read<std::wstring>("auth1", handler, auth1_var1);

			std::wstring auth2_var2;
			Read<std::wstring>("auth2", handler, auth2_var2);

			unsigned long long unknown_var3 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var3);

			unsigned long long unknown_var4 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var4);

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5);

			short unknown_var6 = 0;
			Read<short>("unknown", handler, unknown_var6);

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7);

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8);
		}

		template <>
		void ParsePacket<13, ServerPacket, 0xb>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xb 'ServerList' v13");

			Server::ServerListPacket output0;

			std::string env_var0;
			Read<std::string>("env", handler, env_var0);

			bool loadServers_var1 = false;
			Read<bool>("loadServers", handler, loadServers_var1);

			ValidateValues(handler, "loadServers", loadServers_var1, (bool)0, (bool)1);

			if (loadServers_var1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if loadServers_var1");
				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);

				std::wstring serverName_var3;
				Read<std::wstring>("serverName", handler, serverName_var3);

				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);

				short count_var5 = 0;
				Read<short>("count", handler, count_var5);

				ResizeVector(handler, output0.Servers, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_8(handler, "output0.Servers[", i, "]"); 
					std::wstring ipAddress_var6;
					Read<std::wstring>("ipAddress", handler, ipAddress_var6);

					short port_var7 = 0;
					Read<short>("port", handler, port_var7);
				}

				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8);

				short count2_var9 = 0;
				Read<short>("count2", handler, count2_var9);

				ResizeVector(handler, output0.Channels, count2_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count2_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_13(handler, "output0.Channels[", i, "]"); 
					short channel_var10 = 0;
					Read<short>("channel", handler, channel_var10);
				}
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ServerListPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x47 'Buff' v13");

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			Read<int>("targetId", handler, output0.Effect.TargetId);
			Read<int>("instanceId", handler, output0.Effect.InstanceId);
			Read<int>("sourceId", handler, output0.Effect.SourceId);

			if (output0.Mode == (Server::BuffPacket::ModeEnum)0)
			{
				StackWatch<PacketHandler> watch_5(handler, "if output0.Mode == (Server::BuffPacket::ModeEnum)0");
				ParseEffectStats_v12(handler, output0.Effect.Stats);

				Read<bool>("enabled", handler, output0.Effect.Enabled);

				ValidateValues(handler, "enabled", output0.Effect.Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth);
			}

			if (output0.Mode == (Server::BuffPacket::ModeEnum)2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if output0.Mode == (Server::BuffPacket::ModeEnum)2");
				int flags_var6 = 0;
				Read<int>("flags", handler, flags_var6);

				output0.UpdateEffect = GetBit(flags_var6, 0);
				output0.UpdateShield = GetBit(flags_var6, 1);

				if (GetBit(flags_var6, 0) == 1)
				{
					StackWatch<PacketHandler> watch_11(handler, "if GetBit(flags_var6, 0) == 1");
					ParseEffectStats_v12(handler, output0.Effect.Stats);

					Read<bool>("enabled", handler, output0.Effect.Enabled);

					ValidateValues(handler, "enabled", output0.Effect.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var6, 1) == 1)
				{
					StackWatch<PacketHandler> watch_14(handler, "if GetBit(flags_var6, 1) == 1");
					Read<long long>("shieldHealth", handler, output0.Effect.ShieldHealth);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v13");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v12(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
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

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_32(handler, "if statCount_var4 != 35");
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_33(handler, "output0.Stats.Basic[", i, "]"); 
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type);

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_35(handler, "if output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4");
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current);
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_39(handler, "if output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4");
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current);
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35);

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_51(handler, "if output0.OnMount");
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_59(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v12(handler, output0.Equipment);
				ParseCharacterEquipmentSkinsMandatory_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_64(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v12(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_68(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v12(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46);

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_71(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52);

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53);

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55);

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_89(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v12(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67);

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68);

			int mushkingTailKillCount_var69 = 0;
			Read<int>("mushkingTailKillCount", handler, mushkingTailKillCount_var69);

			int unknownCount_var70 = 0;
			Read<int>("unknownCount", handler, unknownCount_var70);

			ResizeVector(handler, output0.UnknownData, unknownCount_var70);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < unknownCount_var70 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_99(handler, "output0.UnknownData[", i, "]"); 
				int unknown_var71 = 0;
				Read<int>("unknown", handler, unknown_var71);

				std::wstring unknown_var72;
				Read<std::wstring>("unknown", handler, unknown_var72);
			}

			short unknown_var73 = 0;
			Read<short>("unknown", handler, unknown_var73);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddPlayerPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x1c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1c 'UserSync' v13");

			Server::UserSyncPacket output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0);

			unsigned char count_var1 = 0;
			Read<unsigned char>("count", handler, count_var1);

			ResizeVector(handler, output0.StateData, count_var1);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_3(handler, "output0.StateData[", i, "]"); 
				ParseStateSyncData_v13(handler, output0.StateData[i]);
			}

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::UserSyncPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xcc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xcc 'Pet' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)9, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)18, (unsigned char)19, (unsigned char)20, (unsigned char)21);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetAddPacket output0;

				Read<int>("playerActorId", handler, output0.PlayerActorId);
				Read<int>("petActorId", handler, output0.PetActorId);
				ParseFieldPetData_v2497(handler, output0.FieldPet);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 1");
				Server::PetRemovePacket output1;

				Read<int>("playerActorId", handler, output1.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::PetSoundPacket output2;

				Read<int>("playerActorId", handler, output2.PlayerActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSoundPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				Server::PetRenamePacket output3;

				Read<int>("playerActorId", handler, output3.PlayerActorId);
				ParsePetProfileData_v12(handler, output3.PetProfile);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetRenamePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 5");
				Server::PetPotionPacket output4;

				Read<int>("playerActorId", handler, output4.PlayerActorId);
				ParsePetPotionSettingsData_v12(handler, output4.PetPotionSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetPotionPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 6");
				Server::PetLootPacket output5;

				Read<int>("playerActorId", handler, output5.PlayerActorId);
				ParsePetLootSettingsData_v12(handler, output5.PetLootSettings);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLootPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 7");
				Server::PetLoadCollectionPacket output6;

				int count_var10 = 0;
				Read<int>("count", handler, count_var10);

				ResizeVector(handler, output6.Pets, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_29(handler, "output6.Pets[", i, "]"); 
					Read<int>("petId", handler, output6.Pets[i].PetId);
					Read<short>("petRarity", handler, output6.Pets[i].PetRarity);

					ValidateValues(handler, "petRarity", output6.Pets[i].PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLoadCollectionPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 8");
				Server::PetAddCollectionPacket output7;

				Read<int>("petId", handler, output7.PetId);
				Read<short>("petRarity", handler, output7.PetRarity);

				ValidateValues(handler, "petRarity", output7.PetRarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetAddCollectionPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 9");
				Server::PetInfoPacket output8;

				Read<int>("playerActorId", handler, output8.PlayerActorId);
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
				StackWatch<PacketHandler> watch_42(handler, "if mode_var0 == 10");
				Server::PetFusionPacket output9;

				Read<int>("playerActorId", handler, output9.PlayerActorId);
				Read<long long>("exp", handler, output9.Exp);
				Read<long long>("itemInstanceId", handler, output9.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 11");
				Server::PetLevelUpPacket output10;

				Read<int>("playerActorId", handler, output10.PlayerActorId);
				Read<int>("level", handler, output10.Level);
				Read<long long>("itemInstanceId", handler, output10.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLevelUpPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_52(handler, "if mode_var0 == 12");
				Server::PetFusionDialogPacket output11;

				Read<int>("fusionCount", handler, output11.FusionCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetFusionDialogPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 15");
				Server::PetSummonedNoticePacket output12;

				Read<bool>("isSummoned", handler, output12.IsSummoned);

				ValidateValues(handler, "isSummoned", output12.IsSummoned, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetSummonedNoticePacket>(output12);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_58(handler, "if mode_var0 == 16");
				Server::PetOtherPetInfoPacket output13;

				Read<int>("playerActorId", handler, output13.PlayerActorId);
				Read<int>("itemId", handler, output13.ItemId);
				Read<long long>("itemInstanceId", handler, output13.ItemInstanceId);
				Read<int>("rarity", handler, output13.Rarity);

				ValidateValues(handler, "rarity", output13.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output13.ItemData, (unsigned int)output13.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetOtherPetInfoPacket>(output13);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_65(handler, "if mode_var0 == 17");
				Server::PetEvolvePacket output14;

				Read<int>("playerActorId", handler, output14.PlayerActorId);
				Read<long long>("itemInstanceId", handler, output14.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output14.Rarity);

				ValidateValues(handler, "rarity", output14.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("amount", handler, output14.Amount);

				int itemId_var32 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var32 = handler.GetItemIdFromInstance(output14.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var32", itemId_var32, output14.ItemInstanceId);
				}

				if (itemId_var32 == 0)
				{
					StackWatch<PacketHandler> watch_73(handler, "if itemId_var32 == 0");
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
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 18");
				Server::PetEvolvePointsPacket output15;

				Read<int>("playerActorId", handler, output15.PlayerActorId);
				Read<int>("points", handler, output15.Points);
				Read<long long>("itemInstanceId", handler, output15.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetEvolvePointsPacket>(output15);
				}


				return;
			}

			if (mode_var0 == 19)
			{
				StackWatch<PacketHandler> watch_81(handler, "if mode_var0 == 19");
				Server::PetErrorPacket output16;

				int message_var36 = 0;
				Read<int>("message", handler, message_var36);

				ValidateValues(handler, "message", message_var36, (int)27, (int)28, (int)30, (int)32, (int)33, (int)39);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetErrorPacket>(output16);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_84(handler, "if mode_var0 == 20");
				Server::PetLapisSnarePacket output17;

				Read<int>("itemId", handler, output17.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetLapisSnarePacket>(output17);
				}


				return;
			}

			if (mode_var0 == 21)
			{
				StackWatch<PacketHandler> watch_87(handler, "if mode_var0 == 21");
				Server::PetUnknownFieldPetPacket output18;

				Read<int>("playerActorId", handler, output18.PlayerActorId);
				ParseFieldPetData_v2497(handler, output18.FieldPet);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetUnknownFieldPetPacket>(output18);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc 'CharacterList' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Characters[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);
				Read<long long>("characterId", handler, output2.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
			}
			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId);
				Read<int>("messageId", handler, output3.MessageId);
				Read<long long>("deleteTime", handler, output3.DeleteTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);
				Read<int>("messageId", handler, output4.MessageId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 7");
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x27 'ItemSkinPutOn' v2497");

			Server::ItemSkinPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<long long>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (long long)0, (long long)1, (long long)2, (long long)3, (long long)4, (long long)5, (long long)6);

			Read<long long>("slot", handler, output0.Slot);
			ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::ItemSkinPutOnPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x97>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x97 'ItemEnchant' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10, (unsigned char)11, (unsigned char)12);

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 5");
				Server::ItemEnchantBeginPacket output0;

				Read<short>("enchantType", handler, output0.EnchantType);

				ValidateValues(handler, "enchantType", output0.EnchantType, (short)1, (short)2);

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				unsigned char ingredientInfoCount_var3 = 0;
				Read<unsigned char>("ingredientInfoCount", handler, ingredientInfoCount_var3);

				ResizeVector(handler, output0.Ingredients, ingredientInfoCount_var3);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < ingredientInfoCount_var3 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_6(handler, "output0.Ingredients[", i, "]"); 
					int unknown_var4 = 0;
					Read<int>("unknown", handler, unknown_var4);
					Read<int>("requiredItem", handler, output0.Ingredients[i].RequiredItem);

					ValidateValues(handler, "requiredItem", output0.Ingredients[i].RequiredItem, (int)96, (int)97, (int)98, (int)99, (int)100, (int)101, (int)102);

					Read<int>("amount", handler, output0.Ingredients[i].Amount);
				}

				short unknown_var7 = 0;
				Read<short>("unknown", handler, unknown_var7);

				int statCount_var8 = 0;
				Read<int>("statCount", handler, statCount_var8);

				ResizeVector(handler, output0.Stats, statCount_var8);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var8 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_12(handler, "output0.Stats[", i, "]"); 
					ParseBasicStat_v2497(handler, output0.Stats[i]);
				}

				if (output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1)
				{
					StackWatch<PacketHandler> watch_14(handler, "if output0.EnchantType == (Server::ItemEnchantBeginPacket::EnchantTypeEnum)1");
					Read<float>("successRate", handler, output0.SuccessRate);
					Read<float>("unknownRate2", handler, output0.UnknownRate2);
					Read<float>("unknownRate3", handler, output0.UnknownRate3);
					Read<float>("catalystTotalRate", handler, output0.CatalystTotalRate);
					Read<float>("chargeTotalRate", handler, output0.ChargeTotalRate);

					long long unknown_var14 = 0;
					Read<long long>("unknown", handler, unknown_var14);

					long long unknown_var15 = 0;
					Read<long long>("unknown", handler, unknown_var15);

					unsigned char unknown_var16 = 0;
					Read<unsigned char>("unknown", handler, unknown_var16);
				}

				if (output0.EnchantType >= 1 && output0.EnchantType <= 2)
				{
					StackWatch<PacketHandler> watch_23(handler, "if output0.EnchantType >= 1 && output0.EnchantType <= 2");
					Read<int>("itemId", handler, output0.ItemId);
					Read<short>("rarity", handler, output0.Rarity);

					ValidateValues(handler, "rarity", output0.Rarity, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6);

					Read<int>("amount", handler, output0.Amount);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantBeginPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_27(handler, "if mode_var0 == 6");
				Server::ItemEnchantUpdateExpPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);
				Read<int>("enchantExp", handler, output1.EnchantExp);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateExpPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 7");
				Server::ItemEnchantUpdateChargesPacket output2;

				Read<int>("chargeCount", handler, output2.ChargeCount);
				Read<int>("catalystWeight", handler, output2.CatalystWeight);

				int catalystCount_var24 = 0;
				Read<int>("catalystCount", handler, catalystCount_var24);

				ResizeVector(handler, output2.Catalysts, catalystCount_var24);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var24 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_36(handler, "output2.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Catalysts[i].ItemInstanceId);
				}
				Read<float>("successRate", handler, output2.SuccessRate);
				Read<float>("unknownRate2", handler, output2.UnknownRate2);
				Read<float>("unknownRate3", handler, output2.UnknownRate3);
				Read<float>("catalystTotalRate", handler, output2.CatalystTotalRate);
				Read<float>("chargeTotalRate", handler, output2.ChargeTotalRate);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateChargesPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 8");
				Server::ItemEnchantUpdateIngredientsPacket output3;

				Read<int>("catalystWeight", handler, output3.CatalystWeight);

				int catalystCount_var32 = 0;
				Read<int>("catalystCount", handler, catalystCount_var32);

				ResizeVector(handler, output3.Catalysts, catalystCount_var32);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < catalystCount_var32 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_47(handler, "output3.Catalysts[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output3.Catalysts[i].ItemInstanceId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 9");
			}
			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 10");
				Server::ItemEnchantSuccessPacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);

				int itemId_var35 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var35 = handler.GetItemIdFromInstance(output4.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var35", itemId_var35, output4.ItemInstanceId);
				}

				if (itemId_var35 == 0)
				{
					StackWatch<PacketHandler> watch_55(handler, "if itemId_var35 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output4.ItemData, (unsigned int)itemId_var35);

				int statCount_var36 = 0;
				Read<int>("statCount", handler, statCount_var36);

				ResizeVector(handler, output4.Stats, statCount_var36);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < statCount_var36 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_59(handler, "output4.Stats[", i, "]"); 
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
				StackWatch<PacketHandler> watch_61(handler, "if mode_var0 == 11");
				Server::ItemEnchantFailPacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);

				int itemId_var38 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var38 = handler.GetItemIdFromInstance(output5.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var38", itemId_var38, output5.ItemInstanceId);
				}

				if (itemId_var38 == 0)
				{
					StackWatch<PacketHandler> watch_66(handler, "if itemId_var38 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output5.ItemData, (unsigned int)itemId_var38);

				int unknown_var39 = 0;
				Read<int>("unknown", handler, unknown_var39);

				int unknown_var40 = 0;
				Read<int>("unknown", handler, unknown_var40);

				long long unknown_var41 = 0;
				Read<long long>("unknown", handler, unknown_var41);
				Read<int>("failStacks", handler, output5.FailStacks);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantFailPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_73(handler, "if mode_var0 == 12");
				Server::ItemEnchantErrorPacket output6;

				Read<short>("code", handler, output6.Code);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemEnchantErrorPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_76(handler, "if mode_var0 == 15");
				long long itemInstanceId_var44 = 0;
				Read<long long>("itemInstanceId", handler, itemInstanceId_var44);
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_78(handler, "if mode_var0 == 16");
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v2497");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2493(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
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

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_32(handler, "if statCount_var4 != 35");
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_33(handler, "output0.Stats.Basic[", i, "]"); 
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type);

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_35(handler, "if output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4");
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current);
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_39(handler, "if output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4");
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current);
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35);

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_51(handler, "if output0.OnMount");
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_59(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2497(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2497(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_64(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2497(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_68(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2497(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46);

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_71(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52);

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53);

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55);

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_89(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67);

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68);

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x1e 'UserChatItemLink' v2497");

			Server::UserChatItemLinkPacket output0;

			int count_var0 = 0;
			Read<int>("count", handler, count_var0);

			ResizeVector(handler, output0.Items, count_var0);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (int i = 0; i < count_var0 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_2(handler, "output0.Items[", i, "]"); 
				Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
				Read<int>("itemId", handler, output0.Items[i].ItemId);
				Read<int>("rarity", handler, output0.Items[i].Rarity);

				ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2b 'FieldAddItem' v2497");

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<int>("amount", handler, output0.Amount);
			Read<long long>("uid", handler, output0.ItemInstanceId);
			Read<Vector3S>("position", handler, output0.Position);
			Read<int>("ownerId", handler, output0.OwnerId);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8);

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9);

			ValidateValues(handler, "unknown", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10);

			ValidateValues(handler, "unknown", unknown_var10, (bool)0, (bool)1);

			if (output0.ItemId < 90000001 || output0.ItemId > 90000003)
			{
				StackWatch<PacketHandler> watch_12(handler, "if output0.ItemId < 90000001 || output0.ItemId > 90000003");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x23 'FurnishingStorage' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7, (unsigned char)8);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::FurnishingStorageStartListPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageStartListPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 2");
				Server::FurnishingStorageCountPacket output1;

				Read<int>("count", handler, output1.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageCountPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 3");
				Server::FurnishingStorageAddPacket output2;

				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<unsigned char>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

				Read<int>("slot", handler, output2.Slot);
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageAddPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::FurnishingStorageRemovePacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageRemovePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::FurnishingStoragePurchasePacket output4;

				Read<long long>("itemInstanceId", handler, output4.ItemInstanceId);
				Read<int>("count", handler, output4.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStoragePurchasePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 7");
				Server::FurnishingStorageUpdatePacket output5;

				Read<long long>("itemInstanceId", handler, output5.ItemInstanceId);
				Read<int>("count", handler, output5.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FurnishingStorageUpdatePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 8");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x25 'ItemPutOn' v2497");

			Server::ItemPutOnPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<int>("itemId", handler, output0.ItemId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
			Read<unsigned char>("slot", handler, output0.Slot);
			Read<int>("rarity", handler, output0.Rarity);

			ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			Read<unsigned char>("equipTab", handler, output0.EquipTab);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x2a 'ItemUpdate' v2497");

			Server::ItemUpdatePacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var2 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
			}

			if (itemId_var2 == 0)
			{
				StackWatch<PacketHandler> watch_5(handler, "if itemId_var2 == 0");
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
		void ParsePacket<2497, ServerPacket, 0x4b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x4b 'NpcTalk' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::NpcTalkEndPacket output0;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkEndPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_3(handler, "if mode_var0 == 1");
				Server::NpcTalkRespondPacket output1;

				Read<int>("questId", handler, output1.QuestId);
				Read<unsigned char>("flags", handler, output1.Flags);
				ParseNpcDialog_v12(handler, output1.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkRespondPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 2");
				Server::NpcTalkContinuePacket output2;

				Read<unsigned char>("flags", handler, output2.Flags);
				Read<int>("actorId", handler, output2.ActorId);
				ParseNpcDialog_v12(handler, output2.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkContinuePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				unsigned char actionMode_var5 = 0;
				Read<unsigned char>("actionMode", handler, actionMode_var5);

				ValidateValues(handler, "actionMode", actionMode_var5, (unsigned char)9, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7, (unsigned char)8, (unsigned char)10);

				if (actionMode_var5 == 1)
				{
					StackWatch<PacketHandler> watch_15(handler, "if actionMode_var5 == 1");
					std::wstring unknown_var6;
					Read<std::wstring>("unknown", handler, unknown_var6);
				}

				if (actionMode_var5 == 3)
				{
					StackWatch<PacketHandler> watch_17(handler, "if actionMode_var5 == 3");
					Server::NpcTalkActionMovePlayerPacket output3;

					Read<int>("portalId", handler, output3.PortalId);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionMovePlayerPacket>(output3);
					}


					return;
				}

				if (actionMode_var5 == 4)
				{
					StackWatch<PacketHandler> watch_20(handler, "if actionMode_var5 == 4");
					Server::NpcTalkActionOpenDialogPacket output4;

					std::wstring unknown_var8;
					Read<std::wstring>("unknown", handler, unknown_var8);

					std::wstring unknown_var9;
					Read<std::wstring>("unknown", handler, unknown_var9);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionOpenDialogPacket>(output4);
					}


					return;
				}

				if (actionMode_var5 == 5)
				{
					StackWatch<PacketHandler> watch_24(handler, "if actionMode_var5 == 5");
					Server::NpcTalkActionRewardItemPacket output5;

					int count_var10 = 0;
					Read<int>("count", handler, count_var10);

					ResizeVector(handler, output5.Items, count_var10);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (int i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_27(handler, "output5.Items[", i, "]"); 
						Read<int>("itemId", handler, output5.Items[i].ItemId);
						Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

						ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

						Read<int>("amount", handler, output5.Items[i].Amount);
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
					StackWatch<PacketHandler> watch_32(handler, "if actionMode_var5 == 6");
					Server::NpcTalkActionRewardExpPacket output6;

					Read<long long>("exp", handler, output6.Exp);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardExpPacket>(output6);
					}


					return;
				}

				if (actionMode_var5 == 7)
				{
					StackWatch<PacketHandler> watch_35(handler, "if actionMode_var5 == 7");
					Server::NpcTalkActionRewardMesoPacket output7;

					Read<long long>("meso", handler, output7.Meso);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionRewardMesoPacket>(output7);
					}


					return;
				}

				if (actionMode_var5 == 8)
				{
					StackWatch<PacketHandler> watch_38(handler, "if actionMode_var5 == 8");
					Server::NpcTalkActionAddOptionPacket output8;

					Read<int>("addOption", handler, output8.AddOption);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionAddOptionPacket>(output8);
					}


					return;
				}

				if (actionMode_var5 == 9)
				{
					StackWatch<PacketHandler> watch_41(handler, "if actionMode_var5 == 9");
				}
				if (actionMode_var5 == 10)
				{
					StackWatch<PacketHandler> watch_42(handler, "if actionMode_var5 == 10");
					Server::NpcTalkActionCutscenePacket output9;

					int unknown_var17 = 0;
					Read<int>("unknown", handler, unknown_var17);

					std::wstring unknown_var18;
					Read<std::wstring>("unknown", handler, unknown_var18);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Server::NpcTalkActionCutscenePacket>(output9);
					}


					return;
				}
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_46(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 8");
				Server::NpcTalkAlliancePacket output11;

				Read<unsigned char>("flags", handler, output11.Flags);

				int actorId_var20 = 0;
				Read<int>("actorId", handler, actorId_var20);
				ParseNpcDialog_v12(handler, output11.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output11);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_54(handler, "if mode_var0 == 9");
				Server::NpcTalkAlliancePacket output12;

				Read<unsigned char>("flags", handler, output12.Flags);
				ParseNpcDialog_v12(handler, output12.Dialog);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::NpcTalkAlliancePacket>(output12);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x51>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x51 'Shop' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11, (unsigned char)12, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output1.Items[", i, "]"); 
					Read<int>("entryId", handler, output1.Items[i].EntryId);
					Read<int>("itemId", handler, output1.Items[i].ItemId);
					ParseShopItemData_v12(handler, output1.Items[i]);

					bool unknown_var4 = false;
					Read<bool>("unknown", handler, unknown_var4);

					ValidateValues(handler, "unknown", unknown_var4, (bool)0, (bool)1);
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
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId);
				Read<int>("buyCount", handler, output2.BuyCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 4");
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId);
				Read<int>("buyCount", handler, output3.BuyCount);
				Read<int>("totalPrice", handler, output3.TotalPrice);
				Read<unsigned char>("fontColor", handler, output3.FontColor);
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage);

				ValidateValues(handler, "toGuildStorage", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 6");
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_27(handler, "if mode_var0 == 7");
				Server::ShopAddBuyBackPacket output5;

				short count_var13 = 0;
				Read<short>("count", handler, count_var13);

				ResizeVector(handler, output5.Items, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_30(handler, "output5.Items[", i, "]"); 
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId);
					Read<int>("itemId", handler, output5.Items[i].ItemId);
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

					ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price);
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
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 8");
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 9");
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock);

				ValidateValues(handler, "restock", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					StackWatch<PacketHandler> watch_42(handler, "if output7.Restock");
					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20);

					ValidateValues(handler, "unknown", unknown_var20, (int)0);

					int unknown_var21 = 0;
					Read<int>("unknown", handler, unknown_var21);

					ValidateValues(handler, "unknown", unknown_var21, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_45(handler, "if mode_var0 == 11");
				Server::ShopMeretItemCountPacket output8;

				Read<short>("count", handler, output8.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopMeretItemCountPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_48(handler, "if mode_var0 == 12");
				Server::ShopLoadMeretItemPacket output9;

				unsigned char count_var23 = 0;
				Read<unsigned char>("count", handler, count_var23);

				ResizeVector(handler, output9.Items, count_var23);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var23 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_51(handler, "output9.Items[", i, "]"); 
					ParseMeretShopPremiumItemEntry_v2486(handler, output9.Items[i].MeretItemEntry);

					unsigned char unknown_var24 = 0;
					Read<unsigned char>("unknown", handler, unknown_var24);

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25);

					int unknown_var26 = 0;
					Read<int>("unknown", handler, unknown_var26);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_56(handler, "if mode_var0 == 13");
				int npcId_var27 = 0;
				Read<int>("npcId", handler, npcId_var27);

				int shopId_var28 = 0;
				Read<int>("shopId", handler, shopId_var28);

				int unknown_var29 = 0;
				Read<int>("unknown", handler, unknown_var29);

				short unknown_var30 = 0;
				Read<short>("unknown", handler, unknown_var30);
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_61(handler, "if mode_var0 == 14");
				Server::ShopLoadNewPacket output10;

				short count_var31 = 0;
				Read<short>("count", handler, count_var31);

				ResizeVector(handler, output10.Items, count_var31);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var31 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_64(handler, "output10.Items[", i, "]"); 
					Read<int>("itemId", handler, output10.Items[i].ItemId);

					bool unknown_var33 = false;
					Read<bool>("unknown", handler, unknown_var33);

					ValidateValues(handler, "unknown", unknown_var33, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output10.Items[i].Rarity);

					ValidateValues(handler, "rarity", output10.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var35;
					Read<std::string>("unknown", handler, unknown_var35);

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36);

					unsigned char unknown_var37 = 0;
					Read<unsigned char>("unknown", handler, unknown_var37);
					Read<bool>("hasBuyPeriod", handler, output10.Items[i].HasBuyPeriod);

					ValidateValues(handler, "hasBuyPeriod", output10.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output10.Items[i].HasBuyPeriod)
					{
						StackWatch<PacketHandler> watch_72(handler, "if output10.Items[i].HasBuyPeriod");
						ParseBuyPeriodData_v12(handler, output10.Items[i].BuyPeriod);
					}
					ParseItemData_v2497(handler, output10.Items[i].ItemData, (unsigned int)output10.Items[i].ItemId);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadNewPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_75(handler, "if mode_var0 == 15");
				Server::ShopErrorPacket output11;

				Read<int>("message", handler, output11.Message);

				unsigned char unknown_var40 = 0;
				Read<unsigned char>("unknown", handler, unknown_var40);
				Read<int>("stringId", handler, output11.StringId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output11);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x54>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x54 'Mail' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)11, (unsigned char)3, (unsigned char)13, (unsigned char)14, (unsigned char)15, (unsigned char)16, (unsigned char)17, (unsigned char)20, (unsigned char)22);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::MailLoadPacket output0;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1);

				ResizeVector(handler, output0.Mail, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Mail[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
				Server::MailSendCustomConfirmPacket output1;

				Read<long long>("mailInstanceId", handler, output1.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailSendCustomConfirmPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::MailReadPacket output2;

				Read<long long>("mailInstanceId", handler, output2.MailInstanceId);
				Read<long long>("readTime", handler, output2.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReadPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
				Server::MailErrorPacket output3;

				long long unknown_var5 = 0;
				Read<long long>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailErrorPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 10");
				Server::MailCollectingPacket output4;

				Read<long long>("mailInstanceId", handler, output4.MailInstanceId);

				bool unknownCondition_var7 = false;
				Read<bool>("unknownCondition", handler, unknownCondition_var7);

				ValidateValues(handler, "unknownCondition", unknownCondition_var7, (bool)0, (bool)1);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				ValidateValues(handler, "unknown", unknown_var8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("collectTime", handler, output4.CollectTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailCollectingPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 11");
				Server::MailUpdateReadTimePacket output5;

				Read<long long>("mailInstanceId", handler, output5.MailInstanceId);
				Read<long long>("readTime", handler, output5.ReadTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailUpdateReadTimePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_26(handler, "if mode_var0 == 12");
				long long mailInstanceId_var12 = 0;
				Read<long long>("mailInstanceId", handler, mailInstanceId_var12);

				long long timestamp_var13 = 0;
				Read<long long>("timestamp", handler, timestamp_var13);
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 13");
				Server::MailDeletePacket output6;

				Read<long long>("mailInstanceId", handler, output6.MailInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailDeletePacket>(output6);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 14");
				Server::MailReceivePacket output7;

				Read<int>("unreadMailCount", handler, output7.UnreadMailCount);
				Read<bool>("alert", handler, output7.Alert);

				ValidateValues(handler, "alert", output7.Alert, (bool)0, (bool)1);

				Read<int>("count", handler, output7.Count);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailReceivePacket>(output7);
				}


				return;
			}

			if (mode_var0 == 15)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 15");
				Server::MailExpireNotificationPacket output8;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailExpireNotificationPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 16)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 16");
				Server::MailStartListPacket output9;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailStartListPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 17");
				Server::MailEndListPacket output10;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailEndListPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 20)
			{
				StackWatch<PacketHandler> watch_43(handler, "if mode_var0 == 20");
				Server::MailError2Packet output11;

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18);
				Read<unsigned char>("message", handler, output11.Message);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::MailError2Packet>(output11);
				}


				return;
			}

			if (mode_var0 == 22)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 22");
				Server::MailReceiveGiftNotificationPacket output12;

				std::wstring unknown_var20;
				Read<std::wstring>("unknown", handler, unknown_var20);

				unsigned char unknown_var21 = 0;
				Read<unsigned char>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);

				unsigned char unknown_var23 = 0;
				Read<unsigned char>("unknown", handler, unknown_var23);

				int unknown_var24 = 0;
				Read<int>("unknown", handler, unknown_var24);

				std::string unknown_var25;
				Read<std::string>("unknown", handler, unknown_var25);

				std::wstring unknown_var26;
				Read<std::wstring>("unknown", handler, unknown_var26);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x78 'CharacterInfo' v2497");

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId);
			Read<bool>("found", handler, output0.Found);

			ValidateValues(handler, "found", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				StackWatch<PacketHandler> watch_3(handler, "if output0.Found");
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2);

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3);
				Read<long long>("currentTime", handler, output0.CurrentTime);

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_8(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						StackWatch<PacketHandler> watch_10(handler, "output0.Details.Stats");
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v2497(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_16(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2497(handler, output0.Equipment);
					ParseCharacterEquipmentSkins_v2497(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_20(handler, "buffer[", bufferSize_var5, "]");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x7b 'FittingDoll' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::FittingDollLoadPacket output0;

				Read<int>("actorId", handler, output0.ActorId);
				Read<long long>("dollInstanceId", handler, output0.DollInstanceId);
				Read<int>("dollItemId", handler, output0.DollItemId);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("rotation", handler, output0.Rotation);
				Read<bool>("hasItems", handler, output0.HasItems);

				ValidateValues(handler, "hasItems", output0.HasItems, (bool)0, (bool)1);

				int count_var7 = 0;
				Read<int>("count", handler, count_var7);

				ResizeVector(handler, output0.Items, count_var7);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var7 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_10(handler, "output0.Items[", i, "]"); 
					Read<int>("itemId", handler, output0.Items[i].ItemId);
					Read<long long>("itemInstanceId", handler, output0.Items[i].ItemInstanceId);
					Read<unsigned char>("slot", handler, output0.Items[i].Slot);
					Read<int>("rarity", handler, output0.Items[i].Rarity);

					ValidateValues(handler, "rarity", output0.Items[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 1");
				Server::FittingDollRemovePacket output1;

				Read<int>("actorId", handler, output1.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemovePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 4");
				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::FittingDollPutOnItemPacket output2;

				Read<long long>("dollInstanceId", handler, output2.DollInstanceId);
				Read<int>("itemId", handler, output2.ItemId);
				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<unsigned char>("slot", handler, output2.Slot);
				Read<int>("rarity", handler, output2.Rarity);

				ValidateValues(handler, "rarity", output2.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)output2.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollPutOnItemPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 7");
				Server::FittingDollRemoveItemPacket output3;

				Read<long long>("itemInstanceId", handler, output3.ItemInstanceId);
				Read<unsigned char>("slot", handler, output3.Slot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollRemoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 8");
				long long unknown_var21 = 0;
				Read<long long>("unknown", handler, unknown_var21);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22);
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 11");
				Server::FittingDollErrorPacket output4;

				Read<int>("errorCode", handler, output4.ErrorCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::FittingDollErrorPacket>(output4);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x82>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x82 'Trade' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)10, (unsigned char)11, (unsigned char)12, (unsigned char)13);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::TradeReceiveRequestPacket output0;

				Read<std::wstring>("playerName", handler, output0.PlayerName);
				Read<long long>("characterId", handler, output0.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeReceiveRequestPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 1");
				Server::TradeErrorPacket output1;

				Read<unsigned char>("message", handler, output1.Message);
				Read<std::wstring>("name", handler, output1.Name);
				Read<int>("itemId", handler, output1.ItemId);
				Read<int>("level", handler, output1.Level);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeErrorPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::TradeConfirmRequestPacket output2;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeConfirmRequestPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 4");
				Server::TradeDeclinedPacket output3;

				Read<std::wstring>("playerName", handler, output3.PlayerName);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeDeclinedPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::TradeBeginPacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeBeginPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_19(handler, "if mode_var0 == 6");
				Server::TradeEndPacket output5;

				Read<bool>("success", handler, output5.Success);

				ValidateValues(handler, "success", output5.Success, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeEndPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_22(handler, "if mode_var0 == 8");
				Server::TradeAddItemPacket output6;

				Read<unsigned char>("index", handler, output6.Index);

				ValidateValues(handler, "index", output6.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("itemId", handler, output6.ItemId);
				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);
				Read<int>("rarity", handler, output6.Rarity);

				ValidateValues(handler, "rarity", output6.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("tradeSlot", handler, output6.TradeSlot);
				Read<int>("amount", handler, output6.Amount);
				Read<int>("tradeSlot2", handler, output6.TradeSlot2);
				ParseItemData_v2497(handler, output6.ItemData, (unsigned int)output6.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeAddItemPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_32(handler, "if mode_var0 == 9");
				Server::TradeRemoveItemPacket output7;

				Read<unsigned char>("index", handler, output7.Index);

				ValidateValues(handler, "index", output7.Index, (unsigned char)0, (unsigned char)1);

				Read<int>("tradeSlot", handler, output7.TradeSlot);
				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeRemoveItemPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 10");
				Server::TradeSetMoneyPacket output8;

				Read<unsigned char>("index", handler, output8.Index);
				Read<long long>("mesos", handler, output8.Mesos);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeSetMoneyPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 11");
				Server::TradeFinalizePacket output9;

				Read<unsigned char>("index", handler, output9.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizePacket>(output9);
				}


				return;
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_44(handler, "if mode_var0 == 12");
				Server::TradeChangeOfferPacket output10;

				Read<unsigned char>("index", handler, output10.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeChangeOfferPacket>(output10);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 13");
				Server::TradeFinalizeConfirmPacket output11;

				Read<unsigned char>("index", handler, output11.Index);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::TradeFinalizeConfirmPacket>(output11);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_50(handler, "if mode_var0 == 14");
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x98>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x98 'BlackMarket' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::BlackMarketErrorPacket output0;

				unsigned char unknown_var1 = 0;
				Read<unsigned char>("unknown", handler, unknown_var1);
				Read<int>("errorCode", handler, output0.ErrorCode);
				Read<long long>("listingInstanceId", handler, output0.ListingInstanceId);

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4);

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketErrorPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::BlackMarketMyListingsPacket output1;

				int count_var6 = 0;
				Read<int>("count", handler, count_var6);

				ResizeVector(handler, output1.Entries, count_var6);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var6 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output1.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
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
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 3");
				Server::BlackMarketCancelListingPacket output3;

				Read<long long>("listingInstanceId", handler, output3.ListingInstanceId);

				unsigned char unknown_var8 = 0;
				Read<unsigned char>("unknown", handler, unknown_var8);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketCancelListingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::BlackMarketSearchResultsPacket output4;

				int count_var9 = 0;
				Read<int>("count", handler, count_var9);

				ResizeVector(handler, output4.Entries, count_var9);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (int i = 0; i < count_var9 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_23(handler, "output4.Entries[", i, "]"); 
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
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 5");
				Server::BlackMarketPurchasePacket output5;

				Read<long long>("listingInstanceId", handler, output5.ListingInstanceId);
				Read<int>("amount", handler, output5.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPurchasePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_29(handler, "if mode_var0 == 6");
				unsigned char unknown_var12 = 0;
				Read<unsigned char>("unknown", handler, unknown_var12);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);

				long long unknown_var14 = 0;
				Read<long long>("unknown", handler, unknown_var14);
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_33(handler, "if mode_var0 == 7");
				Server::BlackMarketSoldPacket output6;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketSoldPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 8");
				Server::BlackMarketPrepareListingPacket output7;

				Read<int>("itemId", handler, output7.ItemId);
				Read<int>("rarity", handler, output7.Rarity);

				ValidateValues(handler, "rarity", output7.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

				Read<int>("shopPrice", handler, output7.ShopPrice);

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::BlackMarketPrepareListingPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_41(handler, "if mode_var0 == 9");
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xbf>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xbf 'EnchantScroll' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_7(handler, "if mode_var0 == 3");
				short result_var1 = 0;
				Read<short>("result", handler, result_var1);

				ValidateValues(handler, "result", result_var1, (short)0, (short)1, (short)2, (short)3, (short)4, (short)5, (short)6, (short)7, (short)8);

				if (result_var1 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if result_var1 == 0");
					Server::EnchantScrollSuccessPacket output2;

					Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

					int itemId_var3 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var3 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output2.ItemInstanceId);
					}

					if (itemId_var3 == 0)
					{
						StackWatch<PacketHandler> watch_14(handler, "if itemId_var3 == 0");
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
					StackWatch<PacketHandler> watch_17(handler, "else");
					Server::EnchantScrollResultPacket output3;

					short resultData_var4 = 0;

					output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)resultData_var4;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						output3.Result = (Server::EnchantScrollResultPacket::ResultTypeEnum)handler.Copy(result_var1);

						CalledFunction(handler, "Copy", "output3.Result", output3.Result, result_var1);
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
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 4");
				Server::EnchantScrollRewardPacket output4;

				unsigned int count_var5 = 0;
				Read<unsigned int>("count", handler, count_var5);

				ResizeVector(handler, output4.Data, count_var5);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned int i = 0; i < count_var5 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_24(handler, "output4.Data[", i, "]"); 
					Read<int>("itemId", handler, output4.Data[i].ItemId);

					short unknown_var7 = 0;
					Read<short>("unknown", handler, unknown_var7);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc7 'PlayInstrument' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6, (unsigned char)10, (unsigned char)14, (unsigned char)17);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PlayInstrumentStartImprovisePacket output0;

				Read<int>("instrumentId", handler, output0.InstrumentId);
				Read<int>("actorId", handler, output0.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output0.InstrumentPosition);
				Read<int>("gmId", handler, output0.GMId);
				Read<int>("percussionId", handler, output0.PercussionId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartImprovisePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::PlayInstrumentPlayNotePacket output1;

				Read<int>("instrumentId", handler, output1.InstrumentId);
				Read<int>("actorId", handler, output1.ActorId);
				Read<int>("midiNote", handler, output1.MidiNote);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentPlayNotePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
				Server::PlayInstrumentStopImprovisePacket output2;

				Read<int>("instrumentId", handler, output2.InstrumentId);
				Read<int>("actorId", handler, output2.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopImprovisePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 3");
				Server::PlayInstrumentStartScorePacket output3;

				Read<bool>("isCustom", handler, output3.IsCustom);

				ValidateValues(handler, "isCustom", output3.IsCustom, (bool)0, (bool)1);

				Read<int>("instrumentId", handler, output3.InstrumentId);
				Read<int>("actorId", handler, output3.ActorId);
				Read<Vector3S>("instrumentPosition", handler, output3.InstrumentPosition);
				Read<int>("instrumentTick", handler, output3.InstrumentTick);
				Read<int>("gmId", handler, output3.GMId);
				Read<int>("percussionId", handler, output3.PercussionId);

				bool unknown_var18 = false;
				Read<bool>("unknown", handler, unknown_var18);

				ValidateValues(handler, "unknown", unknown_var18, (bool)0, (bool)1);

				if (output3.IsCustom)
				{
					StackWatch<PacketHandler> watch_27(handler, "if output3.IsCustom");
					Read<std::string>("musicCode", handler, output3.MusicCode);
				}

				else
				{
					StackWatch<PacketHandler> watch_29(handler, "else");
					Read<std::wstring>("fileName", handler, output3.FileName);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStartScorePacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 4");
				Server::PlayInstrumentStopScorePacket output4;

				Read<int>("instrumentId", handler, output4.InstrumentId);
				Read<int>("actorId", handler, output4.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentStopScorePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_35(handler, "if mode_var0 == 6");
				Server::PlayInstrumentLeaveEnsemblePacket output5;

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(output5);
				}


				return;
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_37(handler, "if mode_var0 == 8");
				Server::PlayInstrumentCreateScoreResponsePacket output6;

				Read<long long>("itemInstanceId", handler, output6.ItemInstanceId);

				int itemId_var24 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var24 = handler.GetItemIdFromInstance(output6.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var24", itemId_var24, output6.ItemInstanceId);
				}

				if (itemId_var24 == 0)
				{
					StackWatch<PacketHandler> watch_42(handler, "if itemId_var24 == 0");
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
				StackWatch<PacketHandler> watch_45(handler, "if mode_var0 == 9");
				Server::PlayInstrumentUpdateScoreUsesPacket output7;

				Read<long long>("itemInstanceId", handler, output7.ItemInstanceId);
				Read<int>("remainingUses", handler, output7.RemainingUses);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 10)
			{
				StackWatch<PacketHandler> watch_49(handler, "if mode_var0 == 10");
				Server::PlayInstrumentViewMusicPacket output8;

				Read<long long>("itemInstanceId", handler, output8.ItemInstanceId);
				Read<std::string>("musicCode", handler, output8.MusicCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentViewMusicPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_53(handler, "if mode_var0 == 14");
				Server::PlayInstrumentEffectPacket output9;

				Read<int>("actorId", handler, output9.ActorId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PlayInstrumentEffectPacket>(output9);
				}


				return;
			}

			if (mode_var0 == 17)
			{
				StackWatch<PacketHandler> watch_56(handler, "if mode_var0 == 17");
				Server::PlayInstrumentWritePlayDialogPacket output10;

				unsigned char unknown_var30 = 0;
				Read<unsigned char>("unknown", handler, unknown_var30);

				ValidateValues(handler, "unknown", unknown_var30, (unsigned char)16, (unsigned char)8, (unsigned char)10);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc8 'ChangeAttributes' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ChangeAttributesPreviewChangePacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				int itemId_var2 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var2 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var2", itemId_var2, output0.ItemInstanceId);
				}

				if (itemId_var2 == 0)
				{
					StackWatch<PacketHandler> watch_6(handler, "if itemId_var2 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output0.ItemData, (unsigned int)itemId_var2);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesPreviewChangePacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::ChangeAttributesScrollApplyPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var4 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var4 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var4", itemId_var4, output1.ItemInstanceId);
				}

				if (itemId_var4 == 0)
				{
					StackWatch<PacketHandler> watch_14(handler, "if itemId_var4 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output1.ItemData, (unsigned int)itemId_var4);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 4");
				Server::ChangeAttributesErrorPacket output2;

				bool unknown_var5 = false;
				Read<bool>("unknown", handler, unknown_var5);

				ValidateValues(handler, "unknown", unknown_var5, (bool)0, (bool)1);

				int message_var6 = 0;
				Read<int>("message", handler, message_var6);

				ValidateValues(handler, "message", message_var6, (int)9, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)10);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesErrorPacket>(output2);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0xc9>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc9 'ChangeAttributesScroll' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::ChangeAttributesScrollUseScrollPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 2");
				Server::ChangeAttributesScrollPreviewChangePacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				int itemId_var3 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var3 = handler.GetItemIdFromInstance(output1.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var3", itemId_var3, output1.ItemInstanceId);
				}

				if (itemId_var3 == 0)
				{
					StackWatch<PacketHandler> watch_9(handler, "if itemId_var3 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output1.ItemData, (unsigned int)itemId_var3);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollPreviewChangePacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_12(handler, "if mode_var0 == 3");
				Server::ChangeAttributesScrollApplyPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);

				int itemId_var5 = 0;

				if (!handler.PacketStream().HasRecentlyFailed)
				{
					itemId_var5 = handler.GetItemIdFromInstance(output2.ItemInstanceId);

					CalledFunction(handler, "GetItemIdFromInstance", "itemId_var5", itemId_var5, output2.ItemInstanceId);
				}

				if (itemId_var5 == 0)
				{
					StackWatch<PacketHandler> watch_17(handler, "if itemId_var5 == 0");
					handler.DiscardPacket();

					return;

				}
				ParseItemData_v2497(handler, output2.ItemData, (unsigned int)itemId_var5);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ChangeAttributesScrollApplyPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 4");
				Server::ChangeAttributesScrollErrorPacket output3;

				bool unknown_var6 = false;
				Read<bool>("unknown", handler, unknown_var6);

				ValidateValues(handler, "unknown", unknown_var6, (bool)0, (bool)1);

				int message_var7 = 0;
				Read<int>("message", handler, message_var7);

				ValidateValues(handler, "message", message_var7, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)10, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)17);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xce 'PetInventory' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)6);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::PetInventoryStoreItemPacket output0;

				Read<int>("itemId", handler, output0.ItemId);
				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);
				Read<int>("rarity", handler, output0.Rarity);

				ValidateValues(handler, "rarity", output0.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.ItemData, (unsigned int)output0.ItemId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryStoreItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 1");
				Server::PetInventoryRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_11(handler, "if mode_var0 == 2");
				Server::PetInventoryUpdateAmountPacket output2;

				Read<long long>("itemInstanceId", handler, output2.ItemInstanceId);
				Read<int>("amount", handler, output2.Amount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryUpdateAmountPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_15(handler, "if mode_var0 == 3");
				Server::PetInventoryMoveItemPacket output3;

				Read<long long>("srcItemInstanceId", handler, output3.SourceItemInstanceId);
				Read<short>("srcSlot", handler, output3.SourceSlot);
				Read<long long>("dstItemInstanceId", handler, output3.DestinationItemInstanceId);
				Read<short>("dstSlot", handler, output3.DestinationSlot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::PetInventoryMoveItemPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 4");
				Server::PetInventoryListItemsPacket output4;

				short count_var12 = 0;
				Read<short>("count", handler, count_var12);

				ResizeVector(handler, output4.Slots, count_var12);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var12 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_24(handler, "output4.Slots[", i, "]"); 
					Read<int>("itemId", handler, output4.Slots[i].ItemId);
					Read<long long>("itemInstanceId", handler, output4.Slots[i].ItemInstanceId);
					Read<short>("slot", handler, output4.Slots[i].Slot);
					Read<int>("rarity", handler, output4.Slots[i].Rarity);

					ValidateValues(handler, "rarity", output4.Slots[i].Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
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
				StackWatch<PacketHandler> watch_30(handler, "if mode_var0 == 6");
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xdb 'ItemLock' v2497");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 1");
				Server::ItemLockAddItemPacket output0;

				Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);
				Read<short>("slot", handler, output0.Slot);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockAddItemPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_5(handler, "if mode_var0 == 2");
				Server::ItemLockRemoveItemPacket output1;

				Read<long long>("itemInstanceId", handler, output1.ItemInstanceId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockRemoveItemPacket>(output1);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_8(handler, "if mode_var0 == 3");
				Server::ItemLockUpdateItemPacket output2;

				unsigned char count_var4 = 0;
				Read<unsigned char>("count", handler, count_var4);

				ResizeVector(handler, output2.Items, count_var4);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_11(handler, "output2.Items[", i, "]"); 
					Read<long long>("itemInstanceId", handler, output2.Items[i].ItemInstanceId);

					int itemId_var6 = 0;

					if (!handler.PacketStream().HasRecentlyFailed)
					{
						itemId_var6 = handler.GetItemIdFromInstance(output2.Items[i].ItemInstanceId);

						CalledFunction(handler, "GetItemIdFromInstance", "itemId_var6", itemId_var6, output2.Items[i].ItemInstanceId);
					}

					if (itemId_var6 == 0)
					{
						StackWatch<PacketHandler> watch_15(handler, "if itemId_var6 == 0");
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
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 4");
				Server::ItemLockErrorPacket output3;

				Read<int>("errorCode", handler, output3.ErrorCode);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ItemLockErrorPacket>(output3);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x103>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x103 'BindItem' v2497");

			Server::BindItemPacket output0;

			Read<long long>("itemInstanceId", handler, output0.ItemInstanceId);

			int itemId_var1 = 0;

			if (!handler.PacketStream().HasRecentlyFailed)
			{
				itemId_var1 = handler.GetItemIdFromInstance(output0.ItemInstanceId);

				CalledFunction(handler, "GetItemIdFromInstance", "itemId_var1", itemId_var1, output0.ItemInstanceId);
			}

			if (itemId_var1 == 0)
			{
				StackWatch<PacketHandler> watch_4(handler, "if itemId_var1 == 0");
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
		void ParsePacket<2465, ServerPacket, 0x3e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3e 'SkillSync' v2465");

			Server::SkillSyncPacket output0;

			long long skillSn_var0 = 0;
			Read<long long>("skillSn", handler, skillSn_var0);

			int actorId_var1 = 0;
			Read<int>("actorId", handler, actorId_var1);

			int skillId_var2 = 0;
			Read<int>("skillId", handler, skillId_var2);

			short skillLevel_var3 = 0;
			Read<short>("skillLevel", handler, skillLevel_var3);

			unsigned char unknown_var4 = 0;
			Read<unsigned char>("unknown", handler, unknown_var4);

			ValidateValues(handler, "unknown", unknown_var4, (unsigned char)0);

			Vector3S position_var5;
			Read<Vector3S>("position", handler, position_var5);

			Vector3S direction_var6;
			Read<Vector3S>("direction", handler, direction_var6);

			Vector3S rotation_var7;
			Read<Vector3S>("rotation", handler, rotation_var7);

			Vector3S unknown_var8;
			Read<Vector3S>("unknown", handler, unknown_var8);

			unsigned char unknown_var9 = 0;
			Read<unsigned char>("unknown", handler, unknown_var9);

			unsigned char attackPoint_var10 = 0;
			Read<unsigned char>("attackPoint", handler, attackPoint_var10);

			int unknown_var11 = 0;
			Read<int>("unknown", handler, unknown_var11);

			if (handler.Succeeded())
			{
				handler.PacketParsed<Server::SkillSyncPacket>(output0);
			}


			return;
		}

		template <>
		void ParsePacket<2493, ServerPacket, 0x17>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v2493");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2493(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
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

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_32(handler, "if statCount_var4 != 35");
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_33(handler, "output0.Stats.Basic[", i, "]"); 
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type);

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_35(handler, "if output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4");
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current);
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_39(handler, "if output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4");
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current);
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35);

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_51(handler, "if output0.OnMount");
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_59(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_64(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2486(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_68(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2486(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46);

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_71(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52);

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53);

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55);

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_89(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2486(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67);

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68);

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x49 'Job' v2493");

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc 'CharacterList' v2496");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Characters[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);
				Read<long long>("characterId", handler, output2.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
			}
			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId);
				Read<int>("messageId", handler, output3.MessageId);
				Read<long long>("deleteTime", handler, output3.DeleteTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);
				Read<int>("messageId", handler, output4.MessageId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 7");
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListChangeNamePacket>(output5);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2496, ServerPacket, 0x51>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x51 'Shop' v2496");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)14, (unsigned char)15);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
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
				StackWatch<PacketHandler> watch_4(handler, "if mode_var0 == 1");
				Server::ShopLoadItemsPacket output1;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output1.Items, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_7(handler, "output1.Items[", i, "]"); 
					Read<int>("entryId", handler, output1.Items[i].EntryId);
					Read<int>("itemId", handler, output1.Items[i].ItemId);
					ParseShopItemData_v12(handler, output1.Items[i]);

					bool unknown_var4 = false;
					Read<bool>("unknown", handler, unknown_var4);

					ValidateValues(handler, "unknown", unknown_var4, (bool)0, (bool)1);
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
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 2");
				Server::ShopUpdatePacket output2;

				Read<int>("entryId", handler, output2.EntryId);
				Read<int>("buyCount", handler, output2.BuyCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopUpdatePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_17(handler, "if mode_var0 == 4");
				Server::ShopBuyPacket output3;

				Read<int>("itemId", handler, output3.ItemId);
				Read<int>("buyCount", handler, output3.BuyCount);
				Read<int>("totalPrice", handler, output3.TotalPrice);
				Read<unsigned char>("fontColor", handler, output3.FontColor);
				Read<bool>("toGuildStorage", handler, output3.ToGuildStorage);

				ValidateValues(handler, "toGuildStorage", output3.ToGuildStorage, (bool)0, (bool)1);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_24(handler, "if mode_var0 == 6");
				Server::ShopBuyBackItemCountPacket output4;

				Read<short>("itemCount", handler, output4.ItemCount);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopBuyBackItemCountPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_27(handler, "if mode_var0 == 7");
				Server::ShopAddBuyBackPacket output5;

				short count_var13 = 0;
				Read<short>("count", handler, count_var13);

				ResizeVector(handler, output5.Items, count_var13);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var13 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_30(handler, "output5.Items[", i, "]"); 
					Read<int>("repurchaseId", handler, output5.Items[i].RepurchaseId);
					Read<int>("itemId", handler, output5.Items[i].ItemId);
					Read<unsigned char>("rarity", handler, output5.Items[i].Rarity);

					ValidateValues(handler, "rarity", output5.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					Read<long long>("price", handler, output5.Items[i].Price);
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
				StackWatch<PacketHandler> watch_36(handler, "if mode_var0 == 8");
				Server::ShopRemoveBuyBackPacket output6;

				Read<int>("repurchaseId", handler, output6.RepurchaseId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopRemoveBuyBackPacket>(output6);
				}


				return;
			}

			if (mode_var0 == 9)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 9");
				Server::ShopInstantRestockPacket output7;

				Read<bool>("restock", handler, output7.Restock);

				ValidateValues(handler, "restock", output7.Restock, (bool)0, (bool)1);

				if (output7.Restock)
				{
					StackWatch<PacketHandler> watch_42(handler, "if output7.Restock");
					int unknown_var20 = 0;
					Read<int>("unknown", handler, unknown_var20);

					ValidateValues(handler, "unknown", unknown_var20, (int)0);

					int unknown_var21 = 0;
					Read<int>("unknown", handler, unknown_var21);

					ValidateValues(handler, "unknown", unknown_var21, (int)0);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopInstantRestockPacket>(output7);
				}


				return;
			}

			if (mode_var0 == 11)
			{
				StackWatch<PacketHandler> watch_45(handler, "if mode_var0 == 11");
				short unknown_var22 = 0;
				Read<short>("unknown", handler, unknown_var22);
			}

			if (mode_var0 == 12)
			{
				StackWatch<PacketHandler> watch_47(handler, "if mode_var0 == 12");
				Server::ShopLoadMeretItemPacket output8;

				short count_var23 = 0;
				Read<short>("count", handler, count_var23);

				ResizeVector(handler, output8.Items, count_var23);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var23 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_50(handler, "output8.Items[", i, "]"); 
					ParseMeretShopPremiumItemEntry_v12(handler, output8.Items[i].MeretItemEntry);

					unsigned char unknown_var24 = 0;
					Read<unsigned char>("unknown", handler, unknown_var24);

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25);

					int unknown_var26 = 0;
					Read<int>("unknown", handler, unknown_var26);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopLoadMeretItemPacket>(output8);
				}


				return;
			}

			if (mode_var0 == 13)
			{
				StackWatch<PacketHandler> watch_55(handler, "if mode_var0 == 13");
				int npcId_var27 = 0;
				Read<int>("npcId", handler, npcId_var27);

				int shopId_var28 = 0;
				Read<int>("shopId", handler, shopId_var28);

				int unknown_var29 = 0;
				Read<int>("unknown", handler, unknown_var29);

				short unknown_var30 = 0;
				Read<short>("unknown", handler, unknown_var30);
			}

			if (mode_var0 == 14)
			{
				StackWatch<PacketHandler> watch_60(handler, "if mode_var0 == 14");
				Server::ShopLoadNewPacket output9;

				short count_var31 = 0;
				Read<short>("count", handler, count_var31);

				ResizeVector(handler, output9.Items, count_var31);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (short i = 0; i < count_var31 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_63(handler, "output9.Items[", i, "]"); 
					Read<int>("itemId", handler, output9.Items[i].ItemId);

					bool unknown_var33 = false;
					Read<bool>("unknown", handler, unknown_var33);

					ValidateValues(handler, "unknown", unknown_var33, (bool)0, (bool)1);

					Read<unsigned char>("rarity", handler, output9.Items[i].Rarity);

					ValidateValues(handler, "rarity", output9.Items[i].Rarity, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6);

					std::string unknown_var35;
					Read<std::string>("unknown", handler, unknown_var35);

					unsigned char unknown_var36 = 0;
					Read<unsigned char>("unknown", handler, unknown_var36);

					unsigned char unknown_var37 = 0;
					Read<unsigned char>("unknown", handler, unknown_var37);
					Read<bool>("hasBuyPeriod", handler, output9.Items[i].HasBuyPeriod);

					ValidateValues(handler, "hasBuyPeriod", output9.Items[i].HasBuyPeriod, (bool)0, (bool)1);

					if (output9.Items[i].HasBuyPeriod)
					{
						StackWatch<PacketHandler> watch_71(handler, "if output9.Items[i].HasBuyPeriod");
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
				StackWatch<PacketHandler> watch_74(handler, "if mode_var0 == 15");
				Server::ShopErrorPacket output10;

				Read<int>("message", handler, output10.Message);

				unsigned char unknown_var40 = 0;
				Read<unsigned char>("unknown", handler, unknown_var40);
				Read<int>("stringId", handler, output10.StringId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::ShopErrorPacket>(output10);
				}


				return;
			}
		}

		template <>
		void ParsePacket<2496, ServerPacket, 0x78>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x78 'CharacterInfo' v2496");

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId);
			Read<bool>("found", handler, output0.Found);

			ValidateValues(handler, "found", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				StackWatch<PacketHandler> watch_3(handler, "if output0.Found");
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2);

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3);
				Read<long long>("currentTime", handler, output0.CurrentTime);

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_8(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						StackWatch<PacketHandler> watch_10(handler, "output0.Details.Stats");
						ParseCharacterDetailsBasicStats_v12(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v12(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_16(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2486(handler, output0.Equipment);
					ParseCharacterEquipmentSkinsMandatory_v2486(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_20(handler, "buffer[", bufferSize_var5, "]");
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

				StackWatch<PacketHandler> watch_block(handler, "[Client] 0x20 'Skill' v2503");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<int>("serverTick", handler, output0.ServerTick);
				Read<int>("skillId", handler, output0.SkillId);
				Read<short>("skillLevel", handler, output0.SkillLevel);
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint);
				Read<Vector3S>("position", handler, output0.Position);
				Read<Vector3S>("direction", handler, output0.Direction);
				Read<Vector3S>("rotation", handler, output0.Rotation);

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9);

				ValidateValues(handler, "unknown", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick);

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11);

				ValidateValues(handler, "unknown", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12);

				ValidateValues(handler, "unknown", unknown_var12, (long long)0);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13);
				Read<bool>("flag", handler, output0.Flag);

				ValidateValues(handler, "flag", output0.Flag, (bool)0, (bool)1);

				if (output0.Flag)
				{
					StackWatch<PacketHandler> watch_17(handler, "if output0.Flag");
					int unknown_var15 = 0;
					Read<int>("unknown", handler, unknown_var15);

					ValidateValues(handler, "unknown", unknown_var15, (int)0);

					std::string unknown_var16;
					Read<std::string>("unknown", handler, unknown_var16);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_20(handler, "if mode_var0 == 1");
				unsigned char damageMode_var17 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var17);

				ValidateValues(handler, "damageMode", damageMode_var17, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var17 == 0)
				{
					StackWatch<PacketHandler> watch_22(handler, "if damageMode_var17 == 0");
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", handler, output1.SkillSn);
					Read<unsigned char>("attackPoint", handler, output1.AttackPoint);
					Read<Vector3S>("position", handler, output1.Position);
					Read<Vector3S>("rotation", handler, output1.Rotation);

					unsigned char count_var22 = 0;
					Read<unsigned char>("count", handler, count_var22);

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23);

					ValidateValues(handler, "unknown", unknown_var23, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var22);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char projectile_i = 0; projectile_i < count_var22 && !handler.PacketStream().HasRecentlyFailed; ++projectile_i)
					{
						StackWatch<PacketHandler> watch_30(handler, "output1.Projectiles[", projectile_i, "]"); 
						auto& projectile_array0 = output1.Projectiles[projectile_i];

						Read<long long>("skillAttack", handler, projectile_array0.SkillAttack);
						Read<int>("targetId", handler, projectile_array0.TargetId);
						Read<unsigned char>("index", handler, projectile_array0.Index);

						bool moreTargets_var27 = false;
						Read<bool>("moreTargets", handler, moreTargets_var27);

						ValidateValues(handler, "moreTargets", moreTargets_var27, (bool)0, (bool)1);

						size_t nextTarget_j = 0;

						while (moreTargets_var27 && !handler.PacketStream().HasRecentlyFailed)
						{
							StackWatch<PacketHandler> watch_35(handler, "projectile_array0.ChainTargets[", nextTarget_j, "]"); 
							projectile_array0.ChainTargets.push_back({});

							if (handler.PacketStream().HasRecentlyFailed)
							{
								return;
							}

							auto& nextTarget_array1 = projectile_array0.ChainTargets[nextTarget_j];

							Read<long long>("skillAttack", handler, nextTarget_array1.SkillAttack);
							Read<int>("targetId", handler, nextTarget_array1.TargetId);
							Read<unsigned char>("index", handler, nextTarget_array1.Index);

							unsigned char unknown_var31 = 0;
							Read<unsigned char>("unknown", handler, unknown_var31);

							Read<bool>("moreTargets", handler, moreTargets_var27);

							ValidateValues(handler, "moreTargets", moreTargets_var27, (bool)0, (bool)1);

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
					StackWatch<PacketHandler> watch_41(handler, "if damageMode_var17 == 1");
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", handler, output2.SkillSn);
					Read<long long>("skillAttack", handler, output2.SkillAttack);
					Read<Vector3S>("position", handler, output2.Position);
					Read<Vector3S>("hitPoint", handler, output2.HitPoint);
					Read<Vector3S>("rotation", handler, output2.Rotation);
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint);

					unsigned char count_var38 = 0;
					Read<unsigned char>("count", handler, count_var38);

					int unknown_var39 = 0;
					Read<int>("unknown", handler, unknown_var39);

					ValidateValues(handler, "unknown", unknown_var39, (int)0);

					ResizeVector(handler, output2.Hits, count_var38);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char hitActor_i = 0; hitActor_i < count_var38 && !handler.PacketStream().HasRecentlyFailed; ++hitActor_i)
					{
						StackWatch<PacketHandler> watch_51(handler, "output2.Hits[", hitActor_i, "]"); 
						auto& hitActor_array2 = output2.Hits[hitActor_i];

						Read<int>("entityId", handler, hitActor_array2.EntityId);

						unsigned char unknown_var41 = 0;
						Read<unsigned char>("unknown", handler, unknown_var41);

						ValidateValues(handler, "unknown", unknown_var41, (unsigned char)0);
					}

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);
					}


					return;
				}

				if (damageMode_var17 == 2)
				{
					StackWatch<PacketHandler> watch_54(handler, "if damageMode_var17 == 2");
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", handler, output3.SkillSn);
					Read<unsigned char>("attackPoint", handler, output3.AttackPoint);

					int unknown_var44 = 0;
					Read<int>("unknown", handler, unknown_var44);
					Read<int>("attackCounter", handler, output3.AttackCounter);
					Read<Vector3S>("position", handler, output3.Position);
					Read<Vector3S>("rotation", handler, output3.Rotation);

					if (handler.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);
					}


					return;
				}
			}

			if (mode_var0 == 2)
			{
				StackWatch<PacketHandler> watch_62(handler, "if mode_var0 == 2");
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn);
				Read<int>("skillId", handler, output4.SkillId);
				Read<short>("skillLevel", handler, output4.SkillLevel);
				Read<unsigned char>("motionPoint", handler, output4.MotionPoint);
				Read<Vector3S>("position", handler, output4.Position);

				Vector3S unknown_var53;
				Read<Vector3S>("unknown", handler, unknown_var53);
				Read<Vector3S>("rotation", handler, output4.Rotation);

				Vector3S unknown_var55;
				Read<Vector3S>("unknown", handler, unknown_var55);

				bool unknown_var56 = false;
				Read<bool>("unknown", handler, unknown_var56);

				ValidateValues(handler, "unknown", unknown_var56, (bool)0, (bool)1);

				int unknown_var57 = 0;
				Read<int>("unknown", handler, unknown_var57);

				ValidateValues(handler, "unknown", unknown_var57, (int)0);

				unsigned char unknown_var58 = 0;
				Read<unsigned char>("unknown", handler, unknown_var58);

				ValidateValues(handler, "unknown", unknown_var58, (unsigned char)0);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_75(handler, "if mode_var0 == 3");
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn);
				Read<int>("serverTick", handler, output5.ServerTick);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_79(handler, "if mode_var0 == 4");
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x3d 'SkillDamage' v2503");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn);
				Read<int>("casterId", handler, output0.CasterId);
				Read<unsigned int>("skillId", handler, output0.SkillId);
				Read<unsigned short>("skillLevel", handler, output0.SkillLevel);
				Read<unsigned char>("motionPoint", handler, output0.MotionPoint);
				Read<unsigned char>("attackPoint", handler, output0.AttackPoint);
				Read<Vector3Short>("position", handler, output0.Position);
				Read<Vector3S>("direction", handler, output0.Direction);
				Read<bool>("isChaining", handler, output0.IsChaining);

				ValidateValues(handler, "isChaining", output0.IsChaining, (bool)0, (bool)1);

				unsigned char count_var10 = 0;
				Read<unsigned char>("count", handler, count_var10);

				ResizeVector(handler, output0.Hits, count_var10);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var10 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_13(handler, "output0.Hits[", i, "]"); 
					long long unknown_var11 = 0;
					Read<long long>("unknown", handler, unknown_var11);
					Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack);
					Read<int>("targetId", handler, output0.Hits[i].TargetId);
					Read<short>("animation", handler, output0.Hits[i].Animation);
				}

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);
				}


				return;
			}

			if (mode_var0 == 1)
			{
				StackWatch<PacketHandler> watch_18(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 3");
				Server::SkillDamageDotPacket output2;
				ParseSkillDamageDotPacket_v12(handler, output2);

				Read<long long>("damage", handler, output2.Damage);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);
				}


				return;
			}

			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 4");
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
				StackWatch<PacketHandler> watch_28(handler, "if mode_var0 == 5");
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
				StackWatch<PacketHandler> watch_31(handler, "if mode_var0 == 6");
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
				StackWatch<PacketHandler> watch_34(handler, "if mode_var0 == 7");
				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16);

				int count_var17 = 0;
				Read<int>("count", handler, count_var17);

				for (int i = 0; i < count_var17 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_37(handler, "array1[", i, "]"); 
					int unknown_var18 = 0;
					Read<int>("unknown", handler, unknown_var18);
				}
			}

			if (mode_var0 == 8)
			{
				StackWatch<PacketHandler> watch_39(handler, "if mode_var0 == 8");
				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19);

				bool hasTarget_var20 = false;
				Read<bool>("hasTarget", handler, hasTarget_var20);

				ValidateValues(handler, "hasTarget", hasTarget_var20, (bool)0, (bool)1);

				if (hasTarget_var20)
				{
					StackWatch<PacketHandler> watch_42(handler, "if hasTarget_var20");
					unsigned int skillId_var21 = 0;
					Read<unsigned int>("skillId", handler, skillId_var21);

					unsigned short skillLevel_var22 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var22);

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23);

					int npcId_var24 = 0;
					Read<int>("npcId", handler, npcId_var24);
				}
			}
		}

		template <>
		void ParsePacket<2509, ServerPacket, 0xc>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream();

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0xc 'CharacterList' v2509");

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0);

			ValidateValues(handler, "mode", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				StackWatch<PacketHandler> watch_1(handler, "if mode_var0 == 0");
				Server::CharacterListLoadPacket output0;

				unsigned char count_var1 = 0;
				Read<unsigned char>("count", handler, count_var1);

				ResizeVector(handler, output0.Characters, count_var1);

				if (handler.PacketStream().HasRecentlyFailed)
				{
					return;
				}
				for (unsigned char i = 0; i < count_var1 && !handler.PacketStream().HasRecentlyFailed; ++i)
				{
					StackWatch<PacketHandler> watch_4(handler, "output0.Characters[", i, "]"); 
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
				StackWatch<PacketHandler> watch_6(handler, "if mode_var0 == 1");
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
				StackWatch<PacketHandler> watch_9(handler, "if mode_var0 == 2");
				Server::CharacterListDeletePacket output2;

				int unknown_var2 = 0;
				Read<int>("unknown", handler, unknown_var2);
				Read<long long>("characterId", handler, output2.CharacterId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePacket>(output2);
				}


				return;
			}

			if (mode_var0 == 3)
			{
				StackWatch<PacketHandler> watch_13(handler, "if mode_var0 == 3");
			}
			if (mode_var0 == 4)
			{
				StackWatch<PacketHandler> watch_14(handler, "if mode_var0 == 4");
				unsigned char unknown_var4 = 0;
				Read<unsigned char>("unknown", handler, unknown_var4);
			}

			if (mode_var0 == 5)
			{
				StackWatch<PacketHandler> watch_16(handler, "if mode_var0 == 5");
				Server::CharacterListDeletePendingPacket output3;

				Read<long long>("characterId", handler, output3.CharacterId);
				Read<int>("messageId", handler, output3.MessageId);
				Read<long long>("deleteTime", handler, output3.DeleteTime);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListDeletePendingPacket>(output3);
				}


				return;
			}

			if (mode_var0 == 6)
			{
				StackWatch<PacketHandler> watch_21(handler, "if mode_var0 == 6");
				Server::CharacterListCancelDeletePacket output4;

				Read<long long>("characterId", handler, output4.CharacterId);
				Read<int>("messageId", handler, output4.MessageId);

				if (handler.Succeeded())
				{
					handler.PacketParsed<Server::CharacterListCancelDeletePacket>(output4);
				}


				return;
			}

			if (mode_var0 == 7)
			{
				StackWatch<PacketHandler> watch_25(handler, "if mode_var0 == 7");
				Server::CharacterListChangeNamePacket output5;

				Read<int>("confirm", handler, output5.Confirm);
				Read<long long>("characterId", handler, output5.CharacterId);
				Read<std::wstring>("name", handler, output5.Name);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x17 'FieldAddPlayer' v2509");

			Server::FieldAddPlayerPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			ParseCharacterData_v13(handler, output0.Character);
			ParseSkillTreeData_v2509(handler, output0.SkillTree);

			Read<Vector3S>("position", handler, output0.Position);
			Read<Vector3S>("Rotation", handler, output0.Rotation);

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3);

			{
				StackWatch<PacketHandler> watch_7(handler, "output0.Stats");

				unsigned char statCount_var4 = 0;
				Read<unsigned char>("statCount", handler, statCount_var4);

				if (statCount_var4 == 35)
				{
					StackWatch<PacketHandler> watch_9(handler, "if statCount_var4 == 35");
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

					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Max);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Max);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Max);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Max);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Max);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Base);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Base);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Base);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Base);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Base);
					Read<unsigned long long>("health", handler, output0.Stats.Basic[0].Current);
					Read<unsigned int>("attackSpeed", handler, output0.Stats.Basic[1].Current);
					Read<unsigned int>("moveSpeed", handler, output0.Stats.Basic[2].Current);
					Read<unsigned int>("mountMoveSpeed", handler, output0.Stats.Basic[3].Current);
					Read<unsigned int>("jumpHeight", handler, output0.Stats.Basic[4].Current);
				}

				if (statCount_var4 != 35)
				{
					StackWatch<PacketHandler> watch_32(handler, "if statCount_var4 != 35");
					ResizeVector(handler, output0.Stats.Basic, statCount_var4);

					if (handler.PacketStream().HasRecentlyFailed)
					{
						return;
					}
					for (unsigned char i = 0; i < statCount_var4 && !handler.PacketStream().HasRecentlyFailed; ++i)
					{
						StackWatch<PacketHandler> watch_33(handler, "output0.Stats.Basic[", i, "]"); 
						Read<unsigned char>("statType", handler, output0.Stats.Basic[i].Type);

						if (output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_35(handler, "if output0.Stats.Basic[i].Type == (Enum::StatAttributeBasic)4");
							Read<unsigned long long>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned long long>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned long long>("current", handler, output0.Stats.Basic[i].Current);
						}

						if (output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4)
						{
							StackWatch<PacketHandler> watch_39(handler, "if output0.Stats.Basic[i].Type != (Enum::StatAttributeBasic)4");
							Read<unsigned int>("max", handler, output0.Stats.Basic[i].Max);
							Read<unsigned int>("base", handler, output0.Stats.Basic[i].Base);
							Read<unsigned int>("current", handler, output0.Stats.Basic[i].Current);
						}
					}
				}
			}
			Read<bool>("inBattle", handler, output0.InBattle);

			ValidateValues(handler, "inBattle", output0.InBattle, (bool)0, (bool)1);

			unsigned char unknown_var34 = 0;
			Read<unsigned char>("unknown", handler, unknown_var34);
			ParseCubeItemData_v12(handler, output0.HeldCube);

			int unknown_var35 = 0;
			Read<int>("unknown", handler, unknown_var35);

			Color4I_BGRA skinColorPrimary_var36;
			Read<Color4I_BGRA>("skinColorPrimary", handler, skinColorPrimary_var36);

			output0.SkinColor.Primary = (Color4I)skinColorPrimary_var36;

			Color4I_BGRA skinColorSecondary_var37;
			Read<Color4I_BGRA>("skinColorSecondary", handler, skinColorSecondary_var37);

			output0.SkinColor.Secondary = (Color4I)skinColorSecondary_var37;

			Read<std::wstring>("profileUrl", handler, output0.ProfileUrl);
			Read<bool>("onMount", handler, output0.OnMount);

			ValidateValues(handler, "onMount", output0.OnMount, (bool)0, (bool)1);

			if (output0.OnMount)
			{
				StackWatch<PacketHandler> watch_51(handler, "if output0.OnMount");
				ParseMountData_v13(handler, output0.Mount);
			}

			int unknown_var40 = 0;
			Read<int>("unknown", handler, unknown_var40);
			Read<long long>("timestamp", handler, output0.Timestamp);
			Read<int>("weeklyArchitectScore", handler, output0.WeeklyArchitectScore);
			Read<int>("architectScore", handler, output0.ArchitectScore);

			bool isDeflated_var44 = false;
			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			int bufferSize_var45 = 0;
			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_59(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer0(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentItems_v2509(handler, output0.Equipment);
				ParseCharacterEquipmentSkins_v2509(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_64(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer1(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentFashion_v2509(handler, output0.Equipment);
			}

			Read<bool>("isDeflated", handler, isDeflated_var44);

			ValidateValues(handler, "isDeflated", isDeflated_var44, (bool)0, (bool)1);

			Read<int>("bufferSize", handler, bufferSize_var45);

			{
				StackWatch<PacketHandler> watch_68(handler, "buffer[", bufferSize_var45, "]");
				Buffer buffer2(handler, (size_t)bufferSize_var45, isDeflated_var44);
				ParseCharacterEquipmentBadges_v2509(handler, output0.Equipment);
			}

			short effectCount_var46 = 0;
			Read<short>("effectCount", handler, effectCount_var46);

			ResizeVector(handler, output0.Effects, effectCount_var46);

			if (handler.PacketStream().HasRecentlyFailed)
			{
				return;
			}
			for (short i = 0; i < effectCount_var46 && !handler.PacketStream().HasRecentlyFailed; ++i)
			{
				StackWatch<PacketHandler> watch_71(handler, "output0.Effects[", i, "]"); 
				Read<int>("targetId", handler, output0.Effects[i].TargetId);
				Read<int>("effectInstanceId", handler, output0.Effects[i].InstanceId);
				Read<int>("sourceId", handler, output0.Effects[i].SourceId);
				ParseEffectStats_v12(handler, output0.Effects[i].Stats);

				Read<bool>("enabled", handler, output0.Effects[i].Enabled);

				ValidateValues(handler, "enabled", output0.Effects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.Effects[i].ShieldHealth);
			}

			int unknown_var52 = 0;
			Read<int>("unknown", handler, unknown_var52);

			int unknown_var53 = 0;
			Read<int>("unknown", handler, unknown_var53);

			unsigned char unknown_var54 = 0;
			Read<unsigned char>("unknown", handler, unknown_var54);

			int unknown_var55 = 0;
			Read<int>("unknown", handler, unknown_var55);

			unsigned char unknown_var56 = 0;
			Read<unsigned char>("unknown", handler, unknown_var56);

			unsigned char unknown_var57 = 0;
			Read<unsigned char>("unknown", handler, unknown_var57);
			Read<int>("titleId", handler, output0.TitleId);
			Read<short>("insigniaId", handler, output0.InsigniaId);
			Read<unsigned char>("insigniaValue", handler, output0.InsigniaValue);
			Read<int>("petActorId", handler, output0.Pet.ActorId);
			Read<bool>("hasPet", handler, output0.HasPet);

			ValidateValues(handler, "hasPet", output0.HasPet, (bool)0, (bool)1);

			if (output0.HasPet)
			{
				StackWatch<PacketHandler> watch_89(handler, "if output0.HasPet");
				Read<int>("petItemId", handler, output0.Pet.ItemId);
				Read<long long>("petItemInstanceId", handler, output0.Pet.ItemInstanceId);
				Read<int>("petRarity", handler, output0.Pet.Rarity);

				ValidateValues(handler, "petRarity", output0.Pet.Rarity, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);
				ParseItemData_v2497(handler, output0.Pet.ItemData, (unsigned int)output0.Pet.ItemId);
			}

			Read<long long>("premiumExpirationTime", handler, output0.PremiumExpirationTime);

			int unknown_var67 = 0;
			Read<int>("unknown", handler, unknown_var67);

			unsigned char unknown_var68 = 0;
			Read<unsigned char>("unknown", handler, unknown_var68);

			short unknown_var69 = 0;
			Read<short>("unknown", handler, unknown_var69);

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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x49 'Job' v2509");

			Server::JobPacket output0;

			Read<int>("actorId", handler, output0.ActorId);
			Read<unsigned char>("mode", handler, output0.Mode);

			ValidateValues(handler, "mode", output0.Mode, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)10, (unsigned char)2, (unsigned char)3, (unsigned char)7, (unsigned char)11);
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

				StackWatch<PacketHandler> watch_block(handler, "[Server] 0x78 'CharaerInfo' v2509");

			Server::CharacterInfoPacket output0;

			Read<long long>("characterId", handler, output0.CharacterId);
			Read<bool>("found", handler, output0.Found);

			ValidateValues(handler, "found", output0.Found, (bool)0, (bool)1);

			if (output0.Found)
			{
				StackWatch<PacketHandler> watch_3(handler, "if output0.Found");
				long long notAccountId_var2 = 0;
				Read<long long>("notAccountId", handler, notAccountId_var2);

				long long characterId2_var3 = 0;
				Read<long long>("characterId2", handler, characterId2_var3);
				Read<long long>("currentTime", handler, output0.CurrentTime);

				int bufferSize_var5 = 0;
				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_8(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer0(handler, (size_t)bufferSize_var5, false);
					ParseCharacterDetailsHeader_v12(handler, output0.Details);

					{
						StackWatch<PacketHandler> watch_10(handler, "output0.Details.Stats");
						ParseCharacterDetailsBasicStats_v2509(handler, output0.Details.Stats);
						ParseCharacterDetailsSpecialStats_v2497(handler, output0.Details.Stats);
					}
					ParseCharacterDetailsBody_v12(handler, output0.Details);

					long long unknown_var6 = 0;
					Read<long long>("unknown", handler, unknown_var6);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_16(handler, "buffer[", bufferSize_var5, "]");
					Buffer buffer1(handler, (size_t)bufferSize_var5, false);
					ParseCharacterEquipmentItems_v2509(handler, output0.Equipment);
					ParseCharacterEquipmentSkins_v2509(handler, output0.Equipment);
				}

				Read<int>("bufferSize", handler, bufferSize_var5);

				{
					StackWatch<PacketHandler> watch_20(handler, "buffer[", bufferSize_var5, "]");
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
