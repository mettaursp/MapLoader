#include "AnimationLibrary.h"

#include <ArchiveParser/ParserUtils.h>
#include <Engine/VulkanGraphics/FileFormats/KfmParser.h>
#include <Engine/VulkanGraphics/FileFormats/PackageNodes.h>

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

		auto animationList = RigAnimations.find(name);

		if (animationList != RigAnimations.end())
		{
			loadedRig.AnimationList = &animationList->second;
		}

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
			animation.AnimationPackage = AssetLibrary.GetModels().FindModel(animation.Entry);

			if (animation.AnimationPackage != nullptr)
			{
				LoadRigAnimation(animation, animation.AnimationPackage);
			}

			animation.Id = documentAnimation.Id;
			animation.Name = documentAnimation.Name;

			if (animation.Name == "" && loadedRig.AnimationList)
			{
				auto entry = loadedRig.AnimationList->IdNames.find(animation.Id);

				if (entry != loadedRig.AnimationList->IdNames.end())
				{
					animation.Name = entry->second;
				}
			}

			loadedRig.AnimationMap[animation.Name] = &animation;
			loadedRig.AnimationEntryMap[animation.Entry] = &animation;
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

	ModelData* AnimationLibrary::FetchAnimation(RigAnimation* rigAnimation, RigAnimationData* rigAnimationData)
	{
		if (rigAnimation == nullptr) return nullptr;
		if (rigAnimation->Animation != nullptr) return rigAnimation->AnimationPackage;

		if (rigAnimationData == nullptr)
			rigAnimationData = FetchRigAnimations(rigAnimation->ParentEntry);

		LoadRigAnimation(*rigAnimation, AssetLibrary.GetModels().FetchModel(rigAnimation->Entry, false, FetchRig(rigAnimationData)));

		return rigAnimation->AnimationPackage;
	}

	void AnimationLibrary::LoadRigAnimation(RigAnimation& rigAnimation, ModelData* package)
	{
		rigAnimation.AnimationPackage = package;

		for (size_t i = 0; i < rigAnimation.AnimationPackage->Animations.size(); ++i)
		{
			Engine::Graphics::ModelPackageAnimation* animation = &rigAnimation.AnimationPackage->Animations[i];

			if (matchesCaseInsensitive(animation->Name, rigAnimation.Name))
			{
				rigAnimation.Animation = animation;
				rigAnimation.Duration = rigAnimation.Animation->Duration;

				for (size_t i = 0; i < animation->Nodes.size(); ++i)
				{
					const Engine::Graphics::ModelPackageAnimationNode& node = animation->Nodes[i];

					if (!node.IsSpline) continue;

					static const auto cacheKnots = [](const auto& spline)
					{
						size_t count = spline.ControlPoints.size();

						if (count == 0) return;

						if (KnotVectors.size() <= count)
							KnotVectors.resize(count + 1);

						auto& knotVector = KnotVectors[count];

						if (knotVector.size() > 0) return;

						knotVector.resize(count + SplineDegree - 1);

						for (int i = 0; i < (int)knotVector.size(); ++i)
							knotVector[i] = (float)std::max(0, std::min(i - (int)SplineDegree + 1, (int)count - (int)SplineDegree));
					};

					cacheKnots(node.TranslationSpline);
					cacheKnots(node.RotationSpline);
					cacheKnots(node.ScaleSpline);
				}

				return;
			}
		}
	}
}