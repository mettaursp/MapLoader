#include "PacketLogging.h"

#include <PacketProcessing/Handlers/SniffHandler/SniffHandler-decl.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void LogEquipment(SniffHandler* handler, const Maple::Game::EquipmentData& equipment, const char* message)
		{
			Item* item = handler->RegisterItem(equipment.ItemInstanceId, equipment.ItemId);

			item->Amount = 1;
			item->Rarity = equipment.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << message << PrintItem{ handler->Field, equipment.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ handler->Field, equipment.ItemInstanceId };
			}
		}

		void LogEquipment(SniffHandler* handler, const Maple::Game::CharacterEquipment& equipment)
		{
			for (const auto& entry : equipment.Equipment)
			{
				LogEquipment(handler, entry, "\twearing equipment ");
			}
			
			for (const auto& entry : equipment.Badges)
			{
				LogEquipment(handler, entry, "\twearing badges ");
			}
			
			for (const auto& entry : equipment.Skins)
			{
				LogEquipment(handler, entry, "\twearing skins ");
			}
			
			for (const auto& entry : equipment.Fashion)
			{
				LogEquipment(handler, entry, "\twearing fashion ");
			}
		}
	}
}