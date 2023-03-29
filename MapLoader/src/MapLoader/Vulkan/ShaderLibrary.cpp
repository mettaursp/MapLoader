#include "ShaderLibrary.h"

#include <MapLoader/Assets/GameAssetLibrary.h>

namespace fs = std::filesystem;

namespace Graphics
{
	ShaderLibrary::ShaderLibrary(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : VulkanContext(vulkanContext)
	{

	}

	ShaderLibrary::~ShaderLibrary()
	{

	}

	Shader* ShaderLibrary::FetchShader(const std::string& path, VkShaderStageFlagBits stage)
	{
		auto shaderIndex = Shaders.find(path);

		if (shaderIndex != Shaders.end())
			return shaderIndex->second.get();

		auto result = Shaders.insert(std::make_pair(path, std::make_unique<Graphics::Shader>(VulkanContext, path, stage)));

		return result.first->second.get();
	}

	void ShaderLibrary::ReleaseResources()
	{
		Shaders.clear();
	}

	void ShaderLibrary::ReleaseModules()
	{
		for (auto& shader : Shaders)
		{
			shader.second->ReleaseResources();
		}
	}
}