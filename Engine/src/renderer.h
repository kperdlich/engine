#pragma once

#include <array>
#include <memory>
#include "platform.h"
#include "matrix3x4.h"
#include "matrix4x4.h"
#include "camera.h"
#include "colorrgba.h"

namespace core {
    class AABB;
}

namespace renderer {

struct Statistics
{
    uint8_t FPS = 0;
    uint32_t ChunksInFrustrum = 0;
    uint32_t CulledChunks = 0;
    float ChunkDisplayListSizeMB = 0;
};

enum class CullMode : uint8_t {
    None = 0,
    Front = 1,
    Back = 2,
    All = 3
};

class RenderData;
class TTFFont;
class Mesh;
class StaticMesh;
class Sprite;
class Camera;
class VertexArray;

std::array<float, 8> GetUVTextureCoordinates(uint32_t index, uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight);

class Renderer {
public:
    explicit Renderer(bool useVSync);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator = (const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator = (Renderer&&) = delete;

    void SetClearColor(const ColorRGBA& clearColor);
    void PreDraw();
    void DisplayBuffer();
    void SetCamera(std::shared_ptr<Camera> camera);

	void SetVSync(bool isEnabled);
    void SetZModeEnabled(bool isEnabled);
    void SetCullMode(const CullMode& mode);
    void EnableFog(const float startZ, const float endZ, const ColorRGBA &color);
    void DisableFog();

    void LoadModelViewMatrix(const math::Matrix4x4 &modelView, const uint8_t matrixIndex = 0);
    void LoadFont(const uint8_t* fontData, const int32_t size, const uint32_t fontSize);	

    void SetLineWidth(uint8_t width);

	void BindShader(std::shared_ptr<Shader> shader);

    void DrawText(int32_t x, int32_t y, const std::wstring& text, const ColorRGBA &color, uint16_t textStyle = 0x0001);
    void DrawSpriteSheet(int32_t x, int32_t y, Sprite &sprite, uint32_t index,  uint32_t tileWidth, uint32_t tileHeight, uint32_t finalSpriteWidth, uint32_t finalSpriteHeight);
    void DrawSpriteSheet(int32_t x, int32_t y, Sprite &sprite, uint32_t tileX, uint32_t tileY, uint32_t tileWidth, uint32_t tileHeight, uint32_t finalSpriteWidth, uint32_t finalSpriteHeight);
    void Draw(std::shared_ptr<renderer::VertexArray> vertexArray);
    void Draw(Mesh& mesh);
    void Draw(Sprite &sprite);
    void DrawLine(const math::Vector3f &from, const math::Vector3f& end, const renderer::ColorRGBA& color);
    void DrawRay(const math::Vector3f &from, const math::Vector3f &direction, const renderer::ColorRGBA& color);
    void DrawAABB(const core::AABB& aabb, const renderer::ColorRGBA& color, float scale = 1.0f);

    void ClearStatistics();
    void UpdateFPS();

	void* GetWindowHandle();
	bool IsRunning() const;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

	inline math::Matrix4x4 GetViewProjectionMatrix() const;
    inline std::shared_ptr<renderer::Camera> GetCamera() const;
    inline RenderData* GetRenderData();
    inline Statistics& GetStatistics();
    inline const Statistics& GetStatistics() const;

    static Renderer* s_Renderer;
private:
    Statistics mStatistics;
    RenderData* mRenderData;    
    std::shared_ptr<renderer::Camera> mCamera;
};

inline math::Matrix4x4 Renderer::GetViewProjectionMatrix() const
{
	return mCamera->GetProjectionMatrix4x4() * mCamera->GetViewMatrix4x4();
}

inline std::shared_ptr<Camera> Renderer::GetCamera() const
{
    return mCamera;
}

inline RenderData* Renderer::GetRenderData()
{
    return mRenderData;
}

inline Statistics &Renderer::GetStatistics()
{
    return mStatistics;
}

inline const Statistics &Renderer::GetStatistics() const
{
    return mStatistics;
}

};
