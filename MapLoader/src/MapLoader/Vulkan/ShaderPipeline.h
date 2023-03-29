#pragma once

#include <MapLoader/Assets/ModelData.h>
#include <nvvk/resourceallocator_vk.hpp>
#include <Engine/Math/Color4.h>

#include "Shader.h"
#include "DescriptorSet.h"

namespace Graphics
{
	class DescriptorSetLibrary;
	class VulkanContext;
	class RenderPass;

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
		struct Attachment
		{
			VkPipelineColorBlendAttachmentState BlendState = { 0 };
		};

		struct RasterPipelineState
		{
			VkBool32 LogicOpEnable = false;
			VkLogicOp LogicOp = VK_LOGIC_OP_CLEAR;
			Color4 BlendConstants = Color4(0.0f, 0.0f, 0.0f, 0.0f);
		};

		ShaderPipeline(const std::shared_ptr<VulkanContext>& vulkanContext, const std::shared_ptr<DescriptorSetLibrary>& descriptorSetLibrary);
		~ShaderPipeline();

		void SetVertexFormat(const std::shared_ptr<Engine::Graphics::MeshFormat>& format);
		void AddStage(Shader* shader, const std::string& entryPoint = "");
		void LoadDescriptors();
		void CreatePipelineLayout();
		void CreateRasterPipeline();
		static void CreateRasterPipelines(RenderPass& renderPass, const std::vector<ShaderPipeline*>& pipelines);
		void CreateRTPipeline();

		void ReleaseResources();

		// State configuration

		// Shared
		void BindDescriptorSet(const std::string& name, uint32_t index);
		void BindDescriptorSet(DescriptorSet* descriptorSet);
		DescriptorSet& FetchDescriptorSet(uint32_t index);
		void SetVertexInputBinding(uint32_t index);
		VkPushConstantRange& FetchPushConstant();

		// Raster
		VkVertexInputAttributeDescription& FetchVertexInputAttribute(uint32_t index, const std::string& name);
		RasterPipelineState& GetRasterState() { return RasterState; }
		void SetRenderPass(const std::shared_ptr<RenderPass>& renderPass, uint32_t index = 0);
		void SetAttachmentAlphaBlend(size_t index, bool premultiplyAlpha = false);
		void SetAttachmentsAlphaBlend(bool premultiplyAlpha = false);
		VkPipelineColorBlendAttachmentState& GetAttachmentBlendState(size_t index);
		VkPipelineRasterizationStateCreateInfo& GetRasterizationStateCreateInfo();

		// Ray tracing
		void SetShaderRecordSize(uint32_t size);
		void SetMaxRayRecursionDepth(uint32_t depth);
		void AddRayGenGroup(uint32_t rayGenIndex);
		void AddHitGroup(RayHitGroup hitGroup);
		void AddMissGroup(uint32_t missIndex);

		// Getters

		// Shared
		const std::vector<DescriptorSet*>& GetDescriptorSets() const { return DescriptorSets; }
		VkShaderStageFlags GetPresentShaderStages() const { return PresentStages; }
		const std::shared_ptr<Engine::Graphics::MeshFormat>& GetVertexFormat() const { return VertexFormat; }
		const VkPipelineLayout& GetPipelineLayout() const { return PipelineLayout; }
		const VkPipeline& GetPipeline() const { return Pipeline; }
		PipelineType GetPipelineType() const { return Type; }

		// Ray tracing
		const auto& GetRayGenRegion() { return RayGenRegion; }
		const auto& GetRayMissRegion() { return RayMissRegion; }
		const auto& GetRayHitRegion() { return RayHitRegion; }

	private:
		struct RasterCreateInfo
		{
			VkPipelineInputAssemblyStateCreateInfo InputAssemblyState{ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
			VkPipelineRasterizationStateCreateInfo RasterizationState{ VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
			VkPipelineMultisampleStateCreateInfo   MultisampleState{ VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
			VkPipelineDepthStencilStateCreateInfo  DepthStencilState{ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
			VkPipelineViewportStateCreateInfo      ViewportState{ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
			bool HasDynamicState = true;
			VkPipelineDynamicStateCreateInfo       DynamicState{ VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
			VkPipelineColorBlendStateCreateInfo    ColorBlendState{ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
			VkPipelineVertexInputStateCreateInfo   VertexInputState{ VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

			std::vector<VkPipelineColorBlendAttachmentState> BlendStates;
			std::vector<VkPipelineShaderStageCreateInfo> Stages;
			std::vector<VkDynamicState> DynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

			VkGraphicsPipelineCreateInfo PipelineCreateInfo{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
		};

		// Shared
		struct ShaderEntry
		{
			Shader* Shader;
			std::string EntryPoint;
		};

		std::shared_ptr<Engine::Graphics::MeshFormat> VertexFormat;
		std::shared_ptr<VulkanContext> VulkanContext;
		std::shared_ptr<DescriptorSetLibrary> DescriptorSetLibrary;
		VkShaderStageFlags PresentStages = 0;
		VkPipelineLayout PipelineLayout = nullptr;
		VkPipeline Pipeline = nullptr;
		PipelineType Type = PipelineType::None;

		std::vector<ShaderEntry> Shaders;
		std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfo;
		std::vector<DescriptorSet*> DescriptorSets;
		std::vector<VkPushConstantRange> PushConstants;

		// Raster
		uint32_t SubpassIndex = 0;
		std::shared_ptr<RenderPass> PipelineRenderPass;
		std::unique_ptr<RasterCreateInfo> CreateInfo;
		std::vector<VkVertexInputBindingDescription> BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> AttributeDescriptions;
		std::vector<Attachment> Attachments;
		RasterPipelineState RasterState;

		// Ray tracing
		uint32_t ShaderRecordSize = 0;
		uint32_t MaxRayRecursionDepth = 2;
		std::vector<uint32_t> RayGenGroups;
		std::vector<RayHitGroup> RayHitGroups;
		std::vector<uint32_t> RayMissGroups;
		nvvk::Buffer ShaderBindingTableBuffer;
		VkStridedDeviceAddressRegionKHR RayGenRegion = { 0 };
		VkStridedDeviceAddressRegionKHR RayMissRegion = { 0 };
		VkStridedDeviceAddressRegionKHR RayHitRegion = { 0 };

		// Raster
		void ConfigureCreateInfo();
	};
}