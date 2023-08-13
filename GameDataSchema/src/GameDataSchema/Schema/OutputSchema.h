#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include <tinyxml2/tinyxml2.h>

namespace fs = std::filesystem;

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
		bool IsOptional = false;
		bool IsMember = true;
		bool IsVector = true;
		bool IsMap = true;
		std::string Name;
		std::string TypeName;
		std::string KeyTypeName;
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

	extern std::unordered_map<std::string, CollectionSchema> CollectionSchemas;

	void readNamespace(SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* element);

	void readClass(SchemaClass& schemaClass, tinyxml2::XMLElement* element, const std::string& typeSuffix = "");

	void readCollection(SchemaCollection& schemaCollection, tinyxml2::XMLElement* element);

	void readSchemaElement(SchemaNamespace& parentNamespace, tinyxml2::XMLElement* element);

	void readSchema(const fs::path& filePath);

	void readSchemas(const fs::path& directory);
}