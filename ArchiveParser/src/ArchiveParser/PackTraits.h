#pragma once

#include "ArchiveKeys.h"

/*
* Using keys & parsing strategy from https://github.com/Wunkolo/Maple2Tools & http://forum.xentax.com/viewtopic.php?f=10&t=18090
*/

enum class PackVersion
{
	MS2F,
	NS2F,
	OS2F,
	PS2F
};

#pragma pack( push, 1 )

struct PackStreamVer1 // MS2F
{
public:
	std::uint32_t Pad;                    // Always zero

	std::uint64_t FATCompressedSize;      // DEFLATE length
	std::uint64_t FATEncodedSize;         // Base64 length

	std::uint64_t FileListSize;           // Uncompressed size
	std::uint64_t FileListCompressedSize; // DEFLATE length
	std::uint64_t FileListEncodedSize;    // Base64 length

	std::uint64_t TotalFiles;             // Total Files
	std::uint64_t FATSize;                // Uncompressed size
};
static_assert(
	sizeof(PackStreamVer1) == 0x3C,
	"sizeof(PackStreamVer1) != 0x3C"
	);

struct PackStreamVer2 // NS2F
{
public:
	std::uint32_t TotalFiles;             // Total Files

	std::uint64_t FATCompressedSize;      // DEFLATE length
	std::uint64_t FATEncodedSize;         // Base64 length
	std::uint64_t FileListSize;           // Uncompressed size

	std::uint64_t FileListCompressedSize; // DEFLATE length
	std::uint64_t FileListEncodedSize;    // Base64 length
	std::uint64_t FATSize;                // Uncompressed size
};
static_assert(
	sizeof(PackStreamVer2) == 0x34,
	"sizeof(PackStreamVer2) != 0x34"
	);

struct PackStreamVer3 // OS2F/PS2F
{
	std::uint32_t TotalFiles;             // Total Files
	std::uint32_t Pad;                    // Always Zero

	std::uint64_t FATCompressedSize;      // DEFLATE length
	std::uint64_t FATEncodedSize;         // Base64 length

	std::uint64_t FileListCompressedSize; // DEFLATE length
	std::uint64_t FileListEncodedSize;    // Base64 length
	std::uint64_t FileListSize;           // Uncompressed size

	std::uint64_t FATSize;                // Uncompressed size
};
static_assert(
	sizeof(PackStreamVer3) == 0x38,
	"sizeof(PackStreamVer3) != 0x38"
	);

enum class CompressionType : std::uint32_t
{
	None = 0,
	Deflate = 0xEE000009,
	Png = 0xEE000000,
	Usm = 0xFF000000
};

struct PackFileHeaderVer1 // MS2f
{
public:
	std::uint32_t Pad1;
	std::uint32_t FileIndex;
	CompressionType Compression;
	std::uint32_t Pad2;
	std::uint64_t Offset;
	std::uint64_t EncodedSize;
	std::uint64_t CompressedSize;
	std::uint64_t Size;
};
static_assert(
	sizeof(PackFileHeaderVer1) == 0x30,
	"sizeof(PackFileHeaderVer1) != 0x30"
	);

struct PackFileHeaderVer2 // NS2F
{
public:
	CompressionType Compression;
	std::uint32_t FileIndex;
	std::uint32_t EncodedSize;
	std::uint64_t CompressedSize;
	std::uint64_t Size;
	std::uint64_t Offset;
};
static_assert(
	sizeof(PackFileHeaderVer2) == 0x24,
	"sizeof(PackFileHeaderVer2) != 0x24"
	);

struct PackFileHeaderVer3 // OS2F/PS2F
{
public:
	CompressionType Compression;
	std::uint32_t FileIndex;
	std::uint32_t EncodedSize;
	std::uint32_t Pad;
	std::uint64_t CompressedSize;
	std::uint64_t Size;
	std::uint64_t Offset;
};
static_assert(
	sizeof(PackFileHeaderVer3) == 0x28,
	"sizeof(PackFileHeaderVer3) != 0x28"
	);

template <PackVersion Version>
struct PackTraits;

template <>
struct PackTraits<PackVersion::MS2F>
{
	static constexpr PackVersion Version = PackVersion::MS2F;
	static constexpr auto& IV_LUT = Archive::MS2F_IV_LUT;
	static constexpr auto& Key_LUT = Archive::MS2F_Key_LUT;
	typedef PackStreamVer1 StreamType;
	typedef PackFileHeaderVer1 FileHeaderType;
};

template <>
struct PackTraits<PackVersion::NS2F>
{
	static constexpr PackVersion Version = PackVersion::NS2F;
	static constexpr auto& IV_LUT = Archive::NS2F_IV_LUT;
	static constexpr auto& Key_LUT = Archive::NS2F_Key_LUT;
	typedef PackStreamVer2 StreamType;
	typedef PackFileHeaderVer2 FileHeaderType;
};

template <>
struct PackTraits<PackVersion::OS2F>
{
	static constexpr PackVersion Version = PackVersion::OS2F;
	static constexpr auto& IV_LUT = Archive::OS2F_IV_LUT;
	static constexpr auto& Key_LUT = Archive::OS2F_Key_LUT;
	typedef PackStreamVer3 StreamType;
	typedef PackFileHeaderVer3 FileHeaderType;
};

template <>
struct PackTraits<PackVersion::PS2F>
{
	static constexpr PackVersion Version = PackVersion::PS2F;
	static constexpr auto& IV_LUT = Archive::PS2F_IV_LUT;
	static constexpr auto& Key_LUT = Archive::PS2F_Key_LUT;
	typedef PackStreamVer3 StreamType;
	typedef PackFileHeaderVer3 FileHeaderType;
};

#pragma pack(pop)