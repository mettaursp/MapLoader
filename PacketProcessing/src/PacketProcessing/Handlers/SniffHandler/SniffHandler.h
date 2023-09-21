#pragma once

#include "SniffHandler-decl.h"

#include "./../../PacketParserBase.h"

#include <GameData/Packets\Server/EnchantScrollRewardPacket.h>
#include <GameData/Packets\Server/LoadCubesExpirationPacket.h>
#include <GameData/Packets\Client/ReconnectPacket.h>
#include <GameData/Packets\Server/NpcTalkActionMovePlayerPacket.h>
#include <GameData/Packets\Client/ResponseVersionPacket.h>
#include <GameData/Packets\Server/StatPacket.h>
#include <GameData/Packets\Client/LogInPacket.h>
#include <GameData/Packets\Server/FittingDollLoadPacket.h>
#include <GameData/Packets\Server/NpcTalkRespondPacket.h>
#include <GameData/Packets\Client/ResponseHeartbeatPacket.h>
#include <GameData/Packets\Client/ResponseKeyPacket.h>
#include <GameData/Packets\Server/PetRenamePacket.h>
#include <GameData/Packets\Client/HandshakePacket.h>
#include <GameData/Packets\Client/RequestQuitPacket.h>
#include <GameData/Packets\Server/NpcTalkUpdatePacket.h>
#include <GameData/Packets\Server/PlayInstrumentViewMusicPacket.h>
#include <GameData/Packets\Client/LogInAuthTokenPacket.h>
#include <GameData/Packets\Server/PetInfoPacket.h>
#include <GameData/Packets\Server/NpcTalkAlliancePacket.h>
#include <GameData/Packets\Client/SkillCastPacket.h>
#include <GameData/Packets\Server/NpcTalkEndPacket.h>
#include <GameData/Packets\Client/SkillSyncDamagePacket.h>
#include <GameData/Packets\Client/SkillDamagePacket.h>
#include <GameData/Packets\Client/SkillRegionSkillPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardMesoPacket.h>
#include <GameData/Packets\Client/SkillSyncPacket.h>
#include <GameData/Packets\Client/SkillSyncTickPacket.h>
#include <GameData/Packets\Server/NpcTalkActionCutscenePacket.h>
#include <GameData/Packets\Server/PlayInstrumentEffectPacket.h>
#include <GameData/Packets\Client/SkillCancelPacket.h>
#include <GameData/Packets\Client/StateSkillPacket.h>
#include <GameData/Packets\Client/NpcTalkClosePacket.h>
#include <GameData/Packets\Server/NpcTalkActionAddOptionPacket.h>
#include <GameData/Packets\Client/NpcTalkBeginPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardItemPacket.h>
#include <GameData/Packets\Server/PlayInstrumentLeaveEnsemblePacket.h>
#include <GameData/Packets\Client/NpcTalkContinuePacket.h>
#include <GameData/Packets\Client/NpcTalkEnchantUnknownPacket.h>
#include <GameData/Packets\Server/ShopBuyPacket.h>
#include <GameData/Packets\Client/NpcTalkEnchantPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollErrorPacket.h>
#include <GameData/Packets\Server/NpcTalkActionOpenDialogPacket.h>
#include <GameData/Packets\Client/NpcTalkNextQuestPacket.h>
#include <GameData/Packets\Client/NpcTalkAllianceQuestAcceptPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardExpPacket.h>
#include <GameData/Packets\Client/NpcTalkAllianceQuestTalkPacket.h>
#include <GameData/Packets\Client/NpcTalkCinematicPacket.h>
#include <GameData/Packets\Client/SystemInfoPacket.h>
#include <GameData/Packets\Server/MailCollectingPacket.h>
#include <GameData/Packets\Server/CharacterListDeletePendingPacket.h>
#include <GameData/Packets\Server/BlackMarketSoldPacket.h>
#include <GameData/Packets\Server/FieldRemoveNpcPacket.h>
#include <GameData/Packets\Server/ItemLockErrorPacket.h>
#include <GameData/Packets\Server/FieldAddPlayerPacket.h>
#include <GameData/Packets\Server/PetInventoryUpdateAmountPacket.h>
#include <GameData/Packets\Server/Reconnect7Packet.h>
#include <GameData/Packets\Server/MailLoadPacket.h>
#include <GameData/Packets\Server/NpcTalkContinuePacket.h>
#include <GameData/Packets\Server/TradeDeclinedPacket.h>
#include <GameData/Packets\Server/MailErrorPacket.h>
#include <GameData/Packets\Server/CharacterListLoadPacket.h>
#include <GameData/Packets\Server/CharacterListAddPacket.h>
#include <GameData/Packets\Server/CharacterListDeletePacket.h>
#include <GameData/Packets\Server/ItemEnchantSuccessPacket.h>
#include <GameData/Packets\Server/ItemLockRemoveItemPacket.h>
#include <GameData/Packets\Server/CharacterListCancelDeletePacket.h>
#include <GameData/Packets\Server/MailExpireNotificationPacket.h>
#include <GameData/Packets\Server/PetOtherPetInfoPacket.h>
#include <GameData/Packets\Server/CharacterListChangeNamePacket.h>
#include <GameData/Packets\Server/ItemLockAddItemPacket.h>
#include <GameData/Packets\Server/ItemLockUpdateItemPacket.h>
#include <GameData/Packets\Server/ItemEnchantBeginPacket.h>
#include <GameData/Packets\Server/ShopRemoveBuyBackPacket.h>
#include <GameData/Packets\Server/UserChatPacket.h>
#include <GameData/Packets\Server/MailSendCustomConfirmPacket.h>
#include <GameData/Packets\Server/RequestFieldEnterPacket.h>
#include <GameData/Packets\Server/MailReadPacket.h>
#include <GameData/Packets\Server/MailUpdateReadTimePacket.h>
#include <GameData/Packets\Server/MailDeletePacket.h>
#include <GameData/Packets\Server/MailReceivePacket.h>
#include <GameData/Packets\Server/MailStartListPacket.h>
#include <GameData/Packets\Server/FieldRemovePlayerPacket.h>
#include <GameData/Packets\Server/MailEndListPacket.h>
#include <GameData/Packets\Server/MailError2Packet.h>
#include <GameData/Packets\Server/MailReceiveGiftNotificationPacket.h>
#include <GameData/Packets\Server/TradeErrorPacket.h>
#include <GameData/Packets\Server/ServerEnterPacket.h>
#include <GameData/Packets\Server/UserChatItemLinkPacket.h>
#include <GameData/Packets\Server/FieldAddNpcPacket.h>
#include <GameData/Packets\Server/FurnishingStorageStartListPacket.h>
#include <GameData/Packets\Server/FurnishingStorageCountPacket.h>
#include <GameData/Packets\Server/FurnishingStorageAddPacket.h>
#include <GameData/Packets\Server/TradeFinalizeConfirmPacket.h>
#include <GameData/Packets\Server/FurnishingStorageRemovePacket.h>
#include <GameData/Packets\Server/ItemEnchantErrorPacket.h>
#include <GameData/Packets\Server/FurnishingStoragePurchasePacket.h>
#include <GameData/Packets\Server/FurnishingStorageUpdatePacket.h>
#include <GameData/Packets\Server/FurnishingStorageEndListPacket.h>
#include <GameData/Packets\Server/BlackMarketSearchResultsPacket.h>
#include <GameData/Packets\Server/ShopInstantRestockPacket.h>
#include <GameData/Packets\Server/ItemPutOnPacket.h>
#include <GameData/Packets\Server/ItemPutOffPacket.h>
#include <GameData/Packets\Server/ItemSkinPutOnPacket.h>
#include <GameData/Packets\Server/ItemSkinPutOffPacket.h>
#include <GameData/Packets\Server/ItemUpdatePacket.h>
#include <GameData/Packets\Server/FieldAddItemPacket.h>
#include <GameData/Packets\Server/LoadCubesPacket.h>
#include <GameData/Packets\Server/LoadCubesAvailabilityPacket.h>
#include <GameData/Packets\Server/LoadCubesPlotsPacket.h>
#include <GameData/Packets\Server/FieldRemoveItemPacket.h>
#include <GameData/Packets\Server/ExpUpPacket.h>
#include <GameData/Packets\Server/LevelUpPacket.h>
#include <GameData/Packets\Server/BindItemPacket.h>
#include <GameData/Packets\Server/SkillDamageSyncPacket.h>
#include <GameData/Packets\Server/SkillDamagePacket.h>
#include <GameData/Packets\Server/SkillDamageDotPacket.h>
#include <GameData/Packets\Server/SkillDamageHealPacket.h>
#include <GameData/Packets\Server/SkillDamageRegionPacket.h>
#include <GameData/Packets\Server/SkillDamageTilePacket.h>
#include <GameData/Packets\Server/BuffPacket.h>
#include <GameData/Packets\Server/ChangeAttributesPreviewPacket.h>
#include <GameData/Packets\Server/ChangeAttributesAddPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollPreviewItemPacket.h>
#include <GameData/Packets\Server/ShopLoadItemsPacket.h>
#include <GameData/Packets\Server/ChangeAttributesErrorPacket.h>
#include <GameData/Packets\Server/JobPacket.h>
#include <GameData/Packets\Server/ShopOpenPacket.h>
#include <GameData/Packets\Server/PetFusionPacket.h>
#include <GameData/Packets\Server/ShopUpdatePacket.h>
#include <GameData/Packets\Server/ShopBuyBackItemCountPacket.h>
#include <GameData/Packets\Server/ShopAddBuyBackPacket.h>
#include <GameData/Packets\Server/ShopLoadMeretItemPacket.h>
#include <GameData/Packets\Server/ShopLoadNewPacket.h>
#include <GameData/Packets\Server/ShopErrorPacket.h>
#include <GameData/Packets\Server/FieldAddPetPacket.h>
#include <GameData/Packets\Server/FieldRemovePetPacket.h>
#include <GameData/Packets\Server/TrophyStartPacket.h>
#include <GameData/Packets\Server/TrophyContentPacket.h>
#include <GameData/Packets\Server/TrophyUpdatePacket.h>
#include <GameData/Packets\Server/CharacterInfoPacket.h>
#include <GameData/Packets\Server/FittingDollRemovePacket.h>
#include <GameData/Packets\Server/FittingDollPutOnItemPacket.h>
#include <GameData/Packets\Server/FittingDollRemoveItemPacket.h>
#include <GameData/Packets\Server/FittingDollErrorPacket.h>
#include <GameData/Packets\Server/TradeReceiveRequestPacket.h>
#include <GameData/Packets\Server/TradeConfirmRequestPacket.h>
#include <GameData/Packets\Server/TradeBeginPacket.h>
#include <GameData/Packets\Server/PetErrorPacket.h>
#include <GameData/Packets\Server/TradeEndPacket.h>
#include <GameData/Packets\Server/TradeAddItemPacket.h>
#include <GameData/Packets\Server/PetUnknownFieldPetPacket.h>
#include <GameData/Packets\Server/TradeRemoveItemPacket.h>
#include <GameData/Packets\Server/TradeSetMoneyPacket.h>
#include <GameData/Packets\Server/TradeFinalizePacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateExpPacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateChargesPacket.h>
#include <GameData/Packets\Server/ItemEnchantUpdateIngredientsPacket.h>
#include <GameData/Packets\Server/ItemEnchantFailPacket.h>
#include <GameData/Packets\Server/BlackMarketErrorPacket.h>
#include <GameData/Packets\Server/BlackMarketMyListingsPacket.h>
#include <GameData/Packets\Server/BlackMarketCreateListingPacket.h>
#include <GameData/Packets\Server/BlackMarketCancelListingPacket.h>
#include <GameData/Packets\Server/BlackMarketPurchasePacket.h>
#include <GameData/Packets\Server/BlackMarketPrepareListingPacket.h>
#include <GameData/Packets\Server/EnchantScrollEnchantUiPacket.h>
#include <GameData/Packets\Server/PetEvolvePacket.h>
#include <GameData/Packets\Server/EnchantScrollStatUiPacket.h>
#include <GameData/Packets\Server/EnchantScrollSuccessPacket.h>
#include <GameData/Packets\Server/EnchantScrollResultPacket.h>
#include <GameData/Packets\Server/PlayInstrumentStartImprovisePacket.h>
#include <GameData/Packets\Server/PlayInstrumentPlayNotePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStopImprovisePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStartScorePacket.h>
#include <GameData/Packets\Server/PlayInstrumentStopScorePacket.h>
#include <GameData/Packets\Server/PlayInstrumentCreateScoreResponsePacket.h>
#include <GameData/Packets\Server/PlayInstrumentUpdateScoreUsesPacket.h>
#include <GameData/Packets\Server/PlayInstrumentWritePlayDialogPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollUseScrollPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollUseOnItemPacket.h>
#include <GameData/Packets\Server/ChangeAttributesScrollApplyPacket.h>
#include <GameData/Packets\Server/PetAddPacket.h>
#include <GameData/Packets\Server/PetRemovePacket.h>
#include <GameData/Packets\Server/PetSoundPacket.h>
#include <GameData/Packets\Server/PetPotionPacket.h>
#include <GameData/Packets\Server/PetLootPacket.h>
#include <GameData/Packets\Server/PetLoadCollectionPacket.h>
#include <GameData/Packets\Server/PetAddCollectionPacket.h>
#include <GameData/Packets\Server/PetLevelUpPacket.h>
#include <GameData/Packets\Server/PetFusionDialogPacket.h>
#include <GameData/Packets\Server/PetSummonedNoticePacket.h>
#include <GameData/Packets\Server/PetEvolvePointsPacket.h>
#include <GameData/Packets\Server/PetLapisSnarePacket.h>
#include <GameData/Packets\Server/PetInventoryStoreItemPacket.h>
#include <GameData/Packets\Server/PetInventoryRemoveItemPacket.h>
#include <GameData/Packets\Server/PetInventoryMoveItemPacket.h>
#include <GameData/Packets\Server/PetInventoryListItemsPacket.h>
#include <GameData/Packets\Server/PetInventoryStartListPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollRewardPacket>(const Server::EnchantScrollRewardPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesExpirationPacket>(const Server::LoadCubesExpirationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ReconnectPacket>(const Client::ReconnectPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionMovePlayerPacket>(const Server::NpcTalkActionMovePlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::StatPacket>(const Server::StatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::LogInPacket>(const Client::LogInPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollLoadPacket>(const Server::FittingDollLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkRespondPacket>(const Server::NpcTalkRespondPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseHeartbeatPacket>(const Client::ResponseHeartbeatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetRenamePacket>(const Server::PetRenamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::HandshakePacket>(const Client::HandshakePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::RequestQuitPacket>(const Client::RequestQuitPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkUpdatePacket>(const Server::NpcTalkUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentViewMusicPacket>(const Server::PlayInstrumentViewMusicPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::LogInAuthTokenPacket>(const Client::LogInAuthTokenPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInfoPacket>(const Server::PetInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkAlliancePacket>(const Server::NpcTalkAlliancePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillCastPacket>(const Client::SkillCastPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkEndPacket>(const Server::NpcTalkEndPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncDamagePacket>(const Client::SkillSyncDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillDamagePacket>(const Client::SkillDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillRegionSkillPacket>(const Client::SkillRegionSkillPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardMesoPacket>(const Server::NpcTalkActionRewardMesoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncPacket>(const Client::SkillSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillSyncTickPacket>(const Client::SkillSyncTickPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionCutscenePacket>(const Server::NpcTalkActionCutscenePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentEffectPacket>(const Server::PlayInstrumentEffectPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SkillCancelPacket>(const Client::SkillCancelPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::StateSkillPacket>(const Client::StateSkillPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkClosePacket>(const Client::NpcTalkClosePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionAddOptionPacket>(const Server::NpcTalkActionAddOptionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkBeginPacket>(const Client::NpcTalkBeginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardItemPacket>(const Server::NpcTalkActionRewardItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentLeaveEnsemblePacket>(const Server::PlayInstrumentLeaveEnsemblePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkContinuePacket>(const Client::NpcTalkContinuePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantUnknownPacket>(const Client::NpcTalkEnchantUnknownPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyPacket>(const Server::ShopBuyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantPacket>(const Client::NpcTalkEnchantPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollErrorPacket>(const Server::ChangeAttributesScrollErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionOpenDialogPacket>(const Server::NpcTalkActionOpenDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkNextQuestPacket>(const Client::NpcTalkNextQuestPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(const Client::NpcTalkAllianceQuestAcceptPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardExpPacket>(const Server::NpcTalkActionRewardExpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(const Client::NpcTalkAllianceQuestTalkPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkCinematicPacket>(const Client::NpcTalkCinematicPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Client::SystemInfoPacket>(const Client::SystemInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailCollectingPacket>(const Server::MailCollectingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePendingPacket>(const Server::CharacterListDeletePendingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSoldPacket>(const Server::BlackMarketSoldPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveNpcPacket>(const Server::FieldRemoveNpcPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockErrorPacket>(const Server::ItemLockErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPlayerPacket>(const Server::FieldAddPlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryUpdateAmountPacket>(const Server::PetInventoryUpdateAmountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::Reconnect7Packet>(const Server::Reconnect7Packet& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailLoadPacket>(const Server::MailLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkContinuePacket>(const Server::NpcTalkContinuePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeDeclinedPacket>(const Server::TradeDeclinedPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailErrorPacket>(const Server::MailErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListLoadPacket>(const Server::CharacterListLoadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListAddPacket>(const Server::CharacterListAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePacket>(const Server::CharacterListDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantSuccessPacket>(const Server::ItemEnchantSuccessPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockRemoveItemPacket>(const Server::ItemLockRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListCancelDeletePacket>(const Server::CharacterListCancelDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailExpireNotificationPacket>(const Server::MailExpireNotificationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetOtherPetInfoPacket>(const Server::PetOtherPetInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListChangeNamePacket>(const Server::CharacterListChangeNamePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockAddItemPacket>(const Server::ItemLockAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockUpdateItemPacket>(const Server::ItemLockUpdateItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantBeginPacket>(const Server::ItemEnchantBeginPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopRemoveBuyBackPacket>(const Server::ShopRemoveBuyBackPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserChatPacket>(const Server::UserChatPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailSendCustomConfirmPacket>(const Server::MailSendCustomConfirmPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::RequestFieldEnterPacket>(const Server::RequestFieldEnterPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReadPacket>(const Server::MailReadPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailUpdateReadTimePacket>(const Server::MailUpdateReadTimePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailDeletePacket>(const Server::MailDeletePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReceivePacket>(const Server::MailReceivePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailStartListPacket>(const Server::MailStartListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePlayerPacket>(const Server::FieldRemovePlayerPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailEndListPacket>(const Server::MailEndListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailError2Packet>(const Server::MailError2Packet& packet);

		template <>
		void SniffHandler::PacketParsed<Server::MailReceiveGiftNotificationPacket>(const Server::MailReceiveGiftNotificationPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeErrorPacket>(const Server::TradeErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ServerEnterPacket>(const Server::ServerEnterPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::UserChatItemLinkPacket>(const Server::UserChatItemLinkPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddNpcPacket>(const Server::FieldAddNpcPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageStartListPacket>(const Server::FurnishingStorageStartListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageCountPacket>(const Server::FurnishingStorageCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageAddPacket>(const Server::FurnishingStorageAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizeConfirmPacket>(const Server::TradeFinalizeConfirmPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageRemovePacket>(const Server::FurnishingStorageRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantErrorPacket>(const Server::ItemEnchantErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStoragePurchasePacket>(const Server::FurnishingStoragePurchasePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageUpdatePacket>(const Server::FurnishingStorageUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageEndListPacket>(const Server::FurnishingStorageEndListPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSearchResultsPacket>(const Server::BlackMarketSearchResultsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopInstantRestockPacket>(const Server::ShopInstantRestockPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOnPacket>(const Server::ItemPutOnPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOffPacket>(const Server::ItemPutOffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOnPacket>(const Server::ItemSkinPutOnPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOffPacket>(const Server::ItemSkinPutOffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemUpdatePacket>(const Server::ItemUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddItemPacket>(const Server::FieldAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPacket>(const Server::LoadCubesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesAvailabilityPacket>(const Server::LoadCubesAvailabilityPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LoadCubesPlotsPacket>(const Server::LoadCubesPlotsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveItemPacket>(const Server::FieldRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ExpUpPacket>(const Server::ExpUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::LevelUpPacket>(const Server::LevelUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BindItemPacket>(const Server::BindItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageSyncPacket>(const Server::SkillDamageSyncPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamagePacket>(const Server::SkillDamagePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageDotPacket>(const Server::SkillDamageDotPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageHealPacket>(const Server::SkillDamageHealPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageRegionPacket>(const Server::SkillDamageRegionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageTilePacket>(const Server::SkillDamageTilePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesPreviewPacket>(const Server::ChangeAttributesPreviewPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesAddPacket>(const Server::ChangeAttributesAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollPreviewItemPacket>(const Server::ChangeAttributesScrollPreviewItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadItemsPacket>(const Server::ShopLoadItemsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesErrorPacket>(const Server::ChangeAttributesErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::JobPacket>(const Server::JobPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopOpenPacket>(const Server::ShopOpenPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionPacket>(const Server::PetFusionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopUpdatePacket>(const Server::ShopUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyBackItemCountPacket>(const Server::ShopBuyBackItemCountPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopAddBuyBackPacket>(const Server::ShopAddBuyBackPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadMeretItemPacket>(const Server::ShopLoadMeretItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadNewPacket>(const Server::ShopLoadNewPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ShopErrorPacket>(const Server::ShopErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPetPacket>(const Server::FieldAddPetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePetPacket>(const Server::FieldRemovePetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyStartPacket>(const Server::TrophyStartPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyContentPacket>(const Server::TrophyContentPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TrophyUpdatePacket>(const Server::TrophyUpdatePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::CharacterInfoPacket>(const Server::CharacterInfoPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemovePacket>(const Server::FittingDollRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollPutOnItemPacket>(const Server::FittingDollPutOnItemPacket& packet);

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
		void SniffHandler::PacketParsed<Server::PetErrorPacket>(const Server::PetErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeEndPacket>(const Server::TradeEndPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeAddItemPacket>(const Server::TradeAddItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetUnknownFieldPetPacket>(const Server::PetUnknownFieldPetPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeRemoveItemPacket>(const Server::TradeRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeSetMoneyPacket>(const Server::TradeSetMoneyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizePacket>(const Server::TradeFinalizePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateExpPacket>(const Server::ItemEnchantUpdateExpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateChargesPacket>(const Server::ItemEnchantUpdateChargesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(const Server::ItemEnchantUpdateIngredientsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantFailPacket>(const Server::ItemEnchantFailPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketErrorPacket>(const Server::BlackMarketErrorPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketMyListingsPacket>(const Server::BlackMarketMyListingsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCreateListingPacket>(const Server::BlackMarketCreateListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCancelListingPacket>(const Server::BlackMarketCancelListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPurchasePacket>(const Server::BlackMarketPurchasePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPrepareListingPacket>(const Server::BlackMarketPrepareListingPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollEnchantUiPacket>(const Server::EnchantScrollEnchantUiPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePacket>(const Server::PetEvolvePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollStatUiPacket>(const Server::EnchantScrollStatUiPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollSuccessPacket>(const Server::EnchantScrollSuccessPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollResultPacket>(const Server::EnchantScrollResultPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartImprovisePacket>(const Server::PlayInstrumentStartImprovisePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentPlayNotePacket>(const Server::PlayInstrumentPlayNotePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopImprovisePacket>(const Server::PlayInstrumentStopImprovisePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStartScorePacket>(const Server::PlayInstrumentStartScorePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentStopScorePacket>(const Server::PlayInstrumentStopScorePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentCreateScoreResponsePacket>(const Server::PlayInstrumentCreateScoreResponsePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentUpdateScoreUsesPacket>(const Server::PlayInstrumentUpdateScoreUsesPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PlayInstrumentWritePlayDialogPacket>(const Server::PlayInstrumentWritePlayDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollUseScrollPacket>(const Server::ChangeAttributesScrollUseScrollPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollUseOnItemPacket>(const Server::ChangeAttributesScrollUseOnItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::ChangeAttributesScrollApplyPacket>(const Server::ChangeAttributesScrollApplyPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetAddPacket>(const Server::PetAddPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetRemovePacket>(const Server::PetRemovePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetSoundPacket>(const Server::PetSoundPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetPotionPacket>(const Server::PetPotionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLootPacket>(const Server::PetLootPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLoadCollectionPacket>(const Server::PetLoadCollectionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetAddCollectionPacket>(const Server::PetAddCollectionPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLevelUpPacket>(const Server::PetLevelUpPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetFusionDialogPacket>(const Server::PetFusionDialogPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetSummonedNoticePacket>(const Server::PetSummonedNoticePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetEvolvePointsPacket>(const Server::PetEvolvePointsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetLapisSnarePacket>(const Server::PetLapisSnarePacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStoreItemPacket>(const Server::PetInventoryStoreItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryRemoveItemPacket>(const Server::PetInventoryRemoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryMoveItemPacket>(const Server::PetInventoryMoveItemPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryListItemsPacket>(const Server::PetInventoryListItemsPacket& packet);

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStartListPacket>(const Server::PetInventoryStartListPacket& packet);

	}
}
