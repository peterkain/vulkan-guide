#include <iostream>
#include "vulkan_example.h"
#include "validation_layers.h"
#include "physical_devices_and_queue_families.h"
#include "logical_device.h"
#include "surface.h"
#include "swap_chain.h"
#include "image_views.h"
#include "graphics_pipeline.h"
#include "frame_and_command_buffers.h"
#include "triangle.h"
#include "utils.h"

using namespace std;

int main() {
	/*{
		VulkanExample example{"Initializing Vulkan", VK_MAKE_VERSION(1, 0, 0)};
		example.GetSupportedExtensions();
		example.Execute();
	}*/

	/*{
		ValidationLayers example{"Using Validation Layers", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		PhysicalDevicesAndQueueFamilies example{"Choosing a Physical Device", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		LogicalDevice example{"Creating a logical device from the physical device", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		Surface example{"Creating a surface", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		SwapChain example{"Creating the swap chain", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		ImageViews example{"Creating image views", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		GraphicsPipeline example{"Creating the graphics pipeline", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	/*{
		FrameAndCommandBuffers example{"Creating frame and command buffers", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}*/

	{
		Triangle example{"Creating the triangle!", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	
	std::cin.get();
}