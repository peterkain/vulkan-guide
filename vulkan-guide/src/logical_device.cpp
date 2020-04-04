#include "logical_device.h"
#include "utils.h"
#include <set>


LogicalDevice::LogicalDevice(conststr& name, uint32 version)
	: PhysicalDevicesAndQueueFamilies(name, version), deviceFeatures{} {
	GetPhysicalDevice(getPhysicalDevicePredicate);
}


LogicalDevice::~LogicalDevice() {
	vkDestroyDevice(logicalDevice, nullptr);
}


LogicalDevice::LogicalDevice(conststr& name, uint32 version, [[maybe_unused]] bool _override) 
	: PhysicalDevicesAndQueueFamilies(name, version), deviceFeatures{} {
}


void LogicalDevice::CreateLogicalDevice() {
	QueueFamilyIndices indices{FindQueueFamilies(physicalDevice, availableQueueFamilies)};

	VkDeviceQueueCreateInfo queueInfo{};
	queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueInfo.queueCount = 1;
	queueInfo.queueFamilyIndex = indices.graphicsFamily.value();

	float queuePriority{1.f};
	queueInfo.pQueuePriorities = &queuePriority;

	VkDeviceCreateInfo deviceInfo{};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pQueueCreateInfos = &queueInfo;
	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pEnabledFeatures = &deviceFeatures;

	// Not needed anymore, but if using older drivers it would be required:
	deviceInfo.enabledLayerCount = static_cast<uint32>(validationLayers.size());
	deviceInfo.ppEnabledLayerNames = validationLayers.data();

	if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
		ExitMsg("Failed to create a logical device!");
	}
	else {
		Msg("Logical device successfully created!");
		vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
	}
}


void LogicalDevice::CreateLogicalDevice(VkSurfaceKHR surface, VkQueue presentationQueue) {
	QueueFamilyIndices indices{FindQueueFamilies(physicalDevice, surface, availableQueueFamilies)};

	std::vector<VkDeviceQueueCreateInfo> queueInfos;
	std::set<uint32> allQueueFamilies{indices.graphicsFamily.value(), indices.presentationFamily.value()};

	float queuePriority{1.f};
	for (uint32 queueFamily : allQueueFamilies) {
		VkDeviceQueueCreateInfo queueInfo{};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = queueFamily;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &queuePriority;
		queueInfos.push_back(queueInfo);
	}

	VkDeviceCreateInfo deviceInfo{};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pQueueCreateInfos = queueInfos.data();
	deviceInfo.queueCreateInfoCount = static_cast<uint32>(queueInfos.size());
	deviceInfo.pEnabledFeatures = &deviceFeatures;
	deviceInfo.enabledExtensionCount = 0;

	// Not needed anymore, but if using older drivers it would be required:
	deviceInfo.enabledLayerCount = static_cast<uint32>(validationLayers.size());
	deviceInfo.ppEnabledLayerNames = validationLayers.data();

	if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
		ExitMsg("Failed to create a logical device!");
	}
	else {
		Msg("Logical device successfully created!");
		vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(logicalDevice, indices.presentationFamily.value(), 0, &presentationQueue);
	}
}


void LogicalDevice::SetDeviceFeatures(VkPhysicalDeviceFeatures features) {
	deviceFeatures = features;
}


void LogicalDevice::Execute() {
	CreateLogicalDevice();
}