#include "SniffHandler.h"

#include <zlib.h>

#include <ParserUtils/PacketParsing.h>
#include <ArchiveParser/ArchiveParser.h>
#include <Engine/Assets/ParserUtils.h>
#include <GameData/Data/PacketCommon.h>

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

		const std::unordered_map<Enum::StatAttributeBasic, std::string> StatBasicNames = {
			{ Enum::StatAttributeBasic::Str, "Str" },
			{ Enum::StatAttributeBasic::Dex, "Dex" },
			{ Enum::StatAttributeBasic::Int, "Int" },
			{ Enum::StatAttributeBasic::Luk, "Luk" },
			{ Enum::StatAttributeBasic::Hp, "Hp" },
			{ Enum::StatAttributeBasic::HpRegen, "HpRegen" },
			{ Enum::StatAttributeBasic::HpRegenInterval, "HpRegenInterval" },
			{ Enum::StatAttributeBasic::Spirit, "Spirit" },
			{ Enum::StatAttributeBasic::SpRegen, "SpRegen" },
			{ Enum::StatAttributeBasic::SpRegenInterval, "SpRegenInterval" },
			{ Enum::StatAttributeBasic::Stamina, "Stamina" },
			{ Enum::StatAttributeBasic::StaminaRegen, "StaminaRegen" },
			{ Enum::StatAttributeBasic::StaminaRegenInterval, "StaminaRegenInterval" },
			{ Enum::StatAttributeBasic::AttackSpeed, "AttackSpeed" },
			{ Enum::StatAttributeBasic::MoveSpeed, "MoveSpeed" },
			{ Enum::StatAttributeBasic::Accuracy, "Accuracy" },
			{ Enum::StatAttributeBasic::Evasion, "Evasion" },
			{ Enum::StatAttributeBasic::CritRate, "CritRate" },
			{ Enum::StatAttributeBasic::CritDamage, "CritDamage" },
			{ Enum::StatAttributeBasic::CritEvasion, "CritEvasion" },
			{ Enum::StatAttributeBasic::Defense, "Defense" },
			{ Enum::StatAttributeBasic::PerfectGuard, "PerfectGuard" },
			{ Enum::StatAttributeBasic::JumpHeight, "JumpHeight" },
			{ Enum::StatAttributeBasic::PhysicalAtk, "PhysicalAtk" },
			{ Enum::StatAttributeBasic::MagicAtk, "MagicAtk" },
			{ Enum::StatAttributeBasic::PhysicalRes, "PhysicalRes" },
			{ Enum::StatAttributeBasic::MagicRes, "MagicRes" },
			{ Enum::StatAttributeBasic::MinWeaponAtk, "MinWeaponAtk" },
			{ Enum::StatAttributeBasic::MaxWeaponAtk, "MaxWeaponAtk" },
			{ Enum::StatAttributeBasic::MinDamage, "MinDamage" },
			{ Enum::StatAttributeBasic::MaxDamage, "MaxDamage" },
			{ Enum::StatAttributeBasic::Pierce, "Pierce" },
			{ Enum::StatAttributeBasic::MountMoveSpeed, "MountMoveSpeed" },
			{ Enum::StatAttributeBasic::BonusAtk, "BonusAtk" },
			{ Enum::StatAttributeBasic::PetBonusAtk, "PetBonusAtk" }
		};

		const std::unordered_map<Enum::StatAttributeSpecial, std::string> StatSpecialNames = {
			{ Enum::StatAttributeSpecial::ExpBonus, "ExpBonus" },
			{ Enum::StatAttributeSpecial::MesoBonus, "MesoBonus" },
			{ Enum::StatAttributeSpecial::SwimSpeed, "SwimSpeed" },
			{ Enum::StatAttributeSpecial::DashDistance, "DashDistance" },
			{ Enum::StatAttributeSpecial::TonicDropRate, "TonicDropRate" },
			{ Enum::StatAttributeSpecial::GearDropRate, "GearDropRate" },
			{ Enum::StatAttributeSpecial::TotalDamage, "TotalDamage" },
			{ Enum::StatAttributeSpecial::CriticalDamage, "CriticalDamage" },
			{ Enum::StatAttributeSpecial::Damage, "Damage" },
			{ Enum::StatAttributeSpecial::LeaderDamage, "LeaderDamage" },
			{ Enum::StatAttributeSpecial::EliteDamage, "EliteDamage" },
			{ Enum::StatAttributeSpecial::BossDamage, "BossDamage" }, /* This is actually used in conjunction with "sgi_target" in the XMLs. It's not boss damage, it's for a specified monster type. Currently ignoring it and just using it as boss damage, as nothing in the data uses it for non-boss mobs */
			{ Enum::StatAttributeSpecial::HpOnKill, "HpOnKill" },
			{ Enum::StatAttributeSpecial::SpiritOnKill, "SpiritOnKill" },
			{ Enum::StatAttributeSpecial::StaminaOnKill, "StaminaOnKill" },
			{ Enum::StatAttributeSpecial::Heal, "Heal" },
			{ Enum::StatAttributeSpecial::AllyRecovery, "AllyRecovery" },
			{ Enum::StatAttributeSpecial::IceDamage, "IceDamage" },
			{ Enum::StatAttributeSpecial::FireDamage, "FireDamage" },
			{ Enum::StatAttributeSpecial::DarkDamage, "DarkDamage" },
			{ Enum::StatAttributeSpecial::HolyDamage, "HolyDamage" },
			{ Enum::StatAttributeSpecial::PoisonDamage, "PoisonDamage" },
			{ Enum::StatAttributeSpecial::ElectricDamage, "ElectricDamage" },
			{ Enum::StatAttributeSpecial::MeleeDamage, "MeleeDamage" },
			{ Enum::StatAttributeSpecial::RangedDamage, "RangedDamage" },
			{ Enum::StatAttributeSpecial::PhysicalPiercing, "PhysicalPiercing" },
			{ Enum::StatAttributeSpecial::MagicPiercing, "MagicPiercing" },
			{ Enum::StatAttributeSpecial::IceDamageReduce, "IceDamageReduce" },
			{ Enum::StatAttributeSpecial::FireDamageReduce, "FireDamageReduce" },
			{ Enum::StatAttributeSpecial::DarkDamageReduce, "DarkDamageReduce" },
			{ Enum::StatAttributeSpecial::HolyDamageReduce, "HolyDamageReduce" },
			{ Enum::StatAttributeSpecial::PoisonDamageReduce, "PoisonDamageReduce" },
			{ Enum::StatAttributeSpecial::ElectricDamageReduce, "ElectricDamageReduce" },
			{ Enum::StatAttributeSpecial::StunReduce, "StunReduce" },
			{ Enum::StatAttributeSpecial::CooldownReduce, "CooldownReduce" },
			{ Enum::StatAttributeSpecial::DebuffDurationReduce, "DebuffDurationReduce" },
			{ Enum::StatAttributeSpecial::MeleeDamageReduce, "MeleeDamageReduce" },
			{ Enum::StatAttributeSpecial::RangedDamageReduce, "RangedDamageReduce" },
			{ Enum::StatAttributeSpecial::KnockbackReduce, "KnockbackReduce" },
			{ Enum::StatAttributeSpecial::MeleeStun, "MeleeStun" }, /* melee chance to stun */
			{ Enum::StatAttributeSpecial::RangedStun, "RangedStun" }, /* melee chance to stun */
			{ Enum::StatAttributeSpecial::MeeleeKnockback, "MeeleeKnockback" }, /* chance of knockback after meele att */
			{ Enum::StatAttributeSpecial::RangedKnockback, "RangedKnockback" }, /* chance of knockback after ranged att */
			{ Enum::StatAttributeSpecial::MeleeImmob, "MeleeImmob" }, /* ranged chance to immob */
			{ Enum::StatAttributeSpecial::RangedImmob, "RangedImmob" }, /* ranged chance to immob */
			{ Enum::StatAttributeSpecial::MeleeAoeDamage, "MeleeAoeDamage" }, /* melee chance to do aoe damage */
			{ Enum::StatAttributeSpecial::RangedAoeDamage, "RangedAoeDamage" }, /* ranged chance to do aoe damage */
			{ Enum::StatAttributeSpecial::DropRate, "DropRate" },
			{ Enum::StatAttributeSpecial::QuestExp, "QuestExp" },
			{ Enum::StatAttributeSpecial::QuestMeso, "QuestMeso" },
			{ Enum::StatAttributeSpecial::InvokeEffect1, "InvokeEffect1" }, /* needs better name */
			{ Enum::StatAttributeSpecial::InvokeEffect2, "InvokeEffect2" }, /* needs better name */
			{ Enum::StatAttributeSpecial::InvokeEffect3, "InvokeEffect3" }, /* needs better name */
			{ Enum::StatAttributeSpecial::PvPDamage, "PvPDamage" },
			{ Enum::StatAttributeSpecial::PvPDefense, "PvPDefense" },
			{ Enum::StatAttributeSpecial::GuildExp, "GuildExp" },
			{ Enum::StatAttributeSpecial::GuildCoin, "GuildCoin" },
			{ Enum::StatAttributeSpecial::McKayXpOrb, "McKayXpOrb" }, /* mc-kay experience orb value bonus */
			{ Enum::StatAttributeSpecial::FishingExp, "FishingExp" },
			{ Enum::StatAttributeSpecial::ArcadeExp, "ArcadeExp" },

			{ Enum::StatAttributeSpecial::PerformanceExp, "PerformanceExp" },
			{ Enum::StatAttributeSpecial::BlackMarketReduce, "BlackMarketReduce" },
			{ Enum::StatAttributeSpecial::EnchantCatalystDiscount, "EnchantCatalystDiscount" },
			{ Enum::StatAttributeSpecial::MeretReviveFee, "MeretReviveFee" },
			{ Enum::StatAttributeSpecial::MiningBonus, "MiningBonus" },
			{ Enum::StatAttributeSpecial::RanchingBonus, "RanchingBonus" },
			{ Enum::StatAttributeSpecial::SmithingExp, "SmithingExp" },
			{ Enum::StatAttributeSpecial::HandicraftMastery, "HandicraftMastery" },
			{ Enum::StatAttributeSpecial::ForagingBonus, "ForagingBonus" },
			{ Enum::StatAttributeSpecial::FarmingBonus, "FarmingBonus" },
			{ Enum::StatAttributeSpecial::AlchemyMastery, "AlchemyMastery" },
			{ Enum::StatAttributeSpecial::CookingMastery, "CookingMastery" },
			{ Enum::StatAttributeSpecial::ForagingExp, "ForagingExp" },

			/* techs */
			{ Enum::StatAttributeSpecial::TECH, "TECH" }, /* level 1 skill */
			{ Enum::StatAttributeSpecial::TECH_2, "TECH_2" }, /* 2nd level 1 skill */
			{ Enum::StatAttributeSpecial::TECH_10, "TECH_10" }, /* lv 10 skill */
			{ Enum::StatAttributeSpecial::TECH_13, "TECH_13" }, /* lv 13 skill */
			{ Enum::StatAttributeSpecial::TECH_16, "TECH_16" }, /* lv 16 skill */
			{ Enum::StatAttributeSpecial::TECH_19, "TECH_19" }, /* lv 19 skill */
			{ Enum::StatAttributeSpecial::TECH_22, "TECH_22" }, /* lv 22 skill */
			{ Enum::StatAttributeSpecial::TECH_25, "TECH_25" }, /* lv 25 skill */
			{ Enum::StatAttributeSpecial::TECH_28, "TECH_28" }, /* lv 28 skill */
			{ Enum::StatAttributeSpecial::TECH_31, "TECH_31" }, /* lv 31 skill */
			{ Enum::StatAttributeSpecial::TECH_34, "TECH_34" }, /* lv 34 skill */
			{ Enum::StatAttributeSpecial::TECH_37, "TECH_37" }, /* lv 37 skill */
			{ Enum::StatAttributeSpecial::TECH_40, "TECH_40" }, /* lv 40 skill */
			{ Enum::StatAttributeSpecial::TECH_43, "TECH_43" }, /* lv 43 skill */

			{ Enum::StatAttributeSpecial::OXQuizExp, "OXQuizExp" },
			{ Enum::StatAttributeSpecial::TrapMasterExp, "TrapMasterExp" },
			{ Enum::StatAttributeSpecial::SoleSurvivorExp, "SoleSurvivorExp" },
			{ Enum::StatAttributeSpecial::CrazyRunnerExp, "CrazyRunnerExp" },
			{ Enum::StatAttributeSpecial::LudiEscapeExp, "LudiEscapeExp" },
			{ Enum::StatAttributeSpecial::SpringBeachExp, "SpringBeachExp" },
			{ Enum::StatAttributeSpecial::DanceDanceExp, "DanceDanceExp" },

			{ Enum::StatAttributeSpecial::OXMovementSpeed, "OXMovementSpeed" },
			{ Enum::StatAttributeSpecial::TrapMasterMovementSpeed, "TrapMasterMovementSpeed" },
			{ Enum::StatAttributeSpecial::SoleSurvivorMovementSpeed, "SoleSurvivorMovementSpeed" },
			{ Enum::StatAttributeSpecial::CrazyRunnerMovementSpeed, "CrazyRunnerMovementSpeed" },
			{ Enum::StatAttributeSpecial::LudiEscapeMovementSpeed, "LudiEscapeMovementSpeed" },
			{ Enum::StatAttributeSpecial::SpringBeachMovementSpeed, "SpringBeachMovementSpeed" },
			{ Enum::StatAttributeSpecial::DanceDanceStopMovementSpeed, "DanceDanceStopMovementSpeed" },

			{ Enum::StatAttributeSpecial::GenerateSpiritOrbs, "GenerateSpiritOrbs" },
			{ Enum::StatAttributeSpecial::GenerateStaminaOrbs, "GenerateStaminaOrbs" },
			{ Enum::StatAttributeSpecial::ValorTokens, "ValorTokens" },
			{ Enum::StatAttributeSpecial::PvPExp, "PvPExp" },
			{ Enum::StatAttributeSpecial::DarkDescentDamageBonus, "DarkDescentDamageBonus" },
			{ Enum::StatAttributeSpecial::DarkDescentEvasion, "DarkDescentEvasion" },
			{ Enum::StatAttributeSpecial::DarkDescentDamageReduce, "DarkDescentDamageReduce" },

			{ Enum::StatAttributeSpecial::DoubleFishingMastery, "DoubleFishingMastery" },
			{ Enum::StatAttributeSpecial::DoublePerformanceMastery, "DoublePerformanceMastery" },

			{ Enum::StatAttributeSpecial::ExploredAreasMovementSpeed, "ExploredAreasMovementSpeed" },
			{ Enum::StatAttributeSpecial::AirMountAscentSpeed, "AirMountAscentSpeed" },
			{ Enum::StatAttributeSpecial::AdditionalEffect_95000018, "AdditionalEffect_95000018" },
			{ Enum::StatAttributeSpecial::EnemyDefenseDecreaseOnHit, "EnemyDefenseDecreaseOnHit" },
			{ Enum::StatAttributeSpecial::EnemyAttackDecreaseOnHit, "EnemyAttackDecreaseOnHit" },

			{ Enum::StatAttributeSpecial::IncreaseTotalDamageIf1NearbyEnemy, "IncreaseTotalDamageIf1NearbyEnemy" }, /* Increases damage if there is an enemy within 5m */
			{ Enum::StatAttributeSpecial::IncreaseTotalDamageIf3NearbyEnemies, "IncreaseTotalDamageIf3NearbyEnemies" }, /* Increases damage if there is at least 3 enemies within 5m */
			{ Enum::StatAttributeSpecial::IncreaseTotalDamageIf80Spirit, "IncreaseTotalDamageIf80Spirit" }, /* Increase damage if you have 80 or more spirit */
			{ Enum::StatAttributeSpecial::IncreaseTotalDamageIfFullStamina, "IncreaseTotalDamageIfFullStamina" },
			{ Enum::StatAttributeSpecial::IncreaseTotalDamageIfHerbEffectActive, "IncreaseTotalDamageIfHerbEffectActive" }, /* Increase damage if you have a herb-like effect active */
			{ Enum::StatAttributeSpecial::IncreaseTotalDamageToWorldBoss, "IncreaseTotalDamageToWorldBoss" },

			{ Enum::StatAttributeSpecial::Effect95000026, "Effect95000026" },
			{ Enum::StatAttributeSpecial::Effect95000027, "Effect95000027" },
			{ Enum::StatAttributeSpecial::Effect95000028, "Effect95000028" },
			{ Enum::StatAttributeSpecial::Effect95000029, "Effect95000029" },
			{ Enum::StatAttributeSpecial::StaminaRecoverySpeed, "StaminaRecoverySpeed" },
			{ Enum::StatAttributeSpecial::MaxWeaponAttack, "MaxWeaponAttack" },

			{ Enum::StatAttributeSpecial::DoubleMiningProduction, "DoubleMiningProduction" },
			{ Enum::StatAttributeSpecial::DoubleRanchingProduction, "DoubleRanchingProduction" },
			{ Enum::StatAttributeSpecial::DoubleForagingProduction, "DoubleForagingProduction" },
			{ Enum::StatAttributeSpecial::DoubleFarmingProduction, "DoubleFarmingProduction" },
			{ Enum::StatAttributeSpecial::DoubleSmithingProduction, "DoubleSmithingProduction" },
			{ Enum::StatAttributeSpecial::DoubleHandicraftProduction, "DoubleHandicraftProduction" },
			{ Enum::StatAttributeSpecial::DoubleAlchemyProduction, "DoubleAlchemyProduction" },
			{ Enum::StatAttributeSpecial::DoubleCookingProduction, "DoubleCookingProduction" },

			{ Enum::StatAttributeSpecial::DoubleMiningMastery, "DoubleMiningMastery" },
			{ Enum::StatAttributeSpecial::DoubleRanchingMastery, "DoubleRanchingMastery" },
			{ Enum::StatAttributeSpecial::DoubleForagingMastery, "DoubleForagingMastery" },
			{ Enum::StatAttributeSpecial::DoubleFarmingMastery, "DoubleFarmingMastery" },
			{ Enum::StatAttributeSpecial::DoubleSmithingMastery, "DoubleSmithingMastery" },
			{ Enum::StatAttributeSpecial::DoubleHandicraftMastery, "DoubleHandicraftMastery" },
			{ Enum::StatAttributeSpecial::DoubleAlchemyMastery, "DoubleAlchemyMastery" },
			{ Enum::StatAttributeSpecial::DoubleCookingMastery, "DoubleCookingMastery" },

			{ Enum::StatAttributeSpecial::ChaosRaidWeaponAttack, "ChaosRaidWeaponAttack" },
			{ Enum::StatAttributeSpecial::ChaosRaidAttackSpeed, "ChaosRaidAttackSpeed" },
			{ Enum::StatAttributeSpecial::ChaosRaidAccuracy, "ChaosRaidAccuracy" },
			{ Enum::StatAttributeSpecial::ChaosRaidHealth, "ChaosRaidHealth" },

			{ Enum::StatAttributeSpecial::StaminaAndSpiritFromOrbs, "StaminaAndSpiritFromOrbs" },

			{ Enum::StatAttributeSpecial::WorldBossExp, "WorldBossExp" },
			{ Enum::StatAttributeSpecial::WorldBossDropRate, "WorldBossDropRate" },
			{ Enum::StatAttributeSpecial::WorldBossDamageReduce, "WorldBossDamageReduce" },

			{ Enum::StatAttributeSpecial::Effect9500016, "Effect9500016" },
			{ Enum::StatAttributeSpecial::PetCaptureRewards, "PetCaptureRewards" },

			{ Enum::StatAttributeSpecial::MiningEfficency, "MiningEfficency" },
			{ Enum::StatAttributeSpecial::RanchingEfficiency, "RanchingEfficiency" },
			{ Enum::StatAttributeSpecial::ForagingEfficiency, "ForagingEfficiency" },
			{ Enum::StatAttributeSpecial::FarmingEfficiency, "FarmingEfficiency" },

			{ Enum::StatAttributeSpecial::ShanghaiCrazyRunnersExp, "ShanghaiCrazyRunnersExp" },
			{ Enum::StatAttributeSpecial::ShanghaiCrazyRunnersMovementSpeed, "ShanghaiCrazyRunnersMovementSpeed" },

			{ Enum::StatAttributeSpecial::HealthBasedDamageReduce, "HealthBasedDamageReduce" },
			{ Enum::StatAttributeSpecial::ReduceMesoRevivalFee, "ReduceMesoRevivalFee" },
			{ Enum::StatAttributeSpecial::ImproveRidingRunSpeed, "ImproveRidingRunSpeed" },
			{ Enum::StatAttributeSpecial::ImproveDungeonRewardMeso, "ImproveDungeonRewardMeso" },
			{ Enum::StatAttributeSpecial::ImproveShopBuyingMeso, "ImproveShopBuyingMeso" },
			{ Enum::StatAttributeSpecial::ImproveItemboxRewardMeso, "ImproveItemboxRewardMeso" },
			{ Enum::StatAttributeSpecial::ReduceRemakeOptionRee, "ReduceRemakeOptionRee" },
			{ Enum::StatAttributeSpecial::ReduceAirTaxiFee, "ReduceAirTaxiFee" },
			{ Enum::StatAttributeSpecial::ImproveSocketUnlockProbability, "ImproveSocketUnlockProbability" },
			{ Enum::StatAttributeSpecial::ReduceGemstoneUpgradeFee, "ReduceGemstoneUpgradeFee" },
			{ Enum::StatAttributeSpecial::ReducePetRemakeOptionFee, "ReducePetRemakeOptionFee" },
			{ Enum::StatAttributeSpecial::ImproveRidingSpeed, "ImproveRidingSpeed" },
			{ Enum::StatAttributeSpecial::ImproveSurvivalKill_exp, "ImproveSurvivalKill_exp" },
			{ Enum::StatAttributeSpecial::ImproveSurvivalTime_exp, "ImproveSurvivalTime_exp" },
			{ Enum::StatAttributeSpecial::OffensivePhysicalDamage, "OffensivePhysicalDamage" },
			{ Enum::StatAttributeSpecial::OffensiveMagicalDamage, "OffensiveMagicalDamage" },
			{ Enum::StatAttributeSpecial::ReduceGameitemSocketUnlockFee, "ReduceGameitemSocketUnlockFee" }
		};

		const std::unordered_map<Enum::Rarity, std::string> Rarities = {
			{ Enum::Rarity::Common, "Common" },
			{ Enum::Rarity::Rare, "Rare" },
			{ Enum::Rarity::Exceptional, "Exceptional" },
			{ Enum::Rarity::Epic, "Epic" },
			{ Enum::Rarity::Legendary, "Legendary" },
			{ Enum::Rarity::Ascendant, "Ascendant" },
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

		void Actor::AddEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect)
		{
			if (EffectIndices.contains(effect.InstanceId))
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					handler.FoundUnknownValue();

					std::cout << handler.TimeStamp << "adding " << PrintEffect{ *Field, effect, ActorId } << " on " << PrintActor{ *Field, ActorId } << " with instance id that already is in use" << std::endl;
				}

				return;
			}

			EffectIndices[effect.InstanceId] = Effects.size();
			Effects.push_back(effect);

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler.TimeStamp << "adding " << PrintEffect{ *Field, effect, ActorId } << " on " << PrintActor{ *Field, ActorId } << std::endl;
			}
		}

		void Actor::AddEffects(SniffHandler& handler, const std::vector<Maple::Game::AdditionalEffect>& effects)
		{
			for (const Maple::Game::AdditionalEffect& effect : effects)
			{
				AddEffect(handler, effect);
			}
		}

		void Actor::RemoveEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect)
		{
			const auto entry = EffectIndices.find(effect.InstanceId);

			if (entry == EffectIndices.end())
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				//if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					//handler.FoundUnknownValue();
					
					std::cout << handler.TimeStamp << "removing unregistered " << PrintEffect{ *Field, effect, ActorId } << " from " << PrintActor{ *Field, ActorId } << std::endl;
				}

				return;
			}

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler.TimeStamp << "removed " << PrintEffect{ *Field, Effects[entry->second], ActorId } << " from " << PrintActor{ *Field, ActorId } << std::endl;
			}

			size_t index = entry->second;

			EffectIndices[Effects.back().InstanceId] = index;
			EffectIndices.erase(entry);

			Effects[index] = Effects.back();
			Effects.pop_back();
		}

		void Actor::UpdateEffect(SniffHandler& handler, const Maple::Game::AdditionalEffect& effect)
		{
			const auto entry = EffectIndices.find(effect.InstanceId);

			if (entry == EffectIndices.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					handler.FoundUnknownValue();

					std::cout << handler.TimeStamp << "updating unregistered " << PrintEffect{ *Field, effect, ActorId } << " stats on " << PrintActor{ *Field, ActorId } << std::endl;
				}

				return;
			}

			Maple::Game::AdditionalEffect& oldEffect = Effects[entry->second];

			if (oldEffect.SourceId != effect.SourceId && (effect.SourceId != Enum::ActorId::Null))
			{
				std::cout << "mismatching " << PrintEffect{ *Field, oldEffect, ActorId } << " source " << PrintActor{ *Field, effect.SourceId } << std::endl;
			}

			UpdateEffect(handler, effect.InstanceId, effect.Stats, effect.Enabled);
			UpdateEffect(handler, effect.InstanceId, effect.ShieldHealth);
		}

		void Actor::UpdateEffect(SniffHandler& handler, Enum::EffectInstanceId effectHandle, const Maple::Game::EffectStats& stats, bool enabled)
		{
			const auto entry = EffectIndices.find(effectHandle);

			if (entry == EffectIndices.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					handler.FoundUnknownValue();

					Maple::Game::AdditionalEffect effect{
						.TargetId = ActorId,
						.InstanceId = effectHandle,
						.SourceId = Enum::ActorId::Null,
						.Stats = stats
					};

					std::cout << handler.TimeStamp << "updating unregistered " << PrintEffect{ *Field, effect, ActorId } << " stats on " << PrintActor{ *Field, ActorId } << std::endl;
				}

				return;
			}

			Maple::Game::AdditionalEffect& effect = Effects[entry->second];

			bool wasEnabled = effect.Enabled;
			Maple::Game::EffectStats oldStats = effect.Stats;

			effect.Stats = stats;
			effect.Enabled = enabled;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler.TimeStamp << "updated stats ";

				if (wasEnabled != enabled)
				{
					std::cout << (enabled ? "and enabled " : "and disabled ");
				}

				if (oldStats.EffectLevel != stats.EffectLevel)
				{
					unsigned short level1 = (unsigned short)oldStats.EffectLevel;
					unsigned short level2 = (unsigned short)stats.EffectLevel;

					std::cout << (level1 < level2 ? "and increased level from " : "and decreased level from ") << level1 << " to " << level2 << " ";
				}

				if (oldStats.Stacks != stats.Stacks)
				{
					std::cout << (oldStats.Stacks < stats.Stacks ? "and increased stacks from " : "and decreased stacks from ") << oldStats.Stacks << " to " << stats.Stacks << " ";
				}

				unsigned int oldDuration = oldStats.EndTime - oldStats.StartTime;
				unsigned int duration = stats.EndTime - stats.StartTime;
				int durationChange = (int)(stats.EndTime - oldStats.EndTime);
				bool hadDuration = (oldDuration & 0x80000000) == 0;
				bool hasDuration = (duration & 0x80000000) == 0;

				if (duration != 0 || oldDuration != 0)
				{
					if (hadDuration != hasDuration)
					{
						if (hadDuration)
						{
							std::cout << "and removed duration ";
						}
						else
						{
							std::cout << "and added duration lasting " << duration << " ms ";
						}
					}
					else if (hasDuration && durationChange != 0)
					{
						if (durationChange > 0)
						{
							std::cout << "and extended duration by " << durationChange << " ms ";
						}
						else
						{
							std::cout << "and decreased duration by " << durationChange << " ms ";
						}
					}
				}

				std::cout << "on " << PrintEffect{*Field, effect, ActorId} << " on " << PrintActor{*Field, ActorId} << std::endl;
			}
		}

		void Actor::UpdateEffect(SniffHandler& handler, Enum::EffectInstanceId effectHandle, long long shieldHealth)
		{
			const auto entry = EffectIndices.find(effectHandle);

			if (entry == EffectIndices.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					handler.FoundUnknownValue();

					Maple::Game::AdditionalEffect effect{
						.TargetId = ActorId,
						.InstanceId = effectHandle,
						.SourceId = Enum::ActorId::Null,
						.ShieldHealth = shieldHealth
					};

					std::cout << handler.TimeStamp << "updating unregistered " << PrintEffect{ *Field, effect, ActorId } << " shield health on " << PrintActor{ *Field, ActorId } << std::endl;
				}

				return;
			}

			Maple::Game::AdditionalEffect& effect = Effects[entry->second];

			effect.ShieldHealth = shieldHealth;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler.TimeStamp << "updated " << PrintEffect{ *Field, effect, ActorId } << " shield health on " << PrintActor{ *Field, ActorId } << std::endl;
			}
		}

		void Player::AddSkills(SniffHandler& handler, const Maple::Game::SkillTreeData& skillTree)
		{
			AddSkills(handler, Skills.Active, skillTree.Active);
			AddSkills(handler, Skills.Passive, skillTree.Passive);
			AddSkills(handler, Skills.Consumable, skillTree.Consumable);
			AddSkills(handler, Skills.Special, skillTree.Special);
		}

		void Player::AddSkills(SniffHandler& handler, SkillTreePage& tree, const Maple::Game::SkillTreePageData& skillTree)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler.TimeStamp << "adjusting skill tree of " << PrintActor{ *Actor->Field, Actor->ActorId } << std::endl;
			}

			for (const Maple::Game::SkillTreePageData::SkillEntry& entry : skillTree.Skills)
			{
				//if (!entry.Notify)
				//{
				//	continue;
				//}

				bool hasSkill = tree.Skills.contains(entry.SkillId);

				if (hasSkill && !entry.Enabled)
				{
					if constexpr (ParserUtils::Packets::PrintPacketOutput)
					{
						std::cout << "\tremoving skill " << PrintSkill{ *Actor->Field, entry.SkillId, tree.Skills[entry.SkillId] } << std::endl;
					}

					tree.Skills.erase(entry.SkillId);

					continue;
				}

				if (!entry.Enabled)
				{
					continue;
				}

				auto& skillLevel = tree.Skills[entry.SkillId];

				if (skillLevel == entry.SkillLevel)
				{
					continue;
				}

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << (hasSkill ? "\tchanging skill to " : "\tadding skill ") << PrintSkill{ *Actor->Field, entry.SkillId, entry.SkillLevel };
					
					if (hasSkill)
					{
						std::cout << " from Lv" << (unsigned short)skillLevel;
					}

					std::cout << std::endl;
				}

				skillLevel = entry.SkillLevel;
			}
		}

		Actor* FieldState::GetActor(Enum::ActorId actor)
		{
			auto entry = Actors.find(actor);

			return entry != Actors.end() ? &entry->second : nullptr;
		}

		const Actor* FieldState::GetActor(Enum::ActorId actor) const
		{
			auto entry = Actors.find(actor);

			return entry != Actors.end() ? &entry->second : nullptr;
		}

		Pet* FieldState::GetPet(Enum::ActorId actor)
		{
			auto entry = Pets.find(actor);

			return entry != Pets.end() ? &entry->second : nullptr;
		}

		const Pet* FieldState::GetPet(Enum::ActorId actor) const
		{
			auto entry = Pets.find(actor);

			return entry != Pets.end() ? &entry->second : nullptr;
		}

		Npc* FieldState::GetNpc(Enum::ActorId actor)
		{
			auto entry = Npcs.find(actor);

			return entry != Npcs.end() ? &entry->second : nullptr;
		}

		const Npc* FieldState::GetNpc(Enum::ActorId actor) const
		{
			auto entry = Npcs.find(actor);

			return entry != Npcs.end() ? &entry->second : nullptr;
		}

		Player* FieldState::GetPlayer(Enum::ActorId actor)
		{
			auto entry = Players.find(actor);

			return entry != Players.end() ? &entry->second : nullptr;
		}

		const Player* FieldState::GetPlayer(Enum::ActorId actor) const
		{
			auto entry = Players.find(actor);

			return entry != Players.end() ? &entry->second : nullptr;
		}

		const char* SniffHandler::Tabs() const
		{
			static const char tabs[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

			size_t tabIndex = std::max((size_t)0, std::min(sizeof(tabs) - 1, sizeof(tabs) - 1 - StackDepth));

			return tabs + tabIndex;
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

			if (!newTop.HasRecentlyFailed && oldTop.Index < oldTop.Data.size() && !oldTop.DiscardErrors)
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

			newTop.DiscardErrors = oldTop.DiscardErrors;
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

		int SniffHandler::GetItemIdFromInstance(Enum::ItemInstanceId instanceId)
		{
			const auto entry = Field.Items.find(instanceId);

			if (entry == Field.Items.end())
			{
				++DiscardedItemPackets;

				//FindTypeValueReferences<unsigned long long>(instanceId);

				return 0;
			}

			return (int)entry->second.ItemId;
		}

		unsigned int SniffHandler::GetFieldItemType(Enum::ItemEntityId instanceId)
		{
			const auto entry = Field.FieldItems.find(instanceId);

			if (entry == Field.FieldItems.end())
			{
				//FindTypeValueReferences<unsigned int>(instanceId);

				DiscardPacket();

				return 0;
			}

			unsigned int itemId = (unsigned int)entry->second.ItemId;

			//if (itemId == 90000001 || itemId == 90000002 || itemId == 90000010)
			//{
			//	FoundUnknownValue();
			//}

			//size_t combo = (size_t(itemId) << 32) | (size_t(Version) << 16) | StreamStack[0].PacketStream.Data.size();
			//
			//if (!IdAmountStates.contains(combo))
			//{
			//	IdAmountStates.insert(combo);
			//}

			if (itemId == 90000001 || itemId == 90000002)
			{
				return 1;
			}

			if (itemId == 90000010)
			{
				return 2;
			}

			return 0;
		}

		unsigned int SniffHandler::GetFieldItemType(unsigned int instanceId)
		{
			return GetFieldItemType((Enum::ItemEntityId)instanceId);
		}

		unsigned int SniffHandler::GetFieldItemId(Enum::ItemEntityId instanceId)
		{
			const auto entry = Field.FieldItems.find(instanceId);

			if (entry == Field.FieldItems.end())
			{
				FindTypeValueReferences<unsigned int>(instanceId);

				return 0;
			}

			return (unsigned int)entry->second.ItemId;
		}

		unsigned int SniffHandler::GetFieldItemId(unsigned int instanceId)
		{
			return GetFieldItemId((Enum::ItemEntityId)instanceId);
		}

		unsigned int SniffHandler::GetClassFromNpc(unsigned int actorId)
		{
			return GetClassFromNpc((Enum::ActorId)actorId);
		}

		unsigned int SniffHandler::GetClassFromNpc(Enum::ActorId actorId)
		{
			const auto entry = Field.Npcs.find(actorId);

			if (entry == Field.Npcs.end())
			{
				DiscardPacket();

				return 0;
			}

			return (unsigned int)entry->second.Data->Class;
		}

		bool SniffHandler::IsNpcFriendly(unsigned int actorId)
		{
			return IsNpcFriendly((Enum::ActorId)actorId);
		}

		bool SniffHandler::IsNpcFriendly(Enum::ActorId actorId)
		{
			const auto entry = Field.Npcs.find(actorId);

			if (entry == Field.Npcs.end())
			{
				DiscardPacket();

				return 0;
			}

			return entry->second.Data->NpcType != 0;
		}

		Item* SniffHandler::RegisterItem(Enum::ItemInstanceId instanceId, Enum::ItemId itemId)
		{
			if (itemId == Enum::ItemId::Null)
			{
				Item* item = GetItem(instanceId);

				if (item == nullptr)
				{
					if constexpr (ParserUtils::Packets::PrintUnknownValues)
					{
						//FoundUnknownValue();

						//std::cout << TimeStamp << "registering item with null item id that doesn't have a previous entry " << instanceId << std::endl;
					}
				}

				return item;
			}

			if (Field.Items.contains(instanceId))
			{
				Item* item = &Field.Items[instanceId];

				if (item->ItemId == itemId)
				{
					return &Field.Items[instanceId];
				}

				*item = {};

				if (Field.ItemStats.contains(instanceId))
				{
					Field.ItemStats.erase(instanceId);
				}
			}
			
			const auto metaEntry = Field.GameData->Items.find(itemId);

			if (metaEntry == Field.GameData->Items.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "registering item with unknown item id " << itemId << std::endl;
				}

				return nullptr;
			}

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "registering item [" << itemId << "] '" << metaEntry->second.Name << "' " << instanceId << std::endl;
			}

			Item* item = &Field.Items[instanceId];

			item->ItemId = itemId;
			item->InstanceId = instanceId;
			item->Meta = &metaEntry->second;

			if ((unsigned int)itemId < 90000001 || (unsigned int)itemId > 90000003)
			{
				item->Data = &Field.ItemStats[instanceId];
			}

			return item;
		}

		Item* SniffHandler::GetItem(Enum::ItemInstanceId instanceId)
		{
			const auto itemEntry = Field.Items.find(instanceId);

			if (itemEntry == Field.Items.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					//FoundUnknownValue();

					//std::cout << TimeStamp << "referencing unregistered item instance " << instanceId << std::endl;
				}

				return nullptr;
			}

			return &itemEntry->second;
		}

		void SniffHandler::DiscardPacket()
		{
			PacketStream().SuppressErrors = true;
			PacketStream().DiscardErrors = true;
			PacketStream().HasRecentlyFailed = true;
		}

		void SniffHandler::FoundUnknownValue()
		{
			if constexpr (ParserUtils::Packets::PrintUnknownValues)
			{
				if (Field.MapId != Enum::MapId::Null && !Field.PrintedMap)
				{
					Field.PrintedMap = true;

					std::cout << "entered map [" << (unsigned int)Field.MapId << "] '";

					if (Field.CurrentMap)
					{
						std::cout << Field.CurrentMap->Name;
					}

					std::cout << "'" << std::endl;
				}

				PacketStream().FoundUnknownValue = true;
			}
		}

		void SniffHandler::FindValueReferencesInternal(size_t lastBufferEnd)
		{
			size_t size = FindValuesBuffer.size() - lastBufferEnd;

			FindValues.push_back({ lastBufferEnd, size, PacketIndex });
		}

		const std::string& GetStatName(Enum::StatAttributeBasic stat)
		{
			static const std::string unknown = "<unknown>";

			const auto entry = StatBasicNames.find(stat);

			if (entry == StatBasicNames.end())
			{
				return unknown;
			}

			return entry->second;
		}

		const std::string& GetStatName(Enum::StatAttributeSpecial stat)
		{
			static const std::string unknown = "<unknown>";

			const auto entry = StatSpecialNames.find(stat);

			if (entry == StatSpecialNames.end())
			{
				return unknown;
			}

			return entry->second;
		}

		std::string GetJobName(Enum::JobCode jobCode, Enum::JobId job)
		{
			return GetJobName(jobCode, (jobCode >= 10 && jobCode <= 110) ? ((unsigned short)job % 10) : 0);
		}

		std::string GetJobName(Enum::JobCode jobCode, unsigned int rank)
		{
			const auto jobEntry = JobNames.find((unsigned short)jobCode);

			std::string jobName = jobEntry != JobNames.end() ? jobEntry->second : "<unknown>";

			if (rank >= JobSuffixes->size())
			{
				return jobName;
			}

			return jobName + JobSuffixes[rank];
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintActor& actorRef)
{
	using namespace Networking::Packets;

	if (actorRef.Actor == Enum::ActorId::Null)
	{
		return out << "actor <null>";
	}

	const Actor* actor = actorRef.Field.GetActor(actorRef.Actor);
	const Npc* npc = actorRef.Field.GetNpc(actorRef.Actor);
	const Pet* pet = actorRef.Field.GetPet(actorRef.Actor);
	const Player* player = actorRef.Field.GetPlayer(actorRef.Actor);

	if (!actor)
	{
		const char* messages[] = {
			"unregistored actor ",
			"unregistored player ",
			"unregistored pet ",
			"unregistored npc ",
		};

		return out << messages[unsigned int(actorRef.Type)] << (unsigned int)actorRef.Actor;
	}

	if (actor->Type != actorRef.Type && actorRef.Type != ActorType::Actor)
	{
		const char* messages[] = {
			"actor",
			"player",
			"pet",
			"npc",
		};

		out << "expected " << messages[unsigned int(actorRef.Type)] << " got ";
	}

	if (player)
	{
		return out << (actorRef.Actor == player->IsCurrentPlayer ? "current player '" : "player '") << player->Name << "' [" << GetJobName(player->JobCode, player->Job) << "] Lv" << actor->Level << " as actor " << (unsigned int)actorRef.Actor;
	}

	if (pet)
	{
		bool hasSkin = pet->SkinNpcId != Enum::NpcId::Null && pet->SkinNpcId != pet->NpcId;

		std::cout << (pet->ItemId != Enum::ItemInstanceId::Null ? "pet '" : "hungry '");

		if (pet->Name.size())
			std::cout << pet->Name;
		else
			std::cout << pet->NpcName;

		std::cout << "' '";

		if (pet->NpcName.size())
			std::cout << pet->NpcName;
		else
			std::cout << (unsigned int)pet->NpcId;

		if (hasSkin && pet->Npc)
		{
			std::cout << "' (Skin: '";

			if (pet->Npc->Name.size())
				std::cout << pet->Npc->Name;
			else
				std::cout << (unsigned int)pet->SkinNpcId;

			std::cout << "')";
		}
		else
		{
			std::cout << "'";
		}

		std::cout << " Lv" << pet->Actor->Level << " as actor " << (unsigned int)actorRef.Actor;

		if (pet->Owner)
		{
			std::cout << " belonging to player '" << pet->Owner->Name << "' (" << (unsigned int)pet->Owner->Actor->ActorId << ")";
		}

		return out;
	}

	if (npc)
	{
		if (npc->Data)
		{
			return out << "npc [" << (unsigned int)npc->NpcId << "] '" << npc->Data->Name << "' Lv" << npc->Actor->Level << " as actor " << (unsigned int)actorRef.Actor;
		}

		return out << "npc with unknown id " << (unsigned int)npc->NpcId << " '" << npc->Name << "' Lv" << npc->Actor->Level << " as actor " << (unsigned int)actorRef.Actor;
	}

	return out << "unknown actor " << (unsigned int)actorRef.Actor;
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintEffect& effectRef)
{
	bool statsSpecified = effectRef.Effect.Stats.EffectId != Enum::EffectId::Null;

	out << (effectRef.Effect.Enabled ? "" : "[disabled] ") << (statsSpecified ? "effect " : "unknown effect");

	if (statsSpecified)
	{
		out << "[" << (unsigned int)effectRef.Effect.Stats.EffectId << "]";

		const auto entry = effectRef.Field.GameData->Effects.find(effectRef.Effect.Stats.EffectId);

		if (entry != effectRef.Field.GameData->Effects.end())
		{
			const auto levelEntry = entry->second.Names.find(effectRef.Effect.Stats.EffectLevel);

			if (levelEntry != entry->second.Names.end())
			{
				out << " '" << levelEntry->second << "'";
			}
			else
			{
				out << " '" << entry->second.Name << "'";
			}
		}

		out << " Lv" << (unsigned int)effectRef.Effect.Stats.EffectLevel;

		if (effectRef.Effect.Stats.Stacks != 1)
		{
			out << " x" << effectRef.Effect.Stats.Stacks;
		}
	}

	if (effectRef.Effect.ShieldHealth)
	{
		out << " (Shield: " << effectRef.Effect.ShieldHealth << ")";
	}

	unsigned int duration = effectRef.Effect.Stats.EndTime - effectRef.Effect.Stats.StartTime;

	if (duration && (duration & 0x80000000) == 0)
	{
		out << " lasting " << duration << " ms";
	}

	out << " with instance id " << (unsigned int)effectRef.Effect.InstanceId;

	if (effectRef.Effect.SourceId == effectRef.OwnerId)
	{
		out << " from self";
	}
	else if (effectRef.Effect.SourceId != Enum::ActorId::Null)
	{
		out << " from caster " << Networking::Packets::PrintActor{ effectRef.Field, effectRef.Effect.SourceId };
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintSkill& effect)
{
	out << "[" << (unsigned int)effect.SkillId << "] ";

	const auto entry = effect.Field.GameData->Skills.find(effect.SkillId);

	if (entry != effect.Field.GameData->Skills.end())
	{
		out << "'" << entry->second.Name << "' ";
	}

	return out << "Lv" << (unsigned short)effect.SkillLevel;
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItem& itemRef)
{
	const auto itemEntry = itemRef.Field.Items.find(itemRef.ItemInstanceId);

	if (itemEntry == itemRef.Field.Items.end())
	{
		return out << "<unknown item " << itemRef.ItemInstanceId << ">";
	}

	const Networking::Packets::Item* item = &itemEntry->second;

	const auto rarityEntry = Networking::Packets::Rarities.find(item->Rarity);

	out << "[" << item->ItemId << "] ";

	if (rarityEntry != Networking::Packets::Rarities.end())
	{
		out << rarityEntry->second << " ";
	}
	else
	{
		out << "<unknown rarity> ";
	}

	if (item->Meta->Level != 0)
	{
		out << "Lv" << item->Meta->Level << " ";
	}

	out << "'" << item->Meta->Name << "' ";

	if (item->Amount != 1)
	{
		out << "x" << item->Amount << " ";
	}

	if (item->Data)
	{
		if (item->Data->LimitBreak.Level != 0)
		{
			out << "*" << item->Data->LimitBreak.Level << " ";
		}
		else if (item->Data->Enchantment.Level != 0)
		{
			out << "+" << item->Data->Enchantment.Level << " ";
		}

		if (item->Data->Binding.CharacterId != Enum::CharacterId::Null)
		{
			out << "(Bound to " << item->Data->Binding.Name << ") ";
		}
	}

	return out << item->InstanceId;
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItemStats& itemRef)
{
	const auto itemEntry = itemRef.Field.Items.find(itemRef.ItemInstanceId);

	if (itemEntry == itemRef.Field.Items.end())
	{
		return out << "\t<unknown item stats " << itemRef.ItemInstanceId << ">";
	}

	const Networking::Packets::Item* item = &itemEntry->second;

	return out << Networking::Packets::PrintItemDataStats{ itemRef.Field, item->Data, itemRef.Tabs };
}

template <typename T>
void printStat(const std::vector<T>& stats, const char* message, const char* tabs)
{
	if (stats.size())
	{
		std::cout << (tabs + 1) << message << std::endl;
	}

	for (const auto& entry : stats)
	{
		if (entry.Rate == 0 && entry.Value == 0)
		{
			continue;
		}

		std::cout << tabs << Networking::Packets::GetStatName(entry.Type) << ": ";

		if (entry.Rate != 0)
		{
			std::cout << "r: " << (entry.Rate * 100) << (entry.Value != 0 ? "%; " : "%");
		}

		if (entry.Value != 0)
		{
			if constexpr (std::is_floating_point_v<decltype(entry.Value)>)
			{
				std::cout << "v: " << (entry.Value * 100) << "%";
			}
			else
			{

				std::cout << "v: " << entry.Value;
			}
		}

		std::cout << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const Networking::Packets::PrintItemDataStats& itemRef)
{
	const char tabData[] = "\t\t\t\t\t";
	const char* tabs = tabData + (sizeof(tabData) - 1) - itemRef.Tabs;
	
	printStat(itemRef.Data->LimitBreak.Stats.Basic, "limit break basic stats", tabs - 1);
	printStat(itemRef.Data->LimitBreak.Stats.Special, "limit break special stats", tabs - 1);
	printStat(itemRef.Data->Enchantment.Basic, "enchantment basic stats", tabs - 1);

	printStat(itemRef.Data->Stats.Constant.Basic, "constant basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Constant.Special, "constant special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Static.Basic, "static basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Static.Special, "static special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Random.Basic, "random basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Random.Special, "random special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Title.Basic, "title basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Title.Special, "title special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment1.Basic, "empowerment 1 basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment1.Special, "empowerment 1 special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment2.Basic, "empowerment 2 basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment2.Special, "empowerment 2 special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment3.Basic, "empowerment 3 basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment3.Special, "empowerment 3 special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment4.Basic, "empowerment 4 basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment4.Special, "empowerment 4 special stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment5.Basic, "empowerment 5 basic stats", tabs - 1);
	printStat(itemRef.Data->Stats.Empowerment5.Special, "empowerment 5 special stats", tabs - 1);

	return out;
}
