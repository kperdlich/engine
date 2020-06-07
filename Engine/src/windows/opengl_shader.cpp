#include <array>
#include <vector>
#include <fstream>
#include <string>
#include "glm/gtc/type_ptr.hpp"
#include "opengl_shader.h"

renderer::Shader::Shader(uint32_t programId) 
	: mProgramId(programId) {}

renderer::Shader::~Shader()
{
	glDeleteProgram(mProgramId);
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultColorPong()
{
	return LoadFromFile("I:/Engine/assets/shader/glsl/pong/color_pong_vertex.glsl", "I:/Engine/assets/shader/glsl/pong/color_pong_fragment.glsl");
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultColorGouraud()
{
	return LoadFromFile("I:/Engine/assets/shader/glsl/gouraud/color_gouraud_vertex.glsl", "I:/Engine/assets/shader/glsl/gouraud/color_gouraud_fragment.glsl");
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultTexture()
{
	return LoadFromFile("I:/Engine/assets/shader/glsl/texture/texture_vertex.glsl", "I:/Engine/assets/shader/glsl/texture/texture_fragment.glsl");
}

std::shared_ptr<renderer::Shader> renderer::Shader::LoadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::ifstream vertexShaderStream(vertexShaderPath);
	ASSERT(vertexShaderStream.is_open());
	std::ifstream fragmentShaderStream(fragmentShaderPath);
	ASSERT(fragmentShaderStream.is_open());
	std::string vertexShaderLine;
	std::string fragmentShaderLine;
	std::string fragmentShaderSource;
	std::string vertexShaderSource;

	while (std::getline(vertexShaderStream, vertexShaderLine)) 
	{
		vertexShaderSource.append(vertexShaderLine).append("\n");
	}

	while (std::getline(fragmentShaderStream, fragmentShaderLine))
	{
		fragmentShaderSource.append(fragmentShaderLine).append("\n");
	}

	return Create(vertexShaderSource, fragmentShaderSource);
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