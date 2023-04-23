#include "DescriptorSetLibrary.h"

namespace Graphics
{
	DescriptorSetLibrary::DescriptorSetLibrary(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : VulkanContext(vulkanContext)
	{

	}

	DescriptorSet* DescriptorSetLibrary::CreateDescriptorSet(uint32_t index)
	{
		DescriptorSets.push_back(std::make_unique<DescriptorSet>());

		DescriptorSet* set = DescriptorSets.back().get();

		set->SetId = DescriptorSets.size() - 1;
		set->Index = index;

		return set;
	}

	DescriptorSet* DescriptorSetLibrary::FetchDescriptorSet(const std::string& name)
	{
		const auto& setIndex = NamedDescriptorSets.find(name);

		if (setIndex != NamedDescriptorSets.end())
			return setIndex->second;

		return nullptr;
	}

	DescriptorSet* DescriptorSetLibrary::FetchDescriptorSet(const std::string& name, uint32_t index)
	{
		const auto& setIndex = NamedDescriptorSets.find(name);

		if (setIndex != NamedDescriptorSets.end())
			return setIndex->second;

		DescriptorSet* set = CreateDescriptorSet(index);

		set->Name = name;
		NamedDescriptorSets[name] = set;

		return set;
	}

	DescriptorSet* DescriptorSetLibrary::FetchDescriptorSet(size_t setId)
	{
		if (setId >= DescriptorSets.size())
			return nullptr;

		return DescriptorSets[setId].get();
	}

	void DescriptorSetLibrary::CreateLayout(DescriptorSet* descriptorSet, VkDescriptorSetLayoutCreateFlags flags)
	{
		if (descriptorSet == nullptr) return;
		if (descriptorSet->Layout != nullptr) return;

		/*
		  VkDescriptorSetLayoutBindingFlagsCreateInfo bindingsInfo = {
			  isSet(supportFlags, DescriptorSupport::CORE_1_2) ? VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO :
																 VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT};
		  bindingsInfo.bindingCount  = uint32_t(m_bindingFlags.size());
		  bindingsInfo.pBindingFlags = m_bindingFlags.data();

		  createInfo.pNext =
			  m_bindingFlags.empty() && !(isAnySet(supportFlags, (DescriptorSupport::CORE_1_2 | DescriptorSupport::INDEXING_EXT))) ?
				  nullptr :
				  &bindingsInfo;
		*/

		VkDescriptorSetLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
		createInfo.bindingCount = (uint32_t)descriptorSet->LayoutBindings.size();
		createInfo.pBindings = descriptorSet->LayoutBindings.data();
		createInfo.flags = flags;

		VkResult result = vkCreateDescriptorSetLayout(VulkanContext->Device, &createInfo, nullptr, &descriptorSet->Layout);
		assert(result == VK_SUCCESS);
	}

	void DescriptorSetLibrary::CreateDescriptorPool(VkDescriptorPoolCreateFlags flags)
	{
		std::vector<VkDescriptorSetLayout> setLayouts;
		setLayouts.resize(DescriptorSets.size());

		for (size_t i = 0; i < setLayouts.size(); ++i)
			setLayouts[i] = DescriptorSets[i]->Layout;

		const uint32_t maxSets = 1;

		std::vector<VkDescriptorPoolSize> poolSizes;
		std::unordered_map<VkDescriptorType, size_t> indexMap;

		for (auto& descriptorSet : DescriptorSets)
		{
			for (auto& descriptor : descriptorSet->LayoutBindings)
			{
				auto mappedIndex = indexMap.find(descriptor.descriptorType);
				size_t index = poolSizes.size();

				if (mappedIndex != indexMap.end())
					index = mappedIndex->second;
				else
					indexMap[descriptor.descriptorType] = index;

				if (index == poolSizes.size())
					poolSizes.push_back({ descriptor.descriptorType });

				poolSizes[index].descriptorCount += descriptor.descriptorCount * maxSets;
			}
		}

		uint32_t setCount = 0;

		for (size_t i = 0; i < DescriptorSets.size(); ++i)
		{
			setCount += (uint32_t)DescriptorSets[i]->DescriptorSets.size();
		}

		VkDescriptorPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
		createInfo.maxSets = setCount;
		createInfo.poolSizeCount = (uint32_t)poolSizes.size();
		createInfo.pPoolSizes = poolSizes.data();
		createInfo.flags = flags;

		VkResult result = vkCreateDescriptorPool(VulkanContext->Device, &createInfo, nullptr, &DescriptorPool);
		assert(result == VK_SUCCESS);
	}

	void DescriptorSetLibrary::Allocate(DescriptorSet* descriptorSet)
	{
		const uint32_t maxSets = (uint32_t)descriptorSet->DescriptorSets.size();

		std::vector<VkDescriptorSetLayout> layouts(maxSets);

		for (uint32_t i = 0; i < maxSets; ++i)
			layouts[i] = descriptorSet->Layout;

		VkDescriptorSetAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
		allocateInfo.descriptorPool = DescriptorPool;
		allocateInfo.descriptorSetCount = maxSets;
		allocateInfo.pSetLayouts = layouts.data();

		VkResult result = vkAllocateDescriptorSets(VulkanContext->Device, &allocateInfo, descriptorSet->DescriptorSets.data());
		assert(result == VK_SUCCESS);
	}

	void DescriptorSetLibrary::CreateLayouts(VkDescriptorSetLayoutCreateFlags flags)
	{
		for (auto& descriptorSet : DescriptorSets)
			CreateLayout(descriptorSet.get(), flags);
	}

	void DescriptorSetLibrary::CreateDescriptorSets()
	{
		for (auto& descriptorSet : DescriptorSets)
			Allocate(descriptorSet.get());
	}

	void DescriptorSetLibrary::ReleaseResources()
	{
		vkDestroyDescriptorPool(VulkanContext->Device, DescriptorPool, nullptr);
		
		for (size_t i = 0; i < DescriptorSets.size(); ++i)
		{
			if (DescriptorSets[i]->Layout != nullptr)
				vkDestroyDescriptorSetLayout(VulkanContext->Device, DescriptorSets[i]->Layout, nullptr);
		}
	}
}