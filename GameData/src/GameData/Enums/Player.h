#pragma once

namespace Enum
{
	enum class JobTier : unsigned short
	{
	};
	enum class Gender : unsigned char
	{
		Male = 0,
		Female = 1,
		Both = 2
	};
	enum class JobId : unsigned short
	{
	};
	enum class JobCode : unsigned short
	{
		None = 0,
		Beginner = 1,
		Knight = 10,
		Berserker = 20,
		Wizard = 30,
		Archer = 40,
		Priest = 50,
		HeavyGunner = 60,
		Thief = 70,
		Assassin = 80,
		Runeblade = 90,
		Striker = 100,
		Soulbinder = 110,
		GameMaster = 999
	};
}
