#include "PacketSchema.h"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <stdlib.h>
#include <string>

#include "OutputSchema.h"
#include "ModuleWriter.h"

namespace PacketSchema
{
	const std::unordered_set<std::string> NumericTypes = {
		"bool",
		"unsigned char",
		"signed char",
		"char",
		"unsigned short",
		"signed short",
		"short",
		"unsigned int",
		"signed int",
		"int",
		"unsigned long long",
		"signed long long",
		"long long",
		"float",
		"double"
	};
	const std::unordered_map<std::string, PacketType> PacketTypes = {
		{ "bool", { "bool", "bool", "false", 1 }},
		{ "ubyte", { "ubyte", "unsigned char", "0", 1 }},
		{ "sbyte", { "sbyte", "signed char", "0", 1 }},
		{ "byte", { "byte", "unsigned char", "0", 1 }},
		{ "char", { "char", "char", "0", 1 }},
		{ "ushort", { "ushort", "unsigned short", "0", 2 }},
		{ "short", { "short", "short", "0", 2 }},
		{ "uint", { "uint", "unsigned int", "0", 4 }},
		{ "int", { "int", "int", "0", 4 }},
		{ "ulong", { "ulong", "unsigned long long", "0", 8 }},
		{ "long", { "long", "long long", "0", 8 }},
		{ "float", { "float", "float", "0", 4  }},
		{ "double", { "double", "double", "0", 8  }},
		{ "string", { "string", "std::string", "", 0 }},
		{ "wstring", { "wstring", "std::wstring", "", 0 }},
		{ "Vector3S", { "Vector3S", "Vector3S", "", 0 }},
		{ "Vector3Short", { "Vector3Short", "Vector3Short", "", 0, { "Vector3S" }}},
		{ "Vector3Byte", { "Vector3Byte", "Vector3Byte", "", 0, { "Vector3S" }}},
		{ "vector", { "vector", "std::vector", "", 0 }},
		{ "Color4I", { "Color4I", "Color4I_BGRA", "", 0, { "Color4I" }}}
	};

	std::unordered_map<unsigned short, PacketVersion> PacketVersions;

	struct DataOutput
	{
		std::string Name;
		const PacketOutput* Output = nullptr;
		const OutputSchema::SchemaMember* Member = nullptr;
		const OutputSchema::SchemaClass* Class = nullptr;
		bool IsIndexed = false;
	};

	struct StackEntry
	{
		size_t StartIndex = (size_t)-1;
		size_t EndIndex = (size_t)-1;
		DataOutput Output;
		bool IsLoop = false;
		bool IncrementLoopCounter = false;
		std::string LoopParamName;
		char LoopIndex = 0;
	};

	DataResult findDataReference(const PacketOpcode& opcode, const std::vector<StackEntry>& stack, const std::string_view& name, size_t index)
	{
		index = index < opcode.Layout.size() ? index : opcode.Layout.size() - 1;

		const PacketInfo& current = index < opcode.Layout.size() ? opcode.Layout[index] : opcode.Layout.back();
		
		DataResult result;

		for (size_t i = 0; !result.Found && i < index; ++i)
		{
			const PacketInfo& info = opcode.Layout[i];

			if (info.Type != PacketInfoType::Data)
			{
				continue;
			}

			if (info.StackDepth > current.StackDepth)
			{
				continue;
			}

			size_t depthValue = info.StackDepth - (opcode.IsBlock ? 1 : 2);
			size_t startIndex = depthValue > stack.size() ? 0 : stack[depthValue].StartIndex;

			if (startIndex > i)
			{
				continue;
			}

			const PacketInfo& stackStartInfo = opcode.Layout[i];

			size_t regionEnd = opcode.Layout.size();

			switch (stackStartInfo.Type)
			{
			case PacketInfoType::Condition: regionEnd = opcode.Conditions[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::OutputMember: regionEnd = opcode.OutputMembers[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::Array: regionEnd = opcode.Arrays[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::Buffer: regionEnd = opcode.Buffers[stackStartInfo.Index].RegionEnd; break;
			}

			if (regionEnd <= index)
			{
				continue;
			}

			const PacketData& data = opcode.Data[info.Index];

			if (data.Name == name)
			{
				return { true, i };
			}
		}

		for (size_t i = 0; i < opcode.Parameters.size(); ++i)
		{
			if (opcode.Parameters[i].Name == name)
			{
				return { true, (size_t)-1 - opcode.Parameters.size() + i };
			}
		}

		return { false, (size_t)-1 };
	}

	DataResult OpcodeParser::FindDataReference(const std::string_view& name, size_t index) const
	{
		index = index < Opcode.Layout.size() ? index : Opcode.Layout.size() - 1;

		const PacketInfo& current = index < Opcode.Layout.size() ? Opcode.Layout[index] : Opcode.Layout.back();

		DataResult result;

		for (size_t i = 0; !result.Found && i < Opcode.Layout.size(); ++i)
		{
			const PacketInfo& info = Opcode.Layout[i];

			if (info.Type != PacketInfoType::Data)
			{
				continue;
			}

			if (info.StackDepth > current.StackDepth)
			{
				continue;
			}

			size_t startIndex = NodeStack[info.StackDepth - 1].StartIndex;

			if (startIndex > i)
			{
				continue;
			}

			const PacketInfo& stackStartInfo = Opcode.Layout[i];

			size_t regionEnd = Opcode.Layout.size();

			switch (stackStartInfo.Type)
			{
			case PacketInfoType::Condition: regionEnd = Opcode.Conditions[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::OutputMember: regionEnd = Opcode.OutputMembers[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::Array: regionEnd = Opcode.Arrays[stackStartInfo.Index].RegionEnd; break;
			case PacketInfoType::Buffer: regionEnd = Opcode.Buffers[stackStartInfo.Index].RegionEnd; break;
			}

			if (regionEnd <= index)
			{
				continue;
			}

			const PacketData& data = Opcode.Data[info.Index];

			if (data.Name == name)
			{
				return { true, i };
			}
		}

		for (size_t i = 0; i < Opcode.Parameters.size(); ++i)
		{
			if (Opcode.Parameters[i].Name == name)
			{
				return { true, (size_t)-1 - Opcode.Parameters.size() + i };
			}
		}

		return { false, (size_t)-1 };
	}

	void OpcodeParser::ReadOutput(tinyxml2::XMLElement* element)
	{
		PacketOutput& output = Opcode.Outputs.back();

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				output.Name = value;

				continue;
			}

			if (strcmp(name, "type") == 0)
			{
				output.TypeName = value;

				continue;
			}

			if (strcmp(name, "schemaName") == 0)
			{
				output.SchemaName = value;

				continue;
			}

			if (strcmp(name, "noReturn") == 0)
			{
				output.ReturnOnFinish = strcmp(value, "true") != 0;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in output node" << std::endl;
		}

		OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(output.TypeName, output.SchemaName);

		if (entry.Type == OutputSchema::SchemaEntryType::None)
		{
			std::cout << FileName << ": failed to find type '" << output.TypeName << "' in schema '" << output.SchemaName << "'" << std::endl;

			return;
		}

		if (entry.Type != OutputSchema::SchemaEntryType::Class)
		{
			std::cout << FileName << ": type '" << output.TypeName << "' in schema '" << output.SchemaName << "' isn't a class" << std::endl;

			return;
		}

		output.Class = entry.Class;
	}
	
	void OpcodeParser::ReadOutputMember(tinyxml2::XMLElement* element)
	{
		PacketOutputMember& outputMember = Opcode.OutputMembers.back();

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "output") == 0)
			{
				outputMember.Output = value;

				continue;
			}

			if (strcmp(name, "target") == 0)
			{
				outputMember.Target = value;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in output node" << std::endl;
		}
	}

	void OpcodeParser::ReadDataRead(tinyxml2::XMLElement* element)
	{
		PacketRead& dataRead = Opcode.Reads.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": 1` data '" << value << "' in read node" << std::endl;

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				dataRead.DataIndex = result.DataIndex;
				dataRead.Name = value;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in read node" << std::endl;
		}
	}

	void OpcodeParser::ReadBuffer(tinyxml2::XMLElement* element)
	{
		PacketBuffer& buffer = Opcode.Buffers.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "sizeData") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in buffer node sizeData" << std::endl;

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				buffer.BufferSizeDataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "deflatedData") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in buffer node deflatedData" << std::endl;

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				buffer.IsDeflatedDataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "output") == 0)
			{
				buffer.Output = value;

				continue;
			}

			if (strcmp(name, "target") == 0)
			{
				buffer.Target = value;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in read node" << std::endl;
		}
	}

	void OpcodeParser::ReadFunction(tinyxml2::XMLElement* element)
	{
		PacketFunction& function = Opcode.Functions.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				function.Name = value;

				continue;
			}

			if (strcmp(name, "data") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in function node" << std::endl;

					FindDataReference(value);

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				function.DataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "params") == 0)
			{
				std::string_view valueString = value;

				size_t start = 0;
				size_t i = 0;

				for (i = 0; i <= valueString.size(); ++i)
				{
					if (i < valueString.size() && valueString[i] != ',')
					{
						continue;
					}

					if (start == i)
					{
						start = i + 1;

						continue;
					}

					std::string_view current = { value + start, i - start };

					DataResult paramResult = FindDataReference(current);

					if (!paramResult.Found)
					{
						std::cout << FileName << ": unknown referenced param data '" << current << "' in function node" << std::endl;

						FindDataReference(value);

						continue;
					}

					if (paramResult.DataIndex < Opcode.Layout.size())
					{
						const PacketInfo& info = Opcode.Layout[paramResult.DataIndex];
						PacketData& data = Opcode.Data[info.Index];

						data.Referenced = true;
					}

					function.ParamDataIndices.push_back(paramResult.DataIndex);

					start = i + 1;
				}

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in function node" << std::endl;
		}
	}

	void OpcodeParser::ReadData(tinyxml2::XMLElement* element)
	{
		PacketData& data = Opcode.Data.back();

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				data.Name = value;

				continue;
			}

			if (strcmp(name, "type") == 0)
			{
				auto typeEntry = PacketTypes.find(value);

				if (typeEntry == PacketTypes.end())
				{
					std::cout << FileName << ": unknown type '" << value << "' in data node" << std::endl;

					continue;
				}

				data.Type = &typeEntry->second;

				if (data.Type->Name == "bool")
				{
					data.EnumNames[0] = "false";
					data.EnumNames[1] = "true";
				}

				continue;
			}

			if (strcmp(name, "output") == 0)
			{
				data.Output = value;

				continue;
			}

			if (strcmp(name, "target") == 0)
			{
				data.Target = value;

				continue;
			}

			if (strcmp(name, "value") == 0)
			{
				data.Value = value;

				continue;
			}

			if (strcmp(name, "iterator") == 0)
			{
				data.IteratorName = value;

				continue;
			}

			if (strcmp(name, "doRead") == 0)
			{
				data.Read = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in data node" << std::endl;
		}

		if (data.Name.size() == 0)
		{
			std::cout << FileName << ": data given empty name" << std::endl;
		}

		if (data.Type == nullptr)
		{
			std::cout << FileName << ": data '" << data.Name << "' has no type" << std::endl;
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "enum") == 0)
			{
				const tinyxml2::XMLAttribute* nameAttrib = child->FindAttribute("name");
				const tinyxml2::XMLAttribute* valueAttrib = child->FindAttribute("value");

				if (nameAttrib == nullptr || valueAttrib == nullptr)
				{
					if (nameAttrib == nullptr)
					{
						std::cout << FileName << ": enum node missing name attribute" << std::endl;
					}

					if (valueAttrib == nullptr)
					{
						std::cout << FileName << ": enum node missing value attribute" << std::endl;
					}

					continue;
				}

				std::string_view valueData = valueAttrib->Value();

				bool isHex = valueData.size() > 2 && valueData[0] == '0' && (valueData[1] == 'x' || valueData[1] == 'X');

				size_t value = isHex ? (size_t)strtoll (valueData.data() + 2, nullptr, 16) : (size_t)atoll(valueData.data());

				data.EnumNames[value] = nameAttrib->Value();

				continue;
			}

			if (strcmp(name, "bit") == 0)
			{
				const tinyxml2::XMLAttribute* nameAttrib = child->FindAttribute("name");
				const tinyxml2::XMLAttribute* bitIndexAttrib = child->FindAttribute("bitIndex");
				const tinyxml2::XMLAttribute* outputAttrib = child->FindAttribute("output");

				if (nameAttrib == nullptr || bitIndexAttrib == nullptr)
				{
					if (nameAttrib == nullptr)
					{
						std::cout << FileName << ": bit node missing name attribute" << std::endl;
					}

					if (bitIndexAttrib == nullptr)
					{
						std::cout << FileName << ": bit node missing bitIndex attribute" << std::endl;
					}

					continue;
				}

				size_t bitIndex = (size_t)atoi(bitIndexAttrib->Value());

				if (bitIndex >= data.Flags.size())
				{
					data.Flags.resize(bitIndex + 1);
				}

				data.Flags[bitIndex].Name = nameAttrib->Value();

				if (outputAttrib != nullptr)
				{
					data.HasBitOutputs = true;

					data.Flags[bitIndex].Output = outputAttrib->Value();
				}

				continue;
			}

			std::cout << FileName << ": unknown node '" << name << "' in data node" << std::endl;
		}
	}

	void OpcodeParser::ReadCondition(tinyxml2::XMLElement* element)
	{
		PacketCondition& condition = Opcode.Conditions.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "data") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in condition node" << std::endl;

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];
				}

				condition.DataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "value") == 0)
			{
				std::string_view valueData = value;

				bool isHex = valueData.size() > 2 && valueData[0] == '0' && (valueData[1] == 'x' || valueData[1] == 'X');

				condition.Value = isHex ? (size_t)strtoll(valueData.data() + 2, nullptr, 16) : (size_t)atoll(valueData.data());

				continue;
			}

			if (strcmp(name, "value2") == 0)
			{
				std::string_view valueData = value;

				bool isHex = valueData.size() > 2 && valueData[0] == '0' && (valueData[1] == 'x' || valueData[1] == 'X');

				condition.Value2 = isHex ? (size_t)strtoll(valueData.data() + 2, nullptr, 16) : (size_t)atoll(valueData.data());

				continue;
			}

			if (strcmp(name, "else") == 0)
			{
				condition.IsElse = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "bitIndex") == 0)
			{
				if (result.Found)
				{
					size_t bitIndex = (size_t)atoi(value);

					const PacketData& data = Opcode.Data[Opcode.Layout[condition.DataIndex].Index];

					if (data.Type == nullptr)
					{
						std::cout << FileName << ": setting condition bit on data '" << data.Name << "' with null type" << std::endl;
					}
					else if (bitIndex >= data.Type->Size * 8)
					{
						std::cout << FileName << ": condition bit index set out of bounds of '" << data.Name << "' type '" << data.Type->Name << "' at index " << bitIndex << std::endl;
					}

					condition.BitIndex = (unsigned char)bitIndex;
				}

				continue;
			}

			if (strcmp(name, "comparison") == 0)
			{
				if (strcmp(value, "equal") == 0)
				{
					condition.Comparison = PacketInfoComparison::Equal;
				}
				else if (strcmp(value, "notEqual") == 0)
				{
					condition.Comparison = PacketInfoComparison::NotEqual;
				}
				else if (strcmp(value, "between") == 0)
				{
					condition.Comparison = PacketInfoComparison::Between;
				}
				else if (strcmp(value, "notBetween") == 0)
				{
					condition.Comparison = PacketInfoComparison::NotBetween;
				}
				else if (strcmp(value, "lessThan") == 0)
				{
					condition.Comparison = PacketInfoComparison::LessThan;
				}
				else if (strcmp(value, "greaterThan") == 0)
				{
					condition.Comparison = PacketInfoComparison::GreaterThan;
				}
				else if (strcmp(value, "lessEqual") == 0)
				{
					condition.Comparison = PacketInfoComparison::LessEqual;
				}
				else if (strcmp(value, "greaterEqual") == 0)
				{
					condition.Comparison = PacketInfoComparison::GreaterEqual;
				}
				else if (strcmp(value, "none") == 0)
				{
					condition.Comparison = PacketInfoComparison::None;
				}
				else
				{
					std::cout << FileName << ": unknown comparison type '" << value << "'" << std::endl;
				}

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in data node" << std::endl;
		}

		if (!result.Found && !condition.IsElse)
		{
			std::cout << FileName << ": condition data not found" << std::endl;
		}
	}

	void OpcodeParser::ReadArray(tinyxml2::XMLElement* element)
	{
		PacketArray& array = Opcode.Arrays.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "data") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in array node" << std::endl;

					FindDataReference(value);

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				array.DataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "output") == 0)
			{
				array.Output = value;

				continue;
			}

			if (strcmp(name, "target") == 0)
			{
				array.Target = value;

				continue;
			}

			if (strcmp(name, "name") == 0)
			{
				array.Name = value;

				continue;
			}

			if (strcmp(name, "type") == 0)
			{
				if (strcmp(value, "while") == 0)
				{
					array.Type = PacketArray::TypeEnum::While;
				}

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in data node" << std::endl;
		}

		if (!result.Found)
		{
			std::cout << FileName << ": condition data not found" << std::endl;
		}
	}

	void OpcodeParser::ReadArraySize(tinyxml2::XMLElement* element)
	{
		PacketArraySize& arraySize = Opcode.ArraySizes.back();

		DataResult result;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "data") == 0)
			{
				result = FindDataReference(value);

				if (!result.Found)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in array node" << std::endl;

					FindDataReference(value);

					continue;
				}

				if (result.DataIndex < Opcode.Layout.size())
				{
					const PacketInfo& info = Opcode.Layout[result.DataIndex];
					PacketData& data = Opcode.Data[info.Index];

					data.Referenced = true;
				}

				arraySize.DataIndex = result.DataIndex;

				continue;
			}

			if (strcmp(name, "output") == 0)
			{
				arraySize.Output = value;

				continue;
			}

			if (strcmp(name, "target") == 0)
			{
				arraySize.Target = value;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in data node" << std::endl;
		}

		if (!result.Found)
		{
			std::cout << FileName << ": condition data not found" << std::endl;
		}
	}

	void OpcodeParser::Read(tinyxml2::XMLElement* element)
	{
		NodeStack.push_back({ element->FirstChildElement() });
		NodeStack.back().StartIndex = 0;

		while (NodeStack.size())
		{
			NodeStackEntry& node = NodeStack.back();
			bool forcePopEarly = false;

			if (node.Element != nullptr)
			{
				const char* name = node.Element->Name();

				if (strcmp(name, "data") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::Data, Opcode.Data.size(), NodeStack.size() });
					Opcode.Data.push_back({ Opcode.Data.size() });

					ReadData(node.Element);
				}
				else if (strcmp(name, "condition") == 0)
				{
					node.ConditionIndex = Opcode.Conditions.size();

					Opcode.Layout.push_back({ PacketInfoType::Condition, Opcode.Conditions.size(), NodeStack.size() });
					Opcode.Conditions.push_back({});

					ReadCondition(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "output") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::Output, Opcode.Outputs.size(), NodeStack.size() });
					Opcode.Outputs.push_back({ Opcode.Outputs.size() });

					ReadOutput(node.Element);
				}
				else if (strcmp(name, "array") == 0)
				{
					node.ArrayIndex = Opcode.Arrays.size();

					Opcode.Layout.push_back({ PacketInfoType::Array, Opcode.Arrays.size(), NodeStack.size() });
					Opcode.Arrays.push_back({});

					ReadArray(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "arraySize") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::ArraySize, Opcode.ArraySizes.size(), NodeStack.size() });
					Opcode.ArraySizes.push_back({});

					ReadArraySize(node.Element);
				}
				else if (strcmp(name, "read") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::DataRead, Opcode.Reads.size(), NodeStack.size() });
					Opcode.Reads.push_back({ Opcode.Reads.size() });

					ReadDataRead(node.Element);
				}
				else if (strcmp(name, "function") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::Function, Opcode.Functions.size(), NodeStack.size() });
					Opcode.Functions.push_back({ Opcode.Functions.size() });

					ReadFunction(node.Element);
				}
				else if (strcmp(name, "discard") == 0)
				{
					Opcode.Layout.push_back({ PacketInfoType::Discard, (size_t)-1, NodeStack.size()});
				}
				else if (strcmp(name, "outputMember") == 0)
				{
					node.OutputMemberIndex = Opcode.OutputMembers.size();

					Opcode.Layout.push_back({ PacketInfoType::OutputMember, Opcode.OutputMembers.size(), NodeStack.size() });
					Opcode.OutputMembers.push_back({ Opcode.OutputMembers.size() });

					ReadOutputMember(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "buffer") == 0)
				{
					node.BufferIndex = Opcode.Buffers.size();

					Opcode.Layout.push_back({ PacketInfoType::Buffer, Opcode.Buffers.size(), NodeStack.size() });
					Opcode.Buffers.push_back({ Opcode.Buffers.size() });

					ReadBuffer(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "useBlock") == 0)
				{
					const tinyxml2::XMLAttribute* nameAttrib = node.Element->FindAttribute("name");
					const tinyxml2::XMLAttribute* versionAttrib = node.Element->FindAttribute("version");
					const tinyxml2::XMLAttribute* outputAttrib = node.Element->FindAttribute("output");
					const tinyxml2::XMLAttribute* targetAttrib = node.Element->FindAttribute("target");
					const tinyxml2::XMLAttribute* argsAttrib = node.Element->FindAttribute("args");

					if (nameAttrib == nullptr || versionAttrib == nullptr)
					{
						if (!nameAttrib)
						{
							std::cout << "block node missing name attribute" << std::endl;
						}

						if (!versionAttrib)
						{
							std::cout << "block node missing version attribute" << std::endl;
						}

						continue;
					}

					Opcode.Layout.push_back({ PacketInfoType::BlockFunction, Opcode.BlockFunctions.size(), NodeStack.size() });
					Opcode.BlockFunctions.push_back({ Opcode.BlockFunctions.size() });

					PacketBlockFunction& blockFunction = Opcode.BlockFunctions.back();

					blockFunction.Name = nameAttrib->Value();
					blockFunction.Version = (unsigned short)atoi(versionAttrib->Value());

					if (outputAttrib)
					{
						blockFunction.Output = outputAttrib->Value();
					}

					if (targetAttrib)
					{
						blockFunction.Output = targetAttrib->Value();
					}

					if (argsAttrib)
					{
						std::string_view paramsValue = argsAttrib->Value();
						size_t start = 0;
						size_t length = 0;
						while (start <= paramsValue.size())
						{
							for (length; start + length < paramsValue.size() && paramsValue[start + length] != ','; ++length);
							if (length == 0)
							{
								++start;
							}
							std::string_view name = { paramsValue.data() + start, length };
							start += length + 1;
							length = 0;

							DataResult result = FindDataReference(name);

							if (!result.Found)
							{
								std::cout << "useBlock node parameter '" << name << "' not found" << std::endl;

								continue;
							}

							blockFunction.Arguments.push_back(result.DataIndex);
						}
					}

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "outputParam") == 0 || strcmp(name, "blockParam") == 0)
				{
					if (!Opcode.IsBlock)
					{
						std::cout << name << "attempt to use node '" << name << "' in non block opcode: " << Opcode.Name << " [0x" << std::hex << Opcode.Value << std::dec << "]" << std::endl;

						continue;
					}

					bool isOutputParam = strcmp(name, "outputParam") == 0;

					const tinyxml2::XMLAttribute* nameAttribute = node.Element->FindAttribute("name");
					const tinyxml2::XMLAttribute* typeAttribute = node.Element->FindAttribute("type");
					const tinyxml2::XMLAttribute* schemaAttribute = node.Element->FindAttribute("schema");

					if ((!isOutputParam && !nameAttribute) || !typeAttribute)
					{
						if (!isOutputParam && !nameAttribute)
						{
							std::cout << name << " of block '" << Opcode.Name << "' missing 'name' attribute" << std::endl;
						}

						if (!typeAttribute)
						{
							std::cout << name << " of block '" << Opcode.Name << "' missing 'type' attribute" << std::endl;
						}

						continue;
					}

					const char* name = nameAttribute ? nameAttribute->Value() : "blockOutput";
					const char* schema = schemaAttribute ? schemaAttribute->Value() : "";

					PacketOpcode::Parameter param = { name, typeAttribute->Value(), schema };

					if (isOutputParam)
					{
						Opcode.BlockOutputInitialized = true;
						Opcode.BlockOutput = param;
					}
					else
					{
						Opcode.Parameters.push_back(param);
					}
				}
				else
				{
					std::cout << FileName << ": unknown node '" << name << "'" << std::endl;
				}
			}

			while (NodeStack.size() && (NodeStack.back().Element == nullptr || forcePopEarly))
			{
				forcePopEarly = false;

				NodeStack.pop_back();

				if (NodeStack.size())
				{
					NodeStackEntry& next = NodeStack.back();

					if (next.ConditionIndex != (size_t)-1)
					{
						Opcode.Conditions[next.ConditionIndex].RegionEnd = Opcode.Layout.size();
					}

					if (next.ArrayIndex != (size_t)-1)
					{
						Opcode.Arrays[next.ArrayIndex].RegionEnd = Opcode.Layout.size();
					}

					if (next.OutputMemberIndex != (size_t)-1)
					{
						Opcode.OutputMembers[next.OutputMemberIndex].RegionEnd = Opcode.Layout.size();
					}

					if (next.BufferIndex != (size_t)-1)
					{
						Opcode.Buffers[next.BufferIndex].RegionEnd = Opcode.Layout.size();
					}

					next.ConditionIndex = (size_t)-1;
					next.ArrayIndex = (size_t)-1;
					next.OutputMemberIndex = (size_t)-1;
					next.BufferIndex = (size_t)-1;
				}
			}

			if (NodeStack.size())
			{
				NodeStack.back().Element = NodeStack.back().Element->NextSiblingElement();
				NodeStack.back().ConditionIndex = (size_t)-1;
				NodeStack.back().ArrayIndex = (size_t)-1;
				NodeStack.back().OutputMemberIndex = (size_t)-1;
				NodeStack.back().BufferIndex = (size_t)-1;
			}
		}
	}

	void OpcodeParser::Print()
	{
		if constexpr (!PrintGeneratedOpcodes)
		{
			return;
		}

		char tabs[32] = { 0 };
		const char* const typeNames[] = {
			"Data",
			"Condition",
			"Output",
			"OutputMember",
			"Array",
			"Function",
			"Buffer",
		};
		const char* const compares[] = {
			"Equal",
			"NotEqual",
			"Between",
			"NotBetween",
			"LessThan",
			"GreaterThan"
		};
		bool compare2[] = {
			false,
			false,
			true,
			true
		};

		const auto indent = [&tabs](size_t depth)
		{
			tabs[0] = '\n';

			for (int i = 0; i <= (int)depth + 1; ++i)
			{
				tabs[i + 1] = i < depth ? '\t' : 0;
			}

			return tabs;
		};

		for (size_t i = 0; i < Opcode.Layout.size(); ++i)
		{
			const auto& layout = Opcode.Layout[i];

			size_t index = layout.Index;

			std::cout << (indent(layout.StackDepth) + 1) << "[" << i << "] " << typeNames[(int)layout.Type] << " <" << layout.StackDepth << ">: " << index;

			switch (layout.Type)
			{
			case PacketInfoType::Data:
				std::cout << indent(layout.StackDepth + 1) << Opcode.Data[index].Type->Name << " " << Opcode.Data[index].Name << " - " << Opcode.Data[index].Output << " [" << Opcode.Data[index].Target << "]";
				break;
			case PacketInfoType::DataRead:
				std::cout << indent(layout.StackDepth + 1) << Opcode.Reads[index].Name << "; Data: [" << Opcode.Reads[index].DataIndex << "]";
				break;
			case PacketInfoType::Condition:
				std::cout << " -> [" << Opcode.Conditions[index].RegionEnd << "]" << indent(layout.StackDepth + 1) << "Data: [" << Opcode.Conditions[index].DataIndex << "]: " << compares[(int)Opcode.Conditions[index].Comparison] << "(" << Opcode.Conditions[index].Value;
				if (compare2[(int)Opcode.Conditions[index].Comparison])
					std::cout << ", " << Opcode.Conditions[index].Value2;
				std::cout << ")";
				break;
			case PacketInfoType::Output:
				std::cout << indent(layout.StackDepth + 1) << Opcode.Outputs[index].Class->Name << " " << Opcode.Outputs[index].Name;
				break;
			case PacketInfoType::OutputMember:
				std::cout << indent(layout.StackDepth + 1) << Opcode.OutputMembers[index].Output << " [" << Opcode.OutputMembers[index].Target << "]";
				break;
			case PacketInfoType::Array:
				std::cout << " -> [" << Opcode.Arrays[index].RegionEnd << "]" << indent(layout.StackDepth + 1) << "Data: [" << Opcode.Arrays[index].DataIndex << "]: " << Opcode.Arrays[index].Output << " [" << Opcode.Arrays[index].Target << "]";
				break;
			case PacketInfoType::Function:
				std::cout << indent(layout.StackDepth + 1) << "Data: [" << Opcode.Functions[index].DataIndex << "]: " << Opcode.Functions[index].Name << "(";
				for (size_t i = 0; i < Opcode.Functions[index].ParamDataIndices.size(); ++i)
				{
					std::cout << "[" << Opcode.Functions[index].ParamDataIndices[i] << "]";
					if (i + 1 < Opcode.Functions[index].ParamDataIndices.size())
						std::cout << ", ";
				}
				std::cout << ")";
				break;
			case PacketInfoType::Buffer:
				std::cout << " -> [" << Opcode.Buffers[index].RegionEnd << "]" << indent(layout.StackDepth + 1) << "Buffer([" << Opcode.Buffers[index].BufferSizeDataIndex << "], [" << Opcode.Buffers[index].IsDeflatedDataIndex << "])";
				break;
			}

			std::cout << std::endl;
		}
	}

	void readSchema(const fs::path& filePath)
	{
		tinyxml2::XMLDocument document;

		document.LoadFile(filePath.string().c_str());

		tinyxml2::XMLElement* root = document.RootElement();

		if (root == nullptr)
		{
			std::cout << "invalid xml " << filePath << std::endl;

			return;
		}

		const tinyxml2::XMLAttribute* versionAttrib = root->FindAttribute("version");

		if (versionAttrib == nullptr)
		{
			return;
		}

		unsigned short version = (unsigned short)atoi(versionAttrib->Value());

		PacketVersion& schema = PacketVersions[version];

		schema.Version = version;

		const tinyxml2::XMLAttribute* inheritAttrib = root->FindAttribute("inheritPrevious");

		if (inheritAttrib != nullptr)
		{
			schema.InheritPrevious = strcmp(inheritAttrib->Value(), "true") == 0;
		}

		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			if (strcmp(child->Name(), "blocks") == 0)
			{
				for (tinyxml2::XMLElement* blockElement = child->FirstChildElement(); blockElement; blockElement = blockElement->NextSiblingElement())
				{
					if (strcmp(blockElement->Name(), "block") != 0)
					{
						std::cout << filePath.string() << ": unknown node '" << blockElement->Name() << "' in blocks" << std::endl;

						continue;
					}

					const tinyxml2::XMLAttribute* nameAttrib = blockElement->FindAttribute("name");
					const tinyxml2::XMLAttribute* paramsAttrib = blockElement->FindAttribute("params");

					if (nameAttrib == nullptr)
					{
						std::cout << filePath.string() << ": opcode node missing name attribute" << std::endl;

						continue;
					}

					const char* name = nameAttrib->Value();

					PacketOpcode& block = schema.BlockData[name];

					schema.Blocks.push_back(&block);

					block.Name = name;
					block.IsServer = false;
					block.IsBlock = true;

					OpcodeParser parser = { filePath.string(), block };

					if constexpr (PrintGeneratedOpcodes)
					{
						std::cout << "Block: " << name << std::endl;
					}

					parser.Read(blockElement);
					parser.Print();
				}

				continue;
			}

			if (strcmp(child->Name(), "source") != 0)
			{
				std::cout << filePath.string() << ": unknown node '" << child->Name() << "' in packetSchema" << std::endl;

				continue;
			}

			const tinyxml2::XMLAttribute* nameAttrib = child->FindAttribute("name");

			if (nameAttrib == nullptr)
			{
				std::cout << filePath.string() << ": source node missing name attribute" << std::endl;

				continue;
			}

			const char* name = nameAttrib->Value();

			bool isServer = strcmp(name, "server") == 0;
			bool isClient = strcmp(name, "client") == 0;

			if (!isServer && !isClient)
			{
				std::cout << filePath.string() << ": source node name is invalid value '" << name << "'" << std::endl;

				continue;
			}

			for (tinyxml2::XMLElement* opcodeElement = child->FirstChildElement(); opcodeElement; opcodeElement = opcodeElement->NextSiblingElement())
			{
				const char* name = opcodeElement->Name();

				if (strcmp(name, "opcodeReference") == 0)
				{
					const tinyxml2::XMLAttribute* valueAttrib = opcodeElement->FindAttribute("value");
					const tinyxml2::XMLAttribute* removeAttrib = opcodeElement->FindAttribute("removeReference");
					const tinyxml2::XMLAttribute* versionAttrib = opcodeElement->FindAttribute("version");
					const tinyxml2::XMLAttribute* opcodeAttrib = opcodeElement->FindAttribute("opcode");

					bool remove = false;

					if (removeAttrib)
					{
						if (!valueAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing version attribute" << std::endl;

							continue;
						}

						remove = strcmp(removeAttrib->Value(), "true") == 0;
					}

					if (!remove && (versionAttrib == nullptr || valueAttrib == nullptr || opcodeAttrib == nullptr))
					{
						if (!versionAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing version attribute" << std::endl;
						}

						if (!valueAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing value attribute" << std::endl;
						}

						if (!opcodeAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing opcode attribute" << std::endl;
						}

						continue;
					}

					unsigned short value = 0;
					unsigned short version = 0;
					unsigned short opcode = 0;

					{
						size_t valueStart = 0;
						const char* valueData = valueAttrib->Value();

						for (size_t i = 0; !valueStart && valueData[i]; ++i)
						{
							if (valueData[i] == 'x')
							{
								valueStart = i + 1;
							}
						}

						if (valueStart == 0)
						{
							value = (unsigned short)atoi(valueData);
						}
						else
						{
							value = (unsigned short)strtol(valueData + valueStart, nullptr, 16);
						}
					}

					if (remove)
					{
						(isServer ? schema.DoNotInheritServer : schema.DoNotInheritClient).insert(value);

						continue;
					}

					version = (unsigned short)atoi(versionAttrib->Value());

					{
						size_t valueStart = 0;
						const char* valueData = opcodeAttrib->Value();

						for (size_t i = 0; !valueStart && valueData[i]; ++i)
						{
							if (valueData[i] == 'x')
							{
								valueStart = i + 1;
							}
						}

						if (valueStart == 0)
						{
							opcode = (unsigned short)atoi(valueData);
						}
						else
						{
							opcode = (unsigned short)strtol(valueData + valueStart, nullptr, 16);
						}
					}

					(isServer ? schema.ServerOpcodeReferences : schema.ClientOpcodeReferences)[value] = { value, version, opcode };

					continue;
				}

				if (strcmp(name, "opcode") != 0)
				{
					continue;
				}

				const tinyxml2::XMLAttribute* nameAttrib = opcodeElement->FindAttribute("name");
				const tinyxml2::XMLAttribute* valueAttrib = opcodeElement->FindAttribute("value");

				if (nameAttrib == nullptr || valueAttrib == nullptr)
				{
					if (!nameAttrib)
					{
						std::cout << filePath.string() << ": opcode node missing name attribute" << std::endl;
					}

					if (!valueAttrib)
					{
						std::cout << filePath.string() << ": opcode node missing value attribute" << std::endl;
					}

					continue;
				}

				unsigned short value = 0;
				size_t valueStart = 0;
				const char* valueData = valueAttrib->Value();

				for (size_t i = 0; !valueStart && valueData[i]; ++i)
				{
					if (valueData[i] == 'x')
					{
						valueStart = i + 1;
					}
				}

				if (valueStart == 0)
				{
					value = (unsigned short)atoi(valueData);
				}
				else
				{
					value = (unsigned short)strtol(valueData + valueStart, nullptr, 16);
				}

				PacketOpcode& opcode = (isServer ? schema.ServerOpcodes : schema.ClientOpcodes)[value];

				opcode.Name = nameAttrib->Value();
				opcode.Value = value;
				opcode.IsServer = isServer;

				OpcodeParser parser = { filePath.string(), opcode };

				if constexpr (PrintGeneratedOpcodes)
				{
					std::cout << "Opcode: " << (isServer ? "[Server] 0x" : "[Client] 0x") << std::hex << value << std::dec << std::endl;
				}

				parser.Read(opcodeElement);
				parser.Print();
			}
		}
	}

	void readSchemas(const fs::path& directory)
	{
		std::vector<unsigned int> versions;
		std::vector<fs::path> paths;

		for (const auto& entry : fs::recursive_directory_iterator{ directory })
		{
			const fs::path& path = entry.path();

			if (!fs::is_regular_file(path) && !path.has_extension()) continue;

			fs::path extension = path.extension();

			if (extension != ".xml") continue;

			unsigned int version = (unsigned int)atoi(path.filename().stem().string().c_str());
			unsigned int index = (unsigned int)paths.size();

			paths.push_back(path);
			versions.push_back((version << 16) | index);
		}

		std::sort(versions.begin(), versions.end());

		for (unsigned int data : versions)
		{
			unsigned int index = data & 0xFFFF;

			readSchema(paths[index]);
		}
	}

	const fs::path packetProjDir = "./../PacketProcessing";

	struct Generator
	{
		size_t Depth = 3;
		char Tabs[32] = "\t\t\t";
		char LoopIndex = 'i';

		void Push()
		{
			SetDepth(Depth + 1);
		}

		void Pop()
		{
			SetDepth(Depth - 1);
		}

		void SetDepth(size_t depth)
		{
			size_t min = std::min(Depth, depth) - 1;
			size_t max = std::max(Depth, depth);

			for (size_t i = min; i < max; ++i)
			{
				Tabs[i] = i < depth ? '\t' : 0;
			}

			Depth = depth;
		}
	};

	std::ostream& operator<<(std::ostream& out, const PacketData& data)
	{
		return out << data.Name << "_var" << data.Index;
	}

	std::ostream& operator<<(std::ostream& out, const PacketOutput& output)
	{
		if (output.Name.size())
		{
			out << output.Name << "_";
		}

		return out << "output" << output.OutputIndex;
	}

	const PacketOpcode* currentOpcode = nullptr;
	size_t currentIndex = 0;
	unsigned short currentVersion = 0;

	std::ostream& packetDebugInfo(std::ostream& out)
	{
		if (!currentOpcode)
		{
			return out << "[null]";
		}

		out << "[" << currentOpcode->Name << "; ";

		if (currentOpcode->IsBlock)
		{
			out << "Block; ";
		}
		else if (currentOpcode->IsServer)
		{
			out << "Server 0x" << std::hex << currentOpcode->Value << std::dec << "; ";
		}
		else
		{
			out << "Client 0x" << std::hex << currentOpcode->Value << std::dec << "; ";
		}

		out << "Version " << currentVersion << "; ";

		const auto& layout = currentOpcode->Layout[currentIndex];
		size_t index = layout.Index;

		switch (layout.Type)
		{
		case PacketInfoType::Data:
			out << "Data " << currentIndex << " " << currentOpcode->Data[index].Name;
			break;
		case PacketInfoType::Condition:
			out << "Condition " << currentIndex;
			break;
		case PacketInfoType::Output:
			out << "Output " << currentIndex << " " << currentOpcode->Outputs[index].TypeName;
			break;
		case PacketInfoType::OutputMember:
			out << "OutputMember " << currentIndex << " " << currentOpcode->OutputMembers[index].Output;
			break;
		case PacketInfoType::Array:
			out << "Array " << currentIndex << " " << currentOpcode->Arrays[index].Output;
			break;
		case PacketInfoType::Function:
			out << "Function " << currentIndex << " " << currentOpcode->Functions[index].Name;
			break;
		case PacketInfoType::Buffer:
			out << "Buffer " << currentIndex;
			break;
		case PacketInfoType::BlockFunction:
			out << "UseBlock " << currentIndex << " " << currentOpcode->BlockFunctions[index].Name;
			break;
		default:
			out << "<unknown>";
		}						  

		return out << "]";
	}

	void validateOutput(const DataOutput& output)
	{
		if (!output.Output)
		{
			packetDebugInfo(std::cout) << ": failed to find output";
		}
	}

	void validateOutput(const DataOutput& output, const std::string& name, const std::string& target)
	{
		if (!name.size() && !target.size())
		{
			return;
		}

		if (output.Member || output.IsIndexed)
		{
			return;
		}

		packetDebugInfo(std::cout) << ": failed to find output '" << name;

		if (target.size())
		{
			std::cout << "' with target'" << target;
		}

		std::cout << "'" << std::endl;
	}

	DataOutput findOutput(const std::string& name, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack)
	{
		if (name.size())
		{
			auto entry = outputs.find(name);

			if (entry != outputs.end())
			{
				return { "", entry->second };
			}

			return {};
		}

		for (size_t i = 0; i < stack.size(); ++i)
		{
			const auto& entry = stack[stack.size() - i - 1];

			if (entry.Output.Output)
			{
				return entry.Output;
			}
		}

		return { "", topOutput };
	}

	DataOutput findOutput(DataOutput output, const std::string& path)
	{
		const OutputSchema::SchemaClass* outputClass = output.Class == nullptr && output.Output != nullptr ? output.Output->Class : output.Class;

		if (!output.Output)
		{
			return {};
		}

		output.Member = OutputSchema::findSchemaMember(outputClass, path);

		if (!output.Member)
		{
			return {};
		}

		if (output.Name.size())
		{
			output.Name += "." + path;
		}
		else
		{
			std::stringstream stream;

			stream << *output.Output << "." << path;

			output.Name = stream.str();
		}

		if (output.Member->ContainsType.size())
		{
			if (output.Member->Type == "array")
			{
				return output;
			}

			OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(output.Member->ContainsType, output.Output->SchemaName);

			output.Class = entry.Class;

			if (entry.Class == nullptr)
			{
				std::cout << "failed to find class: '" << output.Member->ContainsType << "'" << std::endl;
			}
		}
		else
		{
			OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(output.Member->Type, output.Member->ParentSchemaName);

			output.Class = entry.Class;
		}

		return output;
	}

	bool canCastTypes(const std::string& dataType, const std::string& outputType, const std::string& outputSchema)
	{
		if (outputType == dataType)
		{
			return true;
		}

		if (NumericTypes.contains(dataType))
		{
			if (NumericTypes.contains(outputType))
			{
				return true;
			}

			OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(outputType, outputSchema);

			return entry.Type == OutputSchema::SchemaEntryType::Enum;
		}

		const auto typeEntry = PacketTypes.find(dataType);

		if (typeEntry != PacketTypes.end())
		{
			for (const std::string& canCast : typeEntry->second.CanCastTo)
			{
				if (canCast == outputType)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool canReadDirectly(const DataOutput& output, const PacketData& data)
	{
		if (!output.Member)
		{
			return false;
		}

		if (output.Member->Type == "array")
		{
			return canCastTypes(data.Type->TypeName, output.Member->ContainsType, output.Member->SchemaName);
		}

		return canCastTypes(data.Type->TypeName, output.Member->Type, output.Member->SchemaName);
	}

	DataOutput findOutput(const PacketOpcode& opcode, size_t index, const std::string& name, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack, const std::string& path)
	{
		DataOutput output = findOutput(name, outputs, topOutput, stack);

		size_t start = 0;
		size_t length = 0;

		while (start < path.size())
		{
			for (length; start + length < path.size() && path[start + length] != '.'; ++length);

			if (length == 0)
			{
				return {};
			}

			std::string_view name = { path.data() + start, length };

			start += length + 1;
			length = 0;

			std::string_view indexValue;

			if (name.back() == ']')
			{
				size_t openBracket = name.size() - 1;

				while (openBracket < name.size() && name[openBracket] != '[')
				{
					--openBracket;
				}

				if (openBracket >= name.size())
				{
					std::cout << "missing open bracket on output '" << path << "'" << std::endl;

					return {};
				}

				indexValue = { name.data() + openBracket + 1, name.size() - 2 - openBracket };

				name = { name.data(), openBracket };
			}

			DataOutput nextOutput = findOutput(output, std::string(name));

			if (indexValue.size())
			{
				if (!nextOutput.Member || !nextOutput.Member->ContainsType.size())
				{
					std::cout << "attempt to index nonindexable type '" << nextOutput.Member->ContainsType << "' in path '" << path << "' component '" << std::string_view{ path.data() + start, path.size() - start } << "'" << std::endl;
				}

				validateOutput(nextOutput, std::string(name), "");

				OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(nextOutput.Member->ContainsType, nextOutput.Output->SchemaName);

				nextOutput.Class = entry.Class;

				if (entry.Class == nullptr)
				{
					if (start < path.size())
					{
						if (NumericTypes.contains(nextOutput.Member->ContainsType))
						{
							std::cout << "attempt to index nonindexable type '" << nextOutput.Member->ContainsType << "' in path '" << path << "' component '" << std::string_view{ path.data() + start, path.size() - start } << "'" << std::endl;
						}
						else
						{
							std::cout << "failed to find class: '" << nextOutput.Member->ContainsType << "' in path '" << path << "' component '" << name << "'" << std::endl;
						}
					}

					start = path.size();
					nextOutput.IsIndexed = start >= path.size();
				}

				DataResult result = findDataReference(opcode, stack, indexValue, index);

				if (!result.Found)
				{
					nextOutput.Name += '[' + std::string(indexValue) + ']';
					nextOutput.IsIndexed = true;

					output = nextOutput;

					continue;
				}

				const PacketData& paramData = opcode.Data[opcode.Layout[result.DataIndex].Index];
				bool hasOutput = paramData.Output.size();

				DataOutput paramOutput = hasOutput ? findOutput(opcode, index, paramData.Target, outputs, topOutput, stack, paramData.Output) : DataOutput{};

				validateOutput(paramOutput, paramData.Output, paramData.Target);

				bool memberTypeDoesntMatch = !canReadDirectly(paramOutput, paramData);
				bool makeVariable = !paramData.Read || paramData.HasBitOutputs || (paramData.Referenced && !hasOutput) || paramData.Output.size() == 0 || memberTypeDoesntMatch;
				
				nextOutput.Name += '[';

				if (makeVariable || !paramOutput.Member)
				{
					std::stringstream out;
					out << paramData;
					nextOutput.Name += out.str();
				}
				else
				{
					nextOutput.Name += paramOutput.Name;
				}

				nextOutput.Name += ']';
				nextOutput.IsIndexed = true;
			}

			output = nextOutput;
		}

		return output;
	}

	struct ReferenceInfo
	{
		std::string Name;
		std::string TypeName;
		std::string ContainsType;
		std::string Schema;
	};

	ReferenceInfo getReference(size_t dataIndex, const PacketOpcode& opcode, size_t index, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack);

	ReferenceInfo getLoopReference(const std::string& name, const PacketOpcode& opcode, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack)
	{
		for (size_t stackIndex = stack.size(); stackIndex > 0; --stackIndex)
		{
			const auto& stackEntry = stack[stackIndex - 1];

			if (stackEntry.LoopParamName == name)
			{
				std::string iteratorName = stackEntry.LoopParamName + '_';
				iteratorName.push_back(stackEntry.LoopIndex);

				const auto& loopInfo = opcode.Layout[stackEntry.StartIndex];

				if (loopInfo.Type != PacketInfoType::Array)
				{
					std::cout << "referencing non loop iterator param '" << name << "'" << std::endl;
				}
				else
				{
					const auto& array = opcode.Arrays[loopInfo.Index];

					ReferenceInfo arrayData = getReference(array.DataIndex, opcode, stackEntry.StartIndex, outputs, topOutput, stack);

					return { iteratorName, arrayData.TypeName, arrayData.ContainsType, arrayData.Schema };
				}

				return {};
			}
		}

		return {};
	}

	ReferenceInfo getReference(size_t dataIndex, const PacketOpcode& opcode, size_t index, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack)
	{
		size_t dataParamIndex = dataIndex - ((size_t)-1 - opcode.Parameters.size());

		if (opcode.Parameters.size() && dataParamIndex < opcode.Parameters.size())
		{
			std::stringstream out;
			out << opcode.Parameters[dataParamIndex].Name << "_param" << dataParamIndex;

			return { out.str(), opcode.Parameters[dataParamIndex].Type, "", opcode.Parameters[dataParamIndex].Schema };
		}

		//if (dataIndex >= opcode.Layout.size())
		//{
		//	return getLoopReference(data.IteratorName, opcode, outputs, topOutput, stack);
		//}

		const PacketData& paramData = opcode.Data[opcode.Layout[dataIndex].Index];
		bool hasOutput = paramData.Output.size();

		DataOutput paramOutput = hasOutput ? findOutput(opcode, index, paramData.Target, outputs, topOutput, stack, paramData.Output) : DataOutput{};

		validateOutput(paramOutput, paramData.Output, paramData.Target);

		bool memberTypeDoesntMatch = !canReadDirectly(paramOutput, paramData);
		bool makeVariable = !paramData.Read || paramData.HasBitOutputs || (paramData.Referenced && !hasOutput) || paramData.Output.size() == 0 || memberTypeDoesntMatch;
		
		if (makeVariable || !paramOutput.Member)
		{
			std::stringstream out;
			out << paramData;

			return { out.str(), paramData.Type->TypeName };
		}
		else
		{
			std::string typeName;
			std::string containsType;
			std::string schema;

			if (paramOutput.Member)
			{
				typeName = paramOutput.Member->Type;
				containsType = paramOutput.Member->ContainsType;
				schema = paramOutput.Member->SchemaName;
			}
			else if (paramOutput.Class)
			{
				typeName = paramOutput.Class->TypeName;
				schema = paramOutput.Class->SchemaName;
			}

			return { paramOutput.Name, typeName, containsType, schema };
		}
	}

	struct OutputFiles
	{
		std::vector<const OutputSchema::SchemaClass*> Outputs;
	};
	
	std::unordered_map<std::string, OutputFiles> serverOutputsReferenced;
	std::unordered_map<std::string, OutputFiles> clientOutputsReferenced;
	std::unordered_map<const OutputSchema::SchemaClass*, bool> outputsReferenced;

	void generateParser(Generator& generator, std::ofstream& out, const PacketOpcode& opcode)
	{
		generator.SetDepth(3);

		const auto& tabs = generator.Tabs;

		PacketInfoType lastType = PacketInfoType::Condition;

		std::vector<StackEntry> stack;
		std::unordered_map<std::string, const PacketOutput*> outputs;

		if (opcode.IsBlock)
		{
			out << tabs << "if (handler.PacketStream().HasRecentlyFailed)\n";
			out << tabs << "{\n";
			out << tabs << "\treturn;\n";
			out << tabs << "}\n\n";
		}

		out << tabs << "using namespace ParserUtils::Packets;\n\n";
		out << tabs << "ParserUtils::DataStream& stream = handler.PacketStream();\n\n";

		out << "\t" << tabs << "StackWatch<PacketHandler> watch_block" << "(handler, \"";
		
		if (opcode.IsBlock)
		{
			out << opcode.Name << "_v" << currentVersion << "(\"";
			
			for (size_t i = 0; i < opcode.Parameters.size(); ++i)
			{
				const auto& parameter = opcode.Parameters[i];

				out << (i == 0 ? ", \"" : ", \", ") << parameter.Name << ": \", " << parameter.Name << "_param" << i;
			}

			out << ", \")\");\n\n";
		}
		else
		{
			out << (opcode.IsServer ? "[Server] 0x" : "[Client] 0x") << std::hex << opcode.Value << std::dec << " '" << opcode.Name << "' v" << currentVersion << "\");\n\n";
		}

		const PacketOutput* topOutput = nullptr;

		PacketOutput blockOutputData;

		currentOpcode = &opcode;

		if (opcode.IsBlock)
		{

			OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(opcode.BlockOutput.Type, opcode.BlockOutput.Schema);

			if (entry.Type == OutputSchema::SchemaEntryType::None)
			{
				std::cout << "failed to find type '" << opcode.BlockOutput.Type << "' in schema '" << opcode.BlockOutput.Schema << "'" << std::endl;

				currentOpcode = nullptr;

				return;
			}

			if (entry.Type != OutputSchema::SchemaEntryType::Class)
			{
				std::cout << "type '" << opcode.BlockOutput.Type << "' in schema '" << opcode.BlockOutput.Schema << "' isn't a class" << std::endl;

				currentOpcode = nullptr;

				return;
			}

			blockOutputData = PacketOutput{ (size_t)-1, entry.Class, opcode.BlockOutput.Type, opcode.BlockOutput.Schema, "blockOutput", false };

			DataOutput blockOutput = { opcode.BlockOutput.Name, &blockOutputData, nullptr, entry.Class };

			stack.push_back({ 0, opcode.Layout.size(), blockOutput});
		}

		for (size_t i = 0; i < opcode.Layout.size(); ++i)
		{
			currentIndex = i;

			while (stack.size() && i >= stack.back().EndIndex)
			{
				DataOutput& outputData = stack.back().Output;

				const PacketOutput* output = outputData.Output;

				if (output != nullptr && outputData.Member == nullptr)
				{
					if (stack.size() > 1 || !opcode.IsBlock)
					{
						out << "\n" << tabs << "if (handler.Succeeded())\n" << tabs << "{\n";
						out << tabs << "\thandler.PacketParsed<" << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(output->Class->Scope, "Networking.Packets"), "::") << ">(" << *output << ");\n";

						out << tabs << "}\n\n";

						if (output->ReturnOnFinish)
						{
							out << "\n" << tabs << "return;\n";
						}
					}

					if (outputs.contains(output->Name))
					{
						outputs.erase(output->Name);
					}
				}

				if (stack.back().IsLoop)
				{
					--generator.LoopIndex;

					if (stack.back().IncrementLoopCounter)
					{
						std::string iteratorName;

						if (stack.back().LoopParamName.size())
						{
							iteratorName = stack.back().LoopParamName + '_';
						}

						iteratorName.push_back(generator.LoopIndex);

						out << "\n" << tabs << "++" << iteratorName << ";\n";
					}
				}

				generator.Pop();
				
				if (stack.size() > 1 || !opcode.IsBlock)
				{
					out << tabs << "}\n";
				}

				stack.pop_back();
			}

			PacketInfoType type = opcode.Layout[i].Type;
			size_t index = opcode.Layout[i].Index;

			size_t depthValue = opcode.Layout[i].StackDepth - (opcode.IsBlock ? 0 : 1);

			if (depthValue != stack.size())
			{
				std::cout << opcode.Name << "[" << i << "]: stack size mismatch: " << depthValue << " vs " << stack.size() << std::endl;
			}

			if (type == PacketInfoType::Discard)
			{
				out << tabs << "handler.DiscardPacket();\n\n" << tabs << "return;\n\n";

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::BlockFunction)
			{
				const PacketBlockFunction& blockFunction = opcode.BlockFunctions[index];

				DataOutput output;
				
				if (blockFunction.Output.size())
				{
					output = findOutput(opcode, i, blockFunction.Target, outputs, topOutput, stack, blockFunction.Output);

					validateOutput(output, blockFunction.Output, blockFunction.Target);
				}
				else
				{
					output = findOutput(blockFunction.Target, outputs, topOutput, stack);

					validateOutput(output);
				}

				if (!output.Name.size() && output.Output)
				{
					std::stringstream out;
					out << *output.Output;
					output.Name = out.str();
				}

				out << tabs << "Parse" << blockFunction.Name << "_v" << blockFunction.Version << "(handler, " << output.Name;

				for (size_t i = 0; i < blockFunction.Arguments.size(); ++i)
				{
					size_t dataIndex = blockFunction.Arguments[i];

					out << ", ";

					std::string argType;

					const auto versionEntry = PacketVersions.find(blockFunction.Version);
					
					if (versionEntry != PacketVersions.end())
					{
						const auto blockEntry = versionEntry->second.BlockData.find(blockFunction.Name);

						if (blockEntry != versionEntry->second.BlockData.end())
						{
							const auto& parameters = blockEntry->second.Parameters;

							if (i < parameters.size())
							{
								argType = parameters[i].Type;
							}
						}
					}

					if (opcode.Parameters.size() && dataIndex >= opcode.Layout.size() && dataIndex < (size_t)-1)
					{
						size_t paramIndex = dataIndex - ((size_t)-1 - opcode.Parameters.size());

						if (argType.size() && opcode.Parameters[paramIndex].Type != argType)
						{
							out << "(" << argType << ")";
						}

						out << opcode.Parameters[paramIndex].Name << "_param" << paramIndex;

						continue;
					}

					const PacketData& paramData = opcode.Data[opcode.Layout[dataIndex].Index];
					bool hasOutput = paramData.Output.size();

					DataOutput paramOutput = hasOutput ? findOutput(opcode, i, paramData.Target, outputs, topOutput, stack, paramData.Output) : DataOutput{};

					validateOutput(paramOutput, paramData.Output, paramData.Target);

					bool memberTypeDoesntMatch = !canReadDirectly(paramOutput, paramData);
					bool makeVariable = !paramData.Read || paramData.HasBitOutputs || (paramData.Referenced && !hasOutput) || paramData.Output.size() == 0 || memberTypeDoesntMatch;

					if (argType.size() && paramData.Type->TypeName != argType)
					{
						out << "(" << argType << ")";
					}

					if (makeVariable || !output.Member)
					{
						out << paramData;
					}
					else
					{
						out << paramOutput.Name;
					}
				}

				out << ");\n";

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Data || type == PacketInfoType::DataRead || type == PacketInfoType::Function)
			{
				size_t functionIndex = index;

				if (type == PacketInfoType::DataRead)
				{
					const PacketRead& dataRead = opcode.Reads[index];

					index = opcode.Layout[dataRead.DataIndex].Index;
				}
				else if (type == PacketInfoType::Function)
				{
					const PacketFunction& function = opcode.Functions[index];

					index = opcode.Layout[function.DataIndex].Index;
				}

				const PacketData& data = opcode.Data[index];
				bool hasOutput = data.Output.size();

				DataOutput output = hasOutput ? findOutput(opcode, i, data.Target, outputs, topOutput, stack, data.Output) : DataOutput{};

				validateOutput(output, data.Output, data.Target);

				bool memberTypeDoesntMatch = !canReadDirectly(output, data);
				bool makeVariable = !data.Read || data.HasBitOutputs || (data.Referenced && !hasOutput) || data.Output.size() == 0 || memberTypeDoesntMatch;
				
				if ((lastType != PacketInfoType::Data || makeVariable || !output.Member) && lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array && lastType != PacketInfoType::OutputMember && lastType != PacketInfoType::Buffer)
				{
					out << "\n";
				}

				if (type != PacketInfoType::Function)
				{
					if (type == PacketInfoType::Data)
					{
						if (makeVariable || !output.Member)
						{
							out << tabs << data.Type->TypeName << " " << data;

							if (data.Type->DefaultValue.size())
							{
								out << " = ";
								if (data.Value.size())
								{
									out << data.Value;
								}
								else if (data.IteratorName.size())
								{
									std::string iteratorName = data.Type->DefaultValue;

									ReferenceInfo loopReference = getLoopReference(data.IteratorName, opcode, outputs, topOutput, stack);

									if (loopReference.Name.size())
									{
										iteratorName = loopReference.Name;

										std::string destinationType;

										if (makeVariable)
										{
											destinationType = data.Type->TypeName;
										}
										else
										{
											destinationType = output.Member->ContainsType.size() ? output.Member->ContainsType : output.Member->Type;
										}

										if (destinationType != loopReference.TypeName)
										{
											out << "(" << destinationType << ")";
										}
									}

									out << iteratorName;
								}
								else
								{
									out << data.Type->DefaultValue;
								}
							}

							out << ";\n";
						}
					}

					if (data.Read)
					{
						out << tabs << "Read<" << data.Type->TypeName << ">(\"" << data.Name << "\", handler, ";

						if (makeVariable || !output.Member)
						{
							out << data;
						}
						else
						{
							out << output.Name;
						}

						out << ");\n";
					}
				}
				else
				{
					const PacketFunction& function = opcode.Functions[functionIndex];

					out << tabs << "if (!handler.PacketStream().HasRecentlyFailed)\n";
					out << tabs << "{\n";

					out << tabs << '\t';

					if (/*makeVariable ||*/ !output.Member)
					{
						out << data;
					}
					else
					{
						out << output.Name;
					}

					out << " = ";

					if (/*!makeVariable &&*/ output.Member)
					{
						const std::string& typeName = output.Member->ContainsType.size() ? output.Member->ContainsType : output.Member->Type;

						std::string castTo = OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(typeName, "Networking.Packets"), "::");

						out << "(" << castTo << ")";
					}

					out << "handler." << function.Name << "(";

					for (size_t j = 0; j < function.ParamDataIndices.size(); ++j)
					{
						size_t paramIndex = function.ParamDataIndices[j];

						std::string param = getReference(paramIndex, opcode, i, outputs, topOutput, stack).Name;

						out << param;

						if (j + 1 < function.ParamDataIndices.size())
						{
							out << ", ";
						}
					}

					out << ");\n\n";

					out << tabs << "\tCalledFunction(handler, \"" << function.Name << "\", ";

					if (/*makeVariable ||*/ !output.Member)
					{
						out << "\"" << data << "\", " << data;
					}
					else
					{
						out << "\"" << output.Name << "\", " << output.Name;
					}

					for (size_t j = 0; j < function.ParamDataIndices.size(); ++j)
					{
						size_t paramIndex = function.ParamDataIndices[j];

						std::string param = getReference(paramIndex, opcode, i, outputs, topOutput, stack).Name;

						out << ", " << param;
					}

					out << ");\n";

					out << tabs << "}\n";
				}

				bool isDataInitialization = opcode.Layout[i].Type == PacketInfoType::Data && opcode.Layout[i].Index == index;

				if (data.EnumNames.size() && (data.Read || !isDataInitialization))
				{
					type = PacketInfoType::Validation;

					out << "\n" << tabs << "ValidateValues(handler, \"" << data.Name << "\", ";

					if (makeVariable || !output.Member)
					{
						out << data;
					}
					else
					{
						out << output.Name;
					}

					out << ", ";

					size_t i = 0;

					std::string typeName = OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(data.Type->TypeName, "Networking.Packets"), "::");

					for (const auto& enumEntry : data.EnumNames)
					{
						++i;

						out << "(" << typeName << ")" << enumEntry.first;

						if (i < data.EnumNames.size())
						{
							out << ", ";
						}
					}

					out << ");\n";
				}

				if (output.Member && makeVariable)
				{
					type = PacketInfoType::ValueWrite;

					out << "\n" << tabs << output.Name << " = " << "(" << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(output.Member->Type, "Networking.Packets"), "::") << ")" << data << ";\n";
				}

				if (data.HasBitOutputs)
				{
					out << "\n";

					for (size_t i = 0; i < data.Flags.size(); ++i)
					{
						const PacketDataBit& bit = data.Flags[i];

						if (bit.Output.size())
						{
							DataOutput output = findOutput(opcode, i, bit.Target, outputs, topOutput, stack, bit.Output);

							validateOutput(output, bit.Output, bit.Target);

							out << tabs << output.Name << " = GetBit(" << data << ", " << i << ");\n";
						}
					}

					type = PacketInfoType::ValueWrite;
				}

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::OutputMember)
			{
				const PacketOutputMember& outputMember = opcode.OutputMembers[index];

				DataOutput output = outputMember.Output.size() ? findOutput(opcode, i, outputMember.Target, outputs, topOutput, stack, outputMember.Output) : DataOutput{};

				validateOutput(output, outputMember.Output, outputMember.Target);

				out << "\n" << tabs << "{\n";
				out << "\t" << tabs << "StackWatch<PacketHandler> watch_" << i << "(handler, \"" << output.Name << "\");\n";

				stack.push_back({ i, outputMember.RegionEnd, output });
				generator.Push();
				
				continue;
			}

			if (type == PacketInfoType::Buffer)
			{
				const PacketBuffer& buffer = opcode.Buffers[index];

				DataOutput output = buffer.Output.size() ? findOutput(opcode, i, buffer.Target, outputs, topOutput, stack, buffer.Output) : DataOutput{};

				validateOutput(output, buffer.Output, buffer.Target);

				out << "\n" << tabs << "{\n";
				out << "\t" << tabs << "StackWatch<PacketHandler> watch_" << i << "(handler, \"buffer[\", ";

				stack.push_back({ i, buffer.RegionEnd, output });
				generator.Push();

				std::string sizeParam = getReference(buffer.BufferSizeDataIndex, opcode, i, outputs, topOutput, stack).Name;
				std::string isDeflatedParam = buffer.IsDeflatedDataIndex != (size_t)-1 ? getReference(buffer.IsDeflatedDataIndex, opcode, i, outputs, topOutput, stack).Name : "false";

				out << sizeParam << ", \"]\");\n";

				out << tabs << "Buffer buffer" << index << "(handler, (size_t)" << sizeParam << ", " << isDeflatedParam << ");\n";

				continue;
			}

			if (type == PacketInfoType::ArraySize)
			{
				const PacketArraySize& arraySize = opcode.ArraySizes[index];
				const PacketData& data = opcode.Data[opcode.Layout[arraySize.DataIndex].Index];

				std::string param = getReference(arraySize.DataIndex, opcode, i, outputs, topOutput, stack).Name;

				DataOutput output = arraySize.Output.size() ? findOutput(opcode, i, arraySize.Target, outputs, topOutput, stack, arraySize.Output) : DataOutput{};

				validateOutput(output, arraySize.Output, arraySize.Target);

				if (lastType != PacketInfoType::Condition && lastType != PacketInfoType::ArraySize)
				{
					out << "\n";
				}

				if (output.Output)
				{
					out << tabs << "ResizeVector(handler, " << output.Name << ", " << param << ");\n\n";

					out << tabs << "if (handler.PacketStream().HasRecentlyFailed)\n";
					out << tabs << "{\n";
					out << tabs << "\treturn;\n";
					out << tabs << "}\n";
				}

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Array)
			{
				const PacketArray& array = opcode.Arrays[index];

				ReferenceInfo param = getReference(array.DataIndex, opcode, i, outputs, topOutput, stack);

				DataOutput output = array.Output.size() ? findOutput(opcode, i, array.Target, outputs, topOutput, stack, array.Output) : DataOutput{};

				validateOutput(output, array.Output, array.Target);

				if (lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array)
				{
					out << "\n";
				}

				std::string containerName = output.Name;
				std::string iteratorName;

				if (array.Name.size())
				{
					iteratorName = array.Name + '_';
				}

				iteratorName.push_back(generator.LoopIndex);

				output.Name = containerName + '[' + iteratorName + ']';

				if (array.Type == PacketArray::TypeEnum::For)
				{
					if (output.Output)
					{
						out << tabs << "ResizeVector(handler, " << containerName << ", " << param.Name << ");\n\n";

						out << tabs << "if (handler.PacketStream().HasRecentlyFailed)\n";
						out << tabs << "{\n";
						out << tabs << "\treturn;\n";
						out << tabs << "}\n";
					}

					out << tabs << "for (" << param.TypeName << " " << iteratorName << " = 0; " << iteratorName << " < " << param.Name << " && !handler.PacketStream().HasRecentlyFailed; ++" << iteratorName << ")\n";
					out << tabs << "{\n";
					out << "\t" << tabs << "StackWatch<PacketHandler> watch_" << i << "(handler, \"";
					
					if (output.Output)
					{
						out << containerName << "[\", ";
					}
					else if (array.Name.size())
					{
						out << array.Name << "_array" << index << "[\", ";
					}
					else
					{
						out << "array" << index << "[\", ";
					}

					out << iteratorName << ", \"]\"); \n";

					stack.push_back({ i, array.RegionEnd, output, true, false, array.Name, generator.LoopIndex });
					generator.Push();

					lastType = PacketInfoType::Array;

					if (array.Name.size())
					{
						std::stringstream newName;

						newName << array.Name << "_array" << index;

						out << tabs << "auto& " << newName.str() << " = " << output.Name << ";\n";

						stack.back().Output.Name = newName.str();

						lastType = PacketInfoType::ArrayOutput;
					}

					++generator.LoopIndex;

					continue;
				}

				if (array.Type == PacketArray::TypeEnum::While)
				{
					out << tabs << "size_t " << iteratorName << " = 0;\n\n";

					out << tabs << "while (" << param.Name << " && !handler.PacketStream().HasRecentlyFailed)\n";
					out << tabs << "{\n";
					out << "\t" << tabs << "StackWatch<PacketHandler> watch_" << i << "(handler, \"";

					if (output.Output)
					{
						out << containerName << "[\", ";
					}
					else if (array.Name.size())
					{
						out << array.Name << "_array" << index << "[\", ";
					}
					else
					{
						out << "array" << index << "[\", ";
					}

					out << iteratorName << ", \"]\"); \n";

					stack.push_back({ i, array.RegionEnd, output, true, true, array.Name, generator.LoopIndex });
					generator.Push();

					if (output.Output)
					{
						out << tabs << containerName << ".push_back({});\n\n";

						out << tabs << "if (handler.PacketStream().HasRecentlyFailed)\n";
						out << tabs << "{\n";
						out << tabs << "\treturn;\n";
						out << tabs << "}\n";
					}

					if (array.Name.size())
					{
						std::stringstream newName;

						newName << array.Name << "_array" << index;

						out << "\n" << tabs << "auto& " << newName.str() << " = " << output.Name << ";\n";

						stack.back().Output.Name = newName.str();

						lastType = PacketInfoType::ArrayOutput;
					}

					++generator.LoopIndex;

					continue;
				}

				continue;
			}

			if (type == PacketInfoType::Condition)
			{
				const PacketCondition& condition = opcode.Conditions[index];

				if (lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array)
				{
					out << "\n";
				}

				std::stringstream conditionOut;
				std::string conditionType;

				if (condition.Comparison == PacketInfoComparison::None && condition.IsElse)
				{
					out << tabs << "else\n";

					conditionType = "else";
				}
				else
				{
					size_t dataIndex = opcode.Layout[condition.DataIndex].Index;

					const PacketData& data = opcode.Data[dataIndex];

					out << tabs << (condition.IsElse ? "else if (" : "if (");

					conditionType = condition.IsElse ? "else if " : "if ";

					ReferenceInfo param = getReference(condition.DataIndex, opcode, i, outputs, topOutput, stack);

					std::string cast;
					const std::string& type = param.ContainsType.size() ? param.ContainsType : param.TypeName;

					if (!NumericTypes.contains(type))
					{
						OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(type, param.Schema);

						if (entry.Enum)
						{
							cast = "(" + OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(type, "Networking.Packets"), "::") + ")";
						}
					}

					if (condition.BitIndex != 0xFF)
					{
						conditionOut << "GetBit(" << param.Name << ", " << (int)condition.BitIndex << ")";
					}
					else
					{
						conditionOut << param.Name;
					}

					if (condition.Comparison == PacketInfoComparison::Equal)
					{
						if (condition.Value != 1 || data.Type->TypeName != "bool")
						{
							conditionOut << " == " << cast << condition.Value;
						}
					}
					else if (condition.Comparison == PacketInfoComparison::NotEqual)
					{
						conditionOut << " != " << cast << condition.Value;
					}
					else if (condition.Comparison == PacketInfoComparison::Between)
					{
						conditionOut << " >= " << condition.Value << " && " << param.Name << " <= " << condition.Value2;
					}
					else if (condition.Comparison == PacketInfoComparison::NotBetween)
					{
						conditionOut << " < " << condition.Value << " || " << param.Name << " > " << condition.Value2;
					}
					else if (condition.Comparison == PacketInfoComparison::LessThan)
					{
						conditionOut << " < " << condition.Value;
					}
					else if (condition.Comparison == PacketInfoComparison::GreaterThan)
					{
						conditionOut << " > " << condition.Value;
					}
					else if (condition.Comparison == PacketInfoComparison::LessEqual)
					{
						conditionOut << " <= " << condition.Value;
					}
					else if (condition.Comparison == PacketInfoComparison::GreaterEqual)
					{
						conditionOut << " >= " << condition.Value;
					}

					out << conditionOut.str() << ")\n";
				}

				out << tabs << "{\n";
				out << "\t" << tabs << "StackWatch<PacketHandler> watch_" << i << "(handler, \"" << conditionType << conditionOut.str() << "\");\n";

				stack.push_back({ i, condition.RegionEnd });
				generator.Push();

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Output)
			{
				const PacketOutput& output = opcode.Outputs[index];

				out << tabs << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(output.Class->Scope, "Networking.Packets"), "::") << " " << output << ";\n";

				if (stack.size())
				{
					stack.back().Output.Output = &output;
				}
				else
				{
					topOutput = &output;
				}

				outputs[output.Name] = &output;

				if (!outputsReferenced.contains(output.Class))
				{
					outputsReferenced[output.Class] = opcode.IsServer;

					(opcode.IsServer ? serverOutputsReferenced : clientOutputsReferenced)[opcode.Name].Outputs.push_back(output.Class);
				}

				lastType = type;

				continue;
			}
		}

		while (stack.size())
		{
			DataOutput& outputData = stack.back().Output;

			const PacketOutput* output = outputData.Output;

			if (output != nullptr && outputData.Member == nullptr)
			{
				if (stack.size() > 1 || !opcode.IsBlock)
				{
					out << "\n" << tabs << "if (handler.Succeeded())\n" << tabs << "{\n";
					out << tabs << "\thandler.PacketParsed<" << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(output->Class->Scope, "Networking.Packets"), "::") << ">(" << *output << ");\n";

					out << tabs << "}\n\n";

					if (output->ReturnOnFinish)
					{
						out << "\n" << tabs << "return;\n";
					}
				}

				if (outputs.contains(output->Name))
				{
					outputs.erase(output->Name);
				}
			}

			if (stack.back().IsLoop)
			{
				--generator.LoopIndex;

				if (stack.back().IncrementLoopCounter)
				{
					std::string iteratorName;

					if (stack.back().LoopParamName.size())
					{
						iteratorName = stack.back().LoopParamName + '_';
					}

					iteratorName.push_back(generator.LoopIndex);

					out << "\n" << tabs << "++" << iteratorName << ";\n";
				}
			}
			
			generator.Pop();

			if (stack.size() > 1 || !opcode.IsBlock)
			{
				out << tabs << "}\n";
			}

			stack.pop_back();
		}

		if (topOutput)
		{
			if (stack.size() > 1 || !opcode.IsBlock)
			{
				out << "\n" << tabs << "if (handler.Succeeded())\n" << tabs << "{\n";
				out << tabs << "\thandler.PacketParsed<" << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(topOutput->Class->Scope, "Networking.Packets"), "::") << ">(" << *topOutput << ");\n";

				out << tabs << "}\n\n";

				if (topOutput->ReturnOnFinish)
				{
					out << "\n" << tabs << "return;\n";
				}
			}
		}

		currentOpcode = nullptr;

		generator.LoopIndex = 'i';
	}

	unsigned short minVersion = 0xFFFF;
	unsigned short maxVersion = 0;

	void generateParserOpcodeTable(std::ofstream& cppOut)
	{

		for (const auto& versionEntry : PacketVersions)
		{
			if (versionEntry.first > 13)
			{
				minVersion = std::min(minVersion, versionEntry.first);
				maxVersion = std::max(maxVersion, versionEntry.first);
			}
		}

		if (minVersion != 0xFFFF && PacketVersions.contains(13))
		{
			--minVersion;
		}

		struct OpcodeData
		{
			const PacketOpcode* Opcode = nullptr;
			const PacketOpcodeReference* Reference = nullptr;
			std::string Name;
			unsigned short Version = 0;
		};

		struct VersionData
		{
			const PacketVersion* Version = nullptr;
			size_t Index = (size_t)-1;

			unsigned short MinServerOpcode = 0xFFFF;
			unsigned short MaxServerOpcode = 0;
			unsigned short MinClientOpcode = 0xFFFF;
			unsigned short MaxClientOpcode = 0;

			std::vector<OpcodeData> ServerOpcodes;
			std::vector<OpcodeData> ClientOpcodes;
		};

		std::vector<VersionData> versions;
		std::vector<VersionData> versionOverrides(maxVersion - minVersion + 1);

		if (PacketVersions.contains(12))
		{
			versions.push_back({ &PacketVersions[12], 12 });
		}

		if (PacketVersions.contains(13))
		{
			versionOverrides[0] = { &PacketVersions[13], 13 };
		}

		size_t baseVersionCount = versions.size();

		for (const auto& versionEntry : PacketVersions)
		{
			if (versionEntry.first == 12)
			{
				continue;
			}

			versionOverrides[std::max(versionEntry.first, minVersion) - minVersion] = { &versionEntry.second };
		}

		for (size_t i = 0; i < versionOverrides.size(); ++i)
		{
			VersionData& data = versionOverrides[i];

			if (!data.Version)
			{
				versionOverrides[i] = versionOverrides[i - 1];

				continue;
			}

			data.Index = versions.size();

			versions.push_back({ data.Version, (unsigned short)data.Version->Version });
		}

		cppOut << "#include \"PacketParser.h\"\n\n";
		cppOut << "#include <vector>\n\n";
		cppOut << "namespace Networking\n{\n";

		cppOut << "\tnamespace Packets\n\t{\n";

		cppOut << "\t\tconst std::vector<size_t> VersionIndices = {\n";
		cppOut << "\t\t\t";

		for (size_t i = 0; i < versionOverrides.size(); ++i)
		{
			cppOut << versionOverrides[i].Index;

			if (i + 1 < versionOverrides.size())
			{
				cppOut << ", ";
			}
		}

		cppOut << "\n";
		cppOut << "\t\t};\n";

		cppOut << "\t\tconst std::vector<PacketVersionData> Versions = {\n";

		for (size_t i = 0; i < versions.size(); ++i)
		{
			size_t versionId = versions[i].Index;

			{

				VersionData& versionData = versions[i];
				const PacketVersion* version = versionData.Version;

				bool hasServerOpcodes = false;
				bool hasClientOpcodes = false;

				unsigned short& minServerOpcode = versionData.MinServerOpcode;
				unsigned short& maxServerOpcode = versionData.MaxServerOpcode;
				unsigned short& minClientOpcode = versionData.MinClientOpcode;
				unsigned short& maxClientOpcode = versionData.MaxClientOpcode;

				if (i > 0 && version->InheritPrevious)
				{
					minServerOpcode = versions[i - 1].MinServerOpcode;
					maxServerOpcode = versions[i - 1].MaxServerOpcode;
					minClientOpcode = versions[i - 1].MinClientOpcode;
					maxClientOpcode = versions[i - 1].MaxClientOpcode;

					hasServerOpcodes = versions[i - 1].ServerOpcodes.size() > 0;
					hasClientOpcodes = versions[i - 1].ClientOpcodes.size() > 0;
				}

				for (const auto& opcodeEntry : version->ServerOpcodes)
				{
					minServerOpcode = std::min(minServerOpcode, opcodeEntry.first);
					maxServerOpcode = std::max(maxServerOpcode, opcodeEntry.first);
				}

				for (const auto& opcodeEntry : version->ClientOpcodes)
				{
					minClientOpcode = std::min(minClientOpcode, opcodeEntry.first);
					maxClientOpcode = std::max(maxClientOpcode, opcodeEntry.first);
				}

				for (const auto& opcodeEntry : version->ServerOpcodeReferences)
				{
					minServerOpcode = std::min(minServerOpcode, opcodeEntry.first);
					maxServerOpcode = std::max(maxServerOpcode, opcodeEntry.first);
				}

				for (const auto& opcodeEntry : version->ClientOpcodeReferences)
				{
					minClientOpcode = std::min(minClientOpcode, opcodeEntry.first);
					maxClientOpcode = std::max(maxClientOpcode, opcodeEntry.first);
				}

				hasServerOpcodes |= version->ServerOpcodes.size() || version->ServerOpcodeReferences.size();
				hasClientOpcodes |= version->ClientOpcodes.size() || version->ClientOpcodeReferences.size();

				std::vector<OpcodeData>& serverOpcodes = versionData.ServerOpcodes;
				std::vector<OpcodeData>& clientOpcodes = versionData.ClientOpcodes;

				serverOpcodes.resize(hasServerOpcodes ? maxServerOpcode - minServerOpcode + 1 : 0);
				clientOpcodes.resize(hasClientOpcodes ? maxClientOpcode - minClientOpcode + 1 : 0);

				if (i > 0 && version->InheritPrevious)
				{
					for (size_t j = minServerOpcode; j <= maxServerOpcode; ++j)
					{
						if (!version->DoNotInheritServer.contains((unsigned short)j))
						{
							serverOpcodes[j - minServerOpcode] = versions[i - 1].ServerOpcodes[j - versions[i - 1].MinServerOpcode];
						}
					}

					for (size_t j = minClientOpcode; j <= maxClientOpcode; ++j)
					{
						if (!version->DoNotInheritClient.contains((unsigned short)j))
						{
							clientOpcodes[j - minClientOpcode] = versions[i - 1].ClientOpcodes[j - versions[i - 1].MinClientOpcode];
						}
					}
				}

				for (const auto& opcodeEntry : version->ServerOpcodes)
				{
					serverOpcodes[opcodeEntry.first - minServerOpcode] = { &opcodeEntry.second, nullptr, opcodeEntry.second.Name, version->Version };
				}

				for (const auto& opcodeEntry : version->ClientOpcodes)
				{
					clientOpcodes[opcodeEntry.first - minClientOpcode] = { &opcodeEntry.second, nullptr, opcodeEntry.second.Name, version->Version };
				}

				for (const auto& opcodeEntry : version->ServerOpcodeReferences)
				{
					const PacketOpcodeReference& reference = opcodeEntry.second;
					std::string name = "error";

					size_t index = 0;

					if (reference.TargetVersion == 12)
					{
						index = 0;
					}
					else if (reference.TargetVersion == 13)
					{
						index = baseVersionCount;
					}
					if (reference.TargetVersion >= minVersion && reference.TargetVersion <= maxVersion)
					{
						index = versionOverrides[reference.TargetVersion - minVersion].Index;
					}

					name = versions[index].ServerOpcodes[reference.TargetOpcode - versions[index].MinServerOpcode].Name;

					serverOpcodes[opcodeEntry.first - minServerOpcode] = { nullptr, &reference, name };
				}

				for (const auto& opcodeEntry : version->ClientOpcodeReferences)
				{
					const PacketOpcodeReference& reference = opcodeEntry.second;
					std::string name = "error";

					size_t index = 0;

					if (reference.TargetVersion == 12)
					{
						index = 0;
					}
					else if (reference.TargetVersion == 13)
					{
						index = baseVersionCount;
					}
					else if (reference.TargetVersion >= minVersion && reference.TargetVersion <= maxVersion)
					{
						index = versionOverrides[reference.TargetVersion - minVersion].Index;
					}

					name = versions[index].ClientOpcodes[reference.TargetOpcode - versions[index].MinClientOpcode].Name;

					clientOpcodes[opcodeEntry.first - minClientOpcode] = { nullptr, &opcodeEntry.second, name };
				}

				cppOut << "\t\t\t{\n";
				cppOut << "\t\t\t\t0x" << std::hex << minServerOpcode << ", 0x" << minClientOpcode << std::dec << ", // v" << version->Version << "+\n";

				if (serverOpcodes.size() > 0)
				{
					cppOut << "\t\t\t\t{\n";

					for (size_t i = 0; i < serverOpcodes.size(); ++i)
					{
						const OpcodeData& opcodeData = serverOpcodes[i];

						if (opcodeData.Reference != nullptr)
						{
							cppOut << "\t\t\t\t\t{ \"" << opcodeData.Name << "\", &ParsePacket<" << opcodeData.Reference->TargetVersion << ", ServerPacket, 0x" << std::hex << opcodeData.Reference->TargetOpcode << std::dec << "> }" << (i + 1 < serverOpcodes.size() ? ", // 0x" : " // 0x") << std::hex << (minServerOpcode + i) << "\n" << std::dec;

							continue;
						}

						const PacketOpcode* opcode = opcodeData.Opcode;

						if (!opcode)
						{
							cppOut << "\t\t\t\t\t{ \"\", &ParsePacket<0, false, 0> }" << (i + 1 < serverOpcodes.size() ? ", // 0x" : " // 0x") << std::hex << (minServerOpcode + i) << "\n" << std::dec;

							continue;
						}

						cppOut << "\t\t\t\t\t{ \"" << opcode->Name << "\", &ParsePacket<" << opcodeData.Version << ", ServerPacket, 0x" << std::hex << (minServerOpcode + i) << std::dec << (i + 1 < serverOpcodes.size() ? "> }, // 0x" : "> } // 0x") << std::hex << (minServerOpcode + i) << "\n" << std::dec;
					}

					cppOut << "\t\t\t\t},\n";
				}
				else
				{
					cppOut << "\t\t\t\t{ },\n";
				}

				if (clientOpcodes.size() > 0)
				{
					cppOut << "\t\t\t\t{\n";

					for (size_t i = 0; i < clientOpcodes.size(); ++i)
					{
						const OpcodeData& opcodeData = clientOpcodes[i];

						if (opcodeData.Reference != nullptr)
						{
							cppOut << "\t\t\t\t\t{ \"" << opcodeData.Name << "\", &ParsePacket<" << opcodeData.Reference->TargetVersion << ", ClientPacket, 0x" << std::hex << opcodeData.Reference->TargetOpcode << std::dec << "> }" << (i + 1 < clientOpcodes.size() ? ", // 0x" : " // 0x") << std::hex << (minClientOpcode + i) << "\n" << std::dec;

							continue;
						}

						const PacketOpcode* opcode = opcodeData.Opcode;

						if (!opcode)
						{
							cppOut << "\t\t\t\t\t{ \"\", &ParsePacket<0, false, 0> }" << (i + 1 < clientOpcodes.size() ? ", // 0x" : " // 0x") << std::hex << (minClientOpcode + i) << "\n" << std::dec;

							continue;
						}

						cppOut << "\t\t\t\t\t{ \"" << opcode->Name << "\", &ParsePacket<" << opcodeData.Version << ", ClientPacket, 0x" << std::hex << (minClientOpcode + i) << std::dec << (i + 1 < clientOpcodes.size() ? "> }, // 0x" : "> } // 0x") << std::hex << (minClientOpcode + i) << "\n" << std::dec;
					}

					cppOut << "\t\t\t\t}\n";
				}
				else
				{
					cppOut << "\t\t\t\t{ }\n";
				}

				cppOut << "\t\t\t}";

				if (i + 1 < versions.size())
				{
					cppOut << ",";
				}

				cppOut << "\n";
			}
		}

		cppOut << "\t\t};\n";
		cppOut << "\t};\n";
		cppOut << "};\n";
	}

	void generateParsers()
	{
		fs::path tableCppPath = packetProjDir / "src/PacketProcessing/PacketOpcodes.cpp";

		{
			std::ofstream cppOut(tableCppPath);

			generateParserOpcodeTable(cppOut);
		}

		fs::path headerPath = packetProjDir / "src/PacketProcessing/PacketParser.h";

		{
			std::ofstream headerOut(headerPath);

			headerOut << "#pragma once\n\n";

			headerOut << "#include \"PacketParserBase.h\"\n\n";

			headerOut << "namespace Networking\n{\n";

			headerOut << "\tnamespace Packets\n\t{\n";

			headerOut << "\t\tconst size_t MinVersion = " << minVersion << ";\n";
			headerOut << "\t\tconst size_t MaxVersion = " << maxVersion << ";\n\n";

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;

				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", ClientPacket, 0x" << std::hex << opcode << std::dec << ">(PacketHandler& handler);\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", ServerPacket, 0x" << std::hex << opcode << std::dec << ">(PacketHandler& handler);\n\n";
				}
			}

			headerOut << "\t}\n";
			headerOut << "}\n";
		}

		fs::path cppPath = packetProjDir / "src/PacketProcessing/PacketParser.cpp";

		outputsReferenced.clear();
		serverOutputsReferenced.clear();
		clientOutputsReferenced.clear();

		{
			std::ofstream cppOut(cppPath);

			cppOut << "#include \"PacketParser.h\"\n\n";
			cppOut << "#include <vector>\n\n";
			cppOut << "#include <ParserUtils/PacketParsing.h>\n\n";
			cppOut << "#include \"PacketParserOutputs.h\"\n\n";

			cppOut << "namespace Networking\n{\n";

			cppOut << "\tnamespace Packets\n\t{\n";

			Generator generator;

			std::vector<unsigned int> versionEntries;
			std::vector<const PacketVersion*> versionData;

			for (const auto& versionEntry : PacketVersions)
			{
				unsigned int index = (unsigned int)versionData.size();

				versionData.push_back(&versionEntry.second);
				versionEntries.push_back((versionEntry.first << 16) | index);
			}

			std::sort(versionEntries.begin(), versionEntries.end());

			for (unsigned int data : versionEntries)
			{
				unsigned int index = data & 0xFFFF;
				const auto& version = *versionData[index];

				currentVersion = version.Version;

				for (size_t i = 0; i < version.Blocks.size(); ++i)
				{
					const auto& block = *version.Blocks[i];

					cppOut << "\t\tvoid Parse" << block.Name << "_v" << version.Version << "(PacketHandler& handler, ";
					
					cppOut << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(block.BlockOutput.Type, "Networking.Packets"), "::");
					cppOut << "& " << block.BlockOutput.Name;

					for (size_t i = 0; i < block.Parameters.size(); ++i)
					{
						cppOut << ", ";
						cppOut << OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(block.Parameters[i].Type, "Networking.Packets"), "::");
						cppOut << " " << block.Parameters[i].Name << "_param" << i;
					}

					cppOut << ")\n\t\t{\n";

					generateParser(generator, cppOut, block);

					cppOut << "\t\t}\n\n";
				}
			}

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;

				currentVersion = version;

				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", ClientPacket, 0x" << std::hex << opcode << std::dec << ">(PacketHandler& handler)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second);

					cppOut << "\t\t}\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", ServerPacket, 0x" << std::hex << opcode << std::dec << ">(PacketHandler& handler)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second);

					cppOut << "\t\t}\n\n";
				}
			}

			cppOut << "\t}\n";
			cppOut << "}\n";
		}

		fs::path includesHeaderPath = packetProjDir / "src/PacketProcessing/PacketParserOutputs.h";

		{
			std::ofstream headerOut(includesHeaderPath);

			headerOut << "#pragma once\n";

			std::unordered_set<std::string> printedFiles;

			for (const auto& entry : outputsReferenced)
			{
				const OutputSchema::SchemaClass* schemaClass = entry.first;

				std::string path = schemaClass->Directory + "/" + (schemaClass->FileName.size() ? schemaClass->FileName : schemaClass->Name);

				if (printedFiles.contains(path))
				{
					continue;
				}

				printedFiles.insert(path);

				headerOut << "#include <GameData/" << path << ".h>\n";
			}
		}
	}

	void generateHandler(const std::string& name)
	{
		fs::path handlerPath = packetProjDir / "src/PacketProcessing/Handlers" / name;
		fs::path headerPath = handlerPath / (name + ".h");

		{
			std::ofstream headerOut(headerPath);

			headerOut << "#pragma once\n\n";

			headerOut << "#include \"" << name << "-decl.h\"\n\n";
			headerOut << "#include \"./../../PacketParserBase.h\"\n\n";

			struct NamespaceScope
			{
				std::unordered_set<std::string> Classes;
				std::unordered_map<std::string, const NamespaceScope*> Children;
			};

			std::unordered_map<std::string, NamespaceScope> referencedNamespaces;

			for (const auto& entry : outputsReferenced)
			{
				const OutputSchema::SchemaClass* schemaClass = entry.first;

				size_t lastStart = 0;

				size_t size = schemaClass->Scope.size();

				for (size_t i = 0; i < size; ++i)
				{
					if (schemaClass->Scope[i] == '.')
					{
						std::string current = schemaClass->Scope.substr(lastStart, i - lastStart);
						std::string currentFull = schemaClass->Scope.substr(0, i);
						std::string lastFull = schemaClass->Scope.substr(0, lastStart ? lastStart - 1 : 0);
						
						referencedNamespaces[lastFull].Children[current] = &referencedNamespaces[currentFull];

						lastStart = i + 1;
					}
				}

				if (lastStart < size)
				{
					std::string current = schemaClass->Scope.substr(lastStart, size - lastStart);
					std::string currentFull = schemaClass->Scope.substr(0, lastStart ? lastStart - 1 : 0);

					auto& parent = referencedNamespaces[currentFull];

					if (!parent.Classes.contains(current))
					{
						parent.Classes.insert(current);
					}
				}
			}

			static const char tabs[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
			static const size_t maxTabs = sizeof(tabs);

			struct NamespaceStackEntry
			{
				std::string Name;
				const NamespaceScope* Namespace;
				std::unordered_map<std::string, const NamespaceScope*>::const_iterator Entry;
			};

			std::vector<NamespaceStackEntry> namespaceStack = { { "", &referencedNamespaces[""], referencedNamespaces[""].Children.begin() }};

			while (namespaceStack.size())
			{
				NamespaceStackEntry& entry = namespaceStack.back();

				size_t size = namespaceStack.size();
				const char* currentTabs = tabs + maxTabs - size;

				for (const auto entry : entry.Namespace->Classes)
				{
					headerOut << currentTabs << "struct " << entry << ";\n";
				}

				if (entry.Namespace->Classes.size() && entry.Namespace->Children.size())
				{
					headerOut << currentTabs << "\n";
				}

				if (entry.Entry == entry.Namespace->Children.end())
				{
					namespaceStack.pop_back();

					if (namespaceStack.size() > 0)
					{
						headerOut << (currentTabs + 1) << "}\n";
					}

					continue;
				}

				headerOut << currentTabs << "namespace " << entry.Entry->first << "\n" << currentTabs << "{\n";

				NamespaceStackEntry next = { entry.Entry->first, entry.Entry->second, entry.Entry->second->Children.begin() };

				++entry.Entry;

				namespaceStack.push_back(next);
			}

			if (referencedNamespaces.size() > 1)
			{
				headerOut << "\n";
			}

			headerOut << "\nnamespace Networking\n{\n";

			headerOut << "\tnamespace Packets\n\t{\n";

			for (const auto& entry : outputsReferenced)
			{
				const OutputSchema::SchemaClass* schemaClass = entry.first;

				std::string typeName = OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(schemaClass->Scope, "Networking.Packets"), "::");
				headerOut << "\t\ttemplate <>\n";
				headerOut << "\t\tvoid " << name << "::PacketParsed<" << typeName << ">(const " << typeName << "& packet);\n\n";
			}

			headerOut << "\t}\n";
			headerOut << "}\n";
		}

		fs::path vcxprojPath = packetProjDir / "PacketProcessing.vcxproj";
		fs::path filtersPath = packetProjDir / "PacketProcessing.vcxproj.filters";

		tinyxml2::XMLDocument vcxproj;
		tinyxml2::XMLDocument filters;

		vcxproj.LoadFile(vcxprojPath.string().c_str());
		filters.LoadFile(filtersPath.string().c_str());

		tinyxml2::XMLElement* vcxprojRoot = vcxproj.RootElement();
		tinyxml2::XMLElement* filtersRoot = filters.RootElement();

		fs::create_directories(handlerPath / "Server");
		fs::create_directories(handlerPath / "Client");

		const auto generateStub = [&handlerPath, &vcxprojRoot, &filtersRoot, &name](const std::string& opcodeName, const OutputFiles& opcode, bool isServer)
		{
			fs::path cppPath = handlerPath / (isServer ? "Server" : "Client") / (opcodeName + (isServer ? "-s-" : "-c-") + name + ".cpp");

			if (fs::exists(cppPath))
			{
				return;
			}

			std::ofstream cppOut(cppPath);

			cppOut << "#include \"./../" << name << ".h\"\n\n";

			std::unordered_set<std::string> printedFiles;

			for (const OutputSchema::SchemaClass* schemaClass : opcode.Outputs)
			{
				std::string path = schemaClass->Directory + "/" + (schemaClass->FileName.size() ? schemaClass->FileName : schemaClass->Name);

				if (printedFiles.contains(path))
				{
					continue;
				}

				printedFiles.insert(path);

				cppOut << "#include <GameData/" << path << ".h>\n";
			}

			cppOut << "\nnamespace Networking\n{\n";

			cppOut << "\tnamespace Packets\n\t{\n";

			for (size_t i = 0; i < opcode.Outputs.size(); ++i)
			{
				if (i != 0)
				{
					cppOut << "\t\n";
				}

				const OutputSchema::SchemaClass* schemaClass = opcode.Outputs[i];

				std::string typeName = OutputSchema::swapSeparator(OutputSchema::stripCommonNamespaces(schemaClass->Scope, "Networking.Packets"), "::");
				cppOut << (i == 0 ? "\t\ttemplate <>\n" : "\n\t\ttemplate <>\n");
				cppOut << "\t\tvoid " << name << "::PacketParsed<" << typeName << ">(const " << typeName << "& packet)\n\t\t{\n\t\t\t\n\t\t}\n";
			}

			cppOut << "\t}\n";
			cppOut << "}\n";

			std::string filterData = "Source Files\\Handlers\\" + name + (isServer ? "\\Server" : "\\Client");

			OutputSchema::addProjectNode(vcxprojRoot, "ClCompile", cppPath.string(), nullptr);
			OutputSchema::addProjectNode(filtersRoot, "ClCompile", cppPath.string(), filterData.c_str());
		};

		for (const auto& entry : serverOutputsReferenced)
		{
			generateStub(entry.first, entry.second, true);
		}

		for (const auto& entry : clientOutputsReferenced)
		{
			generateStub(entry.first, entry.second, false);
		}

		vcxproj.SaveFile(vcxprojPath.string().c_str());
		filters.SaveFile(filtersPath.string().c_str());
	}
}
