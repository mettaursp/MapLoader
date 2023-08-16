#include "PacketScheam.h"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <stdlib.h>
#include <string>

#include "OutputSchema.h"

namespace PacketSchema
{
	const std::unordered_map<std::string, PacketType> PacketTypes = {
		{ "bool", { "bool", "bool", "false", 1}},
		{ "ubyte", { "ubyte", "unsigned char", "0", 1}},
		{ "sbyte", { "sbyte", "signed char", "0", 1}},
		{ "byte", { "byte", "unsigned char", "0", 1}},
		{ "char", { "char", "char", "0", 1}},
		{ "ushort", { "ushort", "unsigned short", "0", 2}},
		{ "short", { "short", "short", "0", 2}},
		{ "uint", { "uint", "unsigned int", "0", 4}},
		{ "int", { "int", "int", "0", 4}},
		{ "ulong", { "ulong", "unsigned long long", "0", 8}},
		{ "long", { "long", "long long", "0", 8}},
		{ "float", { "float", "float", "0", 4 }},
		{ "double", { "double", "double", "0", 8 }},
		{ "string", { "string", "std::string", "", 0 }},
		{ "wstring", { "wstring", "std::wstring", "", 0 }},
		{ "Vector3S", { "Vector3S", "Vector3S", "", 0 }},
		{ "vector", { "vector", "std::vector", "", 0 }}
	};

	std::unordered_map<unsigned short, PacketVersion> PacketVersions;

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

	void OpcodeParser::ReadDataRead(tinyxml2::XMLElement* element)
	{
		PacketRead& dataRead = Opcode.Reads.back();

		bool foundData = false;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				for (size_t i = 0; !foundData && i < Opcode.Layout.size(); ++i)
				{
					const PacketInfo& info = Opcode.Layout[i];

					if (info.Type != PacketInfoType::Data)
					{
						continue;
					}

					if (StackDepths[i] > StackDepths.back())
					{
						continue;
					}

					if (NodeStack[StackDepths[i] - 1].StartIndex > i)
					{
						continue;
					}

					PacketData& data = Opcode.Data[info.Index];

					if (data.Name == value)
					{
						data.Referenced = true;
						dataRead.DataIndex = i;
						foundData = true;
					}
				}

				if (!foundData)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in condition node" << std::endl;
				}

				dataRead.Name = value;

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in read node" << std::endl;
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

				size_t value = (size_t)atoll(valueAttrib->Value());

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

		bool foundData = false;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "data") == 0)
			{
				for (size_t i = 0; !foundData && i < Opcode.Layout.size(); ++i)
				{
					const PacketInfo& info = Opcode.Layout[i];

					if (info.Type != PacketInfoType::Data)
					{
						continue;
					}

					if (StackDepths[i] > StackDepths.back())
					{
						continue;
					}

					if (NodeStack[StackDepths[i] - 1].StartIndex > i)
					{
						continue;
					}

					PacketData& data = Opcode.Data[info.Index];

					if (data.Name == value)
					{
						data.Referenced = true;
						condition.DataIndex = i;
						foundData = true;
					}
				}

				if (!foundData)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in condition node" << std::endl;
				}

				continue;
			}
			if (strcmp(name, "value") == 0)
			{
				condition.Value = (size_t)atoll(value);

				continue;
			}
			if (strcmp(name, "bitIndex") == 0)
			{
				if (foundData)
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
				else
				{
					std::cout << FileName << ": unknown comparison type '" << value << "'" << std::endl;
				}

				continue;
			}

			std::cout << FileName << ": unknown attribute '" << name << "' in data node" << std::endl;
		}

		if (!foundData)
		{
			std::cout << FileName << ": condition data not found" << std::endl;
		}
	}

	void OpcodeParser::ReadArray(tinyxml2::XMLElement* element)
	{
		PacketArray& array = Opcode.Arrays.back();

		bool foundData = false;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "data") == 0)
			{
				for (size_t i = 0; !foundData && i < Opcode.Layout.size(); ++i)
				{
					const PacketInfo& info = Opcode.Layout[i];

					if (info.Type != PacketInfoType::Data)
					{
						continue;
					}

					if (StackDepths[i] > StackDepths.back())
					{
						continue;
					}

					if (NodeStack[StackDepths[i] - 1].StartIndex > i)
					{
						continue;
					}

					PacketData& data = Opcode.Data[info.Index];

					if (data.Name == value)
					{
						data.Referenced = true;
						array.DataIndex = info.Index;
						foundData = true;

						break;
					}
				}

				if (!foundData)
				{
					std::cout << FileName << ": unknown referenced data '" << value << "' in array node" << std::endl;
				}

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

		if (!foundData)
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

			if (node.Element != nullptr)
			{
				const char* name = node.Element->Name();

				if (strcmp(name, "data") == 0)
				{
					StackDepths.push_back(NodeStack.size());

					Opcode.Layout.push_back({ PacketInfoType::Data, Opcode.Data.size() });
					Opcode.Data.push_back({ Opcode.Data.size() });

					ReadData(node.Element);
				}
				else if (strcmp(name, "condition") == 0)
				{
					StackDepths.push_back(NodeStack.size());

					node.ConditionIndex = Opcode.Conditions.size();

					Opcode.Layout.push_back({ PacketInfoType::Condition, Opcode.Conditions.size() });
					Opcode.Conditions.push_back({});

					ReadCondition(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "output") == 0)
				{
					StackDepths.push_back(NodeStack.size());

					Opcode.Layout.push_back({ PacketInfoType::Output, Opcode.Outputs.size() });
					Opcode.Outputs.push_back({ Opcode.Outputs.size() });

					ReadOutput(node.Element);
				}
				else if (strcmp(name, "array") == 0)
				{
					StackDepths.push_back(NodeStack.size());

					node.ArrayIndex = Opcode.Arrays.size();

					Opcode.Layout.push_back({ PacketInfoType::Array, Opcode.Arrays.size() });
					Opcode.Arrays.push_back({});

					ReadArray(node.Element);

					NodeStack.push_back({ node.Element->FirstChildElement() });
					NodeStack.back().StartIndex = Opcode.Layout.size();

					continue;
				}
				else if (strcmp(name, "read") == 0)
				{
					StackDepths.push_back(NodeStack.size());

					Opcode.Layout.push_back({ PacketInfoType::DataRead, Opcode.Reads.size() });
					Opcode.Reads.push_back({ Opcode.Reads.size() });

					ReadDataRead(node.Element);
				}
				else
				{
					std::cout << FileName << ": unknown node '" << name << "'" << std::endl;
				}
			}

			while (NodeStack.size() && NodeStack.back().Element == nullptr)
			{
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

					next.ConditionIndex = (size_t)-1;
					next.ArrayIndex = (size_t)-1;
				}
			}

			if (NodeStack.size())
			{
				NodeStack.back().Element = NodeStack.back().Element->NextSiblingElement();
				NodeStack.back().ConditionIndex = (size_t)-1;
				NodeStack.back().ArrayIndex = (size_t)-1;
			}
		}
	}

	void readSchema(const fs::path& filePath)
	{
		tinyxml2::XMLDocument document;

		document.LoadFile(filePath.string().c_str());

		tinyxml2::XMLElement* root = document.RootElement();

		if (root == nullptr)
		{
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
					const tinyxml2::XMLAttribute* versionAttrib = opcodeElement->FindAttribute("version");
					const tinyxml2::XMLAttribute* opcodeAttrib = opcodeElement->FindAttribute("opcode");

					if (versionAttrib == nullptr || valueAttrib == nullptr || opcodeAttrib == nullptr)
					{
						if (versionAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing version attribute" << std::endl;
						}

						if (valueAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing value attribute" << std::endl;
						}

						if (opcodeAttrib)
						{
							std::cout << filePath.string() << ": opcodeReference node missing opcode attribute" << std::endl;
						}

						continue;
					}

					unsigned short value = 0;
					unsigned short version = (unsigned short)atoi(versionAttrib->Value());
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
					if (nameAttrib)
					{
						std::cout << filePath.string() << ": opcode node missing name attribute" << std::endl;
					}

					if (valueAttrib)
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

				OpcodeParser parser = { filePath.string(), opcode };

				parser.Read(opcodeElement);
			}
		}
	}

	void readSchemas(const fs::path& directory)
	{
		for (const auto& entry : fs::recursive_directory_iterator{ directory })
		{
			const fs::path& path = entry.path();

			if (!fs::is_regular_file(path) && !path.has_extension()) continue;

			fs::path extension = path.extension();

			if (extension != ".xml") continue;

			readSchema(path);
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

	struct DataOutput
	{
		std::string Name;
		const PacketOutput* Output = nullptr;
		const OutputSchema::SchemaMember* Member = nullptr;
		const OutputSchema::SchemaClass* Class = nullptr;
	};

	struct StackEntry
	{
		size_t StartIndex = (size_t)-1;
		size_t EndIndex = (size_t)-1;
		DataOutput Output;
		bool IsLoop = false;
		bool IncrementLoopCounter = false;
	};

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

	const OutputSchema::SchemaMember* findOutputMember(const PacketOutput* output, const std::string& path)
	{
		if (!output)
		{
			return nullptr;
		}

		return OutputSchema::findSchemaMember(output->Class, path);
	}

	DataOutput findOutput(DataOutput output, const std::string& path)
	{
		const OutputSchema::SchemaClass* outputClass = output.Class == nullptr ? output.Output->Class : output.Class;

		if (!output.Output)
		{
			return {};
		}

		output.Member = OutputSchema::findSchemaMember(outputClass, path);

		if (!output.Member)
		{
			return {};
		}

		output.Member = OutputSchema::findSchemaMember(outputClass, path);

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
			OutputSchema::SchemaEntry entry = OutputSchema::findSchemaEntry(output.Member->ContainsType, output.Output->SchemaName, ':');

			output.Class = entry.Class;

			if (entry.Class == nullptr)
			{
				std::cout << "failed to find class: '" << output.Member->ContainsType << "'" << std::endl;
			}
		}

		return output;
	}

	DataOutput findOutput(const std::string& name, const std::unordered_map<std::string, const PacketOutput*>& outputs, const PacketOutput* topOutput, const std::vector<StackEntry>& stack, const std::string& path)
	{
		DataOutput output = findOutput(name, outputs, topOutput, stack);

		return findOutput(output, path);
	}

	void generateParser(Generator& generator, std::ofstream& out, const PacketOpcode& opcode, std::unordered_set<const OutputSchema::SchemaClass*>& outputsReferenced)
	{
		generator.SetDepth(3);

		const auto& tabs = generator.Tabs;

		PacketInfoType lastType = PacketInfoType::Condition;

		std::vector<StackEntry> stack;
		std::unordered_map<std::string, const PacketOutput*> outputs;

		out << tabs << "using namespace ParserUtils::Packets;\n\n";

		const PacketOutput* topOutput = nullptr;

		for (size_t i = 0; i < opcode.Layout.size(); ++i)
		{
			while (stack.size() && i >= stack.back().EndIndex)
			{
				DataOutput& outputData = stack.back().Output;

				const PacketOutput* output = outputData.Output;

				if (output != nullptr && outputData.Member == nullptr)
				{
					if (!outputsReferenced.contains(output->Class))
					{
						outputsReferenced.insert(output->Class);
					}

					out << "\n" << tabs << "if (stream.Succeeded())\n" << tabs << "{\n";
					out << tabs << "\tPacketParsed<" << OutputSchema::stripCommonNamespaces(output->Class->Scope, "Networking::Packets", ':') << ">(" << *output << ");\n";

					if (output->ReturnOnFinish)
					{
						out << "\n\t" << tabs << "return;\n";
					}

					out << tabs << "}\n";

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
						out << "\n" << tabs << "++" << generator.LoopIndex << ";\n";
					}
				}

				generator.Pop();
				out << tabs << "}\n";
				stack.pop_back();
			}

			PacketInfoType type = opcode.Layout[i].Type;
			size_t index = opcode.Layout[i].Index;

			if (type == PacketInfoType::Data || type == PacketInfoType::DataRead)
			{
				if (type == PacketInfoType::DataRead)
				{
					const PacketRead& dataRead = opcode.Reads[index];

					index = opcode.Layout[dataRead.DataIndex].Index;
				}

				const PacketData& data = opcode.Data[index];

				DataOutput output = data.Output.size() ? findOutput(data.Target, outputs, topOutput, stack, data.Output) : DataOutput{};

				bool makeVariable = data.HasBitOutputs || data.Referenced || data.Output.size() == 0 || (output.Member && output.Member->Type != data.Type->TypeName);

				if ((lastType != PacketInfoType::Data || makeVariable || !output.Member) && lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array)
				{
					out << "\n";
				}

				if (type == PacketInfoType::Data)
				{
					if (makeVariable || !output.Member)
					{
						out << tabs << data.Type->TypeName << " " << data;

						if (data.Type->DefaultValue.size())
						{
							out << " = " << data.Type->DefaultValue;
						}

						out << ";\n";
					}
				}

				out << tabs << "Read<" << data.Type->TypeName << ">(\"" << data.Name << "\", stream, ";

				if (makeVariable || !output.Member)
				{
					out << data;
				}
				else
				{
					out << output.Name;
				}

				out << ", \"";

				for (size_t i = 0; i <= stack.size(); ++i)
				{
					out << "\\t";
				}

				out << "\"" << ");\n";

				if (data.EnumNames.size())
				{
					type = PacketInfoType::Validation;

					out << "\n" << tabs << "ValidateValues(stream, \"" << data.Name << "\", \"";

					for (size_t i = 0; i <= stack.size(); ++i)
					{
						out << "\\t";
					}
					
					out << "\", ";

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

					std::string typeName = OutputSchema::stripCommonNamespaces(data.Type->TypeName, "Networking::Packets", ':');

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

					out << "\n" << tabs << output.Name << " = " << "(" << OutputSchema::stripCommonNamespaces(output.Member->Type, "Networking::Packets", ':') << ")" << data << ";\n";
				}

				if (data.HasBitOutputs)
				{
					out << "\n";

					for (size_t i = 0; i < data.Flags.size(); ++i)
					{
						const PacketDataBit& bit = data.Flags[i];

						if (bit.Output.size())
						{
							DataOutput output = findOutput(bit.Target, outputs, topOutput, stack, bit.Output);

							out << tabs << output.Name << " = GetBit(" << data << ", " << i << ");\n";
						}
					}

					type = PacketInfoType::ValueWrite;
				}

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Array)
			{
				const PacketArray& array = opcode.Arrays[index];
				const PacketData& data = opcode.Data[array.DataIndex];

				DataOutput output = array.Output.size() ? findOutput(array.Target, outputs, topOutput, stack, array.Output) : DataOutput{};

				if (lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array)
				{
					out << "\n";
				}

				std::string containerName = output.Name;

				output.Name = containerName + '[' + generator.LoopIndex + ']';

				if (array.Type == PacketArray::TypeEnum::For)
				{
					out << tabs << containerName << ".resize(" << data << ");\n\n";

					out << tabs << "for (" << data.Type->TypeName << " " << generator.LoopIndex << " = 0; " << generator.LoopIndex << " < " << data << "; ++" << generator.LoopIndex << ")\n";
					out << tabs << "{\n";

					stack.push_back({ i, array.RegionEnd, output, true });
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
					out << tabs << "size_t " << generator.LoopIndex << " = 0;\n\n";

					out << tabs << "while (" << data << ")\n";
					out << tabs << "{\n";

					stack.push_back({ i, array.RegionEnd, output, true, true });
					generator.Push();

					out << tabs << containerName << ".push_back({});\n";

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

				size_t dataIndex = opcode.Layout[condition.DataIndex].Index;

				const PacketData& data = opcode.Data[dataIndex];

				if (lastType != PacketInfoType::Condition && lastType != PacketInfoType::Array)
				{
					out << "\n";
				}

				out << tabs << "if (";

				if (condition.BitIndex != 0xFF)
				{
					out << "GetBit(" << data << ", " << (int)condition.BitIndex << ")";
				}
				else
				{
					out << data;
				}

				if (condition.Comparison == PacketInfoComparison::Equal)
				{
					if (condition.Value != 1 || data.Type->TypeName != "bool")
					{
						out << " == " << condition.Value;
					}
				}
				else if (condition.Comparison == PacketInfoComparison::NotEqual)
				{
					out << " != " << condition.Value;
				}

				out << ")\n";
				out << tabs << "{\n";

				stack.push_back({ i, condition.RegionEnd });
				generator.Push();

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Output)
			{
				const PacketOutput& output = opcode.Outputs[index];

				out << tabs << OutputSchema::stripCommonNamespaces(output.Class->Scope, "Networking::Packets", ':') << " " << output << ";\n";

				if (stack.size())
				{
					stack.back().Output.Output = &output;
				}
				else
				{
					topOutput = &output;
				}

				outputs[output.Name] = &output;

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
				if (!outputsReferenced.contains(output->Class))
				{
					outputsReferenced.insert(output->Class);
				}

				out << "\n" << tabs << "if (stream.Succeeded())\n" << tabs << "{\n";
				out << tabs << "\tPacketParsed<" << OutputSchema::stripCommonNamespaces(output->Class->Scope, "Networking::Packets", ':') << ">(" << *output << ");\n";

				if (output->ReturnOnFinish)
				{
					out << "\n\t" << tabs << "return;\n";
				}

				out << tabs << "}\n";

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
					out << "\n" << tabs << "++" << generator.LoopIndex << ";\n";
				}
			}
			
			generator.Pop();
			out << tabs << "}\n";
			stack.pop_back();
		}

		if (topOutput)
		{
			if (!outputsReferenced.contains(topOutput->Class))
			{
				outputsReferenced.insert(topOutput->Class);
			}

			out << "\n" << tabs << "if (stream.Succeeded())\n" << tabs << "{\n";
			out << tabs << "\tPacketParsed<" << OutputSchema::stripCommonNamespaces(topOutput->Class->Scope, "Networking::Packets", ':') << ">(" << *topOutput << ");\n";

			if (topOutput->ReturnOnFinish)
			{
				out << "\n\t" << tabs << "return;\n";
			}

			out << tabs << "}\n";
		}

		generator.LoopIndex = 'i';
	}

	void generateParsers()
	{
		fs::path headerPath = packetProjDir / "src/PacketProcessing/PacketParser.h";

		{
			std::ofstream headerOut(headerPath);

			headerOut << "#pragma once\n\n";

			headerOut << "#include \"PacketParserBase.h\"\n\n";

			headerOut << "namespace Networking\n{\n";

			headerOut << "\tnamespace Packets\n\t{\n";

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;

				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", ClientPacket, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream);\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", ServerPacket, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream);\n\n";
				}
			}

			headerOut << "\t}\n";
			headerOut << "}\n";
		}

		fs::path cppPath = packetProjDir / "src/PacketProcessing/PacketParser.cpp";

		std::unordered_set<const OutputSchema::SchemaClass*> outputsReferenced;

		{
			std::ofstream cppOut(cppPath);

			cppOut << "#include \"PacketParser.h\"\n\n";
			cppOut << "#include <vector>\n\n";
			cppOut << "#include <ParserUtils/PacketParsing.h>\n\n";
			cppOut << "#include \"PacketOutput.h\"\n\n";

			cppOut << "namespace Networking\n{\n";

			cppOut << "\tnamespace Packets\n\t{\n";

			Generator generator;

			unsigned short minVersion = 0xFFFF;
			unsigned short maxVersion = 0;

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

			cppOut << "\t\tvoid ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode)\n";
			cppOut << "\t\t{\n";

			cppOut << "\t\t\tstatic const std::vector<size_t> versionIndices = {\n";
			cppOut << "\t\t\t\t";

			for (size_t i = 0; i < versionOverrides.size(); ++i)
			{
				cppOut << versionOverrides[i].Index;

				if (i + 1 < versionOverrides.size())
				{
					cppOut << ", ";
				}
			}

			cppOut << "\n";
			cppOut << "\t\t\t};\n";

			cppOut << "\t\t\tstatic const std::vector<PacketVersionData> versions = {\n";

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
							serverOpcodes[j - minServerOpcode] = versions[i - 1].ServerOpcodes[j - versions[i - 1].MinServerOpcode];
						}

						for (size_t j = minClientOpcode; j <= maxClientOpcode; ++j)
						{
							clientOpcodes[j - minClientOpcode] = versions[i - 1].ClientOpcodes[j - versions[i - 1].MinClientOpcode];
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

					cppOut << "\t\t\t\t{\n";
					cppOut << "\t\t\t\t\t0x" << std::hex << minServerOpcode << ", 0x" << minClientOpcode << std::dec << ",\n";

					if (serverOpcodes.size() > 0)
					{
						cppOut << "\t\t\t\t\t{\n";

						for (size_t i = 0; i < serverOpcodes.size(); ++i)
						{
							const OpcodeData& opcodeData = serverOpcodes[i];

							if (opcodeData.Reference != nullptr)
							{
								cppOut << "\t\t\t\t\t\t{ \"" << opcodeData.Name << "\", &ParsePacket<" << opcodeData.Reference->TargetVersion << ", ServerPacket, 0x" << std::hex << opcodeData.Reference->TargetOpcode << std::dec << "> }" << (i + 1 < serverOpcodes.size() ? ",\n" : "\n");

								continue;
							}

							const PacketOpcode* opcode = opcodeData.Opcode;

							if (!opcode)
							{
								cppOut << "\t\t\t\t\t\t{ \"\", &ParsePacket<0, false, 0> }" << (i + 1 < serverOpcodes.size() ? ",\n" : "\n");

								continue;
							}

							cppOut << "\t\t\t\t\t\t{ \"" << opcode->Name << "\", &ParsePacket<" << opcodeData.Version << ", ServerPacket, 0x" << std::hex << (minServerOpcode + i) << std::dec << (i + 1 < serverOpcodes.size() ? "> },\n" : "> }\n");
						}

						cppOut << "\t\t\t\t\t},\n";
					}
					else
					{
						cppOut << "\t\t\t\t\t{ },\n";
					}

					if (clientOpcodes.size() > 0)
					{
						cppOut << "\t\t\t\t\t{\n";

						for (size_t i = 0; i < clientOpcodes.size(); ++i)
						{
							const OpcodeData& opcodeData = clientOpcodes[i];

							if (opcodeData.Reference != nullptr)
							{
								cppOut << "\t\t\t\t\t\t{ \"" << opcodeData.Name << "\", &ParsePacket<" << opcodeData.Reference->TargetVersion << ", ClientPacket, 0x" << std::hex << opcodeData.Reference->TargetOpcode << std::dec << "> }" << (i + 1 < clientOpcodes.size() ? ",\n" : "\n");

								continue;
							}

							const PacketOpcode* opcode = opcodeData.Opcode;

							if (!opcode)
							{
								cppOut << "\t\t\t\t\t\t{ \"\", &ParsePacket<0, false, 0> }" << (i + 1 < clientOpcodes.size() ? ",\n" : "\n");

								continue;
							}

							cppOut << "\t\t\t\t\t\t{ \"" << opcode->Name << "\", &ParsePacket<" << opcodeData.Version << ", ClientPacket, 0x" << std::hex << (minClientOpcode + i) << std::dec << (i + 1 < clientOpcodes.size() ? "> },\n" : "> }\n");
						}

						cppOut << "\t\t\t\t\t}\n";
					}
					else
					{
						cppOut << "\t\t\t\t\t{ }\n";
					}

					cppOut << "\t\t\t\t}";

					if (i + 1 < versions.size())
					{
						cppOut << ",";
					}

					cppOut << "\n";
				}
			}

			cppOut << "\t\t\t};\n\n";

			cppOut << "\t\t\tsize_t versionIndex = version == 12 ? 0 : versionIndices[std::min(" << maxVersion - minVersion << ", std::max(version, (unsigned short)" << minVersion << ") - " << minVersion << ")];\n";

			cppOut << "\t\t\tconst PacketVersionData& versionData = versions[versionIndex];\n\n";

			cppOut << "\t\t\tsize_t minOpcode = isServer ? versionData.MinServerOpcode : versionData.MinClientOpcode;\n\n";
			cppOut << "\t\t\tconst auto& opcodes = isServer ? versionData.ServerCallbacks : versionData.ClientCallbacks;\n\n";

			cppOut << "\t\t\tif (opcode < minOpcode || opcode - minOpcode >= opcodes.size())\n";
			cppOut << "\t\t\t{\n";
			
			cppOut << "\t\t\t\treturn;\n";
			
			cppOut << "\t\t\t}\n\n";
			cppOut << "\t\t\tif constexpr (ParserUtils::Packets::PrintOutput)\n";
			cppOut << "\t\t\t{\n";
			cppOut << "\t\t\t\tstd::cout << \"[\" << version << \"] Packet Opcode 0x\" << std::hex << opcode << std::dec << \": \" << opcodes[opcode - minOpcode].Name << std::endl;\n";
			cppOut << "\t\t\t}\n\n";

			cppOut << "\t\t\topcodes[opcode - minOpcode].Callback(stream);\n";
;
			cppOut << "\t\t}\n\n";

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;


				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", ClientPacket, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second, outputsReferenced);

					cppOut << "\t\t}\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", ServerPacket, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second, outputsReferenced);

					cppOut << "\t\t}\n\n";
				}
			}

			cppOut << "\t}\n";
			cppOut << "}\n";
		}

		fs::path packetHeaderPath = packetProjDir / "src/PacketProcessing/PacketOutput.h";

		{
			std::ofstream headerOut(packetHeaderPath);

			headerOut << "#pragma once\n\n";

			headerOut << "#include \"PacketParserBase.h\"\n\n";

			for (const OutputSchema::SchemaClass* schemaClass : outputsReferenced)
			{
				headerOut << "#include <GameData/" << schemaClass->Directory << "/" << schemaClass->Name << ".h>\n";
			}

			headerOut << "\nnamespace Networking\n{\n";

			headerOut << "\tnamespace Packets\n\t{\n";

			for (const OutputSchema::SchemaClass* schemaClass : outputsReferenced)
			{
				std::string typeName = OutputSchema::stripCommonNamespaces(schemaClass->Scope, "Networking::Packets", ':');
				headerOut << "\t\ttemplate <>\n";
				headerOut << "\t\tvoid PacketParsed<" << typeName << ">(const " << typeName << "& packet);\n\n";
			}

			headerOut << "\t}\n";
			headerOut << "}\n";
		}
	}
}
