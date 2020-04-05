#pragma once
#include "vulkan_example.h"
#include "logical_device.h"


class Surface : public LogicalDevice
{
public:
	Surface(conststr& name, uint32 version);
	virtual ~Surface();

	void Execute();

protected:
	Surface(conststr& name, uint32 version, [[maybe_unused]] bool _override);
	void CreateSurface();

	bool CheckPhysicalDevice(VkPhysicalDevice device);

	VkSurfaceKHR surface;
	VkQueue presentationQueue;
};