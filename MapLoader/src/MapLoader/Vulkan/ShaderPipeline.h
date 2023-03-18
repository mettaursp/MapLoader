#pragma once

#include <MapLoader/Assets/ModelData.h>

#include "Shader.h"
#include "DescriptorSet.h"

namespace Graphics
{
	class DescriptorSetLibrary;
	class VulkanContext;

	class ShaderPipeline
	{
	public:
		ShaderPipeline(const std::shared_ptr<VulkanContext>& vulkanContext, const std::shared_ptr<DescriptorSetLibrary>& descriptorSetLibrary);

		void SetVertexFormat(const std::shared_ptr<Engine::Graphics::MeshFormat>& format);
		void AddStage(const std::shared_ptr<Shader>& shader);
		void CreatePipeline();
		void LoadDescriptors();

		void ReleaseResources();

		void BindDescriptorSet(const std::string& name, uint32_t index);
		void BindDescriptorSet(DescriptorSet* descriptorSet);
		DescriptorSet& FetchDescriptorSet(uint32_t index);

		void SetVertexInputBinding(uint32_t index);
		VkVertexInputAttributeDescription& FetchVertexInputAttribute(uint32_t index, const std::string& name);
		VkPushConstantRange& FetchPushConstant();

		const std::vector<DescriptorSet*>& GetDescriptorSets() const { return DescriptorSets; }
		VkShaderStageFlags GetPresentShaderStages() const { return PresentStages; }
		const std::shared_ptr<Engine::Graphics::MeshFormat>& GetVertexFormat() const { return VertexFormat; }
		const VkPipelineLayout& GetPipelineLayout() const { return PipelineLayout; }

	private:
		std::shared_ptr<Engine::Graphics::MeshFormat> VertexFormat;
		std::shared_ptr<VulkanContext> VulkanContext;
		std::shared_ptr<DescriptorSetLibrary> DescriptorSetLibrary;
		VkShaderStageFlags PresentStages = 0;
		std::vector<std::shared_ptr<Shader>> Shaders;
		std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfo;
		std::vector<DescriptorSet*> DescriptorSets;
		std::vector<VkVertexInputBindingDescription> BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> AttributeDescriptions;
		std::vector<VkPushConstantRange> PushConstants;
		VkPipelineLayout PipelineLayout;
	};
}