#include "graphics_pipeline.h"
#include "vulkan_helper.h"


GraphicsPipeline::GraphicsPipeline(conststr& name, uint32 version) 
	: GraphicsPipeline{name, version, true} {
	CreateRenderPass();
	CreateGraphicsPipeline();
}


GraphicsPipeline::~GraphicsPipeline() {
	vkDestroyPipeline(logicalDevice, graphicsPipeline, nullptr);
	vkDestroyRenderPass(logicalDevice, renderPass, nullptr);
	vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);
}


GraphicsPipeline::GraphicsPipeline(conststr& name, uint32 version,
								   [[maybe_unused]] bool _override) 
	: ImageViews{name, version}
	, setupVertexBuffer{DefaultSetupVertexBuffer}
	, setupInputAssembly{DefaultSetupInputAssembly}
	, setupViewportScissorInfo{DefaultSetupViewportScissorInfo}
	, setupViewport{DefaultSetupViewport}
	, setupRasterizer{DefaultSetupRasterizer}
	, setupMultisampling{DefaultSetupMultisampling}
	, setupColorBlendAttachment{DefaultSetupColorBlendAttachment}
	, setupColorBlending{DefaultSetupColorBlending}
	, setupPipelineLayout{DefaultSetupPipelineLayout} {
}


void GraphicsPipeline::CreateRenderPass() {
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = swapChainFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentReference{};
	colorAttachmentReference.attachment = 0;
	colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentReference;

	/*VkSubpassDependency dependency{};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;

	dependency.dstSubpass = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;*/

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 0;
	//renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(logicalDevice, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
		ExitMsg("Could not create render pass");
	}
	else {
		Msg("Successfully created the render pass!");
	}
}


void GraphicsPipeline::CreateGraphicsPipeline() {
	MyShaderModule vertex{"data/triangle_vs.spv", &logicalDevice};
	MyShaderModule fragment{"data/triangle_fs.spv", &logicalDevice};

	VkPipelineShaderStageCreateInfo shaderStages[]{
		ShaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, vertex.shaderModule, "main"),
		ShaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, fragment.shaderModule, "main")
	};

	auto vertexBufferInfo     {setupVertexBuffer()};
	auto inputAssemblyInfo    {setupInputAssembly()};
	auto viewportScissor      {setupViewportScissorInfo(swapChainExtent)};
	auto viewportInfo         {setupViewport(viewportScissor.first, viewportScissor.second)};
	auto rasterizerInfo       {setupRasterizer()};
	auto multisamplingInfo    {setupMultisampling()};
	auto colorBlendAttachment {setupColorBlendAttachment()};
	auto colorBlendingInfo    {setupColorBlending(colorBlendAttachment)};
	auto layoutInfo           {setupPipelineLayout()};
	
	if (vkCreatePipelineLayout(logicalDevice, &layoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		ExitMsg("Failed to create pipeline layout");
	}
	else {
		Msg("Successfully created the pipeline layout!");

		VkGraphicsPipelineCreateInfo graphicsPipelineInfo{};
		graphicsPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		graphicsPipelineInfo.stageCount = 2;
		graphicsPipelineInfo.pStages = shaderStages;
		graphicsPipelineInfo.pVertexInputState = &vertexBufferInfo;
		graphicsPipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
		graphicsPipelineInfo.pViewportState = &viewportInfo;
		graphicsPipelineInfo.pRasterizationState = &rasterizerInfo;
		graphicsPipelineInfo.pMultisampleState = &multisamplingInfo;
		graphicsPipelineInfo.pDepthStencilState = nullptr;
		graphicsPipelineInfo.pColorBlendState = &colorBlendingInfo;
		graphicsPipelineInfo.pDynamicState = nullptr;
		graphicsPipelineInfo.layout = pipelineLayout;
		graphicsPipelineInfo.renderPass = renderPass;
		graphicsPipelineInfo.subpass = 0;
		graphicsPipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineInfo.basePipelineIndex = -1;

		if (vkCreateGraphicsPipelines(logicalDevice, VK_NULL_HANDLE, 1, &graphicsPipelineInfo,
									  nullptr, &graphicsPipeline) != VK_SUCCESS) {
			ExitMsg("Failed to create the graphics pipeline");
		}
		else {
			Msg("Successfully created the graphics pipeline!");
		}
	}
}





// DEFAULT FUNCTIONS
// ==================================================================================

VkPipelineVertexInputStateCreateInfo GraphicsPipeline::DefaultSetupVertexBuffer() {
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr;

	return vertexInputInfo;
}


VkPipelineInputAssemblyStateCreateInfo GraphicsPipeline::DefaultSetupInputAssembly() {
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
	inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

	return inputAssemblyInfo;
}


std::pair<VkViewport, VkRect2D> GraphicsPipeline::DefaultSetupViewportScissorInfo(VkExtent2D extent) {
	VkViewport viewport{};
	viewport.x = 0.f;
	viewport.y = 0.f;
	viewport.width = static_cast<float>(extent.width);
	viewport.height = static_cast<float>(extent.height);
	viewport.minDepth = 0.f;
	viewport.maxDepth = 1.f;

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = extent;

	return std::make_pair(viewport, scissor);
}


VkPipelineViewportStateCreateInfo GraphicsPipeline::DefaultSetupViewport(VkViewport& viewport, VkRect2D& scissor) {
	VkPipelineViewportStateCreateInfo viewportStateInfo{};
	viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateInfo.viewportCount = 1;
	viewportStateInfo.pViewports = &viewport;
	viewportStateInfo.scissorCount = 1;
	viewportStateInfo.pScissors = &scissor;

	return viewportStateInfo;
}


VkPipelineRasterizationStateCreateInfo GraphicsPipeline::DefaultSetupRasterizer() {
	VkPipelineRasterizationStateCreateInfo rasterizerInfo{};
	rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizerInfo.depthClampEnable = VK_FALSE;
	rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizerInfo.lineWidth = 1.f;
	rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizerInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizerInfo.depthBiasEnable = VK_FALSE;

	return rasterizerInfo;
}


VkPipelineMultisampleStateCreateInfo GraphicsPipeline::DefaultSetupMultisampling() {
	VkPipelineMultisampleStateCreateInfo multisamplingInfo{};
	multisamplingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisamplingInfo.sampleShadingEnable = VK_FALSE;
	multisamplingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	return multisamplingInfo;
}


VkPipelineColorBlendAttachmentState GraphicsPipeline::DefaultSetupColorBlendAttachment() {
	VkPipelineColorBlendAttachmentState colorBlendAttachement{};
	colorBlendAttachement.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachement.blendEnable = VK_FALSE;

	return colorBlendAttachement;
}


VkPipelineColorBlendStateCreateInfo GraphicsPipeline::DefaultSetupColorBlending(VkPipelineColorBlendAttachmentState& attachment) {
	VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
	colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendInfo.logicOpEnable = VK_FALSE;
	colorBlendInfo.attachmentCount = 1;
	colorBlendInfo.pAttachments = &attachment;

	return colorBlendInfo;
}


VkPipelineLayoutCreateInfo GraphicsPipeline::DefaultSetupPipelineLayout() {
	VkPipelineLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

	return layoutInfo;
}