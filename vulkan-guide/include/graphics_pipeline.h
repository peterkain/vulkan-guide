#pragma once
#include "image_views.h"
#include <functional>


class GraphicsPipeline : public ImageViews
{
public:
	GraphicsPipeline(conststr& name, uint32 version);
	virtual ~GraphicsPipeline();

protected:
	GraphicsPipeline(conststr& name, uint32 version, [[maybe_unused]] bool _override);
	void CreateRenderPass();
	void CreateGraphicsPipeline();

	VkRenderPass renderPass{};
	VkPipelineLayout pipelineLayout{};
	VkPipeline graphicsPipeline{};

	static VkPipelineVertexInputStateCreateInfo DefaultSetupVertexBuffer();
	static VkPipelineInputAssemblyStateCreateInfo DefaultSetupInputAssembly();
	static std::pair<VkViewport, VkRect2D> DefaultSetupViewportScissorInfo(VkExtent2D extent);
	static VkPipelineViewportStateCreateInfo DefaultSetupViewport(VkViewport& viewport, VkRect2D& scissor);
	static VkPipelineRasterizationStateCreateInfo DefaultSetupRasterizer();
	static VkPipelineMultisampleStateCreateInfo DefaultSetupMultisampling();
	static VkPipelineColorBlendAttachmentState DefaultSetupColorBlendAttachment();
	static VkPipelineColorBlendStateCreateInfo DefaultSetupColorBlending(VkPipelineColorBlendAttachmentState& attachment);
	static VkPipelineLayoutCreateInfo DefaultSetupPipelineLayout();

	std::function<VkPipelineVertexInputStateCreateInfo()> setupVertexBuffer;
	std::function<VkPipelineInputAssemblyStateCreateInfo()> setupInputAssembly;
	std::function<std::pair<VkViewport, VkRect2D>(VkExtent2D extent)> setupViewportScissorInfo;
	std::function<VkPipelineViewportStateCreateInfo(VkViewport& viewport, VkRect2D& scissor)> setupViewport;
	std::function<VkPipelineRasterizationStateCreateInfo()> setupRasterizer;
	std::function<VkPipelineMultisampleStateCreateInfo()> setupMultisampling;
	std::function<VkPipelineColorBlendAttachmentState()> setupColorBlendAttachment;
	std::function<VkPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState& attachment)> setupColorBlending;
	std::function<VkPipelineLayoutCreateInfo()> setupPipelineLayout;
};