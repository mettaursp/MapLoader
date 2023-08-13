#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include <tinyxml2/tinyxml2.h>

namespace fs = std::filesystem;

namespace PacketSchema
{
	struct PacketType
	{
		std::string Name;
		std::string TypeName;
		std::string DefaultValue;
		size_t Size = 0;
	};

	extern const std::unordered_map<std::string, PacketType> PacketTypes;

	struct PacketData
	{
		size_t Index = 0;
		std::string Name;
		const PacketType* Type = nullptr;

		std::vector<std::string> BitNames;
		std::unordered_map<size_t, std::string> EnumNames;
	};

	enum class PacketInfoType : unsigned char
	{
		Data,
		Condition
	};

	enum class PacketInfoComparison : unsigned char
	{
		Equal
	};

	struct PacketCondition
	{
		size_t DataIndex = (size_t)-1;
		unsigned char BitIndex = 0xFF;
		size_t Value = 0;
		PacketInfoComparison Comparison = PacketInfoComparison::Equal;
		size_t RegionEnd = 0;
	};

	struct PacketInfo
	{
		PacketInfoType Type = PacketInfoType::Data;
		size_t Index = (size_t)-1;
	};

	struct PacketOpcode
	{
		short Value = 0;
		std::string Name;

		std::vector<PacketData> Data;
		std::vector<PacketCondition> Conditions;
		std::vector<PacketInfo> Layout;
	};

	struct PacketVersion
	{
		int Version = 0;
		std::unordered_map<unsigned short, PacketOpcode> ServerOpcodes;
		std::unordered_map<unsigned short, PacketOpcode> ClientOpcodes;
	};

	extern std::unordered_map<unsigned short, PacketVersion> PacketVersions;

	struct OpcodeParser
	{
		struct NodeStackEntry
		{
			tinyxml2::XMLElement* Element = nullptr;
			size_t ConditionIndex = (size_t)-1;
			size_t StartIndex = (size_t)-1;
		};

		std::string FileName;
		PacketOpcode& Opcode;
		std::vector<NodeStackEntry> NodeStack;
		std::vector<size_t> StackDepths = { };

		void ReadData(tinyxml2::XMLElement* element);
		void ReadCondition(tinyxml2::XMLElement* element);
		void Read(tinyxml2::XMLElement* element);
	};

	void readSchema(const fs::path& filePath);
	void readSchemas(const fs::path& directory);
	void generateParsers();
}