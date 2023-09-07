#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet)
		{
			const std::string locales[] = {
				"KR",
				"",
				"NA",
				"",
				"",
				""
			};

			Feature = packet.Feature;
			Locale = locales[(int)packet.Locale];
		}
	}
}
