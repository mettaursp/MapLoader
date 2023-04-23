#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <unordered_map>
#include <string>

namespace Graphics
{
	struct DescriptorSet
	{
		struct DescriptorReference
		{
			VkDescriptorSetLayoutBinding& Binding;
			std::string& Name;
		};

		uint32_t Index = 0;
		size_t SetId = 0;
		std::string Name;
		std::vector<VkDescriptorSetLayoutBinding> LayoutBindings;
		std::vector<std::string> DescriptorNames;
		std::unordered_map<std::string, VkDescriptorSetLayoutBinding*> DescriptorMap;
		VkDescriptorSetLayout Layout = nullptr;

		std::vector<VkDescriptorSet> DescriptorSets = { nullptr };

		DescriptorReference FetchBinding(uint32_t index);
		VkDescriptorSet& Get(size_t frame = 0);
		const VkDescriptorSet& Get(size_t frame = 0) const;

		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, size_t frame = 0, uint32_t index = 0);
		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, size_t frame = 0, uint32_t index = 0);
		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, size_t frame = 0, uint32_t index = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, size_t frame = 0, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, size_t frame = 0, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, size_t frame = 0, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, size_t frame, uint32_t index, uint32_t count);
	};
}