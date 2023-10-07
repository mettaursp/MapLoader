#include "ModuleWriter.h"

#include <iostream>

namespace OutputSchema
{
	const fs::path gameDataProjDir = "./../GameData";

	void addProjectNode(tinyxml2::XMLElement* root, const char* nodeType, const std::string& fileName, const char* filterContents)
	{
		tinyxml2::XMLElement* itemGroup = root->InsertNewChildElement("ItemGroup");
		tinyxml2::XMLElement* item = itemGroup->InsertNewChildElement(nodeType);

		item->SetAttribute("Include", fileName.c_str());

		if (!filterContents)
		{
			return;
		}

		tinyxml2::XMLElement* filter = item->InsertNewChildElement("Filter");

		filter->SetText(filterContents);
	}

	ModuleWriter::StackHandle::~StackHandle()
	{
		if (!Writer)
		{
			return;
		}

		size_t currentDepth = Writer->GetStackDepth();

		if (currentDepth != StackDepth)
		{
			std::cout << "mismatching stack depth on StackHandle cleanup! expected '" << StackDepth << "', got '" << currentDepth << "'" << std::endl;

			return;
		}

		Writer->PopStack();

		Writer = nullptr;
		StackDepth = (size_t)-1;
	}

	ModuleWriter::~ModuleWriter()
	{
		while (Stack.size())
		{
			PopStack();
		}
	}

	void ModuleWriter::StackHandle::Bind(ModuleWriter& writer)
	{
		if (Writer)
		{
			std::cout << "StackHandle already bound to ModuleWriter" << std::endl;

			return;
		}

		Writer = &writer;
		StackDepth = writer.GetStackDepth();
	}

	void ModuleWriter::PushNamespace(const std::string_view& name)
	{
		Out << Indent() << "namespace " << name << "\n";
		Out << Indent() << "{\n";

		Indentation.push_back('\t');
		Stack.push_back({});

		StackContext& context = Stack.back();

		context.IsNamespace = true;
	}

	void ModuleWriter::PushNamespace(StackHandle& handle, const std::string_view& name)
	{
		PushNamespace(name);

		handle.Bind(*this);
	}

	void ModuleWriter::PushStruct(const std::string_view& name)
	{
		Out << Indent() << "struct " << name << "\n";
		Out << Indent() << "{\n";

		Indentation.push_back('\t');
		Stack.push_back({});
	}

	void ModuleWriter::PushEnum(const std::string_view& name, const std::string_view& parent)
	{
		Out << Indent() << "enum class " << name;

		if (parent.size())
		{
			Out << " : " << parent;
		}

		Out << "\n";
		Out << Indent() << "{\n";

		Indentation.push_back('\t');
		Stack.push_back({});
	}

	void ModuleWriter::PushEnum(StackHandle& handle, const std::string_view& name, const std::string_view& parent)
	{
		PushEnum(name, parent);

		handle.Bind(*this);
	}

	void ModuleWriter::PushLine()
	{
		Out << Indent() << "\n";
	}

	const std::unordered_map<std::string, std::string> TypeDefaultValues = {
		{ "char", "0" },
		{ "unsigned char", "0" },
		{ "signed char", "0" },
		{ "short", "0" },
		{ "unsigned short", "0" },
		{ "int", "0" },
		{ "unsigned int", "0" },
		{ "long long", "0" },
		{ "unsigned long long", "0" },
		{ "float", "0" },
		{ "double", "0" },
		{ "bool", "false" },
	};

	void ModuleWriter::PushMember(const SchemaClass& type)
	{
		Out << Indent() << swapSeparator(stripCommonNamespaces(type.TypeName, type.Scope), "::") << " " << type.MemberName << ";\n";
	}

	void ModuleWriter::PushMember(const std::string& type, const std::string_view& name, const std::string_view& value)
	{
		Out << Indent() << type << " " << name;

		if (value.size())
		{
			Out << " = " << value;
		}
		else
		{
			auto valueEntry = TypeDefaultValues.find(std::string(type));

			if (valueEntry != TypeDefaultValues.end())
			{
				Out << " = " << valueEntry->second;
			}
		}

		Out << ";\n";
	}

	void ModuleWriter::PushMember(const std::string& type, const std::string_view& name, size_t arrayLength)
	{
		Out << Indent() << type << " " << name << "[" << arrayLength << "] = {};\n";
	}

	void ModuleWriter::PushMember(const std::string& type, const std::string_view& name, const std::vector<std::string>& initializers)
	{
		Out << Indent() << type << " " << name << (initializers.size() ? " = {\n" : " = { };\n");

		if (!initializers.size())
		{
			return;
		}

		for (size_t i = 0; i < initializers.size(); ++i)
		{
			Out << Indent() << "\t" << initializers[i] << (i + 1 < initializers.size() ? ",\n" : "\n");
		}

		Out << Indent() << "};\n";
	}

	void ModuleWriter::PushEnumValue(const std::string& name, const std::string_view& value, bool isLast)
	{
		Out << Indent() << name;

		if (value.size())
		{
			Out << " = " << value;
		}

		Out << (isLast ? "\n" : ",\n");
	}

	void ModuleWriter::PushStruct(StackHandle& handle, const std::string_view& name)
	{
		PushStruct(name);

		handle.Bind(*this);
	}

	void ModuleWriter::PushCollection(const std::string_view& name)
	{
		Out << Indent() << "class " << name << "\n";
		Out << Indent() << "{\n";

		Indentation.push_back('\t');
		Stack.push_back({});

		StackContext& context = Stack.back();

		context.CurrentlyPrivate = true;
	}

	void ModuleWriter::PushCollection(StackHandle& handle, const std::string_view& name)
	{
		PushCollection(name);

		handle.Bind(*this);
	}

	void ModuleWriter::PopStack()
	{
		bool isNamespace = Stack.back().IsNamespace;

		Stack.pop_back();
		Indentation.pop_back();

		Out << Indent() << (isNamespace ? "}\n" : "};\n");
	}

	void generateModuleNamespace(ModuleWriter& module, const std::string& currentNamespace)
	{
		size_t depth = 0;
		size_t i = 0;
		size_t length = 0;

		for (depth; currentNamespace[i + length]; ++depth)
		{
			while (currentNamespace[i + length] && currentNamespace[i + length] != '.')
			{
				++length;
			}

			if (depth > module.GetStackDepth())
			{
				module.PushNamespace({ currentNamespace.data() + i, length });
			}

			i += length;
			length = 0;
			++depth;

			if (currentNamespace[i])
			{
				++i;
			}
		}

		while (module.GetStackDepth() > depth)
		{
			module.PopStack();
		}
	}

	void generateEnumDefinitions(const SchemaEnum& schemaEnum, ModuleWriter& module, const std::string& currentNamespace)
	{
		module.PushEnum(schemaEnum.Name, schemaEnum.ParentType);

		for (size_t i = 0; i < schemaEnum.Values.size(); ++i)
		{
			const SchemaEnumValue& enumValue = schemaEnum.Values[i];

			module.PushEnumValue(enumValue.Name, enumValue.Value, i + 1 == schemaEnum.Values.size());
		}

		module.PopStack();
	}

	void generateClassDefinitions(const SchemaClass& schemaClass, ModuleWriter& module, const std::string& currentNamespace)
	{
		module.PushStruct(schemaClass.Name);

		bool isFirst = true;

		for (const SchemaEnum& childEnum : schemaClass.Enums)
		{
			if (!isFirst)
			{
				module.PushLine();
			}

			isFirst = false;

			generateEnumDefinitions(childEnum, module, currentNamespace);
		}

		for (const SchemaClass& childClass : schemaClass.ChildClasses)
		{
			if (!isFirst)
			{
				module.PushLine();
			}

			isFirst = false;

			generateClassDefinitions(childClass, module, currentNamespace);
		}

		if (schemaClass.Members.size())
		{
			if (!isFirst)
			{
				module.PushLine();
			}

			size_t memberClasses = 0;

			for (const SchemaClass& childClass : schemaClass.ChildClasses)
			{
				if (childClass.IsMember)
				{
					module.PushMember(childClass);

					++memberClasses;
				}
			}

			if (memberClasses > 0 && memberClasses < schemaClass.Members.size())
			{
				module.PushLine();
			}

			if (memberClasses < schemaClass.Members.size())
			{
				for (const SchemaMember& member : schemaClass.Members)
				{
					if (member.ChildClassIndex != (size_t)-1)
					{
						continue;
					}
					
					std::string typeName = swapSeparator(stripCommonNamespaces(member.Type, schemaClass.Scope), "::");

					if (member.ContainsType.size())
					{
						std::string innerTypeName = swapSeparator(stripCommonNamespaces(member.ContainsType, schemaClass.Scope), "::");

						if (member.Type == "array")
						{
							module.PushMember(innerTypeName, member.Name, member.Length);

							continue;
						}
						else
						{
							typeName += "<" + innerTypeName + ">";
						}
					}

					if (member.DefaultInitializerValues.size())
					{
						std::vector<std::string> values(member.DefaultInitializerValues.size());
						std::vector<unsigned long long> order(member.DefaultInitializerValues.size());

						unsigned int current = 0;
						size_t cutOut = 0;

						SchemaEntry entry = findSchemaEntry(member.Type, pickSchema(member.SchemaName, member.ParentSchemaName));

						if (entry.Class == nullptr)
						{
							module.PushMember(typeName, member.Name, "");

							continue;
						}

						for (const auto& initializerEntry : member.DefaultInitializerValues)
						{
							unsigned long long memberIndex = (unsigned long long)-1;
							const SchemaMember* referredMember = nullptr;

							for (size_t i = 0; i < entry.Class->Members.size(); ++i)
							{
								if (entry.Class->Members[i].Name == initializerEntry.first)
								{
									referredMember = &entry.Class->Members[i];
									memberIndex = (unsigned long long)-1;

									break;
								}
							}

							order[current] = (unsigned long long)current | (memberIndex << 32);

							if (referredMember == nullptr)
							{
								++current;
								++cutOut;

								continue;
							}

							SchemaEntry entry = findSchemaEntry(referredMember->Type, pickSchema(referredMember->SchemaName, referredMember->ParentSchemaName));

							values[current] = "." + initializerEntry.first + " = ";

							if (entry.Type != SchemaEntryType::None)
							{
								values[current] += swapSeparator(initializerEntry.second, "::");
							}
							else
							{
								values[current] += initializerEntry.second;
							}

							++current;
						}

						std::vector<std::string> initializers(member.DefaultInitializerValues.size() - cutOut);

						for (size_t i = 0; i < initializers.size(); ++i)
						{
							size_t index = (size_t)(order[i] & 0xFFFFFFFF);

							initializers[i] = values[index];
						}

						module.PushMember(typeName, member.Name, initializers);

						continue;
					}

					std::string defaultValue = member.DefaultValue;

					SchemaEntry entry = findSchemaEntry(member.Type, pickSchema(member.SchemaName, member.ParentSchemaName));

					if (member.DefaultValue.size())
					{
						if (entry.Type != SchemaEntryType::None)
						{
							defaultValue = swapSeparator(member.DefaultValue, "::");
						}
					}
					else if (entry.Enum)
					{
						defaultValue = "(" + typeName + ")0";
					}

					module.PushMember(typeName, member.Name, defaultValue);
				}
			}
		}

		module.PopStack();
	}

	void generateClassDeclarations(const SchemaClass& schemaClass, ModuleWriter& module, const std::string& currentNamespace, const std::string& classPath)
	{

		for (const SchemaClass& childClass : schemaClass.ChildClasses)
		{
			generateClassDeclarations(childClass, module, currentNamespace, classPath + "::" + childClass.TypeName);
		}
	}

	void generateCollectionDefinitions(const SchemaCollection& schemaCollection, ModuleWriter& module, const std::string& currentNamespace)
	{

	}

	void generateCollectionDeclarations(const SchemaCollection& schemaCollection, ModuleWriter& module, const std::string& currentNamespace, const std::string& classPath)
	{

	}

	struct OutputNamespace
	{
		std::unordered_map<std::string, const SchemaEnum*> Enums;
		std::unordered_map<std::string, const SchemaClass*> Classes;
		std::unordered_map<std::string, OutputNamespace> Namespaces;
	};

	struct OutputFile
	{
		std::string Directory;
		OutputNamespace Global;
		std::unordered_set<std::string> RequiredHeaders;
	};

	std::unordered_map<std::string, OutputFile> outputFiles;

	void generateClasses(const SchemaClass& schemaClass, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		fs::path outputDir = gameDataProjDir / "src/GameData" / schemaClass.Directory;
		fs::path outputHeader = outputDir / (schemaClass.Name + ".h");
		fs::path outputCpp = outputDir / (schemaClass.Name + ".cpp");

		if (schemaClass.FileName.size())
		{
			return;
		}

		if (outputFiles.contains(outputHeader.string()))
		{
			fs::create_directories(outputDir);

			std::string fileName = outputHeader.string();

			OutputFile& file = outputFiles[fileName];

			for (const std::string& requiredHeader : schemaClass.RequiredHeaders)
			{
				if (!file.RequiredHeaders.contains(requiredHeader))
				{
					file.RequiredHeaders.insert(requiredHeader);
				}
			}

			file.Directory = schemaClass.Directory;

			OutputNamespace* current = &file.Global;

			size_t start = 0;
			size_t length = 0;

			while (start < currentNamespace.size())
			{
				for (length; start + length < currentNamespace.size() && currentNamespace[start + length] != '.'; ++length);

				if (length == 0)
				{
					break;
				}

				std::string_view name = { currentNamespace.data() + start, length };

				start += length + 1;
				length = 0;

				current = &current->Namespaces[std::string(name)];
			}

			current->Classes[schemaClass.Name] = &schemaClass;

			return;
		}

		fs::create_directories(outputDir);

		addProjectNode(vcxprojRoot, "ClInclude", outputHeader.string(), nullptr);
		//addProjectNode(vcxprojRoot, "ClCompile", outputCpp.string(), nullptr);

		std::string filter = "Source Files\\" + schemaClass.Directory;

		addProjectNode(filtersRoot, "ClInclude", outputHeader.string(), filter.c_str());
		//addProjectNode(filtersRoot, "ClCompile", outputCpp.string(), filter.c_str());

		{
			std::ofstream outFile(outputHeader);

			outFile << "#pragma once\n\n";

			for (const std::string& requiredHeader : schemaClass.RequiredHeaders)
			{
				outFile << "#include " << requiredHeader << "\n";
			}

			if (schemaClass.RequiredHeaders.size())
			{
				outFile << "\n";
			}

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			generateClassDefinitions(schemaClass, module, currentNamespace);
		}

		{
			std::ofstream outFile(outputCpp);

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			generateClassDeclarations(schemaClass, module, currentNamespace, schemaClass.Name);
		}
	}

	void generateEnum(const SchemaEnum& schemaEnum, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		fs::path outputDir = gameDataProjDir / "src/GameData" / schemaEnum.Directory;
		fs::path outputHeader = outputDir / (schemaEnum.Name + ".h");

		if (schemaEnum.FileName.size())
		{
			return;
		}

		if (outputFiles.contains(outputHeader.string()))
		{
			fs::create_directories(outputDir);

			std::string fileName = outputHeader.string();

			OutputFile& file = outputFiles[fileName];

			file.Directory = schemaEnum.Directory;

			OutputNamespace* current = &file.Global;

			size_t start = 0;
			size_t length = 0;

			while (start < currentNamespace.size())
			{
				for (length; start + length < currentNamespace.size() && currentNamespace[start + length] != '.'; ++length);

				if (length == 0)
				{
					break;
				}

				std::string_view name = { currentNamespace.data() + start, length };

				start += length + 1;
				length = 0;

				current = &current->Namespaces[std::string(name)];
			}

			current->Enums[schemaEnum.Name] = &schemaEnum;

			return;
		}

		fs::create_directories(outputDir);

		addProjectNode(vcxprojRoot, "ClInclude", outputHeader.string(), nullptr);

		std::string filter = "Source Files\\" + schemaEnum.Directory;

		addProjectNode(filtersRoot, "ClInclude", outputHeader.string(), filter.c_str());

		{
			std::ofstream outFile(outputHeader);

			outFile << "#pragma once\n\n";

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			generateEnumDefinitions(schemaEnum, module, currentNamespace);
		}
	}

	void generateEnums(ModuleWriter& module, const OutputNamespace& out, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace, bool pushNamespace = true)
	{
		size_t i = 0;

		for (const auto& current : out.Enums)
		{
			if (i)
			{
				module.PushLine();
			}

			generateEnumDefinitions(*current.second, module, currentNamespace);

			++i;
		}

		for (const auto& current : out.Classes)
		{
			if (i)
			{
				module.PushLine();
			}

			generateClassDefinitions(*current.second, module, currentNamespace);

			++i;
		}

		for (const auto& current : out.Namespaces)
		{
			if (pushNamespace)
			{
				module.PushNamespace(current.first);
			}

			generateEnums(module, current.second, vcxprojRoot, filtersRoot, currentNamespace.size() ? currentNamespace + "." + current.first : current.first);

			if (pushNamespace)
			{
				module.PopStack();
			}
		}
	}

	bool pathEquals(const std::string& path1, const std::string& path2)
	{
		if (path1.size() != path2.size())
		{
			return false;
		}

		for (size_t i = 0; i < path1.size(); ++i)
		{
			char char1 = path1[i];
			char char2 = path2[i];

			if (char1 >= 'A' && char1 <= 'Z')
			{
				char1 += 'a' - 'A';
			}

			if (char1 == '\\')
			{
				char1 = '/';
			}

			if (char2 >= 'A' && char2 <= 'Z')
			{
				char2 += 'a' - 'A';
			}

			if (char2 == '\\')
			{
				char2 = '/';
			}

			if (char1 != char2)
			{
				return false;
			}
		}

		return true;
	}

	void generateEnums(tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot)
	{
		for (const auto& file : outputFiles)
		{
			std::string outputHeader = file.first;
			std::string outputHeaderBase;

			const char findBase[] = "src/";

			for (size_t i = 0; i < outputHeader.size() - 4 && !outputHeaderBase.size(); ++i)
			{
				bool skip = false;

				for (size_t j = 0; j < 4 && !skip; ++j)
				{
					skip = outputHeader[i + j] != findBase[j];
				}

				if (!skip)
				{
					i += 4;

					outputHeaderBase = outputHeader.substr(i, outputHeader.size() - i);
				}
			}

			addProjectNode(vcxprojRoot, "ClInclude", outputHeader, nullptr);

			std::string filter = "Source Files\\" + file.second.Directory;

			addProjectNode(filtersRoot, "ClInclude", outputHeader, filter.c_str());

			{
				std::ofstream outFile(outputHeader);

				outFile << "#pragma once\n\n";

				for (const std::string& requiredHeader : file.second.RequiredHeaders)
				{
					std::string requiredHeaderBase = requiredHeader.substr(1, requiredHeader.size() - 2);

					if (pathEquals(requiredHeaderBase, outputHeaderBase))
					{
						continue;
					}

					outFile << "#include " << requiredHeader << "\n";
				}

				if (file.second.RequiredHeaders.size())
				{
					outFile << "\n";
				}

				ModuleWriter module(outFile);

				generateEnums(module, file.second.Global, vcxprojRoot, filtersRoot, "", false);
			}
		}
	}

	void generateCollection(const SchemaCollection& schemaCollection, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		fs::path outputDir = gameDataProjDir / "src/GameData/Collection";
		fs::path outputHeader = outputDir / (schemaCollection.Name + ".h");
		fs::path outputCpp = outputDir / (schemaCollection.Name + ".cpp");

		addProjectNode(vcxprojRoot, "ClInclude", outputHeader.string(), nullptr);
		addProjectNode(vcxprojRoot, "ClCompile", outputCpp.string(), nullptr);

		addProjectNode(filtersRoot, "ClInclude", outputHeader.string(), "Source Files\\Collection");
		addProjectNode(filtersRoot, "ClCompile", outputCpp.string(), "Source Files\\Collection");

		{
			std::ofstream outFile(outputHeader);

			outFile << "#pragma once\n\n";

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			module.PushCollection(schemaCollection.Name);

			generateCollectionDefinitions(schemaCollection, module, currentNamespace);
		}

		{
			std::ofstream outFile(outputCpp);

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			generateCollectionDeclarations(schemaCollection, module, currentNamespace, schemaCollection.Name);
		}
	}

	/*
		note: attribute is 'Include' for both ClCompile and ClInclude
		vcxproj:
		<ItemGroup>
			<ClInclude/ClCompile Include="src\GameData\TestFile.h"/>
		</ItemGroup>
		filters:
		<ItemGroup>
			<ClInclude/ClCompile Include="src\GameData\TestFile.h">
				<Filter>Source Files\Collection</Filter>
			</ClInclude/ClCompile>
		</ItemGroup>
	*/

	void generateItemsInNamespace(const SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		for (const SchemaNamespace& childNamespace : schemaNamespace.Namespaces)
		{
			generateItemsInNamespace(childNamespace, vcxprojRoot, filtersRoot, currentNamespace + "." + childNamespace.Name);
		}

		for (const SchemaCollection& schemaCollection : schemaNamespace.Collections)
		{
			generateCollection(schemaCollection, vcxprojRoot, filtersRoot, currentNamespace);
		}

		for (const SchemaClass& schemaClass : schemaNamespace.Classes)
		{
			generateClasses(schemaClass, vcxprojRoot, filtersRoot, currentNamespace);
		}

		for (const SchemaEnum& schemaEnum : schemaNamespace.Enums)
		{
			generateEnum(schemaEnum, vcxprojRoot, filtersRoot, currentNamespace);
		}
	}

	void updateRequiredHeaders(SchemaClass& parentClass, const SchemaClass& schemaClass, const std::string& currentNamespace)
	{
		if (schemaClass.FileName.size())
		{
			fs::path outputDir = gameDataProjDir / "src/GameData" / schemaClass.Directory;

			fs::create_directories(outputDir);

			std::string fileName = (outputDir / (schemaClass.FileName + ".h")).string();

			OutputFile& file = outputFiles[fileName];

			file.Directory = schemaClass.Directory;

			OutputNamespace* current = &file.Global;

			size_t start = 0;
			size_t length = 0;

			while (start < currentNamespace.size())
			{
				for (length; start + length < currentNamespace.size() && currentNamespace[start + length] != '.'; ++length);

				if (length == 0)
				{
					break;
				}

				std::string_view name = { currentNamespace.data() + start, length };

				start += length + 1;
				length = 0;

				current = &current->Namespaces[std::string(name)];
			}

			current->Classes[schemaClass.Name] = &schemaClass;
		}

		for (const SchemaMember& schemaMember : schemaClass.Members)
		{
			std::string includePath;

			if (schemaMember.ContainsType.size())
			{
				includePath = findIncludeDirectory(schemaMember.ContainsType, pickSchema(schemaMember.SchemaName, parentClass.SchemaName));
			}
			else
			{
				includePath = findIncludeDirectory(schemaMember.Type, pickSchema(schemaMember.SchemaName, parentClass.SchemaName));
			}

			if (includePath.size() && !parentClass.RequiredHeaders.contains(includePath))
			{
				parentClass.RequiredHeaders.insert(includePath);
			}
		}

		for (const SchemaClass& childClass : schemaClass.ChildClasses)
		{
			updateRequiredHeaders(parentClass, childClass, currentNamespace);
		}

		if (schemaClass.FileName.size())
		{
			fs::path outputDir = gameDataProjDir / "src/GameData" / schemaClass.Directory;

			std::string fileName = (outputDir / (schemaClass.FileName + ".h")).string();

			OutputFile& file = outputFiles[fileName];

			for (const std::string& requiredHeader : schemaClass.RequiredHeaders)
			{
				if (!file.RequiredHeaders.contains(requiredHeader))
				{
					file.RequiredHeaders.insert(requiredHeader);
				}
			}
		}
	}

	void updateRequiredHeaders(const SchemaEnum& schemaEnum, const std::string& currentNamespace)
	{
		if (!schemaEnum.FileName.size())
		{
			return;
		}

		fs::path outputDir = gameDataProjDir / "src/GameData" / schemaEnum.Directory;

		fs::create_directories(outputDir);

		std::string fileName = (outputDir / (schemaEnum.FileName + ".h")).string();

		OutputFile& file = outputFiles[fileName];

		file.Directory = schemaEnum.Directory;

		OutputNamespace* current = &file.Global;

		size_t start = 0;
		size_t length = 0;

		while (start < currentNamespace.size())
		{
			for (length; start + length < currentNamespace.size() && currentNamespace[start + length] != '.'; ++length);

			if (length == 0)
			{
				break;
			}

			std::string_view name = { currentNamespace.data() + start, length };

			start += length + 1;
			length = 0;

			current = &current->Namespaces[std::string(name)];
		}

		current->Enums[schemaEnum.Name] = &schemaEnum;
	}

	void updateRequiredHeaders(SchemaNamespace& schemaNamespace, const std::string& currentNamespace)
	{
		for (SchemaNamespace& childNamespace : schemaNamespace.Namespaces)
		{
			updateRequiredHeaders(childNamespace, currentNamespace.size() ? currentNamespace + "." + childNamespace.Name : childNamespace.Name);
		}

		for (SchemaCollection& schemaCollection : schemaNamespace.Collections)
		{
			//generateCollection(schemaCollection, vcxprojRoot, filtersRoot, currentNamespace);
		}

		for (SchemaClass& schemaClass : schemaNamespace.Classes)
		{
			updateRequiredHeaders(schemaClass, schemaClass, currentNamespace);
		}

		for (SchemaEnum& schemaEnum : schemaNamespace.Enums)
		{
			updateRequiredHeaders(schemaEnum, currentNamespace);
		}
	}

	void generateGameData()
	{
		if (!fs::exists(gameDataProjDir))
		{
			std::cout << "cannot find project directory. did you make sure to run this project through visual studio?" << std::endl;

			return;
		}

		fs::path vcxprojPath = gameDataProjDir / "GameData.vcxproj";
		fs::path filtersPath = gameDataProjDir / "GameData.vcxproj.filters";

		if (!fs::exists(vcxprojPath))
		{
			std::cout << "cannot find GameData.vcxproj. did you make sure to run this project through visual studio?" << std::endl;

			return;
		}

		if (!fs::exists(filtersPath))
		{
			std::cout << "cannot find GameData.vcxproj. did you make sure to run this project through visual studio?" << std::endl;

			return;
		}

		tinyxml2::XMLDocument vcxproj;
		tinyxml2::XMLDocument filters;

		vcxproj.LoadFile(vcxprojPath.string().c_str());
		filters.LoadFile(filtersPath.string().c_str());

		tinyxml2::XMLElement* vcxprojRoot = vcxproj.RootElement();
		tinyxml2::XMLElement* filtersRoot = filters.RootElement();

		if (!vcxprojRoot)
		{
			std::cout << "GameData.vcxproj cannot be read" << std::endl;

			return;
		}

		if (!filtersRoot)
		{
			std::cout << "GameData.vcxproj.filters cannot be read" << std::endl;

			return;
		}

		for (tinyxml2::XMLElement* child = vcxprojRoot->FirstChildElement(); child; child)
		{
			tinyxml2::XMLElement* next = child->NextSiblingElement();
			tinyxml2::XMLElement* descendant = child->FirstChildElement();

			if (descendant && (strcmp(descendant->Name(), "ClCompile") == 0 || strcmp(descendant->Name(), "ClInclude") == 0))
			{
				vcxprojRoot->DeleteChild(child);
			}
			else
			{
				std::cout << child->Name() << std::endl;
			}

			child = next;
		}

		for (tinyxml2::XMLElement* child = filtersRoot->FirstChildElement(); child; child)
		{
			tinyxml2::XMLElement* next = child->NextSiblingElement();
			tinyxml2::XMLElement* descendant = child->FirstChildElement();

			if (descendant && (strcmp(descendant->Name(), "ClCompile") == 0 || strcmp(descendant->Name(), "ClInclude") == 0))
			{
				filtersRoot->DeleteChild(child);
			}
			else
			{
				std::cout << child->Name() << std::endl;
			}

			child = next;
		}

		while (fs::exists(gameDataProjDir / "src"))
		{
			try
			{
				if (fs::exists(gameDataProjDir / "src"))
				{
					fs::remove_all(gameDataProjDir / "src");
				}
			}
			catch (fs::filesystem_error& err)
			{
				std::cout << "couldn't clear directory. press enter to try again...";

				int a = 0;
				std::cin >> a;
			}
		}

		fs::create_directories(gameDataProjDir / "src/GameData/Collection");
		fs::create_directories(gameDataProjDir / "src/GameData/Data");

		for (auto& schema : CollectionSchemas)
		{
			updateRequiredHeaders(schema.second.Global, "");
		}

		for (auto& schema : CollectionSchemas)
		{
			generateItemsInNamespace(schema.second.Global, vcxprojRoot, filtersRoot);
		}

		generateEnums(vcxprojRoot, filtersRoot);

		vcxproj.SaveFile(vcxprojPath.string().c_str());
		filters.SaveFile(filtersPath.string().c_str());

	}
}