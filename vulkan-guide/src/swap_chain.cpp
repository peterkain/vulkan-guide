#include "swap_chain.h"
#include "utils.h"
#include <algorithm>
#include <cstdint>
#include <cstring>


SwapChain::SwapChain(conststr& name, uint32 version)
	: Surface{name, version, true} {
	CreateWindow();
	CreateSurface();

	getPhysicalDevicePredicate = std::bind(&SwapChain::CheckPhysicalDevice, this, std::placeholders::_1);

	GetPhysicalDevice();
	CreateLogicalDevice(surface, presentationQueue, requiredExtensions);
	CreateSwapChain();
}


SwapChain::~SwapChain() {
	vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);
}


void SwapChain::GetAvailableExtensions(VkPhysicalDevice device) {
	uint32 count;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

	availableExtensions.resize(count);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &count, availableExtensions.data());
}


bool SwapChain::CheckPhysicalDevice(VkPhysicalDevice device) {
	GetAvailableQueueFamilies(device);
	QueueFamilyIndices indices{FindQueueFamilies(device, surface, availableQueueFamilies)};

	GetAvailableExtensions(device);
	
	for (const auto& extension : requiredExtensions) {
		if (!std::any_of(availableExtensions.begin(), availableExtensions.end(),
						 [&](VkExtensionProperties properties) {
							 return std::strcmp(properties.extensionName, extension) == 0;
						 })) {
			return false;
		}
	}

	swapChainDetails = CheckForSwapChainSupport(device);

	return indices.Complete() && !swapChainDetails.formats.empty() &&
		!swapChainDetails.presentModes.empty();
}


SwapChainSupportDetails SwapChain::CheckForSwapChainSupport(VkPhysicalDevice device) {
	SwapChainSupportDetails supportDetails;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &supportDetails.capabilities);

	uint32 formats;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formats, nullptr);

	if (formats) {
		supportDetails.formats.resize(formats);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formats, 
											 supportDetails.formats.data());
	}

	uint32 presentModes;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModes, nullptr);

	if (presentModes) {
		supportDetails.presentModes.resize(presentModes);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModes,
												  supportDetails.presentModes.data());
	}

	return supportDetails;
}


SwapChainConfig SwapChain::ConfigureSwapChain() {
	SwapChainConfig config;
	std::get<0>(config) = swapChainDetails.formats[0];
	std::get<1>(config) = VK_PRESENT_MODE_FIFO_KHR; // Guaranteed to be available

	for (const auto& format : swapChainDetails.formats) {
		if (format.format == VK_FORMAT_B8G8R8A8_SRGB &&
			format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			std::get<0>(config) = format;
		}
	}

	for (const auto& presentMode : swapChainDetails.presentModes) {
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			std::get<1>(config) = presentMode;
		}
	}

	if (swapChainDetails.capabilities.currentExtent.width != UINT32_MAX) {
		std::get<2>(config) = swapChainDetails.capabilities.currentExtent;
	}
	else {
		int w, h;
		glfwGetWindowSize(glfwWindow, &w, &h);

		uint32 width{static_cast<uint32>(w)};
		uint32 height{static_cast<uint32>(h)};

		CLAMP(width, swapChainDetails.capabilities.minImageExtent.width,
			  swapChainDetails.capabilities.maxImageExtent.width);
		CLAMP(height, swapChainDetails.capabilities.minImageExtent.height,
			  swapChainDetails.capabilities.maxImageExtent.height);

		std::get<2>(config).width = width;
		std::get<2>(config).height = height;
	}

	return config;
}


void SwapChain::CreateSwapChain(VkSwapchainKHR oldSwapchain) {
	SwapChainConfig config{ConfigureSwapChain()};

	uint32 imageCount{swapChainDetails.capabilities.minImageCount + 1};
	if (swapChainDetails.capabilities.maxImageCount > 0) {
		CLAMP(imageCount, swapChainDetails.capabilities.minImageCount,
			  swapChainDetails.capabilities.maxImageCount);
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = std::get<0>(config).format;
	createInfo.imageColorSpace = std::get<0>(config).colorSpace;
	createInfo.imageExtent = std::get<2>(config);
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices{FindQueueFamilies(physicalDevice, surface, availableQueueFamilies)};
	if (indices.graphicsFamily != indices.presentationFamily) {
		uint32 queueFamilyIndices[] {indices.graphicsFamily.value(), indices.presentationFamily.value()};
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	createInfo.preTransform = swapChainDetails.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = std::get<1>(config);
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = oldSwapchain;

	if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
		ExitMsg("Failed to create the swapchain");
	}
	else {
		Msg("Successfully created the swapchain!");
		vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());

		swapChainFormat = std::get<0>(config).format;
		swapChainExtent = std::get<2>(config);
	}
}