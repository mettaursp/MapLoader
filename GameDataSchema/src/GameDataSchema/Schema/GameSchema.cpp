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

			if (strcmp(name, "varies") == 0)
			{
				property.Varies = strcmp(value, "true") == 0;

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

	void readNode(Schema& schema, SchemaNode& node, tinyxml2::XMLElement* nodeElement, size_t pivotHeight)
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
					node.PivotNodeHeight = pivotHeight;
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

		if (node.NoVariance && node.PivotNodeHeight == -1)
		{
			std::cout << "node '" << node.Name << "' has noVariance enabled, but no pivot height set" << std::endl;
		}

		if (!node.NoVariance && node.PivotNodeHeight != -1)
		{
			std::cout << "node '" << node.Name << "' has pivot height set, but noVariance is disabled" << std::endl;
		}

		for (tinyxml2::XMLElement* child = nodeElement->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, "node") == 0)
			{
				node.ChildNodes.push_back({});

				readNode(schema, node.ChildNodes.back(), child, pivotHeight == (size_t)-1 ? pivotHeight : pivotHeight + 1);

				continue;
			}

			if (strcmp(name, "property") == 0)
			{
				node.Properties.push_back({});

				readProperty(schema, node.Properties.back(), child);

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

	struct NodeStats
	{
		bool HasFeature = false;
		bool HasLocale = false;
		std::unordered_map<std::string, int> Counts;
	};

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

	class FileValidator
	{
	public:
		bool ValidateNodeSchema(const SchemaNode* parentNode, size_t childIndex, const SchemaNode& node, tinyxml2::XMLElement* element, const std::string& path, std::string& featureOut, NodeStats& stats, bool printSuccesses);
		
	private:
		struct StackEntry
		{
			int AppearanceNumber = 0;
			size_t FeatureTagIndex = 0;
			tinyxml2::XMLElement* Node = nullptr;
		};

		struct AppearanceStats
		{
			int TotalAppearances = 0;
			int MaxChildAppearances = 0;
		};

		struct NodeData
		{
			const SchemaNode* Schema = nullptr;
			tinyxml2::XMLElement* Node = nullptr;
		};

		void FindSimilarNodes(tinyxml2::XMLElement* node, size_t height, size_t startHeight, const std::string& featureTag);
		bool ValidateNodeVariance(const SchemaNode& nodeSchema, size_t height);
		bool CompareNodeAttributes(const SchemaNode* nodeSchema, tinyxml2::XMLElement* node1, tinyxml2::XMLElement* node2, size_t stackIndex);
		void ReportVaryingDescendants(size_t stackIndex);
		std::string GetVaryingDescendantName(size_t stackIndex);

		std::vector<std::string> FeatureTagStack = { "" };
		std::vector<StackEntry> NodeStack;
		std::vector<tinyxml2::XMLElement*> SimilarNodes;
		std::vector<std::vector<NodeData>> SimilarNodeStacks;
		std::string VarianceMessage;
		std::unordered_map<const SchemaNode*, std::vector<std::unordered_map<std::string, AppearanceStats>>> ChildAppearances;
	};

	bool computeFeatureTag(tinyxml2::XMLElement* element, std::string& featureTag, bool& hasFeature, bool& hasLocale)
	{
		std::string feature;
		std::string locale;

		for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			const char* name = attribute->Name();
			const char* value = attribute->Value();

			bool isEmpty = strcmp(value, "") == 0;

			if (strcmp(name, "feature") == 0 && !isEmpty)
			{
				feature = attribute->Value();
				hasFeature = true;

				continue;
			}

			if (strcmp(name, "locale") == 0 && !isEmpty)
			{
				locale = attribute->Value();
				hasLocale = true;

				continue;
			}
		}

		if (hasFeature || hasLocale)
		{
			featureTag = feature + ":" + locale;
		}

		return hasFeature || hasLocale;
	}

	void FileValidator::FindSimilarNodes(tinyxml2::XMLElement* node, size_t height, size_t startHeight, const std::string& featureTag)
	{
		const StackEntry& nodeEntry = NodeStack[NodeStack.size() - 1 - height];

		if (FeatureTagStack[nodeEntry.FeatureTagIndex] != featureTag)
		{
			return;
		}

		if (height == 0)
		{
			SimilarNodes.push_back(node);

			return;
		}

		int appearance = 0;
		const StackEntry& childEntry = NodeStack[NodeStack.size() - height];
		const char* childEntryName = childEntry.Node->Name();

		for (tinyxml2::XMLElement* child = node->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();

			if (strcmp(name, childEntryName) != 0)
			{
				continue;
			}

			std::string feature;
			bool hasFeature = false;
			bool hasLocale = false;
			bool hasFeatureTag = computeFeatureTag(child, feature, hasFeature, hasLocale);

			if (hasFeatureTag)
			{
				feature = featureTag + "|" + feature;
			}

			const std::string& childFeatureTag = hasFeatureTag ? feature : featureTag;

			if (FeatureTagStack[childEntry.FeatureTagIndex] != childFeatureTag)
			{
				continue;
			}

			if (height != startHeight &&/*height < startHeight - 1 &&*/ appearance != childEntry.AppearanceNumber)
			{
				++appearance;

				continue;
			}

			++appearance;

			FindSimilarNodes(child, height - 1, startHeight, childFeatureTag);
		}
	}

	bool FileValidator::CompareNodeAttributes(const SchemaNode* nodeSchema, tinyxml2::XMLElement* node1, tinyxml2::XMLElement* node2, size_t stackIndex)
	{
		if ((node1 == nullptr) != (node2 == nullptr))
		{
			return false;
		}

		if (node1 == nullptr)
		{
			return true;
		}

		const char* name1 = node1->Name();
		const char* name2 = node2->Name();

		if (strcmp(name1, name2) != 0)
		{
			VarianceMessage = "descendant nodes don't match: '";
			VarianceMessage += name1;
			VarianceMessage += "' and '";
			VarianceMessage += name2;
			VarianceMessage += "'";

			return false;
		}

		if (nodeSchema && nodeSchema->Name != name1)
		{
			VarianceMessage = "error with comparing descendants";

			std::cout << "node schema doesn't match with descendant nodes" << std::endl;

			return false;
		}

		const tinyxml2::XMLAttribute* attribute1 = node1->FirstAttribute();
		const tinyxml2::XMLAttribute* attribute2 = node2->FirstAttribute();

		while (attribute1 && attribute2)
		{
			const SchemaProperty* property1 = nullptr;
			const SchemaProperty* property2 = nullptr;

			for (size_t i = 0; !(property1 && property2) && nodeSchema && i < nodeSchema->Properties.size(); ++i)
			{
				if (!property1 && attribute1 && nodeSchema->Properties[i].Name == attribute1->Name())
				{
					property1 = &nodeSchema->Properties[i];
				}

				if (!property2 && attribute2 && nodeSchema->Properties[i].Name == attribute2->Name())
				{
					property2 = &nodeSchema->Properties[i];
				}
			}

			if ((property1 && property1->Varies) || (property2 && property2->Varies))
			{
				if (property1 && property1->Varies && (!property2 || property1 < property2))
				{
					attribute1 = attribute1->Next();

					continue;
				}

				if (property2 && property2->Varies && (!property1 || property2 < property1))
				{
					attribute2 = attribute2->Next();

					continue;
				}

				if (property1 == property2 && strcmp(attribute1->Value(), attribute2->Value()) != 0)
				{
					attribute1 = attribute1->Next();
					attribute2 = attribute2->Next();

					continue;
				}
			}

			if ((attribute1 == nullptr) != (attribute2 == nullptr))
			{
				if (stackIndex == (size_t)-1)
				{
					VarianceMessage = "node has a varying number of attributes";
				}
				else
				{
					VarianceMessage = "descendant '" + GetVaryingDescendantName(stackIndex) + "' has a varying number of attributes";
				}

				return false;
			}
			
			if (property1 != property2)
			{
				if (stackIndex == (size_t)-1)
				{
					VarianceMessage = std::string("node has varying attribute appearances: '") + attribute1->Name() + "' and '" + attribute2->Name() + "'";
				}
				else
				{
					VarianceMessage = "descendant '" + GetVaryingDescendantName(stackIndex) + "' has varying attribute appearances: '" + attribute1->Name() + "' and '" + attribute2->Name() + "'";
				}

				return false;
			}

			if (strcmp(attribute1->Value(), attribute2->Value()) != 0)
			{
				if (stackIndex == (size_t)-1)
				{
					VarianceMessage = std::string("node has varying attribute values in attribute '") + attribute1->Name() + "'";
				}
				else
				{
					VarianceMessage = "descendant '" + GetVaryingDescendantName(stackIndex) + "' has varying attribute values in attribute '" + attribute1->Name() + "'";
				}

				return false;
			}

			attribute1 = attribute1->Next();
			attribute2 = attribute2->Next();
		}

		return true;
	}

	std::string FileValidator::GetVaryingDescendantName(size_t stackIndex)
	{
		auto& stack0 = SimilarNodeStacks[0];
		auto& stack = SimilarNodeStacks[stackIndex];

		size_t size0 = stack0.size();
		size_t size = stack.size();

		if (size0 < size)
		{
			std::string name = stack0[0].Node->Name();

			for (size_t i = 1; i < size0; ++i)
			{
				name += ".";
				name += stack0[i].Node->Name();
			}

			return name;
		}

		std::string name = stack[0].Node->Name();

		for (size_t i = 1; i < size; ++i)
		{
			name += ".";
			name += stack[i].Node->Name();
		}

		return name;
	}

	void FileValidator::ReportVaryingDescendants(size_t stackIndex)
	{
		auto& stack0 = SimilarNodeStacks[0];
		auto& stack = SimilarNodeStacks[stackIndex];

		if (stack0.back().Node == nullptr)
		{
			stack0.pop_back();
		}

		if (stack.back().Node == nullptr)
		{
			stack.pop_back();
		}

		size_t size0 = stack0.size();
		size_t size = stack.size();

		if (size0 == 0 || size == 0)
		{
			VarianceMessage = "node has a varying number of children";

			return;
		}

		VarianceMessage = std::string("descendant '") + GetVaryingDescendantName(stackIndex) + "' has a varying number of children";
	}

	const SchemaNode* findChildSchema(const SchemaNode* parentSchema, tinyxml2::XMLElement* child)
	{
		if (parentSchema == nullptr || child == nullptr)
		{
			return nullptr;
		}

		const char* childName = child->Name();

		for (size_t i = 0; i < parentSchema->ChildNodes.size(); ++i)
		{
			if (parentSchema->ChildNodes[i].Name == childName)
			{
				return &parentSchema->ChildNodes[i];
			}
		}

		return nullptr;
	}

	bool FileValidator::ValidateNodeVariance(const SchemaNode& nodeSchema, size_t height)
	{
		const StackEntry& pivotEntry = NodeStack[NodeStack.size() - 1 - height];

		FindSimilarNodes(pivotEntry.Node, height, height, FeatureTagStack[pivotEntry.FeatureTagIndex]);

		if (SimilarNodes.size() == 0)
		{
			std::cout << "failed to find similar nodes in variance test" << std::endl;

			FindSimilarNodes(pivotEntry.Node, height, height, FeatureTagStack[pivotEntry.FeatureTagIndex]);

			return false;
		}

		if (SimilarNodes.size() == 1)
		{
			SimilarNodes.clear();

			return true;
		}

		for (size_t i = 1; i < SimilarNodes.size(); ++i)
		{
			bool matches = CompareNodeAttributes(&nodeSchema, SimilarNodes[0], SimilarNodes[i], (size_t)-1);

			if (!matches)
			{
				SimilarNodes.clear();

				if (VarianceMessage.size() == 0)
				{
					VarianceMessage = "node has a varying number of children";
				}

				return false;
			}
		}

		SimilarNodeStacks.resize(SimilarNodes.size());

		for (size_t i = 0; i < SimilarNodes.size(); ++i)
		{
			auto& stack = SimilarNodeStacks[i];

			tinyxml2::XMLElement* child = SimilarNodes[i]->FirstChildElement();
			const SchemaNode* childSchema = findChildSchema(&nodeSchema, child);

			stack.push_back({ childSchema, child });
		}

		SimilarNodes.clear();

		while (SimilarNodeStacks[0].size())
		{
			auto& stack0 = SimilarNodeStacks[0];

			for (size_t i = 1; i < SimilarNodeStacks.size(); ++i)
			{
				auto& stack = SimilarNodeStacks[i];

				bool matches = CompareNodeAttributes(stack0.back().Schema, stack0.back().Node, stack.back().Node, i);

				if (!matches)
				{
					if (VarianceMessage.size() == 0)
					{
						ReportVaryingDescendants(i);
					}

					SimilarNodeStacks.clear();

					return false;
				}
			}

			for (size_t i = 0; i < SimilarNodeStacks.size(); ++i)
			{
				auto& stack = SimilarNodeStacks[i];
				const auto& nodeEntry = stack.back();

				if (nodeEntry.Node == nullptr)
				{
					stack.pop_back();

					if (stack.size() > 0)
					{
						const auto& nodeEntry = stack.back();
						const SchemaNode* parentSchema = stack.size() > 1 ? stack[stack.size() - 2].Schema : &nodeSchema;
						tinyxml2::XMLElement* sibling = nodeEntry.Node->NextSiblingElement();
						const SchemaNode* siblingSchema = findChildSchema(parentSchema, sibling);

						stack.back() = { siblingSchema, sibling };
					}

					continue;
				}

				const SchemaNode* parentSchema = stack.size() > 1 ? nodeEntry.Schema : &nodeSchema;
				tinyxml2::XMLElement* child = nodeEntry.Node->FirstChildElement();
				const SchemaNode* childSchema = findChildSchema(parentSchema, child);

				stack.push_back({ childSchema, child });
			}

			for (size_t i = 1; i < SimilarNodeStacks.size(); ++i)
			{
				auto& stack = SimilarNodeStacks[i];

				size_t size0 = stack0.size();
				size_t size = stack.size();

				if (size0 != size)
				{
					SimilarNodeStacks.clear();

					ReportVaryingDescendants(i);

					return false;
				}
			}

			if (stack0.size() == 0)
			{
				return true;
			}
		}

		return true;
	}

	std::string computePivotPath(const std::string& currentPath, const std::string& path, size_t height)
	{
		size_t pathSize = path.size();
		size_t pivotNodeEnd = pathSize;

		for (int i = 0; pivotNodeEnd <= pathSize && i < height - 1; ++i)
		{
			while (pivotNodeEnd <= pathSize && path[pivotNodeEnd] != '.')
			{
				--pivotNodeEnd;
			}

			--pivotNodeEnd;
		}

		if (pivotNodeEnd >= pathSize)
		{
			std::cout << "failed to find pivot subscript on node '" + currentPath + "'" << std::endl;
		}
		else if (path[pivotNodeEnd] == ']')
		{
			size_t count = 1;

			for (count; pivotNodeEnd - count < pathSize && (path[pivotNodeEnd - count] >= '0' && path[pivotNodeEnd - count] <= '9'); ++count);

			std::string start = path.substr(0, pivotNodeEnd - count);
			std::string end = path.substr(pivotNodeEnd + 1, pathSize - pivotNodeEnd - 1);

			if (start[start.size() - 1] == '[' || end[0] == ']')
			{
				std::cout << "error generating pivot path" << std::endl;
			}

			return start + end;
		}

		return path;
	}

	bool FileValidator::ValidateNodeSchema(const SchemaNode* parentNode, size_t childIndex, const SchemaNode& node, tinyxml2::XMLElement* element, const std::string& path, std::string& featureOut, NodeStats& stats, bool printSuccesses)
	{
		bool meetsSchema = true;

		bool hasFeature = false;
		bool hasLocale = false;
		bool hasFeatureTag = computeFeatureTag(element, featureOut, hasFeature, hasLocale);

		stats.HasFeature |= hasFeature;
		stats.HasLocale |= hasLocale;

		if (hasFeatureTag)
		{
			FeatureTagStack.push_back(FeatureTagStack.back() + "|" + featureOut);
		}

		int& count = stats.Counts[featureOut];
		int appearanceNumber = count;
		int totalAppearanceNumber = 0;

		++count;

		auto& childAppearanceVector = ChildAppearances[&node];

		if (childAppearanceVector.size() == 0)
		{
			childAppearanceVector.resize(node.ChildNodes.size());
		}

		NodeStack.push_back({ appearanceNumber, FeatureTagStack.size() - 1, element });

		std::string currentPath = path + "." + node.Name;
		std::string pivotPath = featureOut + "|" + currentPath;

		if (node.NoVariance)
		{
			const StackEntry& pivotNode = NodeStack[NodeStack.size() - node.PivotNodeHeight];

			if (pivotNode.AppearanceNumber != 0)
			{
				pivotPath = computePivotPath(currentPath, pivotPath, node.PivotNodeHeight);
			}
		}

		if (parentNode != nullptr)
		{
			int& currentAppearance = ChildAppearances[parentNode][childIndex][pivotPath].TotalAppearances;

			totalAppearanceNumber = currentAppearance;

			++currentAppearance;
		}

		if (node.NoVariance && totalAppearanceNumber == 0)
		{
			const StackEntry& pivotNode = NodeStack[NodeStack.size() - node.PivotNodeHeight];

			if (pivotNode.AppearanceNumber != 0)
			{
				std::cout << "node " << currentPath << " marked for NoVariance was found to vary: varying number of appearances; first appearance wasn't in pivot node's first appearance" << std::endl;

				meetsSchema = false;
			}
		}

		if (appearanceNumber != 0)
		{
			char buffer[12] = { 0 };

			_itoa_s(appearanceNumber, buffer, 10);

			currentPath = currentPath + "[" + buffer + "]";
		}

		for (const SchemaProperty& property : node.Properties)
		{
			for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				const char* name = attribute->Name();

				if (property.Name != name)
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

				if (!valueMatches && property.Types.size())
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

		std::vector<NodeStats> elementCounts(node.ChildNodes.size());

		for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
		{
			const char* name = child->Name();
			bool foundMatch = false;

			for (size_t i = 0; i < node.ChildNodes.size(); ++i)
			{
				const SchemaNode& childNode = node.ChildNodes[i];
				NodeStats& stats = elementCounts[i];

				if (childNode.Name == name)
				{
					foundMatch = true;

					std::string nodeFeature;
					bool nodeMatches = ValidateNodeSchema(&node, i, childNode, child, currentPath, nodeFeature, stats, printSuccesses);

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
			NodeStats& stats = elementCounts[i];

			bool matches = validateNodeStats(&node, childNode, stats, currentPath);

			meetsSchema &= matches;

			if (childNode.NoVariance)
			{
				const StackEntry& pivotNode = NodeStack[NodeStack.size() - childNode.PivotNodeHeight];
				const StackEntry& pivotNodeChild = NodeStack[NodeStack.size() - childNode.PivotNodeHeight + 1];

				std::string childPath = currentPath + "." + childNode.Name;
				std::string childPivotPath = computePivotPath(childPath, featureOut + "|" + childPath, childNode.PivotNodeHeight);
				auto& childAppearances = ChildAppearances[&node][i];

				int& maxAppearances = childAppearanceVector[i][childPivotPath].MaxChildAppearances;
				int childCount = stats.Counts[featureOut];

				if (pivotNodeChild.AppearanceNumber != 0 && maxAppearances != childCount)
				{
					std::cout << "node " << childPath << " marked for NoVariance was found to vary: varying number of appearances; appearance count is different from previous appearance counts" << std::endl;

					meetsSchema = false;
				}

				maxAppearances = childCount;
			}
		}

		if (node.NoVariance)
		{
			const StackEntry& pivotNode = NodeStack[NodeStack.size() - 1 - node.PivotNodeHeight];
			const StackEntry& pivotNodeChild = NodeStack[NodeStack.size() - node.PivotNodeHeight];
			//bool a;
			//
			//if (((childIndex == 4 && node.PivotNodeHeight == 2) || (childIndex == 1 && node.PivotNodeHeight == 3)) && !(currentPath[10] == '0'))
			//{
			//	a = true;
			//}

			if (pivotNode.AppearanceNumber == 0)
			{
				bool noVariance = ValidateNodeVariance(node, node.PivotNodeHeight);

				if (!noVariance)
				{
					std::cout << "node " << currentPath << " marked for NoVariance was found to vary: " << VarianceMessage << std::endl;

					//ValidateNodeVariance(node.PivotNodeHeight);
				}

				meetsSchema &= noVariance;
			}
		}

		NodeStack.pop_back();

		if (hasFeatureTag)
		{
			FeatureTagStack.pop_back();
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