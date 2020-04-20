#include "wii_defines.h"
#include "vector3f.h"
#include "SkyBox.h"
#include "image2d.h"
#include "texture2d.h"
#include "renderer.h"
#include "camera.h"
#include "vertexformat.h"

constexpr uint8_t SKY_FRONT = 0;
constexpr uint8_t SKY_RIGHT = 1;
constexpr uint8_t SKY_LEFT = 2;
constexpr uint8_t SKY_BACK = 3;
constexpr uint8_t SKY_UP = 4;
constexpr uint8_t SKY_DOWN = 5;
constexpr float PLAYER_DISTANCE = 100.0f;

renderer::Skybox::Skybox()
{
    //mImages[SKY_FRONT] = std::make_unique<renderer::Image2D>(SkyBox_Front_png, SkyBox_Front_png_size);
    //mImages[SKY_RIGHT] = std::make_unique<renderer::Image2D>(SkyBox_Back_png, SkyBox_Back_png_size);
    //mImages[SKY_LEFT]  = std::make_unique<renderer::Image2D>(SkyBox_Left_png, SkyBox_Left_png_size);
    //mImages[SKY_BACK]  = std::make_unique<renderer::Image2D>(SkyBox_Right_png, SkyBox_Right_png_size);
    //mImages[SKY_UP]    = std::make_unique<renderer::Image2D>(SkyBox_Top_png, SkyBox_Top_png_size);
    //mImages[SKY_DOWN]  = std::make_unique<renderer::Image2D>(SkyBox_Bottom_png, SkyBox_Bottom_png_size);

    m_pSkyBoxTextures[SKY_FRONT] = std::make_unique<renderer::Texture2D>(*mImages[SKY_FRONT]);
    m_pSkyBoxTextures[SKY_RIGHT] = std::make_unique<renderer::Texture2D>(*mImages[SKY_RIGHT]);
    m_pSkyBoxTextures[SKY_LEFT] = std::make_unique<renderer::Texture2D>(*mImages[SKY_LEFT]);
    m_pSkyBoxTextures[SKY_BACK] = std::make_unique<renderer::Texture2D>(*mImages[SKY_BACK]);
    m_pSkyBoxTextures[SKY_UP] = std::make_unique<renderer::Texture2D>(*mImages[SKY_UP]);
    m_pSkyBoxTextures[SKY_DOWN] = std::make_unique<renderer::Texture2D>(*mImages[SKY_DOWN]);
}

void renderer::Skybox::CreateSkyBox(renderer::Renderer& renderer)
{
   /* math::Vector3f blockPosition = {0.0f, 0.0f, 0.0f};
    const float blockHalfSize = PLAYER_DISTANCE;
    math::Vector3f vertices[8] = {
            { (float)blockPosition.X() - blockHalfSize, (float)blockPosition.Y() + blockHalfSize, (float)blockPosition.Z() + blockHalfSize },// v1
            { (float)blockPosition.X() - blockHalfSize, (float)blockPosition.Y() - blockHalfSize, (float)blockPosition.Z() + blockHalfSize }, //v2
            { (float)blockPosition.X() + blockHalfSize, (float)blockPosition.Y() - blockHalfSize, (float)blockPosition.Z() + blockHalfSize }, //v3
            { (float)blockPosition.X() + blockHalfSize, (float)blockPosition.Y() + blockHalfSize, (float)blockPosition.Z() + blockHalfSize }, // v4
            { (float)blockPosition.X() - blockHalfSize, (float)blockPosition.Y() + blockHalfSize, (float)blockPosition.Z() - blockHalfSize }, //v5
            { (float)blockPosition.X() + blockHalfSize, (float)blockPosition.Y() + blockHalfSize, (float)blockPosition.Z() - blockHalfSize }, // v6
            { (float)blockPosition.X() + blockHalfSize, (float)blockPosition.Y() - blockHalfSize, (float)blockPosition.Z() - blockHalfSize }, // v7
            { (float)blockPosition.X() - blockHalfSize, (float)blockPosition.Y() - blockHalfSize, (float)blockPosition.Z() - blockHalfSize } // v8
        };


     m_displayList.Begin(4000);

    renderer::VertexFormat skyboxFormat(0);
    skyboxFormat.AddAttribute({GX_DIRECT, GX_VA_POS, GX_POS_XYZ, GX_F32});
    skyboxFormat.AddAttribute({GX_DIRECT, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8});
    skyboxFormat.AddAttribute({GX_DIRECT, GX_VA_TEX0, GX_TEX_ST, GX_F32});
    skyboxFormat.Bind();   

    renderer.SetCullMode(CullMode::Front);

    m_pSkyBoxTextures[SKY_FRONT]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // front side
        GX_Position3f32(vertices[0].X(), vertices[0].Y(), vertices[0].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[3].X(), vertices[3].Y(), vertices[3].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[2].X(), vertices[2].Y(), vertices[2].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[1].X(), vertices[1].Y(), vertices[1].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    m_pSkyBoxTextures[SKY_BACK]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // back side
        GX_Position3f32(vertices[5].X(), vertices[5].Y(), vertices[5].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[4].X(), vertices[4].Y(), vertices[4].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[7].X(), vertices[7].Y(), vertices[7].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[6].X(), vertices[6].Y(), vertices[6].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    m_pSkyBoxTextures[SKY_RIGHT]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // right side
        GX_Position3f32(vertices[3].X(), vertices[3].Y(), vertices[3].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[5].X(), vertices[5].Y(), vertices[5].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[6].X(), vertices[6].Y(), vertices[6].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[2].X(), vertices[2].Y(), vertices[2].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    m_pSkyBoxTextures[SKY_LEFT]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // left side
        GX_Position3f32(vertices[4].X(), vertices[4].Y(), vertices[4].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[0].X(), vertices[0].Y(), vertices[0].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[1].X(), vertices[1].Y(), vertices[1].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[7].X(), vertices[7].Y(), vertices[7].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    m_pSkyBoxTextures[SKY_UP]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // top side
        GX_Position3f32(vertices[4].X(), vertices[4].Y(), vertices[4].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[5].X(), vertices[5].Y(), vertices[5].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[3].X(), vertices[3].Y(), vertices[3].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[0].X(), vertices[0].Y(), vertices[0].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    m_pSkyBoxTextures[SKY_DOWN]->Bind();
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        // bottom side
        GX_Position3f32(vertices[6].X(), vertices[6].Y(), vertices[6].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(0.0f, 0.0f);

        GX_Position3f32(vertices[7].X(), vertices[7].Y(), vertices[7].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 0.0f);

        GX_Position3f32(vertices[1].X(), vertices[1].Y(), vertices[1].Z());
        GX_Color1u32(0xFFFFFFFF);
        GX_TexCoord2f32(1.0f, 1.0f);

        GX_Position3f32(vertices[2].X(), vertices[2].Y(), vertices[2].Z());
        GX_Color1u32(0xFFFFFFFF); GX_TexCoord2f32(0.0f, 1.0f);
    GX_End();

    renderer.SetCullMode(CullMode::Back);

    m_displayList.End();*/
}

void renderer::Skybox::Render(Renderer &renderer)
{    
    const math::Vector3f& position = renderer.GetCamera()->Position();
    math::Matrix3x4 modelMatrix;
    modelMatrix.SetIdentity();
    modelMatrix.Translate(position.X(), position.Y(), position.Z());
    renderer.LoadModelMatrix(renderer.GetCamera()->GetViewMatrix4x4() * modelMatrix);

    if (m_displayList.GetBufferSize() <= 0)
    {
        CreateSkyBox(renderer);
    }

    m_displayList.Render();
}
