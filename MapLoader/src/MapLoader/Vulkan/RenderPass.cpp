#include "RenderPass.h"

#include "VulkanAttributes.h"

namespace Graphics
{
	RenderPass::RenderPass(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : VulkanContext(vulkanContext)
	{

	}

	RenderPass::~RenderPass()
	{
		ReleaseResources();
	}

	void RenderPass::Create()
	{
		std::vector<VkSubpassDescription> subpasses;
		subpasses.resize(Subpasses.size());
		
		for (size_t i = 0; i < subpasses.size(); ++i)
		{
			auto& subpass = Subpasses[i];
			auto& description = subpasses[i];

			description.pipelineBindPoint = subpass.BindPoint;
			description.inputAttachmentCount = (uint32_t)subpass.InputAttachments.size();

			if (subpass.InputAttachments.size() > 0)
				description.pInputAttachments = subpass.InputAttachments.data();

			description.colorAttachmentCount = (uint32_t)subpass.ColorAttachments.size();

			if (subpass.ColorAttachments.size() > 0)
				description.pColorAttachments = subpass.ColorAttachments.data();

			if (subpass.ResolveAttachments.size() > 0)
				description.pResolveAttachments = subpass.ResolveAttachments.data();

			description.preserveAttachmentCount = (uint32_t)subpass.PreserveAttachments.size();

			if (subpass.PreserveAttachments.size() > 0)
				description.pPreserveAttachments = subpass.PreserveAttachments.data();

			description.pDepthStencilAttachment = subpass.HasDepthStencilAttachment ? &subpass.DepthStencilAttachment : nullptr;
			description.flags = subpass.Flags;
		}

		VkRenderPassCreateInfo createInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
		createInfo.attachmentCount = (uint32_t)Attachments.size();
		createInfo.pAttachments = Attachments.data();
		createInfo.subpassCount = (uint32_t)subpasses.size();
		createInfo.pSubpasses = subpasses.data();
		createInfo.dependencyCount = (uint32_t)SubpassDependencies.size();
		createInfo.pDependencies = SubpassDependencies.data();

		VkResult result = vkCreateRenderPass(VulkanContext->Device, &createInfo, nullptr, &Pass);
	}

	void RenderPass::Configure(const std::vector<VkFormat> colorAttachments, VkFormat depthAttachment, bool clear, VkImageLayout initialLayout, VkImageLayout finalLayout)
	{
		Configure(colorAttachments, depthAttachment, clear, clear, initialLayout, finalLayout);
	}

	void RenderPass::Configure(const std::vector<VkFormat> colorAttachments, VkFormat depthAttachment, bool clear, bool clearDepth, VkImageLayout initialLayout, VkImageLayout finalLayout)
	{
		size_t attachmentCount = colorAttachments.size();

		if (depthAttachment != VK_FORMAT_UNDEFINED)
			++attachmentCount;

		Attachments.resize(attachmentCount);

		for (size_t i = 0; i < colorAttachments.size(); ++i)
		{
			auto& attachment = Attachments[i];
			attachment.format = colorAttachments[i];
			attachment.samples = VK_SAMPLE_COUNT_1_BIT;
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;

			if (!clear)
			{
				attachment.loadOp = initialLayout == VK_IMAGE_LAYOUT_UNDEFINED ? VK_ATTACHMENT_LOAD_OP_DONT_CARE : VK_ATTACHMENT_LOAD_OP_LOAD;
			}

			attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachment.initialLayout = initialLayout;
			attachment.finalLayout = finalLayout;
		}

		if (depthAttachment != VK_FORMAT_UNDEFINED)
		{
			auto& attachment = Attachments[colorAttachments.size()];
			attachment.format = depthAttachment;
			attachment.samples = VK_SAMPLE_COUNT_1_BIT;
			attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;

			if (!clearDepth)
			{
				attachment.loadOp = initialLayout == VK_IMAGE_LAYOUT_UNDEFINED ? VK_ATTACHMENT_LOAD_OP_DONT_CARE : VK_ATTACHMENT_LOAD_OP_LOAD;
			}

			VkImageLayout layout = GetDepthStencilLayout(depthAttachment);

			attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachment.initialLayout = layout;
			attachment.finalLayout = layout;
		}
	}

	void RenderPass::SetInputAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments)
	{
		for (size_t subpass : subpasses)
			SetAttachments(Subpasses[subpass].InputAttachments, attachments, VK_IMAGE_LAYOUT_UNDEFINED);
	}

	void RenderPass::SetColorAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments)
	{
		for (size_t subpass : subpasses)
			SetAttachments(Subpasses[subpass].ColorAttachments, attachments, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
	}

	void RenderPass::SetResolveAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments)
	{
		for (size_t subpass : subpasses)
			SetAttachments(Subpasses[subpass].ResolveAttachments, attachments, VK_IMAGE_LAYOUT_UNDEFINED);
	}

	void RenderPass::SetPreserveAttachments(const std::vector<size_t>& subpasses, const std::vector<uint32_t>& attachments)
	{
		for (size_t subpass : subpasses)
			Subpasses[subpass].PreserveAttachments = attachments;
	}

	void RenderPass::SetDepthAttachments(const std::vector<size_t>& subpasses, uint32_t depthIndex)
	{
		for (size_t subpass : subpasses)
		{

			Subpasses[subpass].DepthStencilAttachment.attachment = depthIndex;
			Subpasses[subpass].DepthStencilAttachment.layout = GetDepthStencilLayout(Attachments[depthIndex].format);
			Subpasses[subpass].HasDepthStencilAttachment = true;
		}
	}

	VkImageLayout RenderPass::GetDepthStencilLayout(VkFormat format) const
	{
		const auto& stats = GetDepthStencilStats(format);

		if (stats.DepthEnabled && !stats.StencilEnabled)
			return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

		if (stats.DepthEnabled && stats.StencilEnabled)
			return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		if (!stats.DepthEnabled && stats.StencilEnabled)
			return VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;

		return VK_IMAGE_LAYOUT_UNDEFINED;
	}

	void RenderPass::SetAttachments(std::vector<VkAttachmentReference>& attachments, const std::vector<uint32_t>& attachmentIndices, VkImageLayout layout)
	{
		attachments.resize(attachmentIndices.size());

		for (size_t i = 0; i < attachmentIndices.size(); ++i)
		{
			attachments[i].attachment = attachmentIndices[i];
			attachments[i].layout = layout;
		}
	}

	void RenderPass::ReleaseResources()
	{
		if (Pass)
			vkDestroyRenderPass(VulkanContext->Device, Pass, nullptr);

		Pass = nullptr;
	}

	RenderPass::Subpass& RenderPass::AddSubpass(bool addDependency)
	{
		Subpasses.push_back({ (uint32_t)Subpasses.size() });
		SubpassDependencies.push_back({ 0 });

		auto& subpass = Subpasses.back();

		auto& dependency = SubpassDependencies.back();
		dependency.srcSubpass = Subpasses.size() == 1 ? VK_SUBPASS_EXTERNAL : (uint32_t)Subpasses.size() - 2;
		dependency.dstSubpass = (uint32_t)Subpasses.size() - 1;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		subpass.Index = (uint32_t)Subpasses.size() - 1;

		return subpass;
	}

	RenderPass::Subpass& RenderPass::GetSubpass(size_t index)
	{
		return Subpasses[index];
	}

	VkSubpassDependency& RenderPass::AddDependency()
	{
		SubpassDependencies.push_back({ 0 });

		return SubpassDependencies.back();
	}

	VkSubpassDependency& RenderPass::GetDependency(size_t index)
	{
		return SubpassDependencies[index];
	}
}