#pragma once

#include <vulkan/vulkan_core.h>

#include "VulkanContext.h"

namespace Graphics
{
	class ShaderPipeline;

	class RenderPass
	{
	public:
		struct Subpass
		{
			uint32_t Index = 0;
			VkPipelineBindPoint BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			VkSubpassDescriptionFlags Flags = 0;
			std::vector<VkAttachmentReference> InputAttachments;
			std::vector<VkAttachmentReference> ColorAttachments;
			std::vector<VkAttachmentReference> ResolveAttachments;
			std::vector<uint32_t> PreserveAttachments;
			VkAttachmentReference DepthStencilAttachment;
			bool HasDepthStencilAttachment = false;
		};

		RenderPass(const std::shared_ptr<VulkanContext>& vulkanContext);
		~RenderPass();

		void Create();
		void ReleaseResources();

		void Configure(const std::vector<VkFormat> colorAttachments, VkFormat depthAttachment, bool clear = true, VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
		void Configure(const std::vector<VkFormat> colorAttachments, VkFormat depthAttachment, bool clear, bool clearDepth, VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
		void SetInputAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments);
		void SetColorAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments);
		void SetResolveAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments);
		void SetPreserveAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments);
		void SetDepthAttachments(const std::vector<size_t>& subpasses, uint32_t depthIndex);
		Subpass& AddSubpass(bool addDependency = true);
		Subpass& GetSubpass(size_t index);
		size_t GetSubpasses() const { return Subpasses.size(); }
		VkSubpassDependency& AddDependency();
		VkSubpassDependency& GetDependency(size_t index);
		size_t GetDependences() const { return SubpassDependencies.size(); }

		const VkRenderPass& GetRenderPass() const { return Pass; }
		const auto& GetAttachments() const { return Attachments; }
		const auto& GetVulkanContext() const { return VulkanContext; }

	private:
		std::shared_ptr<VulkanContext> VulkanContext;
		VkRenderPass Pass = nullptr;
		std::vector<Subpass> Subpasses;
		std::vector<VkSubpassDependency> SubpassDependencies;
		std::vector<VkAttachmentDescription> Attachments;

		void SetAttachments(std::vector<VkAttachmentReference>& attachments, const std::vector<uint32_t>& attachmentIndices, VkImageLayout layout);
		VkImageLayout GetDepthStencilLayout(VkFormat format) const;
	};
}