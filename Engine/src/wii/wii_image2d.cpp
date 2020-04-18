#include "image2d.h"
#include "core.h"
#include "tpl_loader.h"
#include "wii_defines.h"

constexpr uint8_t BytesPerPixelRGBA8 = 4;

std::shared_ptr<renderer::Image2D> renderer::Image2D::Create(const uint8_t* data, size_t imageSize)
{
	ASSERT(data != nullptr);
	std::shared_ptr<Image2D> image = std::shared_ptr<Image2D>(new Image2D());
	// check for png signature
	if (data[0] == 0x89 && data[1] == 0x50 && data[2] == 0x4E && data[3] == 0x47)
	{
		image->mFormat = ImageFormat::PNG_32;
		PNGUPROP pngProps;
		IMGCTX context = PNGU_SelectImageFromBuffer(data);
		PNGU_GetImageProperties(context, &pngProps);
		image->mData = PNGU_DecodeTo4x4RGBA8(context, pngProps.imgWidth, pngProps.imgHeight, &image->mWidth, &image->mHeight, nullptr);
		image->mDataSize = BytesPerPixelRGBA8 * pngProps.imgWidth * pngProps.imgHeight;
		ASSERT(static_cast<int>(pngProps.imgWidth) == image->mWidth);
		ASSERT(static_cast<int>(pngProps.imgHeight) == image->mHeight);
		ASSERT(image->mData != nullptr);
		PNGU_ReleaseImageContext(context);
		DCFlushRange(image->mData, image->mDataSize);
	}
	else if (IsTPLTexture(data))
	{
		ASSERT(imageSize > 0);
		TPL_Texture* tplTexture = renderer::GetTPLTexture(data);
		image->mWidth = tplTexture->width;
		image->mHeight = tplTexture->height;
		image->mFormat = ImageFormat::TPL;
		image->mDataSize = imageSize;
		image->mData = (uint8_t*)memalign(32, image->mDataSize);
		memcpy(image->mData, (void*)data, image->mDataSize);
		const size_t tplDataSize = GetTPLTextureSize(imageSize);
		DCFlushRange(image->mData, tplDataSize);
	}
	else
	{
		ASSERT(false);
	}
	return image;
}

renderer::Image2D::~Image2D()
{
    if (mData)
    {
        free(mData);
        mData = nullptr;
    }
}

std::shared_ptr<renderer::Image2D> renderer::Image2D::LoadFromFile(const std::string& filePath)
{
	// TODO Implement
	ASSERT_TEXT(false, "LoadFromFile not implemented!");
	return {};
}

