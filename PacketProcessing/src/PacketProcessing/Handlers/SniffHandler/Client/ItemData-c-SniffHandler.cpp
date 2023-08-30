#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Maple::Game::ItemData>(const Maple::Game::ItemData& packet)
		{
			
		}
	}
}
