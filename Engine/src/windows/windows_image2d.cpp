#include "image2d.h"
#include "platform.h"
#include "stb_image.h"

std::shared_ptr<renderer::Image2D> renderer::Image2D::Create(const uint8_t* data, size_t imageSize)
{
	ASSERT_TEXT(false, "Image2D::Create not implemented for Windows! Use Image2D::LoadFromFile instead!");
	return {};
}

renderer::Image2D::Image2D(uint8_t* data, size_t imageSize, int32_t width, int32_t height, ImageFormat format) 
	: mData(data),
	mDataSize(imageSize),
	mWidth(width),
	mHeight(height),
	mFormat(format)	
{	
}

renderer::Image2D::~Image2D()
{
	if (mData)
	{		
		stbi_image_free(mData);
		mData = nullptr;
	}
}

std::shared_ptr<renderer::Image2D> renderer::Image2D::LoadFromFile(const std::string& filePath)
{
	//stbi_set_flip_vertically_on_load(true);
	int32_t width, height, comp;	
	uint8_t* imageData = stbi_load(filePath.c_str(), &width, &height, &comp, 0);
	ASSERT(imageData != nullptr);
	return std::shared_ptr<renderer::Image2D>(new renderer::Image2D(imageData, width * height * comp, width, height, ImageFormat::PNG));	
}

