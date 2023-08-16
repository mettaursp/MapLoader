#include "PacketOutput.h"

#include <iostream>
#include <string>

namespace Networking
{
	namespace Packets
	{
		std::string toString(std::wstring wstr)
		{
			std::vector<char> buf(wstr.size());
			std::use_facet<std::ctype<wchar_t>>(std::locale{}).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());

			return std::string(buf.data(), buf.size());
		}

		template <>
		void PacketParsed<Client::ResponseHeartbeatPacket>(const Client::ResponseHeartbeatPacket& packet)
		{

		}

		template <>
		void PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet)
		{

		}

		template <>
		void PacketParsed<Client::SkillCancelPacket>(const Client::SkillCancelPacket& packet)
		{
		
		}
		
		template <>
		void PacketParsed<Client::SkillCastPacket>(const Client::SkillCastPacket& packet)
		{
			
		}
		
		template <>
		void PacketParsed<Client::SkillSyncTickPacket>(const Client::SkillSyncTickPacket& packet)
		{
		
		}
		
		template <>
		void PacketParsed<Client::SkillSyncDamagePacket>(const Client::SkillSyncDamagePacket& packet)
		{
		
		}
		
		template <>
		void PacketParsed<Client::SkillDamagePacket>(const Client::SkillDamagePacket& packet)
		{
		
		}
		
		template <>
		void PacketParsed<Client::SkillRegionSkillPacket>(const Client::SkillRegionSkillPacket& packet)
		{
		
		}
		
		template <>
		void PacketParsed<Client::SkillSyncPacket>(const Client::SkillSyncPacket& packet)
		{
		
		}


		template <>
		void PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet)
		{

		}

		template <>
		void PacketParsed<Client::SystemInfoPacket>(const Client::SystemInfoPacket& packet)
		{

		}

		template <>
		void PacketParsed<Client::RequestQuitPacket>(const Client::RequestQuitPacket& packet)
		{

		}

		template <>
		void PacketParsed<Server::UserChatPacket>(const Server::UserChatPacket& packet)
		{
			return;
		
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
			
			std::cout << toString(packet.CharacterName) << ": " << toString(packet.Message) << std::endl;
		}

		template <>
		void PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet)
		{

		}
	}
}
