#include "vulkan_example.h"
#include "utils.h"

VulkanExample::VulkanExample(conststr name, uint32 version)
	: name{name}, version{version}
{
	InitGLFW3();
	CreateInstance();
	Execute();
}


VulkanExample::~VulkanExample() {
	vkDestroyInstance(vkInstance, nullptr);
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();
}


void VulkanExample::InitGLFW3()
{
	/*if (!glfwVulkanSupported()) {
		ExitMsg("Vulkan ist auf dem System nicht unterstützt!");
	}*/
	// Init GLFW
	if (!glfwInit()) {
		ExitMsg("GLFW3 konnte nicht initialisiert werden!");
	}

	//GLFWMonitor* monitor = glfwGetPrimaryMonitor();
	//GLFWvidmode videoMode = glfwGetVideoMode(monitor);

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwNumExtensions);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindow = glfwCreateWindow(800, 600, name.c_str(), nullptr, nullptr);
}


void VulkanExample::CreateInstance() 
{
	VkApplicationInfo exampleInfo{};
	exampleInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	exampleInfo.apiVersion = VK_API_VERSION_1_0;
	exampleInfo.pApplicationName = name.c_str();
	exampleInfo.applicationVersion = version;
	exampleInfo.pEngineName = name.c_str();
	exampleInfo.engineVersion = version;
	
	VkInstanceCreateInfo instanceInfo{};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &exampleInfo;
	instanceInfo.enabledExtensionCount = glfwNumExtensions;
	instanceInfo.ppEnabledExtensionNames = glfwExtensions;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = nullptr;

	if (vkCreateInstance(&instanceInfo, nullptr, &vkInstance) != VK_SUCCESS) {
		ExitMsg("Vulkan Instanz konnte nicht erstellt werden!");
	}
	else {
		Msg("Vulkan Instanz erfolgreich erstellt!");
	}
}


void VulkanExample::Execute() {
	while (!glfwWindowShouldClose(glfwWindow)) {
		glfwPollEvents();
	}
}