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
		std::vector<std::string> CanCastTo;
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
		std::string Value;
		std::string IteratorName;

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
		Buffer,
		BlockFunction,
		ArraySize,
		Discard,
		ValueWrite,
		Validation,
		ArrayOutput,
		DataRead
	};

	enum class PacketInfoComparison : unsigned char
	{
		Equal,
		NotEqual,
		Between,
		NotBetween,
		None
	};

	struct PacketCondition
	{
		size_t DataIndex = (size_t)-1;
		unsigned char BitIndex = 0xFF;
		size_t Value = 0;
		size_t Value2 = 0;
		PacketInfoComparison Comparison = PacketInfoComparison::Equal;
		bool IsElse = false;
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
		std::string Output;
		std::string Target;
		std::string Name;
		TypeEnum Type = TypeEnum::For;
		size_t RegionEnd = 0;
	};

	struct PacketArraySize
	{
		size_t DataIndex = (size_t)-1;
		std::string Output;
		std::string Target;
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

	struct PacketBuffer
	{
		size_t BufferIndex = (size_t)-1;
		size_t BufferSizeDataIndex = (size_t)-1;
		size_t IsDeflatedDataIndex = (size_t)-1;
		size_t RegionEnd = 0;
		std::string Output;
		std::string Target;
	};

	struct PacketBlockFunction
	{
		size_t BlockFunctionIndex = (size_t)-1;
		std::string Name;
		std::string Output;
		std::string Target;
		unsigned int Version = 0;
		std::vector<size_t> Arguments;
	};

	struct PacketInfo
	{
		PacketInfoType Type = PacketInfoType::Data;
		size_t Index = (size_t)-1;
		size_t StackDepth = (size_t)-1;
	};

	struct PacketOpcode
	{
		struct Parameter
		{
			std::string Name;
			std::string Type;
			std::string Schema;
		};

		unsigned short Value = 0;
		std::string Name;
		bool IsServer = false;

		bool IsBlock = false;
		bool BlockOutputInitialized = false;
		Parameter BlockOutput;

		std::vector<PacketData> Data;
		std::vector<PacketCondition> Conditions;
		std::vector<PacketOutput> Outputs;
		std::vector<PacketOutputMember> OutputMembers;
		std::vector<PacketArray> Arrays;
		std::vector<PacketArraySize> ArraySizes;
		std::vector<PacketRead> Reads;
		std::vector<PacketFunction> Functions;
		std::vector<PacketBuffer> Buffers;
		std::vector<PacketBlockFunction> BlockFunctions;
		std::vector<PacketInfo> Layout;
		std::vector<Parameter> Parameters;
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
		std::unordered_map<std::string, PacketOpcode> BlockData;
		std::vector<PacketOpcode*> Blocks;
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

	const bool PrintGeneratedOpcodes = false;

	struct OpcodeParser
	{
		struct NodeStackEntry
		{
			tinyxml2::XMLElement* Element = nullptr;
			size_t ConditionIndex = (size_t)-1;
			size_t ArrayIndex = (size_t)-1;
			size_t OutputMemberIndex = (size_t)-1;
			size_t BufferIndex = (size_t)-1;
			size_t StartIndex = (size_t)-1;
		};

		std::string FileName;
		PacketOpcode& Opcode;
		std::vector<NodeStackEntry> NodeStack;

		DataResult FindDataReference(const std::string_view& name, size_t index = (size_t)-1) const;
		void ReadData(tinyxml2::XMLElement* element);
		void ReadDataRead(tinyxml2::XMLElement* element);
		void ReadCondition(tinyxml2::XMLElement* element);
		void ReadArray(tinyxml2::XMLElement* element);
		void ReadArraySize(tinyxml2::XMLElement* element);
		void ReadFunction(tinyxml2::XMLElement* element);
		void ReadOutput(tinyxml2::XMLElement* element);
		void ReadOutputMember(tinyxml2::XMLElement* element);
		void ReadBuffer(tinyxml2::XMLElement* element);
		void Read(tinyxml2::XMLElement* element);
		void Print();
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