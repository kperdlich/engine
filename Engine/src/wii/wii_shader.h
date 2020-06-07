#pragma once
#include "wii_defines.h"
#include "vector3f.h"
#include "vector4f.h"
#include "matrix4x4.h"
#include "colorrgba.h"

namespace renderer {
	class Shader
	{
	public:
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;
		static std::shared_ptr<Shader> CreateDefaultColorPong();
		static std::shared_ptr<Shader> CreateDefaultColorGouraud();
		static std::shared_ptr<Shader> CreateDefaultTexture();
		static std::shared_ptr<Shader> Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

		void Bind();
		void Unbind();

		void SetUniformInt32(const std::string& uniformName, int32_t value);
		void SetUniformFloat(const std::string& uniformName, float value);
		void SetUniformColorRGB(const std::string& uniformName, const renderer::ColorRGBA& value);
		void SetUniformColorRGBA(const std::string& uniformName, const renderer::ColorRGBA& value);
		void SetUniformFloat3(const std::string& uniformName, const math::Vector3f& value);
		void SetUniformFloat4(const std::string& uniformName, const math::Vector4f& value);
		void SetUniformMatrix4x4(const std::string& uniformName, const math::Matrix4x4& value);
	};
}