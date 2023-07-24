#include "GameSchema.h"

#include "SchemaTypes.h"

namespace GameSchema
{
	const std::unordered_map<std::string, SchemaType> Types = {
		{ "int", { "int", SchemaTypes::Int{} }},
		{ "string", { "string", SchemaTypes::String{} }}
	};

	std::unordered_map<std::string, Schema> Gms2Schemas = {};
	std::unordered_map<std::string, Schema> Kms2Schemas = {};

	void readFile(Schema& schema, SchemaFile& file, tinyxml2::XMLElement* fileElement)
	{
		if (fileElement->FirstChildElement())
		{
			std::cout << "invalid children on 'file' node" << std::endl;
		}

		for (const tinyxml2::XMLAttribute* attribute = fileElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				file.Name = value;
				file.NameRegex = std::regex(value, std::regex_constants::ECMAScript | std::regex_constants::icase);

				continue;
			}

			if (strcmp(name, "nameArguments") == 0)
			{
				int length = 0;
				int start = 0;

				for (int i = 0; value[i]; ++i)
				{
					if (value[i] != ',')
					{
						++length;

						if (value[i + 1])
							continue;
					}

					file.NameArguments.push_back(std::string(value + start, length));

					length = 0;
					start = i + 1;
				}

				continue;
			}

			if (strcmp(name, "nameArgumentTypes") == 0)
			{
				int length = 0;
				int start = 0;

				for (int i = 0; value[i]; ++i)
				{
					if (value[i] != ',')
					{
						++length;

						if (value[i + 1])
							continue;
					}

					std::string typeName(value + start, length);
					const auto& typeEntry = Types.find(typeName);

					length = 0;
					start = i + 1;

					if (typeEntry == Types.end())
					{
						std::cout << "unknown type '" << typeName << "' referenced" << std::endl;

						continue;
					}

					file.NameArgumentTypes.push_back(&typeEntry->second);
				}

				continue;
			}

			std::cout << "unknown 'directory' attribute: '" << name << "'" << std::endl;
		}
	}

	void readDirectory(Schema& schema, SchemaDirectory& directory, tinyxml2::XMLElement* directoryElement)
	{
		for (const tinyxml2::XMLAttribute* attribute = directoryElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "path") == 0)
			{
				directory.Path = value;

				continue;
			}

			if (strcmp(name, "recursive") == 0)
			{
				directory.Recursive = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << "unknown 'directory' attribute: '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = directoryElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "file") == 0)
			{
				directory.Files.push_back({});

				readFile(schema, directory.Files.back(), child);

				continue;
			}

			std::cout << "unknown node: '" << name << "'" << std::endl;
		}
	}

	void readProperty(Schema& schema, SchemaProperty& property, tinyxml2::XMLElement* propertyElement)
	{
		if (propertyElement->FirstChildElement())
		{
			std::cout << "invalid children on 'property' node" << std::endl;
		}

		for (const tinyxml2::XMLAttribute* attribute = propertyElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				property.Name = value;

				continue;
			}

			if (strcmp(name, "default") == 0)
			{
				property.Default = value;

				continue;
			}

			if (strcmp(name, "types") == 0)
			{
				int length = 0;
				int start = 0;

				for (int i = 0; value[i]; ++i)
				{
					if (value[i] != ',')
					{
						++length;

						if (value[i + 1])
							continue;
					}

					std::string typeName(value + start, length);
					const auto& typeEntry = Types.find(typeName);

					length = 0;
					start = i + 1;

					if (typeEntry == Types.end())
					{
						std::cout << "unknown type '" << typeName << "' referenced" << std::endl;

						continue;
					}

					property.Types.push_back(&typeEntry->second);
				}

				continue;
			}

			std::cout << "unknown 'directory' attribute: '" << name << "'" << std::endl;
		}
	}

	void readNode(Schema& schema, SchemaNode& node, tinyxml2::XMLElement* nodeElement)
	{
		for (const tinyxml2::XMLAttribute* attribute = nodeElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				node.Name = value;

				continue;
			}

			if (strcmp(name, "optional") == 0)
			{
				node.Optional = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "allowMultiple") == 0)
			{
				node.AllowMultiple = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "allowUnknownChildren") == 0)
			{
				node.AllowUnknownChildren = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << "unknown 'node' attribute: '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = nodeElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "node") == 0)
			{
				node.ChildNodes.push_back({});

				readNode(schema, node.ChildNodes.back(), child);

				continue;
			}

			if (strcmp(name, "property") == 0)
			{
				node.Properties.push_back({});

				readProperty(schema, node.Properties.back(), child);

				continue;
			}

			std::cout << "unknown node: '" << name << "'" << std::endl;
		}
	}

	void readLayout(Schema& schema, tinyxml2::XMLElement* layoutElement)
	{
		for (const tinyxml2::XMLAttribute* attribute = layoutElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "root") == 0)
			{
				schema.Root = value;

				continue;
			}

			if (strcmp(name, "allowMultiple") == 0)
			{
				schema.AllowMultipleRoots = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "allowUnknownChildren") == 0)
			{
				schema.AllowUnknownChildren = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << "unknown 'layout' attribute: '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = layoutElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "node") == 0)
			{
				schema.Nodes.push_back({});

				readNode(schema, schema.Nodes.back(), child);

				continue;
			}

			std::cout << "unknown node: '" << name << "'" << std::endl;
		}
	}

	void readSchema(const fs::path& filePath, bool isGms2)
	{
		std::string name = filePath.filename().stem().string();

		tinyxml2::XMLDocument document;
		Schema& schema = isGms2 ? Gms2Schemas[name] : Kms2Schemas[name];

		schema.Name = name;

		document.LoadFile(filePath.string().c_str());

		tinyxml2::XMLElement* root = document.RootElement();

		bool parsedLayout = false;

		for (tinyxml2::XMLElement* child = root->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "directory") == 0)
			{
				schema.Directories.push_back({});

				readDirectory(schema, schema.Directories.back(), child);

				continue;
			}

			if (strcmp(name, "layout") == 0)
			{
				if (parsedLayout)
				{
					std::cout << "layout node repeated" << std::endl;

					continue;
				}

				parsedLayout = true;

				readLayout(schema, child);

				continue;
			}

			std::cout << "unknown node: '" << name << "'" << std::endl;
		}
	}

	void readSchemas(const fs::path& directory, bool isGms2)
	{
		for (const auto& entry : fs::recursive_directory_iterator{ directory })
		{
			const fs::path& path = entry.path();

			if (!fs::is_regular_file(path) && !path.has_extension()) continue;

			fs::path extension = path.extension();

			if (extension != ".xml") continue;

			readSchema(path, isGms2);
		}
	}

	bool validateNodeSchema(const Schema& schema, const SchemaNode& node, tinyxml2::XMLElement* element, const std::string& path, bool printSuccesses)
	{
		std::string currentPath = path + "." + node.Name;

		bool meetsSchema = true;

		for (const SchemaProperty& property : node.Properties)
		{
			for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				if (property.Name != attribute->Name())
				{
					continue;
				}

				std::string_view value = attribute->Value();
				bool isDefaultValue = property.Default == value;
				bool valueMatches = false;

				for (size_t i = 0; i < property.Types.size() && !valueMatches; ++i)
				{
					const SchemaType* type = property.Types[i];

					if (type->ValidateValue != nullptr)
					{
						valueMatches = type->ValidateValue(value);
					}

					if (valueMatches)
					{
						if (printSuccesses)
						{
							const char* validMessage = isDefaultValue ? "' [default] valid for type '" : "' valid for type '";

							std::cout << currentPath << "." << property.Name << " value '" << value << isDefaultValue << type->Name << "'" << std::endl;
						}

						break;
					}
				}

				if (!valueMatches)
				{
					std::cout << currentPath << "." << property.Name << " value '" << value << "' not valid for possible types: ";

					bool first = true;

					for (const SchemaType* type : property.Types)
					{
						if (!first)
						{
							std::cout << ", ";
						}

						std::cout << type->Name;

						first = false;
					}

					std::cout << std::endl;

					meetsSchema = false;
				}

				break;
			}
		}

		std::vector<int> elementCounts(node.ChildNodes.size());

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();
			bool foundMatch = false;

			for (size_t i = 0; i < node.ChildNodes.size(); ++i)
			{
				const SchemaNode& childNode = node.ChildNodes[i];

				if (childNode.Name == name)
				{
					++elementCounts[i];

					foundMatch = true;

					bool nodeMatches = validateNodeSchema(schema, childNode, child, currentPath, printSuccesses);

					meetsSchema &= nodeMatches;

					break;
				}
			}

			if (!foundMatch && !node.AllowUnknownChildren)
			{
				std::cout << "unknown node '" << name << "' detected in " << currentPath << " where unknown nodes aren't allowed" << std::endl;

				meetsSchema = false;
			}
		}

		for (size_t i = 0; i < node.ChildNodes.size(); ++i)
		{
			const SchemaNode& childNode = node.ChildNodes[i];

			if (elementCounts[i] == 0 && !childNode.Optional)
			{
				std::cout << "missing required node '" << childNode.Name << "' in " << currentPath << std::endl;

				meetsSchema = false;
			}

			if (elementCounts[i] > 1 && !childNode.AllowMultiple)
			{
				std::cout << "multiple '" << childNode.Name << "' nodes detected in " << currentPath << " where only 1 '" << childNode.Name << "' is allowed" << std::endl;

				meetsSchema = false;
			}
		}

		return meetsSchema;
	}

	bool validateFileSchema(const Schema& schema, const Archive::ArchivePath& path, bool printSuccesses)
	{
		static std::string output;

		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		if (rootElement == nullptr)
		{
			std::cout << "no root in file " << path.GetPath() << ": " << path.GetPath() << std::endl;

			return false;
		}

		if (printSuccesses)
		{
			std::cout << "validating " << path.GetPath() << std::endl;
		}

		bool meetsSchema = true;
		int rootCount = 0;

		for (rootElement; rootElement; rootElement = rootElement->NextSiblingElement())
		{
			if (schema.Root != rootElement->Name())
			{
				std::cout << "file root element '" << rootElement->Name() << "' doesn't match schema '" << schema.Root << "'" << std::endl;

				meetsSchema = false;

				continue;
			}

			++rootCount;

			std::string currentPath = path.GetPath().string() + ":" + rootElement->Name();
			std::vector<int> elementCounts(schema.Nodes.size());

			for (tinyxml2::XMLElement* child = rootElement->FirstChildElement(); child; child = child->NextSiblingElement())
			{
				const char* name = child->Name();
				bool foundMatch = false;

				for (size_t i = 0; i < schema.Nodes.size(); ++i)
				{
					const SchemaNode& node = schema.Nodes[i];

					if (node.Name == name)
					{
						++elementCounts[i];
						foundMatch = true;

						bool nodeMatches = validateNodeSchema(schema, node, child, currentPath, printSuccesses);

						meetsSchema &= nodeMatches;

						break;
					}
				}

				if (!foundMatch && !schema.AllowUnknownChildren)
				{
					std::cout << "unknown node '" << name << "' detected in " << currentPath << " where unknown nodes aren't allowed" << std::endl;

					meetsSchema = false;
				}
			}

			for (size_t i = 0; i < schema.Nodes.size(); ++i)
			{
				const SchemaNode& node = schema.Nodes[i];

				if (elementCounts[i] == 0 && !node.Optional)
				{
					std::cout << "missing required node '" << node.Name << "' in " << currentPath << std::endl;

					meetsSchema = false;
				}

				if (elementCounts[i] > 1 && !node.AllowMultiple)
				{
					std::cout << "multiple '" << node.Name << "' nodes detected in " << currentPath << " where only 1 '" << node.Name << "' is allowed" << std::endl;

					meetsSchema = false;
				}
			}
		}

		if (rootCount > 1 && !schema.AllowMultipleRoots)
		{
			std::cout << "multiple root nodes detected in " << path.GetPath() << " where only 1 root is allowed" << std::endl;

			meetsSchema = false;
		}

		return meetsSchema;
	}

	void validateSchemas(Archive::ArchiveReader& reader, bool isGms2, bool printSuccesses)
	{
		int validationCount = 0;

		for (const auto& schemaEntry : (isGms2 ? Gms2Schemas : Kms2Schemas))
		{
			const Schema& schema = schemaEntry.second;

			for (const SchemaDirectory& directory : schema.Directories)
			{
				Archive::ArchivePath path = reader.GetPath(directory.Path, true);

				if (!path.Loaded())
				{
					std::cout << "failed to load schema '" << schema.Name << "' directory '" << directory.Path << "'" << std::endl;

					continue;
				}

				const auto visit = [&schema, &directory, printSuccesses, &validationCount](const Archive::ArchivePath& path)
				{
					if (validationCount && validationCount % 1000 == 0)
					{
						std::cout << "validated " << validationCount << " files" << std::endl;
					}

					++validationCount;

					std::string fileName = path.GetPath().filename().stem().string();

					bool foundMatches = false;
					const SchemaFile* matchingFile = nullptr;

					for (const SchemaFile& file : directory.Files)
					{
						auto captureBegin = std::sregex_iterator(fileName.begin(), fileName.end(), file.NameRegex);
						auto captureEnd = std::sregex_iterator();

						for (auto captureGroup = captureBegin; captureGroup != captureEnd; ++captureGroup)
						{
							if (printSuccesses)
							{
								std::cout << "captured: " << captureGroup->str() << std::endl;
							}

							foundMatches = true;
						}

						if (foundMatches)
						{
							matchingFile = &file;

							break;
						}
					}

					if (!foundMatches)
					{
						return;
					}

					if (printSuccesses)
					{
						std::cout << fileName << ".xml matches " << matchingFile->Name << std::endl;
					}

					bool results = validateFileSchema(schema, path, printSuccesses);

					if (!results)
					{
						std::cout << "schema failed for '" << fileName << ".xml'" << std::endl;
					}
				};

				Archive::ForEachFile(path, directory.Recursive, visit);
			}
		}
	}
}