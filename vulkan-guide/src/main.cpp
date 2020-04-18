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

const string HELP_MESSAGE {"Usage:\n\
vkguide OPTION\n\
  OPTIONs:\n\
    -0: Run Setup for the Logical Device        (Chapter 2)\n\
    -1: Run the Validation Layers Example       (Chapter 3)\n\
    -2: Run Setup for the Swap Chain            (Chapter 4)\n\
    -3: Run Setup for the Graphics Pipeline     (Chapter 5)\n\
    -4: Run Setup for Frame- and Commandbuffers (Chapter 6)\n\
    -5: Run the Triangle Example                (Chapter 7)\n\
    -h: Display this help message"};

int main(int argc, char** argv) {
	string arg{argv[argc - 1]};
	if (argc != 2 || arg == "-h") {
		Msg(HELP_MESSAGE);
		return 0;
	}
	if (arg == "-0") {
		LogicalDevice example{"Creating a logical device from the physical device", VK_MAKE_VERSION(1, 0, 0)};
		example.GetSupportedExtensions();
		example.Execute();
	}
	else if (arg == "-1") {
		ValidationLayers example{"Using Validation Layers", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	else if (arg == "-2") {
		SwapChain example{"Creating the swap chain", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	else if (arg == "-3") {
		GraphicsPipeline example{"Creating the graphics pipeline", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	else if (arg == "-4") {
		FrameAndCommandBuffers example{"Creating frame and command buffers", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	else if (arg == "-5") {
		Triangle example{"Creating the triangle!", VK_MAKE_VERSION(1, 0, 0)};
		example.Execute();
	}
	else {
		Msg("Unknown command...");
		Msg(HELP_MESSAGE);
		return -1;
	}
	
	cin.get();
}