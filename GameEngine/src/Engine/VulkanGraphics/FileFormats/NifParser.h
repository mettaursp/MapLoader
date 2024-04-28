#pragma once

#include <istream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "ModelParser.h"
#include "PackageNodes.h"

class NifParser : public ModelParser
{
public:
	std::string Name;

	void Parse(std::string_view stream);

private:
	static std::unordered_set<std::string> SemanticsFound;

	void MarkBone(size_t index, std::unordered_map<size_t, size_t>& boneIndices);
};