#pragma once
#include "frame_and_command_buffers.h"


class Triangle : public FrameAndCommandBuffers
{
public:
	Triangle(conststr& name, uint32 version);
	virtual ~Triangle();

	void Execute();

protected:
	void CreateSemaphores();
	void Draw();

	VkSemaphore imageAvailable;
	VkSemaphore renderFinished;
};