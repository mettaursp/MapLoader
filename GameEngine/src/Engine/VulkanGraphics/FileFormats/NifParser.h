#pragma once

#include <istream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "PackageNodes.h"

namespace Engine
{
	namespace Graphics
	{
		class MeshFormat;
		class MeshData;
	}
}

struct ImportedNiMesh
{
	std::shared_ptr<Engine::Graphics::MeshFormat> Format;
	std::shared_ptr<Engine::Graphics::MeshData> Mesh;
};

struct ParentNifNode
{
	std::string Name;
	Matrix4F Transform;
};

struct ParentNifTransforms
{
	std::vector<ParentNifNode> Nodes;
};

class NifParser
{
public:
	std::vector<ImportedNiMesh> ImportedMeshes;
	Engine::Graphics::ModelPackage* Package = nullptr;
	//ParentNifTransforms* ParentNodes = nullptr;
	std::string Name;

	void Parse(std::istream& stream);
	void Parse(std::string_view stream);

private:
	static std::unordered_set<std::string> SemanticsFound;

	void MarkBone(size_t index, std::unordered_map<size_t, size_t>& boneIndices);
};