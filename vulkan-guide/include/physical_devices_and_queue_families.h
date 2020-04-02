#pragma once
#include "validation_layers.h"
#include <optional>


class PhysicalDevicesAndQueueFamilies : public ValidationLayers
{
public:
	PhysicalDevicesAndQueueFamilies(conststr& name, uint32 version);
	void Execute();

protected:
	struct QueueFamilyIndices
	{
		std::optional<uint32> graphicsFamily;

		bool IsComplete() {
			return graphicsFamily.has_value();
		}
	};

	void GetPhysicalDevice();
	bool CheckPhysicalDevice(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	VkPhysicalDevice physicalDevice;
	std::vector<VkPhysicalDevice> availablePhysicalDevices;
	std::vector<VkQueueFamilyProperties> availableQueueFamilies;
};