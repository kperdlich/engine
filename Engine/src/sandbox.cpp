#include "platform.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

int main(int args, char** argv)
{	
	renderer::Renderer renderer(false);
	renderer.SetZModeEnabled(true);
	renderer.SetClearColor(renderer::ColorRGBA::BLUE);

	std::shared_ptr<renderer::Camera> perspectiveCamera = std::make_shared<renderer::Camera>(math::Vector3f{ .0f, .0f, .1f },
		math::Vector3f{ .0f, 1.0f, .0f },
		math::Vector3f{ .0f, .0f, -1.0f },
		false);
	perspectiveCamera->SetFrustrum(renderer.GetHeight(), 0, 0, renderer.GetWidth(), 0, 100.0f);
	renderer.SetCamera(perspectiveCamera);

	std::vector<float> vertices = { 
		0.0f, 0.0f, 0.0f,
		100.0f, 300.0f, 0.0f,
		200.0f, 0.0f, 0.0f
	};	

	std::vector<float> colors = {
		255.0f, .0f, 0.0f,
		00.0f, 0.0f, 255.0f,
		.0f, 255.0f, .0f
	};

	std::vector<uint32_t> indices =
	{
		0, 1, 2
	};

	std::shared_ptr<renderer::Shader> defaultShader = renderer::Shader::CreateDefaultColor();
	std::shared_ptr<renderer::VertexArray> vertexArray = renderer::VertexArray::Create();
	std::shared_ptr<renderer::IndexBuffer> indexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));

	vertexArray->SetIndexBuffer(indexBuffer);

	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexAttribute::Position,
			renderer::VertexAttributeComponentType::Position_XYZ,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float))); 

	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexAttribute::Color,
			renderer::VertexAttributeComponentType::Color_RGB,
			renderer::VertexAttributeComponentTypeSize::Float32 
		},
		renderer::VertexBuffer::Create(colors.data(), colors.size() * sizeof(float)));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)renderer.GetWindowHandle(), false);
	ImGui_ImplOpenGL3_Init(nullptr);
	ImGui::StyleColorsDark();

	math::Vector3f pos = { 0.0f, 0.0f, 0.0f };
	while (renderer.IsRunning())
	{
		renderer.PreDraw();		

		math::Matrix4x4 translationMatrix = math::Matrix4x4::Identity();
		translationMatrix.Translate(pos);

		defaultShader->Bind();		
		defaultShader->SetUniformMatrix4x4("u_ViewProjection", perspectiveCamera->GetProjectionMatrix4x4() * perspectiveCamera->GetViewMatrix4x4() 
			* translationMatrix);
		/*		
		glm::vec3 vecPos = { 0.0f, 0.0f, .1f };
		glm::vec3 vecCamUp = { .0f, 1.0f, .0f };
		glm::vec3 vecLookAt = { perspectiveCamera->Forward().X() + 0.0f, perspectiveCamera->Forward().Y() + 0.0f, perspectiveCamera->Forward().Z() 
		 + 0.1f};		

		defaultShader->SetUniformGLM("u_ViewProjection", 
			glm::ortho(0.0f, (float)renderer.GetWidth(), 0.0f, (float)renderer.GetHeight(), 0.0f, 100.0f)
			* glm::lookAt(vecPos, vecLookAt, vecCamUp) * glm::translate(glm::mat4(1), pos));*/

		//defaultShader->SetUniformColorRGB("u_Color", renderer::ColorRGBA::YELLOW);
		vertexArray->Bind(); 
		indexBuffer->Draw();	

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();
		ImGui::Begin("Transform");
		ImGui::SliderFloat3("Position", pos.Data(), 0.0f, 1024.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderer.DisplayBuffer();
	}

	return 0;
}