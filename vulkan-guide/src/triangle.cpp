#include "triangle.h"
#include "utils.h"
#include <cstdint>


Triangle::Triangle(conststr& name, uint32 version) 
	: FrameAndCommandBuffers{name, version} {
	CreateSemaphores();
}


Triangle::~Triangle() {
	vkDestroySemaphore(logicalDevice, imageAvailable, nullptr);
	vkDestroySemaphore(logicalDevice, renderFinished, nullptr);
}


void Triangle::CreateSemaphores() {
	VkSemaphoreCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(logicalDevice, &info, nullptr, &imageAvailable) != VK_SUCCESS ||
		vkCreateSemaphore(logicalDevice, &info, nullptr, &renderFinished) != VK_SUCCESS) {
		ExitMsg("Failed to create semaphores");
	}
	else {
		Msg("Successfully created semaphores!");
	}
}


void Triangle::Draw() {
	uint32 imageIndex;
	vkAcquireNextImageKHR(logicalDevice, swapChain, UINT64_MAX, imageAvailable, VK_NULL_HANDLE, &imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore* preconditions{&imageAvailable};
	VkPipelineStageFlags requiredStage{VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = preconditions;
	submitInfo.pWaitDstStageMask = &requiredStage;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

	VkSemaphore* postconditions{&renderFinished};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = postconditions;

	if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
		ExitMsg("Failed to submit command buffer");
	}

	VkPresentInfoKHR presentationInfo{};
	presentationInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentationInfo.waitSemaphoreCount = 1;
	presentationInfo.pWaitSemaphores = postconditions;

	VkSwapchainKHR* swapchain{&swapChain};
	presentationInfo.swapchainCount = 1;
	presentationInfo.pSwapchains = swapchain;
	presentationInfo.pImageIndices = &imageIndex;
	presentationInfo.pResults = nullptr;

	vkQueuePresentKHR(presentationQueue, &presentationInfo);
	vkQueueWaitIdle(presentationQueue);
}


void Triangle::Execute() {
	while (!glfwWindowShouldClose(glfwWindow)) {
		glfwPollEvents();
		Draw();
	}

	vkDeviceWaitIdle(logicalDevice);
}