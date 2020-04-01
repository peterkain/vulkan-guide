#include <iostream>
#include "vulkan_example.h"
#include "validation_layers.h"

using namespace std;

int main() {
	//VulkanExample example{"Initializing Vulkan", VK_MAKE_VERSION(1, 0, 0)};
	//example.GetSupportedExtensions();
	//example.Execute();

	ValidationLayers example{"Using Validation Layers", VK_MAKE_VERSION(1, 0, 0)};
	example.Execute();
	
	//std::cin.get();
}