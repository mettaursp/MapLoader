#include <fstream>

#include "Schema/GameSchema.h"
#include "Schema/SchemaTypes.h"

namespace fs = std::filesystem;

fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
fs::path kms2Root = "B:/Files/Maplestars2/MapleStars2";
const fs::path schemaDir = "./schema";
const fs::path gameDataProjDir = "./../GameData";
Archive::ArchiveReader gms2Reader;
Archive::ArchiveReader kms2Reader;

namespace OutputSchema
{
	struct SchemaClass
	{
		std::string Name;

		std::vector<SchemaClass> ChildClasses;
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
	
	void readClass(SchemaClass& schemaClass, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaClass.Name = value;

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

				readClass(schemaClass.ChildClasses.back(), child);

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

	void generateClasses(const SchemaClass& schemaClass, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace)
	{
		fs::path outputDir = gameDataProjDir / "src/GameData/Data";
		fs::path outputHeader = outputDir / (schemaClass.Name + ".h");
		fs::path outputCpp = outputDir / (schemaClass.Name + ".cpp");

		addProjectNode(vcxprojRoot, "ClInclude", outputHeader.string(), nullptr);
		addProjectNode(vcxprojRoot, "ClCompile", outputCpp.string(), nullptr);

		addProjectNode(filtersRoot, "ClInclude", outputHeader.string(), "Source Files\\Data");
		addProjectNode(filtersRoot, "ClCompile", outputCpp.string(), "Source Files\\Data");

		{ std::ofstream(outputHeader).flush(); }
		{ std::ofstream(outputCpp).flush(); }

		for (const SchemaClass& childClass : schemaClass.ChildClasses)
		{
			generateClasses(childClass, vcxprojRoot, filtersRoot, currentNamespace + "." + childClass.Name);
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
		
		{ std::ofstream(outputHeader).flush(); }
		{ std::ofstream(outputCpp).flush(); }
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
	}

	if (!fs::exists(ms2Root)) return -1;
	if (!fs::exists(schemaDir)) return -1;

	gms2Reader.Load(ms2Root / "Data", false);
	kms2Reader.Load(kms2Root / "Data", false);

	GameSchema::readSchemas(schemaDir / "gms2", true);
	GameSchema::readSchemas(schemaDir / "kms2", false);
	//GameSchema::validateSchemas(gms2Reader, true);
	//GameSchema::validateSchemas(kms2Reader, false);

	OutputSchema::readSchemas(schemaDir / "output");

	OutputSchema::generateGameData();


	return 0;
}