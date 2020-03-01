#include "windows_defines.h"

namespace renderer {
	class RenderData
	{
	public:
		RenderData() = default;
		~RenderData() = default;
		RenderData(const RenderData&) = delete;
		RenderData& operator = (const RenderData&) = delete;
		RenderData(RenderData&&) = delete;
		RenderData& operator = (RenderData&&) = delete;
	public:
		bool mUseVSync = false;
		GLFWwindow* mWindow = nullptr;
	};
}