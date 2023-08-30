#include "OutputSchema.h"

#include <iostream>

namespace OutputSchema
{
	std::unordered_map<std::string, CollectionSchema> CollectionSchemas;
	std::vector<CollectionSchema*> GlobalSchemas;

	void readNamespace(SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaNamespace.Name = value;
				schemaNamespace.Scope += value;

				continue;
			}

			std::cout << "unknown attribute of element 'namespace': '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			readSchemaElement(schemaNamespace, child);
		}
	}

	void readEnumValue(SchemaEnumValue& schemaEnumValue, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaEnumValue.Name = value;

				continue;
			}

			if (strcmp(name, "value") == 0)
			{
				schemaEnumValue.Value = value;

				continue;
			}

			std::cout << "unknown attribute of node 'value': '" << name << "'" << std::endl;
		}

		if (element->FirstChildElement())
		{
			std::cout << "unknown child nodes on node 'value'" << std::endl;
		}
	}

	void readEnum(SchemaEnum& schemaEnum, tinyxml2::XMLElement* element)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaEnum.Name = value;
				schemaEnum.Scope += value;

				continue;
			}

			if (strcmp(name, "directory") == 0)
			{
				schemaEnum.Directory = value;

				continue;
			}

			if (strcmp(name, "parent") == 0)
			{
				schemaEnum.ParentType = value;

				continue;
			}

			if (strcmp(name, "file") == 0)
			{
				schemaEnum.FileName = value;

				continue;
			}

			std::cout << "unknown attribute of node 'value': '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "value") == 0)
			{
				schemaEnum.Values.push_back({});

				SchemaEnumValue& childSchema = schemaEnum.Values.back();

				readEnumValue(childSchema, child);

				continue;
			}

			std::cout << "unknown attribute of element 'enum': '" << name << "'" << std::endl;
		}
	}

	const std::unordered_map<std::string, std::string> requiredHeaders = {
		{ "std::string", "<string>" },
		{ "std::wstring", "<string>" },
		{ "std::vector", "<vector>" },
		{ "Vector3S", "<Engine/Math/Vector3S.h>" },
		{ "Color4I", "<Engine/Math/Color4I.h>" }
	};

	const std::unordered_set<std::string> builtIns = {
		"char",
		"unsigned char",
		"signed char",
		"short",
		"unsigned short",
		"int",
		"unsigned int",
		"long long",
		"unsigned long long",
		"float",
		"double",
		"std::vector",
		"std::string",
		"std::wstring",
		"Vector3S",
		"Color4I"
		"array"
	};

	void readMember(SchemaMember& schemaMember, tinyxml2::XMLElement* element, SchemaClass* rootClass)
	{
		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				schemaMember.Name = value;

				continue;
			}

			if (strcmp(name, "type") == 0)
			{
				schemaMember.Type = value;

				continue;
			}

			if (strcmp(name, "default") == 0)
			{
				schemaMember.DefaultValue = value;

				continue;
			}

			if (strcmp(name, "contains") == 0)
			{
				schemaMember.ContainsType = value;

				continue;
			}

			if (strcmp(name, "schemaName") == 0)
			{
				schemaMember.SchemaName = value;

				continue;
			}

			if (strcmp(name, "length") == 0)
			{
				schemaMember.Length = (size_t)atoll(value);

				continue;
			}

			std::cout << "unknown attribute of node 'member': '" << name << "'" << std::endl;
		}

		if (schemaMember.ContainsType.size())
		{
			if (!builtIns.contains(schemaMember.ContainsType))
			{
				std::string newType = findFullPath(schemaMember.Scope, schemaMember.ContainsType, pickSchema(schemaMember.SchemaName, schemaMember.ParentSchemaName));

				if (newType.size())
				{
					schemaMember.ContainsType = newType;
				}
			}
		}

		if (schemaMember.Type.size())
		{
			if (!builtIns.contains(schemaMember.Type))
			{
				std::string newType = findFullPath(schemaMember.Scope, schemaMember.Type, pickSchema(schemaMember.SchemaName, schemaMember.ParentSchemaName));

				if (newType.size())
				{
					schemaMember.Type = newType;
				}
			}

			if (rootClass && !rootClass->RequiredHeaders.contains(schemaMember.Type))
			{
				auto headerEntry = requiredHeaders.find(schemaMember.Type);

				if (headerEntry != requiredHeaders.end())
				{
					rootClass->RequiredHeaders.insert(headerEntry->second);
				}
			}
		}


		if (!schemaMember.SchemaName.size())
		{
			SchemaEntry entry = findSchemaEntry(schemaMember.ContainsType.size() ? schemaMember.ContainsType : schemaMember.Type, schemaMember.ParentSchemaName);

			if (entry.Type != SchemaEntryType::None)
			{
				schemaMember.SchemaName = schemaMember.ParentSchemaName;
			}
		}

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "default") == 0)
			{
				const tinyxml2::XMLAttribute* nameAttrib = child->FindAttribute("name");
				const tinyxml2::XMLAttribute* valueAttrib = child->FindAttribute("value");

				if (nameAttrib == nullptr || valueAttrib == nullptr)
				{
					if (nameAttrib == nullptr)
					{
						std::cout << "member.default node missing name attribute" << std::endl;
					}

					if (valueAttrib == nullptr)
					{
						std::cout << "member.default node missing value attribute" << std::endl;
					}

					continue;
				}

				schemaMember.DefaultInitializerValues[nameAttrib->Value()] = valueAttrib->Value();

				continue;
			}

			std::cout << "unknown child node '" << name << "' on node 'member'" << std::endl;
		}
	}

	void readClass(SchemaClass& schemaClass, tinyxml2::XMLElement* element, SchemaClass* rootClass, const std::string& typeSuffix)
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
				schemaClass.Scope += schemaClass.TypeName;

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

			if (strcmp(name, "directory") == 0)
			{
				schemaClass.Directory = value;

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

				childSchema.Scope = schemaClass.Scope + ".";
				childSchema.SchemaName = schemaClass.SchemaName;

				readClass(childSchema, child, rootClass, schemaClass.ChildTypeSuffix + typeSuffix);

				if (childSchema.IsMember)
				{
					schemaClass.Members.push_back({ childSchema.TypeName, childSchema.MemberName, "", "", "", "", "", schemaClass.ChildClasses.size() - 1});
				}

				continue;
			}

			if (strcmp(name, "member") == 0)
			{
				schemaClass.Members.push_back({});

				SchemaMember& memberSchema = schemaClass.Members.back();

				memberSchema.Scope = schemaClass.Scope;
				memberSchema.ParentSchemaName = schemaClass.SchemaName;

				readMember(memberSchema, child, rootClass);

				continue;
			}

			if (strcmp(name, "enum") == 0)
			{
				schemaClass.Enums.push_back({});

				SchemaEnum& childSchema = schemaClass.Enums.back();

				childSchema.Scope = schemaClass.Scope + ".";
				childSchema.SchemaName = schemaClass.SchemaName;

				readEnum(childSchema, child);

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
				schemaCollection.Scope += value;

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

			SchemaNamespace& childNamespace = parentNamespace.Namespaces.back();

			childNamespace.Scope = parentNamespace.Scope;
			childNamespace.SchemaName = parentNamespace.SchemaName;

			if (parentNamespace.Scope.size())
			{
				childNamespace.Scope += ".";
			}

			readNamespace(childNamespace, element);

			return;
		}

		if (strcmp(name, "class") == 0)
		{
			parentNamespace.Classes.push_back({});

			SchemaClass& childClass = parentNamespace.Classes.back();

			childClass.Scope = parentNamespace.Scope;
			childClass.SchemaName = parentNamespace.SchemaName;

			if (parentNamespace.Scope.size())
			{
				childClass.Scope += ".";
			}

			readClass(childClass, element, &childClass);

			return;
		}

		if (strcmp(name, "collection") == 0)
		{
			parentNamespace.Collections.push_back({});

			SchemaCollection& childCollection = parentNamespace.Collections.back();

			childCollection.Scope = parentNamespace.Scope;
			childCollection.SchemaName = parentNamespace.SchemaName;

			if (parentNamespace.Scope.size())
			{
				childCollection.Scope += ".";
			}

			readCollection(childCollection, element);

			return;
		}

		if (strcmp(name, "enum") == 0)
		{
			parentNamespace.Enums.push_back({});

			SchemaEnum& childSchema = parentNamespace.Enums.back();

			childSchema.Scope = parentNamespace.Scope;
			childSchema.SchemaName = parentNamespace.SchemaName;

			if (parentNamespace.Scope.size())
			{
				childSchema.Scope += ".";
			}

			readEnum(childSchema, element);

			return;
		}

		std::cout << "unknown node: '" << name << "'" << std::endl;
	}

	void readSchema(const fs::path& filePath)
	{
		std::string name = filePath.filename().stem().string();

		CollectionSchema& schema = CollectionSchemas[name];

		schema.Name = name;
		schema.Global.SchemaName = name;

		tinyxml2::XMLDocument document;

		document.LoadFile(filePath.string().c_str());

		tinyxml2::XMLElement* root = document.RootElement();

		const tinyxml2::XMLAttribute* isGlobalAttribute = root->FindAttribute("isGlobal");

		std::string schemaReferenceName = name;

		if (isGlobalAttribute && strcmp(isGlobalAttribute->Value(), "true") == 0)
		{
			GlobalSchemas.push_back(&schema);
		}

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

	SchemaEntry findSchemaEntryInternal(const std::string_view& path, const std::string& schemaName, char separator)
	{
		auto schemaIndex = CollectionSchemas.find(schemaName);

		if (schemaIndex == CollectionSchemas.end())
		{
			return {};
		}

		const SchemaNamespace* current = &schemaIndex->second.Global;
		const SchemaClass* currentClass = nullptr;

		size_t start = 0;
		size_t length = 0;

		while (current && start < path.size())
		{
			for (length; start + length < path.size() && path[start + length] != separator; ++length);

			if (length == 0)
			{
				return {};
			}

			std::string_view name = { path.data() + start, length };

			start += length;

			while (start < path.size() && path[start] == separator)
			{
				++start;
			}

			length = 0;

			for (const SchemaCollection& collection : current->Collections)
			{
				if (collection.Name == name && start >= path.size())
				{
					return {
						.Type = SchemaEntryType::Collection,
						.Collection = &collection
					};
				}
			}

			for (const SchemaEnum& childEnum : current->Enums)
			{
				if (childEnum.Name == name && start >= path.size())
				{
					return {
						.Type = SchemaEntryType::Enum,
						.Enum = &childEnum
					};
				}
			}

			bool found = false;

			for (const SchemaNamespace& childNamespace : current->Namespaces)
			{
				if (childNamespace.Name == name)
				{
					found = true;

					current = &childNamespace;
				}
			}

			if (found)
			{
				continue;
			}

			for (const SchemaClass& childClass : current->Classes)
			{
				if (childClass.Name == name)
				{
					current = nullptr;
					currentClass = &childClass;
				}
			}

			if (currentClass)
			{
				break;
			}

			current = nullptr;

			break;
		}

		if (current == nullptr && currentClass == nullptr)
		{
			return {};
		}

		if (current != nullptr && start < path.size())
		{
			return {};
		}
		
		if (current != nullptr)
		{
			return {
				.Type = SchemaEntryType::Namespace,
				.Namespace = current
			};
		}

		if (currentClass == nullptr)
		{
			return {};
		}

		while (currentClass && start < path.size())
		{
			for (length; start + length < path.size() && path[start + length] != separator; ++length);

			if (length == 0)
			{
				return {};
			}

			std::string_view name = { path.data() + start, length };

			start += length;

			while (start < path.size() && path[start] == separator)
			{
				++start;
			}

			length = 0;

			for (const SchemaEnum& childEnum : currentClass->Enums)
			{
				if (childEnum.Name == name && start >= path.size())
				{
					return {
						.Type = SchemaEntryType::Enum,
						.Enum = &childEnum
					};
				}
			}

			bool found = false;

			for (const SchemaClass& childClass : currentClass->ChildClasses)
			{
				if (childClass.Name == name)
				{
					found = true;

					currentClass = &childClass;
				}
			}

			if (!found)
			{
				currentClass = nullptr;

				break;
			}
		}

		if (currentClass == nullptr || start < path.size())
		{
			return {};
		}

		return {
			.Type = SchemaEntryType::Class,
			.Class = currentClass
		};
	}

	SchemaEntry findSchemaEntry(const std::string_view& path, const std::string& schemaName, char separator)
	{
		if (path.size() == 0)
		{
			return {};
		}

		SchemaEntry entry = findSchemaEntryInternal(path, schemaName, separator);

		if (entry.Type != SchemaEntryType::None)
		{
			return entry;
		}

		for (size_t i = 0; i < GlobalSchemas.size(); ++i)
		{
			SchemaEntry entry = findSchemaEntryInternal(path, GlobalSchemas[i]->Name, separator);

			if (entry.Type != SchemaEntryType::None)
			{
				return entry;
			}
		}

		return {};
	}

	std::string findIncludeDirectoryInternal(const std::string_view& path, const std::string& schemaName, char separator)
	{
		auto schemaIndex = CollectionSchemas.find(schemaName);

		if (schemaIndex == CollectionSchemas.end())
		{
			return "";
		}

		if (path.size() == 0)
		{
			return "";
		}

		const SchemaNamespace* current = &schemaIndex->second.Global;
		const SchemaClass* currentClass = nullptr;

		size_t start = 0;
		size_t length = 0;

		while (current && start < path.size())
		{
			for (length; start + length < path.size() && path[start + length] != separator; ++length);

			if (length == 0)
			{
				return {};
			}

			std::string_view name = { path.data() + start, length };

			start += length;

			while (start < path.size() && path[start] == separator)
			{
				++start;
			}

			length = 0;

			for (const SchemaCollection& collection : current->Collections)
			{
				if (collection.Name == name)
				{
					return "<GameData/Collection/" + collection.Name + ".h>";
				}
			}

			for (const SchemaEnum& childEnum : current->Enums)
			{
				if (childEnum.Name == name)
				{
					return "<GameData/" + childEnum.Directory + "/" + (childEnum.FileName.size() ? childEnum.FileName : childEnum.Name) + ".h>";
				}
			}

			bool found = false;

			for (const SchemaNamespace& childNamespace : current->Namespaces)
			{
				if (childNamespace.Name == name)
				{
					found = true;

					current = &childNamespace;
				}
			}

			if (found)
			{
				continue;
			}

			for (const SchemaClass& childClass : current->Classes)
			{
				if (childClass.Name == name)
				{
					return "<GameData/" + childClass.Directory + "/" + childClass.Name + ".h>";
				}
			}
		}

		return "";
	}

	std::string findIncludeDirectory(const std::string_view& path, const std::string& schemaName, char separator)
	{
		if (path.size() == 0)
		{
			return "";
		}

		std::string include = findIncludeDirectoryInternal(path, schemaName, separator);

		if (include.size())
		{
			return include;
		}

		for (size_t i = 0; i < GlobalSchemas.size(); ++i)
		{
			include = findIncludeDirectoryInternal(path, GlobalSchemas[i]->Name, separator);

			if (include.size())
			{
				return include;
			}
		}

		return "";
	}

	const SchemaMember* findSchemaMember(const SchemaClass* schemaClass, const std::string& path, char separator)
	{
		if (path.size() == 0 || !schemaClass)
		{
			return nullptr;
		}

		const SchemaClass* currentClass = schemaClass;
		const SchemaMember* currentMember = nullptr;

		size_t start = 0;
		size_t length = 0;

		while (currentClass && start < path.size())
		{
			for (length; start + length < path.size() && path[start + length] != separator; ++length);

			if (length == 0)
			{
				return {};
			}

			std::string_view name = { path.data() + start, length };

			start += length;
			length = 0;

			for (const SchemaMember& member : currentClass->Members)
			{
				if (member.Name == name)
				{
					currentClass = nullptr;
					currentMember = &member;

					break;
				}
			}
		}

		//if (start < path.size())
		//{
		//	return nullptr;
		//}

		return currentMember;
	}

	std::string pickSchema(const std::string & override, const std::string& base)
	{
		return override.size() ? override : base;
	}

	std::string stripCommonNamespaces(const std::string& primaryNamespace, const std::string& secondaryNamespace, char separator)
	{
		size_t lastSeparator = 0;

		size_t length = std::min(primaryNamespace.size(), secondaryNamespace.size());

		for (size_t i = 0; i < length + 1; ++i)
		{
			if ((primaryNamespace[i] == 0 || primaryNamespace[i] == separator) && (secondaryNamespace[i] == 0 || secondaryNamespace[i] == separator))
			{
				lastSeparator = i;

				continue;
			}

			if (primaryNamespace[i] != secondaryNamespace[i])
			{
				break;
			}

			if (primaryNamespace[i] == separator)
			{
				lastSeparator = i + 1;
			}
		}

		if (lastSeparator < primaryNamespace.size())// && lastSeparator == secondaryNamespace.size())
		{
			while (lastSeparator < primaryNamespace.size() && primaryNamespace[lastSeparator] == separator)
			{
				++lastSeparator;
			}
		}

		return primaryNamespace.substr(lastSeparator, primaryNamespace.size() - lastSeparator);
	}

	std::string findFullPath(const std::string& currentPath, const std::string& subPath, const std::string& schemaName, char separator)
	{
		if (builtIns.contains(subPath))
		{
			return subPath;
		}

		for (std::string parentPath = currentPath; parentPath.size(); parentPath = stripLastPath(parentPath))
		{
			SchemaEntry entry = findSchemaEntry(parentPath + separator + subPath, schemaName, separator);

			if (entry.Type != SchemaEntryType::None)
			{
				return parentPath + separator + subPath;
			}
		}

		SchemaEntry entry = findSchemaEntry(subPath, schemaName, separator);

		if (entry.Type != SchemaEntryType::None)
		{
			return subPath;
		}

		return "";
	}

	std::string stripLastPath(const std::string& path, char separator)
	{
		if (!path.size())
		{
			return path;
		}

		for (size_t i = path.size() - 1; i < path.size(); --i)
		{
			if (path[i] == separator)
			{
				while (i < path.size() && path[i] == separator)
				{
					--i;
				}

				if (i >= path.size())
				{
					return "";
				}

				return path.substr(0, i + 1);
			}
		}

		return "";
	}

	std::string swapSeparator(const std::string& path, std::string newSeparator, char separator)
	{
		std::string out;

		for (size_t i = 0; i < path.size(); ++i)
		{
			if (path[i] != separator)
			{
				out.push_back(path[i]);

				continue;
			}

			out += newSeparator;
		}

		return out;
	}
}