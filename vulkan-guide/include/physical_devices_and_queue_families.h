#pragma once
#include "validation_layers.h"
#include "queue_family_indices.h"
#include <functional>


class PhysicalDevicesAndQueueFamilies : public ValidationLayers
{
public:
	PhysicalDevicesAndQueueFamilies(conststr& name, uint32 version);
	void Execute();

protected:
	bool CheckPhysicalDevice(VkPhysicalDevice device);
	void GetPhysicalDevice(std::function<bool(VkPhysicalDevice)> predicate);
	void GetAvailableQueueFamilies(VkPhysicalDevice device);

	VkPhysicalDevice physicalDevice;
	std::vector<VkPhysicalDevice> availablePhysicalDevices;
	std::vector<VkQueueFamilyProperties> availableQueueFamilies;
	std::function<bool(VkPhysicalDevice)> getPhysicalDevicePredicate {
		std::bind(&PhysicalDevicesAndQueueFamilies::CheckPhysicalDevice, this, std::placeholders::_1)
	};
};