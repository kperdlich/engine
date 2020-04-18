#include "resource_manager.h"

std::shared_ptr<renderer::Image2D> core::ResourceManager::LoadImage(const std::string& imageFilePath)
{
	if (mImageCache.find(imageFilePath) == mImageCache.end())
	{
		std::shared_ptr<renderer::Image2D> image = renderer::Image2D::LoadFromFile(imageFilePath);
		mImageCache[imageFilePath] = image;
		return image;
	}
	return mImageCache[imageFilePath];
}