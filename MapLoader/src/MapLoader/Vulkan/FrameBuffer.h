#pragma once

#include <memory>
#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"

namespace Graphics
{
	class RenderPass;

	class FrameBuffer
	{
	public:
		FrameBuffer(const std::shared_ptr<RenderPass>& renderPass);
		~FrameBuffer();

		auto& GetAttachments() { return Attachments; }
		void SetResolution(uint32_t width, uint32_t height, uint32_t layers = 1, bool createAttachments = false);
		void Create();
		void ReleaseResources();
		const VkFramebuffer& GetFrameBuffer() const { return Buffer; }

	private:
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Layers = 0;
		std::shared_ptr<VulkanContext> VulkanContext;
		std::shared_ptr<RenderPass> RenderPass;
		std::vector<VkImageView> Attachments;
		VkFramebuffer Buffer;
	};
}