#include "FileValidator.h"

namespace GameSchema
{
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

	bool FileValidator::CompareNodeAttributes(const SchemaNode* nodeSchema, tinyxml2::XMLElement* node1, tinyxml2::XMLElement* node2, size_t stackIndex, std::vector<const SchemaAttribute*>& varyingsAttributesToCheck)
	{
		VarianceMessage.clear();

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
			const SchemaAttribute* attrib1 = nullptr;
			const SchemaAttribute* attrib2 = nullptr;

			for (size_t i = 0; !(attrib1 && attrib2) && nodeSchema && i < nodeSchema->Attributes.size(); ++i)
			{
				if (!attrib1 && attribute1 && nodeSchema->Attributes[i].Name == attribute1->Name())
				{
					attrib1 = &nodeSchema->Attributes[i];
				}

				if (!attrib2 && attribute2 && nodeSchema->Attributes[i].Name == attribute2->Name())
				{
					attrib2 = &nodeSchema->Attributes[i];
				}
			}

			bool ignoreProperty1Variance = false;
			bool property1ChecksValue = false;
			bool ignoreProperty2Variance = false;
			bool property2ChecksValue = false;

			if (attrib1)
			{
				ignoreProperty1Variance = attrib1->Varies;
				property1ChecksValue = (attrib1->IgnoreVarianceIfEqualToParam.size() || attrib1->IgnoreVarianceIfEqual) && (!attrib2 || attrib1 <= attrib2);
			}

			if (attrib2)
			{
				ignoreProperty2Variance = attrib2->Varies;
				property2ChecksValue = (attrib2->IgnoreVarianceIfEqualToParam.size() || attrib2->IgnoreVarianceIfEqual) && (!attrib1 || attrib2 <= attrib1);
			}

			if (ignoreProperty1Variance || ignoreProperty2Variance)
			{
				if (ignoreProperty1Variance && (!attrib2 || attrib1 < attrib2))
				{
					attribute1 = attribute1->Next();

					continue;
				}

				if (ignoreProperty2Variance && (!attrib1 || attrib2 < attrib1))
				{
					attribute2 = attribute2->Next();

					continue;
				}

				if (attrib1 == attrib2)
				{
					attribute1 = attribute1->Next();
					attribute2 = attribute2->Next();

					continue;
				}
			}

			if ((attribute1 == nullptr) != (attribute2 == nullptr))
			{
				if (property1ChecksValue || property2ChecksValue)
				{
					varyingsAttributesToCheck.push_back(attribute1 ? attrib1 : attrib2);

					const tinyxml2::XMLAttribute*& attribute = property1ChecksValue ? attribute1 : attribute2;

					attribute = attribute->Next();

					continue;
				}
				else
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
			}

			if (attrib1 != attrib2)
			{
				if (property1ChecksValue || property2ChecksValue)
				{
					varyingsAttributesToCheck.push_back(property1ChecksValue ? attrib1 : attrib2);

					const tinyxml2::XMLAttribute*& attribute = property1ChecksValue ? attribute1 : attribute2;

					attribute = attribute->Next();

					continue;
				}
				else
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
			}

			if (strcmp(attribute1->Value(), attribute2->Value()) != 0)
			{
				if (property1ChecksValue)
				{
					varyingsAttributesToCheck.push_back(attrib1);

					attribute1 = attribute1->Next();
					attribute2 = attribute2->Next();

					continue;
				}
				else
				{
					if (stackIndex == (size_t)-1)
					{
						VarianceMessage = std::string("node has varying attribute values in attribute '") + attribute1->Name() + "': '";
					}
					else
					{
						VarianceMessage = "descendant '" + GetVaryingDescendantName(stackIndex) + "' has varying attribute values in attribute '" + attribute1->Name() + "': '";
					}

					VarianceMessage = VarianceMessage + attribute1->Value() + "' vs '" + attribute2->Value() + "'";

					return false;
				}
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

	bool FileValidator::ValidateNodeVariance(const SchemaNode& nodeSchema, size_t height, std::vector<const SchemaAttribute*>& varyingsAttributesToCheck)
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
			bool matches = CompareNodeAttributes(&nodeSchema, SimilarNodes[0], SimilarNodes[i], (size_t)-1, varyingsAttributesToCheck);

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

				bool matches = CompareNodeAttributes(stack0.back().Schema, stack0.back().Node, stack.back().Node, i, varyingsAttributesToCheck);

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

		if (node.IsVariancePivot)
		{
			VarianceParameters.clear();
		}

		for (size_t attribIndex = 0; attribIndex < node.Attributes.size(); ++attribIndex)
		{
			const SchemaAttribute& attrib = node.Attributes[attribIndex];

			bool attributeAppears = false;

			for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				const char* name = attribute->Name();

				if (attrib.Name != name)
				{
					continue;
				}

				attributeAppears = true;

				std::string_view value = attribute->Value();
				bool isDefaultValue = attrib.Default == value;
				bool valueMatches = false;

				for (size_t i = 0; i < attrib.Types.size() && !valueMatches; ++i)
				{
					const SchemaType* type = attrib.Types[i];

					if (type->ValidateValue != nullptr)
					{
						valueMatches = type->ValidateValue(value);
					}

					if (valueMatches)
					{
						if (printSuccesses)
						{
							const char* validMessage = isDefaultValue ? "' [default] valid for type '" : "' valid for type '";

							std::cout << currentPath << "." << attrib.Name << " value '" << value << isDefaultValue << type->Name << "'" << std::endl;
						}

						break;
					}
				}

				if (!valueMatches && attrib.Types.size())
				{
					std::cout << currentPath << "." << attrib.Name << " value '" << value << "' not valid for possible types: ";

					bool first = true;

					for (const SchemaType* type : attrib.Types)
					{
						if (!first)
						{
							std::cout << ", ";
						}

						std::cout << type->Name;

						first = false;
					}

					std::cout << std::endl;

					if (!valueMatches && !attrib.IsArray)
					{
						bool foundSeperator = false;

						for (size_t i = 0; !foundSeperator && i < value.size(); ++i)
						{
							foundSeperator = value[i] == ',';
						}

						if (foundSeperator)
						{
							std::cout << currentPath << "." << attrib.Name << " value '" << value << "' has array separator, but isn't marked as an array. did you forget to set it?" << std::endl;
						}
					}

					meetsSchema = false;
				}
				else if (attrib.VarianceParameterId.size())
				{
					VarianceParameters[attrib.VarianceParameterId] = value;
				}

				if (attrib.IsAlwaysDefault && value != attrib.Default)
				{
					std::cout << currentPath << "." << attrib.Name << "marked as always being default value '" << attrib.Default << "', but doesn't match: '" << value << "'" << std::endl;

					meetsSchema = false;
				}

				if (attrib.IsAlwaysNotDefault && value == attrib.Default)
				{
					std::cout << currentPath << "." << attrib.Name << "marked as always not being default value '" << attrib.Default << "', but matches" << std::endl;

					meetsSchema = false;
				}

				break;
			}

			if (!attributeAppears && !attrib.Optional)
			{
				std::cout << currentPath << "." << attrib.Name << " missing, but not marked as optional" << std::endl;

				meetsSchema = false;
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

			if (pivotNode.AppearanceNumber == 0)
			{
				std::vector<const SchemaAttribute*> varyingsAttributesToCheck;

				bool noVariance = ValidateNodeVariance(node, node.PivotNodeHeight, varyingsAttributesToCheck);

				if (noVariance && node.AttributesDependOnVarianceParam && varyingsAttributesToCheck.size())
				{
					for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
					{
						const SchemaAttribute* attrib = nullptr;

						for (size_t i = 0; !attrib && i < varyingsAttributesToCheck.size(); ++i)
						{
							if (varyingsAttributesToCheck[i]->Name == attribute->Name())
							{
								attrib = varyingsAttributesToCheck[i];
							}
						}

						if (!attrib || (!attrib->IgnoreVarianceIfEqualToParam.size() && !attrib->IgnoreVarianceIfEqual))
						{
							continue;
						}

						std::vector<std::string> values;

						if (attrib->IsArray)
						{
							const char* value = attribute->Value();
							size_t start = 0;
							size_t i = 0;

							for (i; value[i]; ++i)
							{
								if (value[i] == ',')
								{
									values.push_back(std::string(value + start, i - start));

									start = i + 1;
								}
							}

							if (value[0])
							{
								values.push_back(std::string(value + start, i - start));
							}
						}
						else
						{
							values.push_back(attribute->Value());
						}

						for (const std::string& value : values)
						{
							if (attrib->IgnoreVarianceIfEqual)
							{
								bool foundMatch = false;

								for (const std::string& ignoreValue : attrib->IgnoreVarianceIfEqualToValues)
								{
									bool valueMatches = value == ignoreValue;

									if (valueMatches)
									{
										foundMatch = true;

										break;
									}
								}

								if (foundMatch)
								{
									continue;
								}

								if (!attrib->IgnoreVarianceIfEqualToParam.size())
								{
									meetsSchema = false;

									std::cout << "node " << currentPath << " attribute '" << attribute->Name() << "' marked to ignore variance if equal to values ";

									for (const std::string& ignoreValue : attrib->IgnoreVarianceIfEqualToValues)
									{
										std::cout << "'" << ignoreValue << "', ";
									}

									std::cout << "'but doesn't match: '" << value << "'" << std::endl;

									continue;

								}
							}

							const auto varyParamEntry = VarianceParameters.find(attrib->IgnoreVarianceIfEqualToParam);

							if (varyParamEntry != VarianceParameters.end())
							{
								if (varyParamEntry->second != value)
								{
									meetsSchema = false;

									std::cout << "node " << currentPath << " attribute '" << attribute->Name() << "' marked to ignore variance if equal to parameter '" << attrib->IgnoreVarianceIfEqualToParam << "' '" << varyParamEntry->second << "', but doesn't match: '" << value << "'" << std::endl;
								}
							}
							else
							{
								meetsSchema = false;

								std::cout << "node " << currentPath << " attribute '" << attribute->Name() << "' marked to ignore variance if equal to parameter '" << attrib->IgnoreVarianceIfEqualToParam << "', but parameter hasn't been set" << std::endl;
							}
						}
					}
				}

				if (!noVariance)
				{
					std::cout << "node " << currentPath << " marked for NoVariance was found to vary: " << VarianceMessage << std::endl;
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
}