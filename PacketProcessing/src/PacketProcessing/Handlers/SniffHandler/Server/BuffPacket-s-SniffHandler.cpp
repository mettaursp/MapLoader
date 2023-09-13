#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet)
		{
			if (!Field.CurrentMap || packet.Effect.InstanceId == Enum::EffectInstanceId::Null || packet.Effect.TargetId == Enum::ActorId::Null)
			{
				return;
			}

			const auto actorEntry = Field.Actors.find(packet.Effect.TargetId);

			PrintEffect effectRef = { Field, packet.Effect, packet.Effect.TargetId };

			if (actorEntry == Field.Actors.end())
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				//if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					//FoundUnknownValue();

					const char* messages[] = {
						"adding ",
						"removing ",
						"updating "
					};
					const char* modifierMessages[] = {
						" to unregistered actor ",
						" from unregistered actor ",
						" on unregistered actor "
					};

					std::cout << TimeStamp << messages[(int)packet.Mode] << effectRef << modifierMessages[(int)packet.Mode] << (unsigned int)packet.Effect.TargetId << std::endl;
				}

				return;
			}

			Actor& actor = actorEntry->second;

			const auto entry = actor.EffectIndices.find(packet.Effect.InstanceId);

			PrintEffect actorEffectRef = PrintEffect{ Field, entry == actor.EffectIndices.end() ? effectRef.Effect : actor.Effects[entry->second], packet.Effect.TargetId };

			if (packet.Mode == Server::BuffPacket::ModeEnum::Add)
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					//std::cout << "adding " << actorEffectRef << " to " << PrintActor{ Field, packet.Effect.TargetId } << std::endl;
				}

				actor.AddEffect(*this, packet.Effect);

				return;
			}

			if (packet.Mode == Server::BuffPacket::ModeEnum::Remove)
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					//std::cout << "removing " << actorEffectRef << " from " << PrintActor{ Field, packet.Effect.TargetId } << std::endl;
				}

				actor.RemoveEffect(*this, packet.Effect);

				return;
			}

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "updating ";

				if (packet.UpdateEffect)
				{
					std::cout << (packet.UpdateShield ? "stats and shield" : "stats");
				}
				else if (packet.UpdateEffect)
				{
					std::cout << "shield";
				}
				else
				{
					std::cout << "nothing";
				}

				std::cout << " on " << actorEffectRef << std::endl;// << " on " << PrintActor{ Field, packet.Effect.TargetId } << std::endl;
			}

			if (packet.UpdateEffect)
			{
				actor.UpdateEffect(*this, packet.Effect.InstanceId, packet.Effect.Stats, packet.Effect.Enabled);
			}

			if (packet.UpdateShield)
			{
				actor.UpdateEffect(*this, packet.Effect.InstanceId, packet.Effect.ShieldHealth);
			}
		}
	}
}
