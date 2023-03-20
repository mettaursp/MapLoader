#pragma once

#include <MapLoader/Assets/ModelData.h>
#include <nvvk/resourceallocator_vk.hpp>

#include "Shader.h"
#include "DescriptorSet.h"

namespace Graphics
{
	class DescriptorSetLibrary;
	class VulkanContext;

	enum class PipelineType
	{
		None,
		Raster,
		Compute,
		RayTracing
	};

	struct RayHitGroup
	{
		uint32_t HitIndex = VK_SHADER_UNUSED_KHR;
		uint32_t AnyHitIndex = VK_SHADER_UNUSED_KHR;
		uint32_t IntersectIndex = VK_SHADER_UNUSED_KHR;
	};

	class ShaderPipeline
	{
	public:
		ShaderPipeline(const std::shared_ptr<VulkanContext>& vulkanContext, const std::shared_ptr<DescriptorSetLibrary>& descriptorSetLibrary);
		~ShaderPipeline();

		void SetVertexFormat(const std::shared_ptr<Engine::Graphics::MeshFormat>& format);
		void AddStage(const std::shared_ptr<Shader>& shader);
		void LoadDescriptors();
		void CreatePipelineLayout();
		void CreateRasterPipeline();
		void CreateRTPipeline();

		void AddRayGenGroup(uint32_t rayGenIndex);
		void AddHitGroup(RayHitGroup hitGroup);
		void AddMissGroup(uint32_t missIndex);

		void ReleaseResources();

		void BindDescriptorSet(const std::string& name, uint32_t index);
		void BindDescriptorSet(DescriptorSet* descriptorSet);
		DescriptorSet& FetchDescriptorSet(uint32_t index);

		void SetVertexInputBinding(uint32_t index);
		VkVertexInputAttributeDescription& FetchVertexInputAttribute(uint32_t index, const std::string& name);
		VkPushConstantRange& FetchPushConstant();
		void SetShaderRecordSize(uint32_t size);
		void SetMaxRayRecursionDepth(uint32_t depth);

		const std::vector<DescriptorSet*>& GetDescriptorSets() const { return DescriptorSets; }
		VkShaderStageFlags GetPresentShaderStages() const { return PresentStages; }
		const std::shared_ptr<Engine::Graphics::MeshFormat>& GetVertexFormat() const { return VertexFormat; }
		const VkPipelineLayout& GetPipelineLayout() const { return PipelineLayout; }
		const VkPipeline& GetPipeline() const { return Pipeline; }
		PipelineType GetPipelineType() const { return Type; }
		const auto& GetRayGenRegion() { return RayGenRegion; }
		const auto& GetRayMissRegion() { return RayMissRegion; }
		const auto& GetRayHitRegion() { return RayHitRegion; }

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
		VkPipeline Pipeline;
		PipelineType Type = PipelineType::None;
		uint32_t ShaderRecordSize = 0;
		uint32_t MaxRayRecursionDepth = 2;
		std::vector<uint32_t> RayGenGroups;
		std::vector<RayHitGroup> RayHitGroups;
		std::vector<uint32_t> RayMissGroups;
		nvvk::Buffer ShaderBindingTableBuffer;
		VkStridedDeviceAddressRegionKHR RayGenRegion;
		VkStridedDeviceAddressRegionKHR RayMissRegion;
		VkStridedDeviceAddressRegionKHR RayHitRegion;
	};
}