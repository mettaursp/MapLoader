#pragma once

#include "SniffHandler-decl.h"

#include "./../../PacketParserBase.h"

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct StateSkillPacket;
			struct LogInPacket;
			struct NpcTalkClosePacket;
			struct ResponseHeartbeatPacket;
			struct ResponseVersionPacket;
			struct NpcTalkBeginPacket;
			struct NpcTalkNextQuestPacket;
			struct HandshakePacket;
			struct RequestQuitPacket;
			struct NpcTalkAllianceQuestAcceptPacket;
			struct LogInAuthTokenPacket;
			struct NpcTalkEnchantPacket;
			struct ResponseKeyPacket;
			struct NpcTalkEnchantUnknownPacket;
			struct ReconnectPacket;
			struct NpcTalkAllianceQuestTalkPacket;
			struct SkillCastPacket;
			struct NpcTalkCinematicPacket;
			struct SkillSyncDamagePacket;
			struct SystemInfoPacket;
			struct SkillRegionSkillPacket;
			struct SkillDamagePacket;
			struct SkillSyncPacket;
			struct SkillSyncTickPacket;
			struct SkillCancelPacket;
			struct NpcTalkContinuePacket;
		}
		namespace Server
		{
			struct RequestHeartbeatPacket;
			struct TrophyUpdatePacket;
			struct VersionResultPacket;
			struct SkillDamageDotPacket;
			struct ServerListPacket;
			struct PetLoadCollectionPacket;
			struct NpcTalkActionRewardMesoPacket;
			struct PlayInstrumentCreateScoreResponsePacket;
			struct ItemEnchantUpdateChargesPacket;
			struct RevivalCountPacket;
			struct DungeonListEntriesPacket;
			struct ItemLockUpdateItemPacket;
			struct ItemEnchantFailPacket;
			struct CharacterListDeletePacket;
			struct Reconnect7Packet;
			struct ChangeAttributesScrollErrorPacket;
			struct ShopUpdatePacket;
			struct TrophyContentPacket;
			struct ItemEnchantBeginPacket;
			struct PetErrorPacket;
			struct GameToLoginPacket;
			struct RequestLoginPacket;
			struct PetSoundPacket;
			struct PlayInstrumentViewMusicPacket;
			struct CharacterListDeletePendingPacket;
			struct PetRemovePacket;
			struct PetFusionDialogPacket;
			struct NpcTalkActionAddOptionPacket;
			struct RequestVersionPacket;
			struct CharacterListLoadPacket;
			struct EmotionLearnPacket;
			struct NpcTalkActionCutscenePacket;
			struct AdventurerBarPacket;
			struct ItemEnchantUpdateExpPacket;
			struct MailSendCustomConfirmPacket;
			struct MailEndListPacket;
			struct CharacterListChangeNamePacket;
			struct NpcTalkRespondPacket;
			struct NpcTalkUpdatePacket;
			struct FieldRemoveItemPacket;
			struct NpcTalkActionMovePlayerPacket;
			struct BuffPacket;
			struct PatchFileDeletePacket;
			struct CharacterListCancelDeletePacket;
			struct LoginToGamePacket;
			struct MoveResultPacket;
			struct StatPacket;
			struct NpcTalkContinuePacket;
			struct UserStatePacket;
			struct PatchFileDownloadPacketPacket;
			struct NpcTalkAlliancePacket;
			struct PatchFileDownloadOnlinePacket;
			struct ResponseTimeSyncSetTimePacket;
			struct RequestKeyPacket;
			struct GameToGamePacket;
			struct TradeEndPacket;
			struct PingPacket;
			struct ResponseTimeSyncResetFieldsPacket;
			struct PetLapisSnarePacket;
			struct SkillDamageSyncPacket;
			struct NpcTalkActionRewardItemPacket;
			struct NpcTalkActionOpenDialogPacket;
			struct FinalizeReconnectPacket;
			struct JobPacket;
			struct CharacterListAddPacket;
			struct LoginResultPacket;
			struct NpcTalkEndPacket;
			struct TradeFinalizePacket;
			struct TradeFinalizeConfirmPacket;
			struct FittingDollPutOnItemPacket;
			struct ChangeAttributesErrorPacket;
			struct NpcTalkActionRewardExpPacket;
			struct ResponseTimeSyncInitializePacket;
			struct ResponseTimeSyncRequestPacket;
			struct ShopOpenPacket;
			struct BlackMarketErrorPacket;
			struct MailCollectingPacket;
			struct ShopLoadItemsPacket;
			struct PetOtherPetInfoPacket;
			struct ShopBuyPacket;
			struct ShopBuyBackItemCountPacket;
			struct PetEvolvePacket;
			struct ItemUpdatePacket;
			struct SkillDamageRegionPacket;
			struct ShopAddBuyBackPacket;
			struct ShopRemoveBuyBackPacket;
			struct BlackMarketSoldPacket;
			struct ShopInstantRestockPacket;
			struct UserSyncPacket;
			struct FieldAddItemPacket;
			struct FittingDollRemovePacket;
			struct LevelUpPacket;
			struct ShopMeretItemCountPacket;
			struct EnchantScrollEnchantUiPacket;
			struct MailReceiveGiftNotificationPacket;
			struct ShopLoadMeretItemPacket;
			struct ShopLoadNewPacket;
			struct PetInventoryRemoveItemPacket;
			struct ShopErrorPacket;
			struct SkillDamagePacket;
			struct RequestClientTickSyncPacket;
			struct SyncNumberPacket;
			struct MailLoadPacket;
			struct MailReadPacket;
			struct PlayInstrumentStopImprovisePacket;
			struct ItemLockRemoveItemPacket;
			struct MailErrorPacket;
			struct MailUpdateReadTimePacket;
			struct MailDeletePacket;
			struct ItemSkinPutOffPacket;
			struct MailReceivePacket;
			struct PetFusionPacket;
			struct MailExpireNotificationPacket;
			struct MailStartListPacket;
			struct MailError2Packet;
			struct PlayInstrumentStopScorePacket;
			struct ServerEnterPacket;
			struct FieldAddNpcPacket;
			struct RequestFieldEnterPacket;
			struct FieldRemoveNpcPacket;
			struct FieldAddPlayerPacket;
			struct FieldRemovePlayerPacket;
			struct UserChatPacket;
			struct PetInventoryUpdateAmountPacket;
			struct BlackMarketMyListingsPacket;
			struct UserChatItemLinkPacket;
			struct EmotionLoadPacket;
			struct EmotionErrorPacket;
			struct FurnishingStorageStartListPacket;
			struct PetRenamePacket;
			struct FurnishingStorageCountPacket;
			struct FurnishingStorageAddPacket;
			struct FurnishingStorageRemovePacket;
			struct PetInventoryListItemsPacket;
			struct PlayInstrumentStartImprovisePacket;
			struct FurnishingStoragePurchasePacket;
			struct PetInventoryMoveItemPacket;
			struct FurnishingStorageUpdatePacket;
			struct BlackMarketSearchResultsPacket;
			struct FurnishingStorageEndListPacket;
			struct FurnishingInventoryUnknownPacket;
			struct PetInventoryStartListPacket;
			struct ItemPutOnPacket;
			struct ItemPutOffPacket;
			struct ItemSkinPutOnPacket;
			struct TradeChangeOfferPacket;
			struct FieldPickUpItemPacket;
			struct PetInfoPacket;
			struct FieldMutateItemPacket;
			struct UserBattlePacket;
			struct FieldAddPetPacket;
			struct UserSkinColorPacket;
			struct TrophyStartPacket;
			struct RevivalConfirmPacket;
			struct ItemEnchantErrorPacket;
			struct ChangeAttributesPreviewChangePacket;
			struct RevivalPacket;
			struct FittingDollLoadPacket;
			struct ExpUpPacket;
			struct LoadCubesExpirationPacket;
			struct MesoPacket;
			struct MeretPacket;
			struct CurrencyTokenPacket;
			struct BlackMarketPrepareListingPacket;
			struct SkillUsePacket;
			struct SkillDamageHealPacket;
			struct TradeErrorPacket;
			struct SkillDamageTilePacket;
			struct ChangeAttributesScrollUseScrollPacket;
			struct TradeDeclinedPacket;
			struct SkillSyncPacket;
			struct FieldRemovePetPacket;
			struct LoadCubesPacket;
			struct LoadCubesAvailabilityPacket;
			struct LoadCubesPlotsPacket;
			struct CharacterInfoPacket;
			struct FittingDollRemoveItemPacket;
			struct PetAddPacket;
			struct FittingDollErrorPacket;
			struct TradeReceiveRequestPacket;
			struct TradeConfirmRequestPacket;
			struct TradeBeginPacket;
			struct TradeAddItemPacket;
			struct EnchantScrollResultPacket;
			struct TradeRemoveItemPacket;
			struct TradeSetMoneyPacket;
			struct ItemEnchantUpdateIngredientsPacket;
			struct ItemEnchantSuccessPacket;
			struct BlackMarketCreateListingPacket;
			struct BlackMarketCancelListingPacket;
			struct BlackMarketPurchasePacket;
			struct EnchantScrollStatUiPacket;
			struct EnchantScrollSuccessPacket;
			struct EnchantScrollRewardPacket;
			struct PlayInstrumentPlayNotePacket;
			struct PlayInstrumentStartScorePacket;
			struct PlayInstrumentLeaveEnsemblePacket;
			struct PlayInstrumentUpdateScoreUsesPacket;
			struct PlayInstrumentEffectPacket;
			struct PlayInstrumentWritePlayDialogPacket;
			struct ChangeAttributesApplyPacket;
			struct ChangeAttributesScrollPreviewChangePacket;
			struct ChangeAttributesScrollApplyPacket;
			struct PetPotionPacket;
			struct PetLootPacket;
			struct PetAddCollectionPacket;
			struct PetLevelUpPacket;
			struct PetSummonedNoticePacket;
			struct PetEvolvePointsPacket;
			struct PetUnknownFieldPetPacket;
			struct PetInventoryStoreItemPacket;
			struct ItemLockAddItemPacket;
			struct ItemLockErrorPacket;
			struct BindItemPacket;
		}
	}
}


namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::StateSkillPacket>(const Client::StateSkillPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLoadCollectionPacket>(const Server::PetLoadCollectionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkNextQuestPacket>(const Client::NpcTalkNextQuestPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseHeartbeatPacket>(const Client::ResponseHeartbeatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::HandshakePacket>(const Client::HandshakePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkClosePacket>(const Client::NpcTalkClosePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockUpdateItemPacket>(const Server::ItemLockUpdateItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkBeginPacket>(const Client::NpcTalkBeginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::LogInPacket>(const Client::LogInPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::RequestQuitPacket>(const Client::RequestQuitPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::Reconnect7Packet>(const Server::Reconnect7Packet& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollErrorPacket>(const Server::ChangeAttributesScrollErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(const Client::NpcTalkAllianceQuestAcceptPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(const Server::PlayInstrumentCreateScoreResponsePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ServerListPacket>(const Server::ServerListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestHeartbeatPacket>(const Server::RequestHeartbeatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::LogInAuthTokenPacket>(const Client::LogInAuthTokenPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantPacket>(const Client::NpcTalkEnchantPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantUnknownPacket>(const Client::NpcTalkEnchantUnknownPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateChargesPacket>(const Server::ItemEnchantUpdateChargesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ReconnectPacket>(const Client::ReconnectPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(const Client::NpcTalkAllianceQuestTalkPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillCastPacket>(const Client::SkillCastPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetErrorPacket>(const Server::PetErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestLoginPacket>(const Server::RequestLoginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkCinematicPacket>(const Client::NpcTalkCinematicPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncDamagePacket>(const Client::SkillSyncDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetSoundPacket>(const Server::PetSoundPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SystemInfoPacket>(const Client::SystemInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillDamagePacket>(const Client::SkillDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillRegionSkillPacket>(const Client::SkillRegionSkillPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePendingPacket>(const Server::CharacterListDeletePendingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncPacket>(const Client::SkillSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionAddOptionPacket>(const Server::NpcTalkActionAddOptionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestVersionPacket>(const Server::RequestVersionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardMesoPacket>(const Server::NpcTalkActionRewardMesoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncTickPacket>(const Client::SkillSyncTickPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::AdventurerBarPacket>(const Server::AdventurerBarPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailSendCustomConfirmPacket>(const Server::MailSendCustomConfirmPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListChangeNamePacket>(const Server::CharacterListChangeNamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkUpdatePacket>(const Server::NpcTalkUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillCancelPacket>(const Client::SkillCancelPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDeletePacket>(const Server::PatchFileDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkContinuePacket>(const Client::NpcTalkContinuePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListCancelDeletePacket>(const Server::CharacterListCancelDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::VersionResultPacket>(const Server::VersionResultPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionCutscenePacket>(const Server::NpcTalkActionCutscenePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MoveResultPacket>(const Server::MoveResultPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantFailPacket>(const Server::ItemEnchantFailPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::DungeonListEntriesPacket>(const Server::DungeonListEntriesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkAlliancePacket>(const Server::NpcTalkAlliancePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDownloadOnlinePacket>(const Server::PatchFileDownloadOnlinePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoginToGamePacket>(const Server::LoginToGamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionDialogPacket>(const Server::PetFusionDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDownloadPacketPacket>(const Server::PatchFileDownloadPacketPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::GameToLoginPacket>(const Server::GameToLoginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyUpdatePacket>(const Server::TrophyUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestKeyPacket>(const Server::RequestKeyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::GameToGamePacket>(const Server::GameToGamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeEndPacket>(const Server::TradeEndPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PingPacket>(const Server::PingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncResetFieldsPacket>(const Server::ResponseTimeSyncResetFieldsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FinalizeReconnectPacket>(const Server::FinalizeReconnectPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::JobPacket>(const Server::JobPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoginResultPacket>(const Server::LoginResultPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkEndPacket>(const Server::NpcTalkEndPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkRespondPacket>(const Server::NpcTalkRespondPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkContinuePacket>(const Server::NpcTalkContinuePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizePacket>(const Server::TradeFinalizePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionMovePlayerPacket>(const Server::NpcTalkActionMovePlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailEndListPacket>(const Server::MailEndListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionOpenDialogPacket>(const Server::NpcTalkActionOpenDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizeConfirmPacket>(const Server::TradeFinalizeConfirmPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardItemPacket>(const Server::NpcTalkActionRewardItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollPutOnItemPacket>(const Server::FittingDollPutOnItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardExpPacket>(const Server::NpcTalkActionRewardExpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListLoadPacket>(const Server::CharacterListLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentViewMusicPacket>(const Server::PlayInstrumentViewMusicPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListAddPacket>(const Server::CharacterListAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePacket>(const Server::CharacterListDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncInitializePacket>(const Server::ResponseTimeSyncInitializePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetRemovePacket>(const Server::PetRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncRequestPacket>(const Server::ResponseTimeSyncRequestPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ResponseTimeSyncSetTimePacket>(const Server::ResponseTimeSyncSetTimePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyContentPacket>(const Server::TrophyContentPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopOpenPacket>(const Server::ShopOpenPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketErrorPacket>(const Server::BlackMarketErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailCollectingPacket>(const Server::MailCollectingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadItemsPacket>(const Server::ShopLoadItemsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetOtherPetInfoPacket>(const Server::PetOtherPetInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopUpdatePacket>(const Server::ShopUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyPacket>(const Server::ShopBuyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyBackItemCountPacket>(const Server::ShopBuyBackItemCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemUpdatePacket>(const Server::ItemUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopAddBuyBackPacket>(const Server::ShopAddBuyBackPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopRemoveBuyBackPacket>(const Server::ShopRemoveBuyBackPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSoldPacket>(const Server::BlackMarketSoldPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopInstantRestockPacket>(const Server::ShopInstantRestockPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemovePacket>(const Server::FittingDollRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopMeretItemCountPacket>(const Server::ShopMeretItemCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollEnchantUiPacket>(const Server::EnchantScrollEnchantUiPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReceiveGiftNotificationPacket>(const Server::MailReceiveGiftNotificationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadMeretItemPacket>(const Server::ShopLoadMeretItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadNewPacket>(const Server::ShopLoadNewPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopErrorPacket>(const Server::ShopErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestClientTickSyncPacket>(const Server::RequestClientTickSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SyncNumberPacket>(const Server::SyncNumberPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailLoadPacket>(const Server::MailLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReadPacket>(const Server::MailReadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockRemoveItemPacket>(const Server::ItemLockRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailErrorPacket>(const Server::MailErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EmotionLearnPacket>(const Server::EmotionLearnPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailUpdateReadTimePacket>(const Server::MailUpdateReadTimePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailDeletePacket>(const Server::MailDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOffPacket>(const Server::ItemSkinPutOffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReceivePacket>(const Server::MailReceivePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailExpireNotificationPacket>(const Server::MailExpireNotificationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddItemPacket>(const Server::FieldAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailStartListPacket>(const Server::MailStartListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailError2Packet>(const Server::MailError2Packet& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ServerEnterPacket>(const Server::ServerEnterPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddNpcPacket>(const Server::FieldAddNpcPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestFieldEnterPacket>(const Server::RequestFieldEnterPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveNpcPacket>(const Server::FieldRemoveNpcPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPlayerPacket>(const Server::FieldAddPlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionPacket>(const Server::PetFusionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePlayerPacket>(const Server::FieldRemovePlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserSyncPacket>(const Server::UserSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserChatPacket>(const Server::UserChatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopScorePacket>(const Server::PlayInstrumentStopScorePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserChatItemLinkPacket>(const Server::UserChatItemLinkPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EmotionLoadPacket>(const Server::EmotionLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EmotionErrorPacket>(const Server::EmotionErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageStartListPacket>(const Server::FurnishingStorageStartListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetRenamePacket>(const Server::PetRenamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageCountPacket>(const Server::FurnishingStorageCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageAddPacket>(const Server::FurnishingStorageAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryRemoveItemPacket>(const Server::PetInventoryRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageRemovePacket>(const Server::FurnishingStorageRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStoragePurchasePacket>(const Server::FurnishingStoragePurchasePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryMoveItemPacket>(const Server::PetInventoryMoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageUpdatePacket>(const Server::FurnishingStorageUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageEndListPacket>(const Server::FurnishingStorageEndListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingInventoryUnknownPacket>(const Server::FurnishingInventoryUnknownPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOnPacket>(const Server::ItemPutOnPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOffPacket>(const Server::ItemPutOffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOnPacket>(const Server::ItemSkinPutOnPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeChangeOfferPacket>(const Server::TradeChangeOfferPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveItemPacket>(const Server::FieldRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldPickUpItemPacket>(const Server::FieldPickUpItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldMutateItemPacket>(const Server::FieldMutateItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::StatPacket>(const Server::StatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserBattlePacket>(const Server::UserBattlePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPetPacket>(const Server::FieldAddPetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserSkinColorPacket>(const Server::UserSkinColorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyStartPacket>(const Server::TrophyStartPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RevivalConfirmPacket>(const Server::RevivalConfirmPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantErrorPacket>(const Server::ItemEnchantErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RevivalPacket>(const Server::RevivalPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RevivalCountPacket>(const Server::RevivalCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserStatePacket>(const Server::UserStatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ExpUpPacket>(const Server::ExpUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LevelUpPacket>(const Server::LevelUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesExpirationPacket>(const Server::LoadCubesExpirationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MesoPacket>(const Server::MesoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MeretPacket>(const Server::MeretPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollLoadPacket>(const Server::FittingDollLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CurrencyTokenPacket>(const Server::CurrencyTokenPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPrepareListingPacket>(const Server::BlackMarketPrepareListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillUsePacket>(const Server::SkillUsePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageSyncPacket>(const Server::SkillDamageSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamagePacket>(const Server::SkillDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageDotPacket>(const Server::SkillDamageDotPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageHealPacket>(const Server::SkillDamageHealPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeErrorPacket>(const Server::TradeErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageRegionPacket>(const Server::SkillDamageRegionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageTilePacket>(const Server::SkillDamageTilePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(const Server::ChangeAttributesScrollUseScrollPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeDeclinedPacket>(const Server::TradeDeclinedPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillSyncPacket>(const Server::SkillSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePetPacket>(const Server::FieldRemovePetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPacket>(const Server::LoadCubesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesAvailabilityPacket>(const Server::LoadCubesAvailabilityPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPlotsPacket>(const Server::LoadCubesPlotsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemoveItemPacket>(const Server::FittingDollRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollErrorPacket>(const Server::FittingDollErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeReceiveRequestPacket>(const Server::TradeReceiveRequestPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeConfirmRequestPacket>(const Server::TradeConfirmRequestPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeBeginPacket>(const Server::TradeBeginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeAddItemPacket>(const Server::TradeAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeRemoveItemPacket>(const Server::TradeRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeSetMoneyPacket>(const Server::TradeSetMoneyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantBeginPacket>(const Server::ItemEnchantBeginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateExpPacket>(const Server::ItemEnchantUpdateExpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(const Server::ItemEnchantUpdateIngredientsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantSuccessPacket>(const Server::ItemEnchantSuccessPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketMyListingsPacket>(const Server::BlackMarketMyListingsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCreateListingPacket>(const Server::BlackMarketCreateListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCancelListingPacket>(const Server::BlackMarketCancelListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSearchResultsPacket>(const Server::BlackMarketSearchResultsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPurchasePacket>(const Server::BlackMarketPurchasePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollStatUiPacket>(const Server::EnchantScrollStatUiPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollSuccessPacket>(const Server::EnchantScrollSuccessPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollResultPacket>(const Server::EnchantScrollResultPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollRewardPacket>(const Server::EnchantScrollRewardPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartImprovisePacket>(const Server::PlayInstrumentStartImprovisePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentPlayNotePacket>(const Server::PlayInstrumentPlayNotePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopImprovisePacket>(const Server::PlayInstrumentStopImprovisePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartScorePacket>(const Server::PlayInstrumentStartScorePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(const Server::PlayInstrumentLeaveEnsemblePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(const Server::PlayInstrumentUpdateScoreUsesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentEffectPacket>(const Server::PlayInstrumentEffectPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(const Server::PlayInstrumentWritePlayDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesPreviewChangePacket>(const Server::ChangeAttributesPreviewChangePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesApplyPacket>(const Server::ChangeAttributesApplyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesErrorPacket>(const Server::ChangeAttributesErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollPreviewChangePacket>(const Server::ChangeAttributesScrollPreviewChangePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollApplyPacket>(const Server::ChangeAttributesScrollApplyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetAddPacket>(const Server::PetAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetPotionPacket>(const Server::PetPotionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLootPacket>(const Server::PetLootPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetAddCollectionPacket>(const Server::PetAddCollectionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInfoPacket>(const Server::PetInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLevelUpPacket>(const Server::PetLevelUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetSummonedNoticePacket>(const Server::PetSummonedNoticePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePacket>(const Server::PetEvolvePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePointsPacket>(const Server::PetEvolvePointsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLapisSnarePacket>(const Server::PetLapisSnarePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetUnknownFieldPetPacket>(const Server::PetUnknownFieldPetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStoreItemPacket>(const Server::PetInventoryStoreItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryUpdateAmountPacket>(const Server::PetInventoryUpdateAmountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryListItemsPacket>(const Server::PetInventoryListItemsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStartListPacket>(const Server::PetInventoryStartListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockAddItemPacket>(const Server::ItemLockAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockErrorPacket>(const Server::ItemLockErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BindItemPacket>(const Server::BindItemPacket& packet);

	}
}
