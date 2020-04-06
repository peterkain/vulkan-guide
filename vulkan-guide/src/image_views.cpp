#include "image_views.h"
#include "utils.h"
#include <algorithm>


ImageViews::ImageViews(conststr& name, uint32 version) 
	: SwapChain{name, version} {
	CreateImageViews();
}


ImageViews::~ImageViews() {
	for (auto& e : swapChainImageViews) {
		vkDestroyImageView(logicalDevice, e, nullptr);
	}
}


void ImageViews::CreateImageViews() {
	swapChainImageViews.resize(swapChainImages.size());

	VkImageViewCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	info.format = swapChainFormat;
	info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	info.subresourceRange.baseMipLevel = 0;
	info.subresourceRange.levelCount = 1;
	info.subresourceRange.baseArrayLayer = 0;
	info.subresourceRange.layerCount = 1;

	for (std::size_t i{}; i != swapChainImages.size(); ++i) {
		info.image = swapChainImages[i];

		if (vkCreateImageView(logicalDevice, &info, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
			ExitMsg("Failed to create image view");
		}
	}

	Msg("Successfully created image views!");
}