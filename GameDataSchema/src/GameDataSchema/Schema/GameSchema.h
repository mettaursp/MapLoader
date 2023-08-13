#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <regex>
#include <string_view>

#include <tinyxml2/tinyxml2.h>
#include <ArchiveParser/ArchiveReader.h>

namespace GameSchema
{
	struct SchemaType
	{
		std::string Name;

		bool(*ValidateValue)(const std::string_view& value);

		SchemaType(const std::string& name) : Name(name), ValidateValue(nullptr) {}

		template <typename T>
		SchemaType(const std::string& name, const T& validator) : Name(name)
		{
			ValidateValue = &T::ValidateValue;
		}
	};

	const SchemaType* FindValidType(const std::string_view& value, const std::vector<const SchemaType*>& types, bool isArray);
	const SchemaType* FindValidType(const std::string_view& value, const std::vector<const SchemaType*>& types, const SchemaType* mapKeyType);

	extern const std::unordered_map<std::string, SchemaType> Types;

	struct SchemaFile
	{
		std::string Name;
		std::regex NameRegex;

		std::vector<std::string> NameArguments;
		std::vector<const SchemaType*> NameArgumentTypes;
	};

	struct SchemaDirectory
	{
		bool Recursive = false;
		std::string Path;

		std::vector<SchemaFile> Files;
	};

	struct SchemaAttribute
	{
		std::string Name;
		std::string Default;
		std::string RemapTo;
		bool Unmapped = false;
		bool Varies = false;
		bool IgnoreVariance = false;
		std::string VarianceParameterId;
		std::string IgnoreVarianceIfEqualToParam;
		std::vector<std::string> IgnoreVarianceIfEqualToValues;
		bool IgnoreVarianceIfEqual = false;
		bool IsArray = false;
		bool IsMap = false;
		bool Optional = false;
		bool IsAlwaysValue = false;
		bool IsValueOptional = false;
		bool IsFilePath = false;
		std::string AlwaysValue;
		bool IsAlwaysNotDefault = false;
		std::string PreferValue;

		const SchemaType* MapKeyType = nullptr;

		std::vector<const SchemaType*> Types;
	};

	struct SchemaNode
	{
		std::string Name;
		bool Optional = false;
		bool AllowMultiple = false;
		bool AllowUnknownChildren = false;
		bool HasFeature = false;
		bool HasLocale = false;
		bool NoVariance = false;
		bool IsVariancePivot = false;
		bool AttributesDependOnVarianceParam = false;
		int PivotNodeHeight = -1;

		std::vector<SchemaNode> ChildNodes;
		std::vector<SchemaAttribute> Attributes;
		std::vector<std::string> RequiredNodes;
	};

	struct Schema
	{
		std::string Name;
		//std::string Root;
		//bool AllowMultipleRoots = false;
		//bool AllowUnknownChildren = false;
		SchemaNode RootNode;

		std::vector<SchemaDirectory> Directories;
		//std::vector<SchemaNode> Nodes;
		//std::vector<std::string> RequiredNodes;
	};

	struct NodeStats
	{
		bool HasFeature = false;
		bool HasLocale = false;
		std::unordered_map<std::string, int> Counts;
	};

	bool validateNodeStats(const SchemaNode* node, const SchemaNode& childNode, const NodeStats& stats, const std::string& currentPath);

	extern std::unordered_map<std::string, Schema> Gms2Schemas;
	extern std::unordered_map<std::string, Schema> Kms2Schemas;

	void readFile(Schema& schema, SchemaFile& file, tinyxml2::XMLElement* fileElement);

	void readDirectory(Schema& schema, SchemaDirectory& directory, tinyxml2::XMLElement* directoryElement);

	void readAttribute(SchemaNode& node, SchemaAttribute& attrib, tinyxml2::XMLElement* attributeElement, size_t pivotHeight);

	void readNode(Schema& schema, SchemaNode& node, tinyxml2::XMLElement* nodeElement, size_t pivotHeight = (size_t)-1);

	void readLayout(Schema& schema, tinyxml2::XMLElement* layoutElement);

	void readSchema(const fs::path& filePath, bool isGms2);

	void readSchemas(const fs::path& directory, bool isGms2);

	bool validateFileSchema(const Schema& schema, const Archive::ArchivePath& path, bool printSuccesses);

	void validateSchemas(Archive::ArchiveReader& reader, bool isGms2, const std::vector<std::string>& schemaNames, bool printSuccesses = false);
}