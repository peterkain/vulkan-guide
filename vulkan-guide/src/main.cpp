#include <iostream>
#include "vulkan_example.h"
#include "validation_layers.h"
#include "physical_devices_and_queue_families.h"
#include "logical_device.h"
#include "utils.h"

using namespace std;

int main() {
	//VulkanExample example{"Initializing Vulkan", VK_MAKE_VERSION(1, 0, 0)};
	//example.GetSupportedExtensions();
	//example.Execute();

	//ValidationLayers example{"Using Validation Layers", VK_MAKE_VERSION(1, 0, 0)};
	//example.Execute();

	//PhysicalDevicesAndQueueFamilies example{"Choosing a Physical Device", VK_MAKE_VERSION(1, 0, 0)};
	//example.Execute();

	LogicalDevice example{"Creating a logical device from the physical device", VK_MAKE_VERSION(1, 0, 0)};
	example.Execute();
	
	std::cin.get();
}