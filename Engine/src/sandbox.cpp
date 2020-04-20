#include "platform.h"
#include "third-party/tiny_obj_loader.h"
#include "mesh.h"
#include "obj_loader.h"
#include "opengl_skybox.h"

#ifndef WINDOWS
	#include "cryengineLogo_png.h"
#endif 

int main(int args, char** argv)
{
	std::shared_ptr<renderer::Renderer> renderer = std::make_shared<renderer::Renderer>(true);
    renderer->SetZModeEnabled(true);
    renderer->SetClearColor(renderer::ColorRGBA::BLACK);
    renderer->SetCullMode(renderer::CullMode::Back);

	std::shared_ptr<input::InputManager> input = std::make_shared<input::InputManager>();
	std::shared_ptr<core::ResourceManager> resourceManager = std::make_shared<core::ResourceManager>();
	
	gEnv->Renderer = renderer;
	gEnv->Input = input;
	gEnv->ResourceManager = resourceManager;

    std::shared_ptr<renderer::Camera> orthographicCamera = renderer::Camera::CreateOrthographic(math::Vector3f{ .0f, .0f, .1f },
        math::Vector3f{ .0f, 1.0f, .0f },
        math::Vector3f{ .0f, .0f, -1.0f }
	);

    orthographicCamera->SetFrustrum(renderer->GetHeight(), 0, 0, renderer->GetWidth(), 0, 100.0f);

    std::shared_ptr<renderer::Camera> perspectiveCamera = renderer::Camera::CreatePerspective(math::Vector3f{ .0f, .0f, .1f },
        math::Vector3f{ .0f, 1.0f, .0f },
        math::Vector3f{ .0f, .0f, -1.0f });
    perspectiveCamera->SetFrustrum(0.1f, 500.0f, 70.0f, (float)renderer->GetWidth() / (float)renderer->GetHeight());
    renderer->SetCamera(perspectiveCamera);

	std::shared_ptr<renderer::Shader> defaultShader = renderer::Shader::CreateNormalTexture();

	std::shared_ptr<renderer::Skybox> skybox = std::make_shared<renderer::Skybox>();	
	skybox->SetPositiveX(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/right.png"));
	skybox->SetNegativeX(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/left.png"));
	skybox->SetPositiveY(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/top.png"));
	skybox->SetNegativeY(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/bottom.png"));
	skybox->SetPositiveZ(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/front.png"));
	skybox->SetNegativeZ(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/back.png"));

	//auto meshes = core::LoadMeshesFromObj("I:/Engine/assets/gun/gun.obj", "I:/Engine/assets/gun");
	auto meshes = core::LoadMeshesFromObj("I:/Engine/assets/nanosuit/nanosuit.obj", "I:/Engine/assets/nanosuit");
	//auto meshes = core::LoadMeshesFromObj("I:/Engine/assets/Box/box_stack.obj", "I:/Engine/assets/Box");

	//std::shared_ptr<renderer::Image2D> image = renderer::Image2D::LoadFromFile("I:/Engine/assets/gun/textures/handgun_C.png");
	//std::shared_ptr<renderer::Texture2D> texture = std::make_shared<renderer::Texture2D>(*image);

/*#ifdef WINDOWS
	std::shared_ptr<renderer::Image2D> image = renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/cryengineLogo.png");
#else
	std::shared_ptr<renderer::Image2D> image = renderer::Image2D::Create(cryengineLogo_png, cryengineLogo_png_size);
#endif

	
	std::shared_ptr<renderer::Texture2D> texture = std::make_shared<renderer::Texture2D>(*image);
	texture->Bind();
	

    std::vector<float> vertices = {
        0.0f, 0.0f, -0.5f, // lower-left
        0.0f, 200.0f, -0.5f, // top-left
        200.0f, 200.0f, -0.5f, // top right
		200.0f, 0.0f, -0.5f // lower-right
    };

	std::vector<float> texCoords = {
		0.0f, 1.0f,  // lower-left corner  
		0.0f, 0.0f,  // top-left corner
		1.f, 0.0f,   // top-right corner
		1.0f, 1.0f   // lower-right corner
	};

    std::vector<uint8_t> colors = {
        255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
    };

    std::vector<uint32_t> indices =
    {
        0,
        1,
        2,
		2,
		3,
		0
    };

    std::shared_ptr<renderer::Shader> defaultShader = renderer::Shader::CreateDefaultTexture();
    std::shared_ptr<renderer::VertexArray> vertexArray = renderer::VertexArray::Create();
    std::shared_ptr<renderer::IndexBuffer> indexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));

    vertexArray->SetIndexBuffer(indexBuffer);

    vertexArray->AddVertexBuffer(
        renderer::VertexFormatAttribute
        {
            renderer::VertexDataInputType::Index,
            renderer::VertexAttribute::Position,
            renderer::VertexAttributeComponentType::Position_XYZ,
            renderer::VertexAttributeComponentTypeSize::Float32
        },
        renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float))
	);

    vertexArray->AddVertexBuffer(
        renderer::VertexFormatAttribute
        {
            renderer::VertexDataInputType::Index,
            renderer::VertexAttribute::Color,
            renderer::VertexAttributeComponentType::Color_RGBA,
            renderer::VertexAttributeComponentTypeSize::RGBA8
        },
        renderer::VertexBuffer::Create(colors.data(), colors.size() * sizeof(int8_t))
	);

	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Texture,
			renderer::VertexAttributeComponentType::Texture_ST,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(texCoords.data(), texCoords.size() * sizeof(float))
	);
    */
    math::Vector3f pos = { -91.0f, -126.0f, -195.0f };	
	//math::Vector3f pos = { .0f, 0.0f, 0.0f };

	math::Vector3f rotation = { 0.0f, 0.0f, 0.0f };
	math::Vector3f scale = { 10.0f, 10.0f, 10.0f };

    while (renderer->IsRunning() && gEnv->Input->GetState(input::KEYCODE_ESC) != input::ButtonState::Pressed)
    {
        renderer->PreDraw();
		renderer->BindShader(defaultShader);

        math::Matrix4x4 translationMatrix, rotationMatrix, scaleMatrix;
        translationMatrix.Translate(pos);
		rotationMatrix.Rotate('X', rotation.X());
		rotationMatrix.Rotate('Y', rotation.Y());
		rotationMatrix.Rotate('Z', rotation.Z());
		scaleMatrix.Scale(scale.X(), scale.Y(), scale.Z());	
		renderer->LoadModelMatrix(translationMatrix* rotationMatrix* scaleMatrix);

		for (auto& mesh : meshes)
		{
			renderer->Draw(*mesh);
		}		

		skybox->Render(*renderer);
		
		const float aValue = gEnv->Input->GetInputValue(input::KEYCODE_LEFT);
		const float dValue = gEnv->Input->GetInputValue(input::KEYCODE_RIGHT);
		const float wValue = gEnv->Input->GetInputValue(input::KEYCODE_UP);
		const float SValue = gEnv->Input->GetInputValue(input::KEYCODE_DOWN);

		perspectiveCamera->Rotate(dValue - aValue, wValue - SValue);

		//pos += math::Vector3f{ dValue - aValue, wValue - SValue, 0.0f };
		//rotation += math::Vector3f{ 0.0f, 0.0f, 0.0f};
		//scale += math::Vector3f{ 0.0f, 0.0f, 0.0f };
		
        ImGui::Begin("Transform");
		ImGui::SliderFloat3("Position", pos.Data(), -200.0f, 200);
		ImGui::SliderFloat3("Rotation", rotation.Data(), 0.0f, 360);
		ImGui::SliderFloat3("Scale", scale.Data(), 0.0f, 50);
		ImGui::End();

        renderer->DisplayBuffer();
    }

    return 0;
}
