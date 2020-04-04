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
	void CreateSurface();

	bool CheckPhysicalDevice(VkPhysicalDevice device);

	VkSurfaceKHR surface;
	VkQueue presentationQueue;
};