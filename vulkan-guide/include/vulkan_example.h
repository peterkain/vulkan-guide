#pragma once

#include "types.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class VulkanExample
{
public:
	VulkanExample(conststr name, uint32 version);
	~VulkanExample();

private:
	void InitGLFW3();
	void CreateInstance();
	void Execute();

	conststr name;
	uint32 version;

	VkInstance vkInstance;

	GLFWwindow* glfwWindow;
	uint32 glfwNumExtensions;
	const char** glfwExtensions;
};