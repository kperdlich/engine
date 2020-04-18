#include "texture2d.h"
#include "image2d.h"
#include "opengl_texture2d_data.h"
#include "platform.h"

renderer::Texture2D::Texture2D(const Image2D& image)
{
	mTextureData = std::make_unique<Texture2DData>();

	glGenTextures(1, &mTextureData->TextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureData->TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	int32_t glFormat;
	switch (image.Format())
	{
		case ImageFormat::PNG_32:
			glFormat = GL_RGBA;
			break;
		case ImageFormat::PNG_24:
			glFormat = GL_RGB;
			break;	
		default:
			ASSERT_TEXT(false, "Image format not supported %d", image.Format());
			break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, image.Width(), image.Height(), 0, glFormat, GL_UNSIGNED_BYTE, image.Data());
	glGenerateMipmap(GL_TEXTURE_2D);
}

renderer::Texture2D::~Texture2D()
{

}

void renderer::Texture2D::Bind(uint8_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, mTextureData->TextureID);
}