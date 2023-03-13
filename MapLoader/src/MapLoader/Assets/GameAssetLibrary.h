#pragma once

#include <MapLoader/Vulkan/VulkanContext.h>
#include <ArchiveParser/ArchiveReader.h>
#include <MapLoader/Assets/ModelLibrary.h>
#include <MapLoader/Assets/TextureLibrary.h>
#include <MapLoader/Map/FlatLibrary.h>
#include <MapLoader/Items/ItemLibrary.h>
#include <MapLoader/Items/EmotionLibrary.h>

namespace MapLoader
{
	class GameAssetLibrary
	{
	public:
		GameAssetLibrary(
			const std::shared_ptr<Archive::ArchiveReader>& reader,
			const std::shared_ptr<Graphics::VulkanContext>& vulkanContext);

		const auto& GetReader() const { return Reader; }
		auto& GetTextures() { return Textures; }
		const auto& GetTextures() const { return Textures; }
		auto& GetModels() { return Models; }
		const auto& GetModels() const { return Models; }
		auto& GetFlats() { return Flats; }
		const auto& GetFlats() const { return Flats; }
		auto& GetMapData() { return MapData; }
		const auto& GetMapData() const { return MapData; }
		auto& GetItems() { return Items; }
		const auto& GetItems() const { return Items; }
		auto& GetEmotions() { return Emotions; }
		const auto& GetEmotions() const { return Emotions; }
		const auto& GetVulkanContext() const { return VulkanContext; }

	private:
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		std::shared_ptr<Archive::ArchiveReader> Reader;
		TextureLibrary Textures;
		ModelLibrary Models;
		FlatLibrary Flats;
		FlatLibrary MapData;
		ItemLibrary Items;
		EmotionLibrary Emotions;
	};
}