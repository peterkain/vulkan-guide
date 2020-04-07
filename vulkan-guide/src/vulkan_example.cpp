#include "vulkan_example.h"
#include "utils.h"
#include <vector>

VulkanExample::VulkanExample(conststr& name, uint32 version)
	: VulkanExample{name, version, true}
{
	//InitGLFW3();
	CreateWindow();
	CreateInstance();
}


VulkanExample::VulkanExample(conststr& name, uint32 version, [[maybe_unused]] bool _override)
	: name{name}, version{version}, glfwWindow{nullptr}
{
	InitGLFW3();
}


VulkanExample::~VulkanExample() {
	vkDestroyInstance(instance, nullptr);
	if (glfwWindow) {
		glfwDestroyWindow(glfwWindow);
	}
	glfwTerminate();
}


void VulkanExample::InitGLFW3() {
	/*if (!glfwVulkanSupported()) {
		ExitMsg("Vulkan ist auf dem System nicht unterst�tzt!");
	}*/
	// Init GLFW
	if (!glfwInit()) {
		ExitMsg("GLFW3 could not be initialized!");
	}

	//GLFWMonitor* monitor = glfwGetPrimaryMonitor();
	//GLFWvidmode videoMode = glfwGetVideoMode(monitor);

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwNumExtensions);
}


void VulkanExample::CreateWindow() {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindow = glfwCreateWindow(800, 600, name.c_str(), nullptr, nullptr);
}


void VulkanExample::CreateInstance(uint32 enabledLayerCount, const char* const* enabledLayerNames) {
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_0;
	appInfo.pApplicationName = name.c_str();
	appInfo.applicationVersion = version;
	appInfo.pEngineName = name.c_str();
	appInfo.engineVersion = version;

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = glfwNumExtensions;
	instanceInfo.ppEnabledExtensionNames = glfwExtensions;
	instanceInfo.enabledLayerCount = enabledLayerCount;
	instanceInfo.ppEnabledLayerNames = enabledLayerNames;

	if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS) {
		ExitMsg("Vulkan instance could not be created!");
	}
	else {
		Msg("Vulkan instance created!");
	}
}


void VulkanExample::GetSupportedExtensions() {
	uint32 numExtensions;
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

	std::vector<VkExtensionProperties> extensions(numExtensions);
	vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, extensions.data());

	std::cout << numExtensions << " EXTENSIONS:" << std::endl;
	for (auto& ext : extensions) {
		std::cout << '\t' << ext.extensionName << std::endl;
	}
}


void VulkanExample::Execute() {
	while (!glfwWindowShouldClose(glfwWindow)) {
		glfwPollEvents();
	}
}