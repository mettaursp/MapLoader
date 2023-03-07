#pragma once

#include <nvvk/resourceallocator_vk.hpp>
#include <nvvk/debug_util_vk.hpp>

namespace Graphics
{
	class VulkanContext
	{
	public:
		nvvk::ResourceAllocatorDma Allocator;
		nvvk::DebugUtil Debug;
		VkDevice Device;
		uint32_t GraphicsQueueIndex = VK_QUEUE_FAMILY_IGNORED;

	private:
	};
}