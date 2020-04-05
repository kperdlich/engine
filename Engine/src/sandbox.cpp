#include "platform.h"

#ifndef WINDOWS
	#include "cryengineLogo_png.h"
#endif 

int main(int args, char** argv)
{
	std::shared_ptr<renderer::Renderer> renderer = std::make_shared<renderer::Renderer>(true);
    renderer->SetZModeEnabled(true);
    renderer->SetClearColor(renderer::ColorRGBA::WHITE);
    renderer->SetCullMode(renderer::CullMode::None);

	std::shared_ptr<input::InputManager> input = std::make_shared<input::InputManager>();
	
	gEnv->Renderer = renderer;
	gEnv->Input = input;

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

#ifdef WINDOWS
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
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255,
		255, 255, 0, 255,
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
    
    math::Vector3f pos = { -91.0f, -126.0f, -195.0f };	
	//math::Vector3f pos = { .0f, 0.0f, 0.0f };

	math::Vector3f rotation = { 0.0f, 0.0f, 0.0f };
	math::Vector3f scale = { 1.0f, 1.0f, 1.0f };

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
		renderer->LoadModelMatrix(translationMatrix * rotationMatrix * scaleMatrix);
        
		texture->Bind();
		
		renderer->Draw(vertexArray);      
		
		const float aValue = gEnv->Input->GetInputValue(input::KEYCODE_LEFT);
		const float dValue = gEnv->Input->GetInputValue(input::KEYCODE_RIGHT);
		const float wValue = gEnv->Input->GetInputValue(input::KEYCODE_UP);
		const float SValue = gEnv->Input->GetInputValue(input::KEYCODE_DOWN);

		//pos += math::Vector3f{ dValue - aValue, wValue - SValue, 0.0f };
		//rotation += math::Vector3f{ 0.0f, 0.0f,  wValue - SValue };
		//scale += math::Vector3f{ 0.0f, 0.0f, wValue - SValue };
		
        ImGui::Begin("Transform");
		ImGui::SliderFloat3("Position", pos.Data(), -200.0f, 200);
		ImGui::SliderFloat3("Rotation", rotation.Data(), 0.0f, 360);
		ImGui::SliderFloat3("Scale", scale.Data(), 0.0f, 50);
		ImGui::End();

        renderer->DisplayBuffer();
    }

    return 0;
}
