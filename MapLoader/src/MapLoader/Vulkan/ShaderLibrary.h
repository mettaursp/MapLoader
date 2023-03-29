#pragma once

#include <memory>
#include <vulkan/vulkan_core.h>

#include "Shader.h"

namespace Graphics
{
	class VulkanContext;

	class ShaderLibrary
	{
	public:
		ShaderLibrary(const std::shared_ptr<VulkanContext>& vulkanContext);
		~ShaderLibrary();

		Shader* FetchShader(const std::string& path, VkShaderStageFlagBits stage);
		void ReleaseResources();
		void ReleaseModules();

	private:
		std::shared_ptr<VulkanContext> VulkanContext;
		std::unordered_map<std::string, std::unique_ptr<Shader>> Shaders;
	};
}