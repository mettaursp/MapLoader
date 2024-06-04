#include "AnimationPlayer.h"

#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Assets/SkinnedModel.h>
#include <MapLoader/Assets/RigAnimationData.h>
#include <ArchiveParser/ParserUtils.h>
#include <Engine/VulkanGraphics/FileFormats/PackageNodes.h>

namespace MapLoader
{
	AnimationPlayer::AnimationPlayer(const std::shared_ptr<GameAssetLibrary>& assetLibrary) : AssetLibrary(assetLibrary)
	{

	}

	void AnimationPlayer::SetRig(SkinnedModel* skinnedModel)
	{
		Rig = skinnedModel;
		RigAnimations = Rig->GetRigAnimations();
	}

	size_t AnimationPlayer::PlayAnimation(RigAnimation* animation, float playbackSpeed, bool looping, float time)
	{
		size_t animationId = GetAnimation(animation);

		if (animationId == (size_t)-1)
		{
			animationId = PlayingAnimationIds.Allocate(PlayingAnimations, {});

			PlayingAnimations[animationId].Index = animationId;
			PlayingAnimations[animationId].Animation = animation;
		}

		PlayingAnimation& playingAnimation = PlayingAnimations[animationId];
		playingAnimation.Looping = looping;
		playingAnimation.PlaybackSpeed = playbackSpeed;

		SetAnimationTime(playingAnimation, time);

		return animationId;
	}

	size_t AnimationPlayer::PlayAnimation(const std::string& name, float playbackSpeed, bool looping, float time)
	{
		return PlayAnimation(RigAnimations->FetchAnimation(name), playbackSpeed, looping, time);
	}

	size_t AnimationPlayer::PlayAnimation(const Archive::Metadata::Entry* entry, float playbackSpeed, bool looping, float time)
	{
		return PlayAnimation(RigAnimations->FetchAnimation(entry), playbackSpeed, looping, time);
	}

	size_t AnimationPlayer::GetAnimation(RigAnimation* animation)
	{
		for (size_t i = 0; i < PlayingAnimations.size(); ++i)
		{
			if (PlayingAnimations[i].Animation == animation)
				return i;
		}

		return (size_t)-1;
	}

	size_t AnimationPlayer::GetAnimation(const std::string& name)
	{
		for (size_t i = 0; i < PlayingAnimations.size(); ++i)
		{
			RigAnimation* animation = PlayingAnimations[i].Animation;

			if (animation != nullptr  && matchesCaseInsensitive(animation->Name, name))
				return i;
		}

		return (size_t)-1;
	}

	size_t AnimationPlayer::GetAnimation(const Archive::Metadata::Entry* entry)
	{
		for (size_t i = 0; i < PlayingAnimations.size(); ++i)
		{
			RigAnimation* animation = PlayingAnimations[i].Animation;

			if (animation != nullptr && animation->Entry == entry)
				return i;
		}

		return (size_t)-1;
	}

	void AnimationPlayer::Update(float delta)
	{
		ComputeNodeMappings();

		for (size_t i = 0; i < PlayingAnimations.size() && delta != 0; ++i)
		{
			if (!IsPlaying(i)) continue;
			
			PlayingAnimation& animation = PlayingAnimations[i];

			if (animation.PlaybackSpeed == 0) continue;

			SetAnimationTime(animation, animation.Time + animation.PlaybackSpeed * delta);

			if (animation.Time == 0 && animation.PlaybackSpeed < 0 && !animation.Looping)
				Stop(i);

			if (animation.Animation != nullptr)
			{
				const auto& nodeMappings = animation.NodeMappings;

				for (size_t i = 0; i < nodeMappings.size(); ++i)
				{
					NodesNeedReset.erase(nodeMappings[i].NodeIndex);
				}
			}
		}

		if (!PoseIsStale) return;

		ComputePose();
	}

	bool AnimationPlayer::IsPlaying(size_t animationId) const
	{
		if (animationId >= PlayingAnimations.size()) return false;

		return PlayingAnimations[animationId].Animation != nullptr;
	}

	bool AnimationPlayer::IsPaused(size_t animationId) const
	{
		if (!IsPlaying(animationId)) return false;

		return PlayingAnimations[animationId].PlaybackSpeed == 0;
	}

	bool AnimationPlayer::IsLooped(size_t animationId) const
	{
		if (!IsPlaying(animationId)) return false;

		return PlayingAnimations[animationId].Looping;
	}

	float AnimationPlayer::GetPlaybackSpeed(size_t animationId) const
	{
		if (!IsPlaying(animationId)) return 0;

		return PlayingAnimations[animationId].PlaybackSpeed;
	}

	float AnimationPlayer::GetTime(size_t animationId) const
	{
		if (!IsPlaying(animationId)) return 0;

		return PlayingAnimations[animationId].Time;
	}

	RigAnimation* AnimationPlayer::GetAnimation(size_t animationId) const
	{
		if (!IsPlaying(animationId)) return nullptr;

		return PlayingAnimations[animationId].Animation;
	}

	void AnimationPlayer::Stop(size_t animationId)
	{
		if (!IsPlaying(animationId)) return;

		PlayingAnimationIds.Release(animationId);
		PlayingAnimations[animationId].Animation = nullptr;

		const auto& nodeMappings = PlayingAnimations[animationId].NodeMappings;

		for (size_t i = 0; i < nodeMappings.size(); ++i)
		{
			if (nodeMappings[i].NodeIndex >= Rig->GetRigNodes().size())
			{
				throw "out o bounds";
			}
			NodesNeedReset.insert(nodeMappings[i].NodeIndex);
		}

		PoseIsStale = true;
	}

	void AnimationPlayer::Pause(size_t animationId)
	{
		if (!IsPlaying(animationId)) return;

		PlayingAnimations[animationId].PlaybackSpeed = 0;
	}

	void AnimationPlayer::SetPlaybackSpeed(size_t animationId, float playbackSpeed)
	{
		if (!IsPlaying(animationId)) return;

		PlayingAnimations[animationId].PlaybackSpeed = playbackSpeed;
	}

	void AnimationPlayer::SetTime(size_t animationId, float time)
	{
		if (!IsPlaying(animationId)) return;

		SetAnimationTime(PlayingAnimations[animationId], time);
	}

	void AnimationPlayer::SetLooping(size_t animationId, bool isLooping)
	{
		if (!IsPlaying(animationId)) return;

		PlayingAnimations[animationId].Looping = isLooping;
	}

	void AnimationPlayer::MarkStalePose()
	{
		PoseIsStale = true;
	}

	void AnimationPlayer::ComputeNodeMappings()
	{
		size_t rigVersion = Rig->GetRigVersion();

		if (rigVersion == LastRigVersion) return;

		for (size_t i = 0; i < PlayingAnimations.size(); ++i)
		{
			ComputeNodeMappings(PlayingAnimations[i]);
		}
	}

	void AnimationPlayer::ComputeNodeMappings(PlayingAnimation& animation)
	{
		if (animation.Animation == nullptr) return;

		if (animation.NodeMappings.size() == 0)
		{
			animation.NodeMappings.resize(animation.Animation->Animation->Nodes.size());

			for (size_t i = 0; i < animation.NodeMappings.size(); ++i)
			{
				animation.NodeMappings[i].AnimationNode = &animation.Animation->Animation->Nodes[i];
			}
		}

		const auto& nodeIndices = Rig->GetNodeIndices();

		for (size_t i = 0; i < animation.NodeMappings.size(); ++i)
		{
			auto nodeIndex = nodeIndices.find(animation.NodeMappings[i].AnimationNode->NodeName);

			animation.NodeMappings[i].NodeIndex = nodeIndex != nodeIndices.end() ? nodeIndex->second : (size_t)-1;
		}
	}

	void AnimationPlayer::ComputePose()
	{
		const auto& rigNodes = Rig->GetRigNodes();

		for (size_t i = 0; i < PlayingAnimations.size(); ++i)
		{
			PlayingAnimation& animation = PlayingAnimations[i];

			if (animation.Animation == nullptr) continue;

			for (size_t j = 0; j < animation.NodeMappings.size(); ++j)
			{
				RigMapping& mapping = animation.NodeMappings[j];

				if (mapping.NodeIndex == (size_t)-1) continue;

				Matrix4F transform = animation.Animation->ComputeAnimationFrame(rigNodes[mapping.NodeIndex].BaseTransform, mapping.AnimationNode, animation.Time);

				Rig->SetRigNodeTransform(mapping.NodeIndex, transform);
			}
		}

		for (size_t resetNode : NodesNeedReset)
		{
			Rig->SetRigNodeTransform(resetNode, Rig->GetRigNodes()[resetNode].BaseTransform);
		}

		NodesNeedReset.clear();
	}

	void AnimationPlayer::SetAnimationTime(PlayingAnimation& animation, float time)
	{
		if (animation.Looping)
		{
			if (time < 0 || time > animation.Animation->Duration)
			{
				time += -animation.Animation->Duration * std::floor(time / animation.Animation->Duration);
			}
		}
		else
		{
			time = std::max(0.f, std::min(animation.Animation->Duration, time));

			if (time == animation.Animation->Duration)
			{
				Stop(animation.Index);
			}
		}

		PoseIsStale |= animation.Time != time;
		animation.Time = time;
	}
}