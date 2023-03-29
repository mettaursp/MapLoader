#include "FrameBuffer.h"

#include "RenderPass.h"

namespace Graphics
{
	FrameBuffer::FrameBuffer(const std::shared_ptr<Graphics::RenderPass>& renderPass) : RenderPass(renderPass), VulkanContext(renderPass->GetVulkanContext())
	{
		Attachments.resize(RenderPass->GetAttachments().size());
	}

	FrameBuffer::~FrameBuffer()
	{
		ReleaseResources();
	}

	void FrameBuffer::ReleaseResources()
	{
		if (Buffer)
			vkDestroyFramebuffer(VulkanContext->Device, Buffer, nullptr);

		Buffer = nullptr;
	}

	void FrameBuffer::SetResolution(uint32_t width, uint32_t height, uint32_t layers, bool createAttachments)
	{
		Width = width;
		Height = height;
		Layers = layers;

		if (createAttachments)
		{

		}
	}

	void FrameBuffer::Create()
	{
		VkFramebufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
		createInfo.renderPass = RenderPass->GetRenderPass();
		createInfo.width = Width;
		createInfo.height = Height;
		createInfo.layers = Layers;
		createInfo.attachmentCount = (uint32_t)Attachments.size();
		createInfo.pAttachments = Attachments.data();

		vkCreateFramebuffer(VulkanContext->Device, &createInfo, nullptr, &Buffer);
	}
}