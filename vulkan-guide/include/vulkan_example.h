#pragma once

#include "types.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class VulkanExample
{
public:
	VulkanExample(conststr& name, uint32 version);
	~VulkanExample();

	void Execute();
	void GetSupportedExtensions();

protected:
	VulkanExample(conststr& name, uint32 version, [[maybe_unused]] bool _override);
	void InitGLFW3();
	void CreateWindow();
	void CreateInstance(uint32 enabledLayerCount = 0, const char* const* enabledLayerNames = nullptr);

	conststr name;
	uint32 version;

	VkInstance vkInstance;

	GLFWwindow* glfwWindow;
	uint32 glfwNumExtensions;
	const char** glfwExtensions;
};