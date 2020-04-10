#include "validation_layers.h"
#include "utils.h"
#include <cstring>
#include <algorithm>

using namespace std::string_literals;


ValidationLayers::ValidationLayers(conststr& name, uint32 version)
	: VulkanExample(name, version, true) {
	GetAvailableLayers();
}


/*ValidationLayers::ValidationLayers(conststr& name, uint32 version, [[maybe_unused]] bool _override)
	: VulkanExample(name, version, true) {

}*/


void ValidationLayers::GetAvailableLayers() {
	uint32 numLayers;
	vkEnumerateInstanceLayerProperties(&numLayers, nullptr);

	availableLayers.resize(numLayers);
	vkEnumerateInstanceLayerProperties(&numLayers, availableLayers.data());
}


void ValidationLayers::PrintAvailableLayers() {
	std::cout << availableLayers.size() << " LAYERS:" << std::endl;
	for (auto& layer : availableLayers) {
		std::cout << '\t' << layer.layerName << std::endl;
	}
}


bool ValidationLayers::CheckIfLayerValid(const char* const name) {
	return std::any_of(availableLayers.begin(), availableLayers.end(),
					   [&](VkLayerProperties layer) {
						   return std::strcmp(layer.layerName, name) == 0;
					   });
}


void ValidationLayers::AddValidationLayer(const char* const name) {
	if (CheckIfLayerValid(name)) {
		validationLayers.push_back(name);
		std::cout << "Adding validation layer: " << name << std::endl;
	}
}


void ValidationLayers::CreateInstanceWithValidationLayers() {
	CreateInstance(static_cast<uint32>(validationLayers.size()), validationLayers.data());
}


void ValidationLayers::Execute() {
	PrintAvailableLayers();
	
	std::vector<std::string> inputs;
	while (true) {
		std::string input;
		std::cout << "Enter validation layer: ";
		std::getline(std::cin, input);
		if (input == "$FINISH") {
			break;
		}
		else if (input == "$PRINT") {
			PrintAvailableLayers();
		}
		else {
			if (CheckIfLayerValid(input.c_str())) {
				inputs.push_back(input);
			}
			else {
				std::cout << "Layer " << input << " not valid" << std::endl;
			}
		}
	}

	validationLayers.reserve(inputs.size());
	std::transform(inputs.begin(), inputs.end(), std::back_inserter(validationLayers),
				   [](std::string& s) {
					   return s.c_str();
				   });

	CreateInstanceWithValidationLayers();
}