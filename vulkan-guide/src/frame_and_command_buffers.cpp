#include "frame_and_command_buffers.h"
#include "utils.h"
#include "queue_family_indices.h"


FrameAndCommandBuffers::FrameAndCommandBuffers(conststr& name, uint32 version) 
	: GraphicsPipeline{name, version} {
	CreateFrameBuffers();
	CreateCommandPool();
	CreateCommandBuffers();
	RecordCommandBuffers();
}


FrameAndCommandBuffers::~FrameAndCommandBuffers() {
	for (auto& e : framebuffers) {
		vkDestroyFramebuffer(logicalDevice, e, nullptr);
	}
	vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
}


void FrameAndCommandBuffers::CreateFrameBuffers() {
	framebuffers.resize(swapChainImageViews.size());

	for (std::size_t i{}; i != swapChainImageViews.size(); ++i) {
		VkImageView attachments[] = {swapChainImageViews[i]};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(logicalDevice, &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
			ExitMsg("Failed to create framebuffer");
		}
	}

	Msg("Successfully created framebuffers!");
}


void FrameAndCommandBuffers::CreateCommandPool() {
	QueueFamilyIndices indices{FindQueueFamilies(physicalDevice, surface, availableQueueFamilies)};
	VkCommandPoolCreateInfo commandPoolInfo{};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.queueFamilyIndex = indices.graphicsFamily.value();
	commandPoolInfo.flags = 0;

	if (vkCreateCommandPool(logicalDevice, &commandPoolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		ExitMsg("Failed to create command pool");
	}
	else {
		Msg("Successfully created the command pool!");
	}
}


void FrameAndCommandBuffers::CreateCommandBuffers() {
	commandBuffers.resize(framebuffers.size());

	VkCommandBufferAllocateInfo allocationInfo{};
	allocationInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocationInfo.commandPool = commandPool;
	allocationInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocationInfo.commandBufferCount = static_cast<uint32>(commandBuffers.size());

	if (vkAllocateCommandBuffers(logicalDevice, &allocationInfo, commandBuffers.data()) != VK_SUCCESS) {
		ExitMsg("Failed to allocate command buffers");
	}
	else {
		Msg("Successfully allocated command buffers!");
	}
}


void FrameAndCommandBuffers::RecordCommandBuffers() {
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	for (std::size_t i{}; i != commandBuffers.size(); ++i) {
		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			ExitMsg("Failed to record command buffer");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = framebuffers[i];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = swapChainExtent;

		VkClearValue clearColor = {0.f, 0.f, 0.f, 1.f};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);
		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			ExitMsg("Failed to record command buffer");
		}
	}

	Msg("Successfully recorded command buffers!");
}