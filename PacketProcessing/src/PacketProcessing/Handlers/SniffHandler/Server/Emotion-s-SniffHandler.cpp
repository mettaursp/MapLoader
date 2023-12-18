#include "./../SniffHandler.h"

#include <GameData/Packets\Server/EmotionData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::EmotionLoadPacket>(const Server::EmotionLoadPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EmotionLearnPacket>(const Server::EmotionLearnPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EmotionErrorPacket>(const Server::EmotionErrorPacket& packet)
		{
			
		}
	}
}
