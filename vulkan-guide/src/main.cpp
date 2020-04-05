#include <iostream>
#include "vulkan_example.h"
#include "validation_layers.h"
#include "physical_devices_and_queue_families.h"
#include "logical_device.h"
#include "surface.h"
#include "swap_chain.h"
#include "utils.h"

using namespace std;

int main() {
	//VulkanExample example{"Initializing Vulkan", VK_MAKE_VERSION(1, 0, 0)};
	//example.GetSupportedExtensions();
	//example.Execute();

	//ValidationLayers validation{"Using Validation Layers", VK_MAKE_VERSION(1, 0, 0)};
	//validation.Execute();

	//PhysicalDevicesAndQueueFamilies physicaldev{"Choosing a Physical Device", VK_MAKE_VERSION(1, 0, 0)};
	//physicaldev.Execute();

	//LogicalDevice logicaldev{"Creating a logical device from the physical device", VK_MAKE_VERSION(1, 0, 0)};
	//logicaldev.Execute();

	//Surface surface{"Creating a surface", VK_MAKE_VERSION(1, 0, 0)};
	//surface.Execute();

	SwapChain swapchain{"Creating the swap chain", VK_MAKE_VERSION(1, 0, 0)};
	swapchain.Execute();
	
	//std::cin.get();
}