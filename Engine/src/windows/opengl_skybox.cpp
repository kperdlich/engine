#include "opengl_skybox.h"
#include "platform.h"

static constexpr char* VERTEX_SHADER =
	R"(#version 330
	layout(location = 0) in vec3 in_Position;
	out vec3 texCoords;
	uniform mat4 u_ViewProjection;
	void main()
	{
		texCoords = in_Position;
		vec4 pos = u_ViewProjection * vec4(in_Position, 1.0);
		gl_Position = pos.xyww;		
	})";

static constexpr char* FRAGMENT_SHADER =
	R"(#version 330
	in vec3 texCoords;
	out vec4 out_color;
	uniform samplerCube u_skybox;
	uniform vec4 u_ambientColor;
	void main()
	{
		out_color = (u_ambientColor / 255.0f) * texture(u_skybox, texCoords);
	})";

std::vector<float> vertices =
{
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
};

std::vector<uint32_t> indices =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};


renderer::Skybox::Skybox(uint32_t textureSlot)
{
	//glActiveTexture(GL_TEXTURE0 + textureSlot);
	//glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &mTextureID);
	mVertexArray = renderer::VertexArray::Create();
	mVertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Position,
			renderer::VertexAttributeComponentType::Position_XYZ,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float))
	);

	mIndexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));
	mShader = renderer::Shader::Create(VERTEX_SHADER, FRAGMENT_SHADER);
}

void renderer::Skybox::Render(renderer::Renderer& renderer)
{	
	renderer.BindShader(mShader);		

	math::Matrix4x4 skyBoxViewMatrix = renderer.GetViewMatrix();
	skyBoxViewMatrix[0][3] = 0; 
	skyBoxViewMatrix[1][3] = 0;
	skyBoxViewMatrix[2][3] = 0;

	mShader->SetUniformMatrix4x4("u_ViewProjection", renderer.GetProjectionMatrix() * skyBoxViewMatrix);
	mShader->SetUniformColorRGBA("u_ambientColor", mAmbientColor);
	mShader->SetUniformSampler2D("u_skybox", 0);

	mVertexArray->Bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);		
	mIndexBuffer->Bind();	

	glDepthFunc(GL_LEQUAL);
	mIndexBuffer->Draw();	
	glDepthFunc(GL_LESS);
}

void renderer::Skybox::SetRight(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Right);
}

void renderer::Skybox::SetLeft(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Left);
}

void renderer::Skybox::SetTop(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Top);
}

void renderer::Skybox::SetBottom(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Bottom);
}

void renderer::Skybox::SetFront(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Front);
}

void renderer::Skybox::SetBack(std::shared_ptr<renderer::Image2D> image)
{
	CreateCubemapTexture(image, Back);
}

void renderer::Skybox::SetAmbientColor(const renderer::ColorRGBA& color)
{
	mAmbientColor = color;
}

void renderer::Skybox::CreateCubemapTexture(std::shared_ptr<renderer::Image2D> image, CubemapSlots cubemapSlot)
{	
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (uint8_t) cubemapSlot, 0, GL_RGBA, image->Width(), image->Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->Data());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
