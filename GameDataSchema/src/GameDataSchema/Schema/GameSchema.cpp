#include "GameSchema.h"

#include "SchemaTypes.h"
#include "FileValidator.h"

namespace GameSchema
{
	const std::unordered_map<std::string, SchemaType> Types = {
		{ "int", { "int", SchemaTypes::Int{} }},
		{ "short", { "short", SchemaTypes::Short{} }},
		{ "long", { "long", SchemaTypes::Long{} }},
		{ "enum", { "enum", SchemaTypes::Enum{} }},
		{ "stringEnum", { "enum", SchemaTypes::StringEnum{} }},
		{ "mixedEnum", { "enum", SchemaTypes::MixedEnum{} }},
		{ "string", { "string", SchemaTypes::String{} }},
		{ "float", { "float", SchemaTypes::Float{} }},
		{ "bool", { "bool", SchemaTypes::Bool{} }},
		{ "stringBool", { "bool", SchemaTypes::StringBool{} }},
		{ "Vector3", { "Vector3", SchemaTypes::Vector3{} }}
	};

	const SchemaType* FindValidType(const std::string_view& value, const std::vector<const SchemaType*>& types, bool isArray)
	{
		for (const SchemaType* type : types)
		{
			if (isArray && SchemaTypes::ValidateArray(value, type->ValidateValue))
			{
				return type;
			}

			if (!isArray && type->ValidateValue(value))
			{
				return type;
			}
		}

		return nullptr;
	}

	const SchemaType* FindValidType(const std::string_view& value, const std::vector<const SchemaType*>& types, const SchemaType* mapKeyType)
	{
		if (mapKeyType == nullptr)
		{
			return nullptr;
		}

		for (const SchemaType* type : types)
		{
			if (SchemaTypes::ValidateMap(value, mapKeyType->ValidateValue, type->ValidateValue))
			{
				return type;
			}
		}

		return nullptr;
	}

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

	void readAttribute(SchemaNode& node, SchemaAttribute& attrib, tinyxml2::XMLElement* attributeElement, size_t pivotHeight)
	{
		for (const tinyxml2::XMLAttribute* attribute = attributeElement->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			if (strcmp(name, "name") == 0)
			{
				attrib.Name = value;

				continue;
			}

			if (strcmp(name, "remapTo") == 0)
			{
				attrib.RemapTo = value;

				continue;
			}

			if (strcmp(name, "default") == 0)
			{
				if (attrib.Types.size() > 0)
				{
					bool foundMatch = FindValidType(value, attrib.Types, attrib.IsArray) != nullptr;

					if (!foundMatch)
					{
						std::cout << "warning: attribute '" << attrib.Name << "' default value '" << value << "' failed type validation" << std::endl;

						continue;
					}
				}

				attrib.Default = value;

				continue;
			}

			if (strcmp(name, "isArray") == 0)
			{
				attrib.IsArray = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "optional") == 0)
			{
				attrib.Optional = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "unmapped") == 0)
			{
				attrib.Unmapped = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "alwaysValue") == 0)
			{
				if (attrib.Types.size() > 0)
				{
					bool foundMatch = FindValidType(value, attrib.Types, attrib.IsArray) != nullptr;

					if (!foundMatch)
					{
						std::cout << "warning: attribute '" << attrib.Name << "' is set to be always value '" << value << "' which failed type validation" << std::endl;

						continue;
					}
				}

				attrib.IsAlwaysValue = true;
				attrib.AlwaysValue = value;

				continue;
			}

			if (strcmp(name, "alwaysNotDefault") == 0)
			{
				attrib.IsAlwaysNotDefault = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "valueOptional") == 0)
			{
				attrib.IsValueOptional = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "filePath") == 0)
			{
				attrib.IsFilePath = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "varies") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked as varying in non varying region" << std::endl;
				}
				else
				{
					attrib.Varies = strcmp(value, "true") == 0;
				}

				continue;
			}

			if (strcmp(name, "ignoreVariance") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked to ignore variance in non varying region" << std::endl;

					continue;
				}

				attrib.Varies = true;
				attrib.IgnoreVariance = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "preferValue") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked to ignore variance in non varying region" << std::endl;

					continue;
				}

				if (attrib.Varies)
				{
					std::cout << "warning: attribute '" << attrib.Name << "' is set to not vary and prefer specific value, but was already specified to vary" << std::endl;

					continue;
				}

				if (!attrib.IgnoreVarianceIfEqual)
				{
					std::cout << "warning: attribute '" << attrib.Name << "' is set to not vary and prefer specific value, but ignore variance values weren't set" << std::endl;

					continue;
				}

				if (attrib.Types.size() > 0)
				{
					bool foundMatch = FindValidType(value, attrib.Types, attrib.IsArray) != nullptr;

					if (!foundMatch)
					{
						std::cout << "warning: attribute '" << attrib.Name << "' is set to be always value '" << value << "' which failed type validation" << std::endl;

						continue;
					}
				}

				attrib.PreferValue = value;

				continue;
			}

			if (strcmp(name, "ignoreVarianceIfEqualToParam") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked to ignore variance if equal to parameter '" << value << "' in non varying region" << std::endl;
				}
				else
				{
					attrib.IgnoreVarianceIfEqualToParam = value;
					node.AttributesDependOnVarianceParam = true;
				}

				continue;
			}

			if (strcmp(name, "ignoreVarianceIfEqualTo") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked to ignore variance if equal to value '" << value << "' in non varying region" << std::endl;
				}
				else
				{
					size_t start = 0;
					size_t i = 0;

					for (i; value[i]; ++i)
					{
						if (value[i] == ',')
						{
							attrib.IgnoreVarianceIfEqualToValues.push_back(std::string(value + start, i - start));

							start = i + 1;
						}
					}

					attrib.IgnoreVarianceIfEqualToValues.push_back(std::string(value + start, i - start));

					if (attrib.Types.size() > 0)
					{
						for (const std::string& value : attrib.IgnoreVarianceIfEqualToValues)
						{
							bool foundMatch = FindValidType(value, attrib.Types, attrib.IsArray) != nullptr;

							if (!foundMatch)
							{
								std::cout << "warning: attribute '" << attrib.Name << "' is set to be always value '" << value << "' which failed type validation" << std::endl;

								continue;
							}
						}
					}

					attrib.IgnoreVarianceIfEqual = true;
					node.AttributesDependOnVarianceParam = true;
				}

				continue;
			}

			if (strcmp(name, "varianceParameterId") == 0)
			{
				if (pivotHeight == (size_t)-1)
				{
					std::cout << "attribute '" << attrib.Name << "' marked as being a variance parameter in non varying region" << std::endl;
				}
				else
				{
					attrib.VarianceParameterId = value;
				}

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

					attrib.Types.push_back(&typeEntry->second);
				}

				continue;
			}

			if (strcmp(name, "mapKeyType") == 0)
			{
				const auto& typeEntry = Types.find(value);

				if (typeEntry == Types.end())
				{
					std::cout << "unknown map key type '" << value << "' referenced" << std::endl;

					continue;
				}

				attrib.IsMap = true;
				attrib.MapKeyType = &typeEntry->second;

				continue;
			}

			std::cout << "unknown 'node' attribute: '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = attributeElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "settings") == 0)
			{
				readAttribute(node, attrib, child, pivotHeight);

				continue;
			}

			std::cout << "invalid child '" << name << "' on 'attribute.settings' node" << std::endl;
		}
	}

	void readNodeSettings(Schema& schema, SchemaNode& node, tinyxml2::XMLElement* nodeElement, size_t& pivotHeight)
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

			if (strcmp(name, "hasFeature") == 0)
			{
				node.HasFeature = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "hasLocale") == 0)
			{
				node.HasLocale = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "allowUnknownChildren") == 0)
			{
				node.AllowUnknownChildren = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "noVariance") == 0)
			{
				if (pivotHeight != (size_t)-1)
				{
					node.NoVariance = strcmp(value, "true") == 0;
					node.PivotNodeHeight = (int)pivotHeight;
				}
				else
				{
					std::cout << "node '" << node.Name << "' marked as having no variance when in a non varying region" << std::endl;
				}

				continue;
			}

			if (strcmp(name, "hasVariants") == 0)
			{
				if (pivotHeight != (size_t)-1)
				{
					std::cout << "node '" << node.Name << "' marked as having variants when in varying region of depth: " << pivotHeight << "" << std::endl;
				}
				else
				{
					node.IsVariancePivot = strcmp(value, "true") == 0;
					pivotHeight = 1;
				}

				continue;
			}

			std::cout << "unknown 'node' attribute: '" << name << "'" << std::endl;
		}
	}

	void readNode(Schema& schema, SchemaNode& node, tinyxml2::XMLElement* nodeElement, size_t pivotHeight)
	{
		readNodeSettings(schema, node, nodeElement, pivotHeight);

		for (tinyxml2::XMLElement* child = nodeElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "node") == 0)
			{
				node.ChildNodes.push_back({});

				readNode(schema, node.ChildNodes.back(), child, pivotHeight == (size_t)-1 ? pivotHeight : pivotHeight + 1);

				continue;
			}

			if (strcmp(name, "attribute") == 0)
			{
				node.Attributes.push_back({});

				readAttribute(node, node.Attributes.back(), child, pivotHeight);

				continue;
			}

			if (strcmp(name, "requiredNode") == 0)
			{
				for (const tinyxml2::XMLAttribute* attribute = child->FirstAttribute(); attribute; attribute = attribute->Next())
				{
					const char* name = attribute->Name();

					if (strcmp(name, "name") == 0)
					{
						node.RequiredNodes.push_back(attribute->Value());

						continue;
					}

					std::cout << "unknown 'requiredNode' attribute: '" << name << "'" << std::endl;
				}

				continue;
			}

			if (strcmp(name, "settings") == 0)
			{
				readNodeSettings(schema, node, child, pivotHeight);

				for (tinyxml2::XMLElement* descendant = child->FirstChildElement(); descendant; descendant = descendant->NextSiblingElement())
				{
					std::cout << "invalid child '" << descendant->Name() << "' on 'node.settings' node" << std::endl;
				}

				continue;
			}

			std::cout << "unknown node: '" << name << "'" << std::endl;
		}

		if (node.NoVariance && node.PivotNodeHeight == -1)
		{
			std::cout << "node '" << node.Name << "' has noVariance enabled, but no pivot height set" << std::endl;
		}

		if (!node.NoVariance && node.PivotNodeHeight != -1)
		{
			std::cout << "node '" << node.Name << "' has pivot height set, but noVariance is disabled" << std::endl;
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
				schema.RootNode.Name = value;

				continue;
			}

			if (strcmp(name, "allowMultiple") == 0)
			{
				schema.RootNode.AllowMultiple = strcmp(value, "true") == 0;

				continue;
			}

			if (strcmp(name, "allowUnknownChildren") == 0)
			{
				schema.RootNode.AllowUnknownChildren = strcmp(value, "true") == 0;

				continue;
			}

			std::cout << "unknown 'layout' attribute: '" << name << "'" << std::endl;
		}

		for (tinyxml2::XMLElement* child = layoutElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "node") == 0)
			{
				schema.RootNode.ChildNodes.push_back({});

				readNode(schema, schema.RootNode.ChildNodes.back(), child);

				continue;
			}

			if (strcmp(name, "requiredNode") == 0)
			{
				for (const tinyxml2::XMLAttribute* attribute = child->FirstAttribute(); attribute; attribute = attribute->Next())
				{
					const char* name = attribute->Name();

					if (strcmp(name, "name") == 0)
					{
						schema.RootNode.RequiredNodes.push_back(attribute->Value());

						continue;
					}

					std::cout << "unknown 'requiredNode' attribute: '" << name << "'" << std::endl;
				}

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

	bool validateNodeStats(const SchemaNode* node, const SchemaNode& childNode, const NodeStats& stats, const std::string& currentPath)
	{
		bool meetsSchema = true;

		if (stats.HasFeature && !childNode.HasFeature)
		{
			std::cout << "node '" << childNode.Name << "' not marked for features has feature" << std::endl;
		}

		if (stats.HasLocale && !childNode.HasLocale)
		{
			std::cout << "node '" << childNode.Name << "' not marked for locale has locale" << std::endl;
		}

		for (const auto& featureCountEntry : stats.Counts)
		{
			int featureCount = featureCountEntry.second;

			if (featureCount > 1 && !childNode.AllowMultiple)
			{
				std::cout << "multiple '" << childNode.Name << "' nodes detected in " << currentPath << " where only 1 '" << childNode.Name << "' is allowed" << std::endl;

				meetsSchema = false;
			}
		}

		bool nodeIsRequired = false;

		if (node != nullptr)
		{
			for (const std::string& required : node->RequiredNodes)
			{
				if (required == childNode.Name)
				{
					nodeIsRequired = true;

					break;
				}
			}
		}

		const auto& featureCountEntry = stats.Counts.find("");

		if (nodeIsRequired && childNode.Optional)
		{
			std::cout << "schema for node '" << childNode.Name << "' marked as required and optional simultaneously" << std::endl;
		}

		if ((featureCountEntry == stats.Counts.end() || featureCountEntry->second == 0) && !childNode.Optional && !nodeIsRequired)
		{
			std::cout << "missing required node '" << childNode.Name << "' in " << currentPath << std::endl;

			meetsSchema = false;
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

		NodeStats rootStats;
		bool meetsSchema = true;
		std::string filePath = path.GetPath().string();
		FileValidator validator;

		for (rootElement; rootElement; rootElement = rootElement->NextSiblingElement())
		{
			std::string currentPath = filePath + ":" + rootElement->Name();

			std::string nodeFeature;

			if (schema.RootNode.Name != rootElement->Name())
			{
				std::cout << "file root element '" << rootElement->Name() << "' doesn't match schema '" << schema.RootNode.Name << "'" << std::endl;

				meetsSchema = false;

				continue;
			}

			bool childrenMatch = validator.ValidateNodeSchema(nullptr, 0, schema.RootNode, rootElement, currentPath, nodeFeature, rootStats, printSuccesses);

			meetsSchema &= childrenMatch;
		}

		bool statsMatch = validateNodeStats(nullptr, schema.RootNode, rootStats, filePath);

		meetsSchema &= statsMatch;

		if (rootStats.Counts[""] > 1 && !schema.RootNode.AllowMultiple)
		{
			std::cout << "multiple root nodes detected in " << path.GetPath() << " where only 1 root is allowed" << std::endl;

			meetsSchema = false;
		}

		return meetsSchema;
	}

	void validateSchemas(Archive::ArchiveReader& reader, bool isGms2, const std::vector<std::string>& schemaNames, bool printSuccesses)
	{
		bool validateAll = schemaNames.size() > 0 && schemaNames[0] == "-all";
		int validationCount = 0;

		for (const auto& schemaEntry : (isGms2 ? Gms2Schemas : Kms2Schemas))
		{
			const Schema& schema = schemaEntry.second;

			if (!validateAll)
			{
				bool skip = true;

				for (const std::string& name : schemaNames)
				{
					if (name == schema.Name)
					{
						skip = false;

						break;
					}
				}
				
				if (skip)
				{
					continue;
				}
			}

			std::cout << (isGms2 ? "validating GMS2 schema type '" : "validating KMS2 schema type '") << schema.Name << "'" << std::endl;

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