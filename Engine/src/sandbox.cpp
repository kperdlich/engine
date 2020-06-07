#include "platform.h"
#include "primitive_plane.h"
//#include "third-party/tiny_obj_loader.h"
//#include "windows/obj_loader.h"
//#include "mesh.h"

#ifndef WINDOWS
	#include "cryengineLogo_png.h"
	#include "back_png.h"
	#include "bottom_png.h"
	#include "front_png.h"
	#include "left_png.h"
	#include "right_png.h"
	#include "top_png.h"
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

	std::shared_ptr<renderer::Shader> textureShader = renderer::Shader::CreateDefaultTexture();
	std::shared_ptr<renderer::Shader> colorShaderPong = renderer::Shader::CreateDefaultColorPong();
	std::shared_ptr<renderer::Shader> colorShaderGouraud = renderer::Shader::CreateDefaultColorGouraud();

	std::shared_ptr<renderer::Skybox> skybox = std::make_shared<renderer::Skybox>();		
#ifndef WINDOWS
	skybox->SetRight(renderer::Image2D::Create(right_png, right_png_size));
	skybox->SetLeft(renderer::Image2D::Create(left_png, left_png_size));
	skybox->SetTop(renderer::Image2D::Create(top_png, top_png_size));
	skybox->SetBottom(renderer::Image2D::Create(bottom_png, bottom_png_size));
	skybox->SetFront(renderer::Image2D::Create(front_png, front_png_size));
	skybox->SetBack(renderer::Image2D::Create(back_png, back_png_size));

	auto image = renderer::Image2D::Create(right_png, right_png_size);

#else 
	skybox->SetRight(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/right.png"));
	skybox->SetLeft(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/left.png"));
	skybox->SetTop(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/top.png"));
	skybox->SetBottom(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/bottom.png"));
	skybox->SetFront(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/front.png"));
	skybox->SetBack(renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/back.png")); 

	auto image = renderer::Image2D::LoadFromFile("I:/Engine/assets/textures/skybox/right.png");
#endif 
	
	auto material = std::make_shared<renderer::Material>();
	material->SetTexture(std::make_shared<renderer::Texture2D>(*image));

	std::unique_ptr<renderer::Mesh> planeColor = primitive::CreatePlaneMesh();
	std::unique_ptr<renderer::Mesh> planeTexture = primitive::CreatePlaneMesh();
	planeTexture->SetMaterial(material);

	//auto meshes = core::LoadMeshesFromObj("I:/Engine/assets/gun/gun.obj", "I:/Engine/assets/gun");
	//auto meshes = core::LoadMeshesFromObj("I:/Engine/assets/nanosuit/nanosuit.obj", "I:/Engine/assets/nanosuit");
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
    math::Vector3f pos = { .0f, .0f, -10.0f };	
	//math::Vector3f pos = { .0f, 0.0f, 0.0f };

	math::Vector3f rotation = { 0.0f, 0.0f, 0.0f };
	math::Vector3f scale = { 1.0f, 1.0f, 1.0f };

	float ambietStrength = .1f;
	float specularStrength = .5f;
	float specularShininess = 32.0f;

	bool perFragmentLight = true;


	math::Vector3f lightPositon = { 0.0f, .0f, -10.0f };

	renderer::ColorRGBA ambientLight = { 255, 128, 12, 255 };
    while (renderer->IsRunning() && gEnv->Input->GetState(input::KEYCODE_ESC) != input::ButtonState::Pressed)
    {
        renderer->PreDraw();

		// https://www.learnopengles.com/tag/gouraud-shading/ Implement vertex lighting using Gouraud shading


		skybox->SetAmbientColor(ambientLight);
		skybox->Render(*renderer);

		{
			math::Matrix4x4 translationMatrix, rotationMatrix, scaleMatrix;
			translationMatrix.Translate(.0f, .0f, -10.0f);
			rotationMatrix.Rotate('X', rotation.X());
			rotationMatrix.Rotate('Y', rotation.Y());
			rotationMatrix.Rotate('Z', rotation.Z());
			scaleMatrix.Scale(10.0f, 10.0f, 10.0f);
			renderer->BindShader(perFragmentLight ? colorShaderPong : colorShaderGouraud);
			colorShaderPong->SetUniformFloat("u_ambientStrength", ambietStrength);
			colorShaderPong->SetUniformFloat("u_specularStrength", specularStrength);
			colorShaderPong->SetUniformFloat("u_specularShininess", specularShininess);
			colorShaderPong->SetUniformColorRGBA("u_ambientColor", ambientLight);
			colorShaderPong->SetUniformFloat3("u_lightPosition", lightPositon);
			colorShaderPong->SetUniformFloat3("u_viewPos", perspectiveCamera->Position());
			math::Matrix4x4 model = translationMatrix * rotationMatrix * scaleMatrix;
			colorShaderPong->SetUniformMatrix4x4("u_model", model);
			colorShaderPong->SetUniformMatrix4x4("u_normalMtx", model.Inverse().Transpose());
			renderer->LoadModelMatrix(model);
			renderer->Draw(*planeColor);
		}
		{
			math::Matrix4x4 translationMatrix, rotationMatrix, scaleMatrix;
			translationMatrix.Translate(lightPositon);
			rotationMatrix.Rotate('X', rotation.X());
			rotationMatrix.Rotate('Y', rotation.Y());
			rotationMatrix.Rotate('Z', rotation.Z());
			scaleMatrix.Scale(1.0f, 1.0f, 1.0f);
			renderer->BindShader(textureShader);
			textureShader->SetUniformFloat("ambientStrength", ambietStrength);
			textureShader->SetUniformColorRGBA("ambientColor", ambientLight);
			renderer->LoadModelMatrix(translationMatrix* rotationMatrix* scaleMatrix);
			renderer->Draw(*planeTexture);
		}

		//renderer->DrawRay({ 0.0f, 0.0f, 0.0f }, math::Vector3f::Forward * 50.0f, renderer::ColorRGBA::GREEN);

		
		//for (auto& mesh : meshes)
		//{
		//	renderer->Draw(*mesh);
		//}		

		const float aValue = gEnv->Input->GetInputValue(input::KEYCODE_LEFT);
		const float dValue = gEnv->Input->GetInputValue(input::KEYCODE_RIGHT);
		const float wValue = gEnv->Input->GetInputValue(input::KEYCODE_UP);
		const float SValue = gEnv->Input->GetInputValue(input::KEYCODE_DOWN);

		perspectiveCamera->Rotate(dValue - aValue, 0.0f);
		//perspectiveCamera->SetPosition(perspectiveCamera->Position() + math::Vector3f{ .0f, .0f, wValue - SValue });
		perspectiveCamera->Move(renderer::CameraMovementDirection::FORWARD, wValue - SValue);

		//pos += math::Vector3f{ dValue - aValue, wValue - SValue, 0.0f };
		//rotation += math::Vector3f{ 0.0f, 0.0f, 0.0f};
		//scale += math::Vector3f{ 0.0f, 0.0f, 0.0f };
		
        ImGui::Begin("Transform");
		ImGui::SliderFloat3("Position", pos.Data(), -200.0f, 200.0f);
		ImGui::SliderFloat3("Rotation", rotation.Data(), 0.0f, 360.0f);
		ImGui::SliderFloat3("Scale", scale.Data(), 0.0f, 50.0f);		
		ImGui::Text("Camera Position %f %f %f", perspectiveCamera->Position().X(), perspectiveCamera->Position().Y(), perspectiveCamera->Position().Z());
		ImGui::Text("Light");
		ImGui::SliderFloat3("Light Pos", lightPositon.Data(), -10.0f, 10.0f);
		ImGui::SliderU8Int4("Ambient Color", ambientLight.Data(), 0.0f, 255.0);
		ImGui::SliderFloat("Ambient Strength", &ambietStrength, 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strength", &specularStrength, 0.0f, 1.0f);		
		ImGui::SliderFloat("Specular Shininess", &specularShininess, 0.0f, 256.0f);
		ImGui::Checkbox("Per Fragment Light", &perFragmentLight);
		ImGui::End();
		
		//ambientLight.Data()[0] += wValue - SValue;

		
		renderer->DisplayBuffer();
    }

    return 0;
}
