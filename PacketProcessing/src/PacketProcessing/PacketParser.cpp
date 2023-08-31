#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void ParseBasicStat_v12(PacketHandler& handler, Maple::Game::BasicStat& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");
			Read<float>("rate", handler, blockOutput.Rate, "\t\t");
		}

		void ParseSpecialStat_v12(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<float>("value", handler, blockOutput.Value, "\t\t");
			Read<float>("rate", handler, blockOutput.Rate, "\t\t");
		}

		void ParseBasicAndSpecialStats_v12(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			for (short i = 0; i < statCount_var0 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				ParseBasicStat_v12(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			for (short i = 0; i < statCount_var0 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				ParseSpecialStat_v12(handler, blockOutput.Special[i]);
			}
		}

		void ParseItemBinding_v12(PacketHandler& handler, Maple::Game::ItemBinding& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<long long>("characterId", handler, blockOutput.CharacterId, "\t\t");
			Read<std::wstring>("name", handler, blockOutput.Name, "\t\t");
		}

		void ParseItemCustomization_v12(PacketHandler& handler, Maple::Game::ItemCustomization& blockOutput, unsigned int itemId_param0)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;


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

			itemCategory_var5 = handler.GetItemCategory(itemId_param0);

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
					Read<Vector3S>("position1", handler, blockOutput.Decal.Position1, "\t\t\t\t");
					Read<Vector3S>("position2", handler, blockOutput.Decal.Position2, "\t\t\t\t");
					Read<Vector3S>("position3", handler, blockOutput.Decal.Position3, "\t\t\t\t");
					Read<Vector3S>("position4", handler, blockOutput.Decal.Position4, "\t\t\t\t");
				}
			}
		}

		void ParseItemData_v12(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var2, (int)18446744073709551615);

			Read<long long>("creationTime", handler, blockOutput.CreationTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");
			Read<int>("timesChanged", handler, blockOutput.TimesChanged, "\t\t");
			Read<int>("remainingUses", handler, blockOutput.RemainingUses, "\t\t");
			Read<bool>("isLocked", handler, blockOutput.IsLocked, "\t\t");

			ValidateValues(stream, "isLocked", "\t\t", blockOutput.IsLocked, (bool)0, (bool)1);

			Read<long long>("unlockTime", handler, blockOutput.UnlockTime, "\t\t");
			Read<short>("glamorForges", handler, blockOutput.GlamorForges, "\t\t");

			unsigned char unknownBool_var11 = 0;
			Read<unsigned char>("unknownBool", handler, unknownBool_var11, "\t\t");

			ValidateValues(stream, "unknownBool", "\t\t", unknownBool_var11, (unsigned char)0);

			int unknown_var12 = 0;
			Read<int>("unknown", handler, unknown_var12, "\t\t");
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{

				unsigned char unknown_var13 = 0;
				Read<unsigned char>("unknown", handler, unknown_var13, "\t\t\t");
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Constant);

				int unknown_var14 = 0;
				Read<int>("unknown", handler, unknown_var14, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Static);

				int unknown_var15 = 0;
				Read<int>("unknown", handler, unknown_var15, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Random);

				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var16, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Title);

				int unknown_var17 = 0;
				Read<int>("unknown", handler, unknown_var17, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var17, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment1);

				int unknown_var18 = 0;
				Read<int>("unknown", handler, unknown_var18, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var18, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment2);

				int unknown_var19 = 0;
				Read<int>("unknown", handler, unknown_var19, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var19, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment3);

				int unknown_var20 = 0;
				Read<int>("unknown", handler, unknown_var20, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var20, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment4);

				int unknown_var21 = 0;
				Read<int>("unknown", handler, unknown_var21, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var21, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment5);

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var22, (int)0);
			}

			{

				Read<int>("enchantLevel", handler, blockOutput.Enchantment.Level, "\t\t\t");
				Read<int>("enchantExp", handler, blockOutput.Enchantment.EnchantExp, "\t\t\t");
				Read<unsigned char>("enchantCharges", handler, blockOutput.Enchantment.EnchantCharges, "\t\t\t");

				long long unknown_var26 = 0;
				Read<long long>("unknown", handler, unknown_var26, "\t\t\t");

				int unknown_var27 = 0;
				Read<int>("unknown", handler, unknown_var27, "\t\t\t");

				int unknown_var28 = 0;
				Read<int>("unknown", handler, unknown_var28, "\t\t\t");
				Read<bool>("canRepackage", handler, blockOutput.Enchantment.CanRepackage, "\t\t\t");

				ValidateValues(stream, "canRepackage", "\t\t\t", blockOutput.Enchantment.CanRepackage, (bool)0, (bool)1);

				Read<int>("charges", handler, blockOutput.Enchantment.Charges, "\t\t\t");

				unsigned char basicStatCount_var31 = 0;
				Read<unsigned char>("basicStatCount", handler, basicStatCount_var31, "\t\t\t");

				ResizeVector(handler, blockOutput.Enchantment.Basic, basicStatCount_var31);

				for (unsigned char i = 0; i < basicStatCount_var31 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("type", handler, blockOutput.Enchantment.Basic[i].Type, "\t\t\t\t");
					Read<int>("value", handler, blockOutput.Enchantment.Basic[i].Value, "\t\t\t\t");
					Read<float>("rate", handler, blockOutput.Enchantment.Basic[i].Rate, "\t\t\t\t");
				}
			}

			{
				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var36 = 0;
					Read<int>("statCount", handler, statCount_var36, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var36);

					for (int i = 0; i < statCount_var36 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var36, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var36);

					for (int i = 0; i < statCount_var36 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var37 = 0;

			extraDataType_var37 = handler.GetItemExtraDataType(itemId_param0);

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var37, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var37 == 1)
			{

				{
					long long unknown_var38 = 0;
					Read<long long>("unknown", handler, unknown_var38, "\t\t\t\t");
					Read<std::wstring>("fileName", handler, blockOutput.Template.FileName, "\t\t\t\t");
					Read<std::wstring>("name", handler, blockOutput.Template.Name, "\t\t\t\t");

					unsigned char unknown_var41 = 0;
					Read<unsigned char>("unknown", handler, unknown_var41, "\t\t\t\t");

					int unknown_var42 = 0;
					Read<int>("unknown", handler, unknown_var42, "\t\t\t\t");
					Read<long long>("accountId", handler, blockOutput.Template.AccountId, "\t\t\t\t");
					Read<long long>("characterId", handler, blockOutput.Template.CharacterId, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Template.Author, "\t\t\t\t");
					Read<long long>("creationTime", handler, blockOutput.Template.CreationTime, "\t\t\t\t");
					Read<std::wstring>("url", handler, blockOutput.Template.Url, "\t\t\t\t");

					unsigned char unknown_var48 = 0;
					Read<unsigned char>("unknown", handler, unknown_var48, "\t\t\t\t");
				}

				{

					long long unknown_var49 = 0;
					Read<long long>("unknown", handler, unknown_var49, "\t\t\t\t");

					int unknown_var50 = 0;
					Read<int>("unknown", handler, unknown_var50, "\t\t\t\t");

					int unknown_var51 = 0;
					Read<int>("unknown", handler, unknown_var51, "\t\t\t\t");

					int unknown_var52 = 0;
					Read<int>("unknown", handler, unknown_var52, "\t\t\t\t");

					long long unknown_var53 = 0;
					Read<long long>("unknown", handler, unknown_var53, "\t\t\t\t");

					int unknown_var54 = 0;
					Read<int>("unknown", handler, unknown_var54, "\t\t\t\t");

					long long unknown_var55 = 0;
					Read<long long>("unknown", handler, unknown_var55, "\t\t\t\t");

					long long unknown_var56 = 0;
					Read<long long>("unknown", handler, unknown_var56, "\t\t\t\t");

					std::wstring unknown_var57;
					Read<std::wstring>("unknown", handler, unknown_var57, "\t\t\t\t");
				}
			}

			if (extraDataType_var37 == 2)
			{

				{
					Read<std::wstring>("name", handler, blockOutput.Pet.Name, "\t\t\t\t");
					Read<long long>("exp", handler, blockOutput.Pet.Exp, "\t\t\t\t");
					Read<int>("evolvePoints", handler, blockOutput.Pet.EvolvePoints, "\t\t\t\t");
					Read<int>("level", handler, blockOutput.Pet.Level, "\t\t\t\t");
					Read<bool>("hasItems", handler, blockOutput.Pet.HasItems, "\t\t\t\t");

					ValidateValues(stream, "hasItems", "\t\t\t\t", blockOutput.Pet.HasItems, (bool)0, (bool)1);
				}
			}

			if (extraDataType_var37 == 3)
			{

				{
					Read<int>("length", handler, blockOutput.Music.Length, "\t\t\t\t");
					Read<int>("instrument", handler, blockOutput.Music.Instrument, "\t\t\t\t");
					Read<std::wstring>("title", handler, blockOutput.Music.Title, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Music.Author, "\t\t\t\t");

					int unknown_var67 = 0;
					Read<int>("unknown", handler, unknown_var67, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var67, (int)1);

					Read<long long>("authorId", handler, blockOutput.Music.AuthorId, "\t\t\t\t");
					Read<bool>("isLocked", handler, blockOutput.Music.IsLocked, "\t\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t\t", blockOutput.Music.IsLocked, (bool)0, (bool)1);

					long long unknown_var70 = 0;
					Read<long long>("unknown", handler, unknown_var70, "\t\t\t\t");

					long long unknown_var71 = 0;
					Read<long long>("unknown", handler, unknown_var71, "\t\t\t\t");
				}
			}

			if (extraDataType_var37 == 4)
			{

				{
					unsigned char unknown_var72 = 0;
					Read<unsigned char>("unknown", handler, unknown_var72, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var72, (unsigned char)1);

					Read<unsigned char>("type", handler, blockOutput.Badge.Type, "\t\t\t\t");

					ValidateValues(stream, "type", "\t\t\t\t", blockOutput.Badge.Type, (unsigned char)1, (unsigned char)11);

					Read<std::wstring>("id", handler, blockOutput.Badge.Id, "\t\t\t\t");

					if (blockOutput.Badge.Type == 1)
					{
						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[0], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[0], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[1], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[1], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[2], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[2], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[3], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[3], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[4], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[4], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[5], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[5], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[6], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[6], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[7], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[7], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[8], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[8], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[9], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[9], (bool)0, (bool)1);
					}

					if (blockOutput.Badge.Type == 11)
					{
						Read<int>("petSkinId", handler, blockOutput.Badge.PetSkinId, "\t\t\t\t\t");
					}
				}
			}

			{
				Read<int>("transferFlags", handler, blockOutput.ItemTransfer.TransferFlags, "\t\t\t");

				bool unknown_var87 = false;
				Read<bool>("unknown", handler, unknown_var87, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var87, (bool)0, (bool)1);

				Read<int>("remainingTrades", handler, blockOutput.ItemTransfer.RemainingTrades, "\t\t\t");
				Read<int>("remainingPackages", handler, blockOutput.ItemTransfer.RemainingPackages, "\t\t\t");

				unsigned char unknown_var90 = 0;
				Read<unsigned char>("unknown", handler, unknown_var90, "\t\t\t");

				bool unknown_var91 = false;
				Read<bool>("unknown", handler, unknown_var91, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var91, (bool)0, (bool)1);

				Read<bool>("isBound", handler, blockOutput.ItemTransfer.IsBound, "\t\t\t");

				ValidateValues(stream, "isBound", "\t\t\t", blockOutput.ItemTransfer.IsBound, (bool)0, (bool)1);

				if (blockOutput.ItemTransfer.IsBound)
				{
					ParseItemBinding_v12(handler, blockOutput.ItemTransfer.Binding);
				}
			}

			{

				Read<unsigned char>("maxSlots", handler, blockOutput.ItemSocket.MaxSlots, "\t\t\t");
				Read<unsigned char>("unlockedSlots", handler, blockOutput.ItemSocket.UnlockedSlots, "\t\t\t");

				ResizeVector(handler, blockOutput.ItemSocket.Sockets, blockOutput.ItemSocket.UnlockedSlots);

				for (unsigned char i = 0; i < blockOutput.ItemSocket.UnlockedSlots && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<bool>("hasGem", handler, blockOutput.ItemSocket.Sockets[i].HasGem, "\t\t\t\t");

					ValidateValues(stream, "hasGem", "\t\t\t\t", blockOutput.ItemSocket.Sockets[i].HasGem, (bool)0, (bool)1);

					if (blockOutput.ItemSocket.Sockets[i].HasGem)
					{

						{
							Read<int>("itemId", handler, blockOutput.ItemSocket.Sockets[i].Gem.ItemId, "\t\t\t\t\t\t");
							Read<bool>("isBound", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsBound, "\t\t\t\t\t\t");

							ValidateValues(stream, "isBound", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsBound, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsBound)
							{
								ParseItemBinding_v12(handler, blockOutput.ItemSocket.Sockets[i].Gem.Binding);
							}

							Read<bool>("isLocked", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsLocked)
							{
								unsigned char unknown_var99 = 0;
								Read<unsigned char>("unknown", handler, unknown_var99, "\t\t\t\t\t\t\t");
								Read<long long>("unlockTime", handler, blockOutput.ItemSocket.Sockets[i].Gem.UnlockTime, "\t\t\t\t\t\t\t");
							}
						}
					}
				}
			}

			{
				Read<long long>("characterId", handler, blockOutput.ItemCouple.CharacterId, "\t\t\t");

				if (blockOutput.ItemCouple.CharacterId != 0)
				{
					Read<std::wstring>("name", handler, blockOutput.ItemCouple.Name, "\t\t\t\t");
					Read<bool>("isCreator", handler, blockOutput.ItemCouple.IsCreator, "\t\t\t\t");

					ValidateValues(stream, "isCreator", "\t\t\t\t", blockOutput.ItemCouple.IsCreator, (bool)0, (bool)1);
				}
			}
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		void ParseItemData_v2486(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			Read<long long>("creationTime", handler, blockOutput.CreationTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");
			Read<int>("timesChanged", handler, blockOutput.TimesChanged, "\t\t");
			Read<int>("remainingUses", handler, blockOutput.RemainingUses, "\t\t");
			Read<bool>("isLocked", handler, blockOutput.IsLocked, "\t\t");

			ValidateValues(stream, "isLocked", "\t\t", blockOutput.IsLocked, (bool)0, (bool)1);

			Read<long long>("unlockTime", handler, blockOutput.UnlockTime, "\t\t");
			Read<short>("glamorForges", handler, blockOutput.GlamorForges, "\t\t");

			unsigned char unknownBool_var11 = 0;
			Read<unsigned char>("unknownBool", handler, unknownBool_var11, "\t\t");

			ValidateValues(stream, "unknownBool", "\t\t", unknownBool_var11, (unsigned char)0);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Constant);

				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var12, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Static);

				int unknown_var13 = 0;
				Read<int>("unknown", handler, unknown_var13, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var13, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Random);

				int unknown_var14 = 0;
				Read<int>("unknown", handler, unknown_var14, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Title);

				int unknown_var15 = 0;
				Read<int>("unknown", handler, unknown_var15, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)0);
				ParseBasicAndSpecialStats_v12(handler, blockOutput.Stats.Empowerment1);

				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var16, (int)0);
			}

			{

				Read<int>("enchantLevel", handler, blockOutput.Enchantment.Level, "\t\t\t");
				Read<int>("enchantExp", handler, blockOutput.Enchantment.EnchantExp, "\t\t\t");
				Read<unsigned char>("enchantCharges", handler, blockOutput.Enchantment.EnchantCharges, "\t\t\t");

				long long unknown_var20 = 0;
				Read<long long>("unknown", handler, unknown_var20, "\t\t\t");

				int unknown_var21 = 0;
				Read<int>("unknown", handler, unknown_var21, "\t\t\t");

				int unknown_var22 = 0;
				Read<int>("unknown", handler, unknown_var22, "\t\t\t");
				Read<bool>("canRepackage", handler, blockOutput.Enchantment.CanRepackage, "\t\t\t");

				ValidateValues(stream, "canRepackage", "\t\t\t", blockOutput.Enchantment.CanRepackage, (bool)0, (bool)1);

				Read<int>("charges", handler, blockOutput.Enchantment.Charges, "\t\t\t");

				unsigned char basicStatCount_var25 = 0;
				Read<unsigned char>("basicStatCount", handler, basicStatCount_var25, "\t\t\t");

				ResizeVector(handler, blockOutput.Enchantment.Basic, basicStatCount_var25);

				for (unsigned char i = 0; i < basicStatCount_var25 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("type", handler, blockOutput.Enchantment.Basic[i].Type, "\t\t\t\t");
					Read<int>("value", handler, blockOutput.Enchantment.Basic[i].Value, "\t\t\t\t");
					Read<float>("rate", handler, blockOutput.Enchantment.Basic[i].Rate, "\t\t\t\t");
				}
			}

			{
				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var30 = 0;
					Read<int>("statCount", handler, statCount_var30, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var30);

					for (int i = 0; i < statCount_var30 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v12(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var30, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var30);

					for (int i = 0; i < statCount_var30 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v12(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var31 = 0;

			extraDataType_var31 = handler.GetItemExtraDataType(itemId_param0);

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var31, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var31 == 1)
			{

				{
					long long unknown_var32 = 0;
					Read<long long>("unknown", handler, unknown_var32, "\t\t\t\t");
					Read<std::wstring>("fileName", handler, blockOutput.Template.FileName, "\t\t\t\t");
					Read<std::wstring>("name", handler, blockOutput.Template.Name, "\t\t\t\t");

					unsigned char unknown_var35 = 0;
					Read<unsigned char>("unknown", handler, unknown_var35, "\t\t\t\t");

					int unknown_var36 = 0;
					Read<int>("unknown", handler, unknown_var36, "\t\t\t\t");
					Read<long long>("accountId", handler, blockOutput.Template.AccountId, "\t\t\t\t");
					Read<long long>("characterId", handler, blockOutput.Template.CharacterId, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Template.Author, "\t\t\t\t");
					Read<long long>("creationTime", handler, blockOutput.Template.CreationTime, "\t\t\t\t");
					Read<std::wstring>("url", handler, blockOutput.Template.Url, "\t\t\t\t");

					unsigned char unknown_var42 = 0;
					Read<unsigned char>("unknown", handler, unknown_var42, "\t\t\t\t");
				}

				{

					long long unknown_var43 = 0;
					Read<long long>("unknown", handler, unknown_var43, "\t\t\t\t");

					int unknown_var44 = 0;
					Read<int>("unknown", handler, unknown_var44, "\t\t\t\t");

					int unknown_var45 = 0;
					Read<int>("unknown", handler, unknown_var45, "\t\t\t\t");

					int unknown_var46 = 0;
					Read<int>("unknown", handler, unknown_var46, "\t\t\t\t");

					long long unknown_var47 = 0;
					Read<long long>("unknown", handler, unknown_var47, "\t\t\t\t");

					int unknown_var48 = 0;
					Read<int>("unknown", handler, unknown_var48, "\t\t\t\t");

					long long unknown_var49 = 0;
					Read<long long>("unknown", handler, unknown_var49, "\t\t\t\t");

					long long unknown_var50 = 0;
					Read<long long>("unknown", handler, unknown_var50, "\t\t\t\t");

					std::wstring unknown_var51;
					Read<std::wstring>("unknown", handler, unknown_var51, "\t\t\t\t");
				}
			}

			if (extraDataType_var31 == 2)
			{

				{
					Read<std::wstring>("name", handler, blockOutput.Pet.Name, "\t\t\t\t");
					Read<long long>("exp", handler, blockOutput.Pet.Exp, "\t\t\t\t");
					Read<int>("evolvePoints", handler, blockOutput.Pet.EvolvePoints, "\t\t\t\t");
					Read<int>("level", handler, blockOutput.Pet.Level, "\t\t\t\t");
					Read<bool>("hasItems", handler, blockOutput.Pet.HasItems, "\t\t\t\t");

					ValidateValues(stream, "hasItems", "\t\t\t\t", blockOutput.Pet.HasItems, (bool)0, (bool)1);
				}
			}

			if (extraDataType_var31 == 3)
			{

				{
					Read<int>("length", handler, blockOutput.Music.Length, "\t\t\t\t");
					Read<int>("instrument", handler, blockOutput.Music.Instrument, "\t\t\t\t");
					Read<std::wstring>("title", handler, blockOutput.Music.Title, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Music.Author, "\t\t\t\t");

					int unknown_var61 = 0;
					Read<int>("unknown", handler, unknown_var61, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var61, (int)1);

					Read<long long>("authorId", handler, blockOutput.Music.AuthorId, "\t\t\t\t");
					Read<bool>("isLocked", handler, blockOutput.Music.IsLocked, "\t\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t\t", blockOutput.Music.IsLocked, (bool)0, (bool)1);

					long long unknown_var64 = 0;
					Read<long long>("unknown", handler, unknown_var64, "\t\t\t\t");

					long long unknown_var65 = 0;
					Read<long long>("unknown", handler, unknown_var65, "\t\t\t\t");
				}
			}

			if (extraDataType_var31 == 4)
			{

				{
					unsigned char unknown_var66 = 0;
					Read<unsigned char>("unknown", handler, unknown_var66, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var66, (unsigned char)1);

					Read<unsigned char>("type", handler, blockOutput.Badge.Type, "\t\t\t\t");

					ValidateValues(stream, "type", "\t\t\t\t", blockOutput.Badge.Type, (unsigned char)1, (unsigned char)11);

					Read<int>("id", handler, blockOutput.Badge.BadgeId, "\t\t\t\t");

					if (blockOutput.Badge.Type == 1)
					{
						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[0], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[0], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[1], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[1], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[2], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[2], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[3], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[3], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[4], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[4], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[5], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[5], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[6], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[6], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[7], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[7], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[8], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[8], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[9], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[9], (bool)0, (bool)1);
					}

					if (blockOutput.Badge.Type == 11)
					{
						Read<int>("petSkinId", handler, blockOutput.Badge.PetSkinId, "\t\t\t\t\t");
					}
				}
			}

			{
				Read<int>("transferFlags", handler, blockOutput.ItemTransfer.TransferFlags, "\t\t\t");

				bool unknown_var81 = false;
				Read<bool>("unknown", handler, unknown_var81, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var81, (bool)0, (bool)1);

				Read<int>("remainingTrades", handler, blockOutput.ItemTransfer.RemainingTrades, "\t\t\t");
				Read<int>("remainingPackages", handler, blockOutput.ItemTransfer.RemainingPackages, "\t\t\t");

				unsigned char unknown_var84 = 0;
				Read<unsigned char>("unknown", handler, unknown_var84, "\t\t\t");

				bool unknown_var85 = false;
				Read<bool>("unknown", handler, unknown_var85, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var85, (bool)0, (bool)1);

				Read<bool>("isBound", handler, blockOutput.ItemTransfer.IsBound, "\t\t\t");

				ValidateValues(stream, "isBound", "\t\t\t", blockOutput.ItemTransfer.IsBound, (bool)0, (bool)1);

				if (blockOutput.ItemTransfer.IsBound)
				{
					ParseItemBinding_v12(handler, blockOutput.ItemTransfer.Binding);
				}
			}

			{

				Read<unsigned char>("maxSlots", handler, blockOutput.ItemSocket.MaxSlots, "\t\t\t");
				Read<unsigned char>("unlockedSlots", handler, blockOutput.ItemSocket.UnlockedSlots, "\t\t\t");

				ResizeVector(handler, blockOutput.ItemSocket.Sockets, blockOutput.ItemSocket.UnlockedSlots);

				for (unsigned char i = 0; i < blockOutput.ItemSocket.UnlockedSlots && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<bool>("hasGem", handler, blockOutput.ItemSocket.Sockets[i].HasGem, "\t\t\t\t");

					ValidateValues(stream, "hasGem", "\t\t\t\t", blockOutput.ItemSocket.Sockets[i].HasGem, (bool)0, (bool)1);

					if (blockOutput.ItemSocket.Sockets[i].HasGem)
					{

						{
							Read<int>("itemId", handler, blockOutput.ItemSocket.Sockets[i].Gem.ItemId, "\t\t\t\t\t\t");
							Read<bool>("isBound", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsBound, "\t\t\t\t\t\t");

							ValidateValues(stream, "isBound", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsBound, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsBound)
							{
								ParseItemBinding_v12(handler, blockOutput.ItemSocket.Sockets[i].Gem.Binding);
							}

							Read<bool>("isLocked", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsLocked)
							{
								unsigned char unknown_var93 = 0;
								Read<unsigned char>("unknown", handler, unknown_var93, "\t\t\t\t\t\t\t");
								Read<long long>("unlockTime", handler, blockOutput.ItemSocket.Sockets[i].Gem.UnlockTime, "\t\t\t\t\t\t\t");
							}
						}
					}
				}
			}

			{
				Read<long long>("characterId", handler, blockOutput.ItemCouple.CharacterId, "\t\t\t");

				if (blockOutput.ItemCouple.CharacterId != 0)
				{
					Read<std::wstring>("name", handler, blockOutput.ItemCouple.Name, "\t\t\t\t");
					Read<bool>("isCreator", handler, blockOutput.ItemCouple.IsCreator, "\t\t\t\t");

					ValidateValues(stream, "isCreator", "\t\t\t\t", blockOutput.ItemCouple.IsCreator, (bool)0, (bool)1);
				}
			}
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		void ParseBasicStat_v2497(PacketHandler& handler, Maple::Game::BasicStat& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<int>("value", handler, blockOutput.Value, "\t\t");
		}

		void ParseSpecialStat_v2497(PacketHandler& handler, Maple::Game::SpecialStat& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<short>("type", handler, blockOutput.Type, "\t\t");
			Read<float>("rate", handler, blockOutput.Rate, "\t\t");
		}

		void ParseBasicAndSpecialStats_v2497(PacketHandler& handler, Maple::Game::BonusStats& blockOutput)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			short statCount_var0 = 0;
			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Basic, statCount_var0);

			for (short i = 0; i < statCount_var0 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				ParseBasicStat_v2497(handler, blockOutput.Basic[i]);
			}

			Read<short>("statCount", handler, statCount_var0, "\t\t");

			ResizeVector(handler, blockOutput.Special, statCount_var0);

			for (short i = 0; i < statCount_var0 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				ParseSpecialStat_v2497(handler, blockOutput.Special[i]);
			}
		}

		void ParseItemData_v2497(PacketHandler& handler, Maple::Game::ItemData& blockOutput, unsigned int itemId_param0)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Read<int>("amount", handler, blockOutput.Amount, "\t\t");

			int unknown_var1 = 0;
			Read<int>("unknown", handler, unknown_var1, "\t\t");

			ValidateValues(stream, "unknown", "\t\t", unknown_var1, (int)18446744073709551615);

			int unknown_var2 = 0;
			Read<int>("unknown", handler, unknown_var2, "\t\t");
			Read<long long>("creationTime", handler, blockOutput.CreationTime, "\t\t");
			Read<long long>("expirationTime", handler, blockOutput.ExpirationTime, "\t\t");

			long long unknown_var5 = 0;
			Read<long long>("unknown", handler, unknown_var5, "\t\t");
			Read<int>("timesChanged", handler, blockOutput.TimesChanged, "\t\t");
			Read<int>("remainingUses", handler, blockOutput.RemainingUses, "\t\t");
			Read<bool>("isLocked", handler, blockOutput.IsLocked, "\t\t");

			ValidateValues(stream, "isLocked", "\t\t", blockOutput.IsLocked, (bool)0, (bool)1);

			Read<long long>("unlockTime", handler, blockOutput.UnlockTime, "\t\t");
			Read<short>("glamorForges", handler, blockOutput.GlamorForges, "\t\t");

			unsigned char unknownBool_var11 = 0;
			Read<unsigned char>("unknownBool", handler, unknownBool_var11, "\t\t");

			ValidateValues(stream, "unknownBool", "\t\t", unknownBool_var11, (unsigned char)0);
			ParseItemCustomization_v12(handler, blockOutput.Customization, itemId_param0);

			{
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Static);

				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var12, (int)0);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Random);

				int unknown_var13 = 0;
				Read<int>("unknown", handler, unknown_var13, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var13, (int)0);
				ParseBasicAndSpecialStats_v2497(handler, blockOutput.Stats.Empowerment1);

				int unknown_var14 = 0;
				Read<int>("unknown", handler, unknown_var14, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);
			}

			{

				Read<int>("enchantLevel", handler, blockOutput.Enchantment.Level, "\t\t\t");
				Read<int>("enchantExp", handler, blockOutput.Enchantment.EnchantExp, "\t\t\t");
				Read<unsigned char>("enchantCharges", handler, blockOutput.Enchantment.EnchantCharges, "\t\t\t");

				long long unknown_var18 = 0;
				Read<long long>("unknown", handler, unknown_var18, "\t\t\t");

				int unknown_var19 = 0;
				Read<int>("unknown", handler, unknown_var19, "\t\t\t");

				int unknown_var20 = 0;
				Read<int>("unknown", handler, unknown_var20, "\t\t\t");
				Read<bool>("canRepackage", handler, blockOutput.Enchantment.CanRepackage, "\t\t\t");

				ValidateValues(stream, "canRepackage", "\t\t\t", blockOutput.Enchantment.CanRepackage, (bool)0, (bool)1);

				Read<int>("charges", handler, blockOutput.Enchantment.Charges, "\t\t\t");

				unsigned char basicStatCount_var23 = 0;
				Read<unsigned char>("basicStatCount", handler, basicStatCount_var23, "\t\t\t");

				ResizeVector(handler, blockOutput.Enchantment.Basic, basicStatCount_var23);

				for (unsigned char i = 0; i < basicStatCount_var23 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("type", handler, blockOutput.Enchantment.Basic[i].Type, "\t\t\t\t");
					Read<int>("value", handler, blockOutput.Enchantment.Basic[i].Value, "\t\t\t\t");
				}
			}

			{
				Read<int>("limitBreakLevel", handler, blockOutput.LimitBreak.Level, "\t\t\t");

				{

					int statCount_var27 = 0;
					Read<int>("statCount", handler, statCount_var27, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Basic, statCount_var27);

					for (int i = 0; i < statCount_var27 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseBasicStat_v2497(handler, blockOutput.LimitBreak.Stats.Basic[i]);
					}

					Read<int>("statCount", handler, statCount_var27, "\t\t\t\t");

					ResizeVector(handler, blockOutput.LimitBreak.Stats.Special, statCount_var27);

					for (int i = 0; i < statCount_var27 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						ParseSpecialStat_v2497(handler, blockOutput.LimitBreak.Stats.Special[i]);
					}
				}
			}

			unsigned char extraDataType_var28 = 0;

			extraDataType_var28 = handler.GetItemExtraDataType(itemId_param0);

			ValidateValues(stream, "extraDataType", "\t\t", extraDataType_var28, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (extraDataType_var28 == 1)
			{

				{
					long long unknown_var29 = 0;
					Read<long long>("unknown", handler, unknown_var29, "\t\t\t\t");
					Read<std::wstring>("fileName", handler, blockOutput.Template.FileName, "\t\t\t\t");
					Read<std::wstring>("name", handler, blockOutput.Template.Name, "\t\t\t\t");

					unsigned char unknown_var32 = 0;
					Read<unsigned char>("unknown", handler, unknown_var32, "\t\t\t\t");

					int unknown_var33 = 0;
					Read<int>("unknown", handler, unknown_var33, "\t\t\t\t");
					Read<long long>("accountId", handler, blockOutput.Template.AccountId, "\t\t\t\t");
					Read<long long>("characterId", handler, blockOutput.Template.CharacterId, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Template.Author, "\t\t\t\t");
					Read<long long>("creationTime", handler, blockOutput.Template.CreationTime, "\t\t\t\t");
					Read<std::wstring>("url", handler, blockOutput.Template.Url, "\t\t\t\t");

					unsigned char unknown_var39 = 0;
					Read<unsigned char>("unknown", handler, unknown_var39, "\t\t\t\t");
				}

				{

					long long unknown_var40 = 0;
					Read<long long>("unknown", handler, unknown_var40, "\t\t\t\t");

					int unknown_var41 = 0;
					Read<int>("unknown", handler, unknown_var41, "\t\t\t\t");

					int unknown_var42 = 0;
					Read<int>("unknown", handler, unknown_var42, "\t\t\t\t");

					int unknown_var43 = 0;
					Read<int>("unknown", handler, unknown_var43, "\t\t\t\t");

					long long unknown_var44 = 0;
					Read<long long>("unknown", handler, unknown_var44, "\t\t\t\t");

					int unknown_var45 = 0;
					Read<int>("unknown", handler, unknown_var45, "\t\t\t\t");

					long long unknown_var46 = 0;
					Read<long long>("unknown", handler, unknown_var46, "\t\t\t\t");

					long long unknown_var47 = 0;
					Read<long long>("unknown", handler, unknown_var47, "\t\t\t\t");

					std::wstring unknown_var48;
					Read<std::wstring>("unknown", handler, unknown_var48, "\t\t\t\t");
				}
			}

			if (extraDataType_var28 == 2)
			{

				{
					Read<std::wstring>("name", handler, blockOutput.Pet.Name, "\t\t\t\t");
					Read<long long>("exp", handler, blockOutput.Pet.Exp, "\t\t\t\t");
					Read<int>("evolvePoints", handler, blockOutput.Pet.EvolvePoints, "\t\t\t\t");
					Read<int>("level", handler, blockOutput.Pet.Level, "\t\t\t\t");
					Read<bool>("hasItems", handler, blockOutput.Pet.HasItems, "\t\t\t\t");

					ValidateValues(stream, "hasItems", "\t\t\t\t", blockOutput.Pet.HasItems, (bool)0, (bool)1);
				}
			}

			if (extraDataType_var28 == 3)
			{

				{
					Read<int>("length", handler, blockOutput.Music.Length, "\t\t\t\t");
					Read<int>("instrument", handler, blockOutput.Music.Instrument, "\t\t\t\t");
					Read<std::wstring>("title", handler, blockOutput.Music.Title, "\t\t\t\t");
					Read<std::wstring>("author", handler, blockOutput.Music.Author, "\t\t\t\t");

					int unknown_var58 = 0;
					Read<int>("unknown", handler, unknown_var58, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var58, (int)1);

					Read<long long>("authorId", handler, blockOutput.Music.AuthorId, "\t\t\t\t");
					Read<bool>("isLocked", handler, blockOutput.Music.IsLocked, "\t\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t\t", blockOutput.Music.IsLocked, (bool)0, (bool)1);

					long long unknown_var61 = 0;
					Read<long long>("unknown", handler, unknown_var61, "\t\t\t\t");

					long long unknown_var62 = 0;
					Read<long long>("unknown", handler, unknown_var62, "\t\t\t\t");
				}
			}

			if (extraDataType_var28 == 4)
			{

				{
					unsigned char unknown_var63 = 0;
					Read<unsigned char>("unknown", handler, unknown_var63, "\t\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var63, (unsigned char)1);

					Read<unsigned char>("type", handler, blockOutput.Badge.Type, "\t\t\t\t");

					ValidateValues(stream, "type", "\t\t\t\t", blockOutput.Badge.Type, (unsigned char)1, (unsigned char)11);

					Read<int>("id", handler, blockOutput.Badge.BadgeId, "\t\t\t\t");

					if (blockOutput.Badge.Type == 1)
					{
						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[0], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[0], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[1], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[1], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[2], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[2], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[3], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[3], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[4], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[4], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[5], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[5], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[6], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[6], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[7], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[7], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[8], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[8], (bool)0, (bool)1);

						Read<bool>("transparency", handler, blockOutput.Badge.Transparency[9], "\t\t\t\t\t");

						ValidateValues(stream, "transparency", "\t\t\t\t\t", blockOutput.Badge.Transparency[9], (bool)0, (bool)1);
					}

					if (blockOutput.Badge.Type == 11)
					{
						Read<int>("petSkinId", handler, blockOutput.Badge.PetSkinId, "\t\t\t\t\t");
					}
				}
			}

			{
				Read<int>("transferFlags", handler, blockOutput.ItemTransfer.TransferFlags, "\t\t\t");

				bool unknown_var78 = false;
				Read<bool>("unknown", handler, unknown_var78, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var78, (bool)0, (bool)1);

				Read<int>("remainingTrades", handler, blockOutput.ItemTransfer.RemainingTrades, "\t\t\t");
				Read<int>("remainingPackages", handler, blockOutput.ItemTransfer.RemainingPackages, "\t\t\t");

				unsigned char unknown_var81 = 0;
				Read<unsigned char>("unknown", handler, unknown_var81, "\t\t\t");

				bool unknown_var82 = false;
				Read<bool>("unknown", handler, unknown_var82, "\t\t\t");

				ValidateValues(stream, "unknown", "\t\t\t", unknown_var82, (bool)0, (bool)1);

				Read<bool>("isBound", handler, blockOutput.ItemTransfer.IsBound, "\t\t\t");

				ValidateValues(stream, "isBound", "\t\t\t", blockOutput.ItemTransfer.IsBound, (bool)0, (bool)1);

				if (blockOutput.ItemTransfer.IsBound)
				{
					ParseItemBinding_v12(handler, blockOutput.ItemTransfer.Binding);
				}
			}

			{

				Read<unsigned char>("maxSlots", handler, blockOutput.ItemSocket.MaxSlots, "\t\t\t");
				Read<unsigned char>("unlockedSlots", handler, blockOutput.ItemSocket.UnlockedSlots, "\t\t\t");

				ResizeVector(handler, blockOutput.ItemSocket.Sockets, blockOutput.ItemSocket.UnlockedSlots);

				for (unsigned char i = 0; i < blockOutput.ItemSocket.UnlockedSlots && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<bool>("hasGem", handler, blockOutput.ItemSocket.Sockets[i].HasGem, "\t\t\t\t");

					ValidateValues(stream, "hasGem", "\t\t\t\t", blockOutput.ItemSocket.Sockets[i].HasGem, (bool)0, (bool)1);

					if (blockOutput.ItemSocket.Sockets[i].HasGem)
					{

						{
							Read<int>("itemId", handler, blockOutput.ItemSocket.Sockets[i].Gem.ItemId, "\t\t\t\t\t\t");
							Read<bool>("isBound", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsBound, "\t\t\t\t\t\t");

							ValidateValues(stream, "isBound", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsBound, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsBound)
							{
								ParseItemBinding_v12(handler, blockOutput.ItemSocket.Sockets[i].Gem.Binding);
							}

							Read<bool>("isLocked", handler, blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t\t", blockOutput.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

							if (blockOutput.ItemSocket.Sockets[i].Gem.IsLocked)
							{
								unsigned char unknown_var90 = 0;
								Read<unsigned char>("unknown", handler, unknown_var90, "\t\t\t\t\t\t\t");
								Read<long long>("unlockTime", handler, blockOutput.ItemSocket.Sockets[i].Gem.UnlockTime, "\t\t\t\t\t\t\t");
							}
						}
					}
				}
			}

			{
				Read<long long>("characterId", handler, blockOutput.ItemCouple.CharacterId, "\t\t\t");

				if (blockOutput.ItemCouple.CharacterId != 0)
				{
					Read<std::wstring>("name", handler, blockOutput.ItemCouple.Name, "\t\t\t\t");
					Read<bool>("isCreator", handler, blockOutput.ItemCouple.IsCreator, "\t\t\t\t");

					ValidateValues(stream, "isCreator", "\t\t\t\t", blockOutput.ItemCouple.IsCreator, (bool)0, (bool)1);
				}
			}
			ParseItemBinding_v12(handler, blockOutput.Binding);
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x21>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::StateSkillPacket>(output0);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", handler, output0.Version, "\t");

			unsigned short feature_var1 = 0;
			Read<unsigned short>("feature", handler, feature_var1, "\t");

			unsigned short locale_var2 = 0;
			Read<unsigned short>("locale", handler, locale_var2, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseVersionPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseHeartbeatPacket output0;

			Read<int>("serverTick", handler, output0.ServerTick, "\t");
			Read<int>("clientTick", handler, output0.ClientTick, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseHeartbeatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x2>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::HandshakePacket output0;

			Read<unsigned char>("function", handler, output0.Function, "\t");

			int count_var1 = 0;
			Read<int>("count", handler, count_var1, "\t");

			ResizeVector(handler, output0.Data, count_var1);

			for (int i = 0; i < count_var1 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				Read<std::wstring>("unknown", handler, output0.Data[i].String, "\t\t");

				long long unknown_var3 = 0;
				Read<long long>("unknown", handler, unknown_var3, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::HandshakePacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::LogInPacket>(output0);

					return;
				}
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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::LogInAuthTokenPacket>(output1);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseKeyPacket output0;

			Read<long long>("accountId", handler, output0.AccountId, "\t");

			if (output0.AccountId != 0)
			{
				Read<int>("tokenA", handler, output0.TokenA, "\t\t");
				Read<int>("tokenB", handler, output0.TokenB, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh, "\t\t");
				Read<unsigned long long>("machineLow", handler, output0.MachineLow, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseKeyPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::RequestQuitPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1);

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::RequestQuitPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
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

					for (unsigned char i = 0; i < count_var21 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						Read<long long>("skillAttack", handler, projectile_array0.SkillAttack, "\t\t\t\t");
						Read<int>("targetId", handler, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var26 = false;
						Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var26 && !handler.PacketStream.HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							Read<long long>("skillAttack", handler, nextTarget_array1.SkillAttack, "\t\t\t\t\t");
							Read<int>("targetId", handler, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var30 = 0;
							Read<unsigned char>("unknown", handler, unknown_var30, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
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

					for (unsigned char i = 0; i < count_var37 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						Read<int>("entityId", handler, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var40 = 0;
						Read<unsigned char>("unknown", handler, unknown_var40, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var40, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
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

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Client::NpcTalkClosePacket output0;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkClosePacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Client::NpcTalkBeginPacket output1;

				Read<int>("actorId", handler, output1.ActorId, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkBeginPacket>(output1);

					return;
				}
			}

			if (mode_var0 == 2)
			{
				Client::NpcTalkContinuePacket output2;

				Read<int>("index", handler, output2.Index, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkContinuePacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::NpcTalkEnchantUnknownPacket output3;

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantUnknownPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Client::NpcTalkEnchantPacket output4;

				Read<int>("npcId", handler, output4.NpcId, "\t\t");
				Read<int>("scriptId", handler, output4.ScriptId, "\t\t");
				Read<short>("eventType", handler, output4.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output4.EventType, (short)1, (short)202, (short)2, (short)3);

				if (output4.EventType == 1)
				{
					Read<long long>("itemInstanceId", handler, output4.ItemInstanceId, "\t\t\t");
				}

				if (output4.EventType == 202)
				{
					short unknown_var8 = 0;
					Read<short>("unknown", handler, unknown_var8, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				Client::NpcTalkNextQuestPacket output5;

				Read<int>("questId", handler, output5.QuestId, "\t\t");
				Read<short>("eventType", handler, output5.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output5.EventType, (short)0, (short)2);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkNextQuestPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 8)
			{
				Client::NpcTalkAllianceQuestAcceptPacket output6;

				Read<int>("index", handler, output6.Index, "\t\t");
				Read<short>("eventType", handler, output6.EventType, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", output6.EventType, (short)0, (short)2);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(output6);

					return;
				}
			}

			if (mode_var0 == 9)
			{
				Client::NpcTalkAllianceQuestTalkPacket output7;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(output7);

					return;
				}
			}

			if (mode_var0 == 11)
			{
				Client::NpcTalkCinematicPacket output8;

				Read<int>("actorId", handler, output8.ActorId, "\t\t");
				Read<int>("index", handler, output8.Index, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkCinematicPacket>(output8);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::SystemInfoPacket output0;

			Read<std::wstring>("info", handler, output0.Info, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::SystemInfoPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::Reconnect7Packet output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::Reconnect7Packet>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");

				if (output0.SkillId == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (output0.SkillId != 0)
				{
					Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t\t");
					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");
					Read<Vector3Short>("position", handler, output0.Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					int serverTick_var11 = 0;
					Read<int>("serverTick", handler, serverTick_var11, "\t\t\t");

					unsigned char count_var12 = 0;
					Read<unsigned char>("count", handler, count_var12, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var12);

					for (unsigned char i = 0; i < count_var12 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long unknown_var13 = 0;
						Read<long long>("unknown", handler, unknown_var13, "\t\t\t\t");
						Read<long long>("skillAttack", handler, output0.Hits[i].SkillAttack, "\t\t\t\t");
						Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t\t");
						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				Read<long long>("skillSn", handler, output1.SkillSn, "\t\t");
				Read<long long>("skillAttack", handler, output1.SkillAttack, "\t\t");
				Read<int>("casterId", handler, output1.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output1.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output1.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output1.Position, "\t\t");
				Read<Vector3Short>("direction", handler, output1.Direction, "\t\t");

				unsigned char count_var26 = 0;
				Read<unsigned char>("count", handler, count_var26, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var26);

				for (unsigned char i = 0; i < count_var26 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output1.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var28 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var28, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var28);

					for (unsigned char j = 0; j < damageCount_var28 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output1.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output1.DamagedTargets[i].Damages[j].HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				Read<int>("casterId", handler, output2.CasterId, "\t\t");
				Read<int>("targetId", handler, output2.TargetId, "\t\t");
				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");
				Read<unsigned char>("hitType", handler, output2.HitType, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", output2.HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<int>("damage", handler, output2.Damage, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				Read<int>("casterId", handler, output3.CasterId, "\t\t");
				Read<int>("targetId", handler, output3.TargetId, "\t\t");
				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn, "\t\t");
				Read<int>("casterId", handler, output4.CasterId, "\t\t");
				Read<int>("regionSkillObjectId", handler, output4.RegionSkillObjectId, "\t\t");
				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var47 = 0;
				Read<unsigned char>("count", handler, count_var47, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var47);

				for (unsigned char i = 0; i < count_var47 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output4.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var49 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var49, "\t\t\t");
					Read<Vector3Short>("position", handler, output4.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var49);

					for (unsigned char j = 0; j < damageCount_var49 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output4.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output4.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<unsigned int>("skillId", handler, output5.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output5.SkillLevel, "\t\t");

				unsigned char count_var57 = 0;
				Read<unsigned char>("count", handler, count_var57, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var57);

				for (unsigned char i = 0; i < count_var57 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output5.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var59 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var59, "\t\t\t");
					Read<Vector3Short>("position", handler, output5.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var59);

					for (unsigned char j = 0; j < damageCount_var59 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output5.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output5.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var64 = 0;
				Read<int>("unknown", handler, unknown_var64, "\t\t");

				int count_var65 = 0;
				Read<int>("count", handler, count_var65, "\t\t");

				for (int i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var66 = 0;
					Read<int>("unknown", handler, unknown_var66, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var67 = 0;
				Read<long long>("skillSn", handler, skillSn_var67, "\t\t");

				bool hasTarget_var68 = false;
				Read<bool>("hasTarget", handler, hasTarget_var68, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var68, (bool)0, (bool)1);

				if (hasTarget_var68)
				{
					unsigned int skillId_var69 = 0;
					Read<unsigned int>("skillId", handler, skillId_var69, "\t\t\t");

					unsigned short skillLevel_var70 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var70, "\t\t\t");

					int unknown_var71 = 0;
					Read<int>("unknown", handler, unknown_var71, "\t\t\t");

					int npcId_var72 = 0;
					Read<int>("npcId", handler, npcId_var72, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddNpc output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");
			Read<int>("npcId", handler, output0.NpcId, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("rotation", handler, output0.Rotation, "\t");

			bool isBoss_var4 = false;

			isBoss_var4 = handler.IsNpcBoss(output0.NpcId);

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
				Read<unsigned int>("moveSpeedMax", handler, output0.MoveSpeed.Max, "\t\t");
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base, "\t\t");
				Read<unsigned int>("moveSpeedBase", handler, output0.MoveSpeed.Base, "\t\t");
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current, "\t\t");
				Read<unsigned int>("moveSpeedCurrent", handler, output0.MoveSpeed.Current, "\t\t");
			}
			Read<bool>("isDead", handler, output0.IsDead, "\t");

			ValidateValues(stream, "isDead", "\t", output0.IsDead, (bool)0, (bool)1);

			unsigned short effectCount_var14 = 0;
			Read<unsigned short>("effectCount", handler, effectCount_var14, "\t");

			ResizeVector(handler, output0.AdditionalEffects, effectCount_var14);

			for (unsigned short i = 0; i < effectCount_var14 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				Read<int>("ownerId", handler, output0.AdditionalEffects[i].OwnerId, "\t\t");

				int buffInstanceId_var16 = 0;
				Read<int>("buffInstanceId", handler, buffInstanceId_var16, "\t\t");
				Read<int>("casterId", handler, output0.AdditionalEffects[i].CasterId, "\t\t");
				Read<int>("startTick", handler, output0.AdditionalEffects[i].StartTick, "\t\t");
				Read<int>("endTick", handler, output0.AdditionalEffects[i].EndTick, "\t\t");
				Read<int>("effectId", handler, output0.AdditionalEffects[i].EffectId, "\t\t");
				Read<short>("effectLevel", handler, output0.AdditionalEffects[i].EffectLevel, "\t\t");
				Read<int>("stacks", handler, output0.AdditionalEffects[i].Stacks, "\t\t");
				Read<bool>("enabled", handler, output0.AdditionalEffects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.AdditionalEffects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.AdditionalEffects[i].ShieldHealth, "\t\t");
			}

			long long petItemInstanceId_var25 = 0;
			Read<long long>("petItemInstanceId", handler, petItemInstanceId_var25, "\t");

			unsigned char unknown_var26 = 0;
			Read<unsigned char>("unknown", handler, unknown_var26, "\t");
			Read<short>("level", handler, output0.Level, "\t");

			short unknownLevelPad_var28 = 0;
			Read<short>("unknownLevelPad", handler, unknownLevelPad_var28, "\t");

			ValidateValues(stream, "unknownLevelPad", "\t", unknownLevelPad_var28, (short)0);

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29, "\t");

			if (isBoss_var4)
			{
				Read<std::wstring>("spawnEffect", handler, output0.SpawnEffect, "\t\t");

				int skillCount_var31 = 0;
				Read<int>("skillCount", handler, skillCount_var31, "\t\t");

				ResizeVector(handler, output0.Skills, skillCount_var31);

				for (int i = 0; i < skillCount_var31 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("skillId", handler, output0.Skills[i].SkillId, "\t\t\t");
					Read<short>("skillLevel", handler, output0.Skills[i].SkillLevel, "\t\t\t");
				}

				int unknown_var34 = 0;
				Read<int>("unknown", handler, unknown_var34, "\t\t");
			}

			bool hasHiddenHp_var35 = false;

			hasHiddenHp_var35 = handler.NpcHasHiddenHp(output0.NpcId);

			ValidateValues(stream, "hasHiddenHp", "\t", hasHiddenHp_var35, (bool)0, (bool)1);

			if (hasHiddenHp_var35)
			{
				Read<long long>("hiddenHpAdd", handler, output0.HiddenHpAdd, "\t\t");
			}

			bool unknownBool_var37 = false;
			Read<bool>("unknownBool", handler, unknownBool_var37, "\t");

			ValidateValues(stream, "unknownBool", "\t", unknownBool_var37, (bool)0, (bool)1);

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddNpc>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x16>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::RequestFieldEnterPacket>(output0);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			Read<int>("targetId", handler, output0.TargetId, "\t");
			Read<int>("instanceId", handler, output0.InstanceId, "\t");
			Read<int>("sourceId", handler, output0.SourceId, "\t");

			if (output0.InstanceId != 0)
			{
				if (output0.Mode == 0)
				{
					Read<int>("startTime", handler, output0.StartTime, "\t\t\t");
					Read<int>("endTime", handler, output0.EndTime, "\t\t\t");
					Read<int>("effectId", handler, output0.EffectId, "\t\t\t");
					Read<short>("effectLevel", handler, output0.EffectLevel, "\t\t\t");
					Read<int>("stacks", handler, output0.Stacks, "\t\t\t");
					Read<bool>("hasShield", handler, output0.UpdateShield, "\t\t\t");

					ValidateValues(stream, "hasShield", "\t\t\t", output0.UpdateShield, (bool)0, (bool)1);

					Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t");
				}

				if (output0.Mode == 2)
				{
					int flags_var11 = 0;
					Read<int>("flags", handler, flags_var11, "\t\t\t");

					output0.UpdateEffect = GetBit(flags_var11, 0);
					output0.UpdateShield = GetBit(flags_var11, 1);

					if (GetBit(flags_var11, 0) == 1)
					{
						Read<int>("startTime", handler, output0.StartTime, "\t\t\t\t");
						Read<int>("endTime", handler, output0.EndTime, "\t\t\t\t");
						Read<int>("effectId", handler, output0.EffectId, "\t\t\t\t");
						Read<short>("effectLevel", handler, output0.EffectLevel, "\t\t\t\t");
						Read<int>("stacks", handler, output0.Stacks, "\t\t\t\t");
						Read<bool>("enabled", handler, output0.Enabled, "\t\t\t\t");

						ValidateValues(stream, "enabled", "\t\t\t\t", output0.Enabled, (bool)0, (bool)1);
					}

					if (GetBit(flags_var11, 1) == 1)
					{
						Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemovePlayerPacket output0;

			Read<int>("characterId", handler, output0.CharacterId, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemovePlayerPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::UserChatPacket output0;

			Read<long long>("accountId", handler, output0.AccountId, "\t");
			Read<long long>("characterId", handler, output0.CharacterId, "\t");
			Read<std::wstring>("characterName", handler, output0.CharacterName, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");
			Read<std::wstring>("message", handler, output0.Message, "\t");
			Read<int>("type", handler, output0.Type, "\t");

			ValidateValues(stream, "type", "\t", output0.Type, (int)8, (int)0, (int)3, (int)4, (int)5, (int)6, (int)7, (int)9, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)18, (int)19, (int)20, (int)23);

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");
			Read<int>("channelId", handler, output0.ChannelId, "\t");

			if (output0.Type == 3)
			{
				std::wstring unknown_var8;
				Read<std::wstring>("unknown", handler, unknown_var8, "\t\t");
			}

			if (output0.Type == 16)
			{
				Read<int>("superChatId", handler, output0.SuperChatId, "\t\t");
			}

			if (output0.Type == 20)
			{
				Read<long long>("clubId", handler, output0.ClubId, "\t\t");
			}

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::UserChatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");

			bool hasUid_var3 = false;
			Read<bool>("hasUid", handler, hasUid_var3, "\t");

			ValidateValues(stream, "hasUid", "\t", hasUid_var3, (bool)0, (bool)1);

			if (hasUid_var3)
			{
				long long uid_var4 = 0;
				Read<long long>("uid", handler, uid_var4, "\t\t");
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

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemoveItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemoveNpc output0;

			Read<int>("actorId", handler, output0.ActorId, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveNpc>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::TrophyStartPacket output0;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyStartPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::TrophyContentPacket output1;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Trophies, count_var1);

				for (int i = 0; i < count_var1 && !handler.PacketStream.HasRecentlyFailed; ++i)
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

					for (int j = 0; j < timestampsCount_var10 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<int>("index", handler, output1.Trophies[i].Timestamps[j].Index, "\t\t\t\t");
						Read<long long>("timestamp", handler, output1.Trophies[i].Timestamps[j].Time, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyContentPacket>(output1);

					return;
				}
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

				for (int i = 0; i < timestampsCount_var20 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("index", handler, output2.Timestamps[i].Index, "\t\t\t");
					Read<long long>("timestamp", handler, output2.Timestamps[i].Time, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyUpdatePacket>(output2);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");

			long long uid_var3 = 0;
			Read<long long>("uid", handler, uid_var3, "\t");
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

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");

				if (output0.SkillId == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (output0.SkillId != 0)
				{
					Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t\t");
					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");
					Read<Vector3Short>("position", handler, output0.Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var11 = 0;
					Read<unsigned char>("count", handler, count_var11, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var11);

					for (unsigned char i = 0; i < count_var11 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long hitId_var12 = 0;
						Read<long long>("hitId", handler, hitId_var12, "\t\t\t\t");

						int attackCount_var13 = 0;
						Read<int>("attackCount", handler, attackCount_var13, "\t\t\t\t");

						int casterId_var14 = 0;
						Read<int>("casterId", handler, casterId_var14, "\t\t\t\t");
						Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t\t");
						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				Read<long long>("skillSn", handler, output1.SkillSn, "\t\t");

				long long hitId_var18 = 0;
				Read<long long>("hitId", handler, hitId_var18, "\t\t");
				Read<int>("casterId", handler, output1.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output1.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output1.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output1.Position, "\t\t");
				Read<Vector3Short>("direction", handler, output1.Direction, "\t\t");

				unsigned char count_var26 = 0;
				Read<unsigned char>("count", handler, count_var26, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var26);

				for (unsigned char i = 0; i < count_var26 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output1.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var28 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var28, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var28);

					for (unsigned char j = 0; j < damageCount_var28 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output1.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output1.DamagedTargets[i].Damages[j].HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				Read<int>("casterId", handler, output2.CasterId, "\t\t");
				Read<int>("targetId", handler, output2.TargetId, "\t\t");
				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");
				Read<unsigned char>("hitType", handler, output2.HitType, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", output2.HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<int>("damage", handler, output2.Damage, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				Read<int>("casterId", handler, output3.CasterId, "\t\t");
				Read<int>("targetId", handler, output3.TargetId, "\t\t");
				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn, "\t\t");
				Read<int>("casterId", handler, output4.CasterId, "\t\t");
				Read<int>("regionSkillObjectId", handler, output4.RegionSkillObjectId, "\t\t");
				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var47 = 0;
				Read<unsigned char>("count", handler, count_var47, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var47);

				for (unsigned char i = 0; i < count_var47 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output4.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var49 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var49, "\t\t\t");
					Read<Vector3Short>("position", handler, output4.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var49);

					for (unsigned char j = 0; j < damageCount_var49 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output4.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output4.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<unsigned int>("skillId", handler, output5.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output5.SkillLevel, "\t\t");

				unsigned char count_var57 = 0;
				Read<unsigned char>("count", handler, count_var57, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var57);

				for (unsigned char i = 0; i < count_var57 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output5.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var59 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var59, "\t\t\t");
					Read<Vector3Short>("position", handler, output5.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var59);

					for (unsigned char j = 0; j < damageCount_var59 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output5.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output5.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var64 = 0;
				Read<int>("unknown", handler, unknown_var64, "\t\t");

				int count_var65 = 0;
				Read<int>("count", handler, count_var65, "\t\t");

				for (int i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var66 = 0;
					Read<int>("unknown", handler, unknown_var66, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var67 = 0;
				Read<long long>("skillSn", handler, skillSn_var67, "\t\t");

				bool hasTarget_var68 = false;
				Read<bool>("hasTarget", handler, hasTarget_var68, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var68, (bool)0, (bool)1);

				if (hasTarget_var68)
				{
					unsigned int skillId_var69 = 0;
					Read<unsigned int>("skillId", handler, skillId_var69, "\t\t\t");

					unsigned short skillLevel_var70 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var70, "\t\t\t");

					int unknown_var71 = 0;
					Read<int>("unknown", handler, unknown_var71, "\t\t\t");

					int npcId_var72 = 0;
					Read<int>("npcId", handler, npcId_var72, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::BuffPacket output0;

			Read<unsigned char>("mode", handler, output0.Mode, "\t");

			ValidateValues(stream, "mode", "\t", output0.Mode, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			int targetActor_var1 = 0;
			Read<int>("targetActor", handler, targetActor_var1, "\t");
			Read<int>("instanceId", handler, output0.InstanceId, "\t");

			int sourceActor_var3 = 0;
			Read<int>("sourceActor", handler, sourceActor_var3, "\t");

			if (output0.Mode == 0)
			{
				Read<int>("startTime", handler, output0.StartTime, "\t\t");
				Read<int>("endTime", handler, output0.EndTime, "\t\t");
				Read<int>("effectId", handler, output0.EffectId, "\t\t");
				Read<short>("effectLevel", handler, output0.EffectLevel, "\t\t");
				Read<int>("stacks", handler, output0.Stacks, "\t\t");
				Read<bool>("hasShield", handler, output0.UpdateShield, "\t\t");

				ValidateValues(stream, "hasShield", "\t\t", output0.UpdateShield, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t");
			}

			if (output0.Mode == 2)
			{
				int flags_var11 = 0;
				Read<int>("flags", handler, flags_var11, "\t\t");

				output0.UpdateEffect = GetBit(flags_var11, 0);
				output0.UpdateShield = GetBit(flags_var11, 1);

				if (GetBit(flags_var11, 0) == 1)
				{
					Read<int>("startTime", handler, output0.StartTime, "\t\t\t");
					Read<int>("endTime", handler, output0.EndTime, "\t\t\t");
					Read<int>("effectId", handler, output0.EffectId, "\t\t\t");
					Read<short>("effectLevel", handler, output0.EffectLevel, "\t\t\t");
					Read<int>("stacks", handler, output0.Stacks, "\t\t\t");
					Read<bool>("enabled", handler, output0.Enabled, "\t\t\t");

					ValidateValues(stream, "enabled", "\t\t\t", output0.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var11, 1) == 1)
				{
					Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t");
				}
			}

			if (output0.InstanceId == 0)
			{
				int unknown_var19 = 0;
				Read<int>("unknown", handler, unknown_var19, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			Read<int>("objectId", handler, output0.ObjectId, "\t");
			Read<int>("itemId", handler, output0.ItemId, "\t");
			Read<int>("amount", handler, output0.Amount, "\t");

			long long uid_var3 = 0;
			Read<long long>("uid", handler, uid_var3, "\t");
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

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

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

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
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

					for (unsigned char i = 0; i < count_var22 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						int attackCount_var24 = 0;
						Read<int>("attackCount", handler, attackCount_var24, "\t\t\t\t");

						int sourceId_var25 = 0;
						Read<int>("sourceId", handler, sourceId_var25, "\t\t\t\t");
						Read<int>("targetId", handler, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var28 = false;
						Read<bool>("moreTargets", handler, moreTargets_var28, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var28 && !handler.PacketStream.HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							int attackCount_var29 = 0;
							Read<int>("attackCount", handler, attackCount_var29, "\t\t\t\t\t");

							int sourceId_var30 = 0;
							Read<int>("sourceId", handler, sourceId_var30, "\t\t\t\t\t");
							Read<int>("targetId", handler, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var33 = 0;
							Read<unsigned char>("unknown", handler, unknown_var33, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var28, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
				}

				if (damageMode_var17 == 1)
				{
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", handler, output2.SkillSn, "\t\t\t");

					int attackCounter_var35 = 0;
					Read<int>("attackCounter", handler, attackCounter_var35, "\t\t\t");

					int sourceId_var36 = 0;
					Read<int>("sourceId", handler, sourceId_var36, "\t\t\t");
					Read<Vector3S>("position", handler, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", handler, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", handler, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint, "\t\t\t");

					unsigned char count_var41 = 0;
					Read<unsigned char>("count", handler, count_var41, "\t\t\t");

					int unknown_var42 = 0;
					Read<int>("unknown", handler, unknown_var42, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var42, (int)0);

					ResizeVector(handler, output2.Hits, count_var41);

					for (unsigned char i = 0; i < count_var41 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						Read<int>("entityId", handler, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var44 = 0;
						Read<unsigned char>("unknown", handler, unknown_var44, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var44, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
				}

				if (damageMode_var17 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", handler, output3.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output3.AttackPoint, "\t\t\t");

					int unknown_var47 = 0;
					Read<int>("unknown", handler, unknown_var47, "\t\t\t");
					Read<int>("attackCounter", handler, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", handler, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output3.Rotation, "\t\t\t");

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
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

				Vector3S unknown_var56;
				Read<Vector3S>("unknown", handler, unknown_var56, "\t\t");
				Read<Vector3S>("rotation", handler, output4.Rotation, "\t\t");

				Vector3S unknown_var58;
				Read<Vector3S>("unknown", handler, unknown_var58, "\t\t");

				bool unknown_var59 = false;
				Read<bool>("unknown", handler, unknown_var59, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var59, (bool)0, (bool)1);

				int unknown_var60 = 0;
				Read<int>("unknown", handler, unknown_var60, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var60, (int)0);

				unsigned char unknown_var61 = 0;
				Read<unsigned char>("unknown", handler, unknown_var61, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var61, (unsigned char)0);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", handler, output6.SkillSn, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				Read<long long>("skillSn", handler, output0.SkillSn, "\t\t");
				Read<int>("casterId", handler, output0.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output0.SkillId, "\t\t");

				if (output0.SkillId == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (output0.SkillId != 0)
				{
					Read<unsigned short>("skillLevel", handler, output0.SkillLevel, "\t\t\t");
					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");
					Read<Vector3Short>("position", handler, output0.Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var11 = 0;
					Read<unsigned char>("count", handler, count_var11, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var11);

					for (unsigned char i = 0; i < count_var11 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long hitId_var12 = 0;
						Read<long long>("hitId", handler, hitId_var12, "\t\t\t\t");

						int attackCount_var13 = 0;
						Read<int>("attackCount", handler, attackCount_var13, "\t\t\t\t");

						int casterId_var14 = 0;
						Read<int>("casterId", handler, casterId_var14, "\t\t\t\t");
						Read<int>("targetId", handler, output0.Hits[i].TargetId, "\t\t\t\t");
						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				Read<long long>("skillSn", handler, output1.SkillSn, "\t\t");

				long long hitId_var18 = 0;
				Read<long long>("hitId", handler, hitId_var18, "\t\t");
				Read<int>("casterId", handler, output1.CasterId, "\t\t");
				Read<unsigned int>("skillId", handler, output1.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output1.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");
				Read<Vector3Short>("position", handler, output1.Position, "\t\t");
				Read<Vector3Short>("direction", handler, output1.Direction, "\t\t");

				unsigned char count_var26 = 0;
				Read<unsigned char>("count", handler, count_var26, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var26);

				for (unsigned char i = 0; i < count_var26 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output1.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var28 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var28, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var28);

					for (unsigned char j = 0; j < damageCount_var28 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output1.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output1.DamagedTargets[i].Damages[j].HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				Read<int>("casterId", handler, output2.CasterId, "\t\t");
				Read<int>("targetId", handler, output2.TargetId, "\t\t");
				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");
				Read<unsigned char>("hitType", handler, output2.HitType, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", output2.HitType, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				Read<long long>("damage", handler, output2.Damage, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				Read<int>("casterId", handler, output3.CasterId, "\t\t");
				Read<int>("targetId", handler, output3.TargetId, "\t\t");
				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				Read<long long>("skillSn", handler, output4.SkillSn, "\t\t");
				Read<int>("casterId", handler, output4.CasterId, "\t\t");
				Read<int>("regionSkillObjectId", handler, output4.RegionSkillObjectId, "\t\t");
				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var47 = 0;
				Read<unsigned char>("count", handler, count_var47, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var47);

				for (unsigned char i = 0; i < count_var47 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output4.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var49 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var49, "\t\t\t");
					Read<Vector3Short>("position", handler, output4.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var49);

					for (unsigned char j = 0; j < damageCount_var49 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output4.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output4.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				Read<long long>("skillSn", handler, output5.SkillSn, "\t\t");
				Read<unsigned int>("skillId", handler, output5.SkillId, "\t\t");
				Read<unsigned short>("skillLevel", handler, output5.SkillLevel, "\t\t");

				unsigned char count_var57 = 0;
				Read<unsigned char>("count", handler, count_var57, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var57);

				for (unsigned char i = 0; i < count_var57 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("targetId", handler, output5.DamagedTargets[i].TargetId, "\t\t\t");

					unsigned char damageCount_var59 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var59, "\t\t\t");
					Read<Vector3Short>("position", handler, output5.DamagedTargets[i].Position, "\t\t\t");
					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var59);

					for (unsigned char j = 0; j < damageCount_var59 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<unsigned char>("hitType", handler, output5.DamagedTargets[i].Damages[j].HitType, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", output5.DamagedTargets[i].Damages[j].HitType, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var64 = 0;
				Read<int>("unknown", handler, unknown_var64, "\t\t");

				int count_var65 = 0;
				Read<int>("count", handler, count_var65, "\t\t");

				for (int i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var66 = 0;
					Read<int>("unknown", handler, unknown_var66, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var67 = 0;
				Read<long long>("skillSn", handler, skillSn_var67, "\t\t");

				bool hasTarget_var68 = false;
				Read<bool>("hasTarget", handler, hasTarget_var68, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var68, (bool)0, (bool)1);

				if (hasTarget_var68)
				{
					unsigned int skillId_var69 = 0;
					Read<unsigned int>("skillId", handler, skillId_var69, "\t\t\t");

					unsigned short skillLevel_var70 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var70, "\t\t\t");

					int unknown_var71 = 0;
					Read<int>("unknown", handler, unknown_var71, "\t\t\t");

					int npcId_var72 = 0;
					Read<int>("npcId", handler, npcId_var72, "\t\t\t");
				}
			}
		}

	}
}
