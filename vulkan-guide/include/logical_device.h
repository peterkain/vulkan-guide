#pragma once
#include "physical_devices_and_queue_families.h"


class LogicalDevice : public PhysicalDevicesAndQueueFamilies
{
public:
	LogicalDevice(conststr& name, uint32 version);
	virtual ~LogicalDevice();

	void Execute();

protected:
	LogicalDevice(conststr& name, uint32 version, [[maybe_unused]] bool _override);

	void CreateLogicalDevice();
	void CreateLogicalDevice(VkSurfaceKHR surface, VkQueue& presentationQueue,
							 const std::vector<const char*>& requiredExtensions = {});
	void SetDeviceFeatures(VkPhysicalDeviceFeatures features);

	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkPhysicalDeviceFeatures deviceFeatures;
};