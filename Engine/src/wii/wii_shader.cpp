#include "wii_shader.h"

// WII doesn't support shader!

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultColor()
{
	return Create("", "");
}

std::shared_ptr<renderer::Shader> renderer::Shader::CreateDefaultTexture()
{
	return Create("", "");
}

std::shared_ptr<renderer::Shader> renderer::Shader::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	return {};
}

void renderer::Shader::Bind()
{
}

void renderer::Shader::Unbind()
{	
}

void renderer::Shader::SetUniformInt32(const std::string& uniformName, int32_t value)
{	
}

void renderer::Shader::SetUniformFloat(const std::string& uniformName, float value)
{	
}

void renderer::Shader::SetUniformColorRGB(const std::string& uniformName, const renderer::ColorRGBA& value)
{
	
}

void renderer::Shader::SetUniformColorRGBA(const std::string& uniformName, const renderer::ColorRGBA& value)
{
	
}

void renderer::Shader::SetUniformFloat3(const std::string& uniformName, const math::Vector3f& value)
{
	
}

void renderer::Shader::SetUniformFloat4(const std::string& uniformName, const math::Vector4f& value)
{	
}

void renderer::Shader::SetUniformMatrix4x4(const std::string& uniformName, const math::Matrix4x4& value)
{	
}
