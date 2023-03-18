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
		VkDescriptorSetLayout Layout;
		VkDescriptorSet DescriptorSet;

		DescriptorReference FetchBinding(uint32_t index);

		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, uint32_t index = 0);
		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, uint32_t index = 0);
		VkWriteDescriptorSet MakeWrite(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, uint32_t index = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, uint32_t index = 0, uint32_t count = 0);
		VkWriteDescriptorSet MakeWriteArray(uint32_t binding, uint32_t index, uint32_t count);
	};
}