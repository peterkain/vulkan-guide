#pragma once
#include "physical_devices_and_queue_families.h"


class LogicalDevice : public PhysicalDevicesAndQueueFamilies
{
public:
	LogicalDevice(conststr& name, uint32 version);
	virtual ~LogicalDevice();

	void Execute();

protected:
	void CreateLogicalDevice();
	void SetDeviceFeatures(VkPhysicalDeviceFeatures features);

	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkPhysicalDeviceFeatures deviceFeatures;
};