#pragma once
#include "graphics_pipeline.h"


class FrameAndCommandBuffers : public GraphicsPipeline
{
public:
	FrameAndCommandBuffers(conststr& name, uint32 version);
	virtual ~FrameAndCommandBuffers();

protected:
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void RecordCommandBuffers();

	std::vector<VkFramebuffer> framebuffers;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
};