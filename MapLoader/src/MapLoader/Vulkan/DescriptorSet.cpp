#include "DescriptorSet.h"

#include <cassert>

namespace Graphics
{
	template <typename T>
	T& insert(std::vector<T>& vector, const T& value, size_t index)
	{
		if (index == vector.size())
		{
			vector.push_back(value);

			return vector.back();
		}

		vector.push_back(vector.back());

		for (size_t i = vector.size() - 2; i > index; --i)
		{
			vector[i] = vector[i - 1];
		}

		vector[index] = value;

		return vector[index];
	}

	DescriptorSet::DescriptorReference DescriptorSet::FetchBinding(uint32_t index)
	{
		size_t arrayIndex = 0;

		for (size_t i = 0; i < LayoutBindings.size(); ++i)
		{
			VkDescriptorSetLayoutBinding& descriptor = LayoutBindings[i];

			if (descriptor.binding == index)
				return { descriptor, DescriptorNames[i] };
			
			if (index > descriptor.binding)
				++arrayIndex;
			else
				break;
		}

		VkDescriptorSetLayoutBinding& descriptor = insert(LayoutBindings, { index }, arrayIndex);
		std::string& name = insert(DescriptorNames, {}, arrayIndex);

		return { descriptor, name };
	}

	VkWriteDescriptorSet DescriptorSet::MakeWriteArray(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, uint32_t index, uint32_t count)
	{
		VkWriteDescriptorSet writeSet = MakeWriteArray(binding, index, count);

		assert(
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT
		);

		writeSet.pImageInfo = pImageInfo;

		return writeSet;
	}

	VkWriteDescriptorSet DescriptorSet::MakeWrite(uint32_t binding, const VkDescriptorImageInfo* pImageInfo, uint32_t index)
	{
		return MakeWriteArray(binding, pImageInfo, index, 1);
	}

	VkWriteDescriptorSet DescriptorSet::MakeWriteArray(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, uint32_t index, uint32_t count)
	{
		VkWriteDescriptorSet writeSet = MakeWriteArray(binding, index, count);

		assert(
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
			writeSet.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
		);

		writeSet.pBufferInfo = pBufferInfo;

		return writeSet;
	}

	VkWriteDescriptorSet DescriptorSet::MakeWrite(uint32_t binding, const VkDescriptorBufferInfo* pBufferInfo, uint32_t index)
	{
		return MakeWriteArray(binding, pBufferInfo, index, 1);
	}

	VkWriteDescriptorSet DescriptorSet::MakeWriteArray(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, uint32_t index, uint32_t count)
	{
		VkWriteDescriptorSet writeSet = MakeWriteArray(binding, index, count);

		assert(writeSet.descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR);

		writeSet.pNext = pAccel;

		return writeSet;
	}

	VkWriteDescriptorSet DescriptorSet::MakeWrite(uint32_t binding, const VkWriteDescriptorSetAccelerationStructureKHR* pAccel, uint32_t index)
	{
		return MakeWriteArray(binding, pAccel, index, 1);
	}

	VkWriteDescriptorSet DescriptorSet::MakeWriteArray(uint32_t binding, uint32_t index, uint32_t count)
	{
		VkWriteDescriptorSet writeSet = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };
		
		for (size_t i = 0; i < LayoutBindings.size(); ++i)
		{
			auto& descriptor = LayoutBindings[i];

			if (descriptor.binding == binding)
			{
				writeSet.descriptorCount = count == 0 ? descriptor.descriptorCount : count;
				writeSet.descriptorType = descriptor.descriptorType;
				writeSet.dstBinding = binding;
				writeSet.dstSet = DescriptorSet;
				writeSet.dstArrayElement = index;

				return writeSet;
			}
		}

		throw "not found";
	}
}