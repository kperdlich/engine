#include "windows_defines.h"
#include "renderer.h"
#include "opengl_renderdata.h"

renderer::Renderer::Renderer(bool useVSync)
{
	mRenderData = new RenderData();
	mRenderData->mUseVSync = useVSync;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mRenderData->mWindow = glfwCreateWindow(640, 480, "Engine", nullptr, nullptr);
	glfwMakeContextCurrent(mRenderData->mWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glfwSwapInterval(mRenderData->mUseVSync);

	std::cout << "Context created: OpenGL " << glGetString(GL_VERSION) << " / " << glGetString(GL_RENDERER) << std::endl;
}

renderer::Renderer::~Renderer()
{
	if (!mRenderData)
		return;

	if (mRenderData->mWindow)
	{
		glfwDestroyWindow(mRenderData->mWindow);
	}

	delete mRenderData;
	mRenderData = nullptr;
	glfwTerminate();	
}

void renderer::Renderer::DisplayBuffer() 
{
	glfwSwapBuffers(mRenderData->mWindow);
	glfwPollEvents();
}

void renderer::Renderer::PreDraw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::Renderer::SetClearColor(const ColorRGBA& clearColor) 
{
	glClearColor(clearColor.Red(), clearColor.Green(), clearColor.Blue(), clearColor.Alpha());
}

/*void renderer::Renderer::SetCamera(std::shared_ptr<Camera> camera) {}

void renderer::Renderer::SetZModeEnabled(bool isEnabled) {}
void renderer::Renderer::SetCullMode(const CullMode& mode) {}
void renderer::Renderer::EnableFog(const float startZ, const float endZ, const ColorRGBA& color) {}
void renderer::Renderer::DisableFog() {}

void renderer::Renderer::LoadModelViewMatrix(const math::Matrix3x4& modelView, const uint8_t matrixIndex) {}
void renderer::Renderer::LoadFont(const uint8_t* fontData, const int32_t size, const uint32_t fontSize) {}
void renderer::Renderer::SetLineWidth(uint8_t width) {}

void renderer::Renderer::DrawText(int32_t x, int32_t y, const std::wstring& text, const ColorRGBA& color, uint16_t textStyle) {}
void renderer::Renderer::DrawSpriteSheet(int32_t x, int32_t y, Sprite& sprite, uint32_t index, uint32_t tileWidth, uint32_t tileHeight, uint32_t finalSpriteWidth, uint32_t finalSpriteHeight) {}
void renderer::Renderer::DrawSpriteSheet(int32_t x, int32_t y, Sprite& sprite, uint32_t tileX, uint32_t tileY, uint32_t tileWidth, uint32_t tileHeight, uint32_t finalSpriteWidth, uint32_t finalSpriteHeight) {}
void renderer::Renderer::Draw(Mesh& mesh) {}
void renderer::Renderer::Draw(Sprite& sprite) {}
void renderer::Renderer::DrawLine(const math::Vector3f& from, const math::Vector3f& end, const renderer::ColorRGBA& color) {}
void renderer::Renderer::DrawRay(const math::Vector3f& from, const math::Vector3f& direction, const renderer::ColorRGBA& color) {}
void renderer::Renderer::DrawAABB(const core::AABB& aabb, const renderer::ColorRGBA& color, float scale) {}

void renderer::Renderer::ClearStatistics() {}
void renderer::Renderer::UpdateFPS() {}

uint32_t renderer::Renderer::GetWidth() const { return 0; }
uint32_t renderer::Renderer::GetHeight() const { return 0; }*/
