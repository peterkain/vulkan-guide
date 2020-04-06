#pragma once
#include "swap_chain.h"


class ImageViews : public SwapChain
{
public:
	ImageViews(conststr& name, uint32 version);
	virtual ~ImageViews();

protected:
	void CreateImageViews();

	std::vector<VkImageView> swapChainImageViews;
};