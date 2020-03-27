#include "windows_defines.h"
#include "matrix4x4.h"

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
		math::Matrix4x4 mProjectionMatrix;
		std::shared_ptr<Shader> mCurrentShader;
		GLFWwindow* mWindow = nullptr;
		bool mUseVSync = false;
	};
}