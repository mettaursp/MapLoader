#include "ItemLibrary.h"

#include <tinyxml2/tinyxml2.h>
#include <ArchiveParser/ParserUtils.h>
#include <MapLoader/Assets/GameAssetLibrary.h>

namespace MapLoader
{
	ItemLibrary::ItemLibrary(GameAssetLibrary& assetLibrary) : AssetLibrary(assetLibrary)
	{

	}

	const char* adjustPath(const char* path)
	{
		for (int i = 0; i < 3 && path[i]; ++i)
		{
			if (strncmp(path + i, "Data/", 5) == 0)
			{
				return path + i + 5;
			}
		}

		return path;
	}

	const ItemModel* ItemLibrary::LoadItem(const Item& item, Gender gender)
	{
		if (item.Id == 0) return nullptr;

		const std::unordered_map<int, ItemModel>& itemMap = gender == Gender::Male ? MaleItems : FemaleItems;
		const auto& itemIndex = itemMap.find(item.Id);

		if (itemIndex != itemMap.end())
		{
			return &itemIndex->second;
		}

		std::stringstream idString;
		idString << item.Id;

		std::string id = idString.str();
		char itemDir[6] = {
			((item.Id / 10000000) % 10) + '0',
			'/',
			((item.Id / 1000000) % 10) + '0',
			((item.Id / 100000) % 10) + '0',
			'/',
			0
		};

		Archive::ArchivePath file = AssetLibrary.GetReader()->GetPath("Xml/Item/" + std::string(itemDir) + (id + ".xml"));

		if (!file.Loaded())
		{
			std::cout << "failed to load item " << file.GetPath().string() << std::endl;
			return nullptr;
		}

		tinyxml2::XMLDocument document;

		file.Read(DocumentBuffer);
		document.Parse(DocumentBuffer.data(), DocumentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();
		tinyxml2::XMLElement* envElement = nullptr;

		SupportSettings feature;
		SupportSettings locale;

		ItemModel& model = (gender == Gender::Male ? MaleItems : FemaleItems)[item.Id];

		model.Id = item.Id;

		for (tinyxml2::XMLElement* currentEnvElement = rootElement->FirstChildElement(); currentEnvElement; currentEnvElement = currentEnvElement->NextSiblingElement())
		{
			if (!isNodeEnabled(currentEnvElement, &feature, &locale))
				continue;

			envElement = currentEnvElement;
		}

		for (tinyxml2::XMLElement* componentElement = envElement->FirstChildElement(); componentElement; componentElement = componentElement->NextSiblingElement())
		{
			const char* name = componentElement->Name();

			if (strcmp(name, "slots") == 0)
			{
				for (tinyxml2::XMLElement* slotElement = componentElement->FirstChildElement(); slotElement; slotElement = slotElement->NextSiblingElement())
				{
					model.Slots.push_back(ItemSlot{});

					ItemSlot& slot = model.Slots.back();

					slot.Name = readAttribute<const char*>(slotElement, "name", "");

					for (tinyxml2::XMLElement* attributeElement = slotElement->FirstChildElement(); attributeElement; attributeElement = attributeElement->NextSiblingElement())
					{
						const char* attributeName = attributeElement->Name();

						if (strcmp(attributeName, "asset") == 0)
						{
							Gender itemGender = (Gender)readAttribute<int>(attributeElement, "gender", 2);

							if (itemGender != Gender::Either && itemGender != gender) continue;

							slot.Assets.push_back(ItemData{});

							ItemData& asset = slot.Assets.back();

							const char* nifPath = readAttribute<const char*>(attributeElement, "name", "");

							if (strncmp(nifPath, "urn:", 4) == 0)
							{
								int lastColon = 3;

								for (int i = 4; nifPath[i]; ++i)
									if (nifPath[i] == ':')
										lastColon = i;

								if (nifPath[lastColon + 1])
								{
									asset.ModelEntry = Archive::Metadata::Entry::FindFirstEntryByTags(nifPath + lastColon + 1, "gamebryo-scenegraph");

									if (asset.ModelEntry)
									{
										asset.NifPath = "Resource" + asset.ModelEntry->RelativePath.string();
										asset.Model = AssetLibrary.GetModels().FetchModel(asset.ModelEntry, slot.Name == "HR");
									}
								}
							}
							else
							{
								asset.NifPath = nifPath + 5;
								asset.ModelEntry = Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(nifPath + 5 + 8, "gamebryo-scenegraph");
								asset.Model = AssetLibrary.GetModels().FetchModel(asset.ModelEntry, slot.Name == "HR");
							}

							asset.SelfNode = readAttribute<const char*>(attributeElement, "selfnode", "");
							asset.TargetNode = readAttribute<const char*>(attributeElement, "targetnode", "");
							asset.AttachNode = readAttribute<const char*>(attributeElement, "attachnode", "");
							asset.Replace = readAttribute<int>(attributeElement, "replace", 0) != 0;
							asset.EarFold = readAttribute<int>(attributeElement, "earfold", 0) != 0;
							asset.HasPonytail = readAttribute<int>(attributeElement, "pony", 0) != 0;
							asset.IsWeapon = readAttribute<int>(attributeElement, "weapon", 0) != 0;

							continue;
						}

						if (strcmp(attributeName, "scale") == 0)
						{
							slot.Scales.push_back(ItemSlotScale{});

							ItemSlotScale& scale = slot.Scales.back();

							scale.Value = readAttribute<Vector3SF>(attributeElement, "value", Vector3SF());
							scale.Min = readAttribute<float>(attributeElement, "min", 0);
							scale.Max = readAttribute<float>(attributeElement, "max", 0);
							scale.Reverse = readAttribute<int>(attributeElement, "reverse", 0) != 0;

							continue;
						}

						if (strcmp(attributeName, "decal") == 0)
						{
							slot.Decals.push_back(ItemDecal{});

							ItemDecal& decal = slot.Decals.back();

							decal.TexturePath = adjustPath(readAttribute<const char*>(attributeElement, "texture", ""));
							decal.ControlTexturePath = adjustPath(readAttribute<const char*>(attributeElement, "controlTexture", ""));

							for (tinyxml2::XMLElement* customElement = attributeElement->FirstChildElement(); customElement; customElement = customElement->NextSiblingElement())
							{
								if (strcmp(customElement->Name(), "custom") != 0)
									continue;

								decal.Transforms.push_back(ItemDecalTransform{});

								ItemDecalTransform& transform = decal.Transforms.back();

								auto& textureTransforms = AssetLibrary.GetModels().GetTextureTransforms();

								transform.Position = readAttribute<Vector3SF>(customElement, "position", {});
								transform.Rotation = readAttribute<Vector3SF>(customElement, "rotation", {});
								transform.TextureTransformId = (int)textureTransforms.size();

								textureTransforms.push_back(TextureTransform{});

								TextureTransform& textureTransform = textureTransforms.back();
								textureTransform.scale = { 1, 1 };
								textureTransform.translation = { -transform.Position.X, -transform.Position.Y };
								textureTransform.pivot = { 0.5f, 0.5f };
								textureTransform.rotation = -transform.Rotation.Z;// *PI / 180;
								textureTransform.mode = 1;

								if (slot.Scales.size() > 0)
								{
									textureTransform.scale = { 1 / slot.Scales[0].Value.X, 1 / slot.Scales[0].Value.X };
								}
							}

							VkSamplerCreateInfo sampler = MapLoader::TextureAsset::GetDefaultSampler();
							sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
							sampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
							sampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;

							decal.Texture = AssetLibrary.GetTextures().FetchTexture(decal.TexturePath, VK_FORMAT_R8G8B8A8_UNORM, sampler);
							decal.ControlTexture = AssetLibrary.GetTextures().FetchTexture(decal.ControlTexturePath, VK_FORMAT_R8G8B8A8_UNORM, sampler);

							continue;
						}

						attributeName += 0;
					}
				}

				continue;
			}

			if (strcmp(name, "cutting") == 0)
			{
				for (tinyxml2::XMLElement* meshElement = componentElement->FirstChildElement(); meshElement; meshElement = meshElement->NextSiblingElement())
				{
					if (strcmp(meshElement->Name(), "mesh") != 0)
						continue;

					if ((Gender)readAttribute<int>(meshElement, "gender", 2) != gender) continue;

					model.Cutting.push_back(readAttribute<const char*>(meshElement, "name", ""));
				}

				continue;
			}

			if (strcmp(name, "customize") == 0)
			{
				for (tinyxml2::XMLElement* slotElement = componentElement->FirstChildElement(); slotElement; slotElement = slotElement->NextSiblingElement())
				{
					const char* slotName = slotElement->Name();

					if (strcmp(slotName, "HR") == 0)
					{
						model.Customization.HairScale = readAttribute<int>(slotElement, "scale", 0) != 0;
						model.Customization.HairPonytail = readAttribute<int>(slotElement, "pony", 0) != 0;

						continue;
					}

					if (strcmp(slotName, "FD") == 0)
					{
						model.Customization.FaceDecorTranslation = readAttribute<int>(slotElement, "translation", 0) != 0;
						model.Customization.FaceDecorRotation = readAttribute<int>(slotElement, "rotation", 0) != 0;
						model.Customization.FaceDecorScale = readAttribute<int>(slotElement, "scale", 0) != 0;

						continue;
					}

					if (strcmp(slotName, "CP") == 0)
					{
						model.Customization.HatRotationX = readAttribute<int>(slotElement, "xrotation", 0) != 0;
						model.Customization.HatRotationY = readAttribute<int>(slotElement, "yrotation", 0) != 0;
						model.Customization.HatRotationZ = readAttribute<int>(slotElement, "zrotation", 0) != 0;
						model.Customization.HatScale = readAttribute<int>(slotElement, "scale", 0) != 0;
						model.Customization.HatAttach = readAttribute<int>(slotElement, "attach", 0) != 0;

						for (tinyxml2::XMLElement* transformElement = slotElement->FirstChildElement(); transformElement; transformElement = transformElement->NextSiblingElement())
						{
							if (strcmp(transformElement->Name(), "transform") != 0)
								continue;

							model.Customization.HasDefaultHatTransform = true;

							Vector3SF position = readAttribute<Vector3SF>(transformElement, "position", {});
							Vector3SF rotation = readAttribute<Vector3SF>(transformElement, "rotation", {});
							float scale = readAttribute<float>(transformElement, "scale", 1);

							model.Customization.DefaultHatTransform = MapLoader::getMatrix(position, rotation, scale, false);
						}

						continue;
					}
				}

				continue;
			}
		}

		AssetLibrary.GetTextures().FlushLoadingQueue();

		return &model;
	}
}