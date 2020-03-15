#include "platform.h"


int main(int args, char** argv)
{
    renderer::Renderer renderer(false);
    renderer.SetZModeEnabled(true);
    renderer.SetClearColor(renderer::ColorRGBA::BLUE);
    renderer.SetCullMode(renderer::CullMode::None);

    std::shared_ptr<renderer::Camera> orthographicCamera = renderer::Camera::Create(math::Vector3f{ .0f, .0f, .1f },
        math::Vector3f{ .0f, 1.0f, .0f },
        math::Vector3f{ .0f, .0f, -1.0f },
        false);
    orthographicCamera->SetFrustrum(renderer.GetHeight(), 0, 0, renderer.GetWidth(), 0, 100.0f);

    std::shared_ptr<renderer::Camera> perspectiveCamera = renderer::Camera::Create(math::Vector3f{ .0f, .0f, .1f },
        math::Vector3f{ .0f, 1.0f, .0f },
        math::Vector3f{ .0f, .0f, -1.0f },
        true);
    perspectiveCamera->SetFrustrum(0.1f, 200.0f, 70.0f, (float)renderer.GetWidth() / (float)renderer.GetHeight());
    renderer.SetCamera(perspectiveCamera);

    std::vector<float> vertices = {
        0.0f, 0.0f, -0.5f,
        100.0f, 300.0f, -0.5f,
        200.0f, 0.0f, -0.5f
    };

    std::vector<uint8_t> colors = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    std::vector<uint32_t> indices =
    {
        0,
        1,
        2
    };

    std::shared_ptr<renderer::Shader> defaultShader = renderer::Shader::CreateDefaultColor();
    std::shared_ptr<renderer::VertexArray> vertexArray = renderer::VertexArray::Create();
    std::shared_ptr<renderer::IndexBuffer> indexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));

    vertexArray->SetIndexBuffer(indexBuffer);

    vertexArray->AddVertexBuffer(
        renderer::VertexFormatAttribute
        {
            renderer::VertexDataInputType::INDEX,
            renderer::VertexAttribute::Position,
            renderer::VertexAttributeComponentType::Position_XYZ,
            renderer::VertexAttributeComponentTypeSize::Float32
        },
        renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float)));

    vertexArray->AddVertexBuffer(
        renderer::VertexFormatAttribute
        {
            renderer::VertexDataInputType::INDEX,
            renderer::VertexAttribute::Color,
            renderer::VertexAttributeComponentType::Color_RGB,
            renderer::VertexAttributeComponentTypeSize::RGB8
        },
        renderer::VertexBuffer::Create(colors.data(), colors.size() * sizeof(int8_t)));

    /*IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)renderer.GetWindowHandle(), false);
    ImGui_ImplOpenGL3_Init(nullptr);
    ImGui::StyleColorsDark();*/

    math::Vector3f pos = { 0.0f, 0.0f, 0.0f };
    while (renderer.IsRunning())
    {
        renderer.PreDraw();


        math::Matrix4x4 translationMatrix = math::Matrix4x4::Identity();
        translationMatrix.Translate(pos);

        defaultShader->Bind();
        defaultShader->SetUniformMatrix4x4("u_ViewProjection", renderer.GetViewProjectionMatrix() * translationMatrix);

		renderer.Draw(vertexArray);

        /*ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Transform");
        ImGui::SliderFloat3("Position", pos.Data(), -200.0f, 0);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

        renderer.DisplayBuffer();
    }

    return 0;
}
