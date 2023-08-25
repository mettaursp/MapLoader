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
	}
}