#pragma once
#include "surface.h"
#include "swap_chain_support_details.h"

using SwapChainConfig = std::tuple<VkSurfaceFormatKHR, VkPresentModeKHR, VkExtent2D>;

class SwapChain : public Surface
{
public:
	SwapChain(conststr& name, uint32 version);
	virtual ~SwapChain();

protected:
	bool CheckPhysicalDevice(VkPhysicalDevice device);
	void GetAvailableExtensions(VkPhysicalDevice device);
	SwapChainSupportDetails CheckForSwapChainSupport(VkPhysicalDevice device);
	SwapChainConfig ConfigureSwapChain();
	void CreateSwapChain(VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE);

	std::vector<const char*> requiredExtensions{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	std::vector<VkExtensionProperties> availableExtensions;
	SwapChainSupportDetails swapChainDetails;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainFormat;
	VkExtent2D swapChainExtent;
};