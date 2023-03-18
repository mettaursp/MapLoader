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

	void ShaderPipeline::CreatePipeline()
	{
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

	void ShaderPipeline::ReleaseResources()
	{
		vkDestroyPipelineLayout(VulkanContext->Device, PipelineLayout, nullptr);
	}
}