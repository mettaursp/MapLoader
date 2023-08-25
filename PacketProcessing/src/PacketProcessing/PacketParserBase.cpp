#include "PacketParserBase.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void ParsePacket<0, false, 0>(PacketHandler& handler) { }
	}
}