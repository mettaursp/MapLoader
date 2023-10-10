#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>
#include <string>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentWritePlayDialogPacket
			{
			};
			
			struct PlayInstrumentEffectPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
			
			struct PlayInstrumentViewMusicPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::string MusicCode;
			};
			
			struct PlayInstrumentUpdateScoreUsesPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				int RemainingUses = 0;
			};
			
			struct PlayInstrumentCreateScoreResponsePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct PlayInstrumentPlayNotePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				int MidiNote = 0;
			};
			
			struct PlayInstrumentStartScorePacket
			{
				bool IsCustom = false;
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Vector3S InstrumentPosition;
				int InstrumentTick = 0;
				int GMId = 0;
				int PercussionId = 0;
				std::string MusicCode;
				std::wstring FileName;
			};
			
			struct PlayInstrumentStopScorePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
			
			struct PlayInstrumentStopImprovisePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
			
			struct PlayInstrumentLeaveEnsemblePacket
			{
			};
			
			struct PlayInstrumentStartImprovisePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Vector3S InstrumentPosition;
				int GMId = 0;
				int PercussionId = 0;
			};
		}
	}
}
