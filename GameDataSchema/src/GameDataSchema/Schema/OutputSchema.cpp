#include "OutputSchema.h"

#include <iostream>

namespace OutputSchema
{
	std::unordered_map<std::string, CollectionSchema> CollectionSchemas;

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

	void readClass(SchemaClass& schemaClass, tinyxml2::XMLElement* element, const std::string& typeSuffix)
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

			if (strcmp(name, "isOptional") == 0)
			{
				schemaClass.IsOptional = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "isMember") == 0)
			{
				schemaClass.IsMember = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "isVector") == 0)
			{
				schemaClass.IsVector = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "isMap") == 0)
			{
				schemaClass.IsMap = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "keyTypeName") == 0)
			{
				schemaClass.KeyTypeName = value;

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
}