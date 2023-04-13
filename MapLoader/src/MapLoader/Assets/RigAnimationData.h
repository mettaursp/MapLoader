#pragma once

#include <vector>
#include <unordered_map>

#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Assets/ModelData.h>

namespace MapLoader
{
	struct RigAnimationData;

	struct RigAnimation
	{
		size_t Index = 0;
		unsigned int Id = 0;
		const Archive::Metadata::Entry* ParentEntry = nullptr;
		const Archive::Metadata::Entry* Entry = nullptr;
		ModelData* Animation = nullptr;
		std::string Name;
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
	};
}