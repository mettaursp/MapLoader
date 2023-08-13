#include "PacketScheam.h"

#include <iostream>
#include <fstream>

namespace PacketSchema
{
	const std::unordered_map<std::string, PacketType> PacketTypes = {
		{ "byte", { "byte", "unsigned char", "0", 1}},
		{ "short", { "short", "short", "0", 2}},
		{ "int", { "int", "int", "0", 4}},
		{ "long", { "long", "long long", "0", 8}}
	};

	std::unordered_map<unsigned short, PacketVersion> PacketVersions;

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

				if (bitIndex >= data.BitNames.size())
				{
					data.BitNames.resize(bitIndex + 1);
				}

				data.BitNames[bitIndex] = nameAttrib->Value();

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
				for (size_t i = 0; i < Opcode.Layout.size(); ++i)
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

					const PacketData& data = Opcode.Data[info.Index];

					if (data.Name == value)
					{
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
					Opcode.Data.push_back({ Opcode.Data.size()});

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

					next.ConditionIndex = (size_t)-1;
				}
			}

			if (NodeStack.size())
			{
				NodeStack.back().Element = NodeStack.back().Element->NextSiblingElement();
				NodeStack.back().ConditionIndex = (size_t)-1;
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

		short version = atoi(versionAttrib->Value());

		PacketVersion& schema = PacketVersions[version];

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

				short value = atoi(valueAttrib->Value());

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

	void generateParser(Generator& generator, std::ofstream& out, const PacketOpcode& opcode)
	{
		generator.SetDepth(3);

		const auto& tabs = generator.Tabs;

		PacketInfoType lastType = PacketInfoType::Condition;

		struct StackEntry
		{
			size_t StartIndex = (size_t)-1;
			size_t EndIndex = (size_t)-1;
		};

		std::vector<StackEntry> stack;

		out << tabs << "using namespace ParserUtils::Packets;\n\n";

		for (size_t i = 0; i < opcode.Layout.size(); ++i)
		{
			while (stack.size() && i >= stack.back().EndIndex)
			{
				generator.Pop();
				out << tabs << "}\n";
				stack.pop_back();
			}

			PacketInfoType type = opcode.Layout[i].Type;
			size_t index = opcode.Layout[i].Index;

			if (type == PacketInfoType::Data)
			{
				const PacketData& data = opcode.Data[index];

				out << tabs << data.Type->TypeName << " " << data << " = " << data.Type->DefaultValue << ";\n";

				//out << tabs << "stream.Read<" << data.Type->TypeName << ">(" << data << ");\n";
				out << tabs << "Read<" << data.Type->TypeName << ">(\"" << data.Name << "\", stream, " << data << ", \"";

				for (size_t i = 0; i <= stack.size(); ++i)
				{
					out << "\\t";
				}

				out << "\"" << ");\n";

				lastType = type;

				continue;
			}

			if (type == PacketInfoType::Condition)
			{
				const PacketCondition& condition = opcode.Conditions[index];

				size_t dataIndex = opcode.Layout[condition.DataIndex].Index;

				const PacketData& data = opcode.Data[dataIndex];

				if (lastType == PacketInfoType::Data)
				{
					out << "\n";
				}

				out << tabs << "if (";

				if (condition.BitIndex != 0xFF)
				{
					out << "(1 & (" << data << " >> " << (int)condition.BitIndex << "))";
				}
				else
				{
					out << data;
				}

				if (condition.Comparison == PacketInfoComparison::Equal)
				{
					out << " == " << condition.Value;
				}

				out << ")\n";
				out << tabs << "{\n";

				stack.push_back({ i, condition.RegionEnd });
				generator.Push();

				lastType = type;

				continue;
			}
		}

		while (stack.size())
		{
			generator.Pop();
			out << tabs << "}\n";
			stack.pop_back();
		}
	}

	void generateParsers()
	{
		fs::path headerPath = packetProjDir / "src/PacketProcessing/PacketParser.h";

		{
			std::ofstream headerOut(headerPath);

			headerOut << "#pragma once\n\n";

			headerOut << "#include <ParserUtils/DataStream.h>\n\n";

			headerOut << "namespace Networking\n{\n";

			headerOut << "\tnamespace Packets\n\t{\n";

			headerOut << "\t\tvoid ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode);\n\n";

			headerOut << "\t\tconst bool Server = true;\n";
			headerOut << "\t\tconst bool Client = false;\n\n";

			headerOut << "\t\ttemplate <short Version, bool IsServer, short Opcode>\n";
			headerOut << "\t\tvoid ParsePacket(ParserUtils::DataStream& stream)\n";
			headerOut << "\t\t{\n";
			//headerOut << "\t\t\tstatic_assert(false, \"unimplemented packet structure\");\n";
			headerOut << "\t\t}\n\n";

			headerOut << "\t\ttemplate <>\n";
			headerOut << "\t\tvoid ParsePacket<0, false, 0>(ParserUtils::DataStream& stream);\n\n";

			headerOut << "\t\ttypedef void (*PacketParserCallback)(ParserUtils::DataStream& stream);\n\n";

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;

				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", Client, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream);\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					headerOut << "\t\ttemplate <>\n";
					headerOut << "\t\tvoid ParsePacket<" << version << ", Server, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream);\n\n";
				}
			}

			headerOut << "\t}\n";
			headerOut << "}\n";
		}

		fs::path cppPath = packetProjDir / "src/PacketProcessing/PacketParser.cpp";

		{
			std::ofstream cppOut(cppPath);

			cppOut << "#include \"PacketParser.h\"\n\n";
			cppOut << "#include <vector>\n\n";
			cppOut << "#include <ParserUtils/PacketParsing.h>\n\n";

			cppOut << "namespace Networking\n{\n";

			cppOut << "\tnamespace Packets\n\t{\n";

			Generator generator;

			unsigned short minVersion = 0xFFFF;
			unsigned short maxVersion = 0;

			for (const auto& versionEntry : PacketVersions)
			{
				minVersion = std::min(minVersion, versionEntry.first);
				maxVersion = std::max(maxVersion, versionEntry.first);
			}

			std::vector<const PacketVersion*> versions(maxVersion - minVersion + 1);

			for (const auto& versionEntry : PacketVersions)
			{
				versions[versionEntry.first - minVersion] = &versionEntry.second;
			}

			cppOut << "\t\ttemplate <>\n";
			cppOut << "\t\tvoid ParsePacket<0, false, 0>(ParserUtils::DataStream& stream) { }\n\n";

			cppOut << "\t\tvoid ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode)\n";
			cppOut << "\t\t{\n";

			cppOut << "\t\t\tstruct PacketVersionData\n";
			cppOut << "\t\t\t{\n";
				
			cppOut << "\t\t\t\tsize_t MinServerOpcode = 0;\n";
			cppOut << "\t\t\t\tsize_t MinClientOpcode = 0;\n";
			cppOut << "\t\t\t\tstd::vector<PacketParserCallback> ServerCallbacks;\n";
			cppOut << "\t\t\t\tstd::vector<PacketParserCallback> ClientCallbacks;\n";

			cppOut << "\t\t\t};\n\n";

			cppOut << "\t\t\tstatic const std::vector<PacketVersionData> versions = {\n";

			for (size_t i = 0; i < versions.size(); ++i)
			{
				if (versions[i] == nullptr)
				{
					cppOut << ((i + 1 < versions.size()) ? "\t\t\t\t{ 0, 0 },\n" : "\t\t\t\t{ 0, 0 }\n");

					continue;
				}

				size_t versionId = minVersion + i;

				{
					unsigned short minServerOpcode = 0xFFFF;
					unsigned short maxServerOpcode = 0;
					unsigned short minClientOpcode = 0xFFFF;
					unsigned short maxClientOpcode = 0;

					for (const auto& opcodeEntry : versions[i]->ServerOpcodes)
					{
						minServerOpcode = std::min(minServerOpcode, opcodeEntry.first);
						maxServerOpcode = std::max(maxServerOpcode, opcodeEntry.first);
					}

					for (const auto& opcodeEntry : versions[i]->ClientOpcodes)
					{
						minClientOpcode = std::min(minClientOpcode, opcodeEntry.first);
						maxClientOpcode = std::max(maxClientOpcode, opcodeEntry.first);
					}

					std::vector<bool> serverOpcodes(versions[i]->ServerOpcodes.size() ? maxServerOpcode - minServerOpcode + 1 : 0);
					std::vector<bool> clientOpcodes(versions[i]->ClientOpcodes.size() ? maxClientOpcode - minClientOpcode + 1 : 0);

					for (const auto& opcodeEntry : versions[i]->ServerOpcodes)
					{
						serverOpcodes[opcodeEntry.first - minServerOpcode] = true;
					}

					for (const auto& opcodeEntry : versions[i]->ClientOpcodes)
					{
						clientOpcodes[opcodeEntry.first - minClientOpcode] = true;
					}

					cppOut << "\t\t\t\t{\n";
					cppOut << "\t\t\t\t\t" << minServerOpcode << ", " << minClientOpcode << ",\n";

					if (serverOpcodes.size() > 0)
					{
						cppOut << "\t\t\t\t\t{\n";

						for (size_t i = 0; i < serverOpcodes.size(); ++i)
						{
							if (!serverOpcodes[i])
							{
								cppOut << "\t\t\t\t\t\t&ParsePacket<0, false, 0>" << (i + 1 < serverOpcodes.size() ? ",\n" : "\n");

								continue;
							}

							cppOut << "\t\t\t\t\t\t&ParsePacket<" << versionId << ", Server, " << (minServerOpcode + i) << (i + 1 < serverOpcodes.size() ? ">,\n" : ">\n");
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
							if (!clientOpcodes[i])
							{
								cppOut << "\t\t\t\t\t\t&ParsePacket<0, false, 0>" << (i + 1 < clientOpcodes.size() ? ",\n" : "\n");
							}
							cppOut << "\t\t\t\t\t\t&ParsePacket<" << versionId << ", Client, " << (minClientOpcode + i) << (i + 1 < clientOpcodes.size() ? ">,\n" : ">\n");
						}

						cppOut << "\t\t\t\t\t}\n";
					}
					else
					{
						cppOut << "\t\t\t\t\t{ }\n";
					}

					cppOut << "\t\t\t\t}\n";
				}
			}

			cppOut << "\t\t\t};\n\n";

			cppOut << "\t\t\tif (version < " << minVersion << " || version > " << maxVersion << ")\n";
			cppOut << "\t\t\t{\n";

			cppOut << "\t\t\t\treturn;\n";

			cppOut << "\t\t\t}\n\n";

			cppOut << "\t\t\tconst PacketVersionData& versionData = versions[version - " << minVersion << "];\n\n";

			cppOut << "\t\t\tsize_t minOpcode = isServer ? versionData.MinServerOpcode : versionData.MinClientOpcode;\n\n";
			cppOut << "\t\t\tconst auto& opcodes = isServer ? versionData.ServerCallbacks : versionData.ClientCallbacks;\n\n";

			cppOut << "\t\t\tif (opcode < minOpcode || opcode - minOpcode >= opcodes.size())\n";
			cppOut << "\t\t\t{\n";

			cppOut << "\t\t\t\treturn;\n";

			cppOut << "\t\t\t}\n\n";
			cppOut << "\t\t\tif constexpr (ParserUtils::Packets::PrintOutput)\n";
			cppOut << "\t\t\t{\n";
			cppOut << "\t\t\t\tstd::cout << \"[\" << version << \"] Packet Opcode 0x\" << std::hex << opcode << std::dec << std::endl; \n";
			cppOut << "\t\t\t}\n\n";

			cppOut << "\t\t\topcodes[opcode - minOpcode](stream);\n";
;
			cppOut << "\t\t}\n\n";

			for (const auto& versionEntry : PacketVersions)
			{
				short version = versionEntry.first;


				for (const auto& opcodeEntry : versionEntry.second.ClientOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", Client, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second);

					cppOut << "\t\t}\n\n";
				}

				for (const auto& opcodeEntry : versionEntry.second.ServerOpcodes)
				{
					short opcode = opcodeEntry.first;

					cppOut << "\t\ttemplate <>\n";
					cppOut << "\t\tvoid ParsePacket<" << version << ", Server, 0x" << std::hex << opcode << std::dec << ">(ParserUtils::DataStream& stream)\n";
					cppOut << "\t\t{\n";

					generateParser(generator, cppOut, opcodeEntry.second);

					cppOut << "\t\t}\n\n";
				}
			}

			cppOut << "\t}\n";
			cppOut << "}\n";
		}
	}
}
