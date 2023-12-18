#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PatchFileData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDeletePacket>(const Server::PatchFileDeletePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDownloadOnlinePacket>(const Server::PatchFileDownloadOnlinePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PatchFileDownloadPacketPacket>(const Server::PatchFileDownloadPacketPacket& packet)
		{
			
		}
	}
}
