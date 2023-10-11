#pragma once

namespace Maple
{
	namespace Game
	{
		struct CharacterEquipment;
	}
}

namespace Networking
{
	namespace Packets
	{
		class SniffHandler;

		void LogEquipment(SniffHandler* handler, const Maple::Game::CharacterEquipment& equipment);
	}
}