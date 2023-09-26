#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserChatPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserChatPacket>(const Server::UserChatPacket& packet)
		{
			if constexpr (!ParserUtils::Packets::PrintPacketOutput)
			{
				return;
			}

			using TypeEnum = Server::UserChatPacket::TypeEnum;

			switch (packet.Type)
			{
			case TypeEnum::WhisperFrom:
				std::cout << "[Whisper from] "; break;
			case TypeEnum::WhisperTo:
				std::cout << "[Whisper to] "; break;
			case TypeEnum::WhisperFail:
				std::cout << "[Whisper failed] "; break;
			case TypeEnum::WhisperReject:
				std::cout << "[Whisper rejected] "; break;
			case TypeEnum::Party:
				std::cout << "[Party] "; break;
			case TypeEnum::Guild:
				std::cout << "[Guild] "; break;
			case TypeEnum::Notice:
				std::cout << "[Server] "; break;
			case TypeEnum::World:
				std::cout << "[World] "; break;
			case TypeEnum::Channel:
				std::cout << "[Channel] "; break;
			case TypeEnum::NoticeAlert:
				std::cout << "[Alert] "; break;
			case TypeEnum::NoticeAlert2:
				std::cout << "[Alert2] "; break;
			case TypeEnum::Super:
				std::cout << "[Super] "; break;
			case TypeEnum::GuildAlert:
				std::cout << "[Guild alert] "; break;
			case TypeEnum::Club:
				std::cout << "[Club] "; break;
			default: break;
			}

			std::cout << packet.CharacterName << ": " << packet.Message << std::endl;
		}
	}
}
