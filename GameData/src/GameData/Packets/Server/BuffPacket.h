#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BuffPacket
			{
				enum class ModeEnum
				{
					Add = 0,
					Remove = 1,
					Update = 2
				};
				
				ModeEnum Mode = ModeEnum::Add;
				int TargetActor = 0;
				int InstanceId = 0;
				bool UpdateEffect = false;
				int StartTime = 0;
				int EndTime = 0;
				int EffectId = 0;
				short EffectLevel = 0;
				int Stacks = 0;
				bool Enabled = false;
				bool UpdateShield = false;
				long long ShieldHealth = 0;
			};
		}
	}
}
