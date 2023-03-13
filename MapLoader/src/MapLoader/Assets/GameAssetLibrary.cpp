#include "GameAssetLibrary.h"

namespace MapLoader
{
	GameAssetLibrary::GameAssetLibrary(
		const std::shared_ptr<Archive::ArchiveReader>& reader,
		const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) :
		Reader(reader),
		VulkanContext(vulkanContext),
		Textures(*this),
		Models(*this),
		Flats(*this),
		MapData(*this),
		Items(*this)
	{

	}
}