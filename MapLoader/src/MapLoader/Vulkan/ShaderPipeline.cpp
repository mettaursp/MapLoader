#include "ShaderPipeline.h"

#include <iostream>

#include "VulkanContext.h"
#include "DescriptorSetLibrary.h"
#include "VulkanAttributes.h"

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

	void ShaderPipeline::AddStage(const std::shared_ptr<Shader>& shader)
	{
		Shaders.push_back(shader);
	}

	void ShaderPipeline::LoadDescriptors()
	{
		for (auto& shader : Shaders)
		{
			PresentStages |= shader->GetShaderStage();

			shader->LoadByteCode();
			shader->LoadReflection();
			shader->LoadDescriptors(*this);
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

		Type = PipelineType::RayTracing;
	}

	void ShaderPipeline::CreateRTPipeline()
	{
		std::vector<VkPipelineShaderStageCreateInfo> stages;
		stages.resize(Shaders.size(), { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO });

		for (size_t i = 0; i < stages.size(); ++i)
		{
			Shaders[i]->LoadModule();

			auto& stage = stages[i];

			stage.pName = Shaders[i]->GetEntryPoint().c_str();
			stage.module = Shaders[i]->GetModule();
			stage.stage = Shaders[i]->GetShaderStage();
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
			Shaders[i]->ReleaseResources();
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
		for (uint32_t i = 0; i < rayGenCount; ++i, ++handleIndex)
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

		ShaderBindingTableBuffer = {};
	}
}