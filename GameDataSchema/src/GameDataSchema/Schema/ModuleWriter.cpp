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

	void ModuleWriter::PushLine()
	{
		Out << Indent() << "\n";
	}

	void ModuleWriter::PushMember(const SchemaClass& type)
	{
		Out << Indent() << type.TypeName << " " << type.MemberName << ";\n";
	}

	void ModuleWriter::PushMember(const std::string& type, const std::string_view& name)
	{

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

	void generateClassDefinitions(const SchemaClass& schemaClass, ModuleWriter& module, const std::string& currentNamespace)
	{
		bool isFirst = true;

		for (const SchemaClass& childClass : schemaClass.ChildClasses)
		{
			if (!isFirst)
			{
				module.PushLine();
			}

			isFirst = false;

			generateClassDefinitions(schemaClass, module, currentNamespace);
		}

		if (schemaClass.Members.size())
		{
			if (schemaClass.ChildClasses.size() > 0)
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

			}
		}
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

	void generateClasses(const SchemaClass& schemaClass, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		fs::path outputDir = gameDataProjDir / "src/GameData/Data";
		fs::path outputHeader = outputDir / (schemaClass.Name + ".h");
		fs::path outputCpp = outputDir / (schemaClass.Name + ".cpp");

		addProjectNode(vcxprojRoot, "ClInclude", outputHeader.string(), nullptr);
		addProjectNode(vcxprojRoot, "ClCompile", outputCpp.string(), nullptr);

		addProjectNode(filtersRoot, "ClInclude", outputHeader.string(), "Source Files\\Data");
		addProjectNode(filtersRoot, "ClCompile", outputCpp.string(), "Source Files\\Data");

		{
			std::ofstream outFile(outputHeader);

			outFile << "#pragma once\n\n";

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			module.PushStruct(schemaClass.Name);

			generateClassDefinitions(schemaClass, module, currentNamespace);
		}

		{
			std::ofstream outFile(outputCpp);

			ModuleWriter module(outFile);

			generateModuleNamespace(module, currentNamespace);

			generateClassDeclarations(schemaClass, module, currentNamespace, schemaClass.Name);
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

		fs::remove_all(gameDataProjDir / "src");
		fs::create_directories(gameDataProjDir / "src/GameData/Collection");
		fs::create_directories(gameDataProjDir / "src/GameData/Data");

		for (const auto& schema : CollectionSchemas)
		{
			generateItemsInNamespace(schema.second.Global, vcxprojRoot, filtersRoot);
		}

		vcxproj.SaveFile(vcxprojPath.string().c_str());
		filters.SaveFile(filtersPath.string().c_str());

	}
}