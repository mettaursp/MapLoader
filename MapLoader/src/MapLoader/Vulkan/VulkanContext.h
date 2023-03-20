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
		VkPhysicalDeviceRayTracingPipelinePropertiesKHR RTDeviceProperties{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR };

	private:
	};

	template <class Type>
	constexpr Type AlignUp(Type x, size_t a)
	{
		return Type((x + (Type(a) - 1)) & ~Type(a - 1));
	}
}