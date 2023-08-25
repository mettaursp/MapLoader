#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>

#include <tinyxml2/tinyxml2.h>

namespace fs = std::filesystem;

namespace OutputSchema
{
	struct SchemaClass;
}

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

	struct PacketDataBit
	{
		std::string Name;
		std::string Output;
		std::string Target;
	};

	struct PacketData
	{
		size_t Index = 0;
		std::string Name;
		const PacketType* Type = nullptr;
		bool Referenced = false;
		bool HasBitOutputs = false;
		bool Read = true;
		std::string Output;
		std::string Target;
		std::string Index;

		std::vector<PacketDataBit> Flags;
		std::unordered_map<size_t, std::string> EnumNames;
	};

	struct PacketRead
	{
		size_t Index = 0;
		size_t DataIndex = 0;
		std::string Name;
	};

	struct PacketFunction
	{
		size_t Index = 0;
		size_t DataIndex = 0;
		std::string Name;
		std::vector<size_t> ParamDataIndices;
	};

	enum class PacketInfoType : unsigned char
	{
		Data,
		Condition,
		Output,
		OutputMember,
		Array,
		Function,
		ValueWrite,
		Validation,
		ArrayOutput,
		DataRead
	};

	enum class PacketInfoComparison : unsigned char
	{
		Equal,
		NotEqual
	};

	struct PacketCondition
	{
		size_t DataIndex = (size_t)-1;
		unsigned char BitIndex = 0xFF;
		size_t Value = 0;
		PacketInfoComparison Comparison = PacketInfoComparison::Equal;
		size_t RegionEnd = 0;
	};

	struct PacketArray
	{
		enum class TypeEnum
		{
			For,
			While
		};

		size_t DataIndex = (size_t)-1;
		size_t OutputIndex = (size_t)-1;
		std::string Output;
		std::string Target;
		std::string Name;
		TypeEnum Type = TypeEnum::For;
		size_t RegionEnd = 0;
	};

	struct PacketOutput
	{
		size_t OutputIndex = (size_t)-1;
		const OutputSchema::SchemaClass* Class = nullptr;
		std::string TypeName;
		std::string SchemaName;
		std::string Name;
		bool ReturnOnFinish = true;
	};

	struct PacketOutputMember
	{
		size_t OutputMemberIndex = (size_t)-1;
		std::string Output;
		std::string Target;
		size_t RegionEnd = 0;
	};

	struct PacketInfo
	{
		PacketInfoType Type = PacketInfoType::Data;
		size_t Index = (size_t)-1;
		size_t StackDepth = (size_t)-1;
	};

	struct PacketOpcode
	{
		unsigned short Value = 0;
		std::string Name;
		bool IsServer = false;

		std::vector<PacketData> Data;
		std::vector<PacketCondition> Conditions;
		std::vector<PacketOutput> Outputs;
		std::vector<PacketOutputMember> OutputMembers;
		std::vector<PacketArray> Arrays;
		std::vector<PacketRead> Reads;
		std::vector<PacketFunction> Functions;
		std::vector<PacketInfo> Layout;
	};

	struct PacketOpcodeReference
	{
		unsigned short Value = 0;
		int TargetVersion = 0;
		unsigned short TargetOpcode = 0;
		bool RemoveReference = false;
	};

	struct PacketVersion
	{
		unsigned short Version = 0;
		bool InheritPrevious = true;
		std::unordered_map<unsigned short, PacketOpcode> ServerOpcodes;
		std::unordered_map<unsigned short, PacketOpcode> ClientOpcodes;
		std::unordered_map<unsigned short, PacketOpcodeReference> ServerOpcodeReferences;
		std::unordered_map<unsigned short, PacketOpcodeReference> ClientOpcodeReferences;
		std::unordered_set<unsigned short> DoNotInheritServer;
		std::unordered_set<unsigned short> DoNotInheritClient;
	};

	extern std::unordered_map<unsigned short, PacketVersion> PacketVersions;

	struct DataResult
	{
		bool Found = false;
		size_t DataIndex = (size_t)-1;
	};

	struct OpcodeParser
	{
		struct NodeStackEntry
		{
			tinyxml2::XMLElement* Element = nullptr;
			size_t ConditionIndex = (size_t)-1;
			size_t ArrayIndex = (size_t)-1;
			size_t OutputMemberIndex = (size_t)-1;
			size_t StartIndex = (size_t)-1;
		};

		std::string FileName;
		PacketOpcode& Opcode;
		std::vector<NodeStackEntry> NodeStack;
		//std::vector<size_t> StackDepths = { };

		DataResult FindDataReference(const std::string_view& name, size_t index = (size_t)-1) const;
		void ReadData(tinyxml2::XMLElement* element);
		void ReadDataRead(tinyxml2::XMLElement* element);
		void ReadCondition(tinyxml2::XMLElement* element);
		void ReadArray(tinyxml2::XMLElement* element);
		void ReadFunction(tinyxml2::XMLElement* element);
		void ReadOutput(tinyxml2::XMLElement* element);
		void ReadOutputMember(tinyxml2::XMLElement* element);
		void Read(tinyxml2::XMLElement* element);
	};

	void readSchema(const fs::path& filePath);
	void readSchemas(const fs::path& directory);
	void generateParsers();

	template <typename T>
	concept String = requires(T param)
	{
		{ std::is_same_v<T, std::string> };
	};

	void generateHandler(const std::string& name);

	template <String... T>
	void generateHandlers(const T&... handlers)
	{
		(generateHandler(handlers), ...);
	}
}