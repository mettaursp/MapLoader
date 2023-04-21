#pragma once

#include <ArchiveParser/MetadataMapper.h>
#include <ArchiveParser/ArchiveReader.h>

#include "RigAnimationData.h"

namespace MapLoader
{
	class GameAssetLibrary;

	class AnimationLibrary
	{
	public:
		AnimationLibrary(GameAssetLibrary& assetLibrary);
		~AnimationLibrary();

		RigAnimationData* FetchRigAnimations(const Archive::Metadata::Entry* entry);
		ModelData* FetchRig(RigAnimationData* rigAnimationData);
		ModelData* FetchAnimation(RigAnimation* rigAnimation, RigAnimationData* rigAnimationData = nullptr);

	private:
		GameAssetLibrary& AssetLibrary;
		std::string KfmDocumentBuffer;

		std::unordered_map<const Archive::Metadata::Entry*, size_t> RigMap;
		std::vector<std::unique_ptr<RigAnimationData>> Rigs;

		bool FetchRigAnimations(const Archive::ArchivePath& file, RigAnimationData& loadedRig);
		void LoadRigAnimation(RigAnimation& rigAnimation, ModelData* package);
	};
}