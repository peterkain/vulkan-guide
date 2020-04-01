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
	void GetAvailableLayers();
	void PrintAvailableLayers();

	std::vector<const char*> validationLayers;
	std::vector<VkLayerProperties> availableLayers;

private:
	void _AddValidationLayer(const char* const name);
};