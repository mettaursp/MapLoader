#include "ShaderPipeline.h"

#include <iostream>

#include "VulkanContext.h"
#include "DescriptorSetLibrary.h"
#include "VulkanAttributes.h"
#include "RenderPass.h"

namespace Graphics
{
	ShaderPipeline::ShaderPipeline(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext, const std::shared_ptr<Graphics::DescriptorSetLibrary>& descriptorSetLibrary) : VulkanContext(vulkanContext), DescriptorSetLibrary(descriptorSetLibrary)
	{

	}

	ShaderPipeline::~ShaderPipeline()
	{
		ReleaseResources();
	}

	void ShaderPipeline::SetVertexFormat(const std::shared_ptr<Engine::Graphics::MeshFormat>& format)
	{
		VertexFormat = format;
	}

	void ShaderPipeline::AddStage(Shader* shader, const std::string& entryPoint)
	{
		Shaders.push_back({ shader, entryPoint });
	}

	void ShaderPipeline::LoadDescriptors()
	{
		for (auto& shader : Shaders)
		{
			PresentStages |= shader.Shader->GetShaderStage();

			shader.Shader->LoadByteCode();
			shader.Shader->LoadReflection();
			shader.Shader->LoadDescriptors(*this);
		}
	}

	void ShaderPipeline::CreatePipelineLayout()
	{
		if (PipelineLayout) return;

		std::vector<VkDescriptorSetLayout> layouts;
		layouts.resize(DescriptorSets.size());

		for (size_t i = 0; i < layouts.size(); ++i)
			layouts[i] = DescriptorSets[i]->Layout;

		VkPipelineLayoutCreateInfo createInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
		createInfo.setLayoutCount = (uint32_t)layouts.size();
		createInfo.pSetLayouts = layouts.data();
		createInfo.pushConstantRangeCount = (uint32_t)PushConstants.size();
		createInfo.pPushConstantRanges = PushConstants.data();

		VkResult result = vkCreatePipelineLayout(VulkanContext->Device, &createInfo, nullptr, &PipelineLayout);
		assert(result == VK_SUCCESS);
	}

	void ShaderPipeline::CreateRasterPipeline()
	{
		if (!PipelineLayout) return;
		if (Pipeline) return;

		Type = PipelineType::Raster;

		CreateInfo->PipelineCreateInfo.layout = PipelineLayout;

		auto& createInfo = CreateInfo->PipelineCreateInfo;

		VkResult result = vkCreateGraphicsPipelines(VulkanContext->Device, nullptr, 1, &CreateInfo->PipelineCreateInfo, nullptr, &Pipeline);
		assert(result == VK_SUCCESS);
	}

	void ShaderPipeline::CreateRasterPipelines(RenderPass& renderPass, const std::vector<ShaderPipeline*>& pipelines)
	{
		std::vector<VkGraphicsPipelineCreateInfo> createInfos;
		createInfos.resize(pipelines.size());
		std::vector<VkPipeline> pipelineHandles;
		pipelineHandles.resize(pipelines.size());

		for (size_t i = 0; i < pipelines.size(); ++i)
		{
			createInfos[i] = pipelines[i]->CreateInfo->PipelineCreateInfo;
		}

		VkResult result = vkCreateGraphicsPipelines(pipelines[0]->VulkanContext->Device, nullptr, (uint32_t)pipelines.size(), createInfos.data(), nullptr, pipelineHandles.data());
		assert(result == VK_SUCCESS);

		for (size_t i = 0; i < pipelines.size(); ++i)
		{
			pipelines[i]->Type = PipelineType::Raster;
			pipelines[i]->Pipeline = pipelineHandles[i];
		}
	}

	void ShaderPipeline::SetRenderPass(const std::shared_ptr<RenderPass>& renderPass, uint32_t index)
	{
		CreateInfo = std::make_unique<RasterCreateInfo>();

		CreateInfo->InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		CreateInfo->RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
		CreateInfo->RasterizationState.cullMode = VK_CULL_MODE_BACK_BIT;
		CreateInfo->RasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		CreateInfo->RasterizationState.lineWidth = 1;

		CreateInfo->MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		CreateInfo->PipelineCreateInfo.renderPass = renderPass->GetRenderPass();
		CreateInfo->PipelineCreateInfo.subpass = index;

		PipelineRenderPass = renderPass;
		SubpassIndex = index;

		ConfigureCreateInfo();
	}

	void ShaderPipeline::ConfigureCreateInfo()
	{
		RenderPass::Subpass& subpass = PipelineRenderPass->GetSubpass(SubpassIndex);

		for (size_t i = 0; i < Shaders.size(); ++i)
		{
			Shaders[i].Shader->LoadOutputs(*this, *PipelineRenderPass.get());
		}

		const auto& attachments = PipelineRenderPass->GetAttachments();

		if (subpass.HasDepthStencilAttachment)
		{
			const auto& depthStencilStats = GetDepthStencilStats(attachments[subpass.DepthStencilAttachment.attachment].format);

			if (depthStencilStats.DepthEnabled)
			{
				CreateInfo->DepthStencilState.depthTestEnable = true;
				CreateInfo->DepthStencilState.depthWriteEnable = true;
				CreateInfo->DepthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			}

			if (depthStencilStats.StencilEnabled)
			{
				CreateInfo->DepthStencilState.stencilTestEnable = true;
			}
		}

		CreateInfo->ViewportState.viewportCount = 1;
		CreateInfo->ViewportState.pViewports = nullptr;
		CreateInfo->ViewportState.scissorCount = 1;
		CreateInfo->ViewportState.pScissors = nullptr;

		if (CreateInfo->HasDynamicState)
		{
			CreateInfo->DynamicState.dynamicStateCount = (uint32_t)CreateInfo->DynamicStates.size();
			CreateInfo->DynamicState.pDynamicStates = CreateInfo->DynamicStates.data();
		}

		CreateInfo->BlendStates.resize(subpass.ColorAttachments.size());

		for (size_t i = 0; i < CreateInfo->BlendStates.size(); ++i)
		{
			const auto& attachment = attachments[subpass.ColorAttachments[i].attachment];
			auto& blendAttachment = CreateInfo->BlendStates[i];
			const FormatStats& format = GetFormatStats(attachment.format);

			blendAttachment.blendEnable = VK_FALSE;
			blendAttachment.colorWriteMask = format.Components;
		}

		CreateInfo->ColorBlendState.attachmentCount = (uint32_t)CreateInfo->BlendStates.size();
		CreateInfo->ColorBlendState.pAttachments = CreateInfo->BlendStates.data();
		CreateInfo->ColorBlendState.logicOpEnable = RasterState.LogicOpEnable;
		CreateInfo->ColorBlendState.logicOp = RasterState.LogicOp;

		for (size_t i = 0; i < 4; ++i)
			CreateInfo->ColorBlendState.blendConstants[i] = (&RasterState.BlendConstants.R)[i];

		CreateInfo->VertexInputState.vertexAttributeDescriptionCount = (uint32_t)AttributeDescriptions.size();
		CreateInfo->VertexInputState.vertexBindingDescriptionCount = (uint32_t)BindingDescriptions.size();
		CreateInfo->VertexInputState.pVertexAttributeDescriptions = AttributeDescriptions.data();
		CreateInfo->VertexInputState.pVertexBindingDescriptions = BindingDescriptions.data();

		CreateInfo->Stages.resize(Shaders.size(), { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO });

		for (size_t i = 0; i < CreateInfo->Stages.size(); ++i)
		{
			auto& shader = Shaders[i].Shader;

			shader->LoadModule();

			auto& stage = CreateInfo->Stages[i];

			stage.pName = Shaders[i].EntryPoint != "" ? Shaders[i].EntryPoint.c_str() : shader->GetEntryPoint().c_str();
			stage.module = shader->GetModule();
			stage.stage = shader->GetShaderStage();
		}

		VkGraphicsPipelineCreateInfo createInfo{ VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };

		CreateInfo->PipelineCreateInfo.stageCount = (uint32_t)CreateInfo->Stages.size();
		CreateInfo->PipelineCreateInfo.pStages = CreateInfo->Stages.data();

		CreateInfo->PipelineCreateInfo.pInputAssemblyState = &CreateInfo->InputAssemblyState;
		CreateInfo->PipelineCreateInfo.pRasterizationState = &CreateInfo->RasterizationState;
		CreateInfo->PipelineCreateInfo.pMultisampleState = &CreateInfo->MultisampleState;
		CreateInfo->PipelineCreateInfo.pDepthStencilState = &CreateInfo->DepthStencilState;
		CreateInfo->PipelineCreateInfo.pViewportState = &CreateInfo->ViewportState;

		if (CreateInfo->HasDynamicState)
			CreateInfo->PipelineCreateInfo.pDynamicState = &CreateInfo->DynamicState;

		CreateInfo->PipelineCreateInfo.pColorBlendState = &CreateInfo->ColorBlendState;
		CreateInfo->PipelineCreateInfo.pVertexInputState = &CreateInfo->VertexInputState;
		CreateInfo->PipelineCreateInfo.layout = PipelineLayout;
	}

	void ShaderPipeline::SetAttachmentAlphaBlend(size_t index, bool premultiplyAlpha)
	{
		VkPipelineColorBlendAttachmentState& blendState = CreateInfo->BlendStates[index];

		blendState.blendEnable = VK_TRUE;

		blendState.srcColorBlendFactor = premultiplyAlpha ? VK_BLEND_FACTOR_ONE : VK_BLEND_FACTOR_SRC_ALPHA;
		blendState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		blendState.colorBlendOp = VK_BLEND_OP_ADD;
		blendState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		blendState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		blendState.alphaBlendOp = VK_BLEND_OP_ADD;
	}

	void ShaderPipeline::SetAttachmentsAlphaBlend(bool premultiplyAlpha)
	{
		for (size_t i = 0; i < CreateInfo->BlendStates.size(); ++i)
			SetAttachmentAlphaBlend(i, premultiplyAlpha);
	}

	VkPipelineDepthStencilStateCreateInfo& ShaderPipeline::GetDepthStencilState()
	{
		return CreateInfo->DepthStencilState;
	}

	VkPipelineInputAssemblyStateCreateInfo& ShaderPipeline::GetInputAssemblyState()
	{
		return CreateInfo->InputAssemblyState;
	}

	VkPipelineColorBlendAttachmentState& ShaderPipeline::GetAttachmentBlendState(size_t index)
	{
		return CreateInfo->BlendStates[index];
	}

	VkPipelineRasterizationStateCreateInfo& ShaderPipeline::GetRasterizationState()
	{
		return CreateInfo->RasterizationState;
	}

	void ShaderPipeline::CreateRTPipeline()
	{
		Type = PipelineType::RayTracing;

		std::vector<VkPipelineShaderStageCreateInfo> stages;
		stages.resize(Shaders.size(), { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO });

		for (size_t i = 0; i < stages.size(); ++i)
		{
			auto& shader = Shaders[i].Shader;

			shader->LoadModule();

			auto& stage = stages[i];

			stage.pName = Shaders[i].EntryPoint != "" ? Shaders[i].EntryPoint.c_str() : shader->GetEntryPoint().c_str();
			stage.module = shader->GetModule();
			stage.stage = shader->GetShaderStage();
		}

		std::vector<VkRayTracingShaderGroupCreateInfoKHR> groups;

		{
			const VkRayTracingShaderGroupCreateInfoKHR templateGroup{
				VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
				nullptr,
				VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
				VK_SHADER_UNUSED_KHR,
				VK_SHADER_UNUSED_KHR,
				VK_SHADER_UNUSED_KHR,
				VK_SHADER_UNUSED_KHR
			};

			groups.resize(RayGenGroups.size() + RayHitGroups.size() + RayMissGroups.size(), templateGroup);
		}

		size_t index = 0;

		for (size_t i = 0; i < RayGenGroups.size(); ++i, ++index)
		{
			uint32_t rayGenGroup = RayGenGroups[i];
			auto& group = groups[index];

			group.generalShader = rayGenGroup;
		}

		for (size_t i = 0; i < RayMissGroups.size(); ++i, ++index)
		{
			uint32_t rayGenGroup = RayMissGroups[i];
			auto& group = groups[index];

			group.generalShader = rayGenGroup;
		}

		for (size_t i = 0; i < RayHitGroups.size(); ++i, ++index)
		{
			RayHitGroup& rayGenGroup = RayHitGroups[i];
			auto& group = groups[index];

			group.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR;
			group.closestHitShader = rayGenGroup.HitIndex;
			group.anyHitShader = rayGenGroup.AnyHitIndex;
			group.intersectionShader = rayGenGroup.IntersectIndex;
		}

		VkRayTracingPipelineCreateInfoKHR rayPipelineInfo{ VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR };
		rayPipelineInfo.stageCount = (uint32_t)stages.size();
		rayPipelineInfo.pStages = stages.data();
		rayPipelineInfo.groupCount = (uint32_t)groups.size();
		rayPipelineInfo.pGroups = groups.data();
		rayPipelineInfo.maxPipelineRayRecursionDepth = MaxRayRecursionDepth;
		rayPipelineInfo.layout = PipelineLayout;

		vkCreateRayTracingPipelinesKHR(VulkanContext->Device, {}, {}, 1, &rayPipelineInfo, nullptr, &Pipeline);

		if (VulkanContext->RTDeviceProperties.maxRayRecursionDepth <= 2)
		{
			throw std::runtime_error("Device fails to support ray recursion (m_rtProperties.maxRayRecursionDepth <= 2)");
		}

		for (size_t i = 0; i < Shaders.size(); ++i)
		{
			Shaders[i].Shader->ReleaseResources();
		}

		uint32_t rayGenCount = (uint32_t)RayGenGroups.size();
		uint32_t rayMissCount = (uint32_t)RayMissGroups.size();
		uint32_t rayHitCount = (uint32_t)RayHitGroups.size();
		uint32_t handleCount = rayGenCount + rayMissCount + rayHitCount;
		uint32_t handleSize = VulkanContext->RTDeviceProperties.shaderGroupHandleSize;
		uint32_t handleAlignment = VulkanContext->RTDeviceProperties.shaderGroupHandleAlignment;
		uint32_t baseAlignment = VulkanContext->RTDeviceProperties.shaderGroupBaseAlignment;

		uint32_t handleSizeAligned = AlignUp(handleSize, handleAlignment);

		RayGenRegion = {};
		RayMissRegion = {};
		RayHitRegion = {};

		RayGenRegion.stride = AlignUp(handleSizeAligned, baseAlignment);
		RayGenRegion.size = AlignUp(rayGenCount * RayGenRegion.stride, baseAlignment);

		RayMissRegion.stride = handleSizeAligned;
		RayMissRegion.size = AlignUp(rayMissCount * RayMissRegion.stride, baseAlignment);

		RayHitRegion.stride = AlignUp(handleSize + ShaderRecordSize, baseAlignment);
		RayHitRegion.size = AlignUp(rayHitCount * RayHitRegion.stride, baseAlignment);

		uint32_t dataSize = handleCount * handleSize;
		std::vector<uint8_t> handles(dataSize);

		VkResult result = vkGetRayTracingShaderGroupHandlesKHR(VulkanContext->Device, Pipeline, 0, handleCount, dataSize, handles.data());
		assert(result == VK_SUCCESS);

		VkBufferUsageFlags bufferUsage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR;
		VkMemoryAllocateFlags memoryUsage = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VkDeviceSize bindingTableSize = RayGenRegion.size + RayMissRegion.size + RayHitRegion.size;
		ShaderBindingTableBuffer = VulkanContext->Allocator.createBuffer(bindingTableSize, bufferUsage, memoryUsage);
		VulkanContext->Debug.setObjectName(ShaderBindingTableBuffer.buffer, "SBT");

		VkBufferDeviceAddressInfo info{ VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO, nullptr, ShaderBindingTableBuffer.buffer };
		VkDeviceAddress bindingTableAddress = vkGetBufferDeviceAddress(VulkanContext->Device, &info);

		RayGenRegion.deviceAddress = bindingTableAddress;
		RayMissRegion.deviceAddress = RayGenRegion.deviceAddress + RayGenRegion.size;
		RayHitRegion.deviceAddress = RayMissRegion.deviceAddress + RayMissRegion.size;

		uint8_t* bindingTableBuffer = reinterpret_cast<uint8_t*>(VulkanContext->Allocator.map(ShaderBindingTableBuffer));

		uint8_t* pData = bindingTableBuffer;
		uint32_t handleIndex = 0;

		for (uint32_t i = 0; i < rayGenCount; ++i, ++handleIndex)
		{
			std::memcpy(pData, handles.data() + handleIndex * handleSize, handleSize);
			pData += RayGenRegion.stride;
		}

		pData = bindingTableBuffer + RayGenRegion.size;
		for (uint32_t i = 0; i < rayMissCount; ++i, ++handleIndex)
		{
			std::memcpy(pData, handles.data() + handleIndex * handleSize, handleSize);
			pData += RayMissRegion.stride;
		}

		pData = bindingTableBuffer + RayGenRegion.size + RayMissRegion.size;
		for (uint32_t i = 0; i < rayHitCount; ++i, ++handleIndex)
		{
			std::memcpy(pData, handles.data() + handleIndex * handleSize, handleSize);
			pData += RayHitRegion.stride;
		}

		VulkanContext->Allocator.unmap(ShaderBindingTableBuffer);
		VulkanContext->Allocator.finalizeAndReleaseStaging();
	}

	void ShaderPipeline::AddRayGenGroup(uint32_t rayGenIndex)
	{
		RayGenGroups.push_back(rayGenIndex);
	}

	void ShaderPipeline::AddHitGroup(RayHitGroup hitGroup)
	{
		RayHitGroups.push_back(hitGroup);
	}

	void ShaderPipeline::AddMissGroup(uint32_t missIndex)
	{
		RayMissGroups.push_back(missIndex);
	}

	void ShaderPipeline::BindDescriptorSet(const std::string& name, uint32_t index)
	{
		BindDescriptorSet(DescriptorSetLibrary->FetchDescriptorSet(name, index));
	}

	void ShaderPipeline::BindDescriptorSet(DescriptorSet* descriptorSet)
	{
		if (descriptorSet == nullptr) return;

		const auto comparator = [](uint32_t index, const auto& value) { return value->Index > index; };

		auto iterator = std::upper_bound(DescriptorSets.begin(), DescriptorSets.end(), descriptorSet->Index, comparator);

		if (iterator != DescriptorSets.end())
		{
			std::cout << "attempt to bind descriptor set to already bound index: " << descriptorSet->Index << "\n";

			return;
		}

		DescriptorSets.insert(iterator, descriptorSet);
	}

	DescriptorSet& ShaderPipeline::FetchDescriptorSet(uint32_t index)
	{
		for (DescriptorSet* set : DescriptorSets)
		{
			if (set->Index == index)
				return *set;
		}

		const auto comparator = [](uint32_t index, const auto& value) { return value->Index > index; };

		auto iterator = std::upper_bound(DescriptorSets.begin(), DescriptorSets.end(), index, comparator);

		return **DescriptorSets.insert(iterator, DescriptorSetLibrary->CreateDescriptorSet(index));
	}

	void ShaderPipeline::SetVertexInputBinding(uint32_t index)
	{
		for (VkVertexInputBindingDescription& binding : BindingDescriptions)
		{
			if (binding.binding == index)
				return;
		}

		const auto comparator = [](uint32_t index, const auto& value) { return value.binding > index; };

		auto iterator = std::upper_bound(BindingDescriptions.begin(), BindingDescriptions.end(), index, comparator);

		BindingDescriptions.insert(iterator, { index, (uint32_t)VertexFormat->GetVertexSize(index)});
	}

	VkVertexInputAttributeDescription& ShaderPipeline::FetchVertexInputAttribute(uint32_t index, const std::string& name)
	{
		static VkVertexInputAttributeDescription errorResult = { (uint32_t)-1, (uint32_t)-1, VK_FORMAT_UNDEFINED, (uint32_t)-1 };

		const auto* attributeFormat = VertexFormat->GetAttribute(name);

		if (attributeFormat == nullptr) return errorResult;

		for (VkVertexInputAttributeDescription& attribute : AttributeDescriptions)
		{
			if (attribute.location == index)
				return attribute;
		}

		const auto comparator = [](uint32_t index, const auto& value) { return value.location > index; };

		auto iterator = std::upper_bound(AttributeDescriptions.begin(), AttributeDescriptions.end(), index, comparator);

		VkVertexInputAttributeDescription& attribute = *AttributeDescriptions.insert(iterator, { index, (uint32_t)attributeFormat->Binding });

		SetVertexInputBinding(attribute.binding);

		attribute.offset = (uint32_t)attributeFormat->Offset;
		attribute.format = GetVulkanFormat(attributeFormat->Type, attributeFormat->ElementCount);

		return attribute;
	}

	VkPushConstantRange& ShaderPipeline::FetchPushConstant()
	{
		if (PushConstants.size() == 0)
			PushConstants.push_back({});

		return PushConstants.back();
	}

	void ShaderPipeline::SetShaderRecordSize(uint32_t size)
	{
		ShaderRecordSize = std::max(ShaderRecordSize, size);
	}

	void ShaderPipeline::SetMaxRayRecursionDepth(uint32_t depth)
	{
		MaxRayRecursionDepth = depth;
	}

	void ShaderPipeline::ReleaseResources()
	{
		Type = PipelineType::None;
		ShaderRecordSize = 0;

		if (PipelineLayout)
			vkDestroyPipelineLayout(VulkanContext->Device, PipelineLayout, nullptr);

		PipelineLayout = nullptr;

		if (ShaderBindingTableBuffer.buffer)
			VulkanContext->Allocator.destroy(ShaderBindingTableBuffer);

		if (Pipeline)
			vkDestroyPipeline(VulkanContext->Device, Pipeline, nullptr);

		Pipeline = nullptr;

		ShaderBindingTableBuffer = {};
	}
}