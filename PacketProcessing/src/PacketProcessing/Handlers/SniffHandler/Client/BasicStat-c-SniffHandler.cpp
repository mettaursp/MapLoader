#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Maple::Game::BasicStat>(const Maple::Game::BasicStat& packet)
		{
			
		}
	}
}
