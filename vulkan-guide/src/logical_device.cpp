#include "logical_device.h"
#include "utils.h"


LogicalDevice::LogicalDevice(conststr& name, uint32 version)
	: PhysicalDevicesAndQueueFamilies(name, version), deviceFeatures{} {
	GetPhysicalDevice();
}


LogicalDevice::~LogicalDevice() {
	vkDestroyDevice(logicalDevice, nullptr);
}


void LogicalDevice::CreateLogicalDevice() {
	QueueFamilyIndices indices{FindQueueFamilies(physicalDevice)};

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


void LogicalDevice::SetDeviceFeatures(VkPhysicalDeviceFeatures features) {
	deviceFeatures = features;
}


void LogicalDevice::Execute() {
	CreateLogicalDevice();
}