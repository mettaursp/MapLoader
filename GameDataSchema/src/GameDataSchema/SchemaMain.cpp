#include <fstream>

#include "Schema/GameSchema.h"
#include "Schema/SchemaTypes.h"

namespace fs = std::filesystem;

fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
fs::path kms2Root = "B:/Files/ms2export/kms2export";
const fs::path schemaDir = "./schema";
const fs::path gameDataProjDir = "./../GameData";
Archive::ArchiveReader gms2Reader;
Archive::ArchiveReader kms2Reader;

namespace OutputSchema
{
	struct SchemaMember
	{
		std::string Type;
		std::string Name;
		size_t ChildClassIndex = (size_t)-1;
	};

	struct SchemaClass
	{
		bool IsMember = true;
		std::string Name;
		std::string TypeName;
		std::string MemberName;
		std::string ChildTypeSuffix;

		std::vector<SchemaClass> ChildClasses;
		std::vector<SchemaMember> Members;
	};

	struct SchemaCollection
	{
		std::string Name;
		std::string KeyName;
		std::string KeyType;
		std::string StoredClass;
	};

	struct SchemaNamespace
	{
		std::string Name;

		std::vector<SchemaNamespace> Namespaces;
		std::vector<SchemaCollection> Collections;
		std::vector<SchemaClass> Classes;
	};

	struct CollectionSchema
	{
		std::string Name;

		SchemaNamespace Global;
	};

	std::unordered_map<std::string, CollectionSchema> CollectionSchemas;

	void readSchemaElement(SchemaNamespace& parentNamespace, tinyxml2::XMLElement* element);
	
	void readNamespace(SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaNamespace.Name = value;

				continue;
			}

			std::cout << "unknown attribute of element 'namespace': '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			readSchemaElement(schemaNamespace, child);
		}
	}
	
	void readClass(SchemaClass& schemaClass, tinyxml2::XMLElement* element, const std::string& typeSuffix = "")
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaClass.Name = value;
				schemaClass.MemberName = value;
				schemaClass.TypeName = value + typeSuffix;

				continue;
			}

			if (strcmp(name, "childTypeSuffix") == 0)
			{
				schemaClass.ChildTypeSuffix = value;

				continue;
			}

			if (strcmp(name, "isMember") == 0)
			{
				schemaClass.IsMember = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << "unknown attribute of element 'namespace': '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "class") == 0)
			{
				schemaClass.ChildClasses.push_back({});

				SchemaClass& childSchema = schemaClass.ChildClasses.back();

				readClass(childSchema, child, schemaClass.ChildTypeSuffix + typeSuffix);

				if (childSchema.IsMember)
				{
					schemaClass.Members.push_back({ childSchema.TypeName, childSchema.MemberName, schemaClass.ChildClasses.size() - 1 });
				}

				continue;
			}

			std::cout << "unknown child element of element 'class': '" << name << "'" << std::endl;
		}
	}
	
	void readCollection(SchemaCollection& schemaCollection, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaCollection.Name = value;

				continue;
			}

			if (strcmp(name, "keyName") == 0)
			{
				schemaCollection.KeyName = value;

				continue;
			}

			if (strcmp(name, "keyType") == 0)
			{
				schemaCollection.KeyType = value;

				continue;
			}

			if (strcmp(name, "class") == 0)
			{
				schemaCollection.StoredClass = value;

				continue;
			}

			std::cout << "unknown attribute of element 'namespace': '" << name << "'" << std::endl;
		}

		tinyxml2::XMLElement* child = element->FirstChildElement();

		if (child)
		{
			std::cout << "unknown child element of element 'collection': '" << child->Name() << "'" << std::endl;
		}
	}

	void readSchemaElement(SchemaNamespace& parentNamespace, tinyxml2::XMLElement* element)
	{
		const char* name = element->Name();

		if (strcmp(name, "namespace") == 0)
		{
			parentNamespace.Namespaces.push_back({});

			readNamespace(parentNamespace.Namespaces.back(), element);

			return;
		}

		if (strcmp(name, "class") == 0)
		{
			parentNamespace.Classes.push_back({});

			readClass(parentNamespace.Classes.back(), element);

			return;
		}

		if (strcmp(name, "collection") == 0)
		{
			parentNamespace.Collections.push_back({});

			readCollection(parentNamespace.Collections.back(), element);

			return;
		}

		std::cout << "unknown node: '" << name << "'" << std::endl;
	}

	void readSchema(const fs::path& filePath)
	{
		std::string name = filePath.filename().stem().string();

		tinyxml2::XMLDocument document;
		CollectionSchema& schema = CollectionSchemas[name];

		schema.Name = name;

		document.LoadFile(filePath.string().c_str());

		tinyxml2::XMLElement* root = document.RootElement();

		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			readSchemaElement(schema.Global, child);
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

	class ModuleWriter
	{
	public:
		struct StackContext
		{
			bool IsNamespace = false;
			bool CurrentlyPrivate = false;
		};

		struct StackHandle
		{
			~StackHandle();

			void Bind(ModuleWriter& writer);

		private:
			size_t StackDepth = (size_t)-1;
			ModuleWriter* Writer = nullptr;
		};

		std::ofstream& Out;

		ModuleWriter(std::ofstream& out) : Out(out) {}
		~ModuleWriter();

		void PushNamespace(const std::string_view& name);
		void PushNamespace(StackHandle& handle, const std::string_view& name);
		void PushStruct(const std::string_view& name);
		void PushStruct(StackHandle& handle, const std::string_view& name);
		void PushCollection(const std::string_view& name);
		void PushCollection(StackHandle& handle, const std::string_view& name);
		void PushLine();
		void PushMember(const SchemaClass& type);
		void PushMember(const std::string& type, const std::string_view& name);
		void PopStack();

		size_t GetStackDepth() const { return Stack.size(); }
		const auto& GetStack() const { return Stack; }

		std::string_view Indent() const { return { Indentation.data(), Indentation.size() }; }

	private:
		std::vector<StackContext> Stack;
		std::vector<char> Indentation;
	};

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

	void generateItemsInNamespace(const SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace = "Global")
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

int main(int argc, char** argv)
{
	std::vector<std::string> validateGms2Dirs;
	std::vector<std::string> validateKms2Dirs;

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "--root") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root = argv[i];
		}

		if (strcmp(argv[i], "--rootExtracted") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find extracted root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2RootExtracted = argv[i];
		}

		if (strcmp(argv[i], "--validate") == 0 && ++i + 1 < argc)
		{
			if (strcmp(argv[i], "gms2") == 0)
			{
				validateGms2Dirs.push_back(argv[++i]);
			}
			else if (strcmp(argv[i], "kms2") == 0)
			{
				validateKms2Dirs.push_back(argv[++i]);
			}
		}
	}

	if (!fs::exists(ms2Root)) return -1;
	if (!fs::exists(schemaDir)) return -1;

	gms2Reader.Load(ms2Root / "Data", false);
	kms2Reader.Load(kms2Root / "Data", false);

	GameSchema::readSchemas(schemaDir / "gms2", true);
	GameSchema::readSchemas(schemaDir / "kms2", false);
	GameSchema::validateSchemas(gms2Reader, true, validateGms2Dirs);
	GameSchema::validateSchemas(kms2Reader, false, validateKms2Dirs);

	OutputSchema::readSchemas(schemaDir / "output");

	//OutputSchema::generateGameData();


	return 0;
}