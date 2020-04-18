#pragma once

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include <string>

namespace renderer {

enum class ImageFormat : int8_t
{
    PNG_32 = 0,
	PNG_24 = 1,
	PNG_16 = 2,
	PNG_8 = 3,
    TPL = 4
};

class Image2D
{
public:    	
    ~Image2D();
    Image2D(const Image2D&) = delete;
    Image2D(Image2D&&) = delete;
    Image2D& operator=(const Image2D&) = delete;
    Image2D& operator=(Image2D&&) = delete;

	int Width() const;
	int Height() const;
    ImageFormat Format() const;
    const uint8_t *Data() const;

	static std::shared_ptr<Image2D> Create(const uint8_t* data, size_t imageSize = 0);
	static std::shared_ptr<Image2D> LoadFromFile(const std::string& filePath);

private:
	Image2D() = default;
	Image2D(uint8_t* data, size_t imageSize, int32_t width, int32_t height, ImageFormat format);
	int mWidth;
	int mHeight;
    ImageFormat mFormat;
    uint8_t* mData;
    size_t mDataSize;
};

inline int Image2D::Width() const
{
    return mWidth;
}

inline int Image2D::Height() const
{
    return mHeight;
}

inline ImageFormat Image2D::Format() const
{
    return mFormat;
}

inline const uint8_t* Image2D::Data() const
{
    return mData;
}

}
