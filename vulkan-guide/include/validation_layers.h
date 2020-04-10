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
	//ValidationLayers(conststr& name, uint32 version, [[maybe_unused]] bool _override);
	void GetAvailableLayers();
	void PrintAvailableLayers();

	std::vector<const char*> validationLayers;
	std::vector<VkLayerProperties> availableLayers;

	const char* const khronosValidationLayer{"VK_LAYER_KHRONOS_validation"}; 
	const char* const lunargCoreValidationLayer{"VK_LAYER_LUNARG_core_validation"};
	const char* const lunargApiDumpValidationLayer{"VK_LAYER_LUNARG_api_dump"};
	const char* const lunargParameterValidationLayer{"VK_LAYER_LUNARG_parameter_validation"};
};