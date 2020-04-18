#pragma once
#include "utils.h"
#include <vulkan/vulkan.h>


struct MyShaderModule
{
	MyShaderModule(conststr& path, VkDevice* device) : logicalDevice{device} {
		auto spv{ReadSPV(path)};

		VkShaderModuleCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize = spv.size();
		info.pCode = reinterpret_cast<const uint32*>(spv.data());

		//std::cout << "Codesize for " << path << ": " << info.codeSize << std::endl;

		if (vkCreateShaderModule(*logicalDevice, &info, nullptr, &shaderModule) != VK_SUCCESS) {
			ExitMsg("Failed to create shader module");
		}
		else {
			Msg("Created shader module for " + path + '!');
		}
	}

	~MyShaderModule() {
		vkDestroyShaderModule(*logicalDevice, shaderModule, nullptr);
	}

	VkShaderModule shaderModule;
	VkDevice* logicalDevice;
};


[[maybe_unused]]
static VkPipelineShaderStageCreateInfo ShaderStageCreateInfo(
	VkShaderStageFlagBits bit, VkShaderModule module, const char* name) {
	VkPipelineShaderStageCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = bit;
	info.module = module;
	info.pName = name;

	return info;
}