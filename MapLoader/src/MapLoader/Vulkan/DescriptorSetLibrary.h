#pragma once

#include <memory>

#include "DescriptorSet.h"
#include "VulkanContext.h"

namespace Graphics
{
	class DescriptorSetLibrary
	{
	public:
		DescriptorSetLibrary(const std::shared_ptr<VulkanContext>& vulkanContext);

		DescriptorSet* CreateDescriptorSet(uint32_t index);
		DescriptorSet* FetchDescriptorSet(const std::string& name, uint32_t index);
		DescriptorSet* FetchDescriptorSet(const std::string& name);
		DescriptorSet* FetchDescriptorSet(size_t setId);

		void CreateLayout(DescriptorSet* descriptorSet, VkDescriptorSetLayoutCreateFlags flags = 0);
		void CreateDescriptorPool(VkDescriptorPoolCreateFlags flags = 0);
		void Allocate(DescriptorSet* descriptorSet);
		void CreateLayouts(VkDescriptorSetLayoutCreateFlags flags = 0);
		void CreateDescriptorSets();

		void ReleaseResources();

	private:
		VkDescriptorPool DescriptorPool;
		std::shared_ptr<VulkanContext> VulkanContext;
		std::vector<std::unique_ptr<DescriptorSet>> DescriptorSets;
		std::unordered_map<std::string, DescriptorSet*> NamedDescriptorSets;
	};
}