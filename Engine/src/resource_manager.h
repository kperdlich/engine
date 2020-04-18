#pragma once

#include <string>
#include <unordered_map>
#include "image2d.h"

namespace core {

	class ResourceManager 
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		std::shared_ptr<renderer::Image2D> LoadImage(const std::string& imageFilePath);	
	private:
		std::unordered_map<std::string, std::shared_ptr<renderer::Image2D>> mImageCache;
	};
}