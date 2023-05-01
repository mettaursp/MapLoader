#pragma once

/*
* Using keys & parsing strategy from https://github.com/Wunkolo/Maple2Tools & http://forum.xentax.com/viewtopic.php?f=10&t=18090
*/

#include <cmath>

struct evp_cipher_ctx_st;

namespace Archive
{
	extern const std::uint8_t MS2F_Key_LUT[128][32];
	extern const std::uint8_t MS2F_IV_LUT[128][16];

	extern const std::uint8_t NS2F_Key_LUT[128][32];
	extern const std::uint8_t NS2F_IV_LUT[128][16];

	extern const std::uint8_t OS2F_Key_LUT[128][32];
	extern const std::uint8_t OS2F_IV_LUT[128][16];

	extern const std::uint8_t PS2F_Key_LUT[128][32];
	extern const std::uint8_t PS2F_IV_LUT[128][16];
}