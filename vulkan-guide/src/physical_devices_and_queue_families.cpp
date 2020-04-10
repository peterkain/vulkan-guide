#include "physical_devices_and_queue_families.h"
#include "utils.h"
#include <sstream>

PhysicalDevicesAndQueueFamilies::PhysicalDevicesAndQueueFamilies(conststr& name, uint32 version)
	: ValidationLayers(name, version), physicalDevice{VK_NULL_HANDLE} {
	AddValidationLayer(khronosValidationLayer);
	AddValidationLayer("VK_LAYER_LUNARG_standard_validation");
	AddValidationLayer(lunargApiDumpValidationLayer);
	AddValidationLayer(lunargCoreValidationLayer);
	AddValidationLayer(lunargParameterValidationLayer);
	CreateInstanceWithValidationLayers();
}


void PhysicalDevicesAndQueueFamilies::GetPhysicalDevice() {
	uint32 count;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);

	if (!count) {
		ExitMsg("No physical device with Vulkan support found");
	}

	availablePhysicalDevices.resize(count);
	vkEnumeratePhysicalDevices(instance, &count, availablePhysicalDevices.data());

	for (const auto& device : availablePhysicalDevices) {
		if (getPhysicalDevicePredicate(device)) {
			physicalDevice = device;
			Msg("Physical device found!");
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		ExitMsg("No suitable physical device found");
	}
}


bool PhysicalDevicesAndQueueFamilies::CheckPhysicalDevice(VkPhysicalDevice device) {
	// Can do checks to select best suitable device, but isn't needed
	// VkPhysicalDeviceProperties
	// VkPhysicalDeviceFeatures
	GetAvailableQueueFamilies(device);
	QueueFamilyIndices indices{FindQueueFamilies(availableQueueFamilies)};
	return indices.graphicsFamily.has_value();
}


void PhysicalDevicesAndQueueFamilies::GetAvailableQueueFamilies(VkPhysicalDevice device) {
	uint32 count;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

	availableQueueFamilies.resize(count);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &count, availableQueueFamilies.data());
}


void PhysicalDevicesAndQueueFamilies::Execute() {
	GetPhysicalDevice();

	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;

	vkGetPhysicalDeviceProperties(physicalDevice, &properties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &features);

	std::stringstream ss;
	ss << "Some Properties about the Physical Device: " << '\n';
	ss << "\tDevice Name: " << properties.deviceName << '\n';
	ss << "\tDevice API version: ";
	PrintVersion(ss, properties.apiVersion);
	ss << "\tDevice Vulkan Driver version: ";
	PrintVersion(ss, properties.driverVersion);
	ss << "\tDevice Max Framebuffer Width: " << properties.limits.maxFramebufferWidth << '\n';
	ss << "\tDevice Max Framebuffer Height: " << properties.limits.maxFramebufferHeight << '\n';
	ss << '\n';
	ss << "Some Features of the Physical Device: " << '\n';
	ss << "\tDevice supports Geometry Shaders: " << features.geometryShader << '\n';
	ss << "\tDevice supports Tessellation Shaders: " << features.tessellationShader << '\n';
	ss << "\tDevice supports Blend operations with two sources: " << features.dualSrcBlend << '\n';
	ss << "\tDevice supports more than one active Viewport: " << features.multiViewport << '\n';

	std::cout << ss.str() << std::endl;
}