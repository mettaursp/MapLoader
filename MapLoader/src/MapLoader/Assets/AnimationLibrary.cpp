#include "AnimationLibrary.h"

#include <ArchiveParser/ParserUtils.h>
#include <Engine/VulkanGraphics/FileFormats/KfmParser.h>

#include "GameAssetLibrary.h"

namespace MapLoader
{
	AnimationLibrary::AnimationLibrary(GameAssetLibrary& assetLibrary) : AssetLibrary(assetLibrary)
	{

	}

	AnimationLibrary::~AnimationLibrary()
	{

	}

	RigAnimationData* AnimationLibrary::FetchRigAnimations(const Archive::Metadata::Entry* entry)
	{
		if (entry == nullptr) return nullptr;

		fs::path filepath = "Resource";
		filepath += entry->RelativePath;

		std::string name = lower(entry->Name);

		const auto& asset = RigMap.find(entry);

		if (asset != RigMap.end())
		{
			return Rigs[asset->second].get();
		}

		RigMap[entry] = Rigs.size();
		Rigs.push_back(std::move(std::make_unique<RigAnimationData>()));

		RigAnimationData& loadedRig = *Rigs.back();

		loadedRig.Entry = entry;
		loadedRig.Index = (uint32_t)Rigs.size() - 1;

		FetchRigAnimations(AssetLibrary.GetReader()->GetPath(filepath), loadedRig);

		return &loadedRig;
	}

	void SanitizePath(std::string& path)
	{
		for (size_t i = 0; i < path.size(); ++i)
		{
			if (path[i] == '\\')
				path[i] = '/';
		}
	}

	const Archive::Metadata::Entry* GetEntry(std::string& path, const Archive::Metadata::Entry* kfmEntry, const std::string& tagType)
	{
		SanitizePath(path);

		if (path[0] == '.')
		{
			std::string relpath = kfmEntry->RelativePath.string();
			size_t lastSlash = 0;

			for (lastSlash = relpath.size(); lastSlash > 0 && relpath[lastSlash - 1] != '/'; --lastSlash);

			path = relpath.substr(0, lastSlash) + path.substr(2, path.size() - 2);
		}

		return Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(path, tagType);
	}

	bool AnimationLibrary::FetchRigAnimations(const Archive::ArchivePath& file, RigAnimationData& loadedRig)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load model " << file.GetPath().string() << std::endl;
			return false;
		}

		KfmDocument document;
		KfmParser parser;
		parser.Document = &document;

		file.Read(KfmDocumentBuffer);
		parser.Parse(KfmDocumentBuffer);

		loadedRig.RigEntry = GetEntry(document.NifPath, loadedRig.Entry, "gamebryo-scenegraph");
		loadedRig.Rig = AssetLibrary.GetModels().FindModel(loadedRig.RigEntry);
		loadedRig.RootName = document.RootName;
		loadedRig.Animations.resize(document.Animations.size());

		for (size_t i = 0; i < document.Animations.size(); ++i)
		{
			RigAnimation& animation = loadedRig.Animations[i];
			KfmAnimation& documentAnimation = document.Animations[i];

			animation.Index = i;
			animation.ParentEntry = loadedRig.Entry;
			animation.Entry = GetEntry(documentAnimation.Path, loadedRig.Entry, "gamebryo-sequence-file");
			animation.Animation = AssetLibrary.GetModels().FindModel(animation.Entry);
			animation.Id = documentAnimation.Id;
			animation.Name = documentAnimation.Name;

			loadedRig.AnimationMap[animation.Name] = &animation;
		}

		return true;
	}

	ModelData* AnimationLibrary::FetchRig(RigAnimationData* rigAnimationData)
	{
		if (rigAnimationData == nullptr) return nullptr;
		if (rigAnimationData->Rig != nullptr) return rigAnimationData->Rig;

		rigAnimationData->Rig = AssetLibrary.GetModels().FetchModel(rigAnimationData->RigEntry);

		return rigAnimationData->Rig;
	}

	ModelData* AnimationLibrary::FetchAnimation(RigAnimationData* rigAnimationData, const std::string& name)
	{
		if (rigAnimationData == nullptr) return nullptr;

		auto animationIndex = rigAnimationData->AnimationMap.find(name);

		if (animationIndex == rigAnimationData->AnimationMap.end()) return nullptr;

		return FetchAnimation(animationIndex->second);
	}

	ModelData* AnimationLibrary::FetchAnimation(RigAnimation* rigAnimation, RigAnimationData* rigAnimationData)
	{
		if (rigAnimation == nullptr) return nullptr;
		if (rigAnimation->Animation != nullptr) return rigAnimation->Animation;

		if (rigAnimationData == nullptr)
			rigAnimationData = FetchRigAnimations(rigAnimation->ParentEntry);

		rigAnimation->Animation = AssetLibrary.GetModels().FetchModel(rigAnimation->Entry, false, FetchRig(rigAnimationData));

		return rigAnimation->Animation;
	}
}