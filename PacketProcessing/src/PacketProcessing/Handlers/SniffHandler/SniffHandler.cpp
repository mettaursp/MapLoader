#include "SniffHandler-decl.h"

namespace Networking
{
	namespace Packets
	{
		bool SniffHandler::IsNpcBoss(unsigned int npcId) const
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

		bool SniffHandler::NpcHasHiddenHp(unsigned int npcId) const
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

			const auto itemHandle = Data->Items.find(itemId);

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

			if (itemHandle->second.BadgeType != 0)
			{
				return 4;
			}

			return 0;
		}

		unsigned short SniffHandler::GetItemCategory(unsigned int itemId) const
		{
			return (unsigned short)(itemId / 100000);
		}
	}
}