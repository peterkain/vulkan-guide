#pragma once
#include "vulkan_example.h"
#include <vector>

class ValidationLayers : public VulkanExample
{
public:
	ValidationLayers(conststr& name, uint32 version);

	bool CheckIfLayerValid(const char* const name);
	void AddValidationLayer(const char* const name);
	void CreateInstanceWithValidationLayers();

	void Execute();

protected:
	ValidationLayers(conststr& name, uint32 version, [[maybe_unused]] bool _override);
	void GetAvailableLayers();
	void PrintAvailableLayers();

	std::vector<const char*> validationLayers;
	std::vector<VkLayerProperties> availableLayers;

	const char* const standardValidationLayer{"VK_LAYER_KHRONOS_validation"};
};