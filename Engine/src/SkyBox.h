#pragma once

#include <memory>
#include "wii_displaylist.h"
#include "matrix3x4.h"
#include "texture2d.h"
#include "image2d.h"

namespace renderer {

class Camera;

class Skybox {
public:
    Skybox();
    ~Skybox() = default;
	Skybox(const Skybox&) = delete;
	Skybox(Skybox&&) = delete;
	void operator=(const Skybox&) = delete;
	void operator=(Skybox&&) = delete;
    void Render(renderer::Renderer& renderer);
private:
    void CreateSkyBox(renderer::Renderer& renderer);
    std::unique_ptr<renderer::Texture2D> m_pSkyBoxTextures[6];
    std::unique_ptr<renderer::Image2D> mImages[6];
    renderer::DisplayList m_displayList;
};
}
