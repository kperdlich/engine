#include <array>
#include <vector>
#include "glm/gtc/type_ptr.hpp"
#include "opengl_shader.h"

static constexpr char* DEFAULT_VERTEX_SHADER_COLOR =
	R"(#version 330
	layout(location = 0) in vec3 in_Position;
	layout(location = 1) in vec4 in_Color;
	layout(location = 2) in vec3 in_Normal;
	out vec4 color;
	out vec3 normal;
	out vec3 fragPos;
	uniform mat4 u_mvp;
	uniform mat4 u_model;
	uniform mat4 u_normalMtx;
	void main()
	{		
		fragPos = vec3(u_model * vec4(in_Position, 1.0));
		gl_Position = u_mvp * vec4(in_Position, 1.0);
		normal = mat3(u_normalMtx) * in_Normal;
		color = in_Color;
	})";

static constexpr char* DEFAULT_FRAGMENT_SHADER_COLOR =
	R"(#version 330
	in vec3 fragPos;
	in vec4 color;
	in vec3 normal;

	out vec4 out_color;

	uniform float u_ambientStrength;
	uniform float u_specularStrength;
	uniform float u_specularShininess;
	uniform vec4 u_ambientColor;
	uniform vec3 u_lightPosition;
	uniform vec3 u_viewPos;

	void main()
	{
		vec3 lightColor = vec3(u_ambientColor.xyz / 255);

		// ambient
		vec3 ambient = u_ambientStrength * lightColor;

		// diffuse
		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(u_lightPosition - fragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;		

		// specular
		vec3 viewDir = normalize(u_viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_specularShininess);
		vec3 specular = u_specularStrength * spec * lightColor;
	
		vec3 result = (ambient + diffuse + specular) * vec3(color.xyz / 255.0);
		out_color = vec4(result, 1.0);
		
	})";

static constexpr char* DEFAULT_VERTEX_SHADER_TEXTURE =
	R"(#version 330
	layout(location = 0) in vec3 in_position;
	layout(location = 1) in vec4 in_Color;
	layout(location = 2) in vec3 in_Normals;
	layout(location = 3) in vec2 in_TexCoord;
	out vec4 color;
	out vec2 texCoord;
	uniform mat4 u_mvp;
	void main()
	{
		gl_Position = u_mvp * vec4(in_position, 1.0);
		color = in_Color;
		texCoord = in_TexCoord;
	})";

static constexpr char* DEFAULT_FRAGMENT_SHADER_TEXTURE = 
	R"(#version 330
	in vec4 color;
	in vec2 texCoord;
	out vec4 out_color;
	uniform sampler2D texture2d;
	uniform float ambientStrength;
	uniform vec4 ambientColor;
	void main()
	{
		vec4 object_color = texture(texture2d, texCoord) * vec4(color.xyzw / 255);

		vec3 ambient = ambientStrength * vec3(ambientColor.xyz / 255);
		out_color = vec4(ambient.xyz, ambientColor.w / 255) * object_color;;
	})";

renderer::Shader::Shader(uint32_t programId) 
	: mProgramId(programId) {}

renderer::Shader::~Shader()
{
	glDeleteProgram(mProgramId);
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultColor()
{
	return Create(DEFAULT_VERTEX_SHADER_COLOR, DEFAULT_FRAGMENT_SHADER_COLOR);
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultTexture()
{
	return Create(DEFAULT_VERTEX_SHADER_TEXTURE, DEFAULT_FRAGMENT_SHADER_TEXTURE);
}

std::shared_ptr<renderer::Shader> renderer::Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	const std::array<ShaderSourceInfo, 2> shaderSourceInfos = {
		ShaderSourceInfo {GL_VERTEX_SHADER, vertexShaderSource},
		ShaderSourceInfo {GL_FRAGMENT_SHADER, fragmentShaderSource}
	};
	std::vector<GLint> shaderIds;
	shaderIds.reserve(2);

	const GLuint programId = glCreateProgram();	

	for (const auto& shaderSourceInfo : shaderSourceInfos)
	{
		const GLuint shaderId = glCreateShader(shaderSourceInfo.Type);
		const GLchar* shaderSourceCstr = shaderSourceInfo.Source.c_str();
		glShaderSource(shaderId, 1, &shaderSourceCstr, 0);
		glCompileShader(shaderId);
		GLint isShaderCompiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isShaderCompiled);
		if (isShaderCompiled == GL_FALSE)
		{
			GLint logLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> logMsg(logLength);			
			glGetShaderInfoLog(shaderId, logLength, &logLength, &logMsg[0]);
			glDeleteShader(shaderId);

			std::cout << "Shader compilation error: " << &logMsg[0] << std::endl;
			ASSERT(false);
		}
		shaderIds.push_back(shaderId);
		glAttachShader(programId, shaderId);
	}

	glLinkProgram(programId);
	GLint isProgramLinked = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
	if (isProgramLinked == GL_FALSE) 
	{
		GLint logLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> logMsg(logLength);
		logMsg.reserve(logLength);
		glGetProgramInfoLog(programId, logLength, &logLength, &logMsg[0]);
		glDeleteProgram(programId);

		for (const GLuint id : shaderIds) 
		{
			glDetachShader(programId, id);
			glDeleteShader(id);
		}

		std::cout << "Shader link error: " << &logMsg[0] << std::endl;
		ASSERT(false);
	}

	for (const GLuint id : shaderIds)
	{
		glDetachShader(programId, id);
		glDeleteShader(id);
	}	

	return std::shared_ptr<Shader>(new Shader(programId));
}

void renderer::Shader::Bind()
{
	glUseProgram(mProgramId);
}

void renderer::Shader::Unbind()
{
	glUseProgram(0);
}

void renderer::Shader::SetUniformInt32(const std::string& uniformName, int32_t value)
{	
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform1i(location, value);
}

void renderer::Shader::SetUniformFloat(const std::string& uniformName, float value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform1f(location, value);
}

void renderer::Shader::SetUniformColorRGB(const std::string& uniformName, const renderer::ColorRGBA& value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform3f(location, value.Red(), value.Green(), value.Blue());
}

void renderer::Shader::SetUniformColorRGBA(const std::string& uniformName, const renderer::ColorRGBA& value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform4f(location, value.Red(), value.Green(), value.Blue(), value.Alpha());
}

void renderer::Shader::SetUniformFloat3(const std::string& uniformName, const math::Vector3f& value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform3f(location, value.X(), value.Y(), value.Z());
}

void renderer::Shader::SetUniformFloat4(const std::string& uniformName, const math::Vector4f& value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform4f(location, value.X(), value.Y(), value.Z(), value.W());
}

void renderer::Shader::SetUniformMatrix4x4(const std::string& uniformName, const math::Matrix4x4& value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	const float mtx[16] = 
	{	
		value.mMatrix[0][0], value.mMatrix[1][0], value.mMatrix[2][0], value.mMatrix[3][0],
		value.mMatrix[0][1], value.mMatrix[1][1], value.mMatrix[2][1], value.mMatrix[3][1],
		value.mMatrix[0][2], value.mMatrix[1][2], value.mMatrix[2][2], value.mMatrix[3][2],
		value.mMatrix[0][3], value.mMatrix[1][3], value.mMatrix[2][3], value.mMatrix[3][3]
	};
	glUniformMatrix4fv(location, 1, GL_FALSE, mtx);
}

void renderer::Shader::SetUniformSampler2D(const std::string& uniformName, uint32_t value)
{
	const GLint location = glGetUniformLocation(mProgramId, uniformName.c_str());
	glUniform1i(location, value);
}
