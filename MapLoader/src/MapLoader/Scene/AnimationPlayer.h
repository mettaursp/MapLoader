#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include <Engine/IdentifierHeap.h>
#include <ArchiveParser/MetadataMapper.h>

namespace Engine
{
	namespace Graphics
	{
		struct ModelPackageAnimationNode;
	}
}

namespace MapLoader
{
	struct RigAnimation;
	struct RigAnimationData;
	class GameAssetLibrary;
	class SkinnedModel;

	class AnimationPlayer
	{
	public:
		AnimationPlayer(const std::shared_ptr<GameAssetLibrary>& assetLibrary);

		void SetRig(SkinnedModel* skinnedModel);
		size_t PlayAnimation(RigAnimation* animation, float playbackSpeed = 1, bool looping = false, float time = 0);
		size_t PlayAnimation(const std::string& name, float playbackSpeed = 1, bool looping = false, float time = 0);
		size_t PlayAnimation(const Archive::Metadata::Entry* entry, float playbackSpeed = 1, bool looping = false, float time = 0);

		size_t GetAnimation(RigAnimation* animation);
		size_t GetAnimation(const std::string& name);
		size_t GetAnimation(const Archive::Metadata::Entry* entry);
		size_t GetAnimationCapacity() const { return PlayingAnimations.size(); }
		size_t GetPlayingAnimations() const { return PlayingAnimationIds.AllocatedIDs(); }

		void Update(float delta);

		bool IsPlaying(size_t animationId) const;
		bool IsPaused(size_t animationId) const;
		bool IsLooped(size_t animationId) const;
		float GetPlaybackSpeed(size_t animationId) const;
		float GetTime(size_t animationId) const;
		RigAnimation* GetAnimation(size_t animationId) const;

		void Stop(size_t animationId);
		void Pause(size_t animationId);
		void SetPlaybackSpeed(size_t animationId, float playbackSpeed);
		void SetTime(size_t animationId, float time);
		void SetLooping(size_t animationId, bool isLooping);
		void MarkStalePose();

	private:
		struct RigMapping
		{
			Engine::Graphics::ModelPackageAnimationNode* AnimationNode = nullptr;
			size_t NodeIndex = (size_t)-1;
		};

		struct PlayingAnimation
		{
			size_t Index = 0;
			RigAnimation* Animation = nullptr;
			float Time = 0;
			float PlaybackSpeed = 1;
			bool Looping = false;
			float BlendWeight = 1;
			std::vector<RigMapping> NodeMappings;
		};

		std::shared_ptr<GameAssetLibrary> AssetLibrary;
		SkinnedModel* Rig = nullptr;
		RigAnimationData* RigAnimations = nullptr;
		std::vector<PlayingAnimation> PlayingAnimations;
		std::unordered_set<size_t> NodesNeedReset;
		IDHeap PlayingAnimationIds;
		bool PoseIsStale = false;
		size_t LastRigVersion = (size_t)-1;

		void ComputeNodeMappings();
		void ComputeNodeMappings(PlayingAnimation& animation);
		void ComputePose();
		void SetAnimationTime(PlayingAnimation& animation, float time);
	};
}