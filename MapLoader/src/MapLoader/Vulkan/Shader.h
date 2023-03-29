#pragma once

#include <vulkan/vulkan_core.h>
#include <string>
#include <filesystem>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <spirv_cross/spirv_cross.hpp>
#include "VulkanContext.h"

namespace fs = std::filesystem;

//namespace spirv_cross
//{
//	class Compiler;
//	struct Resource;
//
//	template <typename T, size_t N = 8>
//	class SmallVector;
//}

namespace Graphics
{
	class ShaderPipeline;
	class RenderPass;

	class Shader
	{
	public:
		Shader(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext, VkShaderStageFlagBits shaderStage = VK_SHADER_STAGE_ALL) : Stage(shaderStage), VulkanContext(vulkanContext) {}
		Shader(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext, const fs::path& shaderPath, VkShaderStageFlagBits shaderStage = VK_SHADER_STAGE_ALL);
		~Shader();

		void SetPath(const fs::path& shaderPath);
		void SetSourceDirectory(const fs::path& sourcePath);
		void SetBinaryDirectory(const fs::path& binaryPath);
		void SetShaderStage(VkShaderStageFlagBits stage);
		void LoadByteCode(bool forceReload = false);
		void LoadModule(bool forceReload = false);
		void LoadReflection(bool forceReload = false);
		void LoadDescriptors(ShaderPipeline& pipeline);
		void LoadOutputs(ShaderPipeline& pipeline, RenderPass& renderPass);
		void ReleaseResources();
		void ClearBuffers();

		const fs::path& GetPath() const { return ShaderPath; }
		const fs::path& GetSourceDirectory() const { return SourcePath; }
		fs::path GetSourcePath() const { return SourcePath / ShaderPath; }
		const fs::path& GetBinaryDirectory() const { return BinaryPath; }
		fs::path GetBinaryPath() const;
		VkShaderStageFlagBits GetShaderStage() const { return Stage; }
		VkShaderModule GetModule() const { return Module; }
		const std::string& GetEntryPoint() const { return EntryPoint; }

	private:
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		std::unique_ptr<spirv_cross::Compiler> Compiler;
		fs::path ShaderPath;
		fs::path SourcePath = "./shaders";
		fs::path BinaryPath = "./spv";
		VkShaderModule Module = nullptr;
		std::string Source;
		std::string ByteCode;
		std::string EntryPoint = "main";
		VkShaderStageFlagBits Stage = VK_SHADER_STAGE_ALL;

		void LoadDescriptor(ShaderPipeline& pipeline, const spirv_cross::Resource& resource, VkDescriptorType type);
		void LoadDescriptors(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources, VkDescriptorType type);
		void LoadInputs(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources);
		void LoadPushConstants(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources);
		void LoadShaderRecords(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources);
		void LoadOutputs(ShaderPipeline& pipeline, RenderPass& renderPass, const spirv_cross::SmallVector<spirv_cross::Resource>& resources);
	};
}