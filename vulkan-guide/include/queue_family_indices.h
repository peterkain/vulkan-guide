#pragma once
#include <optional>


struct QueueFamilyIndices
{
	// For physical_devices_and_queue_families
	std::optional<uint32> graphicsFamily;

	// For surface
	std::optional<uint32> presentationFamily;

	bool Complete() {
		return graphicsFamily.has_value() && presentationFamily.has_value();
	}
};


[[maybe_unused]]
static QueueFamilyIndices FindQueueFamilies(const std::vector<VkQueueFamilyProperties>& availableQueueFamilies) {
	QueueFamilyIndices indices;

	for (uint32 i{0}; i != availableQueueFamilies.size(); ++i) {
		if (availableQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.Complete()) {
			break;
		}
	}

	return indices;
}


[[maybe_unused]]
static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface,
											const std::vector<VkQueueFamilyProperties>& availableQueueFamilies) {
	QueueFamilyIndices indices;

	for (uint32 i{0}; i != availableQueueFamilies.size(); ++i) {
		if (availableQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		VkBool32 supportForPresentation;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supportForPresentation);

		if (supportForPresentation) {
			indices.presentationFamily = i;
		}

		if (indices.Complete()) {
			break;
		}
	}

	return indices;
}