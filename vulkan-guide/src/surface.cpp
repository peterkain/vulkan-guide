#include "surface.h"
#include "utils.h"


Surface::Surface(conststr& name, uint32 version)
	: LogicalDevice{name, version, true} {
	CreateWindow();
	CreateSurface();

	getPhysicalDevicePredicate = std::bind(&Surface::CheckPhysicalDevice, this, std::placeholders::_1);
	GetPhysicalDevice();
	CreateLogicalDevice(surface, presentationQueue);
}


Surface::~Surface() {
	vkDestroySurfaceKHR(instance, surface, nullptr);
}


Surface::Surface(conststr& name, uint32 version, [[maybe_unused]] bool _override)
	: LogicalDevice{name, version, true} {
}


void Surface::CreateSurface() {
	// Normally a platform-specific call has to be made, but GLFW does that for us
	// 1. Fill the Vk *PLATFORM* SurfaceCreateInfoKHR struct
	// 2. Call vkCreate *PLATFORM* SurfaceKHR(instance, aboveStruct, allocator, &surface)

	if (glfwCreateWindowSurface(instance, glfwWindow, nullptr, &surface) != VK_SUCCESS) {
		ExitMsg("Failed to create the surface!");
	}
	else {
		Msg("Surface successfully created!");
	}
}


bool Surface::CheckPhysicalDevice(VkPhysicalDevice device) {
	GetAvailableQueueFamilies(device);
	QueueFamilyIndices indices{FindQueueFamilies(device, surface, availableQueueFamilies)};
	return indices.Complete();
}


void Surface::Execute() {
	while (!glfwWindowShouldClose(glfwWindow)) {
		glfwPollEvents();
	}
}