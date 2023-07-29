#pragma once

#include "GameSchema.h"

namespace GameSchema
{
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
		bool ValidateNodeVariance(const SchemaNode& nodeSchema, size_t height, std::vector<const SchemaAttribute*>& varyingsAttributesToCheck);
		bool CompareNodeAttributes(const SchemaNode* nodeSchema, tinyxml2::XMLElement* node1, tinyxml2::XMLElement* node2, size_t stackIndex, std::vector<const SchemaAttribute*>& varyingsAttributesToCheck);
		void ReportVaryingDescendants(size_t stackIndex);
		std::string GetVaryingDescendantName(size_t stackIndex);

		std::vector<std::string> FeatureTagStack = { "" };
		std::vector<StackEntry> NodeStack;
		std::vector<tinyxml2::XMLElement*> SimilarNodes;
		std::vector<std::vector<NodeData>> SimilarNodeStacks;
		std::string VarianceMessage;
		std::unordered_map<const SchemaNode*, std::vector<std::unordered_map<std::string, AppearanceStats>>> ChildAppearances;
		std::unordered_map<std::string, std::string> VarianceParameters;
	};
}