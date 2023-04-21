#pragma once

#include <vector>
#include <unordered_map>

#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Assets/ModelData.h>

namespace Engine
{
	namespace Graphics
	{
		struct ModelPackageAnimationNode;
	}
}

namespace MapLoader
{
	struct RigAnimationData;

	const size_t SplineDegree = 3;
	extern std::vector<std::vector<float>> KnotVectors;

	struct RigAnimation
	{
		size_t Index = 0;
		unsigned int Id = 0;
		const Archive::Metadata::Entry* ParentEntry = nullptr;
		const Archive::Metadata::Entry* Entry = nullptr;
		ModelData* AnimationPackage = nullptr;
		Engine::Graphics::ModelPackageAnimation* Animation = nullptr;
		std::string Name;
		float Duration = 0;

		Matrix4F ComputeAnimationFrame(const Matrix4F& baseTransformation, Engine::Graphics::ModelPackageAnimationNode* node, float time);

	private:
		void ComputeSplineAnimationFrame(Vector3SF& translation, Quaternion& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time);
		void ComputeKeyframeAnimationFrame(Vector3SF& translation, Quaternion& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time);
		void ComputeKeyframeAnimationFrame(Vector3SF& translation, Vector3SF& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time);
		Matrix4F ComputeAnimationMatrix(const Vector3SF& translation, const Quaternion& rotation, float scale);
		Matrix4F ComputeAnimationMatrix(const Vector3SF& translation, const Vector3SF& rotation, float scale);
	};

	struct RigAnimationData
	{
		size_t Index = 0;
		const Archive::Metadata::Entry* Entry = nullptr;
		const Archive::Metadata::Entry* RigEntry = nullptr;
		ModelData* Rig = nullptr;
		std::string RootName;
		std::vector<RigAnimation> Animations;
		std::unordered_map<std::string, RigAnimation*> AnimationMap;
		std::unordered_map<const Archive::Metadata::Entry*, RigAnimation*> AnimationEntryMap;

		RigAnimation* FetchAnimation(const std::string& name);
		RigAnimation* FetchAnimation(const Archive::Metadata::Entry* entry);
	};
}